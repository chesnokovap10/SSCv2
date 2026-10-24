/* libssc — Samsung "headroom": fixed attenuation of the upper MDCT bins of both
 * channels before the band energies (ssc_encode calls it right after the MDCT).
 *
 * Each bin is scaled by a Q15 gain with Opus MULT16_32_Q15 arithmetic:
 *   x * g = (x >> 16) * 2g + (((x & 0xffff) * g) >> 15)
 * freq holds two channels of N (864) bins; M is the number of short MDCTs (8),
 * so band b starts at bin eBands[b] * M.
 */
#include "ssc_internal.h"
#include "ssc_mode.h"

#define NBINS 864

static inline int32_t mul16_32_q15(int32_t g, int32_t x) {
    return (int32_t)((uint32_t)(x >> 16) * (uint32_t)(g * 2) +
                     (uint32_t)((int32_t)((uint32_t)g * (uint32_t)(x & 0xffff)) >> 15));
}

/* Gain given as the 32-bit value g << 16 (the blob's ramps are built that way). */
static inline int32_t mul_q16(int32_t g16, int32_t x) {
    return (int32_t)((uint32_t)(g16 >> 15) * (uint32_t)(x >> 16) +
                     (uint32_t)((int32_t)((uint32_t)(x & 0xffff) * (uint32_t)(g16 >> 16)) >> 15));
}

static void scale(int32_t *freq, int lo, int hi, int32_t g) {  /* uhq_headroom: N = 864 */
    int i;
    for (i = lo; i < hi; i++) {
        freq[i] = mul16_32_q15(g, freq[i]);
        freq[i + NBINS] = mul16_32_q15(g, freq[i + NBINS]);
    }
}

void normal_headroom(int32_t *freq, int bitrate, int M, const int16_t *eBands, int N) {
    int i;
    if (bitrate >= 96000) {
        /* Bands 20..21 from 34 * (M/4) bins into band 20 on: per-bin gains from
         * headroom_gain[] (low 16 bits), indexed from the start of band 20. */
        int b20 = eBands[20] * M, lo = b20 + (M >> 2) * 34, hi = eBands[22] * M;
        for (i = lo; i < hi; i++) {
            int32_t g = (int16_t)headroom_gain[i - b20];
            freq[i] = mul16_32_q15(g, freq[i]);
            freq[i + N] = mul16_32_q15(g, freq[i + N]);
        }
    } else {
        /* Two linear ramps: from band 17 down by 3/32768 per bin until 15 bins
         * before band 20, then down by 5 per bin to the end of band 21. */
        int b17 = eBands[17] * M, b20 = eBands[20] * M, b22 = eBands[22] * M;
        int knee = b20 - 15;
        int32_t g;
        if (knee <= b17) {
            g = 0x7767;
        } else {
            for (i = b17; i < knee; i++) {
                int32_t g16 = (int32_t)(0x7fff0000u - (uint32_t)(i - b17) * 0x30000u);
                freq[i] = mul_q16(g16, freq[i]);
                freq[i + N] = mul_q16(g16, freq[i + N]);
            }
            g = (eBands[20] - eBands[17]) * M * -3 + 0x7794;
        }
        for (i = knee; i < b22; i++) {
            int32_t g16 = (int32_t)((uint32_t)(g - 5 * (i - knee)) << 16);
            freq[i] = mul_q16(g16, freq[i]);
            freq[i + N] = mul_q16(g16, freq[i + N]);
        }
    }
}

void uhq_headroom(int32_t *freq, int bitrate, int M, const int16_t *eBands) {
    int lo = eBands[18] * M;
    if (bitrate >= 270000) {
        scale(freq, lo, lo + 25, 0x78c8);
        if (lo + 25 < 354) scale(freq, lo + 25, 354, 0x7864);
        scale(freq, 354, 400, 0x7800);
        scale(freq, 400, NBINS, 0x779c);
    } else {
        scale(freq, lo, lo + 25, 0x78c8);
        if (lo + 25 < 350) scale(freq, lo + 25, 350, 0x781e);
        scale(freq, 350, NBINS, 0x779c);
    }
}

/* Not called by ssc_encode; N passes through to normal_headroom (w4), uhq is w5. */
void headroom_process(int32_t *freq, int bitrate, int M, const int16_t *eBands, int N, int uhq) {
    if (uhq)
        uhq_headroom(freq, bitrate, M, eBands);
    else
        normal_headroom(freq, bitrate, M, eBands, N);
}
