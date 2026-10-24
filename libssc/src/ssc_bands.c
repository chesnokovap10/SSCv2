/* libssc — band energies, normalisation and transient decisions.
 *
 * compute_band_energies, amp2Log2 and normalise_bands are Opus 1.1 bands.c /
 * quant_bands.c with C = 2 and M = 8 fixed by the blob. Samsung additions:
 * compute_band_energies_for_lastband (energies of narrow sub-bands above the
 * last band, used for the header's bandwidth flags), a patch_transient_decision
 * limited to bands 13+, and a float time-domain transient detector.
 */
#include <string.h>

#include "opus/arch.h"
#include "opus/entcode.h"
#include "opus/mathops.h"
#include "ssc_encoder.h"
#include "ssc_internal.h"

#define C2 2
#define M8 8

/* VSHR32 with wrap-safe left shifts (EXTRACT16 follows in the callers). */
static inline int32_t vshr32(int32_t a, int s) {
    return s > 0 ? a >> s : (int32_t)((uint32_t)a << -s);
}

/* Energy of X[lo..hi) (at least one bin, like Opus' do-while): 1 + sqrt(sum)
 * with the samples normalised to ~10 bits first; 1 for an all-zero range. */
static int32_t range_energy(const int32_t *X, int lo, int hi) {
    int32_t maxval = 0, sum = 0;
    int j = lo, shift;
    do {
        if (maxval <= X[j]) maxval = X[j];
        if (maxval <= -X[j]) maxval = -X[j];
    } while (++j < hi);
    if (maxval < 1) return 1;
    shift = (int16_t)(EC_ILOG(maxval) - 1) - 10;
    j = lo;
    do {
        int32_t t = (int16_t)vshr32(X[j], shift);
        sum = (int32_t)((uint32_t)sum + (uint32_t)(t * t));
    } while (++j < hi);
    return 1 + vshr32(celt_sqrt(sum), -shift);
}

void compute_band_energies(const SscMode *m, const int32_t *X, int32_t *bandE, int end) {
    const int16_t *eBands = m->eBands;
    int N = M8 * m->shortMdctSize, c, i;
    for (c = 0; c < C2; c++)
        for (i = 0; i < end; i++)
            bandE[i + c * m->nbEBands] =
                range_energy(X + c * N, M8 * eBands[i], M8 * eBands[i + 1]);
}

void amp2Log2(const SscMode *m, int effEnd, int end, const int32_t *bandE, int16_t *bandLogE,
              int C) {
    int c = 0, i;
    do {
        for (i = 0; i < effEnd; i++)
            bandLogE[i + c * m->nbEBands] =
                (int16_t)(celt_log2(SHL32(bandE[i + c * m->nbEBands], 2)) - SHL16(eMeans[i], 6));
        for (i = effEnd; i < end; i++) bandLogE[c * m->nbEBands + i] = -QCONST16(14.f, DB_SHIFT);
    } while (++c < C);
}

/* X (int16) overwrites freq (int32) in place, as in the blob: element j of X
 * only clobbers freq[j/2], already consumed. Accesses go through memcpy so
 * the compiler sees the aliasing. */
void normalise_bands(const SscMode *m, const int32_t *freq, int16_t *X, const int32_t *bandE,
                     int end) {
    const int16_t *eBands = m->eBands;
    int N = M8 * m->shortMdctSize, c, i, j;
    for (c = 0; c < C2; c++) {
        i = 0;
        do {
            int32_t E32 = bandE[i + c * m->nbEBands];
            int shift = celt_zlog2(E32) - 13;
            int16_t E = (int16_t)vshr32(E32, shift);
            int16_t g = (int16_t)celt_rcp(SHL32((int32_t)E, 3));
            j = M8 * eBands[i];
            do {
                int32_t f;
                int16_t x;
                memcpy(&f, (const char *)freq + 4 * (j + c * N), 4);
                x = (int16_t)(((int32_t)(int16_t)vshr32(f, shift - 1) * g) >> 15);
                memcpy((char *)X + 2 * (j + c * N), &x, 2);
            } while (++j < M8 * eBands[i + 1]);
        } while (++i < end);
    }
}

/* Energies of the narrow sub-bands above the last band, out[0..n) for the
 * first channel and out[n..2n) for the second. Sub-band ends come from the
 * int16 tables cutoff_start_index (4 x 36 bins from band 21) or, for UHQ,
 * row `row` of cutoff_start_uhq_index (8 x 18 bins from band 21 - row).
 * The second channel always starts at band 21 (blob quirk, kept). */
void compute_band_energies_for_lastband(const SscMode *m, const int32_t *X, int32_t *out, int n,
                                        int uhq, int row) {
    const int16_t *ends = uhq ? (const int16_t *)cutoff_start_uhq_index + 8 * row
                              : (const int16_t *)cutoff_start_index;
    const int32_t *X1 = X + (m->shortMdctSize << 3);
    int j, lo;
    if (n < 1) return;
    lo = m->eBands[m->nbEBands - 1 - (uhq ? row : 0)] << 3;
    for (j = 0; j < n; j++) {
        out[j] = range_energy(X, lo, ends[j]);
        lo = ends[j];
    }
    lo = m->eBands[m->nbEBands - 1] << 3;
    for (j = 0; j < n; j++) {
        out[n + j] = range_energy(X1, lo, ends[j]);
        lo = ends[j];
    }
}

/* Opus 1.1 patch_transient_decision from band 13 on: spread the old energies
 * by -1 dB/band both ways, then the mean positive increase over bands
 * 13..end-2 (two identical passes, C = 2) must exceed 1 dB. */
int patch_transient_decision(const int16_t *newE, const int16_t *oldE, int nb, int end) {
    int16_t spread[32];
    int32_t sum = 0, acc, den, mean;
    int i, pass;
    acc = oldE[13] <= oldE[13 + nb] ? oldE[13 + nb] : oldE[13];
    spread[13] = (int16_t)acc;
    for (i = 14; i < end; i++) {
        int16_t prev = (int16_t)acc;
        int16_t v = oldE[i] <= oldE[i + nb] ? oldE[i + nb] : oldE[i];
        acc -= 0x400;  /* kept as int between bands, truncated on store (blob) */
        if (prev - 0x400 <= v) acc = v;
        spread[i] = (int16_t)acc;
    }
    if (end - 2 > 12) {
        for (i = end - 2; i >= 13; i--)
            if (spread[i] <= spread[i + 1] - 0x400) spread[i] = (int16_t)(spread[i + 1] - 0x400);
        if (end - 1 > 13)
            for (pass = 0; pass < C2; pass++)
                for (i = 13; i < end - 1; i++) {
                    int32_t x1 = newE[i] > 0 ? newE[i] : 0;
                    int32_t x2 = spread[i] > 0 ? spread[i] : 0;
                    if (x1 > x2) sum += x1 - x2;
                }
    }
    den = 2 * end - 28;
    mean = den ? sum / den : 0;
    return mean > 0x400;
}

/* Samsung time-domain detector, single-precision float like the blob (plain
 * mul/sub/add, no FMA). Per channel: high-pass y = 0.7548 (x - x') + 0.5095 y'
 * over the 8 sub-blocks of `in`, energy of each; a sub-block is "loud" when its
 * energy beats r_k = 0.3 e_{k-1} + 0.7 r_{k-1}, seeded from the last sub-block
 * and running average of the previous frame. */
int patch_transient_decision_temporal(const SscMode *m, SscEncoder *st, const int32_t *in) {
    const float A = 0.7548f, B = 0.5095f;
    int L = m->shortMdctSize, stride = m->overlap + 8 * L, c, b, k, count = 0;
    int32_t pos[2] = {0, 0};  /* blob: uninitialised stack slots, observed 0 */
    for (c = 0; c < C2; c++) {
        const int32_t *x = in + c * stride;
        float e[8] = {0}, r[8], r0, mx;
        int any = 0, last = 0, hit;
        if (L >= 1) {
            float xp = st->tr_hp[c][0], yp = st->tr_hp[c][1];
            for (b = 0; b < 8; b++) {
                float s = 0.0f;
                for (k = 0; k < L; k++) {
                    float t1 = xp * A, t2 = yp * B, xf = (float)x[b * L + k];
                    float t = xf * A - t1;
                    yp = t + t2;
                    s = s + yp * yp;
                    xp = xf;
                }
                e[b] = s;
            }
            st->tr_hp[c][0] = xp;
            st->tr_hp[c][1] = yp;
        }
        r0 = st->tr_energy[c][7] * 3.0f + st->tr_avg[c] * 7.0f;
        r[0] = r0;
        for (b = 1; b < 8; b++) r[b] = e[b - 1] * 3.0f + (r[b - 1] / 10.0f) * 7.0f;
        mx = e[0] > 0.0f ? e[0] : 0.0f;
        for (b = 0; b < 8; b++) {
            if (b && !(mx > e[b])) mx = e[b];
            if (e[b] > r[b]) {
                any = 1;
                if (b) last = b;
            }
        }
        if (any) pos[c] = last;
        st->tr_avg[c] = r[7] / 10.0f;
        if (mx < 1e6f || !any)
            hit = st->tr_flag ? st->tr_pos[c] == 7 : 0;
        else
            hit = 1;
        count += hit;
        st->tr_pos[c] = pos[c];
        memcpy(st->tr_energy[c], e, sizeof e);
    }
    st->tr_flag = count != 0;
    return st->tr_flag;
}
