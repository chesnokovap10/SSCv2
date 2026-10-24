# libssc

Своя реализация Samsung Scalable Codec (SSC): энкодер и декодер, бит-точные
относительно `libScalable_Encoder.so` из текущей прошивки телефона. Только
приватное использование.
План и журнал: [PLAN.md](PLAN.md).

| Путь | Что |
|---|---|
| `oracle/` | эталон: оригинальный блоб под Unicorn + трассировка |
| `ref/libScalable_Encoder.so` | блоб Samsung из прошивки (aarch64, clang 14, sha256 `90c4c1cb…ce7`), только для сверки |
| `ref/libbluetooth_jni.so` | Bluetooth-стек телефона (из `com.android.bt.apex`): кто и как вызывает энкодер |
| `testdata/*.golden` | 6 профилей × 16 кадров, замороженный вывод блоба |
| `src/` | **сама библиотека** (C, fixed-point): `src/opus/` — Opus 1.1.5 + патч ec24, `ssc_*.c` — наш код |
| `test/twin.py` | стенд-двойник: libssc и блоб с одинаковыми входами, побайтное сравнение (в т.ч. кадры голденов целиком) |
| `test/replay.py` | реальные вызовы функции из блоба (вход/выход/глобалы) → та же функция libssc |
| `test/stages.py` | оба энкодера покадрово: контрольные точки по цепочке, кадр, состояние и общие буферы после кадра |
| `test/corpus.py` | кадры целиком: все 14 битрейтов × 10 сигналов |
| `test/edge.py` | фаза 4: длинные прогоны, неизвестные и меняющиеся битрейты, крайние сигналы, 16 бит, 44,1 кГц |
| `test/signals.py` | детерминированные тестовые сигналы × профили |
| `test/cgo_ref.py` | фаза 5: хэши кадров блоба для Go-теста `internal/codec/ssc` (cgo-сборка = блоб) |
| `tools/gen_tables.py` | `research/tables.json` → `src/ssc_tables.c` |
| `research/` | реверс: таблицы режимов, модель заголовка, дифф-стенд, декомпиляция; `decomp_bt/` — SSC-часть BT-стека телефона |

## Сборка и проверка

```powershell
py -3.14 libssc\build.py          # MinGW gcc -> libssc\build\libssc.dll
py -3.14 libssc\test\twin.py      # 17 проверок против блоба, включая голдены целиком
py -3.14 libssc\test\corpus.py    # кадры целиком, все битрейты и сигналы
py -3.14 libssc\test\edge.py      # 216 крайних сценариев (--only NAME, --list)
py -3.14 libssc\test\replay.py    # перенесённые функции на реальных вызовах
py -3.14 libssc\test\stages.py    # покадровые контрольные точки
# replay.py и stages.py: --rates all — все 14 битрейтов вместо 6 профилей
```

libssc — ABI-двойник блоба: те же имена функций, сигнатуры и раскладки
структур (режим, `ec_ctx`, состояние энкодера, `SscAlloc`), поэтому любую
функцию можно вызвать с обеих сторон на одной и той же памяти. Имена блоба
(`ssc_quant_all_bands`, `ssc_ec_encode`, …) даёт `src/ssc_names.h`, который
`build.py` подключает ко всем файлам (`-include`).

## research/

```powershell
py -3.14 -m pip install capstone                       # для disasm.py
py -3.14 libssc\research\disasm.py ssc_encoder_create   # дизассемблер с символами
py -3.14 libssc\research\dump_mode.py [--json F]        # режимы и таблицы
py -3.14 libssc\research\header_model.py                # модель заголовка vs голдены
# дифф-стенд: Opus (git clone xiph/opus, checkout v1.1.5) + MinGW gcc
py -3.14 libssc\research\difftest\build_ref.py <opus-dir> --tag v1.1.5 --patch ec24
py -3.14 libssc\research\difftest\difftest.py
# декомпиляция (JDK 21 + Ghidra портативно в D:\2\tools)
pwsh libssc\research\ghidra\decompile.ps1     # -> research\decomp\*.c
pwsh libssc\research\ghidra\decompile_bt.ps1  # BT-стек телефона, SSC-функции -> research\decomp_bt (~15 мин)
```

В каталогах нет `.go`-файлов, `go build` их не трогает. В приложение libssc
входит через cgo-пакет `internal/codec/ssc` (обёртки `zssc_*.c` от `tools/genwrap`):

```powershell
go test ./internal/codec/ssc        # 14 битрейтов против хэшей блоба (testdata/oracle.txt)
py -3.14 libssc\test\cgo_ref.py     # переснять хэши с блоба
```

## oracle/

`ssc_oracle.py` запускает оригинальный блоб (aarch64) под Unicorn прямо в
Windows, без WSL2 и Qiling. Это эталон для пошаговой сверки.

```powershell
py -3.14 -m pip install unicorn          # один раз (проверено на 2.1.4)
py -3.14 libssc\oracle\ssc_oracle.py check-golden
py -3.14 libssc\oracle\ssc_oracle.py make-golden   # переснять голдены с блоба
py -3.14 libssc\oracle\ssc_oracle.py trace --bitrate 229000 --frame 1
py -3.14 libssc\oracle\ssc_oracle.py trace --rate 96000 --bitrate 584000 --max-depth 1
```

Из Python:

```python
from ssc_oracle import Oracle, golden_pcm
o = Oracle(trace=True).open(48000, 2, 229000)
o.probes_exit["ssc_compute_band_energies"] = lambda o, rec: print(rec.args[:4], rec.ret)
frame = o.encode(golden_pcm(0x5A5C2026, 0, 48000))   # 864 x 2ch, int32, шкала 2^29
for rec in o.calls: ...                               # дерево вызовов последнего кадра
```

- Один `Oracle` — один «процесс»: блоб держит состояние энкодера в глобалах
  `.bss`, поэтому на каждый поток нужен новый экземпляр.
- Порядок вызовов повторяет `ssc_blob_helper.c` старого демона
  (get_size → init на warm-up состоянии → create → encode).
- `malloc` — bump-аллокатор по обнулённой памяти, `free` ничего не делает.
