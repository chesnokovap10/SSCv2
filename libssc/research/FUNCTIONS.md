# Карта функций блоба ↔ libopus CELT

Блоб: `libssc/ref/libScalable_Encoder.so`, собран Android NDK r20 (clang 8.0.7,
API 28) — примерно 2019–2020. База — **libopus 1.1.x** CELT fixed-point (берём
1.1.5): в состоянии энкодера три массива энергий на канал (`energyError` появился
в 1.2), `spreading_decision` без `spread_weight` (появился в 1.3). Листовые функции
одинаковы в 1.1.5 / 1.2.1 / 1.3.1.

Декомпиляция Ghidra 12.1.4: `research/decomp/<функция>.c` (пересобрать:
`research/ghidra/decompile.ps1`).

Статусы:
- **✅ = Opus** — дифф-тест (`difftest/`) совпадает с libopus на случайных входах
- **🔶 = Opus + патч** — совпадает после именованного патча из `build_ref.py`
- **❌ отличается** — дифф-тест расходится, причина ниже
- **🔸 изменена (статика)** — видно по дизассемблеру, дифф-теста пока нет
- **⬜ не проверено**
- **🆕 Samsung** — в Opus аналога нет

## Математика и утилиты

| Блоб | Opus | Размер | Статус | Заметки |
|---|---|---|---|---|
| `ec_ilog` | `EC_ILOG` / `ec_ilog` | 108 | ✅ | |
| `ssc_rcp` | `celt_rcp` | 196 | ✅ | |
| `ssc_sqrt` | `celt_sqrt` | 232 | ✅ | |
| `ssc_rsqrt_norm` | `celt_rsqrt_norm` | 120 | ✅ | |
| `ssc_cos_norm` | `celt_cos_norm` | 280 | ✅ | |
| `frac_div32` | `frac_div32` | 416 | ✅ | |
| `ssc_lcg_rand` | `celt_lcg_rand` | 24 | ✅ | |
| `smull32_x86` | — | 12 | 🆕 | 32×32→64 умножение |
| `SSC_COPY8/16/32`, `SSC_CLEAR` | `OPUS_COPY` / `OPUS_CLEAR` | 36–48 | ⬜ | макросы стали функциями |

## Range coder

| Блоб | Opus | Размер | Статус | Заметки |
|---|---|---|---|---|
| `ec_enc_init` | `ec_enc_init` | 44 | 🔶 ec24 | `ec_ctx` поле в поле как в Opus |
| `ec_encode` | `ec_encode` | 320 | 🔶 ec24 | |
| `ec_encode_bin` | `ec_encode_bin` | 328 | 🔶 ec24 | |
| `ec_enc_bit_logp` | `ec_enc_bit_logp` | 292 | 🔶 ec24 | |
| `ec_enc_icdf` | `ec_enc_icdf` | 336 | 🔶 ec24 | |
| `ec_enc_uint` | `ec_enc_uint` | 300 | 🔶 ec24 | |
| `ec_enc_bits` | `ec_enc_bits` | 168 | ✅ | сырые биты не зависят от EC_CODE_BITS |
| `ec_enc_done` | `ec_enc_done` | 816 | 🔶 ec24 | |
| `ec_tell_frac` | `ec_tell_frac` | 180 | 🔶 ec24 | сверяется после каждой операции |
| `ec_laplace_encode` | `ec_laplace_encode` | 240 | 🔶 ec24 | |
| `ec_enc_patch_initial_bits` | `ec_enc_patch_initial_bits` | 148 | ⬜ | |
| `ec_enc_shrink` | `ec_enc_shrink` | 64 | ⬜ | |
| `encode_pulses` | `encode_pulses` (cwrs.c) | 240 | ⬜ | |

**Патч ec24:** `mfrngcod.h` `EC_CODE_BITS 32 → 24` (BOT `0x8000`, SHIFT 15,
перенос по биту 23). Следствие: `ft` у `ec_encode` не больше 2^15.

## Полосы, квантование, распределение

| Блоб | Opus | Размер | Статус | Заметки |
|---|---|---|---|---|
| `haar1` | `haar1` | 144 | ❌ → в libssc (twin ✅) | Samsung: `(a·46340)>>16 ± (b·46340)>>16` (усечение каждого); Opus: `PSHR32(a·23170 ± b·23170, 15)` (округление суммы) |
| `inv_haar1` | — | 144 | 🆕 | обратное преобразование (в Opus только у декодера через haar1) |
| `hysteresis_decision` | `hysteresis_decision` | 136 | ⬜ | |
| `compute_band_energies` | `compute_band_energies` | 1152 | ⬜ | раскладка mode другая |
| `compute_band_energies_for_lastband` | — | 1240 | 🆕 | |
| `normalise_bands` | `normalise_bands` | 1088 | ⬜ | |
| `spreading_decision` | `spreading_decision` | 808 | 🔸 | цикл начинается с полосы 8, `end < 9 →` выход; без `spread_weight` (как в ≤1.2) |
| `quant_all_bands` | `quant_all_bands` (+`quant_band*`) | 2088 | ⬜ | |
| `alg_quant` | `alg_quant` | 4300 | ⬜ | |
| `renormalise_vector` | `renormalise_vector` | 480 | ⬜ | |
| `stereo_itheta` | `stereo_itheta` | 936 | ⬜ | |
| `quant_coarse_energy` | `quant_coarse_energy` | 1164 | ⬜ | |
| `quant_fine_energy` | `quant_fine_energy` | 296 | ⬜ | |
| `quant_energy_finalise` | `quant_energy_finalise` | 424 | ⬜ | |
| `amp2Log2` | `amp2Log2` | 664 | ⬜ | |
| `compute_allocation` | `clt_compute_allocation` | 3844 | ⬜ | две таблицы распределения (11×22 каждая) |
| `init_caps` | `init_caps` | 96 | 🔸 | caps — int32 на полосу, без измерений LM/C |

## Анализ: MDCT, pitch, LPC

| Блоб | Opus | Размер | Статус | Заметки |
|---|---|---|---|---|
| `ssc_mdct_forward` | `clt_mdct_forward` | 1000 | ⬜ | N=1728, окно int32 Q31 (в Opus int16) |
| `ssc_fft` | `opus_fft` | 904 | ⬜ | 2 состояния: nfft 144 и 18; twiddles 432 × (i32,i32) |
| `ssc_preemphasis` | `celt_preemphasis` | 220 | ⬜ | коэффициенты не в mode |
| `pitch_downsample` | `pitch_downsample` | 1152 | ⬜ | |
| `pitch_search` | `pitch_search` | 1356 | ⬜ | |
| `remove_doubling` | `remove_doubling` | 2204 | ⬜ | |
| `ssc_pitch_xcorr_c1/c2`, `dual_inner_prod` | `celt_pitch_xcorr`, `dual_inner_prod` | asm | ⬜ | секция `test`, ручной asm |
| `_ssc_lpc` | `_celt_lpc` | 372 | ⬜ | |
| `_ssc_autocorr` | `_celt_autocorr` | 632 | ⬜ | |
| `comb_filter` | `comb_filter` | 2404 | ⬜ | |
| `tone_detect` | — (в Opus 1.6 другая) | 480 | 🆕 | блоб старше Opus 1.6 |
| `patch_transient_decision` | `patch_transient_decision` (static) | 668 | ⬜ | |
| `patch_transient_decision_temporal` | — | 1468 | 🆕 | |

## Добавки Samsung и верхний уровень

| Блоб | Opus | Размер | Статус | Заметки |
|---|---|---|---|---|
| `ssc_custom_mode_create` | `opus_custom_mode_create` | 92 | 🔸 | только 2 статических режима: 44,1/48k → `0x28a18` (Fs=44100), 96k → `0x28aa0` |
| `ssc_encoder_get_size` | `celt_encoder_get_size` | 76 | 🔸 | `(overlap·4 + nb·6 + 4096)·C + 300` |
| `ssc_encoder_init` | `celt_encoder_init` | 364 | ⬜ | |
| `ssc_encoder_create` | `opus_custom_encoder_create` | 176 | 🔸 | malloc + init |
| `ssc_encoder_destroy` | `opus_custom_encoder_destroy` | 4 | ⬜ | пустая (`ret`) |
| `ssc_encode` | `celt_encode_with_ec` | 17984 | 🔸 | заголовок/бюджет — см. `header_model.py` |
| `normal_headroom`, `uhq_headroom`, `headroom_process` | — | 1028/2056/12 | 🆕 | после MDCT |
| `last_band_info_calc` | — | 80 | 🆕 | |
| `Biquad_Narrow_int2int_stereo` | — | 252 | 🆕 | коэф. `coeffs` (48k) / `coeffs96andbelow`, вероятно Q28 |
| `powercalc`, `CalculateLimitGain` | — | 228/492 | 🆕 | |
| `SoundBooster_DRC_*`, `set_DRC_limit_gain` | — | | 🆕 | лимитер на входе, 8 блоков по 108 |

## Режимы (`tables.json`)

- `nbEBands=22`, `effEBands=21`, `overlap=108`, 8 коротких MDCT по 108 (LM=3), N=1728.
- 48k: `eBands = [0..8,10,12,14,16,20,24,28,34,40,48,60,72,84,102]` — как
  `eband5ms` Opus до 60, дальше свои полосы до 102 из 108 бинов.
- 96k: `eBands = [0..12,14,16,20,24,30,36,54,72,90,108]`.
- `logN` 48k совпадает с Opus `logN400` (+ полоса 21 = 34).
- `allocVectors` — своя таблица 11×22 (не `band_allocation` Opus), общая для режимов;
  `allocVectors2` — вторая таблица 11×22, своя у каждого режима.
- Окно — int32 Q31 (108 значений), общее; trig/twiddles общие.

## Внутренние функции без имён (Ghidra `FUN_*`)

| Ghidra | Размер | Opus (по вызовам) |
|---|---|---|
| `FUN_00104310` | 1072 | `quant_band` / `quant_band_stereo` (вызывает `quant_partition`) |
| `FUN_00104740` | 1196 | `quant_partition` (рекурсия, `alg_quant`) |
| `FUN_00104bec` | 784 | `compute_theta` (`stereo_itheta`, `ec_encode`, `ec_enc_uint`) |
| `FUN_00104efc` | 480 | `intensity_stereo` (`ssc_sqrt`) |
| `FUN_00106180`, `FUN_0010644c`, `FUN_0010664c` | 716/512/468 | бабочки/работа FFT (`kf_bfly*`, `kf_work`) |
| `FUN_00107ddc` | 1036 | `find_best_pitch` |
| `FUN_00108f10` | 1216 | `quant_coarse_energy_impl` (`ec_laplace_encode`, `ec_enc_icdf`) |
| `FUN_001023c0`, `FUN_0010282c`, `entry` | — | PLT / CRT |
