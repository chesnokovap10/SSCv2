/* libssc — pitch analysis under the blob's names and signatures.
 *
 * Samsung kept Opus 1.1 pitch.c / celt_lpc.c and specialised them for the SSC
 * frame (N = 864, C = 2): _ssc_autocorr is _celt_autocorr(n = 944, lag 4,
 * no window), the asm kernels ssc_pitch_xcorr_c1/c2 and dual_inner_prod are
 * celt_pitch_xcorr / dual_inner_prod with fixed lengths (sums mod 2^32, so the
 * order of accumulation does not matter). The Opus files are compiled here
 * under opus_* names; the blob-named entry points below fix the parameters.
 */
#undef pitch_downsample  /* ssc_names.h: the wrappers below get the blob names */
#undef pitch_search
#undef remove_doubling
#define pitch_downsample opus_pitch_downsample
#define pitch_search opus_pitch_search
#define remove_doubling opus_remove_doubling
#define _celt_autocorr opus_celt_autocorr
#define _celt_lpc opus_celt_lpc
#include "opus/celt_lpc.c"
int _ssc_autocorr(const opus_val16 *x, opus_val32 *ac);
void ssc_pitch_xcorr_c1(const opus_val16 *x, const opus_val16 *y, opus_val32 *xcorr);
#include "opus/pitch.c"
#undef pitch_downsample
#undef pitch_search
#undef remove_doubling
#undef _celt_autocorr
#undef _celt_lpc
#undef dual_inner_prod  /* pitch.h macro; the blob exports a real function */

#define SSC_PITCH_LEN (864 + 1024)  /* N + COMBFILTER_MAXPERIOD */

extern opus_int32 in_shared[];

/* _celt_autocorr(n = 944, lag 4, no window) with two Samsung changes: ac0 is
 * the plain sum of x^2 >> 9 (no 1 + (n << 7)), and the scaled copy is written
 * to in_shared[] (int16 from its start) - where the caller's x already is, so
 * the input gets scaled in place. */
int _ssc_autocorr(const opus_val16 *x, opus_val32 *ac) {
    enum { n = SSC_PITCH_LEN >> 1, lag = 4, fastN = n - lag };
    opus_val16 *xx = (opus_val16 *)in_shared;
    const opus_val16 *xp = x;
    opus_uint32 ac0 = 0;
    int i, k, shift = 0;
    for (i = 0; i < n; i++) ac0 += (opus_uint32)(x[i] * x[i]) >> 9;
    if (ac0 >= 0x400000) {
        int s = (11 - __builtin_clz(ac0)) >> 1, round = (1 << s) >> 1;
        for (i = 0; i < n; i++) xx[i] = (opus_val16)((round + xp[i]) >> s);
        xp = xx;
        shift = 2 * s;
    }
    ssc_pitch_xcorr_c1(xp, xp, ac);
    for (k = 0; k <= lag; k++) {
        opus_val32 d = 0;
        for (i = k + fastN; i < n; i++) d += xp[i] * xp[i - k];
        ac[k] += d;
    }
    if (shift <= 0) ac[0] += 1;
    if (ac[0] < 268435456) {
        int s2 = __builtin_clz((opus_uint32)ac[0]) - 3;
        for (i = 0; i <= lag; i++) ac[i] = (opus_val32)((opus_uint32)ac[i] << s2);
        shift -= s2;
    } else if (ac[0] >= 536870912) {
        int s2 = ac[0] >= 1073741824 ? 2 : 1;
        ac[0] = (opus_val32)((opus_uint32)ac[0] >> s2);
        for (i = 1; i <= lag; i++) ac[i] >>= s2;
        shift += s2;
    }
    return shift;
}

void _ssc_lpc(opus_val16 *lpc, const opus_val32 *ac) { opus_celt_lpc(lpc, ac, 4); }

void ssc_pitch_xcorr_c1(const opus_val16 *x, const opus_val16 *y, opus_val32 *xcorr) {
    celt_pitch_xcorr(x, y, xcorr, (SSC_PITCH_LEN >> 1) - 4, 5, 0);
}

opus_val32 ssc_pitch_xcorr_c2(const opus_val16 *x, const opus_val16 *y, opus_val32 *xcorr) {
    return celt_pitch_xcorr(x, y, xcorr, 864 >> 2, (1024 - 3 * 15) >> 2, 0);
}

void dual_inner_prod(const opus_val16 *x, const opus_val16 *y01, const opus_val16 *y02,
                     int unused, opus_val32 *xy1, opus_val32 *xy2) {
    (void)unused;
    dual_inner_prod_c(x, y01, y02, 864 >> 1, xy1, xy2);
}

/* Channel pointers instead of Opus' array. The blob takes the max |x| over
 * x0[0 .. 2*len), which is both channels because ssc_encode always passes
 * x1 = x0 + len (the two halves of _pre_shared). */
void ssc_pitch_downsample(celt_sig *x0, celt_sig *x1, opus_val16 *x_lp, int len) {
    celt_sig *x[2] = {x0, x1};
    opus_pitch_downsample(x, x_lp, len, 2, 0);
}

void ssc_pitch_search(const opus_val16 *x_lp, opus_val16 *y, int len, int max_pitch, int *pitch) {
    opus_pitch_search(x_lp, y, len, max_pitch, pitch, 0);
}

opus_val16 ssc_remove_doubling(opus_val16 *x, int maxperiod, int minperiod, int N, int *T0,
                           int prev_period, opus_val16 prev_gain) {
    return opus_remove_doubling(x, maxperiod, minperiod, N, T0, prev_period, prev_gain, 0);
}
