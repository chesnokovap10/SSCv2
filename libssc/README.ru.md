# libssc

[English](README.md) · **Русский**

Своя реализация энкодера Samsung Scalable Codec (SSC), **бит-точная** относительно
`libScalable_Encoder.so` из текущей прошивки телефона (clang 14, NDK r25). C99, fixed-point,
на основе CELT из Opus 1.1.5. В SSCv2 подключается через cgo-пакет `internal/codec/ssc`.
Только для личного использования. План и итоги фаз: [PLAN.ru.md](PLAN.ru.md).

## Что внутри

| Путь | Что |
|---|---|
| `src/` | **сама библиотека**: `ssc_*.c` — наш код, `src/opus/` — Opus 1.1.5 + патчи (`PATCHES.md`, лицензия `COPYING`) |
| `src/ssc_names.h` | имена блоба (`ssc_quant_all_bands`, `ssc_ec_encode`, …) для всех файлов (`-include` в `build.py`, `#include` в обёртках cgo) |
| `ref/libScalable_Encoder.so` | блоб Samsung из прошивки (aarch64), только для сверки |
| `ref/libbluetooth_jni.so` | Bluetooth-стек телефона (`com.android.bt.apex`): как телефон вызывает энкодер, выбирает битрейт и пакует кадры |
| `oracle/ssc_oracle.py` | эталон: блоб под Unicorn прямо в Windows + трассировка вызовов |
| `testdata/*.golden` | 6 профилей × 16 кадров, замороженный вывод блоба |
| `test/` | стенды сверки (ниже) |
| `tools/gen_tables.py` | `research/tables.json` → `src/ssc_tables.c` |
| `research/` | реверс: дизассемблер, таблицы режимов, модель заголовка, дифф-стенд с Opus, декомпиляция Ghidra (`decomp/` — энкодер, `decomp_bt/` — SSC-часть BT-стека) |

libssc — **ABI-двойник** блоба: те же имена функций, сигнатуры и раскладки структур (режим,
`ec_ctx`, состояние энкодера, `SscAlloc`), поэтому любую функцию можно вызвать с обеих сторон
на одной и той же памяти и сравнить побайтно. Как у блоба, состояние DRC и рабочие буферы —
глобалы процесса: одновременно открыт один энкодер.

## API

```c
SscEncoder *ssc_encoder_create(int rate, int channels, int bits, int *err); // 44100|48000|96000, 2, 16|24
int ssc_encode(SscEncoder *st, int32_t *pcm, int frame, uint8_t *out, int bitrate); // pcm меняется (DRC)
void ssc_encoder_destroy(SscEncoder *st);
```

* Кадр — 864 сэмпла на канал (18 мс на 48 кГц, 9 мс на 96 кГц), вход int32 в шкале 2^23 (24 бит).
* Битрейты: 48 кГц — 88/96/128/192/229/256/328k; UHQ 96 кГц — 152/250/291/308/442/584/886k.
  Кодер CBR: размер кадра = `FrameBytes(rate, bitrate)` в `internal/codec/ssc`.

## Сборка и проверка

```powershell
py -3.14 libssc\build.py          # MinGW gcc -> libssc\build\libssc.dll
py -3.14 libssc\test\twin.py      # 17 проверок против блоба, включая голдены целиком
py -3.14 libssc\test\corpus.py    # кадры целиком: 14 битрейтов × 10 сигналов
py -3.14 libssc\test\edge.py      # 216 крайних сценариев (--only NAME, --list)
py -3.14 libssc\test\replay.py    # функции libssc на реальных вызовах из блоба
py -3.14 libssc\test\stages.py    # покадровые контрольные точки по цепочке
# replay.py и stages.py: --rates all — все 14 битрейтов вместо 6 профилей

go test ./internal/codec/ssc      # cgo-сборка против хэшей блоба (testdata/oracle.txt)
py -3.14 libssc\test\cgo_ref.py   # переснять эти хэши
```

| Стенд | Что сравнивает |
|---|---|
| `test/twin.py` | функции математики, range coder, режимы, состояние после init, кадры голденов |
| `test/replay.py` | записанные вызовы функции блоба (вход, выход, глобалы) → та же функция libssc |
| `test/stages.py` | оба энкодера покадрово: контрольные точки, кадр, состояние и общие буферы |
| `test/corpus.py` | кадры целиком на всех битрейтах и сигналах `test/signals.py` |
| `test/edge.py` | длинные прогоны, неизвестные и меняющиеся битрейты, крайние сигналы, 16 бит, 44,1 кГц |
| `test/cgo_ref.py` | хэши кадров блоба для Go-теста |

После добавления файлов в `src/` перегенерировать обёртки: `go run ./tools/genwrap`.

## Оракул

`oracle/ssc_oracle.py` загружает блоб (aarch64 ELF) в Unicorn: свои релокации, 8 заглушек
libc, stack guard. Это эталон для пошаговой сверки.

```powershell
py -3.14 -m pip install unicorn          # один раз (проверено на 2.1.4)
py -3.14 libssc\oracle\ssc_oracle.py check-golden
py -3.14 libssc\oracle\ssc_oracle.py make-golden   # переснять голдены
py -3.14 libssc\oracle\ssc_oracle.py trace --bitrate 229000 --frame 1
py -3.14 libssc\oracle\ssc_oracle.py trace --rate 96000 --bitrate 584000 --max-depth 1
```

```python
from ssc_oracle import Oracle, golden_pcm
o = Oracle(trace=True).open(48000, 2, 229000)
o.probes_exit["ssc_compute_band_energies"] = lambda o, rec: print(rec.args[:4], rec.ret)
frame = o.encode(golden_pcm(0x5A5C2026, 0, 48000))
for rec in o.calls: ...                               # дерево вызовов последнего кадра
```

Один `Oracle` — один «процесс» (состояние блоба в `.bss`); `malloc` — bump-аллокатор,
`free` ничего не делает.

## research/

```powershell
py -3.14 -m pip install capstone
py -3.14 libssc\research\disasm.py ssc_encoder_create   # дизассемблер с символами
py -3.14 libssc\research\dump_mode.py [--json F]        # режимы и таблицы
py -3.14 libssc\research\header_model.py                # модель заголовка против голденов
# дифф-стенд: Opus (git clone xiph/opus, checkout v1.1.5) + MinGW gcc
py -3.14 libssc\research\difftest\build_ref.py <opus-dir> --tag v1.1.5 --patch ec24
py -3.14 libssc\research\difftest\difftest.py
# декомпиляция (JDK 21 + Ghidra портативно в D:\2\tools)
pwsh libssc\research\ghidra\decompile.ps1      # -> research\decomp\*.c
pwsh libssc\research\ghidra\decompile_bt.ps1   # BT-стек телефона -> research\decomp_bt (~15 мин)
```

В `libssc/` нет `.go`-файлов, `go build` каталог не трогает.
