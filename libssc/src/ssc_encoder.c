/* libssc — encoder entry points (ssc_encoder_* / ssc_encode).
 *
 * Phase 2 skeleton: mode selection, state init, frame header and byte budget
 * are bit-exact with the blob; the CELT payload is not produced yet (the
 * range coder is finished empty). The pipeline is ported stage by stage in
 * phase 3, see libssc/PLAN.md.
 */
#include "ssc_encoder.h"

#include <stdlib.h>
#include <string.h>

#include "opus/entenc.h"

_Static_assert(offsetof(SscEncoder, fs_mode) == 0x60, "encoder layout");
_Static_assert(offsetof(SscEncoder, frame_counter) == 0xd4, "encoder layout");
_Static_assert(offsetof(SscEncoder, in_mem) == 300, "encoder layout");

const SscMode *ssc_custom_mode_create(int fs, int frame_size, int *err) {
    (void)frame_size; /* the blob ignores it: both modes are fixed at 864 */
    if (err) *err = 0;
    if (fs == 44100 || fs == 48000) return &ssc_mode_48k;
    if (fs == 96000) return &ssc_mode_96k;
    if (err) *err = -1;
    return NULL;
}

static int state_size(const SscMode *m, int channels) {
    return (m->nbEBands * 6 + m->overlap * 4 + 4 * SSC_COMBFILTER_MAXPERIOD) * channels + 300;
}

int ssc_encoder_get_size(int channels, int fs) {
    const SscMode *m = ssc_custom_mode_create(fs, SSC_FRAME_SIZE, NULL);
    return m ? state_size(m, channels) : 0;
}

int ssc_encoder_init(SscEncoder *st, int fs, int channels, int bit_depth) {
    const SscMode *m = ssc_custom_mode_create(fs, SSC_FRAME_SIZE, NULL);
    int ret;
    if (channels > 2) return -1;  /* blob: -1, and it touches st below anyway */
    if (!st || !m) return -7;
    memset(st, 0, state_size(m, channels));
    st->mode = m;
    st->overlap = m->overlap;
    st->channels = channels;
    st->end = m->effEBands;
    st->f18 = -1;
    st->f20 = 2;
    st->f24 = 1;
    st->f28 = 256;
    ret = 0;
    st->fs_mode = fs == 48000 ? 44100 : fs;
    st->fs = fs;
    st->bit_depth = bit_depth;
    st->frame_counter = 0;
    st->hdr_low_bits = 1;
    /* TODO(phase 4): previous_uhq_index = 0; SoundBooster_DRC_Init(fs, channels);
     * SoundBooster_DRC_SetPar(1, 0x7b8e, 0, 50000, 0). */
    return ret;
}

SscEncoder *ssc_encoder_create(int fs, int channels, int bit_depth, int *err) {
    const SscMode *m = ssc_custom_mode_create(fs, SSC_FRAME_SIZE, NULL);
    SscEncoder *st;
    int ret;
    if (!m) {
        if (err) *err = -1;
        return NULL;
    }
    st = (SscEncoder *)malloc(state_size(m, channels));
    if (!st) {
        if (err) *err = -7;
        return NULL;
    }
    ret = ssc_encoder_init(st, fs, channels, bit_depth);
    if (err) *err = ret;
    if (ret != 0) {
        free(st);
        return NULL;
    }
    return st;
}

void ssc_encoder_destroy(SscEncoder *st) { free(st); } /* blob: empty (leaks) */

/* Bitrate table from ssc_encode @0xd1d0..0xd47c. */
typedef struct {
    int32_t bitrate;
    uint8_t byte3;    /* (flags << 5) | rate index; flags may change later in the frame */
    uint8_t uhq;      /* header byte 1 carries the counter's high nibble */
    uint8_t wide;     /* no +3/128 budget boost */
    int32_t drc_gain; /* set_DRC_limit_gain() for 24-bit input */
} SscRate;

static const SscRate kRates[] = {
    {88000, 0xF0, 0, 0, 0x76F200},  {96000, 0xF1, 0, 0, 0x76F200},
    {128000, 0xF2, 0, 0, 0x78B400}, {192000, 0xF3, 0, 0, 0x7A9400},
    {229000, 0xF4, 0, 0, 0x7A9400}, {328000, 0xF5, 0, 1, 0x7B4C00},
    {256000, 0xF6, 0, 1, 0x79F800}, {291000, 0xE0, 1, 1, 0x7B4C00},
    {308000, 0xE1, 1, 1, 0x7B4C00}, {442000, 0xE2, 1, 1, 0x7B4C00},
    {584000, 0xE3, 1, 1, 0x7B4C00}, {886000, 0xE4, 1, 1, 0x7B4C00},
    {250000, 0xE5, 1, 1, 0x79F800}, {152000, 0xE6, 1, 1, 0x79F800},
};

static const SscRate *find_rate(int bitrate) {
    size_t i;
    for (i = 0; i < sizeof(kRates) / sizeof(kRates[0]); i++)
        if (kRates[i].bitrate == bitrate) return &kRates[i];
    return NULL;
}

int ssc_encode(SscEncoder *st, const int32_t *pcm, int frame_size, uint8_t *out, int bitrate) {
    const SscRate *rate = find_rate(bitrate);
    int wide = rate ? rate->wide : 0;
    int uhq = rate ? rate->uhq : 0;
    int n, budget;
    ec_enc enc;

    /* Header bytes 0..3 (blob writes them before checking pcm). */
    st->end = st->mode->nbEBands;
    st->bitrate = bitrate;
    out[0] = 0xFF;
    out[1] = 0xEE;
    out[3] = rate ? rate->byte3 : 0xF3; /* unknown rate: 0xF3, no DRC gain update */
    out[2] = (uint8_t)((st->frame_counter << 4) | (st->hdr_low_bits & 3));
    if (uhq) out[1] = (uint8_t)(0xE0 | ((st->frame_counter >> 4) & 0xF));
    /* TODO(phase 4): set_DRC_limit_gain(rate->drc_gain) (24-bit; other depths differ). */

    /* Byte budget: the 44.1/48 kHz mode counts at Fs = 44100. */
    n = st->bitrate * frame_size / (st->fs_mode * 8);
    if (!wide) n += (n * 3) >> 7;
    n |= 1;
    budget = n - 1;
    ec_enc_init(&enc, out + SSC_HEADER_BYTES, budget);

    /* TODO(phase 3/4): Biquad + DRC on the input, then the CELT pipeline. */
    ec_enc_shrink(&enc, budget);
    if (!pcm || n < 3) return -1;

    ec_enc_done(&enc);
    st->frame_counter = (uint16_t)(st->frame_counter + 1 == 256 ? 0 : st->frame_counter + 1);
    return enc.error ? -3 : budget + SSC_HEADER_BYTES;
}
