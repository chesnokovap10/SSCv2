# libssc

Своя реализация Samsung Scalable Codec (SSC): энкодер и декодер, бит-точные
относительно `libScalable_Encoder.so`. Только приватное использование.
План и журнал: [PLAN.md](PLAN.md).

| Путь | Что |
|---|---|
| `oracle/` | эталон: оригинальный блоб под Unicorn + трассировка |
| `ref/libScalable_Encoder.so` | блоб Samsung (aarch64, sha256 `9248e264…b461`), только для сверки |
| `testdata/*.golden` | 6 профилей × 16 кадров, замороженный вывод блоба |
| `research/` | реверс: карта функций, таблицы режимов, модель заголовка, дифф-стенд |

## research/

```powershell
py -3.14 -m pip install capstone                       # для disasm.py
py -3.14 libssc\research\disasm.py ssc_encoder_create   # дизассемблер с символами
py -3.14 libssc\research\dump_mode.py [--json F]        # режимы и таблицы
py -3.14 libssc\research\header_model.py                # модель заголовка vs голдены
# дифф-стенд: Opus (git clone xiph/opus, checkout v1.3.1) + MinGW gcc
py -3.14 libssc\research\difftest\build_ref.py <opus-dir> --tag v1.3.1 --patch ec24
py -3.14 libssc\research\difftest\difftest.py
```

В каталогах нет `.go`-файлов, `go build` их не трогает.

## oracle/

`ssc_oracle.py` запускает оригинальный блоб (aarch64) под Unicorn прямо в
Windows, без WSL2 и Qiling. Это эталон для пошаговой сверки.

```powershell
py -3.14 -m pip install unicorn          # один раз (проверено на 2.1.4)
py -3.14 libssc\oracle\ssc_oracle.py check-golden
py -3.14 libssc\oracle\ssc_oracle.py trace --bitrate 229000 --frame 1
py -3.14 libssc\oracle\ssc_oracle.py trace --rate 96000 --bitrate 584000 --max-depth 1
```

Из Python:

```python
from ssc_oracle import Oracle, golden_pcm
o = Oracle(trace=True).open(48000, 2, 229000)
o.probes_exit["compute_band_energies"] = lambda o, rec: print(rec.args[:4], rec.ret)
frame = o.encode(golden_pcm(0x5A5C2026, 0, 48000))   # 864 x 2ch, int32, шкала 2^29
for rec in o.calls: ...                               # дерево вызовов последнего кадра
```

- Один `Oracle` — один «процесс»: блоб держит состояние энкодера в глобалах
  `.bss`, поэтому на каждый поток нужен новый экземпляр.
- Порядок вызовов повторяет `ssc_blob_helper.c` старого демона
  (get_size → init на warm-up состоянии → create → encode).
- `malloc` — bump-аллокатор по обнулённой памяти, `free` ничего не делает.
