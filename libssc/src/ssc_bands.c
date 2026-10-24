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

/* Samsung: ssc_amp2Log2_asm on the even part (two bands per step, run at least
 * once), then C on the odd last band. Both take the second channel at an offset
 * of `end` (even part: end rounded down to even), not nbEBands: ssc_encode
 * always passes end = nbEBands = 22, where the two agree.
 * log2 step by step as the asm: celt_log2 without the zero check, in 32-bit
 * lanes; e << 2 wraps for energies >= 2^29 (short blocks of loud input) and the
 * negative value goes through the same shifts. */
static int32_t q15_step(int32_t n, int32_t acc, int32_t c) {
    return (int32_t)(int16_t)((int32_t)((uint32_t)n * (uint32_t)acc) >> 15) + c;
}

static int16_t log2_band(int32_t e, int i) {
    int32_t x = (int32_t)((uint32_t)e << 2), n, f;
    int i13 = 18 - (x ? __builtin_clz((uint32_t)x) : 32), sh = 2 - i13;
    n = sh >= 0 ? (int32_t)((uint32_t)x << sh) : x >> -sh;
    n -= 0xc000;
    f = (int16_t)(((int32_t)((uint32_t)n * (uint32_t)-1401) >> 15) + 2545);
    f = (int16_t)q15_step(n, f, -5217);
    f = (int16_t)q15_step(n, f, 15746);
    f = (int16_t)q15_step(n, f, -6793);
    return (int16_t)((f >> 4) + (int32_t)((uint32_t)i13 << 10) - eMeans[i] * 64);
}

void amp2Log2(const SscMode *m, int end, const int32_t *bandE, int16_t *bandLogE) {
    int even = end - end % 2, i = 0;
    (void)m;
    do {
        bandLogE[i] = log2_band(bandE[i], i);
        bandLogE[i + 1] = log2_band(bandE[i + 1], i + 1);
        bandLogE[even + i] = log2_band(bandE[even + i], i);
        bandLogE[even + i + 1] = log2_band(bandE[even + i + 1], i + 1);
        i += 2;
    } while (i < even);
    for (i = even; i < end; i++) {
        bandLogE[i] = log2_band(bandE[i], i);
        bandLogE[end + i] = log2_band(bandE[end + i], i);
    }
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

/* Sub-band ends (bins) above the last band; unnamed .rodata in the blob. */
static const int16_t cutoff_normal[4] = {708, 744, 780, 816};  /* blob va 0x27f8 */
static const int16_t cutoff_uhq[4][8] = {                      /* blob va 0x2840 */
    {738, 756, 774, 792, 810, 828, 846, 864}, {594, 612, 630, 648, 666, 684, 702, 720},
    {450, 468, 486, 504, 522, 540, 558, 576}, {306, 324, 342, 360, 378, 396, 414, 432}};

/* Energies of the narrow sub-bands above the last band, out[0..n) for the
 * first channel and out[n..2n) for the second: 4 x 36 bins from band 21 or,
 * for UHQ, row `row` (8 x 18 bins from band 21 - row), both channels alike
 * (older builds started the second channel at band 21). */
void compute_band_energies_for_lastband(const SscMode *m, const int32_t *X, int32_t *out, int n,
                                        int uhq, int row) {
    const int16_t *ends = uhq ? cutoff_uhq[row] : cutoff_normal;
    const int32_t *X1 = X + (m->shortMdctSize << 3);
    int j, lo, lo0;
    if (n < 1) return;
    lo = lo0 = m->eBands[m->nbEBands - 1 - (uhq ? row : 0)] << 3;
    for (j = 0; j < n; j++) {
        out[j] = range_energy(X, lo, ends[j]);
        lo = ends[j];
    }
    lo = lo0;
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
