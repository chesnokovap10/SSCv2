/* libssc — Samsung input processing (see ssc_drc.h). Ported from the blob's
 * aarch64 code (NEON paths folded into plain loops; integer results identical). */
#include "ssc_drc.h"

SscDrcState drc_struct;
int32_t DRC_ChNum;
int32_t Soundbooster_DRC_Fs;
int32_t DRC_ModeFlag;
int32_t _pcmpower[864 * 2];
int32_t previous_uhq_index;

/* Loop count used by the blob's do/while loops: n for n > 0, else 1. */
static int at_least_one(int n) { return n > 0 ? n : 1; }

void Biquad_Narrow_int2int_stereo(int32_t *out, const int32_t *in, const int32_t *coef,
                                  int64_t *state, int n) {
    int ch, i, count = at_least_one(n);
    for (ch = 0; ch < 2; ch++) {
        int64_t *s = state + 5 * ch;
        int32_t x1 = (int32_t)s[0], x2 = (int32_t)s[1];
        int32_t y1 = (int32_t)s[2], y2 = (int32_t)s[3];
        int64_t acc = s[4];  /* first sample: the stored (sign-extended) remainder */
        int32_t x0 = x1;
        for (i = 0; i < count; i++) {
            int32_t y;
            x0 = (int32_t)((uint32_t)in[2 * i + ch] << 7);
            acc += (int64_t)x0 * coef[0] + (int64_t)x1 * coef[1] + (int64_t)x2 * coef[2] +
                   (int64_t)y1 * coef[3] + (int64_t)y2 * coef[4];
            y = (int32_t)(acc >> 32);                  /* addhn: high half, truncating */
            acc = (int64_t)(uint32_t)acc;              /* keep the low half, unsigned */
            out[2 * i + ch] = y >> 4;
            x2 = x1;
            x1 = x0;
            y2 = y1;
            y1 = (int32_t)((uint32_t)y << 3);
        }
        s[0] = x0;
        s[1] = x2;   /* blob stores the sample before the last one */
        s[2] = y1;
        s[3] = y2;
        s[4] = (int32_t)(uint32_t)acc;               /* sign-extended low half */
    }
}

void powercalc(const int32_t *x, int n, int32_t *out) {
    uint64_t sum = 0;
    int i;
    if (n == 0) {
        *out = 0;
        return;
    }
    for (i = 0; i < 2 * (int)(uint32_t)n; i++) {
        int32_t t = (int32_t)((uint64_t)((int64_t)x[i] * x[i]) >> 16);
        sum += (uint64_t)(int64_t)(t >> 1);
    }
    *out = (int32_t)(sum >> 9);
}

static int32_t mul_q16(int32_t a, int32_t c) { return (int32_t)(((int64_t)a * c) >> 16); }

int CalculateLimitGain(int p_filtered, int p_rest, int bitrate, int fs) {
    int32_t base, drop;
    if (bitrate <= 96000) {
        base = 0x76c0;
        drop = 0x50;
    } else if (bitrate <= 128000) {
        base = 0x78b4;
        drop = 0x2f8;
    } else if (fs != 96000) {
        if (mul_q16(p_rest, 0xe666) <= p_filtered) return 0x7a94;
        if (p_filtered < mul_q16(p_rest, 0xcccc))
            return (p_rest >> 2 <= p_filtered) ? 0x741d : 0x8000;
        return 0x76b3;
    } else {
        int hi = bitrate >= 270000;
        if (mul_q16(p_rest, 0xf0a4) <= p_filtered) return 0x7b4c;
        if (mul_q16(p_rest, 0xeb85) <= p_filtered) return hi ? 0x7a01 : 0x7a52;
        if (mul_q16(p_rest, 0xe666) <= p_filtered) return hi ? 0x78f4 : 0x796c;
        if (mul_q16(p_rest, 0xcccc) <= p_filtered) return hi ? 0x785e : 0x7890;
        return 0x75d4;
    }
    if (mul_q16(p_rest, 0xe666) <= p_filtered) return base;
    return (p_rest >> 2 <= p_filtered) ? base - drop : 0x8000;
}

void set_DRC_limit_gain(int32_t limit) { drc_struct.limit = limit; }

void SoundBooster_DRC_Init(int fs, int channels) {
    if (fs <= 8000) fs = 8000;
    if (fs >= 192000) fs = 192000;
    Soundbooster_DRC_Fs = fs;
    DRC_ChNum = channels == 2 ? 2 : 1;
    drc_struct.g_start = 0x400000;
    drc_struct.g_prev = 0x20000000;
}

void SoundBooster_DRC_SetPar(int mode, int32_t limit) {
    DRC_ModeFlag = mode == 1;
    drc_struct.c_release = Soundbooster_DRC_Fs != 96000 ? 0x3ca4a1 : 0x3e6f79;
    drc_struct.limit = limit;
    drc_struct.c_attack = 0;
    drc_struct.g_smooth = 0x400000;
}

void SoundBooster_DRC_Exe(int32_t *x, int n) {
    SscDrcState *d = &drc_struct;
    int total = at_least_one(DRC_ChNum * n), frames = at_least_one(n);
    int32_t peak = 0, g = 0x400000, coef, target, step, g_new;
    uint32_t over = 0;
    int i;
    for (i = 0; i < total; i++) {
        int32_t a = x[i] < 0 ? (int32_t)(0u - (uint32_t)x[i]) : x[i];
        if (a > peak) peak = a;
        if (a > d->limit) over++;
    }
    if (over >= 25) {
        uint64_t div = (uint32_t)peak;
        int64_t q = div ? ((int64_t)d->limit << 31) / (int64_t)div : 0;
        g = (int32_t)q >> 9;
    }
    coef = g > d->g_smooth ? d->c_release : d->c_attack;
    g_new = (int32_t)((uint64_t)((int64_t)coef * d->g_smooth +
                                 (int64_t)(0x400000 - coef) * g) >> 22);
    target = d->g_prev < g_new ? d->g_prev : g_new;
    step = n ? (target - d->g_start) / n : 0;  /* aarch64 sdiv by 0 yields 0 */
    d->g_smooth = g_new;
    if (d->g_start != 0x400000 || step != 0) {
        int64_t gi = d->g_start;
        for (i = 0; i < frames; i++) {
            x[2 * i] = (int32_t)((uint64_t)(gi * x[2 * i]) >> 22);
            x[2 * i + 1] = (int32_t)((uint64_t)(gi * x[2 * i + 1]) >> 22);
            gi += step;
        }
    }
    d->g_start = target;
    d->g_prev = g_new;
}

const char *SoundBooster_DRC_Get_Version(void) {
    return "SoundBooster_DRC_classic for SBM ver 1.0 Release: 2019.12.05";
}
