/* libssc — encoder state, ABI twin of the blob's CELT-derived encoder struct.
 *
 * Header is 0xe0 bytes, then per-channel arrays laid out like Opus 1.1
 * celt_encoder.c:
 *   int32 in_mem[C*overlap]          at +0xe0
 *   int32 prefilter_mem[C*1024]
 *   int16 oldBandE[C*nb], oldLogE[C*nb], oldLogE2[C*nb]
 * Field names are ours; `fXX` fields are not understood yet (XX = offset).
 */
#ifndef SSC_ENCODER_H
#define SSC_ENCODER_H

#include <stddef.h>
#include <stdint.h>

#include "ssc_mode.h"

#define SSC_COMBFILTER_MAXPERIOD 1024
#define SSC_COMBFILTER_MINPERIOD 15
#define SSC_HEADER_BYTES 4

typedef struct SscEncoder {
    const SscMode *mode;        /* 0x00 */
    int32_t overlap;            /* 0x08 */
    int32_t channels;           /* 0x0c */
    int32_t force_intra;        /* 0x10  0 after init */
    int32_t end;                /* 0x14  mode->effEBands at init, mode->nbEBands per frame */
    int32_t f18;                /* 0x18  -1 after init (Opus: bitrate / VBR target) */
    int32_t rng;                /* 0x1c  range coder state at the end of the frame */
    int32_t spread_decision;    /* 0x20  2 (SPREAD_NORMAL) after init */
    int32_t delayedIntra;       /* 0x24  1 after init */
    int32_t tonal_average;      /* 0x28  256 after init */
    int32_t lastCodedBands;     /* 0x2c */
    int32_t hf_average;         /* 0x30 */
    int32_t tapset_decision;    /* 0x34 */
    int32_t prefilter_period;   /* 0x38 */
    int16_t prefilter_gain;     /* 0x3c */
    int16_t f3e;
    int32_t consec_transient;   /* 0x40 */
    int32_t preemph_memE[2];    /* 0x44  Opus preemphasis memory: always 0 (older builds computed it) */
    int32_t overlap_max;        /* 0x4c  max |pcm| over the last overlap samples */
    int32_t intensity;          /* 0x50  intensity stereo start band */
    uint8_t f54[0x60 - 0x54];
    int32_t fs_mode;            /* 0x60  44100 for 48 kHz input, else Fs */
    int32_t fs;                 /* 0x64  real input rate */
    int32_t bitrate;            /* 0x68  bps, set per frame */
    int32_t bit_depth;          /* 0x6c  24 */
    uint8_t f70[0x8c - 0x70];   /* 0x70  not understood yet (zero after init) */
    uint16_t frame_counter;     /* 0x8c  8-bit, wraps at 256 */
    uint16_t hdr_low_bits;      /* 0x8e  low 2 bits of header byte 2 (1 after init) */
    int64_t biquad[10];         /* 0x90  Biquad_Narrow_int2int_stereo state */
    int32_t in_mem[];           /* 0xe0  per-channel arrays follow */
} SscEncoder;

/* Shared work buffers. The blob keeps them as process globals with these names. */
extern int32_t in_shared[2 * (864 + SSC_OVERLAP)];               /* CELT `in` */
extern int32_t _pre_shared[2 * (864 + SSC_COMBFILTER_MAXPERIOD)]; /* prefilter `pre` */

/* Test hook: called at named points of ssc_encode with the live range coder
 * (const ec_enc *). Lets the stage bench snapshot libssc where it snapshots the
 * blob. NULL in normal use. */
enum {
    SSC_STAGE_PRE_MDCT = 1,
    SSC_STAGE_POST_MDCT = 2,
    SSC_STAGE_POST_NORMALISE = 3,
    SSC_STAGE_PRE_PVQ = 4,  /* entry of quant_all_bands */
    SSC_STAGE_PRE_COARSE = 5,
    SSC_STAGE_PRE_ALLOC = 6,
    SSC_STAGE_PRE_FINE = 7
};

/* Filled before SSC_STAGE_PRE_PVQ: the quant_all_bands arguments and the
 * allocation/energy arrays, in the order the stage bench reads them. */
typedef struct {
    int32_t end, shortBlocks, spread, dual_stereo, intensity, total_bits, balance, codedBands;
    int32_t tf_res[22], pulses[22], fine_quant[22], fine_priority[22];
    int32_t bandE[44];
    int16_t error[44];
} SscStageAlloc;
extern SscStageAlloc ssc_stage_alloc;
/* Filled before SSC_STAGE_PRE_COARSE: the scalar arguments of quant_coarse_energy
 * and its bandLogE input. */
typedef struct {
    int32_t nbBands, end, budget, nbAvailableBytes, force_intra;
    int16_t bandLogE[44];
} SscStageCoarse;
extern SscStageCoarse ssc_stage_coarse;
/* Copy of the frame's SscAlloc (ssc_internal.h, 0x184 bytes) before
 * SSC_STAGE_PRE_ALLOC and SSC_STAGE_PRE_FINE, and codedBands for the latter. */
extern uint8_t ssc_stage_a[0x184];
extern int32_t ssc_stage_coded;
typedef void (*ssc_stage_fn)(int stage, const struct SscEncoder *st, const void *enc);
extern ssc_stage_fn ssc_stage_hook;

int ssc_encoder_get_size(int channels, int fs);
int ssc_encoder_init(SscEncoder *st, int fs, int channels, int bit_depth);
SscEncoder *ssc_encoder_create(int fs, int channels, int bit_depth, int *err);
void ssc_encoder_destroy(SscEncoder *st);
const SscMode *ssc_custom_mode_create(int fs, int frame_size, int *err);

/* Encode one frame of interleaved int32 PCM (24-bit: full scale 2^23) into out.
 * Like the blob, the DRC limiter rewrites pcm in place.
 * Returns the frame length in bytes (header + payload) or a negative error. */
int ssc_encode(SscEncoder *st, int32_t *pcm, int frame_size, uint8_t *out, int bitrate);

#endif
