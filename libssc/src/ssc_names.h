/* libssc — symbol names of the Samsung blob.
 *
 * libScalable_Encoder.so exports most CELT functions with an `ssc_` prefix
 * (ssc_quant_all_bands, ssc_ec_encode, ...). libssc keeps the Opus names in
 * its sources (src/opus is vendored libopus) and is compiled with
 * `-include ssc_names.h`, so the exported symbols are the blob's names and the
 * test benches can call the same function in both. Keep this flag in the cgo
 * CFLAGS (phase 5).
 */
#ifndef SSC_NAMES_H
#define SSC_NAMES_H

/* range coder (entenc.c, laplace.c) */
#define ec_enc_init ssc_ec_enc_init
#define ec_encode ssc_ec_encode
#define ec_encode_bin ssc_ec_encode_bin
#define ec_enc_bit_logp ssc_ec_enc_bit_logp
#define ec_enc_icdf ssc_ec_enc_icdf
#define ec_enc_uint ssc_ec_enc_uint
#define ec_enc_bits ssc_ec_enc_bits
#define ec_enc_patch_initial_bits ssc_ec_enc_patch_initial_bits
#define ec_enc_shrink ssc_ec_enc_shrink
#define ec_enc_done ssc_ec_enc_done
#define ec_tell_frac ssc_ec_tell_frac
#define ec_laplace_encode ssc_ec_laplace_encode

/* math, cwrs */
#define frac_div32 ssc_frac_div32
#define encode_pulses ssc_encode_pulses

/* pitch, prefilter */
#define pitch_downsample ssc_pitch_downsample
#define pitch_search ssc_pitch_search
#define remove_doubling ssc_remove_doubling
#define comb_filter ssc_comb_filter

/* band analysis */
#define compute_band_energies ssc_compute_band_energies
#define compute_band_energies_for_lastband ssc_compute_band_energies_for_lastband
#define amp2Log2 ssc_amp2Log2
#define normalise_bands ssc_normalise_bands
#define patch_transient_decision ssc_patch_transient_decision
#define spreading_decision ssc_spreading_decision
#define hysteresis_decision ssc_hysteresis_decision
#define haar1 ssc_haar1

/* energy quantisation, allocation, PVQ */
#define quant_coarse_energy ssc_quant_coarse_energy
#define quant_fine_energy ssc_quant_fine_energy
#define quant_energy_finalise ssc_quant_energy_finalise
#define compute_allocation ssc_compute_allocation
#define quant_all_bands ssc_quant_all_bands
#define alg_quant ssc_alg_quant
#define stereo_itheta ssc_stereo_itheta

/* data */
#define eMeans ssc_eMeans_tmp
#define tf_select_table ssc_tf_select_table

#endif
