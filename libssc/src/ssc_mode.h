/* libssc — Samsung Scalable Codec, bit-exact twin of libScalable_Encoder.so.
 *
 * Mode structures. Layouts match the blob byte for byte (LP64 / LLP64 alike:
 * only fixed-width ints and pointers), so the test bench can hand the same
 * memory to the blob and to libssc. Offsets are asserted in ssc_tables.c.
 */
#ifndef SSC_MODE_H
#define SSC_MODE_H

#include <stdint.h>

#define SSC_NB_EBANDS 22
#define SSC_OVERLAP 108
#define SSC_FRAME_SIZE 864         /* 8 short MDCTs of 108, LM = 3 */
#define SSC_NB_ALLOC_VECTORS 11

/* kiss-FFT state (Samsung, 24 bytes). */
typedef struct {
    int32_t nfft;
    int32_t shift;
    const int16_t *bitrev;
    const int32_t *twiddles;       /* (re, im) pairs, Q31 */
} ssc_fft_state;

/* MDCT lookup (32 bytes at mode+64). */
typedef struct {
    int32_t n;                     /* 1728 */
    int32_t maxshift;              /* 3 */
    const ssc_fft_state *kfft[2];
    const int32_t *trig;           /* quarter cosine, Q31, 433 entries */
} ssc_mdct_lookup;

/* Pulse cache (32 bytes at mode+96). */
typedef struct {
    int32_t size;
    const int16_t *index;          /* 5 x nbEBands */
    const uint8_t *bits;
    const int32_t *caps;           /* one int32 per band (Opus: u8 per LM/C) */
} ssc_pulse_cache;

/* Mode (128 bytes). Opus OpusCustomMode without preemph[]/maxLM/window, plus a
 * second allocation table and int32 caps. The MDCT window is ssc_window. */
typedef struct SscMode {
    int32_t Fs;                    /* 44100 for the 44.1/48 kHz mode, 96000 for UHQ */
    int32_t overlap;
    int32_t nbEBands;
    int32_t effEBands;
    const int16_t *eBands;
    int32_t nbShortMdcts;
    int32_t shortMdctSize;
    int32_t nbAllocVectors;
    const uint8_t *allocVectors;   /* nbAllocVectors x nbEBands */
    const uint8_t *allocVectors2;  /* Samsung: second table, same shape */
    const int16_t *logN;
    ssc_mdct_lookup mdct;
    ssc_pulse_cache cache;
} SscMode;

extern const SscMode ssc_mode_48k;  /* blob va 0x1b9c0 */
extern const SscMode ssc_mode_96k;  /* blob va 0x1ba40 */
extern const int32_t ssc_window[SSC_OVERLAP];  /* MDCT window, Q31 (blob va 0x3d80) */

/* Named data objects exported by the blob (same names). Some live in the
 * blob's writable .data; kept mutable here too until we know who writes them. */
extern const int8_t eMeans[25];
extern const int8_t tf_select_table[8];
extern const int32_t coeffs[5];
extern const int32_t coeffs96andbelow[5];
extern int32_t win_square[108];
extern int32_t margin;
extern int32_t headroom_gain[240];
/* Q15 gains, named by the blob after their value */
extern const int16_t GAIN_DB_MINUS_0_307, GAIN_DB_MINUS_0_482, GAIN_DB_MINUS_0_572;
extern const int16_t GAIN_VALUE_0_047, GAIN_VALUE_0_094, GAIN_VALUE_0_100, GAIN_VALUE_0_200,
    GAIN_VALUE_0_400, GAIN_VALUE_0_550, GAIN_VALUE_0_700;

#endif
