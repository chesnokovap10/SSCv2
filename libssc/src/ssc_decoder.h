/* libssc — SSC decoder (phase 6).
 *
 * Reads frames written by ssc_encode (and by the blob, which writes the same
 * bits): the header, then the CELT payload in exactly the encoder's order.
 * Bitstream parsing and the quantised energies are exact (integer, the
 * encoder's own allocation arithmetic); the synthesis (PVQ vectors, inverse
 * MDCT, overlap-add) is float, the post-filter is the encoder's comb filter.
 * Output is interleaved stereo int32 at 2^23 full scale (24 bit), delayed by
 * the 108-sample overlap.
 *
 * Not reproduced (the encoder never signals how the Buds decoder does it):
 * folding into bands without pulses (noise is used), anti-collapse.
 */
#ifndef SSC_DECODER_H
#define SSC_DECODER_H

#include <stdint.h>

typedef struct SscDecoder SscDecoder;

/* What the last frame carried (for analysis). */
typedef struct {
    int32_t bitrate;        /* from the header, bps */
    int32_t fs;             /* 48000 or 96000 */
    int32_t counter;        /* frame counter from the header */
    int32_t payload;        /* range-coded bytes */
    int32_t silence, transient, pf_on, pf_period, pf_qg;
    int32_t intra, spread, intensity, dual_stereo, alloc_trim, codedBands, drop;
    int32_t anti_collapse;  /* the flag (not applied) */
    int32_t bits_used;      /* ec_tell at the end */
    int16_t oldBandE[44];   /* quantised log energies after the frame (Q10, minus eMeans) */
    int32_t pulses[22], fine_quant[22], offsets[22];
} SscDecInfo;

SscDecoder *ssc_decoder_create(int fs, int *err);   /* 44100 | 48000 | 96000 */
void ssc_decoder_destroy(SscDecoder *st);
/* Decodes one frame (header included). pcm: 864 stereo frames, interleaved.
 * Returns 864, or < 0 (-1 bad header, -2 wrong length, -3 other mode). */
int ssc_decode(SscDecoder *st, const uint8_t *frame, int len, int32_t *pcm);
void ssc_decoder_info(const SscDecoder *st, SscDecInfo *info);

#endif
