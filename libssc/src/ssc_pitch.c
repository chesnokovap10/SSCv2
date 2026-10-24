/* libssc — pitch analysis under the blob's names and signatures.
 *
 * Samsung kept Opus 1.1 pitch.c / celt_lpc.c and specialised them for the SSC
 * frame (N = 864, C = 2): _ssc_autocorr is _celt_autocorr(n = 944, lag 4,
 * no window), the asm kernels ssc_pitch_xcorr_c1/c2 and dual_inner_prod are
 * celt_pitch_xcorr / dual_inner_prod with fixed lengths (sums mod 2^32, so the
 * order of accumulation does not matter). The Opus files are compiled here
 * under opus_* names; the blob-named entry points below fix the parameters.
 */
#define pitch_downsample opus_pitch_downsample
#define pitch_search opus_pitch_search
#define remove_doubling opus_remove_doubling
#define _celt_autocorr opus_celt_autocorr
#define _celt_lpc opus_celt_lpc
#include "opus/celt_lpc.c"
#include "opus/pitch.c"
#undef pitch_downsample
#undef pitch_search
#undef remove_doubling
#undef _celt_autocorr
#undef _celt_lpc
#undef dual_inner_prod  /* pitch.h macro; the blob exports a real function */

#define SSC_PITCH_LEN (864 + 1024)  /* N + COMBFILTER_MAXPERIOD */

int _ssc_autocorr(const opus_val16 *x, opus_val32 *ac) {
    return opus_celt_autocorr(x, ac, NULL, 0, 4, SSC_PITCH_LEN >> 1, 0);
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

void pitch_downsample(celt_sig *x[], opus_val16 *x_lp, int len) {
    opus_pitch_downsample(x, x_lp, len, 2, 0);
}

void pitch_search(const opus_val16 *x_lp, opus_val16 *y, int len, int max_pitch, int *pitch) {
    opus_pitch_search(x_lp, y, len, max_pitch, pitch, 0);
}

opus_val16 remove_doubling(opus_val16 *x, int maxperiod, int minperiod, int N, int *T0,
                           int prev_period, opus_val16 prev_gain) {
    return opus_remove_doubling(x, maxperiod, minperiod, N, T0, prev_period, prev_gain, 0);
}
