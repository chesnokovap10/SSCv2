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
void haar1(int16_t *X, int N0, int stride);

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

/* ssc_quant.c (start 0, C = 2, LM = 3) */
struct ec_ctx;
void quant_coarse_energy(const SscMode *m, int nbBands, int end, const int16_t *eBands,
                         int16_t *oldEBands, uint32_t budget, int16_t *error, struct ec_ctx *enc,
                         int nbAvailableBytes, int force_intra, int32_t *delayedIntra);
void quant_fine_energy(const SscMode *m, int end, int16_t *oldEBands, int16_t *error,
                       const int *fine_quant, struct ec_ctx *enc, int C);
int spreading_decision(const SscMode *m, const int16_t *X, int *average, int last_decision,
                       int *hf_average, int *tapset_decision, int update_hf, int end);
int hysteresis_decision(int16_t val, const int16_t *thresholds, const int16_t *hysteresis, int N,
                        int prev);
void init_caps(const SscMode *m, int *cap, int LM, int C);
int compute_allocation(const SscMode *m, int end, const int *offsets, const int *cap,
                       int alloc_trim, int *intensity, int *dual_stereo, int32_t total,
                       int32_t *balance, int *pulses, int *ebits, int *fine_priority,
                       struct ec_ctx *ec, int prev, int signalBandwidth, int hi_rate);

/* ssc_pvq.c */
int stereo_itheta(const int16_t *X, const int16_t *Y, int stereo, int N);
unsigned alg_quant(int16_t *X, int N, int K, int spread, int B, struct ec_ctx *enc);
void quant_all_bands(const SscMode *m, int end, int16_t *X_, unsigned char *collapse_masks,
                     const int32_t *bandE, const int *pulses, int shortBlocks, int spread,
                     int dual_stereo, int intensity, const int *tf_res, int32_t total_bits,
                     int32_t balance, struct ec_ctx *ec, int codedBands, uint32_t *seed);
void quant_energy_finalise(const SscMode *m, int end, int16_t *oldEBands, const int16_t *error,
                           const int *fine_quant, const int *fine_priority, int bits_left,
                           struct ec_ctx *enc, int C);

/* ssc_tone.c */
int tone_detect(const int32_t *xcorr, int *best_pitch, int32_t maxcorr, int n);
int last_band_info_calc(int thr, int n, const int32_t *e);

#endif
