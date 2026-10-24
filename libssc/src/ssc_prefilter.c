/* libssc — Samsung comb (pitch pre-)filter. Port of the blob's comb_filter.
 *
 * Opus 1.1 comb_filter with tapset 0 only, but higher precision: the cross-fade
 * weight is win_square (Q31, a squared window) and each tap coefficient is
 * MULT16_32_Q15(g, w) (Q31); taps are accumulated in 64 bits and rounded with
 * >>31. After the overlap, the constant filter is (g*x + 0x4000) >> 15 in 64
 * bits (Opus truncates). Which tap pairs are summed in 32 vs 64 bits follows
 * the blob exactly.
 */
#include <stdint.h>

#include "ssc_mode.h"

void SSC_COPY32(int32_t *dst, const int32_t *src, int n);

/* MULT16_32_Q15(g, w) the way the blob splits it: g*2*hi + ((lo*g) >> 15). */
static int32_t mq(int32_t g, int32_t w) {
    uint32_t hi = (uint32_t)(int32_t)(w >> 16), lo = (uint32_t)w & 0xffff;
    return (int32_t)((uint32_t)g * 2u * hi) + ((int32_t)(lo * (uint32_t)g) >> 15);
}

static int32_t r31(uint64_t s) { return (int32_t)((s + 0x40000000u) >> 31); }

static uint64_t mul(int64_t a, int64_t b) { return (uint64_t)a * (uint64_t)b; }

/* 32-bit (wrapping) sum of two taps, then widened: what the blob does for T1 taps. */
static int64_t s32(int32_t a, int32_t b) { return (int32_t)((uint32_t)a + (uint32_t)b); }

void comb_filter(int32_t *y, int32_t *x, int T0, int T1, int N, int16_t g0, int16_t g1,
                 int overlap) {
    int32_t g00, g01, g02, g10, g11, g12, x0, x1, x2, x3, x4;
    int i, ov;
    if (g0 == 0 && g1 == 0) {
        if (x != y) SSC_COPY32(y, x, N);
        return;
    }
    g10 = (int16_t)((g1 * 0x2740) >> 15);
    g11 = (g1 * 0x1bc8) >> 15;
    g12 = (g1 * 0x1098) >> 15;
    g00 = (int16_t)((g0 * 0x2740) >> 15);
    g01 = (g0 * 0x1bc8) >> 15;
    g02 = (g0 * 0x1098) >> 15;
    ov = ((overlap - 1) & 0xffff) + 1;  /* do/while over a 16-bit count */
    x1 = x[1 - T1];
    x2 = x[-T1];
    x3 = x[-T1 - 1];
    x4 = x[-T1 - 2];

    if (g1 == 0) {  /* old filter fades out, then plain copy */
        for (i = 0; i < ov; i++) {
            int32_t fp = 0x7fffffff - win_square[i];
            uint64_t s = mul(mq(g00, fp), x[i - T0]) +
                         mul(mq(g01, fp), (int64_t)x[i - T0 - 1] + x[i - T0 + 1]) +
                         mul((int64_t)x[i - T0 - 2] + x[i - T0 + 2], mq(g02, fp));
            y[i] = (int32_t)((uint32_t)x[i] + (uint32_t)r31(s));
        }
        if (x == y) return;
        SSC_COPY32(y + ov, x + ov, N - overlap);
        return;
    }

    for (i = 0; i < ov; i++) {
        int32_t f = win_square[i], fp = 0x7fffffff - f;
        uint64_t s;
        x0 = x[i + 2 - T1];
        if (g0 == 0) {          /* new filter fades in */
            s = mul(mq(g11, f), s32(x3, x1)) + mul(mq(g10, f), x2) + mul(mq(g12, f), s32(x0, x4));
        } else if (T0 == T1) {  /* same period: blend the gains */
            s = mul((int64_t)mq(g01, fp) + mq(g11, f), s32(x3, x1)) +
                mul((int64_t)mq(g02, fp) + mq(g12, f), s32(x0, x4)) +
                mul((int64_t)mq(g00, fp) + mq(g10, f), x2);
        } else {                /* period change: old taps at T0, new at T1 */
            s = mul(mq(g10, f), x2) + mul(mq(g11, f), s32(x3, x1)) + mul(mq(g12, f), s32(x0, x4)) +
                mul(mq(g01, fp), (int64_t)x[i - T0 - 1] + x[i - T0 + 1]) +
                mul(mq(g00, fp), x[i - T0]) +
                mul((int64_t)x[i - T0 - 2] + x[i - T0 + 2], mq(g02, fp));
        }
        y[i] = (int32_t)((uint32_t)x[i] + (uint32_t)r31(s));
        x4 = x3;
        x3 = x2;
        x2 = x1;
        x1 = x0;
    }

    /* constant filter for the rest of the frame */
    x1 = x[ov + 1 - T1];
    x2 = x[ov - T1];
    x3 = x[ov - T1 - 1];
    x4 = x[ov - T1 - 2];
    for (i = ov; i < ov + (N - overlap); i++) {
        uint64_t s;
        x0 = x[i + 2 - T1];
        s = mul((int16_t)g11, s32(x3, x1)) + mul((int16_t)g10, x2) + mul((int16_t)g12, s32(x0, x4));
        y[i] = (int32_t)((uint32_t)x[i] + (uint32_t)(int32_t)((s + 0x4000u) >> 15));
        x4 = x3;
        x3 = x2;
        x2 = x1;
        x1 = x0;
    }
}
