/* libssc â€” encoder entry points (ssc_encoder_* / ssc_encode).
 *
 * Ported stage by stage (libssc/PLAN.md, phase 3). Bit-exact so far: header,
 * byte budget, input processing (3a), silence flag and prefilter (3b), long
 * MDCT and headroom (3c), band analysis, transient decision and header flags
 * (3d). The rest of the CELT payload is not produced yet (range coder finished
 * early).
 */
#include "ssc_encoder.h"

#include <stdlib.h>
#include <string.h>

#include "opus/entenc.h"
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
} SscFrame;

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
    st->f20 = 2;
    st->f24 = 1;
    st->f28 = 256;
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

    /* TODO(phase 3e+): coarse/fine energy, allocation, PVQ. */

    /* End-of-frame state (ssc_encode @0x111b8..). Still missing: band energies,
     * consec_transient (+0x40). */
    previous_uhq_index = f.drop;
    st->prefilter_period = f.pitch_index;
    st->prefilter_gain = f.gain1;
    st->f1c = (int32_t)enc.rng;  /* seed for the next frame's quant_all_bands */
    ec_enc_done(&enc);
    st->frame_counter = (uint16_t)(st->frame_counter + 1 == 256 ? 0 : st->frame_counter + 1);
    return enc.error ? -3 : budget + SSC_HEADER_BYTES;
}
