/* libssc — encoder state, ABI twin of the blob's CELT-derived encoder struct.
 *
 * Header is 300 bytes (blob: get_size = (nb*6 + overlap*4 + 4096)*C + 300),
 * followed by per-channel arrays laid out like Opus 1.1 celt_encoder.c:
 *   int32 in_mem[C*overlap]   (starts at +300, Opus `celt_sig in_mem[1]`)
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
#define SSC_HEADER_BYTES 4

typedef struct SscEncoder {
    const SscMode *mode;        /* 0x00 */
    int32_t overlap;            /* 0x08 */
    int32_t channels;           /* 0x0c */
    int32_t f10;                /* 0x10  0 after init */
    int32_t end;                /* 0x14  mode->effEBands at init, mode->nbEBands per frame */
    int32_t f18;                /* 0x18  -1 after init */
    int32_t f1c;                /* 0x1c  written at end of every frame */
    int32_t f20;                /* 0x20  2 after init (spread decision, SPREAD_NORMAL?) */
    int32_t f24;                /* 0x24  1 after init */
    int32_t f28;                /* 0x28  256 after init (tonal average?) */
    uint8_t f2c[0x60 - 0x2c];
    int32_t fs_mode;            /* 0x60  44100 for 48 kHz input, else Fs */
    int32_t fs;                 /* 0x64  real input rate */
    int32_t bitrate;            /* 0x68  bps, set per frame */
    int32_t bit_depth;          /* 0x6c  24 */
    uint8_t f70[0xd4 - 0x70];
    uint16_t frame_counter;     /* 0xd4  8-bit, wraps at 256 */
    uint16_t hdr_low_bits;      /* 0xd6  low 2 bits of header byte 2 (1 after init) */
    uint8_t fd8[0x12c - 0xd8];  /* 0xd8  Biquad_Narrow state starts here */
    int32_t in_mem[1];          /* 0x12c  per-channel arrays follow */
} SscEncoder;

int ssc_encoder_get_size(int channels, int fs);
int ssc_encoder_init(SscEncoder *st, int fs, int channels, int bit_depth);
SscEncoder *ssc_encoder_create(int fs, int channels, int bit_depth, int *err);
void ssc_encoder_destroy(SscEncoder *st);
const SscMode *ssc_custom_mode_create(int fs, int frame_size, int *err);

/* Encode one frame of interleaved int32 PCM (24-bit at 2^29 scale) into out.
 * Returns the frame length in bytes (header + payload) or a negative error. */
int ssc_encode(SscEncoder *st, const int32_t *pcm, int frame_size, uint8_t *out, int bitrate);

#endif
