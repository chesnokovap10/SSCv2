/* libssc — internal declarations of the blob-named functions (Samsung signatures). */
#ifndef SSC_INTERNAL_H
#define SSC_INTERNAL_H

#include <stdint.h>

#include "ssc_mode.h"

/* ssc_twin.c */
void SSC_COPY32(int32_t *dst, const int32_t *src, int n);
void SSC_COPY16(int16_t *dst, const int16_t *src, int n);
void SSC_COPY8(uint8_t *dst, const uint8_t *src, int n);
void SSC_CLEAR(void *p, unsigned n);

/* ssc_pitch.c (Opus 1.1 pitch.c / celt_lpc.c, N = 864, C = 2) */
void pitch_downsample(int32_t *x[], int16_t *x_lp, int len);
void pitch_search(const int16_t *x_lp, int16_t *y, int len, int max_pitch, int *pitch);
int16_t remove_doubling(int16_t *x, int maxperiod, int minperiod, int N, int *T0,
                        int prev_period, int16_t prev_gain);

/* ssc_prefilter.c */
void comb_filter(int32_t *y, int32_t *x, int T0, int T1, int N, int16_t g0, int16_t g1,
                 int overlap);

/* ssc_mdct.c (32-bit MDCT/FFT; scratch in _pre_shared like the blob) */
void ssc_fft(const ssc_fft_state *st, const int32_t *fin, int32_t *fout);
void ssc_mdct_forward(const ssc_mdct_lookup *l, int32_t *in, int32_t *out, const int32_t *window,
                      int overlap, int shift, int stride);

/* ssc_headroom.c (freq: 2 x 864 bins, M = 8) */
void normal_headroom(int32_t *freq, int bitrate, int M, const int16_t *eBands);
void uhq_headroom(int32_t *freq, int bitrate, int M, const int16_t *eBands);
void headroom_process(int32_t *freq, int bitrate, int M, const int16_t *eBands, int uhq);

/* ssc_bands.c (C = 2, M = 8) */
struct SscEncoder;
void compute_band_energies(const SscMode *m, const int32_t *X, int32_t *bandE, int end);
void amp2Log2(const SscMode *m, int effEnd, int end, const int32_t *bandE, int16_t *bandLogE,
              int C);
void normalise_bands(const SscMode *m, const int32_t *freq, int16_t *X, const int32_t *bandE,
                     int end);
void compute_band_energies_for_lastband(const SscMode *m, const int32_t *X, int32_t *out, int n,
                                        int uhq, int row);
int patch_transient_decision(const int16_t *newE, const int16_t *oldE, int nb, int end);
int patch_transient_decision_temporal(const SscMode *m, struct SscEncoder *st, const int32_t *in);

/* ssc_tone.c */
int tone_detect(const int32_t *xcorr, int *best_pitch, int32_t maxcorr, int n);
int last_band_info_calc(int thr, int n, const int32_t *e);

#endif
