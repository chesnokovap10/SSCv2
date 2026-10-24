/* libssc — Samsung input processing before CELT: Biquad_Narrow, powercalc,
 * CalculateLimitGain and the SSC_DRC peak limiter (SoundBooster DRC in older builds).
 *
 * Twin of the blob: same names, same globals (the blob keeps the DRC state in
 * process globals, so like the blob this is one stream per process for now;
 * moving it into SscEncoder is a phase-5 item).
 */
#ifndef SSC_DRC_H
#define SSC_DRC_H

#include <stdint.h>

/* drc_struct @ blob 0x20500 (24 bytes). Field names are ours. */
typedef struct {
    int32_t limit;      /* +0x00  threshold, set every frame by set_DRC_limit_gain */
    int32_t c_attack;   /* +0x04  Q22 smoothing when the gain goes down (0) */
    int32_t c_release;  /* +0x08  Q22 smoothing when the gain goes up */
    int32_t g_smooth;   /* +0x0c  smoothed gain, Q22 */
    int32_t g_start;    /* +0x10  gain at the start of the next block, Q22 */
    int32_t g_prev;     /* +0x14  smoothed gain of the previous block */
} SscDrcState;

extern SscDrcState drc_struct;
extern int32_t DRC_ChNum;
extern int32_t Soundbooster_DRC_Fs;
extern int32_t DRC_ModeFlag;
extern int32_t count_for_debug;
extern int32_t _pcmpower[864 * 2];   /* Biquad output (blob global) */
extern int32_t previous_uhq_index;

/* 2nd-order IIR over interleaved stereo int32. state: 10 x int64
 * (per channel: x1, x2, y1<<3, y2<<3, accumulator remainder). Runs at least once. */
void Biquad_Narrow_int2int_stereo(int32_t *out, const int32_t *in, const int32_t *coef,
                                  int64_t *state, int n);
/* sum over n stereo frames of ((x*x)>>16)>>1, result >> 9 */
void powercalc(const int32_t *x, int n, int32_t *out);
int CalculateLimitGain(int p_filtered, int p_rest, int bitrate, int fs);
void set_DRC_limit_gain(int32_t limit);
void SSC_DRC_Init(int fs, int channels);
void SSC_DRC_SetPar(int mode, int32_t limit);
/* In place on n interleaved stereo frames. */
void SSC_DRC_Exe(int32_t *x, int n);

#endif
