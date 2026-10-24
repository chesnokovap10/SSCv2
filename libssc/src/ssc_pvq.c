/* libssc — PVQ band quantisation (encoder only, no resynthesis).
 *
 * Opus 1.1.5 bands.c / vq.c (quant_all_bands, quant_band, quant_partition,
 * compute_theta, alg_quant) with LM = 3, C = 2, start 0 and without the
 * folding/resynthesis paths the encoder never needs. Samsung changes are
 * marked "Samsung:"; the main ones are truncating (not rounding) products in
 * the rotations and splits, an exact 64-bit division in itheta and the spread
 * gain, a finer PVQ search metric, and scratch arrays inside in_shared.
 */
#include <stdlib.h>
#include <string.h>

#include "opus/arch.h"
#include "opus/cwrs.h"
#include "opus/entcode.h"
#include "opus/entenc.h"
#include "opus/mathops.h"
#include "ssc_encoder.h"
#include "ssc_internal.h"

#define LM3 3
#define BITRES 3
#define QTHETA_OFFSET 4

typedef struct {     /* Opus 1.1.5 band_ctx layout (blob: same offsets) */
    int encode;
    const SscMode *m;
    int i;
    int intensity;
    int spread;
    int tf_change;
    ec_enc *ec;
    int32_t remaining_bits;
    const int32_t *bandE;
    uint32_t seed;
} band_ctx;

static const int16_t exp2_table8[8] = {16384, 17866, 19483, 21247, 23170, 25267, 27554, 30048};
static const unsigned char bit_interleave_table[16] = {0, 1, 1, 1, 2, 3, 3, 3,
                                                       2, 3, 3, 3, 2, 3, 3, 3};
static const int ordery_table[] = {1, 0, 3, 0, 2, 1, 7, 0, 4, 3, 6, 1, 5, 2,
                                   15, 0, 8, 7, 12, 3, 11, 4, 14, 1, 9, 6, 13, 2, 10, 5};

/* ------------------------------------------------------------ helpers */

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

/* Samsung atan2p: exact y/x via ssc_rcp and a 64-bit product; first polynomial
 * step is (x*M4 + 2^15) >> 16. */
static int16_t atan01(int16_t x) {
    int32_t t = (int32_t)((((uint32_t)(x * 9872) + 0x8000u) & 0xffff0000u) + 0xd1590000u) >> 16;
    t = (int32_t)((((uint32_t)(t * x * 2) + 0x8000u) & 0xffff0000u) - 0x150000u) >> 16;
    t = (int32_t)((((uint32_t)(t * x * 2) + 0x8000u) & 0xffff0000u) + 0x7fff0000u) >> 16;
    return (int16_t)t;  /* caller does the last * x step */
}

static int32_t div_q15(int16_t num, int16_t den) {
    int32_t r = celt_rcp(den);
    int32_t q = (int32_t)(((int64_t)r * (int64_t)((int32_t)((uint32_t)(uint16_t)num << 16) >> 1)) >> 31);
    return q > 0x7ffe ? 0x7fff : q;
}

static int compute_itheta(const int16_t *X, const int16_t *Y, int stereo, int N) {
    int32_t Emid = 1, Eside = 1;
    int16_t mid, side, a, r;
    int i;
    if (stereo) {
        for (i = 0; i < N; i++) {
            int16_t m = (int16_t)((X[i] >> 1) + (Y[i] >> 1)), s = (int16_t)((X[i] >> 1) - (Y[i] >> 1));
            Emid += m * m;
            Eside += s * s;
        }
    } else {
        for (i = 0; i < N; i++) {
            Emid += X[i] * X[i];
            Eside += Y[i] * Y[i];
        }
    }
    mid = (int16_t)celt_sqrt(Emid);
    side = (int16_t)celt_sqrt(Eside);
    if (side < mid) {
        int16_t x = (int16_t)div_q15(side, mid);
        a = atan01(x);
        r = (int16_t)((a * x + 0x4000) >> 15 >> 1);
    } else {
        int16_t x = (int16_t)div_q15(mid, side);
        a = atan01(x);
        r = (int16_t)(0x6488 - (int16_t)(((a * x + 0x4000) * 2) >> 17));
    }
    return (r * 0x517d) >> 15;
}

/* Exported mid/side variant (the mono split goes through compute_itheta). */
int stereo_itheta(const int16_t *X, const int16_t *Y, int N) { return compute_itheta(X, Y, 1, N); }

/* Samsung intensity_stereo: each product shifted on its own. */
static void intensity_stereo(const SscMode *m, int16_t *X, const int16_t *Y, const int32_t *bandE,
                             int i, int N) {
    int32_t l = bandE[i], r = bandE[i + m->nbEBands], mx = IMAX(l, r);
    int shift = mx < 1 ? 0 - 13 : (int16_t)(EC_ILOG(mx) - 1) - 13;
    int16_t left, right, a1 = 0, a2 = 0, norm;
    int j;
    left = (int16_t)(shift > 0 ? l >> shift : (int32_t)((uint32_t)l << -shift));
    right = (int16_t)(shift > 0 ? r >> shift : (int32_t)((uint32_t)r << -shift));
    norm = (int16_t)(celt_sqrt(right * right + left * left + 1) + 1);
    if (norm) {
        a2 = (int16_t)(((int32_t)((uint32_t)(int32_t)right << 16) >> 2) / norm);
        a1 = (int16_t)(((int32_t)((uint32_t)(int32_t)left << 16) >> 2) / norm);
    }
    for (j = 0; j < N; j++)
        X[j] = (int16_t)((int16_t)((uint32_t)(a2 * Y[j]) >> 14) +
                         (int16_t)((uint32_t)(a1 * X[j]) >> 14));
}

/* Samsung stereo_split: products truncated before the sum (like haar1). */
static void stereo_split(int16_t *X, int16_t *Y, int N) {
    int j;
    for (j = 0; j < N; j++) {
        int16_t l = (int16_t)((uint32_t)(X[j] * 46340) >> 16);
        int16_t r = (int16_t)((uint32_t)(Y[j] * 46340) >> 16);
        X[j] = (int16_t)(r + l);
        Y[j] = (int16_t)(r - l);
    }
}

static void deinterleave_hadamard(int16_t *X, int N0, int stride, int hadamard) {
    int16_t tmp[176];
    int i, j, N = N0 * stride;
    if (hadamard) {
        const int *ordery = ordery_table + stride - 2;
        for (i = 0; i < stride; i++)
            for (j = 0; j < N0; j++) tmp[ordery[i] * N0 + j] = X[j * stride + i];
    } else {
        for (i = 0; i < stride; i++)
            for (j = 0; j < N0; j++) tmp[i * N0 + j] = X[j * stride + i];
    }
    memcpy(X, tmp, N * sizeof(*X));
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

/* ------------------------------------------------------------ alg_quant */

/* Samsung exp_rotation1: no rounding before >> 15. */
static void exp_rotation1(int16_t *X, int len, int stride, int16_t c, int16_t s) {
    int i;
    int16_t ms = (int16_t)-s, *Xptr = X;
    for (i = 0; i < len - stride; i++) {
        int16_t x1 = Xptr[0], x2 = Xptr[stride];
        Xptr[stride] = (int16_t)((uint32_t)(c * x2 + s * x1) >> 15);
        *Xptr++ = (int16_t)((uint32_t)(c * x1 + ms * x2) >> 15);
    }
    Xptr = &X[len - 2 * stride - 1];
    for (i = len - 2 * stride - 1; i >= 0; i--) {
        int16_t x1 = Xptr[0], x2 = Xptr[stride];
        Xptr[stride] = (int16_t)((uint32_t)(c * x2 + s * x1) >> 15);
        *Xptr-- = (int16_t)((uint32_t)(c * x1 + ms * x2) >> 15);
    }
}

static void exp_rotation(int16_t *X, int len, int stride, int K, int spread) {
    static const int SPREAD_FACTOR[3] = {15, 10, 5};
    int i, stride2 = 0;
    int16_t c, s, gain, theta;
    if (2 * K >= len || spread == 0) return;
    /* Samsung: exact Q31 product of 32767*len and rcp(len + factor*K) */
    gain = (int16_t)((int64_t)celt_rcp(len + SPREAD_FACTOR[spread - 1] * K) *
                         (int64_t)((int16_t)len * 32767) >> 31);
    theta = (int16_t)((uint32_t)(gain * gain) >> 16);
    c = celt_cos_norm(EXTEND32(theta));
    s = celt_cos_norm(EXTEND32(theta ^ 0x7fff));
    if (len >= 8 * stride) {
        stride2 = 1;
        while ((stride2 * stride2 + stride2) * stride + (stride >> 2) < len) stride2++;
    }
    len /= stride;
    for (i = 0; i < stride; i++) {
        exp_rotation1(X + i * len, len, 1, c, (int16_t)-s);
        if (stride2) exp_rotation1(X + i * len, len, stride2, s, (int16_t)-c);
    }
}

/* Scratch in in_shared like the blob: iy (int32) at byte 0xd80, y (int16) at
 * 0xfc0, signx (int16) at 0x1200. */
#define AQ_IY ((int32_t *)((char *)in_shared + 0xd80))
#define AQ_Y ((int16_t *)((char *)in_shared + 0xfc0))
#define AQ_SIGNX ((int16_t *)((char *)in_shared + 0x1200))

unsigned alg_quant(int16_t *X, int N, int K, int spread, int B, ec_enc *enc) {
    int32_t *iy = AQ_IY;
    int16_t *y = AQ_Y, *signx = AQ_SIGNX, yy = 0;
    int32_t xy = 0, sum = 0;
    int i, j, pulsesLeft = K;
    unsigned collapse_mask;

    exp_rotation(X, N, B, K, spread);
    for (j = N - 1; j >= 0; j--) {
        if (X[j] < 1) {
            signx[j] = -1;
            X[j] = (int16_t)-X[j];
        } else {
            signx[j] = 1;
        }
        y[j] = 0;
        iy[j] = 0;
    }
    if (K > (N >> 1)) {
        int32_t rcp;
        for (j = N - 1; j >= 0; j--) sum += X[j];
        if (sum <= K) {
            X[0] = 16384;
            memset(X + 1, 0, (N - 1) * sizeof(*X));
            sum = 16384;
        }
        rcp = (int32_t)((uint32_t)celt_rcp(sum) * (uint32_t)(int16_t)(K - 1)) >> 16;
        for (j = N - 1; j >= 0; j--) {
            int32_t p = rcp * X[j];
            iy[j] = p >> 15;
            yy = (int16_t)((p >> 15) * (p >> 15) + yy);
            xy += (p >> 15) * X[j];
            pulsesLeft -= iy[j];
            y[j] = (int16_t)(iy[j] << 1);
        }
    }
    if (pulsesLeft > N + 3) {
        iy[0] += pulsesLeft;
        pulsesLeft = 0;
    }
    for (i = 1; i <= pulsesLeft; i++) {
        int best_id = 0, rshift = EC_ILOG(i + K - pulsesLeft);
        int32_t best_num = -32767;
        int16_t best_den = 0;
        for (j = 0; j < N; j++) {
            int16_t Rxy = (int16_t)((xy + X[j]) >> rshift);
            int16_t Ryy = (int16_t)(y[j] + yy + 1);
            int32_t num = (int32_t)((uint32_t)(Rxy * Rxy) >> 7);  /* Samsung: >> 7 */
            if ((int64_t)(uint32_t)num * best_den > (int64_t)Ryy * best_num) {
                best_den = Ryy;
                best_num = num;
                best_id = j;
            }
        }
        xy += X[best_id];
        yy = (int16_t)(y[best_id] + yy + 1);
        y[best_id] = (int16_t)(y[best_id] + 2);
        iy[best_id]++;
    }
    for (j = N - 1; j >= 0; j--) {
        X[j] = (int16_t)(X[j] * signx[j]);
        iy[j] *= signx[j];
    }
    encode_pulses(iy, N, K, enc);
    if (B <= 1) return 1;
    collapse_mask = 0;
    for (i = 0; i < B; i++) {
        int N0 = N / B;
        for (j = 0; j < N0; j++)
            if (iy[i * N0 + j]) {
                collapse_mask |= 1u << i;
                break;
            }
    }
    return collapse_mask;
}

/* ------------------------------------------------------------ bands */

typedef struct {
    int imid, iside, delta, itheta, qalloc;
} split_ctx;

static void theta_to_split(split_ctx *s, int itheta, int N, int B, int *fill) {
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

/* Mono time/frequency split (Opus compute_theta with stereo = 0). */
static void compute_theta_mono(band_ctx *ctx, split_ctx *s, int16_t *X, int16_t *Y, int N, int *b,
                               int B, int B0, int LM, int *fill) {
    int pulse_cap = ctx->m->logN[ctx->i] + LM * (1 << BITRES);
    int offset = (pulse_cap >> 1) - QTHETA_OFFSET;
    int qn = compute_qn(N, *b, offset, pulse_cap), itheta = compute_itheta(X, Y, 0, N);
    int32_t tell = ec_tell_frac(ctx->ec);
    if (qn != 1) {
        itheta = (itheta * qn + 8192) >> 14;
        if (B0 > 1) {
            ec_enc_uint(ctx->ec, itheta, qn + 1);
        } else {
            int ft = ((qn >> 1) + 1) * ((qn >> 1) + 1);
            int fs = itheta <= (qn >> 1) ? itheta + 1 : qn + 1 - itheta;
            int fl = itheta <= (qn >> 1) ? itheta * (itheta + 1) >> 1
                                         : ft - ((qn + 1 - itheta) * (qn + 2 - itheta) >> 1);
            ec_encode(ctx->ec, fl, fl + fs, ft);
        }
        itheta = (itheta * 16384) / qn;
    }
    s->qalloc = ec_tell_frac(ctx->ec) - tell;
    *b -= s->qalloc;
    theta_to_split(s, itheta, N, B, fill);
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

static unsigned quant_partition(band_ctx *ctx, int16_t *X, int N, int b, int B, int LM,
                                int16_t gain, int fill) {
    const SscMode *m = ctx->m;
    const unsigned char *cache = m->cache.bits + m->cache.index[(LM + 1) * m->nbEBands + ctx->i];
    unsigned cm = 0;
    int B0 = B;
    if (LM != -1 && b > cache[cache[0]] + 12 && N > 2) {
        int mbits, sbits, delta, itheta;
        int32_t rebalance;
        split_ctx s;
        int16_t *Y;
        N >>= 1;
        Y = X + N;
        LM -= 1;
        if (B == 1) fill = (fill & 1) | (fill << 1);
        B = (B + 1) >> 1;
        compute_theta_mono(ctx, &s, X, Y, N, &b, B, B0, LM, &fill);
        delta = s.delta;
        itheta = s.itheta;
        if (B0 > 1 && (itheta & 0x3fff)) {
            if (itheta > 8192) delta -= delta >> (4 - LM);
            else delta = IMIN(0, delta + (N << BITRES >> (5 - LM)));
        }
        mbits = IMAX(0, IMIN(b, (b - delta) / 2));
        sbits = b - mbits;
        ctx->remaining_bits -= s.qalloc;
        rebalance = ctx->remaining_bits;
        if (mbits >= sbits) {
            cm = quant_partition(ctx, X, N, mbits, B, LM, (int16_t)MULT16_16_P15(gain, s.imid), fill);
            rebalance = mbits - (rebalance - ctx->remaining_bits);
            if (rebalance > 3 << BITRES && itheta != 0) sbits += rebalance - (3 << BITRES);
            cm |= quant_partition(ctx, Y, N, sbits, B, LM, (int16_t)MULT16_16_P15(gain, s.iside),
                                  fill >> B) << (B0 >> 1);
        } else {
            cm = quant_partition(ctx, Y, N, sbits, B, LM, (int16_t)MULT16_16_P15(gain, s.iside),
                                 fill >> B) << (B0 >> 1);
            rebalance = sbits - (rebalance - ctx->remaining_bits);
            if (rebalance > 3 << BITRES && itheta != 16384) mbits += rebalance - (3 << BITRES);
            cm |= quant_partition(ctx, X, N, mbits, B, LM, (int16_t)MULT16_16_P15(gain, s.imid), fill);
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
            cm = alg_quant(X, N, K, ctx->spread, B, ctx->ec);
        }
    }
    return cm;
}

/* Opus quant_band without lowband/resynthesis; Samsung haar1. */
static unsigned quant_band(band_ctx *ctx, int16_t *X, int N, int b, int B, int16_t gain, int fill) {
    int N_B = N / B, B0, k, recombine = 0, tf_change = ctx->tf_change, longBlocks = B == 1;
    if (tf_change > 0) recombine = tf_change;
    for (k = 0; k < recombine; k++) {
        haar1(X, N >> k, 1 << k);
        fill = bit_interleave_table[fill & 0xF] | bit_interleave_table[fill >> 4] << 2;
    }
    B >>= recombine;
    N_B <<= recombine;
    while ((N_B & 1) == 0 && tf_change < 0) {
        haar1(X, N_B, B);
        fill |= fill << B;
        B <<= 1;
        N_B >>= 1;
        tf_change++;
    }
    B0 = B;
    if (B0 > 1) deinterleave_hadamard(X, N_B >> recombine, B0 << recombine, longBlocks);
    return quant_partition(ctx, X, N, b, B, LM3, gain, fill);
}

/* Samsung quant_all_bands: per band, the stereo split of Opus
 * quant_band_stereo (N > 2) inlined, then quant_band on mid and side. */
void quant_all_bands(const SscMode *m, int end, int16_t *X_, unsigned char *collapse_masks,
                     const int32_t *bandE, const int *pulses, int shortBlocks, int spread,
                     int dual_stereo, int intensity, const int *tf_res, int32_t total_bits,
                     int32_t balance, ec_enc *ec, int codedBands, uint32_t *seed) {
    const int16_t *eBands = m->eBands;
    int B = shortBlocks ? 8 : 1, i, fill = (1 << B) - 1;
    band_ctx ctx;
    ctx.encode = 1;
    ctx.m = m;
    ctx.intensity = intensity;
    ctx.spread = spread;
    ctx.ec = ec;
    ctx.bandE = bandE;
    ctx.seed = *seed;
    for (i = 0; i < end; i++) {
        int16_t *X = X_ + 8 * eBands[i], *Y = X + 864;
        int N = 8 * (eBands[i + 1] - eBands[i]), b = 0;
        int32_t tell = ec_tell_frac(ec), remaining_bits;
        unsigned x_cm, y_cm;
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
            x_cm = quant_band(&ctx, X, N, b / 2, B, 32767, fill);
            y_cm = quant_band(&ctx, Y, N, b / 2, B, 32767, fill);
        } else {
            /* compute_theta (stereo) */
            int pulse_cap = m->logN[i] + LM3 * (1 << BITRES), offset = (pulse_cap >> 1) - QTHETA_OFFSET;
            int qn = compute_qn(N, b, offset, pulse_cap), itheta = compute_itheta(X, Y, 1, N);
            int32_t t0 = ec_tell_frac(ec), rebalance;
            int mbits, sbits, sfill = fill;
            split_ctx s;
            unsigned cm;
            if (i >= intensity) qn = 1;
            if (qn != 1) {
                int x0 = qn / 2, ft = 3 * (x0 + 1) + x0, x;
                itheta = (itheta * qn + 8192) >> 14;
                x = itheta;
                ec_encode(ec, x <= x0 ? 3 * x : (x - 1 - x0) + (x0 + 1) * 3,
                          x <= x0 ? 3 * (x + 1) : (x - x0) + (x0 + 1) * 3, ft);
                itheta = (itheta * 16384) / qn;
                if (itheta == 0)
                    intensity_stereo(m, X, Y, bandE, i, N);
                else
                    stereo_split(X, Y, N);
            } else {
                int inv = itheta > 8192, j;
                if (inv)
                    for (j = 0; j < N; j++) Y[j] = (int16_t)-Y[j];
                intensity_stereo(m, X, Y, bandE, i, N);
                if (b > 2 << BITRES && ctx.remaining_bits > 2 << BITRES) ec_enc_bit_logp(ec, inv, 2);
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
                cm = quant_band(&ctx, X, N, mbits, B, 32767, sfill);
                rebalance = mbits - (rebalance - ctx.remaining_bits);
                if (rebalance > 3 << BITRES && itheta != 0) sbits += rebalance - (3 << BITRES);
                cm |= quant_band(&ctx, Y, N, sbits, B, (int16_t)s.iside, sfill >> B);
            } else {
                cm = quant_band(&ctx, Y, N, sbits, B, (int16_t)s.iside, sfill >> B);
                rebalance = sbits - (rebalance - ctx.remaining_bits);
                if (rebalance > 3 << BITRES && itheta != 16384) mbits += rebalance - (3 << BITRES);
                cm |= quant_band(&ctx, X, N, mbits, B, 32767, sfill);
            }
            x_cm = y_cm = cm;
        }
        collapse_masks[2 * i] = (unsigned char)x_cm;
        collapse_masks[2 * i + 1] = (unsigned char)y_cm;
        balance += pulses[i] + tell;
    }
    *seed = ctx.seed;
}

/* Opus quant_energy_finalise, start 0. */
void quant_energy_finalise(const SscMode *m, int end, int16_t *oldEBands, const int16_t *error,
                           const int32_t *fine_quant, const int32_t *fine_priority, int bits_left,
                           ec_enc *enc) {
    int i, prio, c, C = 2;
    for (prio = 0; prio < 2; prio++)
        for (i = 0; i < end && bits_left >= C; i++) {
            if (fine_quant[i] >= 8 || fine_priority[i] != prio) continue;
            c = 0;
            do {
                int q2 = error[i + c * m->nbEBands] < 0 ? 0 : 1;
                ec_enc_bits(enc, q2, 1);
                oldEBands[i + c * m->nbEBands] =
                    (int16_t)(oldEBands[i + c * m->nbEBands] + ((q2 * 1024 - 512) >> (fine_quant[i] + 1)));
                bits_left--;
            } while (++c < C);
        }
}
