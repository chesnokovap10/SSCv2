/* libssc — functions under the blob's export names, so the twin test bench
 * can call libssc and the blob side by side. Opus functions that the blob
 * renamed (celt_* -> ssc_*) are thin wrappers; Samsung-modified ones are
 * implemented here until they get a proper home in phase 3.
 */
#include <stdint.h>
#include <string.h>

#include "opus/arch.h"
#include "opus/entcode.h"
#include "opus/mathops.h"

int ec_ilog(opus_uint32 v) { return EC_ILOG(v); }

opus_val32 ssc_rcp(opus_val32 x) { return celt_rcp(x); }
opus_val32 ssc_sqrt(opus_val32 x) { return celt_sqrt(x); }
opus_val16 ssc_rsqrt_norm(opus_val32 x) { return celt_rsqrt_norm(x); }
opus_val16 ssc_cos_norm(opus_val32 x) { return celt_cos_norm(x); }
opus_uint32 ssc_lcg_rand(opus_uint32 seed) { return 1664525 * seed + 1013904223; }

/* Samsung haar1: each product is truncated to Q15 before the butterfly
 * ((x*46340)>>16), where Opus rounds the sum (PSHR32(a*23170 +- b*23170, 15)). */
void haar1(int16_t *X, int N0, int stride) {
    int i, j;
    if (stride < 1 || N0 < 2) return;
    N0 >>= 1;
    for (i = 0; i < stride; i++)
        for (j = 0; j < N0; j++) {
            int16_t a = (int16_t)((X[stride * 2 * j + i] * 46340) >> 16);
            int16_t b = (int16_t)((X[stride * (2 * j + 1) + i] * 46340) >> 16);
            X[stride * 2 * j + i] = (int16_t)(a + b);
            X[stride * (2 * j + 1) + i] = (int16_t)(a - b);
        }
}

/* Blob copy helpers. They copy from the END backwards (not memmove-safe in the
 * other direction), which matters if a caller ever overlaps dst > src. */
void SSC_COPY32(int32_t *dst, const int32_t *src, int n) {
    long i;
    for (i = (long)n - 1; n != 0 && i >= 0; i--) dst[i] = src[i];
}

void SSC_COPY16(int16_t *dst, const int16_t *src, int n) {
    long i;
    for (i = (long)n - 1; n != 0 && i >= 0; i--) dst[i] = src[i];
}

void SSC_COPY8(uint8_t *dst, const uint8_t *src, int n) {
    long i;
    for (i = (long)n - 1; n != 0 && i >= 0; i--) dst[i] = src[i];
}

void SSC_CLEAR(void *p, unsigned n) {
    if (n) memset(p, 0, n);
}
