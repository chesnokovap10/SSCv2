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
void pitch_downsample(int32_t *x0, int32_t *x1, int16_t *x_lp, int len);
void pitch_search(const int16_t *x_lp, int16_t *y, int len, int max_pitch, int *pitch);
int16_t remove_doubling(int16_t *x, int maxperiod, int minperiod, int N, int *T0,
                        int prev_period, int16_t prev_gain);

/* ssc_prefilter.c */
void comb_filter(int32_t *y, int32_t *x, int T0, int T1, int N, int16_t g0, int16_t g1,
                 int overlap);

/* ssc_mdct.c (32-bit MDCT/FFT; scratch in _pre_shared like the blob) */
void ssc_fft(const ssc_fft_state *st, const int32_t *fin, int32_t *fout);
void ssc_mdct_forward(const ssc_mdct_lookup *l, int32_t *in, int32_t *out, int overlap, int shift,
                      int stride);

/* ssc_headroom.c (freq: 2 x 864 bins, M = 8) */
void normal_headroom(int32_t *freq, int bitrate, int M, const int16_t *eBands, int N);
void uhq_headroom(int32_t *freq, int bitrate, int M, const int16_t *eBands);
void headroom_process(int32_t *freq, int bitrate, int M, const int16_t *eBands, int N, int uhq);

/* ssc_bands.c (C = 2, M = 8) */
struct SscEncoder;
void compute_band_energies(const SscMode *m, const int32_t *X, int32_t *bandE, int end);
void amp2Log2(const SscMode *m, int end, const int32_t *bandE, int16_t *bandLogE);
void normalise_bands(const SscMode *m, const int32_t *freq, int16_t *X, const int32_t *bandE,
                     int end);
void compute_band_energies_for_lastband(const SscMode *m, const int32_t *X, int32_t *out, int n,
                                        int uhq, int row);
int patch_transient_decision(const int16_t *newE, const int16_t *oldE, int nb, int end);

/* ssc_quant.c (start 0, C = 2, LM = 3) */
struct ec_ctx;

/* Bit allocation in and out of ssc_compute_allocation: one struct on the blob's
 * stack (ssc_encode @ sp+0x2b0); quant_fine_energy / quant_energy_finalise and
 * ssc_quant_all_bands get pointers into it. Field names are ours. */
typedef struct {
    int32_t total;              /* 0x000 in: bits for the bands (1/8 bit) */
    int32_t fine_quant[22];     /* 0x004 out (Opus ebits) */
    int32_t pulses[22];         /* 0x05c out (Opus bits) */
    int32_t f0b4;               /* 0x0b4 not understood (0) */
    const int32_t *caps;        /* 0x0b8 in: mode->cache.caps */
    int32_t offsets[22];        /* 0x0c0 in: dynalloc boosts */
    int32_t fine_priority[22];  /* 0x118 out */
    int32_t alloc_trim;         /* 0x170 in */
    int32_t dual_stereo;        /* 0x174 in/out */
    int32_t balance;            /* 0x178 out */
    int32_t f17c;               /* 0x17c not understood (0) */
    int32_t table2;             /* 0x180 in: bitrate > 192000, use mode->allocVectors2 */
} SscAlloc;
void quant_coarse_energy(const SscMode *m, int nbBands, int end, const int16_t *eBands,
                         int16_t *oldEBands, uint32_t budget, int16_t *error, struct ec_ctx *enc,
                         int nbAvailableBytes, int force_intra, int32_t *delayedIntra);
void quant_fine_energy(const SscMode *m, int end, int16_t *oldEBands, int16_t *error,
                       const int32_t *fine_quant, struct ec_ctx *enc);
int spreading_decision(struct SscEncoder *st, const int16_t *X, int update_hf, int end);
int hysteresis_decision(int16_t val, const int16_t *thresholds, const int16_t *hysteresis, int N,
                        int prev);
void init_caps(const SscMode *m, int *cap, int LM, int C);
/* st: mode, intensity (in/out), lastCodedBands (prev). Returns codedBands. */
int compute_allocation(struct SscEncoder *st, SscAlloc *a, struct ec_ctx *ec, int end,
                       int signalBandwidth);

/* ssc_pvq.c */
int stereo_itheta(const int16_t *X, const int16_t *Y, int N);  /* mid/side only */
unsigned alg_quant(int16_t *X, int N, int K, int spread, int B, struct ec_ctx *enc);
void quant_all_bands(const SscMode *m, int end, int16_t *X_, unsigned char *collapse_masks,
                     const int32_t *bandE, const int *pulses, int shortBlocks, int spread,
                     int dual_stereo, int intensity, const int *tf_res, int32_t total_bits,
                     int32_t balance, struct ec_ctx *ec, int codedBands, uint32_t *seed);
void quant_energy_finalise(const SscMode *m, int end, int16_t *oldEBands, const int16_t *error,
                           const int32_t *fine_quant, const int32_t *fine_priority, int bits_left,
                           struct ec_ctx *enc);

/* ssc_tone.c */
int tone_detect(const int32_t *xcorr, int *best_pitch, int32_t maxcorr, int n);
int last_band_info_calc(int thr, int n, const int32_t *e);

#endif
