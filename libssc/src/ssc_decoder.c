/* libssc — SSC decoder (phase 6), see ssc_decoder.h.
 *
 * The parsing mirrors ssc_encode stage by stage (Opus 1.1 celt_decode_with_ec
 * order with the Samsung changes of the encoder): every ec_enc_* there is the
 * matching ec_dec_* here, and the allocation arithmetic is copied from
 * ssc_quant.c / ssc_pvq.c. The quantised energies therefore follow the
 * encoder's oldBandE exactly (test/decode.py checks it frame by frame).
 */
#include "ssc_decoder.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "opus/arch.h"
#include "opus/cwrs.h"
#include "opus/entcode.h"
#include "opus/entdec.h"
#include "opus/laplace.h"
#include "opus/mathops.h"
#include "ssc_encoder.h"
#include "ssc_internal.h"

#define NB 22
#define N0 864          /* spectrum bins per channel, PCM frames per frame */
#define OV SSC_OVERLAP  /* 108 */
#define L8 8            /* short blocks */
#define LM3 3
#define BITRES 3
#define MAX_FINE_BITS 8
#define FINE_OFFSET 21
#define QTHETA_OFFSET 4
#define PF_HIST 1100    /* post-filter history (max period 1022 + taps) */

/* ------------------------------------------------------------ tables (copies) */

typedef struct {
    int32_t bitrate;
    uint8_t code;   /* byte 3, low 5 bits */
    uint8_t uhq, wide;
} Rate;

static const Rate kRates[] = {
    {88000, 0x10, 0, 0},  {96000, 0x11, 0, 0},  {128000, 0x12, 0, 0}, {192000, 0x13, 0, 0},
    {229000, 0x14, 0, 0}, {328000, 0x15, 0, 1}, {256000, 0x16, 0, 1}, {291000, 0x00, 1, 1},
    {308000, 0x01, 1, 1}, {442000, 0x02, 1, 1}, {584000, 0x03, 1, 1}, {886000, 0x04, 1, 1},
    {250000, 0x05, 1, 1}, {152000, 0x06, 1, 1},
};

static const unsigned char e_prob_inter[42] = {
    42, 121, 96, 66, 108, 43, 111, 40, 117, 44, 123, 32, 120, 36, 119, 33, 127, 33, 134, 34, 139,
    21, 147, 23, 152, 20, 158, 25, 154, 26, 166, 21, 173, 16, 184, 13, 184, 10, 150, 13, 139, 15};
static const unsigned char e_prob_intra[42] = {
    22, 178, 63, 114, 74, 82, 84, 83, 92, 82, 103, 62, 96, 72, 96, 67, 101, 73, 107, 72, 113,
    55, 118, 52, 125, 52, 118, 52, 117, 55, 135, 49, 137, 39, 157, 32, 145, 29, 97, 33, 77, 40};
static const unsigned char small_energy_icdf[3] = {2, 1, 0};
static const unsigned char LOG2_FRAC_TABLE[24] = {0,  8,  13, 16, 19, 21, 23, 24, 26, 27, 28, 29,
                                                  30, 31, 32, 32, 33, 34, 34, 35, 36, 36, 37, 37};
static const unsigned char kSpreadIcdf[4] = {25, 23, 2, 0};
static const unsigned char kTrimIcdf[11] = {126, 124, 119, 109, 87, 41, 19, 9, 4, 2, 0};
static const int16_t exp2_table8[8] = {16384, 17866, 19483, 21247, 23170, 25267, 27554, 30048};
static const unsigned char bit_interleave_table[16] = {0, 1, 1, 1, 2, 3, 3, 3,
                                                       2, 3, 3, 3, 2, 3, 3, 3};
static const unsigned char bit_deinterleave_table[16] = {0x00, 0x03, 0x0C, 0x0F, 0x30, 0x33,
                                                         0x3C, 0x3F, 0xC0, 0xC3, 0xCC, 0xCF,
                                                         0xF0, 0xF3, 0xFC, 0xFF};
static const int ordery_table[] = {1, 0, 3, 0, 2, 1, 7, 0, 4, 3, 6, 1, 5, 2,
                                   15, 0, 8, 7, 12, 3, 11, 4, 14, 1, 9, 6, 13, 2, 10, 5};

/* ------------------------------------------------------------ synthesis matrices */

/* The inverse MDCT is the transpose of the encoder's own forward MDCT, taken
 * from ssc_mdct_forward with unit impulses (window, signs and scaling then
 * match whatever the 32-bit transform does), times a gain fitted so that
 * overlap-add reconstructs the input. */
typedef struct {
    const ssc_mdct_lookup *l;
    int shift, n2, len;  /* outputs, inputs (n2 + overlap) */
    float *F;            /* n2 x len */
    double gain;
    double recon_snr;    /* dB, reconstruction check of the fit */
} Synth;

static Synth g_synth[4];

static uint32_t lcg(uint32_t s) { return 1664525u * s + 1013904223u; }

static Synth *synth_for(const ssc_mdct_lookup *l, int shift) {
    int i, k, n, f;
    Synth *s = NULL;
    for (i = 0; i < 4; i++) {
        if (g_synth[i].F && g_synth[i].l == l && g_synth[i].shift == shift) return &g_synth[i];
        if (!g_synth[i].F && !s) s = &g_synth[i];
    }
    if (!s) return NULL;
    s->l = l;
    s->shift = shift;
    s->n2 = (l->n >> shift) >> 1;
    s->len = s->n2 + OV;
    s->F = (float *)malloc(sizeof(float) * s->n2 * s->len);
    {
        const double A = (double)(1 << 25);
        int32_t *in = (int32_t *)calloc(s->len, sizeof(int32_t));
        int32_t *out = (int32_t *)malloc(sizeof(int32_t) * s->n2);
        for (n = 0; n < s->len; n++) {
            in[n] = 1 << 25;
            ssc_mdct_forward(l, in, out, OV, shift, 1);
            for (k = 0; k < s->n2; k++) s->F[k * s->len + n] = (float)(out[k] / A);
            in[n] = 0;
        }
        free(in);
        free(out);
    }
    {   /* fit the overlap-add gain on 8 frames of noise */
        int frames = 8, T = frames * s->n2 + OV;
        double *x = (double *)malloc(sizeof(double) * T), *y = (double *)calloc(T, sizeof(double));
        double *X = (double *)malloc(sizeof(double) * s->n2), xy = 0, yy = 0, ee = 0, xx = 0;
        uint32_t seed = 12345;
        for (i = 0; i < T; i++) {
            seed = lcg(seed);
            x[i] = (double)(int32_t)seed / 2147483648.0;
        }
        for (f = 0; f < frames; f++) {
            const double *b = x + f * s->n2;
            for (k = 0; k < s->n2; k++) {
                double a = 0;
                const float *row = s->F + k * s->len;
                for (n = 0; n < s->len; n++) a += row[n] * b[n];
                X[k] = a;
            }
            for (k = 0; k < s->n2; k++)
                for (n = 0; n < s->len; n++) y[f * s->n2 + n] += s->F[k * s->len + n] * X[k];
        }
        for (i = s->n2; i < (frames - 1) * s->n2; i++) {
            xy += x[i] * y[i];
            yy += y[i] * y[i];
        }
        s->gain = yy > 0 ? xy / yy : 1;
        for (i = s->n2; i < (frames - 1) * s->n2; i++) {
            double e = x[i] - s->gain * y[i];
            ee += e * e;
            xx += x[i] * x[i];
        }
        s->recon_snr = ee > 0 ? 10 * log10(xx / ee) : 200;
        free(x);
        free(y);
        free(X);
    }
    return s;
}

/* ------------------------------------------------------------ state */

struct SscDecoder {
    const SscMode *m;
    int fs;
    int16_t oldBandE[2 * NB];
    int spread;
    int pf_period, pf_period_old;
    int16_t pf_gain, pf_gain_old;
    uint32_t seed;
    float syn[2][N0 + OV];          /* [0, OV): overlap tail of the previous frame */
    int32_t pf[2][PF_HIST + N0];    /* post-filter history + this frame */
    SscDecInfo info;
};

static void reset(SscDecoder *st, const SscMode *m) {
    int i;
    memset(st, 0, sizeof *st);
    st->m = m;
    for (i = 0; i < 2 * NB; i++) st->oldBandE[i] = 0;  /* encoder: cleared state */
    st->spread = 2;
    st->pf_period = st->pf_period_old = SSC_COMBFILTER_MINPERIOD;
}

SscDecoder *ssc_decoder_create(int fs, int *err) {
    const SscMode *m = ssc_custom_mode_create(fs, SSC_FRAME_SIZE, NULL);
    SscDecoder *st;
    if (!m) {
        if (err) *err = -1;
        return NULL;
    }
    st = (SscDecoder *)malloc(sizeof *st);
    if (!st) {
        if (err) *err = -7;
        return NULL;
    }
    reset(st, m);
    st->fs = fs;
    if (!synth_for(&m->mdct, 0) || !synth_for(&m->mdct, 3)) {
        free(st);
        if (err) *err = -7;
        return NULL;
    }
    if (err) *err = 0;
    return st;
}

void ssc_decoder_destroy(SscDecoder *st) { free(st); }

void ssc_decoder_info(const SscDecoder *st, SscDecInfo *info) { *info = st->info; }

/* Reconstruction SNR of the synthesis fit (dB), for the test bench. */
double ssc_decoder_synth_snr(int shift) {
    int i;
    for (i = 0; i < 4; i++)
        if (g_synth[i].F && g_synth[i].shift == shift) return g_synth[i].recon_snr;
    return -1;
}

/* ------------------------------------------------------------ energies */

static int dq_coarse(SscDecoder *st, ec_dec *dec, int end, int32_t budget) {
    int16_t *old = st->oldBandE;
    int32_t prev[2] = {0, 0};
    int i, c, intra = 0;
    int32_t coef, beta;
    const unsigned char *prob;
    if ((int32_t)ec_tell(dec) + 3 <= budget) intra = ec_dec_bit_logp(dec, 3);
    prob = intra ? e_prob_intra : e_prob_inter;
    coef = intra ? 0 : 16384;
    beta = intra ? 4915 : 6554;
    for (i = 0; i < end; i++)
        for (c = 0; c < 2; c++) {
            int qi;
            int32_t tell = ec_tell(dec), q, tmp, cterm;
            int16_t oldE;
            if (budget - tell >= 15) {
                int pi = 2 * IMIN(i, 20);
                qi = ec_laplace_decode(dec, prob[pi] << 7, prob[pi + 1] << 6);
            } else if (budget - tell >= 2) {
                qi = ec_dec_icdf(dec, small_energy_icdf, 2);
                qi = (qi >> 1) ^ -(qi & 1);
            } else if (budget - tell >= 1) {
                qi = -ec_dec_bit_logp(dec, 1);
            } else {
                qi = -1;
            }
            oldE = MAX16(-QCONST16(9.f, DB_SHIFT), old[i + c * NB]);
            cterm = (coef * oldE) >> 8;
            q = (int32_t)SHL32(EXTEND32(qi), DB_SHIFT);
            tmp = cterm + prev[c] + SHL32(q, 7);
            tmp = MAX32(-QCONST32(28.f, DB_SHIFT + 7), tmp);
            old[i + c * NB] = (int16_t)PSHR32(tmp, 7);
            prev[c] = prev[c] + SHL32(q, 7) - MULT16_16(beta, (int16_t)PSHR32(q, 8));
        }
    return intra;
}

static void dq_fine(SscDecoder *st, ec_dec *dec, int end, const int32_t *fine_quant) {
    int i, c;
    for (i = 0; i < end; i++) {
        if (fine_quant[i] <= 0) continue;
        for (c = 0; c < 2; c++) {
            int q2 = (int)ec_dec_bits(dec, fine_quant[i]);
            int16_t offset = (int16_t)(SHR32(SHL32(EXTEND32(q2), DB_SHIFT) + QCONST16(.5f, DB_SHIFT),
                                             fine_quant[i]) -
                                       QCONST16(.5f, DB_SHIFT));
            st->oldBandE[i + c * NB] = (int16_t)(st->oldBandE[i + c * NB] + offset);
        }
    }
}

static void dq_finalise(SscDecoder *st, ec_dec *dec, int end, const int32_t *fine_quant,
                        const int32_t *fine_priority, int bits_left) {
    int i, prio, c;
    for (prio = 0; prio < 2; prio++)
        for (i = 0; i < end && bits_left >= 2; i++) {
            if (fine_quant[i] >= 8 || fine_priority[i] != prio) continue;
            for (c = 0; c < 2; c++) {
                int q2 = (int)ec_dec_bits(dec, 1);
                st->oldBandE[i + c * NB] =
                    (int16_t)(st->oldBandE[i + c * NB] + ((q2 * 1024 - 512) >> (fine_quant[i] + 1)));
                bits_left--;
            }
        }
}

/* ------------------------------------------------------------ tf */

static void tf_decode(int end, int isTransient, int *tf_res, ec_dec *dec) {
    uint32_t budget = dec->storage * 8, tell = ec_tell(dec);
    int logp = isTransient ? 2 : 4, tf_select_rsv, tf_changed = 0, curr = 0, tf_select = 0, i;
    tf_select_rsv = tell + logp + 1 <= budget;
    budget -= tf_select_rsv;
    for (i = 0; i < end; i++) {
        if (tell + logp <= budget) {
            curr ^= ec_dec_bit_logp(dec, logp);
            tell = ec_tell(dec);
            tf_changed |= curr;
        }
        tf_res[i] = curr;
        logp = isTransient ? 4 : 5;
    }
    if (tf_select_rsv && tf_select_table[4 * isTransient + 0 + tf_changed] !=
                             tf_select_table[4 * isTransient + 2 + tf_changed])
        tf_select = ec_dec_bit_logp(dec, 1);
    for (i = 0; i < end; i++) tf_res[i] = tf_select_table[4 * isTransient + 2 * tf_select + tf_res[i]];
}

/* ------------------------------------------------------------ allocation (decode side) */

typedef struct {
    int32_t total;
    int32_t fine_quant[NB], pulses[NB], fine_priority[NB];
    int offsets[NB];
    int alloc_trim, dual_stereo, intensity;
    int32_t balance;
    int table2;
} Alloc;

static int interp_bits2pulses(const SscMode *m, int end, int skip_start, const int *bits1,
                              const int *bits2, const int *thresh, const int32_t *cap, int32_t total,
                              int32_t *_balance, int skip_rsv, int *intensity, int intensity_rsv,
                              int *dual_stereo, int dual_stereo_rsv, int32_t *bits, int32_t *ebits,
                              int32_t *fine_priority, ec_dec *ec) {
    const int16_t *eBands = m->eBands;
    int32_t psum, left, percoeff, balance;
    int lo = 0, hi = 1 << 6, i, j, codedBands, done;
    const int alloc_floor = 2 << BITRES, stereo = 1, logM = LM3 << BITRES;
    for (i = 0; i < 6; i++) {
        int mid = (lo + hi) >> 1;
        psum = 0;
        done = 0;
        for (j = end; j-- > 0;) {
            int tmp = bits1[j] + (mid * (int32_t)bits2[j] >> 6);
            if (tmp >= thresh[j] || done) {
                done = 1;
                psum += IMIN(tmp, cap[j]);
            } else if (tmp >= alloc_floor) {
                psum += alloc_floor;
            }
        }
        if (psum > total) hi = mid;
        else lo = mid;
    }
    psum = 0;
    done = 0;
    for (j = end; j-- > 0;) {
        int tmp = bits1[j] + ((int32_t)lo * bits2[j] >> 6);
        if (tmp < thresh[j] && !done)
            tmp = tmp >= alloc_floor ? alloc_floor : 0;
        else
            done = 1;
        tmp = IMIN(tmp, cap[j]);
        bits[j] = tmp;
        psum += tmp;
    }
    for (codedBands = end;; codedBands--) {
        int band_width, band_bits, rem;
        j = codedBands - 1;
        if (j <= skip_start) {
            total += skip_rsv;
            break;
        }
        left = total - psum;
        percoeff = (int32_t)((uint32_t)left / (uint32_t)(eBands[codedBands] - eBands[0]));
        left -= (eBands[codedBands] - eBands[0]) * percoeff;
        rem = IMAX(left - (eBands[j] - eBands[0]), 0);
        band_width = eBands[codedBands] - eBands[j];
        band_bits = (int)(bits[j] + percoeff * band_width + rem);
        if (band_bits >= IMAX(thresh[j], alloc_floor + (1 << BITRES))) {
            if (ec_dec_bit_logp(ec, 1)) break;
            psum += 1 << BITRES;
            band_bits -= 1 << BITRES;
        }
        psum -= bits[j] + intensity_rsv;
        if (intensity_rsv > 0) intensity_rsv = LOG2_FRAC_TABLE[j];
        psum += intensity_rsv;
        if (band_bits >= alloc_floor) {
            psum += alloc_floor;
            bits[j] = alloc_floor;
        } else {
            bits[j] = 0;
        }
    }
    if (intensity_rsv > 0)
        *intensity = (int)ec_dec_uint(ec, codedBands + 1);
    else
        *intensity = 0;
    if (*intensity <= 0) {
        total += dual_stereo_rsv;
        dual_stereo_rsv = 0;
    }
    if (dual_stereo_rsv > 0)
        *dual_stereo = ec_dec_bit_logp(ec, 1);
    else
        *dual_stereo = 0;

    left = total - psum;
    percoeff = (int32_t)((uint32_t)left / (uint32_t)(eBands[codedBands] - eBands[0]));
    left -= (eBands[codedBands] - eBands[0]) * percoeff;
    for (j = 0; j < codedBands; j++) bits[j] += (int)percoeff * (eBands[j + 1] - eBands[j]);
    for (j = 0; j < codedBands; j++) {
        int tmp = (int)IMIN(left, eBands[j + 1] - eBands[j]);
        bits[j] += tmp;
        left -= tmp;
    }
    balance = 0;
    for (j = 0; j < codedBands; j++) {
        int N0b = eBands[j + 1] - eBands[j], N = N0b << LM3, den, offset, NClogN;
        int32_t excess, bit = (int32_t)bits[j] + balance;
        if (N > 1) {
            excess = MAX32(bit - cap[j], 0);
            bits[j] = bit - excess;
            den = 2 * N + ((N > 2 && !*dual_stereo && j < *intensity) ? 1 : 0);
            NClogN = den * (m->logN[j] + logM);
            offset = (NClogN >> 1) - den * FINE_OFFSET;
            if (N == 2) offset += den << BITRES >> 2;
            if (bits[j] + offset < den * 2 << BITRES)
                offset += NClogN >> 2;
            else if (bits[j] + offset < den * 3 << BITRES)
                offset += NClogN >> 3;
            ebits[j] = IMAX(0, (bits[j] + offset + (den << (BITRES - 1))));
            ebits[j] = (int)((uint32_t)ebits[j] / (uint32_t)den) >> BITRES;
            if (2 * ebits[j] > (bits[j] >> BITRES)) ebits[j] = bits[j] >> stereo >> BITRES;
            ebits[j] = IMIN(ebits[j], MAX_FINE_BITS);
            fine_priority[j] = ebits[j] * (den << BITRES) >= bits[j] + offset;
            bits[j] -= 2 * ebits[j] << BITRES;
        } else {
            excess = MAX32(0, bit - (2 << BITRES));
            bits[j] = bit - excess;
            ebits[j] = 0;
            fine_priority[j] = 1;
        }
        if (excess > 0) {
            int extra_fine = IMIN(excess >> (stereo + BITRES), MAX_FINE_BITS - ebits[j]);
            int extra_bits = extra_fine * 2 << BITRES;
            ebits[j] += extra_fine;
            fine_priority[j] = extra_bits >= excess - balance;
            excess -= extra_bits;
        }
        balance = excess;
    }
    *_balance = balance;
    for (; j < end; j++) {
        ebits[j] = bits[j] >> stereo >> BITRES;
        bits[j] = 0;
        fine_priority[j] = ebits[j] < 1;
    }
    return codedBands;
}

static int compute_allocation_dec(const SscMode *m, Alloc *a, ec_dec *ec, int end) {
    const int16_t *eBands = m->eBands;
    const int32_t *cap = m->cache.caps;
    const uint8_t *alloc = a->table2 ? m->allocVectors2 : m->allocVectors;
    int len = m->nbEBands, lo, hi, j, skip_start = 0, skip_rsv, intensity_rsv, dual_stereo_rsv;
    int bits1[NB], bits2[NB], thresh[NB], trim_offset[NB];
    int32_t total = IMAX(a->total, 0);
    skip_rsv = total >= 1 << BITRES ? 1 << BITRES : 0;
    total -= skip_rsv;
    intensity_rsv = LOG2_FRAC_TABLE[end];
    dual_stereo_rsv = 0;
    if (intensity_rsv > total) {
        intensity_rsv = 0;
    } else {
        total -= intensity_rsv;
        dual_stereo_rsv = total >= 1 << BITRES ? 1 << BITRES : 0;
        total -= dual_stereo_rsv;
    }
    for (j = 0; j < end; j++) {
        int w = eBands[j + 1] - eBands[j];
        thresh[j] = IMAX(2 << BITRES, (3 * w << LM3 << BITRES) >> 4);
        trim_offset[j] = 2 * w * (a->alloc_trim - 5 - LM3) * (end - j - 1) * (1 << (LM3 + BITRES)) >> 6;
        if (w << LM3 == 1) trim_offset[j] -= 2 << BITRES;
    }
    lo = 1;
    hi = m->nbAllocVectors - 1;
    do {
        int done = 0, psum = 0, mid = (lo + hi) >> 1;
        for (j = end; j-- > 0;) {
            int N = eBands[j + 1] - eBands[j];
            int bitsj = 2 * N * alloc[mid * len + j] << LM3 >> 2;
            if (bitsj > 0) bitsj = IMAX(0, bitsj + trim_offset[j]);
            bitsj += a->offsets[j];
            if (bitsj >= thresh[j] || done) {
                done = 1;
                psum += IMIN(bitsj, cap[j]);
            } else if (bitsj >= 2 << BITRES) {
                psum += 2 << BITRES;
            }
        }
        if (psum > total) hi = mid - 1;
        else lo = mid + 1;
    } while (lo <= hi);
    hi = lo--;
    for (j = 0; j < end; j++) {
        int N = eBands[j + 1] - eBands[j];
        int bits1j = 2 * N * alloc[lo * len + j] << LM3 >> 2;
        int bits2j = hi >= m->nbAllocVectors ? cap[j] : 2 * N * alloc[hi * len + j] << LM3 >> 2;
        if (bits1j > 0) bits1j = IMAX(0, bits1j + trim_offset[j]);
        if (bits2j > 0) bits2j = IMAX(0, bits2j + trim_offset[j]);
        if (lo > 0) bits1j += a->offsets[j];
        bits2j += a->offsets[j];
        if (a->offsets[j] > 0) skip_start = j;
        bits2j = IMAX(0, bits2j - bits1j);
        bits1[j] = bits1j;
        bits2[j] = bits2j;
    }
    return interp_bits2pulses(m, end, skip_start, bits1, bits2, thresh, cap, total, &a->balance,
                              skip_rsv, &a->intensity, intensity_rsv, &a->dual_stereo,
                              dual_stereo_rsv, a->pulses, a->fine_quant, a->fine_priority, ec);
}

/* ------------------------------------------------------------ PVQ (decode, float) */

typedef struct {
    const SscMode *m;
    int i, spread, tf_change;
    ec_dec *ec;
    int32_t remaining_bits;
    uint32_t seed;
} Ctx;

typedef struct {
    int imid, iside, delta, itheta, qalloc;
} Split;

static int16_t bitexact_cos(int16_t x) {
    int32_t tmp;
    int16_t x2;
    tmp = (4096 + ((int32_t)(x) * (x))) >> 13;
    x2 = (int16_t)tmp;
    x2 = (int16_t)((32767 - x2) + FRAC_MUL16(x2, (-7651 + FRAC_MUL16(x2, (8277 + FRAC_MUL16(-626, x2))))));
    return (int16_t)(1 + x2);
}

static int bitexact_log2tan(int isin, int icos) {
    int lc = EC_ILOG(icos), ls = EC_ILOG(isin);
    icos <<= 15 - lc;
    isin <<= 15 - ls;
    return (ls - lc) * (1 << 11) + FRAC_MUL16(isin, FRAC_MUL16(isin, -2597) + 7932) -
           FRAC_MUL16(icos, FRAC_MUL16(icos, -2597) + 7932);
}

static int compute_qn(int N, int b, int offset, int pulse_cap) {
    int qn, qb, N2 = 2 * N - 1;
    qb = N2 ? (b + N2 * offset) / N2 : 0;
    qb = IMIN(b - pulse_cap - (4 << BITRES), qb);
    qb = IMIN(8 << BITRES, qb);
    if (qb < (1 << BITRES >> 1)) return 1;
    qn = exp2_table8[qb & 0x7] >> (14 - (qb >> BITRES));
    return (qn + 1) >> 1 << 1;
}

static void theta_to_split(Split *s, int itheta, int N, int B, int *fill) {
    if (itheta == 0) {
        s->imid = 32767;
        s->iside = 0;
        *fill &= (1 << B) - 1;
        s->delta = -16384;
    } else if (itheta == 16384) {
        s->imid = 0;
        s->iside = 32767;
        *fill &= ((1 << B) - 1) << B;
        s->delta = 16384;
    } else {
        s->imid = bitexact_cos((int16_t)itheta);
        s->iside = bitexact_cos((int16_t)(16384 - itheta));
        s->delta = FRAC_MUL16((N - 1) << 7, bitexact_log2tan(s->iside, s->imid));
    }
    s->itheta = itheta;
}

static int bits2pulses(const SscMode *m, int band, int LM, int bits) {
    const unsigned char *cache = m->cache.bits + m->cache.index[(LM + 1) * m->nbEBands + band];
    int i, lo = 0, hi = cache[0];
    bits--;
    for (i = 0; i < 6; i++) {
        int mid = (lo + hi + 1) >> 1;
        if ((int)cache[mid] >= bits) hi = mid;
        else lo = mid;
    }
    if (bits - (lo == 0 ? -1 : (int)cache[lo]) <= (int)cache[hi] - bits) return lo;
    return hi;
}

static int pulses2bits(const SscMode *m, int band, int LM, int pulses) {
    const unsigned char *cache = m->cache.bits + m->cache.index[(LM + 1) * m->nbEBands + band];
    return pulses == 0 ? 0 : cache[pulses] + 1;
}

static void haar1f(float *X, int n0, int stride) {
    int i, j;
    n0 >>= 1;
    for (i = 0; i < stride; i++)
        for (j = 0; j < n0; j++) {
            float a = .70710678f * X[stride * 2 * j + i], b = .70710678f * X[stride * (2 * j + 1) + i];
            X[stride * 2 * j + i] = a + b;
            X[stride * (2 * j + 1) + i] = a - b;
        }
}

static void interleave_hadamard(float *X, int n0, int stride, int hadamard) {
    float tmp[N0];
    int i, j, N = n0 * stride;
    if (hadamard) {
        const int *ordery = ordery_table + stride - 2;
        for (i = 0; i < stride; i++)
            for (j = 0; j < n0; j++) tmp[j * stride + i] = X[ordery[i] * n0 + j];
    } else {
        for (i = 0; i < stride; i++)
            for (j = 0; j < n0; j++) tmp[j * stride + i] = X[i * n0 + j];
    }
    memcpy(X, tmp, N * sizeof(*X));
}

static void renormalise(float *X, int N, float gain) {
    double e = 1e-15;
    int j;
    for (j = 0; j < N; j++) e += (double)X[j] * X[j];
    e = gain / sqrt(e);
    for (j = 0; j < N; j++) X[j] = (float)(X[j] * e);
}

static void exp_rotation1(float *X, int len, int stride, float c, float s) {
    int i;
    float ms = -s, *Xptr = X;
    for (i = 0; i < len - stride; i++) {
        float x1 = Xptr[0], x2 = Xptr[stride];
        Xptr[stride] = c * x2 + s * x1;
        *Xptr++ = c * x1 + ms * x2;
    }
    Xptr = &X[len - 2 * stride - 1];
    for (i = len - 2 * stride - 1; i >= 0; i--) {
        float x1 = Xptr[0], x2 = Xptr[stride];
        Xptr[stride] = c * x2 + s * x1;
        *Xptr-- = c * x1 + ms * x2;
    }
}

/* Inverse of the encoder's exp_rotation (Opus dir = -1), same gain/theta. */
static void exp_rotation_inv(float *X, int len, int stride, int K, int spread) {
    static const int SPREAD_FACTOR[3] = {15, 10, 5};
    int i, stride2 = 0;
    int16_t gain, theta;
    float c, s;
    if (2 * K >= len || spread == 0) return;
    gain = (int16_t)((int64_t)celt_rcp(len + SPREAD_FACTOR[spread - 1] * K) *
                         (int64_t)((int16_t)len * 32767) >> 31);
    theta = (int16_t)((uint32_t)(gain * gain) >> 16);
    c = celt_cos_norm(EXTEND32(theta)) / 32768.f;
    s = celt_cos_norm(EXTEND32(theta ^ 0x7fff)) / 32768.f;
    if (len >= 8 * stride) {
        stride2 = 1;
        while ((stride2 * stride2 + stride2) * stride + (stride >> 2) < len) stride2++;
    }
    len /= stride;
    for (i = 0; i < stride; i++) {
        if (stride2) exp_rotation1(X + i * len, len, stride2, s, c);
        exp_rotation1(X + i * len, len, 1, c, s);
    }
}

static unsigned alg_unquant(float *X, int N, int K, int spread, int B, ec_dec *dec, float gain) {
    int iy[N0], i, j;
    double Ryy = 0;
    unsigned cm = 0;
    decode_pulses(iy, N, K, dec);
    for (j = 0; j < N; j++) Ryy += (double)iy[j] * iy[j];
    for (j = 0; j < N; j++) X[j] = (float)(iy[j] * gain / sqrt(Ryy));
    exp_rotation_inv(X, N, B, K, spread);
    if (B <= 1) return 1;
    for (i = 0; i < B; i++) {
        int n0 = N / B;
        for (j = 0; j < n0; j++)
            if (iy[i * n0 + j]) {
                cm |= 1u << i;
                break;
            }
    }
    return cm;
}

static void theta_mono(Ctx *ctx, Split *s, int N, int *b, int B, int B0, int LM, int *fill) {
    int pulse_cap = ctx->m->logN[ctx->i] + LM * (1 << BITRES);
    int offset = (pulse_cap >> 1) - QTHETA_OFFSET;
    int qn = compute_qn(N, *b, offset, pulse_cap), itheta = 0;
    int32_t tell = ec_tell_frac(ctx->ec);
    if (qn != 1) {
        if (B0 > 1) {
            itheta = (int)ec_dec_uint(ctx->ec, qn + 1);
        } else {
            int fm, fs, fl, ft = ((qn >> 1) + 1) * ((qn >> 1) + 1);
            fm = (int)ec_decode(ctx->ec, ft);
            if (fm < ((qn >> 1) * ((qn >> 1) + 1) >> 1)) {
                itheta = (int)(isqrt32(8 * (uint32_t)fm + 1) - 1) >> 1;
                fs = itheta + 1;
                fl = itheta * (itheta + 1) >> 1;
            } else {
                itheta = (2 * (qn + 1) - (int)isqrt32(8 * (uint32_t)(ft - fm - 1) + 1)) >> 1;
                fs = qn + 1 - itheta;
                fl = ft - ((qn + 1 - itheta) * (qn + 2 - itheta) >> 1);
            }
            ec_dec_update(ctx->ec, fl, fl + fs, ft);
        }
        itheta = (itheta * 16384) / qn;
    }
    s->qalloc = ec_tell_frac(ctx->ec) - tell;
    *b -= s->qalloc;
    theta_to_split(s, itheta, N, B, fill);
}

static unsigned dq_partition(Ctx *ctx, float *X, int N, int b, int B, int LM, float gain, int fill) {
    const SscMode *m = ctx->m;
    const unsigned char *cache = m->cache.bits + m->cache.index[(LM + 1) * m->nbEBands + ctx->i];
    unsigned cm = 0;
    int B0 = B;
    if (LM != -1 && b > cache[cache[0]] + 12 && N > 2) {
        int mbits, sbits, delta, itheta;
        int32_t rebalance;
        Split s;
        float *Y, mid, side;
        N >>= 1;
        Y = X + N;
        LM -= 1;
        if (B == 1) fill = (fill & 1) | (fill << 1);
        B = (B + 1) >> 1;
        theta_mono(ctx, &s, N, &b, B, B0, LM, &fill);
        delta = s.delta;
        itheta = s.itheta;
        mid = s.imid / 32768.f;
        side = s.iside / 32768.f;
        if (B0 > 1 && (itheta & 0x3fff)) {
            if (itheta > 8192) delta -= delta >> (4 - LM);
            else delta = IMIN(0, delta + (N << BITRES >> (5 - LM)));
        }
        mbits = IMAX(0, IMIN(b, (b - delta) / 2));
        sbits = b - mbits;
        ctx->remaining_bits -= s.qalloc;
        rebalance = ctx->remaining_bits;
        if (mbits >= sbits) {
            cm = dq_partition(ctx, X, N, mbits, B, LM, gain * mid, fill);
            rebalance = mbits - (rebalance - ctx->remaining_bits);
            if (rebalance > 3 << BITRES && itheta != 0) sbits += rebalance - (3 << BITRES);
            cm |= dq_partition(ctx, Y, N, sbits, B, LM, gain * side, fill >> B) << (B0 >> 1);
        } else {
            cm = dq_partition(ctx, Y, N, sbits, B, LM, gain * side, fill >> B) << (B0 >> 1);
            rebalance = sbits - (rebalance - ctx->remaining_bits);
            if (rebalance > 3 << BITRES && itheta != 16384) mbits += rebalance - (3 << BITRES);
            cm |= dq_partition(ctx, X, N, mbits, B, LM, gain * mid, fill);
        }
    } else {
        int q = bits2pulses(m, ctx->i, LM, b), curr_bits = pulses2bits(m, ctx->i, LM, q);
        ctx->remaining_bits -= curr_bits;
        while (ctx->remaining_bits < 0 && q > 0) {
            ctx->remaining_bits += curr_bits;
            q--;
            curr_bits = pulses2bits(m, ctx->i, LM, q);
            ctx->remaining_bits -= curr_bits;
        }
        if (q != 0) {
            int K = q < 8 ? q : (8 + (q & 7)) << ((q >> 3) - 1);
            cm = alg_unquant(X, N, K, ctx->spread, B, ctx->ec, gain);
        } else {
            /* no pulses: noise where the band is not folded (Opus folds lower
             * bands here; the Buds' behaviour is not known) */
            unsigned mask = (1u << B) - 1;
            int j;
            fill &= (int)mask;
            if (!fill) {
                for (j = 0; j < N; j++) X[j] = 0;
            } else {
                for (j = 0; j < N; j++) {
                    ctx->seed = lcg(ctx->seed);
                    X[j] = (float)((int32_t)ctx->seed >> 20);
                }
                cm = mask;
                renormalise(X, N, gain);
            }
        }
    }
    return cm;
}

static unsigned dq_band(Ctx *ctx, float *X, int N, int b, int B, float gain, int fill) {
    int N_B = N / B, N_B0, B0, k, recombine = 0, time_divide = 0, tf_change = ctx->tf_change;
    int longBlocks = B == 1;
    unsigned cm;
    if (tf_change > 0) recombine = tf_change;
    for (k = 0; k < recombine; k++)
        fill = bit_interleave_table[fill & 0xF] | bit_interleave_table[fill >> 4] << 2;
    B >>= recombine;
    N_B <<= recombine;
    while ((N_B & 1) == 0 && tf_change < 0) {
        fill |= fill << B;
        B <<= 1;
        N_B >>= 1;
        time_divide++;
        tf_change++;
    }
    B0 = B;
    N_B0 = N_B;
    cm = dq_partition(ctx, X, N, b, B, LM3, gain, fill);
    if (B0 > 1) interleave_hadamard(X, N_B >> recombine, B0 << recombine, longBlocks);
    N_B = N_B0;
    B = B0;
    for (k = 0; k < time_divide; k++) {
        B >>= 1;
        N_B <<= 1;
        cm |= cm >> B;
        haar1f(X, N_B, B);
    }
    for (k = 0; k < recombine; k++) {
        cm = bit_deinterleave_table[cm & 0xF];
        haar1f(X, N >> k, 1 << k);
    }
    return cm;
}

static void stereo_merge(float *X, float *Y, float mid, int N) {
    double xp = 0, side = 0, El, Er, lg, rg;
    int j;
    for (j = 0; j < N; j++) {
        xp += (double)Y[j] * X[j];
        side += (double)Y[j] * Y[j];
    }
    xp *= mid;
    El = (double)mid * mid + side - 2 * xp;
    Er = (double)mid * mid + side + 2 * xp;
    if (Er < 6e-4 || El < 6e-4) {
        memcpy(Y, X, N * sizeof(*X));
        return;
    }
    lg = 1 / sqrt(El);
    rg = 1 / sqrt(Er);
    for (j = 0; j < N; j++) {
        double l = mid * X[j], r = Y[j];
        X[j] = (float)(lg * (l - r));
        Y[j] = (float)(rg * (l + r));
    }
}

static void dq_all_bands(SscDecoder *st, int end, float *X_, const int32_t *pulses, int shortBlocks,
                         int spread, int dual_stereo, int intensity, const int *tf_res,
                         int32_t total_bits, int32_t balance, ec_dec *ec, int codedBands) {
    const SscMode *m = st->m;
    const int16_t *eBands = m->eBands;
    int B = shortBlocks ? 8 : 1, i, fill = (1 << B) - 1;
    Ctx ctx;
    ctx.m = m;
    ctx.spread = spread;
    ctx.ec = ec;
    ctx.seed = st->seed;
    for (i = 0; i < end; i++) {
        float *X = X_ + 8 * eBands[i], *Y = X + N0;
        int N = 8 * (eBands[i + 1] - eBands[i]), b = 0;
        int32_t tell = ec_tell_frac(ec), remaining_bits;
        ctx.i = i;
        if (i != 0) balance -= tell;
        remaining_bits = total_bits - tell - 1;
        ctx.remaining_bits = remaining_bits;
        if (i < codedBands) {
            int32_t curr_balance = balance / IMIN(3, codedBands - i);
            b = IMAX(0, IMIN(16383, IMIN(remaining_bits + 1, pulses[i] + curr_balance)));
        }
        ctx.tf_change = tf_res[i];
        if (dual_stereo && i == intensity) dual_stereo = 0;
        if (dual_stereo) {
            dq_band(&ctx, X, N, b / 2, B, 1.f, fill);
            dq_band(&ctx, Y, N, b / 2, B, 1.f, fill);
        } else {
            int pulse_cap = m->logN[i] + LM3 * (1 << BITRES), offset = (pulse_cap >> 1) - QTHETA_OFFSET;
            int qn = compute_qn(N, b, offset, pulse_cap), itheta = 0, inv = 0, j;
            int32_t t0 = ec_tell_frac(ec), rebalance;
            int mbits, sbits, sfill = fill;
            Split s;
            if (i >= intensity) qn = 1;
            if (qn != 1) {
                int x0 = qn / 2, ft = 3 * (x0 + 1) + x0, fs, x;
                fs = (int)ec_decode(ec, ft);
                x = fs < (x0 + 1) * 3 ? fs / 3 : x0 + 1 + (fs - (x0 + 1) * 3);
                ec_dec_update(ec, x <= x0 ? 3 * x : (x - 1 - x0) + (x0 + 1) * 3,
                              x <= x0 ? 3 * (x + 1) : (x - x0) + (x0 + 1) * 3, ft);
                itheta = (x * 16384) / qn;
            } else {
                if (b > 2 << BITRES && ctx.remaining_bits > 2 << BITRES) inv = ec_dec_bit_logp(ec, 2);
                itheta = 0;
            }
            s.qalloc = ec_tell_frac(ec) - t0;
            b -= s.qalloc;
            theta_to_split(&s, itheta, N, B, &sfill);
            mbits = IMAX(0, IMIN(b, (b - s.delta) / 2));
            sbits = b - mbits;
            ctx.remaining_bits -= s.qalloc;
            rebalance = ctx.remaining_bits;
            if (mbits >= sbits) {
                dq_band(&ctx, X, N, mbits, B, 1.f, sfill);
                rebalance = mbits - (rebalance - ctx.remaining_bits);
                if (rebalance > 3 << BITRES && itheta != 0) sbits += rebalance - (3 << BITRES);
                dq_band(&ctx, Y, N, sbits, B, s.iside / 32768.f, sfill >> B);
            } else {
                dq_band(&ctx, Y, N, sbits, B, s.iside / 32768.f, sfill >> B);
                rebalance = sbits - (rebalance - ctx.remaining_bits);
                if (rebalance > 3 << BITRES && itheta != 16384) mbits += rebalance - (3 << BITRES);
                dq_band(&ctx, X, N, mbits, B, 1.f, sfill);
            }
            stereo_merge(X, Y, s.imid / 32768.f, N);
            if (inv)
                for (j = 0; j < N; j++) Y[j] = -Y[j];
        }
        balance += pulses[i] + tell;
    }
    st->seed = ctx.seed;
}

/* ------------------------------------------------------------ frame */

static const Rate *parse_header(const uint8_t *fr, int *counter, int *drop) {
    const Rate *r = NULL;
    size_t i;
    int code = fr[3] & 0x1f;
    if (fr[0] != 0xFF) return NULL;
    for (i = 0; i < sizeof kRates / sizeof kRates[0]; i++)
        if (kRates[i].code == code) r = &kRates[i];
    if (!r) return NULL;
    if (!r->uhq && fr[1] != 0xEE) return NULL;
    if (r->uhq && (fr[1] & 0xF0) != 0xE0) return NULL;
    *counter = (fr[2] >> 4) | (r->uhq ? (fr[1] & 0x0F) << 4 : 0);
    if (!r->wide) *drop = 0;
    else if (r->bitrate == 152000) *drop = 4;
    else if (!r->uhq) *drop = 0;
    else *drop = (fr[2] >> 2) & 3;
    return r;
}

int ssc_decode(SscDecoder *st, const uint8_t *frame, int len, int32_t *pcm) {
    const SscMode *m;
    const Rate *r;
    int counter, drop, n, nbBytes, total_bits, endc, i, c, k;
    int silence = 0, pf_on = 0, pitch = 0, qg = 0, isTransient = 0, intra, codedBands;
    int16_t gain1 = 0;
    int tf_res[NB];
    float X[2 * N0];
    int32_t tell;
    ec_dec dec;
    Alloc a;
    SscDecInfo *info = &st->info;

    if (len < 5 || !(r = parse_header(frame, &counter, &drop))) return -1;
    m = r->uhq ? &ssc_mode_96k : &ssc_mode_48k;
    if (m != st->m) {
        int fs = st->fs;
        reset(st, m);  /* another mode: a new stream */
        st->fs = fs;
        if (!synth_for(&m->mdct, 0) || !synth_for(&m->mdct, 3)) return -3;
    }
    n = r->bitrate * N0 / (m->Fs * 8);
    if (!r->wide) n += (n * 3) >> 7;
    n |= 1;
    nbBytes = IMIN(n - 1, 1275);
    if (len != nbBytes + SSC_HEADER_BYTES) return -2;
    total_bits = nbBytes * 8;
    endc = NB - drop;
    memset(info, 0, sizeof *info);
    memset(&a, 0, sizeof a);
    info->bitrate = r->bitrate;
    info->fs = r->uhq ? 96000 : 48000;
    info->counter = counter;
    info->payload = nbBytes;
    info->drop = drop;

    ec_dec_init(&dec, (unsigned char *)frame + SSC_HEADER_BYTES, (uint32_t)nbBytes);

    /* silence flag (tell is taken before it, as in the encoder) */
    tell = ec_tell(&dec);
    if (tell == 1) silence = ec_dec_bit_logp(&dec, 15);
    if (silence) {
        dec.nbits_total += total_bits - ec_tell(&dec);
        tell = total_bits;
    }
    /* post-filter */
    if (tell + 16 <= total_bits && ec_dec_bit_logp(&dec, 1)) {
        int octave = (int)ec_dec_uint(&dec, 6);
        pitch = (16 << octave) + (int)ec_dec_bits(&dec, 4 + octave) - 1;
        qg = (int)ec_dec_bits(&dec, 3);
        gain1 = (int16_t)(0xc00 * (qg + 1));
        pf_on = 1;
    }
    /* transient */
    if ((int32_t)ec_tell(&dec) + 3 <= total_bits) isTransient = ec_dec_bit_logp(&dec, 3);
    /* energies, tf, spread */
    intra = dq_coarse(st, &dec, endc, total_bits);
    if (!r->wide)
        tf_decode(NB, isTransient, tf_res, &dec);
    else
        for (i = 0; i < NB; i++) tf_res[i] = 0;
    if ((int32_t)ec_tell(&dec) + 4 <= total_bits) st->spread = ec_dec_icdf(&dec, kSpreadIcdf, 5);
    /* dynalloc boosts */
    {
        int dynalloc_logp = 6;
        int32_t tb = total_bits << 3, tf = ec_tell_frac(&dec), total_boost = 0;
        for (i = 0; i < endc; i++) {
            int width = (m->eBands[i + 1] - m->eBands[i]) << 4;
            int quanta = IMIN(width << 3, IMAX(6 << 3, width));
            int loop_logp = dynalloc_logp, boost = 0;
            while (tf + (loop_logp << 3) < tb - total_boost && boost < m->cache.caps[i]) {
                int flag = ec_dec_bit_logp(&dec, loop_logp);
                tf = ec_tell_frac(&dec);
                if (!flag) break;
                boost += quanta;
                total_boost += quanta;
                loop_logp = 1;
            }
            if (boost > 0) dynalloc_logp = IMAX(2, dynalloc_logp - 1);
            a.offsets[i] = boost;
        }
        /* Samsung: boost spill-over (uses the coarse energies, like the encoder) */
        for (i = 18; i <= 20; i++)
            if (a.offsets[i] > 1000 && a.offsets[i + 1] == 0) {
                if (st->oldBandE[i + 1] > 7000 || st->oldBandE[i + 1] > st->oldBandE[i] >> 1)
                    a.offsets[i + 1] = a.offsets[i];
                break;
            }
        a.alloc_trim = 5;
        if (tf + (6 << 3) <= tb - total_boost) a.alloc_trim = ec_dec_icdf(&dec, kTrimIcdf, 7);
        a.total = tb - (int32_t)ec_tell_frac(&dec) - 1;
    }
    {
        int anti_collapse_rsv = isTransient && a.total >= 40 ? 8 : 0, anti_collapse = 0;
        a.total -= anti_collapse_rsv;
        a.table2 = r->bitrate > 192000;
        codedBands = compute_allocation_dec(m, &a, &dec, endc);
        dq_fine(st, &dec, endc, a.fine_quant);
        memset(X, 0, sizeof X);
        dq_all_bands(st, endc, X, a.pulses, isTransient ? 8 : 0, st->spread, a.dual_stereo,
                     a.intensity, tf_res, (total_bits << 3) - anti_collapse_rsv, a.balance, &dec,
                     codedBands);
        if (anti_collapse_rsv > 0) anti_collapse = (int)ec_dec_bits(&dec, 1);
        dq_finalise(st, &dec, endc, a.fine_quant, a.fine_priority, total_bits - ec_tell(&dec));
        info->anti_collapse = anti_collapse;
    }

    /* denormalise (energies minus nothing: X has unit norm per band) */
    {
        float freq[2 * N0];
        memset(freq, 0, sizeof freq);
        if (!silence)
            for (c = 0; c < 2; c++)
                for (i = 0; i < endc; i++) {
                    int lo = 8 * m->eBands[i], hi = 8 * m->eBands[i + 1], j;
                    /* amp2Log2: log2(4 * bandE) with celt_log2's Q14 input */
                    double E = exp2((st->oldBandE[i + c * NB] + eMeans[i] * 64) / 1024.0) * 4096.0;
                    for (j = lo; j < hi; j++) freq[c * N0 + j] = (float)(X[c * N0 + j] * E);
                }
        /* energy state for the next frame, as the encoder keeps it */
        if (silence)
            for (i = 0; i < 2 * NB; i++) st->oldBandE[i] = -28672;
        for (i = endc; i < NB; i++) st->oldBandE[i] = st->oldBandE[NB + i] = -28672;

        /* inverse MDCT + overlap-add */
        for (c = 0; c < 2; c++) {
            float *syn = st->syn[c];
            memset(syn + OV, 0, sizeof(float) * N0);
            if (!isTransient) {
                Synth *s = synth_for(&m->mdct, 0);
                float g = (float)s->gain;
                for (k = 0; k < s->n2; k++) {
                    float v = freq[c * N0 + k] * g;
                    const float *row = s->F + k * s->len;
                    if (v == 0) continue;
                    for (n = 0; n < s->len; n++) syn[n] += row[n] * v;
                }
            } else {
                Synth *s = synth_for(&m->mdct, 3);
                float g = (float)s->gain;
                int b;
                for (b = 0; b < L8; b++)
                    for (k = 0; k < s->n2; k++) {
                        float v = freq[c * N0 + k * L8 + b] * g;
                        const float *row = s->F + k * s->len;
                        if (v == 0) continue;
                        for (n = 0; n < s->len; n++) syn[b * s->n2 + n] += row[n] * v;
                    }
            }
            /* to int32 for the post-filter (encoder's comb filter, gains +) */
            for (i = 0; i < N0; i++) {
                double v = syn[i];
                st->pf[c][PF_HIST + i] = v > 2147483647.0 ? 2147483647 : v < -2147483648.0 ? INT32_MIN
                                                                                         : (int32_t)lrint(v);
            }
            memmove(syn, syn + N0, sizeof(float) * OV);
        }
    }

    /* post-filter: first short block with the last frame's filter, the rest
     * crossfading to this frame's (Opus 1.1 decoder, LM != 0) */
    {
        int T0 = IMAX(st->pf_period, SSC_COMBFILTER_MINPERIOD);
        int T1 = IMAX(pf_on ? pitch : 0, SSC_COMBFILTER_MINPERIOD);
        int16_t g0 = st->pf_gain, g1 = pf_on ? gain1 : 0;
        for (c = 0; c < 2; c++) {
            int32_t *y = st->pf[c] + PF_HIST;
            comb_filter(y, y, T0, T0, OV, g0, g0, OV);
            comb_filter(y + OV, y + OV, T0, T1, N0 - OV, g0, g1, OV);
        }
        st->pf_period = pf_on ? pitch : 0;
        st->pf_gain = g1;
    }
    for (i = 0; i < N0; i++)
        for (c = 0; c < 2; c++) {
            int32_t v = st->pf[c][PF_HIST + i] >> 4;  /* CELT scale 2^27 -> 24 bit */
            pcm[2 * i + c] = v > 8388607 ? 8388607 : v < -8388608 ? -8388608 : v;
        }
    for (c = 0; c < 2; c++) memmove(st->pf[c], st->pf[c] + N0, sizeof(int32_t) * PF_HIST);

    info->silence = silence;
    info->transient = isTransient;
    info->pf_on = pf_on;
    info->pf_period = pitch;
    info->pf_qg = qg;
    info->intra = intra;
    info->spread = st->spread;
    info->intensity = a.intensity;
    info->dual_stereo = a.dual_stereo;
    info->alloc_trim = a.alloc_trim;
    info->codedBands = codedBands;
    info->bits_used = ec_tell(&dec);
    memcpy(info->oldBandE, st->oldBandE, sizeof info->oldBandE);
    for (i = 0; i < NB; i++) {
        info->pulses[i] = a.pulses[i];
        info->fine_quant[i] = a.fine_quant[i];
        info->offsets[i] = a.offsets[i];
    }
    return N0;
}
