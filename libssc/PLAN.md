# libssc — план: своя библиотека SSC (энкодер + декодер)

Статус: **в работе**, начато 2026-10-24.

## Решения

| Вопрос | Решение |
|--------|---------|
| Цель | **Бит-точное** совпадение с `libScalable_Encoder.so` на всех профилях |
| Распространение | Только приватно, под наше железо (Buds3 FE + наши донглы). Публичного релиза нет |
| Где живёт | `libssc/` в SSCv2 (Go-трей). Подключение — cgo-пакет `internal/codec/ssc`, точка входа `internal/engine/codecs.go` → `newSSC` |
| Декодер | Нужен (фаза 6) |
| Темп | По одной фазе. После каждой — разбор результатов, потом следующая |

## Исходная находка

SSC — это доработанный **CELT из libopus** (fixed-point):

- Экспорты блоба совпадают по именам с CELT: `quant_all_bands`, `alg_quant`,
  `compute_allocation`, `quant_coarse_energy`, `quant_fine_energy`, `ec_enc_*`,
  `spreading_decision`, `pitch_search`, `remove_doubling`, `comb_filter`,
  `stereo_itheta`, `haar1`, `renormalise_vector`, `ec_laplace_encode`.
- `eMeans` (25 байт) байт в байт равна fixed-point таблице libopus.
- `tf_select_table` (8 байт) = строка LM=3 из libopus.
- Кадр 864 = 8 × 108 → кастомный режим CELT (8 коротких MDCT по 108).
- Добавки Samsung: `normal_headroom` / `uhq_headroom`, SoundBooster DRC,
  `tone_detect`, `patch_transient_decision(_temporal)`, `hysteresis_decision`,
  обрезка полосы (`cutoff_start_index`, `last_band_info_calc`), UHQ 96 кГц.
- `ssc_encode` — монолит 18 КБ, основная логика Samsung заинлайнена туда.

Заголовок кадра (по голденам): `FF EE` (48 кГц) / `FF E0` (96 кГц), затем
байт со счётчиком кадров в старшем полубайте, затем байт режима/битрейта,
дальше полезная нагрузка range coder'а.

Размер кадра: 96 кГц — битрейт × 9 мс (+3 байта); 48 кГц — битрейт × **20** мс
(+4), хотя кадр длится 18 мс. → Разобрано в фазе 1: режим 48k считает бюджет
от Fs=44100 (см. журнал).

## Фазы

### Фаза 0 — Эталон под рукой

Свой запуск блоба на Unicorn (aarch64), без WSL2/qemu и Qiling. Блобу нужны
только 8 импортов libc (`malloc`, `free`, `memcpy`, `memset`,
`__stack_chk_fail`, `__cxa_finalize`, `__cxa_atexit`, `__register_atfork`).

Результат:
- `libssc/oracle/` — Python-обвязка: загрузка ELF, релокации, заглушки libc,
  вызов `ssc_encoder_*` / `ssc_encode` напрямую.
- Совпадение со всеми 6 голденами байт в байт.
- Трассировка: хуки на входы/выходы экспортируемых функций, снятие аргументов
  и буферов — основа для пошаговой сверки в фазе 3.

### Фаза 1 — Карта отличий от CELT

Каждой функции блоба — пара в libopus и пометка: совпадает / изменена / новая.
Восстановить параметры режима (полосы, overlap, окно `win_square`, LM),
формат заголовка, формулу «битрейт → байты». Расширить корпус сигналов
(музыка, тишина, транзиенты, свипы).

### Фаза 2 — Каркас `libssc`

C99, fixed-point, на основе CELT-энкодера libopus (BSD-3). API как у блоба.
Сборка MSVC, без внешних зависимостей. Тестовый стенд: сравнение с оракулом.

### Фаза 3 — Бит-точность по этапам

MDCT → энергии полос → coarse/fine energy → allocation → PVQ → range coder →
заголовок. Каждый этап сверяется с дампами оракула. Критерий: голдены и
расширенный корпус совпадают байт в байт.

### Фаза 4 — Добавки Samsung

headroom, DRC, tone detect, патч транзиентов, UHQ 96 кГц.

### Фаза 5 — Интеграция

cgo-пакет `internal/codec/ssc` (как `internal/codec/aac`), `newSSC` в
`internal/engine/codecs.go` вместо `ErrSSCNotReady`. SSC в A2DP: vendor
Samsung `0x00000075`, codec `0x0103` + байт capability — перенести из старого
`D:\2\SSC` (`btstack_transport.cpp`, `codec_policy.h`). Демона и WSL в SSCv2 нет и не будет.

### Фаза 6 — Декодер

На основе CELT-декодера libopus. Проверка: decode(libssc) ≈ исходный PCM,
сравнение с decode(blob-кадров). Позволяет оценивать качество без наушников.

## Журнал

- 2026-10-24 — план записан, начата фаза 0 (в `D:\2\SSC`, затем перенесено в SSCv2/libssc; блоб и голдены скопированы в `ref/` и `testdata/`).
- 2026-10-24 — **фаза 0 готова.** `libssc/oracle/ssc_oracle.py`: свой ELF-загрузчик
  на Unicorn 2.1.4 (129 релокаций трёх типов, 8 заглушек libc, stack guard через
  `tpidr_el0+0x28`). Все 6 голденов совпадают байт в байт, 96 кадров < 1 с.
  Трассировка: ~5400 вызовов экспортов на кадр, дерево вызовов + пробы на
  вход/выход. Отрицательный тест (испорченный байт в голдене) ловится.

### Наблюдения из первой трассировки (вход для фазы 1)

- **До CELT стоит препроцессинг Samsung:** `Biquad_Narrow_int2int_stereo`
  (коэффициенты `coeffs` для 48k / `coeffs96andbelow` для 96k) → `powercalc` ×2 →
  `CalculateLimitGain` → `SoundBooster_DRC_Exe` ×8 блоками по 108 сэмплов.
  Для бит-точности это нужно повторить в точности.
- Бюджет range coder'а на 48 кГц: `ec_enc_init(out+4, 572)` = 229000 × 20 мс / 8.
  Заголовок 4 байта, полезная нагрузка считается от 20 мс, а не от 18 мс.
- Цепочка внутри `ssc_encode` в целом как у `celt_encode_with_ec`: pitch
  (`pitch_downsample`/`pitch_search`/`remove_doubling`) → `comb_filter` ×2 →
  `ssc_mdct_forward` ×2 → `normal_headroom`/`uhq_headroom` →
  `compute_band_energies` → `amp2Log2` → `patch_transient_decision(_temporal)` →
  `compute_band_energies_for_lastband` → `tone_detect` → `normalise_bands` →
  `quant_coarse_energy` → `spreading_decision` → `compute_allocation` →
  `quant_fine_energy` → `quant_all_bands` → `quant_energy_finalise` → `ec_enc_done`.
- Структура режима (mode) — статические данные блоба (`0x28aa0` в
  `.data.rel.ro`), её можно прочитать напрямую. В 96k-трассе
  `compute_band_energies(..., 0x16)` → 22 полосы (в Opus 21).

- 2026-10-24 — **фаза 1 готова.** Всё в `libssc/research/`:
  [FUNCTIONS.md](research/FUNCTIONS.md) (карта 75 функций),
  `dump_mode.py` → `tables.json`, `header_model.py`, `disasm.py`, `difftest/`.

### Итоги фазы 1

**Блоб.** Android NDK r20, clang 8.0.7, API 28 → ~2019–2020. База — libopus CELT
fixed-point. `tone_detect` у Samsung своя (в Opus она появилась только в 1.6).
Листовые функции одинаковы в Opus 1.1.5/1.2.1/1.3.1; `spreading_decision` без
`spread_weight` → база скорее ≤1.2, но эта функция всё равно переписана.

**Режимы.** Два статических режима по 136 байт: `0x28a18` (Fs=**44100**,
используется для 44,1 и 48 кГц) и `0x28aa0` (96000). Раскладка своя: нет
`preemph[]` и `maxLM`, вторая таблица распределения 11×22, окно int32 Q31,
два FFT-состояния (144 и 18), caps int32 на полосу. 22 полосы, effEBands 21,
overlap 108, LM=3 (8×108), N=1728. Все таблицы — в `tables.json`.

**Заголовок и бюджет** (`header_model.py`, совпадает на всех 96 кадрах голденов):
- `FF`, затем `EE` (обычный) или `E0 | counter>>4` (UHQ), затем
  `counter<<4 | флаги`, затем `верх3<<5 | индекс битрейта`.
- 14 допустимых битрейтов: 48k — 88/96/128/192/229/256/328k (`F0..F6`),
  UHQ — 291/308/442/584/886/250/152k (`E0..E6`).
- `n = bitrate·864 / (Fs_mode·8)`; для «узких» (≤229k) `n += 3n>>7`;
  `n |= 1`; бюджет range coder'а `n−1`, кадр `4 + n−1`.
- Открыто: флаги в битах 2–3 байта 2 (в 192k/229k = `0b11`) и верхние 3 бита
  байта 3 — ставятся по ходу кодирования (около `0xe914` и `0xeb44`).

**Дифф-стенд** (`difftest/`): libopus собирается MinGW gcc в DLL с именованными
патчами, блоб вызывается через оракул, входы случайные.
- ✅ Совпадает с Opus: `ec_ilog`, `celt_rcp`, `celt_sqrt`, `celt_rsqrt_norm`,
  `celt_cos_norm`, `frac_div32`, `celt_lcg_rand`, `ec_enc_bits`.
- 🔶 Совпадает после патча **ec24** (`EC_CODE_BITS 32→24`): весь range coder —
  `ec_encode*`, `ec_enc_bit_logp`, `ec_enc_icdf`, `ec_enc_uint`,
  `ec_laplace_encode`, `ec_tell_frac`, `ec_enc_done`.
- ❌ `haar1`: Samsung усекает каждое слагаемое, Opus округляет сумму.

**Оракул:** `call(..., max_insns=N)` — защита от зацикливания (тайм-аут Unicorn
на Windows стоит ~15 мс на вызов, лимит инструкций — нет).

**Вывод для фазы 2:** основа libssc = Opus CELT fixed-point + патчи
(ec24, haar1, …) + таблицы Samsung + свой `ssc_encode`. Функции среднего
уровня проверяются тем же стендом по мере переноса — для этого стенду нужен
режим Samsung в формате Opus (собрать `OpusCustomMode` из `tables.json`).
