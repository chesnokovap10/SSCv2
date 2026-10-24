/* libssc — internal declarations of the blob-named functions (Samsung signatures). */
#ifndef SSC_INTERNAL_H
#define SSC_INTERNAL_H

#include <stdint.h>

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

#endif
