/* libssc — energy quantisation, spreading decision and bit allocation.
 *
 * Opus 1.1 quant_bands.c / bands.c / rate.c with the blob's signatures: the
 * start band is always 0, C = 2, LM = 3, the encoder side only. Samsung
 * changes are marked "Samsung:". Bits are in 1/8 (BITRES = 3).
 */
#include <stdlib.h>
#include <string.h>

#include "opus/arch.h"
#include "opus/entcode.h"
#include "opus/entenc.h"
#include "opus/laplace.h"
#include "opus/mathops.h"
#include "ssc_encoder.h"
#include "ssc_internal.h"

#define C2 2
#define LM3 3
#define BITRES 3
#define MAX_FINE_BITS 8
#define FINE_OFFSET 21

static const unsigned char e_prob_inter[42] = {
    42, 121, 96, 66, 108, 43, 111, 40, 117, 44, 123, 32, 120, 36, 119, 33, 127, 33, 134, 34, 139,
    21, 147, 23, 152, 20, 158, 25, 154, 26, 166, 21, 173, 16, 184, 13, 184, 10, 150, 13, 139, 15};
static const unsigned char e_prob_intra[42] = {
    22, 178, 63, 114, 74, 82, 84, 83, 92, 82, 103, 62, 96, 72, 96, 67, 101, 73, 107, 72, 113,
    55, 118, 52, 125, 52, 118, 52, 117, 55, 135, 49, 137, 39, 157, 32, 145, 29, 97, 33, 77, 40};
static const unsigned char small_energy_icdf[3] = {2, 1, 0};
static const unsigned char LOG2_FRAC_TABLE[24] = {0,  8,  13, 16, 19, 21, 23, 24, 26, 27, 28, 29,
                                                  30, 31, 32, 32, 33, 34, 34, 35, 36, 36, 37, 37};

/* ------------------------------------------------------------ coarse energy */

/* Opus quant_coarse_energy_impl, start 0 (blob FUN_00108f10). */
static int coarse_impl(const SscMode *m, int end, const int16_t *eBands, int16_t *oldEBands,
                       int32_t budget, int32_t tell, const unsigned char *prob_model,
                       int16_t *error, ec_enc *enc, int intra, int16_t max_decay) {
    int i, c, badness = 0, nb = m->nbEBands;
    int32_t prev[2] = {0, 0};
    int32_t coef = intra ? 0 : 16384, beta = intra ? 4915 : 6554;
    if (tell + 3 <= budget) ec_enc_bit_logp(enc, intra, 3);
    for (i = 0; i < end; i++) {
        for (c = 0; c < C2; c++) {
            int bits_left, qi, qi0;
            int32_t q, f, tmp, cterm;
            int16_t x = eBands[i + c * nb], oldE, decay_bound;
            oldE = MAX16(-QCONST16(9.f, DB_SHIFT), oldEBands[i + c * nb]);
            cterm = (coef * oldE) >> 8;  /* Samsung: no rounding (exact here anyway) */
            f = SHL32(EXTEND32(x), 7) - cterm - prev[c];
            qi = (f + QCONST32(.5f, DB_SHIFT + 7)) >> (DB_SHIFT + 7);
            decay_bound = EXTRACT16(MAX32(-QCONST16(28.f, DB_SHIFT),
                                          SUB32((int32_t)oldEBands[i + c * nb], max_decay)));
            if (qi < 0 && x < decay_bound) {
                qi += (decay_bound - x) >> DB_SHIFT;
                if (qi > 0) qi = 0;
            }
            qi0 = qi;
            tell = ec_tell(enc);
            bits_left = budget - tell - 3 * C2 * (end - i);
            if (i != 0 && bits_left < 30) {
                if (bits_left < 24) qi = IMIN(1, qi);
                if (bits_left < 16) qi = IMAX(-1, qi);
            }
            if (budget - tell >= 15) {
                int pi = 2 * IMIN(i, 20);
                ec_laplace_encode(enc, &qi, prob_model[pi] << 7, prob_model[pi + 1] << 6);
            } else if (budget - tell >= 2) {
                qi = IMAX(-1, IMIN(qi, 1));
                ec_enc_icdf(enc, 2 * qi ^ -(qi < 0), small_energy_icdf, 2);
            } else if (budget - tell >= 1) {
                qi = IMIN(0, qi);
                ec_enc_bit_logp(enc, -qi, 1);
            } else {
                qi = -1;
            }
            error[i + c * nb] = (int16_t)(PSHR32(f, 7) - SHL16(qi, DB_SHIFT));
            badness += abs(qi0 - qi);
            q = (int32_t)SHL32(EXTEND32(qi), DB_SHIFT);
            tmp = cterm + prev[c] + SHL32(q, 7);
            tmp = MAX32(-QCONST32(28.f, DB_SHIFT + 7), tmp);
            oldEBands[i + c * nb] = (int16_t)PSHR32(tmp, 7);
            prev[c] = prev[c] + SHL32(q, 7) - MULT16_16(beta, (int16_t)PSHR32(q, 8));
        }
    }
    return badness;
}

/* Opus quant_coarse_energy with two_pass on, no loss_rate and start 0.
 * nbBands is unused. Samsung: the intra pass is kept only while its bytes fit
 * a 150-byte buffer, and the distortion that feeds delayedIntra runs over the
 * first 2*end entries of the arrays (not end per channel: blob quirk, kept). */
#define INTRA_BUF 150
void quant_coarse_energy(const SscMode *m, int nbBands, int end, const int16_t *eBands,
                         int16_t *oldEBands, uint32_t budget, int16_t *error, ec_enc *enc,
                         int nbAvailableBytes, int force_intra, int32_t *delayedIntra) {
    int nb = m->nbEBands, i, badness1 = 0, badness2, intra, intra_ok;
    int16_t oldE_intra[2 * SSC_NB_EBANDS], error_intra[2 * SSC_NB_EBANDS], max_decay;
    uint32_t dist = 0, tell;
    int32_t new_distortion, tell_intra, md;
    ec_enc start_state, intra_state;
    unsigned char intra_bits[INTRA_BUF];
    uint32_t nstart, nintra;
    (void)nbBands;

    for (i = 0; i < 2 * end; i++) {
        int d = (eBands[i] >> 3) - (oldEBands[i] >> 3);
        dist += (uint32_t)(d * d);
    }
    new_distortion = end > 0 ? (int32_t)((dist >> 14) < 200 ? dist >> 14 : 200) : 0;

    tell = ec_tell(enc);
    md = (int32_t)((uint32_t)nbAvailableBytes << 7);
    max_decay = (int16_t)(md > 0x3fff ? 0x4000 : md);
    start_state = *enc;
    memcpy(oldE_intra, oldEBands, sizeof(int16_t) * C2 * nb);
    if (tell + 3 <= budget)
        badness1 = coarse_impl(m, end, eBands, oldE_intra, budget, tell, e_prob_intra,
                               error_intra, enc, 1, max_decay);
    intra = force_intra && tell + 3 <= budget;
    if (intra) {
        memcpy(oldEBands, oldE_intra, sizeof(int16_t) * C2 * nb);
        memcpy(error, error_intra, sizeof(int16_t) * C2 * nb);
    } else {
        intra_ok = tell + 3 <= budget;
        tell_intra = ec_tell_frac(enc);
        intra_state = *enc;
        nstart = ec_range_bytes(&start_state);
        nintra = ec_range_bytes(&intra_state);
        if (nintra - nstart < INTRA_BUF)
            memcpy(intra_bits, ec_get_buffer(&intra_state) + nstart, nintra - nstart);
        else
            intra_ok = 0;
        *enc = start_state;
        badness2 = coarse_impl(m, end, eBands, oldEBands, budget, tell, e_prob_inter, error, enc,
                               0, max_decay);
        if (intra_ok &&
            (badness1 < badness2 ||
             (badness1 == badness2 && (int32_t)ec_tell_frac(enc) > tell_intra))) {
            *enc = intra_state;
            memcpy(ec_get_buffer(&intra_state) + nstart, intra_bits, nintra - nstart);
            memcpy(oldEBands, oldE_intra, sizeof(int16_t) * C2 * nb);
            memcpy(error, error_intra, sizeof(int16_t) * C2 * nb);
            intra = 1;
        }
    }
    if (intra)
        *delayedIntra = new_distortion;
    else
        *delayedIntra = (*delayedIntra >> 2) + new_distortion;
}

/* Opus quant_fine_energy, start 0. */
void quant_fine_energy(const SscMode *m, int end, int16_t *oldEBands, int16_t *error,
                       const int32_t *fine_quant, ec_enc *enc) {
    int i, c;
    for (i = 0; i < end; i++) {
        int16_t frac = (int16_t)(1 << fine_quant[i]);
        if (fine_quant[i] <= 0) continue;
        c = 0;
        do {
            int q2;
            int16_t offset;
            q2 = (error[i + c * m->nbEBands] + QCONST16(.5f, DB_SHIFT)) >>
                 (DB_SHIFT - fine_quant[i]);
            if (q2 > frac - 1) q2 = frac - 1;
            if (q2 < 0) q2 = 0;
            ec_enc_bits(enc, q2, fine_quant[i]);
            offset = (int16_t)(SHR32(SHL32(EXTEND32(q2), DB_SHIFT) + QCONST16(.5f, DB_SHIFT),
                                     fine_quant[i]) -
                               QCONST16(.5f, DB_SHIFT));
            oldEBands[i + c * m->nbEBands] += offset;
            error[i + c * m->nbEBands] -= offset;
        } while (++c < C2);
    }
}

/* ------------------------------------------------------------ spreading */

/* Samsung spreading_decision: only bands 8..end-1, tcounts kept doubled (so
 * hf_sum is twice Opus'), no SPREAD_NONE shortcut, hysteresis on 4x scale.
 * State in the encoder: spread_decision (last), tonal_average, hf_average,
 * tapset_decision. hf_sum is divided by 8 whatever end is (older builds:
 * by 2 (end + 4 - nbEBands)). */
int spreading_decision(SscEncoder *st, const int16_t *X, int update_hf, int end) {
    const SscMode *m = st->mode;
    const int16_t *eBands = m->eBands;
    int *average = &st->tonal_average, last_decision = st->spread_decision;
    int *hf_average = &st->hf_average, *tapset_decision = &st->tapset_decision;
    int N0 = 8 * m->shortMdctSize, c, i, j, sum = 0, nbBands = 0, hf_sum = 0, v;
    if (end >= 9)
        for (c = 0; c < C2; c++)
            for (i = 8; i < end; i++) {
                const int16_t *x = X + 8 * eBands[i] + c * N0;
                int N = 8 * (eBands[i + 1] - eBands[i]), t0 = 0, t1 = 0, t2 = 0, tmp;
                if (eBands[i + 1] - eBands[i] <= 1) continue;
                for (j = 0; j < N; j++) {
                    int32_t x2N = (int32_t)(((uint32_t)(x[j] * x[j]) >> 15) * N);
                    if (x2N < 0x80) t2 += 2;
                    if (x2N < 0x200) t1 += 2;
                    if (x2N < 0x800) t0 += 2;
                }
                if (i > m->nbEBands - 4) hf_sum += (32 * (t1 + t0)) / N;
                tmp = (t2 >= N) + (t1 >= N) + (t0 >= N);
                sum += tmp * 256;
                nbBands++;
            }
    if (update_hf) {
        *hf_average = (*hf_average + (hf_sum >> 3)) >> 1;
        hf_sum = *hf_average;
        if (*tapset_decision == 0) hf_sum -= 4;
        else if (*tapset_decision == 2) hf_sum += 4;
        *tapset_decision = hf_sum > 22 ? 2 : hf_sum > 18;
    }
    sum = nbBands ? sum / nbBands : 0;  /* aarch64 sdiv by 0 gives 0 */
    v = (*average + sum) >> 1;
    sum = ((384 - (last_decision << 7)) | 0x42) + ((*average + sum) & ~1) + v;
    *average = v;
    if (sum < 0x140) return 3;
    if (sum < 0x400) return 2;
    return sum < 0x600;
}

int hysteresis_decision(int16_t val, const int16_t *thresholds, const int16_t *hysteresis, int N,
                        int prev) {
    int i;
    for (i = 0; i < N; i++)
        if (val < thresholds[i]) break;
    if (i > prev && val < thresholds[prev] + hysteresis[prev]) i = prev;
    if (i < prev && val > thresholds[prev - 1] - hysteresis[prev - 1]) i = prev;
    return i;
}

/* Exported, not called by ssc_encode (it reads mode->cache.caps directly). */
void init_caps(const SscMode *m, int *cap, int LM, int C) {
    int i;
    for (i = 0; i < m->nbEBands; i++)
        cap[i] = (m->cache.caps[i] + 64) * C * ((m->eBands[i + 1] - m->eBands[i]) << LM) >> 2;
}

/* ------------------------------------------------------------ allocation */

#define ALLOC_STEPS 6

static int interp_bits2pulses(const SscMode *m, int end, int skip_start, const int *bits1,
                              const int *bits2, const int *thresh, const int *cap, int32_t total,
                              int32_t *_balance, int skip_rsv, int *intensity, int intensity_rsv,
                              int *dual_stereo, int dual_stereo_rsv, int *bits, int *ebits,
                              int *fine_priority, ec_enc *ec, int prev, int signalBandwidth) {
    const int16_t *eBands = m->eBands;
    int32_t psum, left, percoeff, balance;
    int lo = 0, hi = 1 << ALLOC_STEPS, i, j, codedBands, done;
    const int alloc_floor = C2 << BITRES, stereo = 1, logM = LM3 << BITRES;
    for (i = 0; i < ALLOC_STEPS; i++) {
        int mid = (lo + hi) >> 1;
        psum = 0;
        done = 0;
        for (j = end; j-- > 0;) {
            int tmp = bits1[j] + (mid * (int32_t)bits2[j] >> ALLOC_STEPS);
            if (tmp >= thresh[j] || done) {
                done = 1;
                psum += IMIN(tmp, cap[j]);
            } else if (tmp >= alloc_floor) {
                psum += alloc_floor;
            }
        }
        if (psum > total) hi = mid;
        else lo = mid;
    }
    psum = 0;
    done = 0;
    for (j = end; j-- > 0;) {
        int tmp = bits1[j] + ((int32_t)lo * bits2[j] >> ALLOC_STEPS);
        if (tmp < thresh[j] && !done)
            tmp = tmp >= alloc_floor ? alloc_floor : 0;
        else
            done = 1;
        tmp = IMIN(tmp, cap[j]);
        bits[j] = tmp;
        psum += tmp;
    }
    for (codedBands = end;; codedBands--) {
        int band_width, band_bits, rem;
        j = codedBands - 1;
        if (j <= skip_start) {
            total += skip_rsv;
            break;
        }
        left = total - psum;
        percoeff = (int32_t)((uint32_t)left / (uint32_t)(eBands[codedBands] - eBands[0]));
        left -= (eBands[codedBands] - eBands[0]) * percoeff;
        rem = IMAX(left - (eBands[j] - eBands[0]), 0);
        band_width = eBands[codedBands] - eBands[j];
        band_bits = (int)(bits[j] + percoeff * band_width + rem);
        if (band_bits >= IMAX(thresh[j], alloc_floor + (1 << BITRES))) {
            if (codedBands <= 2 ||
                (band_bits > ((j < prev ? 7 : 9) * band_width << LM3 << BITRES) >> 4 &&
                 j <= signalBandwidth)) {
                ec_enc_bit_logp(ec, 1, 1);
                break;
            }
            ec_enc_bit_logp(ec, 0, 1);
            psum += 1 << BITRES;
            band_bits -= 1 << BITRES;
        }
        psum -= bits[j] + intensity_rsv;
        if (intensity_rsv > 0) intensity_rsv = LOG2_FRAC_TABLE[j];
        psum += intensity_rsv;
        if (band_bits >= alloc_floor) {
            psum += alloc_floor;
            bits[j] = alloc_floor;
        } else {
            bits[j] = 0;
        }
    }
    if (intensity_rsv > 0) {
        *intensity = IMIN(*intensity, codedBands);
        ec_enc_uint(ec, *intensity, codedBands + 1);
    } else {
        *intensity = 0;
    }
    if (*intensity <= 0) {
        total += dual_stereo_rsv;
        dual_stereo_rsv = 0;
    }
    if (dual_stereo_rsv > 0)
        ec_enc_bit_logp(ec, *dual_stereo, 1);
    else
        *dual_stereo = 0;

    left = total - psum;
    percoeff = (int32_t)((uint32_t)left / (uint32_t)(eBands[codedBands] - eBands[0]));
    left -= (eBands[codedBands] - eBands[0]) * percoeff;
    for (j = 0; j < codedBands; j++) bits[j] += (int)percoeff * (eBands[j + 1] - eBands[j]);
    for (j = 0; j < codedBands; j++) {
        int tmp = (int)IMIN(left, eBands[j + 1] - eBands[j]);
        bits[j] += tmp;
        left -= tmp;
    }
    balance = 0;
    for (j = 0; j < codedBands; j++) {
        int N0 = eBands[j + 1] - eBands[j], N = N0 << LM3, den, offset, NClogN;
        int32_t excess, bit = (int32_t)bits[j] + balance;
        if (N > 1) {
            excess = MAX32(bit - cap[j], 0);
            bits[j] = bit - excess;
            den = C2 * N + ((N > 2 && !*dual_stereo && j < *intensity) ? 1 : 0);
            NClogN = den * (m->logN[j] + logM);
            offset = (NClogN >> 1) - den * FINE_OFFSET;
            if (N == 2) offset += den << BITRES >> 2;
            if (bits[j] + offset < den * 2 << BITRES)
                offset += NClogN >> 2;
            else if (bits[j] + offset < den * 3 << BITRES)
                offset += NClogN >> 3;
            ebits[j] = IMAX(0, (bits[j] + offset + (den << (BITRES - 1))));
            ebits[j] = (int)((uint32_t)ebits[j] / (uint32_t)den) >> BITRES;
            if (C2 * ebits[j] > (bits[j] >> BITRES)) ebits[j] = bits[j] >> stereo >> BITRES;
            ebits[j] = IMIN(ebits[j], MAX_FINE_BITS);
            fine_priority[j] = ebits[j] * (den << BITRES) >= bits[j] + offset;
            bits[j] -= C2 * ebits[j] << BITRES;
        } else {
            excess = MAX32(0, bit - (C2 << BITRES));
            bits[j] = bit - excess;
            ebits[j] = 0;
            fine_priority[j] = 1;
        }
        if (excess > 0) {
            int extra_fine = IMIN(excess >> (stereo + BITRES), MAX_FINE_BITS - ebits[j]);
            int extra_bits = extra_fine * C2 << BITRES;
            ebits[j] += extra_fine;
            fine_priority[j] = extra_bits >= excess - balance;
            excess -= extra_bits;
        }
        balance = excess;
    }
    *_balance = balance;
    for (; j < end; j++) {
        ebits[j] = bits[j] >> stereo >> BITRES;
        bits[j] = 0;
        fine_priority[j] = ebits[j] < 1;
    }
    return codedBands;
}

/* Opus compute_allocation, start 0, C 2, LM 3, encoder. Samsung: a->table2
 * (bitrate > 192k) picks the second allocation table (mode->allocVectors2). */
int compute_allocation(SscEncoder *st, SscAlloc *a, ec_enc *ec, int end, int signalBandwidth) {
    const SscMode *m = st->mode;
    const int *offsets = a->offsets, *cap = a->caps;
    int alloc_trim = a->alloc_trim, *intensity = &st->intensity, *dual_stereo = &a->dual_stereo;
    int32_t total = a->total, *balance = &a->balance;
    int *pulses = a->pulses, *ebits = a->fine_quant, *fine_priority = a->fine_priority;
    int prev = st->lastCodedBands;
    const int16_t *eBands = m->eBands;
    const uint8_t *alloc = a->table2 ? m->allocVectors2 : m->allocVectors;
    int len = m->nbEBands, lo, hi, j, skip_start = 0, skip_rsv, intensity_rsv, dual_stereo_rsv;
    int bits1[SSC_NB_EBANDS], bits2[SSC_NB_EBANDS], thresh[SSC_NB_EBANDS];
    int trim_offset[SSC_NB_EBANDS];

    total = IMAX(total, 0);
    skip_rsv = total >= 1 << BITRES ? 1 << BITRES : 0;
    total -= skip_rsv;
    intensity_rsv = LOG2_FRAC_TABLE[end];
    dual_stereo_rsv = 0;
    if (intensity_rsv > total) {
        intensity_rsv = 0;
    } else {
        total -= intensity_rsv;
        dual_stereo_rsv = total >= 1 << BITRES ? 1 << BITRES : 0;
        total -= dual_stereo_rsv;
    }
    for (j = 0; j < end; j++) {
        int w = eBands[j + 1] - eBands[j];
        thresh[j] = IMAX(C2 << BITRES, (3 * w << LM3 << BITRES) >> 4);
        trim_offset[j] = C2 * w * (alloc_trim - 5 - LM3) * (end - j - 1) * (1 << (LM3 + BITRES)) >> 6;
        if (w << LM3 == 1) trim_offset[j] -= C2 << BITRES;
    }
    lo = 1;
    hi = m->nbAllocVectors - 1;
    do {
        int done = 0, psum = 0, mid = (lo + hi) >> 1;
        for (j = end; j-- > 0;) {
            int N = eBands[j + 1] - eBands[j];
            int bitsj = C2 * N * alloc[mid * len + j] << LM3 >> 2;
            if (bitsj > 0) bitsj = IMAX(0, bitsj + trim_offset[j]);
            bitsj += offsets[j];
            if (bitsj >= thresh[j] || done) {
                done = 1;
                psum += IMIN(bitsj, cap[j]);
            } else if (bitsj >= C2 << BITRES) {
                psum += C2 << BITRES;
            }
        }
        if (psum > total) hi = mid - 1;
        else lo = mid + 1;
    } while (lo <= hi);
    hi = lo--;
    for (j = 0; j < end; j++) {
        int N = eBands[j + 1] - eBands[j];
        int bits1j = C2 * N * alloc[lo * len + j] << LM3 >> 2;
        int bits2j = hi >= m->nbAllocVectors ? cap[j] : C2 * N * alloc[hi * len + j] << LM3 >> 2;
        if (bits1j > 0) bits1j = IMAX(0, bits1j + trim_offset[j]);
        if (bits2j > 0) bits2j = IMAX(0, bits2j + trim_offset[j]);
        if (lo > 0) bits1j += offsets[j];
        bits2j += offsets[j];
        if (offsets[j] > 0) skip_start = j;
        bits2j = IMAX(0, bits2j - bits1j);
        bits1[j] = bits1j;
        bits2[j] = bits2j;
    }
    return interp_bits2pulses(m, end, skip_start, bits1, bits2, thresh, cap, total, balance,
                              skip_rsv, intensity, intensity_rsv, dual_stereo, dual_stereo_rsv,
                              pulses, ebits, fine_priority, ec, prev, signalBandwidth);
}
