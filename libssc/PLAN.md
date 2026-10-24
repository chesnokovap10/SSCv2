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
Сборка MinGW gcc (как весь SSCv2 через cgo), без внешних зависимостей.
Тестовый стенд: сравнение с оракулом.

### Фаза 3 — Бит-точность по этапам

Переносим по порядку цепочки `ssc_encode`; добавки Samsung — там, где они стоят
в цепочке (отдельной фазы для них нет). Каждая функция проверяется
`test/replay.py` (реальные вызовы из блоба), каждая стадия — `test/stages.py`
(контрольные точки после каждого кадра). Подэтапы, после каждого — пауза:

- **3a** ✅ вход: Biquad, powercalc, CalculateLimitGain, DRC (SoundBooster).
- **3b** pitch: `pitch_downsample`, `_ssc_autocorr`, `_ssc_lpc`, xcorr,
  `find_best_pitch`, `pitch_search`, `remove_doubling`; префильтр `comb_filter`
  и память префильтра в состоянии.
- **3c** MDCT/FFT (32-бит), `normal_headroom` / `uhq_headroom`.
- **3d** энергии и решения: `compute_band_energies`, `amp2Log2`,
  `patch_transient_decision(_temporal)`, `compute_band_energies_for_lastband`,
  `tone_detect`, `normalise_bands`, `last_band_info_calc`.
- **3e** coarse/fine энергия, `spreading_decision`, tf, `compute_allocation`.
- **3f** `quant_all_bands` (PVQ, стерео, cwrs), `quant_energy_finalise`,
  флаги заголовка. Критерий фазы: голдены и корпус `test/signals.py` совпадают
  байт в байт.

### Фаза 4 — Полная проверка

Все 14 битрейтов, длинные прогоны (счётчик кадров переходит через 256),
неизвестные битрейты, крайние сигналы (клиппинг, INT_MIN, DC).

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

- 2026-10-24 — **фаза 2 готова.** Каркас `libssc/src`, стенд-двойник
  `libssc/test/twin.py`: **18/18 PASS**.

### Итоги фазы 2

**Инструменты.** JDK 21.0.12.1 (Microsoft) + Ghidra 12.1.4 портативно в
`D:\2\tools` (SHA-256 сверены). `research/ghidra/decompile.ps1` → 86 функций в
`research/decomp/*.c` (`ssc_encode` — 3800 строк псевдо-C). Опознаны 11
внутренних функций без имён (`quant_partition`, `compute_theta`,
`intensity_stereo`, `quant_coarse_energy_impl`, `find_best_pitch`, бабочки FFT).

**База — Opus 1.1.5**, а не 1.3.1: у Samsung в состоянии энкодера три массива
энергий на канал (в 1.2 добавлен `energyError`), а `spreading_decision` без
`spread_weight` (добавлен в 1.3).

**libssc = ABI-двойник блоба.** Те же имена функций, сигнатуры и раскладки
структур (режим 136 байт, `ec_ctx`, состояние энкодера: заголовок 300 байт +
массивы на канал), смещения закреплены `_Static_assert`. Поэтому стенд даёт
обеим сторонам одинаковую память и сравнивает результат побайтно.
- `src/opus/` — файлы Opus 1.1.5 (range coder, Laplace, математика, cwrs) без
  изменений, кроме патча ec24 в `mfrngcod.h`. Лицензия Opus — `src/opus/COPYING`.
- `src/ssc_mode.h`, `src/ssc_tables.c` — оба режима и все таблицы
  (генерируется `tools/gen_tables.py` из `research/tables.json`).
- `src/ssc_encoder.{h,c}` — `ssc_custom_mode_create`, `ssc_encoder_get_size/
  init/create/destroy`, `ssc_encode`: заголовок, бюджет, счётчик кадров —
  бит-точно; полезной нагрузки пока нет (range coder завершается пустым).
- `src/ssc_twin.c` — функции под именами блоба (`ssc_rcp`, `ec_ilog`, …) и
  `haar1` в варианте Samsung.
- `build.py` → `build/libssc.dll` (gcc `-Wall` без предупреждений).

**Стенд-двойник** (`test/twin.py`): режимы со всеми таблицами; 7 функций
математики; `haar1`; range coder на случайных сценариях; состояние после
`ssc_encoder_init` (48k/96k) байт в байт; `ssc_encode` — заголовок и длина на
всех 96 кадрах голденов. Полезная нагрузка совпадает на ~0,4 % байт (случайно).

**Исправлено попутно:** в тесте `haar1` аргумент `N0` передавался как общая
длина (это длина на один stride) — функции писали за буфер. Вывод «Samsung
округляет иначе» после исправления подтвердился.

**Открыто для фазы 3:** MDCT и FFT у Samsung 32-битные (окно, trig и данные
int32, умножения Q31) — переносить с декомпиляции, а не из Opus. Порядок
переноса — по цепочке `ssc_encode`, каждая функция сразу проверяется двойником.

- 2026-10-24 — **фаза 3, подэтап 3a готов** (вход до CELT).

### Итоги 3a

**Что делает вход у Samsung** (`ssc_encode` @0xd504..0xd688):
1. `Biquad_Narrow_int2int_stereo` фильтрует копию входа в глобальный
   `_pcmpower` (коэффициенты Q28: `coeffs96andbelow` для битрейтов ≤96k и всех
   «широких»/UHQ, иначе `coeffs`). 64-битный аккумулятор, остаток переносится
   между сэмплами (внутри блока без знака, в состоянии — со знаком), обратная
   связь хранится как `y<<3`, выход `y>>4`. Состояние — 10×int64 в `st+0xd8`.
2. `powercalc` — Σ((x²>>16)>>1) по обоим каналам, `>>9`, для фильтрованного и
   исходного сигнала; `CalculateLimitGain(p_filt, p_rest, bitrate, fs)` —
   порог лимитера по доле мощности (для «узких» битрейтов `p_rest = p_in−p_filt`),
   `<<8` для 24-битного входа.
3. `SoundBooster_DRC_Exe` — пиковый лимитер «SoundBooster_DRC_classic v1.0,
   2019.12.05» **на месте во входном PCM**, 8 блоков по 108 кадров: если больше
   24 сэмплов выше порога, цель = порог·2³¹/пик; сглаживание Q22 (атака 0,
   отпускание 0x3ca4a1 / 0x3e6f79 для 96k); линейная рампа усиления по кадрам.
   Состояние — глобальная структура `drc_struct` (24 байта).

**Код:** `src/ssc_drc.{h,c}` (те же имена и глобалы, что в блобе),
`ssc_encoder.c`: `preprocess()`, DRC init в `ssc_encoder_init`, таблица усилений
для 16/24 бит. `ssc_encode` теперь принимает изменяемый PCM (как блоб).

**Новые стенды:**
- `test/signals.py` — 7 детерминированных сигналов (golden, тишина, шум,
  громкий/клиппинг, свип, разные каналы, щелчки) × 6 профилей.
- `test/replay.py` — записывает реальные вызовы функции в блобе (вход, выход,
  глобалы) и повторяет их на libssc. 5/5 функций, 3528 вызовов совпали;
  DRC реально меняет сигнал в 1440 из 2016 вызовов, `CalculateLimitGain`
  прошёл 7 разных веток.
- `test/stages.py` — оба энкодера покадрово, контрольные точки: PCM после DRC,
  `_pcmpower`, `drc_struct`, состояние biquad, заголовок (кроме флагов CELT),
  длина — **совпадают на 504/504 кадрах**. Флаги заголовка и полезная
  нагрузка — `PEND` до 3f.

**Заметка на фазу 5:** состояние DRC и `_pcmpower` — глобалы процесса, как у
блоба; для нескольких потоков в одном процессе их надо перенести в `SscEncoder`.
