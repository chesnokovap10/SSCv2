/* libssc — forward MDCT and its kiss FFT (Samsung 32-bit variant).
 *
 * Same structure as Opus 1.1 clt_mdct_forward / opus_fft, but all data,
 * window, trig and twiddles are int32 (Q31) with 64-bit products, and the
 * "sin(x) ~= x" rotation of Opus is an exact rotation by a fixed (cos, sin).
 * The FFT is fully unrolled for the two sizes the encoder uses:
 *   432 points (long MDCT, shift 0):  3 x 3 x 3 x 4 x 4
 *    54 points (short MDCT, shift 3): 3 x 3 x 3 x 2
 * Every stage scales down by its radix, so the FFT divides by N.
 *
 * Arithmetic wraps like the aarch64 code: sums of products are uint64,
 * 32-bit sums are uint32.
 */
#include "ssc_encoder.h"
#include "ssc_internal.h"

typedef uint64_t u64;
typedef uint32_t u32;

#define MUL(a, b) ((u64)((int64_t)(int32_t)(a) * (int64_t)(int32_t)(b)))
#define ASR(v, s) ((int64_t)(u64)(v) >> (s))
#define ADD(a, b) ((int32_t)((u32)(a) + (u32)(b)))
#define SUB(a, b) ((int32_t)((u32)(a) - (u32)(b)))

#define RND31 0x40000000ull
#define RND33 0x100000000ull

/* round(x / 3) and round(x * -sin(2pi/3)), Q31. */
static inline int32_t div3(int32_t x) { return (int32_t)ASR(MUL(x, 0x2aaaaaab) + RND31, 31); }
static inline int32_t msin3(int32_t x) { return (int32_t)ASR(MUL(x, -0x6ed9eba1) + RND31, 31); }

/* x * w, Q31, one rounding for the whole complex term. */
static inline void cmul31(int32_t *r, int32_t *i, int32_t xr, int32_t xi, const int32_t *w) {
    *r = (int32_t)ASR(MUL(xr, w[0]) + RND31 - MUL(xi, w[1]), 31);
    *i = (int32_t)ASR(MUL(xr, w[1]) + MUL(xi, w[0]) + RND31, 31);
}

/* Radix-3 butterflies over `groups` blocks of 3m complex values (FUN_00106180
 * for m = 3, FUN_0010644c for m = 9, the first loop of ssc_fft for m = 1).
 * Inputs are divided by 3 first; k = 0 skips the twiddle multiply. */
static void bfly3(int32_t *F, int m, int groups, const int32_t *tw, int fstride) {
    int g, k;
    for (g = 0; g < groups; g++, F += 6 * m) {
        for (k = 0; k < m; k++) {
            int32_t *f0 = F + 2 * k, *f1 = f0 + 2 * m, *f2 = f1 + 2 * m;
            int32_t ar = div3(f0[0]), ai = div3(f0[1]);
            int32_t br = div3(f1[0]), bi = div3(f1[1]);
            int32_t cr = div3(f2[0]), ci = div3(f2[1]);
            int32_t tr, ti, hr, hi, er, ei;
            if (k) {
                cmul31(&br, &bi, br, bi, tw + 2 * (k * fstride));
                cmul31(&cr, &ci, cr, ci, tw + 2 * (2 * k * fstride));
            }
            tr = ADD(br, cr);
            ti = ADD(bi, ci);
            hr = SUB(ar, tr >> 1);
            hi = SUB(ai, ti >> 1);
            er = msin3(SUB(bi, ci));
            ei = msin3(SUB(br, cr));
            f0[0] = ADD(tr, ar);
            f0[1] = ADD(ti, ai);
            f1[0] = SUB(hr, er);
            f1[1] = ADD(hi, ei);
            f2[0] = ADD(hr, er);
            f2[1] = SUB(hi, ei);
        }
    }
}

/* Radix-4 butterfly, one block of 4m (FUN_0010664c; fs2 = 2 * fstride is its
 * second argument). Fout[0] is divided by 4 with rounding, the twiddled terms
 * by a Q33 product; no k = 0 shortcut. */
static void bfly4(int32_t *F, int m, const int32_t *tw, int fstride) {
    int u;
    for (u = 0; u < m; u++) {
        int32_t *p0 = F + 2 * u, *p1 = p0 + 2 * m, *p2 = p1 + 2 * m, *p3 = p2 + 2 * m;
        const int32_t *w1 = tw + 2 * (u * fstride), *w2 = tw + 2 * (2 * u * fstride),
                      *w3 = tw + 2 * (3 * u * fstride);
        int32_t f0r = ADD(p0[0], 2) >> 2, f0i = ADD(p0[1], 2) >> 2;
        int32_t s0r = (int32_t)ASR(MUL(w1[0], p1[0]) + RND33 - MUL(w1[1], p1[1]), 33);
        int32_t s0i = (int32_t)ASR(MUL(w1[1], p1[0]) + MUL(p1[1], w1[0]) + RND33, 33);
        int32_t s1r = (int32_t)ASR(MUL(w2[0], p2[0]) + RND33 - MUL(w2[1], p2[1]), 33);
        int32_t s1i = (int32_t)ASR(MUL(w2[1], p2[0]) + MUL(p2[1], w2[0]) + RND33, 33);
        int32_t s2r = (int32_t)ASR(MUL(w3[0], p3[0]) + RND33 - MUL(w3[1], p3[1]), 33);
        int32_t s2i = (int32_t)ASR(MUL(w3[1], p3[0]) + MUL(p3[1], w3[0]) + RND33, 33);
        int32_t s5r = SUB(f0r, s1r), s5i = SUB(f0i, s1i);
        int32_t ar = ADD(f0r, s1r), ai = ADD(f0i, s1i);
        int32_t s3r = ADD(s0r, s2r), s3i = ADD(s0i, s2i);
        int32_t s4r = SUB(s0r, s2r), s4i = SUB(s0i, s2i);
        p2[0] = SUB(ar, s3r);
        p2[1] = SUB(ai, s3i);
        p0[0] = ADD(ar, s3r);
        p0[1] = ADD(ai, s3i);
        p1[0] = ADD(s4i, s5r);
        p1[1] = SUB(s5i, s4r);
        p3[0] = SUB(s5r, s4i);
        p3[1] = ADD(s5i, s4r);
    }
}

/* Radix-2 last stage of the 54-point FFT: twiddle (Q31), then halve. */
static void bfly2(int32_t *F, int m, const int32_t *tw, int fstride) {
    int u;
    for (u = 0; u < m; u++) {
        int32_t *a = F + 2 * u, *b = a + 2 * m, tr, ti;
        const int32_t *w = tw + 2 * (u * fstride);
        tr = (int32_t)ASR(MUL(w[0], b[0]) + RND31 - MUL(w[1], b[1]), 31);
        ti = (int32_t)ASR(MUL(w[1], b[0]) + MUL(b[1], w[0]) + RND31, 31);
        b[0] = SUB(ADD(a[0], 1), tr) >> 1;
        b[1] = SUB(ADD(a[1], 1), ti) >> 1;
        a[0] = ADD(ADD(tr, a[0]), 1) >> 1;
        a[1] = ADD(ADD(a[1], 1), ti) >> 1;
    }
}

void ssc_fft(const ssc_fft_state *st, const int32_t *fin, int32_t *fout) {
    const int32_t *tw = st->twiddles;
    int n3 = st->nfft, i;

    /* Bit-reversal fused with the radix-3 split: bitrev[] holds int offsets. */
    for (i = 0; i < n3; i++) {
        int32_t *d = fout + st->bitrev[i];
        d[0] = fin[2 * i];
        d[1] = fin[2 * i + 1];
        d[2] = fin[2 * (i + n3)];
        d[3] = fin[2 * (i + n3) + 1];
        d[4] = fin[2 * (i + 2 * n3)];
        d[5] = fin[2 * (i + 2 * n3) + 1];
    }
    bfly3(fout, 1, n3, tw, 0);
    /* The blob runs the m = 3 stage once more than needed (count + 1 blocks):
     * for 432 points it touches the 9 complex values after fout, for 54 points
     * fout[54..62]. Kept for identical memory. */
    if (st->shift == 0) {
        bfly3(fout, 3, 48 + 1, tw, 48);
        bfly3(fout, 9, 16, tw, 16);
        for (i = 0; i < 4; i++) bfly4(fout + 2 * 108 * i, 27, tw, 4);
        bfly4(fout, 108, tw, 1);
    } else {
        bfly3(fout, 3, 6 + 1, tw, 48);
        bfly3(fout, 9, 2, tw, 16);
        bfly2(fout, 27, tw, 8);
    }
}

/* Rotation by (cos, sin) of pi/4/N, Q31: shift 0 -> N = 1728, shift 3 -> 216. */
#define ROT_COS(shift) ((shift) ? 0x7fffc88cll : 0x7fffff22ll)
#define ROT_SIN(shift) ((shift) ? 0x7725c6ll : 0xee4bbll)

void ssc_mdct_forward(const ssc_mdct_lookup *l, int32_t *in, int32_t *out, int overlap, int shift,
                      int stride) {
    const int32_t *window = ssc_window;
    int N = l->n >> shift, N2 = N >> 1, N4 = N >> 2, i;
    int ov4 = (overlap + 3) >> 2, step = 1 << shift;
    const int32_t *trig = l->trig;
    const int64_t C = ROT_COS(shift), S = ROT_SIN(shift);
    int32_t *f = _pre_shared;               /* N2 values, rotated in place */
    int32_t *f2 = _pre_shared + 864;        /* FFT output (blob: fixed address) */

    /* Window, shuffle, fold (Opus 1.1 order). */
    {
        const int32_t *xp1 = in + (overlap >> 1);
        const int32_t *xp2 = in + N2 - 1 + (overlap >> 1);
        const int32_t *wp1 = window + (overlap >> 1);
        const int32_t *wp2 = window + (overlap >> 1) - 1;
        int32_t *yp = f;
        for (i = 0; i < ov4; i++) {
            *yp++ = (int32_t)ASR(MUL(*wp1, *xp2) + MUL(*wp2, xp1[N2]) + RND31, 31);
            *yp++ = (int32_t)ASR(MUL(*wp1, *xp1) + RND31 - MUL(*wp2, xp2[-N2]), 31);
            xp1 += 2;
            xp2 -= 2;
            wp1 += 2;
            wp2 -= 2;
        }
        wp1 = window;
        wp2 = window + overlap - 1;
        for (; i < N4 - ov4; i++) {
            *yp++ = *xp2;
            *yp++ = *xp1;
            xp1 += 2;
            xp2 -= 2;
        }
        for (; i < N4; i++) {
            *yp++ = (int32_t)ASR(MUL(*wp2, *xp2) + RND31 - MUL(*wp1, xp1[-N2]), 31);
            *yp++ = (int32_t)ASR(MUL(*wp1, xp2[N2]) + MUL(*wp2, *xp1) + RND31, 31);
            xp1 += 2;
            xp2 -= 2;
            wp1 += 2;
            wp2 -= 2;
        }
    }

    /* Pre-rotation. */
    if (N >= 4) {
        const int32_t *t0 = trig, *t1 = trig + (N4 << shift);
        int32_t *yp = f;
        i = 0;
        do {
            int32_t re = yp[0], im = yp[1];
            int64_t yr = -(ASR(((MUL(*t1, im) + MUL(*t0, re)) << 1) + 0x80000000ull, 32));
            int64_t yi = ASR(((MUL(*t1, re) - MUL(*t0, im)) << 1) + 0x80000000ull, 32);
            yp[0] = (int32_t)ASR((u64)yr * (u64)C + (u64)yi * (u64)S + RND31, 31);
            yp[1] = (int32_t)ASR((u64)yi * (u64)C + RND31 - (u64)yr * (u64)S, 31);
            yp += 2;
            t0 += step;
            t1 -= step;
        } while (++i < N4);
    }

    ssc_fft(l->kfft[shift >> 1], f, f2);

    /* Post-rotation. */
    {
        const int32_t *fp = f2, *t0 = trig, *t1 = trig + (N4 << shift);
        int32_t *yp1 = out, *yp2 = out + stride * (N2 - 1);
        i = N4;
        do {
            int64_t yr = ASR(((MUL(*t1, fp[1]) + MUL(*t0, fp[0])) << 1) + 0x80000000ull, 32);
            int64_t yi = ASR(((MUL(fp[0], *t1) - MUL(*t0, fp[1])) << 1) + 0x80000000ull, 32);
            *yp1 = (int32_t)ASR((u64)yr * (u64)C + RND31 - (u64)yi * (u64)S, 31);
            *yp2 = (int32_t)ASR((u64)yi * (u64)C + (u64)yr * (u64)S + RND31, 31);
            fp += 2;
            t0 += step;
            t1 -= step;
            yp1 += 2 * stride;
            yp2 -= 2 * stride;
        } while (--i);
    }
}
