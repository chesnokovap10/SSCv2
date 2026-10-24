/* libssc — Samsung tone detector (called from pitch_search) and the unused
 * last_band_info_calc export.
 *
 * tone_detect looks at the coarse (4x decimated) pitch correlation. When both
 * best candidates are strong (>= 0.93 * maxcorr) and the correlation shows a
 * regular comb of peaks d apart (5 <= d <= n/2) across the whole lag range, it
 * replaces the candidates with the last peak of the comb and the one d before.
 * Reads of xcorr[-1] and xcorr[n] are what the blob does too (see pitch.c).
 */
#include <stdint.h>

int tone_detect(const int32_t *xcorr, int *best_pitch, int32_t maxcorr, int n) {
    int p0 = best_pitch[0], p1 = best_pitch[1];
    int32_t thr = (int32_t)(((int64_t)maxcorr * 0x7730) >> 15);
    int hi, lo, d, k, pos, step, j, last, q;
    int32_t a, b;

    if (xcorr[p0] < thr || xcorr[p1] < thr) return 0;
    hi = p0 <= p1 ? p1 : p0;
    lo = p0 <= p1 ? p0 : p1;
    d = (hi - lo) - (xcorr[hi + 1] <= xcorr[hi - 1]);
    if (d < 5) return 0;

    /* The first strong lag after lo sets the comb spacing. */
    for (k = 2; k < d; k++) {
        int32_t v = xcorr[lo + k];
        if (thr < v) {
            int32_t nxt = xcorr[lo + k + 1];
            d = k;
            if (nxt < v) d = k - (nxt < xcorr[lo + k - 1]);
            if (d < 5 || (n >> 1) < d) return 0;
            break;
        }
    }
    if ((n >> 1) < d) return 0;

    /* Peaks must continue every d (or d + 1) lags up to the end... */
    pos = hi + d;
    step = d;
    while (pos < n - 1) {
        a = xcorr[pos];
        b = xcorr[pos + 1];
        step = d;
        if (a <= b) {
            step = d + 1;
            a = b;
        }
        if (a < thr) return 0;
        pos += step;
    }
    last = pos - step;

    /* ...and back down to the start. */
    j = hi - d;
    while (j >= 1) {
        a = xcorr[j - 1];
        b = xcorr[j];
        step = d;
        if (b <= a) {
            step = d + 1;
            b = a;
        }
        if (b < thr) return 0;
        j -= step;
    }
    q = last - d;
    if (xcorr[q] <= xcorr[q - 1]) q--;
    if (n <= last || q < 0) return 0;
    best_pitch[0] = last;
    best_pitch[1] = q;
    return 1;
}

/* Highest band i in [1, n] whose two-channel mean e[i-1], e[n+i-1] exceeds
 * thr, else 0. Exported by the blob but never called by it. */
int last_band_info_calc(int thr, int n, const int32_t *e) {
    int i;
    for (i = n; i >= 1; i--)
        if (thr < ((int32_t)((uint32_t)e[n + i - 1] + (uint32_t)e[i - 1]) >> 1)) return i;
    return 0;
}
