/* Thin exported wrappers around libopus CELT internals (FIXED_POINT build),
 * so Python can call the reference next to the blob and diff the results.
 * Built per opus version by build_ref.py into ref_<tag>.dll. */
#include <stdint.h>
#include <string.h>

#include "arch.h"
#include "bands.h"
#include "entcode.h"
#include "entenc.h"
#include "laplace.h"
#include "mathops.h"

#define EXPORT __declspec(dllexport)

EXPORT int ref_ec_ilog(uint32_t v) { return EC_ILOG(v); }
EXPORT int32_t ref_celt_rcp(int32_t x) { return celt_rcp(x); }
EXPORT int32_t ref_celt_sqrt(int32_t x) { return celt_sqrt(x); }
EXPORT int32_t ref_celt_rsqrt_norm(int32_t x) { return celt_rsqrt_norm(x); }
EXPORT int32_t ref_celt_cos_norm(int32_t x) { return celt_cos_norm(x); }
EXPORT int32_t ref_frac_div32(int32_t a, int32_t b) { return frac_div32(a, b); }
EXPORT uint32_t ref_lcg_rand(uint32_t s) { return celt_lcg_rand(s); }
EXPORT void ref_haar1(int16_t *x, int n0, int stride) { haar1(x, n0, stride); }

/* Range-coder script. Each op is 4 ints: kind, a, b, c.
 *   0 ec_encode(a,b,c)        1 ec_encode_bin(a,b,c)   2 ec_enc_bit_logp(a,b)
 *   3 ec_enc_icdf(a, icdf[b..], c)  (icdf table index b into a fixed table)
 *   4 ec_enc_uint(a,b)        5 ec_enc_bits(a,b)       6 ec_laplace_encode(&a,b,c)
 * Returns ec.error; buf receives the finished stream (ec_enc_done). */
static const unsigned char kIcdf[3][8] = {
    {25, 23, 2, 0},            /* trim-like */
    {2, 1, 0},                 /* spread-like */
    {255 - 128, 0},
};

EXPORT int ref_ec_script(uint8_t *buf, int size, const int *ops, int nops, int *tell_out) {
    ec_enc enc;
    int i;
    ec_enc_init(&enc, buf, size);
    for (i = 0; i < nops; i++) {
        const int *op = ops + 4 * i;
        int v;
        switch (op[0]) {
        case 0: ec_encode(&enc, op[1], op[2], op[3]); break;
        case 1: ec_encode_bin(&enc, op[1], op[2], op[3]); break;
        case 2: ec_enc_bit_logp(&enc, op[1], op[2]); break;
        case 3: ec_enc_icdf(&enc, op[1], kIcdf[op[2]], op[3]); break;
        case 4: ec_enc_uint(&enc, op[1], op[2]); break;
        case 5: ec_enc_bits(&enc, op[1], op[2]); break;
        case 6: v = op[1]; ec_laplace_encode(&enc, &v, op[2], op[3]); break;
        }
        if (tell_out) tell_out[i] = ec_tell_frac(&enc);
    }
    ec_enc_done(&enc);
    return enc.error;
}
