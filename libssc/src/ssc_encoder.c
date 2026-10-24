/* libssc â€” encoder entry points (ssc_encoder_* / ssc_encode).
 *
 * Ported stage by stage (libssc/PLAN.md, phase 3). Bit-exact so far: header,
 * byte budget, input processing (3a), silence flag and prefilter (3b), long
 * MDCT and headroom (3c), band analysis, transient decision and header flags
 * (3d), energy quantisation and bit allocation (3e). Still missing: PVQ
 * (quant_all_bands) and the final energy bits (3f).
 */
#include "ssc_encoder.h"

#include <stdlib.h>
#include <string.h>

#include "opus/entenc.h"
#include "opus/arch.h"
#include "opus/mathops.h"
#include "ssc_drc.h"
#include "ssc_internal.h"

_Static_assert(offsetof(SscEncoder, prefilter_period) == 0x38, "encoder layout");
_Static_assert(offsetof(SscEncoder, overlap_max) == 0x4c, "encoder layout");
_Static_assert(offsetof(SscEncoder, fs_mode) == 0x60, "encoder layout");
_Static_assert(offsetof(SscEncoder, tr_energy) == 0x7c, "encoder layout");
_Static_assert(offsetof(SscEncoder, tr_hp) == 0xc4, "encoder layout");
_Static_assert(offsetof(SscEncoder, frame_counter) == 0xd4, "encoder layout");
_Static_assert(offsetof(SscEncoder, biquad) == 0xd8, "encoder layout");
_Static_assert(offsetof(SscEncoder, in_mem) == 0x128, "encoder layout");
_Static_assert(sizeof(SscEncoder) == 0x130, "encoder layout");

int32_t in_shared[2 * (864 + SSC_OVERLAP)];
int32_t _pre_shared[2 * (864 + SSC_COMBFILTER_MAXPERIOD)];
ssc_stage_fn ssc_stage_hook;

/* Per-frame values shared between the stages of ssc_encode. */
typedef struct {
    int N, C, overlap;
    int nbCompressedBytes;   /* budget, at most 1275 */
    int nbAvailableBytes;
    int total_bits;
    int tell;                /* after the silence flag */
    int silence;
    int pitch_index;
    int16_t gain1;           /* quantised prefilter gain (0 when off) */
    int qg;
    int pf_on;
    /* 3d: band analysis */
    int32_t bandE[2 * SSC_NB_EBANDS];
    int16_t bandLogE[2 * SSC_NB_EBANDS];
    int16_t bandLogE2[2 * SSC_NB_EBANDS];
    int isTransient;
    int shortBlocks;         /* M (8) when transient, else 0 */
    int16_t tf_estimate;     /* Q14: .2 when the transient was patched in */
    int drop;                /* top bands not coded (UHQ bandwidth / 152k) */
    /* 3e: energy quantisation and allocation */
    int effectiveBytes;      /* = nbCompressedBytes (no VBR) */
    int tf_res[SSC_NB_EBANDS];
    int tf_select;
    int16_t error[2 * SSC_NB_EBANDS];
    int offsets[SSC_NB_EBANDS];
    int32_t total_boost;
    int dual_stereo;
    int alloc_trim;
    int anti_collapse_rsv;
    int32_t alloc_bits;      /* total passed to compute_allocation */
    int32_t balance;
    int codedBands;
    int pulses[SSC_NB_EBANDS];
    int fine_quant[SSC_NB_EBANDS];
    int fine_priority[SSC_NB_EBANDS];
} SscFrame;

SscStageAlloc ssc_stage_alloc;

const SscMode *ssc_custom_mode_create(int fs, int frame_size, int *err) {
    (void)frame_size; /* the blob ignores it: both modes are fixed at 864 */
    if (err) *err = 0;
    if (fs == 44100 || fs == 48000) return &ssc_mode_48k;
    if (fs == 96000) return &ssc_mode_96k;
    if (err) *err = -1;
    return NULL;
}

static int state_size(const SscMode *m, int channels) {
    return (m->nbEBands * 6 + m->overlap * 4 + 4 * SSC_COMBFILTER_MAXPERIOD) * channels + 300;
}

int ssc_encoder_get_size(int channels, int fs) {
    const SscMode *m = ssc_custom_mode_create(fs, SSC_FRAME_SIZE, NULL);
    return m ? state_size(m, channels) : 0;
}

int ssc_encoder_init(SscEncoder *st, int fs, int channels, int bit_depth) {
    const SscMode *m = ssc_custom_mode_create(fs, SSC_FRAME_SIZE, NULL);
    int ret;
    if (channels > 2) return -1;  /* blob: -1, and it touches st below anyway */
    if (!st || !m) return -7;
    memset(st, 0, state_size(m, channels));
    st->mode = m;
    st->overlap = m->overlap;
    st->channels = channels;
    st->end = m->effEBands;
    st->f18 = -1;
    st->spread_decision = 2;
    st->delayedIntra = 1;
    st->tonal_average = 256;
    ret = 0;
    st->fs_mode = fs == 48000 ? 44100 : fs;
    st->fs = fs;
    st->bit_depth = bit_depth;
    st->frame_counter = 0;
    st->hdr_low_bits = 1;
    previous_uhq_index = 0;
    SoundBooster_DRC_Init(fs, channels);
    SoundBooster_DRC_SetPar(1, 0x7b8e); /* blob also passes (0, 50000, 0), unused */
    return ret;
}

SscEncoder *ssc_encoder_create(int fs, int channels, int bit_depth, int *err) {
    const SscMode *m = ssc_custom_mode_create(fs, SSC_FRAME_SIZE, NULL);
    SscEncoder *st;
    int ret;
    if (!m) {
        if (err) *err = -1;
        return NULL;
    }
    st = (SscEncoder *)malloc(state_size(m, channels));
    if (!st) {
        if (err) *err = -7;
        return NULL;
    }
    ret = ssc_encoder_init(st, fs, channels, bit_depth);
    if (err) *err = ret;
    if (ret != 0) {
        free(st);
        return NULL;
    }
    return st;
}

void ssc_encoder_destroy(SscEncoder *st) { free(st); } /* blob: empty (leaks) */

/* Bitrate table from ssc_encode @0xd1d0..0xd47c. */
typedef struct {
    int32_t bitrate;
    uint8_t byte3;    /* (flags << 5) | rate index; flags may change later in the frame */
    uint8_t uhq;      /* header byte 1 carries the counter's high nibble */
    uint8_t wide;     /* no +3/128 budget boost */
    int32_t drc_gain; /* set_DRC_limit_gain(); narrow rates: >>8 unless 24-bit input */
} SscRate;

static const SscRate kRates[] = {
    {88000, 0xF0, 0, 0, 0x76F200},  {96000, 0xF1, 0, 0, 0x76F200},
    {128000, 0xF2, 0, 0, 0x78B400}, {192000, 0xF3, 0, 0, 0x7A9400},
    {229000, 0xF4, 0, 0, 0x7A9400}, {328000, 0xF5, 0, 1, 0x7B4C00},
    {256000, 0xF6, 0, 1, 0x79F800}, {291000, 0xE0, 1, 1, 0x7B4C00},
    {308000, 0xE1, 1, 1, 0x7B4C00}, {442000, 0xE2, 1, 1, 0x7B4C00},
    {584000, 0xE3, 1, 1, 0x7B4C00}, {886000, 0xE4, 1, 1, 0x7B4C00},
    {250000, 0xE5, 1, 1, 0x79F800}, {152000, 0xE6, 1, 1, 0x79F800},
};

static const SscRate *find_rate(int bitrate) {
    size_t i;
    for (i = 0; i < sizeof(kRates) / sizeof(kRates[0]); i++)
        if (kRates[i].bitrate == bitrate) return &kRates[i];
    return NULL;
}

/* Input processing before CELT (ssc_encode @0xd504..0xd688): a biquad copy of
 * the input drives CalculateLimitGain, then the DRC limiter rewrites pcm in
 * place in 8 blocks of frame_size/8 stereo frames. */
static void preprocess(SscEncoder *st, int32_t *pcm, int frame_size, int bitrate, int wide) {
    int32_t p_filtered, p_input, gain;
    int i, block = frame_size >> 2;
    if (!wide) {
        const int32_t *coef = bitrate <= 96000 ? coeffs96andbelow : coeffs;
        Biquad_Narrow_int2int_stereo(_pcmpower, pcm, coef, st->biquad, frame_size);
        powercalc(_pcmpower, frame_size, &p_filtered);
        powercalc(pcm, frame_size, &p_input);
        gain = CalculateLimitGain(p_filtered, p_input - p_filtered, bitrate, st->fs);
        if (st->bit_depth == 24) gain <<= 8;
    } else {
        Biquad_Narrow_int2int_stereo(_pcmpower, pcm, coeffs96andbelow, st->biquad, frame_size);
        powercalc(_pcmpower, frame_size, &p_filtered);
        powercalc(pcm, frame_size, &p_input);
        gain = CalculateLimitGain(p_filtered, p_input, bitrate, st->fs) << 8;
    }
    set_DRC_limit_gain(gain);
    for (i = 0; i < 8; i++) SoundBooster_DRC_Exe(pcm + i * block, frame_size >> 3);
}

/* max(max, -min) with max/min starting at 0, like celt_maxabs32. */
static int32_t maxabs32(const int32_t *x, int n) {
    int32_t mx = 0, mn = 0, neg;
    int i;
    for (i = 0; i < n; i++) {
        if (x[i] > mx) mx = x[i];
        if (x[i] < mn) mn = x[i];
    }
    neg = (int32_t)(0u - (uint32_t)mn);
    return mx <= neg ? neg : mx;
}

/* Silence flag and the CELT input buffer (ssc_encode @0xd690..0xdb90).
 * Samsung computes the pre-emphasis memory like Opus but never subtracts it:
 * `in` is just pcm << shift (4 for 24-bit input, 12 otherwise on narrow rates). */
static void silence_and_input(SscEncoder *st, const int32_t *pcm, ec_enc *enc, SscFrame *f,
                              int budget, int shift) {
    int N = f->N, ov = f->overlap, C = f->C, n1 = C * (N - ov), c, i;
    int tell0 = ec_tell(enc);
    int32_t sample_max = st->overlap_max, m;

    f->nbCompressedBytes = budget > 1275 ? 1275 : budget;
    /* st->f18 (Opus VBR target) is -1 for SSC: no VBR budget adjustment. */
    f->total_bits = f->nbCompressedBytes * 8;

    if (n1 < 1) {
        if (sample_max < 1) sample_max = 0;
    } else {
        m = maxabs32(pcm, n1);
        if (sample_max <= m) sample_max = m;
    }
    m = C * ov >= 1 ? maxabs32(pcm + n1, C * ov) : 0;
    st->overlap_max = m;
    if (sample_max <= m) sample_max = m;

    f->silence = 0;
    f->tell = tell0;
    if (tell0 == 1) {
        int sil = sample_max == 0;
        ec_enc_bit_logp(enc, sil, 15);
        if (sil) {  /* pretend the whole budget is used */
            enc->nbits_total = f->total_bits + EC_ILOG(enc->rng);
            f->tell = f->total_bits;
            f->silence = 1;
        }
    }
    f->nbAvailableBytes = f->nbCompressedBytes - ((tell0 + 4) >> 3);

    if (N < 1) return;
    for (c = 0; c < 2; c++) {  /* the blob hard-codes a stride of 2 */
        int32_t *dst = in_shared + c * (N + ov) + ov;
        uint32_t x;
        for (i = 0; i < N; i++) dst[i] = (int32_t)((uint32_t)pcm[2 * i + c] << shift);
        x = (uint32_t)dst[N - 1];
        st->preemph_memE[c] = (int32_t)(0u - ((uint32_t)(((int32_t)x >> 16) * 0xd99a) +
                                               (((x & 0xfff0) * 0x6ccd) >> 15)));
    }
}

/* MDCT of the prefiltered input (ssc_encode @0xe01c..0xe1a0). The spectrum
 * lives in _pre_shared after the FFT scratch, like the blob's. */
#define SSC_FREQ (_pre_shared + 1944)

/* Shared tail of the long and short MDCT paths. */
static void spectrum_fixup(SscEncoder *st, int bitrate, int wide) {
    const SscMode *m = st->mode;
    int32_t *freq = SSC_FREQ;
    int i, top;
    /* Narrow rates below 192k: nothing above the last band (M = 8 hard-coded). */
    top = m->eBands[st->end - 1];
    if (!wide && bitrate < 192000 && top < 108)
        for (i = top * 8; i < 864; i++) freq[i] = freq[i + 864] = 0;
    if (wide)
        uhq_headroom(freq, bitrate, 8, m->eBands);
    else
        normal_headroom(freq, bitrate, 8, m->eBands);
}

static void long_mdct(SscEncoder *st, SscFrame *f, int bitrate, int wide) {
    const SscMode *m = st->mode;
    int N = f->N, ov = f->overlap, c;
    for (c = 0; c < 2; c++)  /* stride 2 hard-coded, like the input copy */
        ssc_mdct_forward(&m->mdct, in_shared + c * (N + ov), SSC_FREQ + c * N, m->window, ov, 0,
                         1);
    spectrum_fixup(st, bitrate, wide);
}

/* 8 short MDCTs per channel, interleaved (stride 8), as Opus compute_mdcts. */
static void short_mdcts(SscEncoder *st, SscFrame *f, int bitrate, int wide) {
    const SscMode *m = st->mode;
    int L = m->shortMdctSize, ov = f->overlap, c, b;
    for (c = 0; c < 2; c++)
        for (b = 0; b < 8; b++)
            ssc_mdct_forward(&m->mdct, in_shared + c * (8 * L + ov) + b * L,
                             SSC_FREQ + c * 8 * L + b, m->window, ov, 3, 8);
    spectrum_fixup(st, bitrate, wide);
}

static int32_t add32(int32_t a, int32_t b) { return (int32_t)((uint32_t)a + (uint32_t)b); }

/* Header bandwidth flags from the sub-band energies above the last band
 * (ssc_encode @0xe228..0xeb44 and @0xe890). Narrow rates: byte 2 += 4k for the
 * highest of 3 sub-bands with energy > 30001 (two channels summed). UHQ (not
 * 152k): rows 0..3 drop 0..3 top bands; the first row with a sub-band > 12001
 * sets byte 2 += 4·row and the sub-band index into byte 3 bits 5..7. */
static void bandwidth_flags(SscEncoder *st, SscFrame *f, uint8_t *out, int wide, int uhq) {
    const SscMode *m = st->mode;
    int32_t e[16];
    int row = 0, j = 0, found = 0;
    if (!wide) {
        int k = 0;
        compute_band_energies_for_lastband(m, SSC_FREQ, e, 4, 0, 0);
        if (add32(e[3], e[7]) >= 30002) k = 3;
        else if (add32(e[2], e[6]) >= 30002) k = 2;
        else if (add32(e[1], e[5]) >= 30002) k = 1;
        out[2] = (uint8_t)(out[2] + 4 * k);
        f->drop = 0;
        return;
    }
    if (out[3] == 0xE6) {  /* 152k: four bands off, no flags */
        f->drop = 4;
        return;
    }
    f->drop = 0;
    if (!uhq) return;  /* 256k / 328k on the 48 kHz mode */
    for (row = 0; row < 4 && !found; row++) {
        compute_band_energies_for_lastband(m, SSC_FREQ, e, 8, 1, row);
        for (j = 7; j >= 0; j--)
            if (add32(e[j], e[8 + j]) > 0x2ee1) {
                found = 1;
                break;
            }
    }
    row--;
    if (!found) j = 0;
    f->drop = row;
    out[2] = (uint8_t)(out[2] + 4 * row);
    out[3] = (uint8_t)((j << 5) | (out[3] & 0x1f));
}

/* Band energies, transient decision, bandwidth flags, normalisation
 * (ssc_encode @0xe184..0xebcc; Opus 1.1 celt_encode_with_ec order). */
static void analysis(SscEncoder *st, ec_enc *enc, SscFrame *f, uint8_t *out, int bitrate,
                     int wide, int uhq) {
    const SscMode *m = st->mode;
    int nb = m->nbEBands, C = st->channels, end = st->end, i, checked;
    const int16_t *oldBandE = (const int16_t *)(st->in_mem + (f->overlap + 1024) * C);

    compute_band_energies(m, SSC_FREQ, f->bandE, end);
    amp2Log2(m, end, end, f->bandE, f->bandLogE, C);
    memcpy(f->bandLogE2, f->bandLogE, sizeof(int16_t) * nb * C);
    f->isTransient = 0;
    f->shortBlocks = 0;
    f->tf_estimate = 0;
    checked = ec_tell(enc) + 3 <= f->total_bits;
    if (checked) {
        /* Both detectors always run (the temporal one keeps state). */
        int t1 = patch_transient_decision(f->bandLogE, oldBandE, nb, end - previous_uhq_index);
        int t2 = patch_transient_decision_temporal(m, st, in_shared);
        if (t1 || t2) {
            short_mdcts(st, f, bitrate, wide);
            compute_band_energies(m, SSC_FREQ, f->bandE, end);
            amp2Log2(m, end, end, f->bandE, f->bandLogE, C);
            for (i = 0; i < 2 * nb; i++)  /* short vs long MDCT scaling: LM/2 */
                f->bandLogE2[i] = (int16_t)(f->bandLogE2[i] + 0x600);
            f->isTransient = 1;
            f->shortBlocks = 8;
            f->tf_estimate = 0xccd;
        }
    }
    bandwidth_flags(st, f, out, wide, uhq);
    if (checked) ec_enc_bit_logp(enc, f->isTransient, 3);
    normalise_bands(m, SSC_FREQ, (int16_t *)SSC_FREQ, f->bandE, end - f->drop);
}

/* Pitch pre-filter (Opus run_prefilter, Samsung variant; @0xdb90..0xdfdc). */
static void prefilter(SscEncoder *st, ec_enc *enc, SscFrame *f) {
    int N = f->N, ov = f->overlap, c, d, qg = 0, pf_on = 0, pitch_index;
    int32_t *prefilter_mem = st->in_mem + f->C * ov;
    int32_t *pre[2] = {_pre_shared, _pre_shared + N + SSC_COMBFILTER_MAXPERIOD};
    int16_t gain1, pg = st->prefilter_gain;
    uint16_t thr;

    for (c = 0; c < 2; c++) {
        SSC_COPY32(pre[c], prefilter_mem + c * SSC_COMBFILTER_MAXPERIOD, SSC_COMBFILTER_MAXPERIOD);
        SSC_COPY32(pre[c] + SSC_COMBFILTER_MAXPERIOD, in_shared + c * (N + ov) + ov, N);
    }
    if (f->nbAvailableBytes < 25 || f->silence) {
        gain1 = 0;
        pitch_index = SSC_COMBFILTER_MINPERIOD;
    } else {
        int16_t *pitch_buf = (int16_t *)in_shared;  /* the blob reuses in_shared */
        int16_t g;
        pitch_downsample(pre, pitch_buf, N + SSC_COMBFILTER_MAXPERIOD);
        pitch_search(pitch_buf + (SSC_COMBFILTER_MAXPERIOD >> 1), pitch_buf, N,
                     SSC_COMBFILTER_MAXPERIOD - 3 * SSC_COMBFILTER_MINPERIOD, &pitch_index);
        pitch_index = SSC_COMBFILTER_MAXPERIOD - pitch_index;
        g = remove_doubling(pitch_buf, SSC_COMBFILTER_MAXPERIOD, SSC_COMBFILTER_MINPERIOD, N,
                            &pitch_index, st->prefilter_period, pg);
        if (pitch_index > SSC_COMBFILTER_MAXPERIOD - 2) pitch_index = SSC_COMBFILTER_MAXPERIOD - 2;
        gain1 = (int16_t)((uint32_t)(g * 0x599a) >> 15);  /* .7 * g */
    }

    /* Gain threshold: .2/.4 base, +.2 / +.1 for small budgets, -.1 / -.2 for a
     * strong previous gain, at least .2 (16-bit arithmetic, as in the blob). */
    d = pitch_index - st->prefilter_period;
    if (d < 0) d = -d;
    thr = d * 10 <= pitch_index ? 0x199a : 0x3334;
    if (f->nbAvailableBytes < 25) thr += 0x199a;
    else if (f->nbAvailableBytes <= 34) thr += 0xccd;
    if (pg > 0x4666) thr += 0xe666;
    else if (pg >= 0x3334) thr -= 0xccd;
    if ((int16_t)thr < 0x199b) thr = 0x199a;

    if ((int)gain1 < (int)thr) {
        gain1 = 0;
    } else {
        int16_t gs = gain1;
        d = gain1 - pg;
        if (d < 0) d = -d;
        if (d <= 0xccc) gs = pg;
        qg = ((gs + 0x600) >> 10) / 3 - 1;
        if (qg > 6) qg = 7;
        if (qg < 0) qg = 0;
        gain1 = (int16_t)(0xc00 * (qg + 1));
        pf_on = 1;
    }

    for (c = 0; c < 2; c++) {
        int32_t *in = in_shared + c * (N + ov);
        int32_t *mem = prefilter_mem + c * SSC_COMBFILTER_MAXPERIOD;
        if (st->prefilter_period < 16) st->prefilter_period = SSC_COMBFILTER_MINPERIOD;
        SSC_COPY32(in, st->in_mem + c * ov, ov);
        comb_filter(in + ov, pre[c] + SSC_COMBFILTER_MAXPERIOD, st->prefilter_period, pitch_index,
                    N, (int16_t)(0u - (uint16_t)pg), (int16_t)(0 - gain1), ov);
        SSC_COPY32(st->in_mem + c * ov, in + N, ov);
        SSC_COPY32(mem, mem + N, SSC_COMBFILTER_MAXPERIOD - N);
        SSC_COPY32(mem + SSC_COMBFILTER_MAXPERIOD - N, pre[c] + SSC_COMBFILTER_MAXPERIOD, N);
    }

    if (pf_on) {
        int pi = pitch_index + 1, l = EC_ILOG(pi);
        ec_enc_bit_logp(enc, 1, 1);
        ec_enc_uint(enc, l - 5, 6);
        ec_enc_bits(enc, pi - (16 << (l - 5)), l - 1);
        ec_enc_bits(enc, qg, 3);
    } else if (f->tell + 16 <= f->total_bits) {
        ec_enc_bit_logp(enc, 0, 1);
    }
    f->pitch_index = pitch_index;
    f->gain1 = gain1;
    f->qg = qg;
    f->pf_on = pf_on;
}

/* ------------------------------------------------------------------ 3e */

#define C2 2

/* Samsung intensity tables (blob 0x16b4c / 0x16b7a); ssc_encode always asks
 * with 510 kbps, so the decision ends up "intensity = end - drop". */
static const int16_t kIntensityThr[23] = {1,  2,  3,  4,  5,  6,  7,  8,  16, 24, 36, 44,
                                          50, 56, 62, 67, 72, 77, 83, 89, 95, 102, 109};
static const int16_t kIntensityHys[23] = {1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
                                          2, 2, 3, 3, 3, 4, 4, 5, 5, 7, 7};
static const unsigned char kSpreadIcdf[4] = {25, 23, 2, 0};
static const unsigned char kTrimIcdf[11] = {126, 124, 119, 109, 87, 41, 19, 9, 4, 2, 0};

/* L1 + MULT16_32_Q15(a, L1), Samsung split ((x & 0x7fff) and x >> 15). */
static int32_t l1_metric(const int16_t *tmp, int N, int32_t a) {
    int32_t L1 = 0;
    int j;
    for (j = 0; j < N; j++) L1 += tmp[j] < 0 ? -tmp[j] : tmp[j];
    return L1 + (int32_t)(((uint32_t)(L1 & 0x7fff) * (uint32_t)a) >> 15) +
           ((int32_t)((uint32_t)L1 << 1) >> 16) * a;
}

/* Opus tf_analysis (tf_chan 0, LM 3). Scratch lives in in_shared like the
 * blob's: metric +0, path0 +22, path1 +44 (int32), tmp at byte 0x108 and
 * tmp_1 at byte 0x348 (int16). Samsung: tf_res[0] = tf_res[1] = isTransient. */
static int tf_analysis(const SscMode *m, int len, int isTransient, int *tf_res, int lambda,
                       const int16_t *X, int16_t tf_estimate) {
    int32_t *metric = in_shared, *path0 = in_shared + 22, *path1 = in_shared + 44;
    int16_t *tmp = (int16_t *)((char *)in_shared + 0x108);
    int16_t *tmp_1 = (int16_t *)((char *)in_shared + 0x348);
    int32_t bias = ((int16_t)(8192 - tf_estimate) * 1311) >> 14;
    int i, j, k, sel, cost0, cost1, selcost[2], tf_select = 0;
    const int8_t *tsel = tf_select_table + 4 * isTransient;

    for (i = 0; i < len; i++) {
        int w = m->eBands[i + 1] - m->eBands[i], N = w << 3, narrow = w == 1;
        int best_level = 0, count;
        int32_t L1, best_L1;
        for (j = 0; j < N; j++) tmp[j] = X[j + (m->eBands[i] << 3)];
        L1 = l1_metric(tmp, N, isTransient ? (int32_t)(bias * 0x30000) >> 16 : 0);
        best_L1 = L1;
        if (isTransient && !narrow) {
            for (j = 0; j < N; j++) tmp_1[j] = tmp[j];
            haar1(tmp_1, N >> 3, 8);
            L1 = l1_metric(tmp_1, N, bias * 4);
            if (L1 < best_L1) {
                best_L1 = L1;
                best_level = -1;
            }
        }
        count = 3 + !(isTransient || narrow);
        for (k = 0; k < count; k++) {
            int32_t a = isTransient ? (int32_t)((uint32_t)bias * 0x10000u * (uint32_t)(2 - k)) >> 16
                                    : (int32_t)(((uint32_t)bias * 0x10000u * (uint32_t)(k + 1)) >> 16);
            haar1(tmp, N >> k, 1 << k);
            L1 = l1_metric(tmp, N, a);
            if (L1 < best_L1) {
                best_L1 = L1;
                best_level = k + 1;
            }
        }
        metric[i] = isTransient ? 2 * best_level : -2 * best_level;
        if (narrow && (metric[i] == 0 || metric[i] == -6)) metric[i] -= 1;
    }
    for (sel = 0; sel < 2; sel++) {
        cost0 = 0;
        cost1 = isTransient ? 0 : lambda;
        for (i = 1; i < len; i++) {
            int curr0 = IMIN(cost0, cost1 + lambda), curr1 = IMIN(cost0 + lambda, cost1);
            cost0 = curr0 + abs(metric[i] - 2 * tsel[2 * sel + 0]);
            cost1 = curr1 + abs(metric[i] - 2 * tsel[2 * sel + 1]);
        }
        selcost[sel] = IMIN(cost0, cost1);
    }
    if (selcost[1] < selcost[0] && isTransient) tf_select = 1;
    cost0 = 0;
    cost1 = isTransient ? 0 : lambda;
    for (i = 1; i < len; i++) {
        int from0 = cost0, from1 = cost1 + lambda, curr0, curr1;
        curr0 = from0 < from1 ? from0 : from1;
        path0[i] = !(from0 < from1);
        from0 = cost0 + lambda;
        from1 = cost1;
        curr1 = from0 < from1 ? from0 : from1;
        path1[i] = !(from0 < from1);
        cost0 = curr0 + abs(metric[i] - 2 * tsel[2 * tf_select + 0]);
        cost1 = curr1 + abs(metric[i] - 2 * tsel[2 * tf_select + 1]);
    }
    tf_res[len - 1] = cost0 < cost1 ? 0 : 1;
    for (i = len - 2; i >= 0; i--) tf_res[i] = tf_res[i + 1] == 1 ? path1[i + 1] : path0[i + 1];
    tf_res[0] = tf_res[1] = isTransient;
    return tf_select;
}

/* Opus tf_encode, start 0, LM 3. */
static void tf_encode(int end, int isTransient, int *tf_res, int tf_select, ec_enc *enc) {
    uint32_t budget = enc->storage * 8, tell = ec_tell(enc);
    int logp = isTransient ? 2 : 4, tf_select_rsv, tf_changed = 0, curr = 0, i;
    tf_select_rsv = tell + logp + 1 <= budget;
    budget -= tf_select_rsv;
    for (i = 0; i < end; i++) {
        if (tell + logp <= budget) {
            ec_enc_bit_logp(enc, tf_res[i] ^ curr, logp);
            tell = ec_tell(enc);
            curr = tf_res[i];
            tf_changed |= curr;
        } else {
            tf_res[i] = curr;
        }
        logp = isTransient ? 4 : 5;
    }
    if (tf_select_rsv && tf_select_table[4 * isTransient + 0 + tf_changed] !=
                             tf_select_table[4 * isTransient + 2 + tf_changed])
        ec_enc_bit_logp(enc, tf_select, 1);
    else
        tf_select = 0;
    for (i = 0; i < end; i++) tf_res[i] = tf_select_table[4 * isTransient + 2 * tf_select + tf_res[i]];
}

/* Opus dynalloc_analysis (C 2, LM 3, lsb_depth 16, CBR), offsets in quanta. */
static void dynalloc_analysis(const SscMode *m, const SscFrame *f, int end, int *offsets,
                              int32_t *tot_boost_) {
    const int16_t *eBands = m->eBands, *bandLogE = f->bandLogE, *bandLogE2 = f->bandLogE2;
    int nb = m->nbEBands, i, c, last = 0;
    int16_t follower[2 * SSC_NB_EBANDS], noise_floor[SSC_NB_EBANDS];
    int32_t tot_boost = 0;
    for (i = 0; i < nb; i++) offsets[i] = 0;
    for (i = 0; i < end; i++)
        noise_floor[i] = (int16_t)(m->logN[i] * 64 - 0x1a00 - eMeans[i] * 64 +
                                   6 * (int16_t)((i + 5) * (i + 5)));
    if (f->effectiveBytes > 50) {
        for (c = 0; c < C2; c++) {
            follower[c * nb] = bandLogE2[c * nb];
            for (i = 1; i < end; i++) {
                if (bandLogE2[c * nb + i] > bandLogE2[c * nb + i - 1] + 512) last = i;
                follower[c * nb + i] =
                    (int16_t)IMIN(follower[c * nb + i - 1] + 0x600, bandLogE2[c * nb + i]);
            }
            for (i = last - 1; i >= 0; i--)
                follower[c * nb + i] = (int16_t)IMIN(
                    follower[c * nb + i], IMIN(follower[c * nb + i + 1] + 0x800, bandLogE2[c * nb + i]));
            for (i = 0; i < end; i++)
                follower[c * nb + i] = (int16_t)IMAX(follower[c * nb + i], noise_floor[i]);
        }
        for (i = 0; i < end; i++) {
            int a, b;
            follower[nb + i] = (int16_t)IMAX(follower[nb + i], follower[i] - 0x1000);
            follower[i] = (int16_t)IMAX(follower[i], follower[nb + i] - 0x1000);
            a = IMAX(0, bandLogE[i] - follower[i]);
            b = IMAX(0, bandLogE[nb + i] - follower[nb + i]);
            follower[i] = (int16_t)((a + b) >> 1);
        }
        if (!f->isTransient)
            for (i = 0; i < end; i++) follower[i] = (int16_t)(follower[i] >> 1);
        for (i = 0; i < end; i++) {
            int width, boost, boost_bits;
            if (i < 8) follower[i] = (int16_t)(follower[i] * 2);
            if (i >= 12) follower[i] = (int16_t)(follower[i] >> 1);
            follower[i] = (int16_t)IMIN(follower[i], 0x1000);
            width = (eBands[i + 1] - eBands[i]) * C2 * 8;
            if (width < 6) {
                boost = follower[i] >> 10;
                boost_bits = boost * width << 3;
            } else if (width > 48) {
                boost = follower[i] >> 7;
                boost_bits = (boost * width << 3) / 8;
            } else {
                boost = (width * follower[i]) / 6 >> 10;
                boost_bits = boost * 6 << 3;
            }
            if ((tot_boost + boost_bits) >> 6 > f->effectiveBytes / 4) {
                int32_t cap = (f->effectiveBytes / 4) << 6;
                offsets[i] = cap - tot_boost;
                tot_boost = cap;
                *tot_boost_ = tot_boost;
                return;  /* blob: also skips the low-band boosts below */
            }
            offsets[i] = boost;
            tot_boost += boost_bits;
        }
    }
    *tot_boost_ = tot_boost;

    /* Samsung: extra boost for strong low peaks in bands 0 and 1 (bandLogE2). */
    {
        int a = IMIN(bandLogE2[0] - 0x1964, bandLogE2[nb] - 0x1964);
        int d = IMIN(bandLogE2[0] - bandLogE2[1], bandLogE2[nb] - bandLogE2[nb + 1]);
        if (a > 0 && d > 0) {
            int v = (int)((uint32_t)(a & 0xffff) / 200 + ((uint32_t)IMAX(0, d - 1500) >> 7));
            if (v > 9) v = 10;
            if (offsets[0] < v) offsets[0] = v;
        }
    }
    {
        int d1 = IMIN(bandLogE2[1] - bandLogE2[0], bandLogE2[nb + 1] - bandLogE2[nb]);
        int a = IMIN(bandLogE2[1] - 0x17d4, bandLogE2[nb + 1] - 0x17d4);
        int d2 = IMIN(bandLogE2[1] - bandLogE2[2], bandLogE2[nb + 1] - bandLogE2[nb + 2]);
        if (d1 > 0 && a > 0 && d2 > 0) {
            int v = (d2 - 0x6a4) / 0xa0 + (int)((uint32_t)(a & 0xffff) / 200);
            if (v > 9) v = 10;
            if (offsets[1] < v) offsets[1] = v;
        }
    }
}

/* Opus stereo_analysis (bands 0..12, LM 3). */
static int stereo_analysis(const SscMode *m, const int16_t *X, int N0) {
    int32_t sumLR = 1, sumMS = 1, lhs, rhs;
    int i, j, t = (int16_t)(m->eBands[13] << 4);
    for (i = 0; i < 13; i++)
        for (j = m->eBands[i] << 3; j < m->eBands[i + 1] << 3; j++) {
            int32_t L = X[j], R = X[N0 + j], M = L + R, S = L - R;
            sumLR += abs(L) + abs(R);
            sumMS += abs(M) + abs(S);
        }
    sumMS = MULT16_32_Q15(QCONST16(0.707107f, 15), sumMS);
    lhs = MULT16_32_Q15(t, sumLR);
    rhs = MULT16_32_Q15(t | 13, sumMS);
    return lhs < rhs;
}

/* Opus alloc_trim_analysis without stereo_saving/analysis/surround (Samsung). */
static int alloc_trim_analysis(const SscMode *m, const int16_t *X, const int16_t *bandLogE, int end,
                               int N0, int16_t tf_estimate, int intensity) {
    int i, c;
    int32_t diff = 0, sum = 0, d6;
    int16_t trim, logXC;
    for (i = 0; i < 8; i++) {
        int32_t partial = 0;
        for (c = m->eBands[i] << 3; c < m->eBands[i + 1] << 3; c++) partial += X[c] * X[N0 + c];
        sum += (int16_t)(partial >> 18);
    }
    sum = (int16_t)sum >> 3;
    if (sum < 0) sum = -sum;
    if (sum > 1024) sum = 1024;
    (void)intensity;  /* minXC / logXC2 are computed by the blob but never used */
    logXC = celt_log2(QCONST32(1.001f, 20) - sum * sum);
    logXC = (int16_t)((int32_t)((uint32_t)logXC * 0x4000u - 0x5ff8000u) >> 16);
    if (logXC * 0x6000 < -0x2000000)
        trim = 0x100;
    else
        trim = (int16_t)((int32_t)(((uint32_t)(logXC * 0xc000) & 0xffff0000u) + 0x5000000u) >> 16);
    for (c = 0; c < C2; c++)
        for (i = 0; i < end - 1; i++) diff += bandLogE[i + c * m->nbEBands] * (2 + 2 * i - end);
    diff = end - 1 != 0 ? diff / ((end - 1) * 2) : 0;
    d6 = ((diff + 1024) >> 2) / 6;
    if (d6 > 512) d6 = 512;
    if (d6 < -512) d6 = -512;
    i = (int16_t)(trim - (int16_t)(tf_estimate >> 5) - d6) + 0x80;
    i >>= 8;
    return i < 0 ? 0 : i > 10 ? 10 : i;
}

/* Coarse energy, tf, spreading, dynalloc, trim, allocation, fine energy
 * (ssc_encode @0xebcc..0x11068, Opus 1.1 order with Samsung changes). */
static void quantise(SscEncoder *st, ec_enc *enc, SscFrame *f, int bitrate, int wide) {
    const SscMode *m = st->mode;
    const int16_t *X = (const int16_t *)SSC_FREQ;
    int nb = m->nbEBands, C = st->channels, end = st->end, endc = end - f->drop, N0 = 864, i;
    int16_t *oldBandE = (int16_t *)(st->in_mem + (f->overlap + 1024) * C);
    const int32_t *caps = m->cache.caps;
    int32_t total_bits = f->total_bits, tell;

    f->effectiveBytes = f->nbCompressedBytes;
    if (!wide && C * 15 <= f->effectiveBytes) {
        int lambda = f->effectiveBytes < 40 ? 24 : f->effectiveBytes < 60 ? 12
                     : f->effectiveBytes < 100 ? 8 : 6;
        f->tf_select = tf_analysis(m, end, f->isTransient, f->tf_res, lambda, X, f->tf_estimate);
    } else {
        for (i = 0; i < end; i++) f->tf_res[i] = f->isTransient;
        f->tf_select = 0;
    }

    quant_coarse_energy(m, end, endc, f->bandLogE, oldBandE, (uint32_t)total_bits, f->error, enc,
                        f->nbAvailableBytes, st->force_intra, &st->delayedIntra);

    if (!wide)
        tf_encode(end, f->isTransient, f->tf_res, f->tf_select, enc);
    else
        memset(f->tf_res, 0, sizeof(int) * end);

    if (ec_tell(enc) + 4 <= total_bits) {
        if (f->nbAvailableBytes < C * 10 || f->shortBlocks)
            st->spread_decision = 2;
        else
            st->spread_decision = spreading_decision(m, X, &st->tonal_average, st->spread_decision,
                                                     &st->hf_average, &st->tapset_decision,
                                                     f->pf_on, endc);
        ec_enc_icdf(enc, st->spread_decision, kSpreadIcdf, 5);
    }

    dynalloc_analysis(m, f, endc, f->offsets, &f->total_boost);

    /* Encode the boosts (Opus 1.1 loop, caps straight from the mode). */
    total_bits <<= 3;
    tell = ec_tell_frac(enc);
    {
        int dynalloc_logp = 6;
        int32_t total_boost = 0;
        for (i = 0; i < endc; i++) {
            int width = C * (m->eBands[i + 1] - m->eBands[i]) << 3;
            int quanta = IMIN(width << 3, IMAX(6 << 3, width));
            int loop_logp = dynalloc_logp, boost = 0, j;
            for (j = 0; tell + (loop_logp << 3) < total_bits - total_boost && boost < caps[i]; j++) {
                int flag = j < f->offsets[i];
                ec_enc_bit_logp(enc, flag, loop_logp);
                tell = ec_tell_frac(enc);
                if (!flag) break;
                boost += quanta;
                total_boost += quanta;
                loop_logp = 1;
            }
            if (j) dynalloc_logp = IMAX(2, dynalloc_logp - 1);
            f->offsets[i] = boost;
        }
        f->total_boost = total_boost;
    }
    /* Samsung: a big boost on band 18, 19 or 20 next to an unboosted band
     * spills over to it when that band's (new) energy is high enough. */
    for (i = 18; i <= 20; i++)
        if (f->offsets[i] > 1000 && f->offsets[i + 1] == 0) {
            if (oldBandE[i + 1] > 7000 || oldBandE[i + 1] > oldBandE[i] >> 1)
                f->offsets[i + 1] = f->offsets[i];
            break;
        }

    f->dual_stereo = stereo_analysis(m, X, N0);
    i = hysteresis_decision(510, kIntensityThr, kIntensityHys, 22 - f->drop, st->intensity);
    st->intensity = IMIN(endc, IMAX(0, i));

    f->alloc_trim = 5;
    if (tell + (6 << 3) <= total_bits - f->total_boost) {
        f->alloc_trim = alloc_trim_analysis(m, X, f->bandLogE, endc, N0, f->tf_estimate,
                                            st->intensity);
        ec_enc_icdf(enc, f->alloc_trim, kTrimIcdf, 7);
    }

    f->alloc_bits = total_bits - (int32_t)ec_tell_frac(enc) - 1;
    f->anti_collapse_rsv = f->isTransient && f->alloc_bits >= 40 ? 8 : 0;
    f->alloc_bits -= f->anti_collapse_rsv;
    f->codedBands = compute_allocation(m, endc, f->offsets, caps, f->alloc_trim, &st->intensity,
                                       &f->dual_stereo, f->alloc_bits, &f->balance, f->pulses,
                                       f->fine_quant, f->fine_priority, enc, st->lastCodedBands,
                                       endc - 1, bitrate > 192000);
    if (st->lastCodedBands)
        st->lastCodedBands =
            IMIN(st->lastCodedBands + 1, IMAX(st->lastCodedBands - 1, f->codedBands));
    else
        st->lastCodedBands = f->codedBands;

    quant_fine_energy(m, endc, oldBandE, f->error, f->fine_quant, enc, C);
    (void)nb;
}

static void fill_stage_alloc(const SscEncoder *st, const SscFrame *f) {
    SscStageAlloc *a = &ssc_stage_alloc;
    int i;
    a->end = st->end - f->drop;
    a->shortBlocks = f->shortBlocks;
    a->spread = st->spread_decision;
    a->dual_stereo = f->dual_stereo;
    a->intensity = st->intensity;
    a->total_bits = (f->total_bits << 3) - f->anti_collapse_rsv;
    a->balance = f->balance;
    a->codedBands = f->codedBands;
    for (i = 0; i < 22; i++) {
        a->tf_res[i] = f->tf_res[i];
        a->pulses[i] = f->pulses[i];
        a->fine_quant[i] = f->fine_quant[i];
        a->fine_priority[i] = f->fine_priority[i];
    }
    memcpy(a->bandE, f->bandE, sizeof a->bandE);
    memcpy(a->error, f->error, sizeof a->error);
}

int ssc_encode(SscEncoder *st, int32_t *pcm, int frame_size, uint8_t *out, int bitrate) {
    const SscRate *rate = find_rate(bitrate);
    int wide = rate ? rate->wide : 0;
    int uhq = rate ? rate->uhq : 0;
    int n, budget;
    ec_enc enc;
    SscFrame f;

    /* Header bytes 0..3 (blob writes them before checking pcm). */
    st->end = st->mode->nbEBands;
    st->bitrate = bitrate;
    out[0] = 0xFF;
    out[1] = 0xEE;
    out[3] = rate ? rate->byte3 : 0xF3; /* unknown rate: 0xF3, no DRC gain update */
    out[2] = (uint8_t)((st->frame_counter << 4) | (st->hdr_low_bits & 3));
    if (uhq) out[1] = (uint8_t)(0xE0 | ((st->frame_counter >> 4) & 0xF));
    if (rate) /* overwritten by preprocess(); kept for state parity with the blob */
        set_DRC_limit_gain(wide || st->bit_depth == 24 ? rate->drc_gain : rate->drc_gain >> 8);

    /* Byte budget: the 44.1/48 kHz mode counts at Fs = 44100. */
    n = st->bitrate * frame_size / (st->fs_mode * 8);
    if (!wide) n += (n * 3) >> 7;
    n |= 1;
    budget = n - 1;
    ec_enc_init(&enc, out + SSC_HEADER_BYTES, budget);

    preprocess(st, pcm, frame_size, bitrate, wide);
    ec_enc_shrink(&enc, budget);
    if (!pcm || n < 3) return -1;

    f.N = frame_size;
    f.C = st->channels;
    f.overlap = st->mode->overlap;
    silence_and_input(st, pcm, &enc, &f, budget,
                      st->bit_depth != 24 && !wide ? 12 : 4);
    prefilter(st, &enc, &f);
    if (ssc_stage_hook) ssc_stage_hook(SSC_STAGE_PRE_MDCT, st, &enc);
    long_mdct(st, &f, bitrate, wide);
    if (ssc_stage_hook) ssc_stage_hook(SSC_STAGE_POST_MDCT, st, &enc);
    analysis(st, &enc, &f, out, bitrate, wide, uhq);
    if (ssc_stage_hook) ssc_stage_hook(SSC_STAGE_POST_NORMALISE, st, &enc);
    quantise(st, &enc, &f, bitrate, wide);
    if (ssc_stage_hook) {
        fill_stage_alloc(st, &f);
        ssc_stage_hook(SSC_STAGE_PRE_PVQ, st, &enc);
    }

    /* TODO(phase 3f): quant_all_bands, anti-collapse, energy finalise. */

    /* End-of-frame state (ssc_encode @0x111b8..). Still missing: band energies,
     * consec_transient (+0x40). */
    previous_uhq_index = f.drop;
    st->prefilter_period = f.pitch_index;
    st->prefilter_gain = f.gain1;
    st->rng = (int32_t)enc.rng;  /* seed for the next frame's quant_all_bands */
    ec_enc_done(&enc);
    st->frame_counter = (uint16_t)(st->frame_counter + 1 == 256 ? 0 : st->frame_counter + 1);
    return enc.error ? -3 : budget + SSC_HEADER_BYTES;
}
