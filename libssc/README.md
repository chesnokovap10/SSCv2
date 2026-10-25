# libssc

**English** · [Русский](README.ru.md)

Our own Samsung Scalable Codec (SSC) encoder, **bit-exact** with `libScalable_Encoder.so`
from the current phone firmware (clang 14, NDK r25). C99, fixed-point, built on CELT from
Opus 1.1.5. SSCv2 uses it through the cgo package `internal/codec/ssc`. Personal use only.
Plan and phase results: [PLAN.md](PLAN.md).

## Contents

| Path | What |
|---|---|
| `src/` | **the library**: `ssc_*.c` — our code, `src/opus/` — Opus 1.1.5 + patches (`PATCHES.md`, licence `COPYING`) |
| `src/ssc_names.h` | the blob's names (`ssc_quant_all_bands`, `ssc_ec_encode`, …) for every file (`-include` in `build.py`, `#include` in the cgo wrappers) |
| `ref/libScalable_Encoder.so` | Samsung's blob from the firmware (aarch64), for comparison only |
| `ref/libbluetooth_jni.so` | the phone's Bluetooth stack (`com.android.bt.apex`): how the phone calls the encoder, picks the bitrate and packs frames |
| `oracle/ssc_oracle.py` | reference: the blob under Unicorn, right on Windows, with call tracing |
| `testdata/*.golden` | 6 profiles × 16 frames, frozen blob output |
| `test/` | comparison benches (below) |
| `tools/gen_tables.py` | `research/tables.json` → `src/ssc_tables.c` |
| `research/` | reverse engineering: disassembler, mode tables, header model, Opus diff bench, Ghidra decompilation (`decomp/` — encoder, `decomp_bt/` — the SSC part of the BT stack) |

libssc is an **ABI twin** of the blob: the same function names, signatures and struct layouts
(mode, `ec_ctx`, encoder state, `SscAlloc`), so any function can be called on both sides with
the same memory and compared byte by byte. Like the blob, the DRC state and work buffers are
process globals: one encoder open at a time.

## API

```c
SscEncoder *ssc_encoder_create(int rate, int channels, int bits, int *err); // 44100|48000|96000, 2, 16|24
int ssc_encode(SscEncoder *st, int32_t *pcm, int frame, uint8_t *out, int bitrate); // pcm is modified (DRC)
void ssc_encoder_destroy(SscEncoder *st);
```

* A frame is 864 samples per channel (18 ms at 48 kHz, 9 ms at 96 kHz); input int32 at 2^23
  full scale (24 bit).
* Bitrates: 48 kHz — 88/96/128/192/229/256/328k; UHQ 96 kHz — 152/250/291/308/442/584/886k.
  The coder is CBR: frame size = `FrameBytes(rate, bitrate)` in `internal/codec/ssc`.

## Build and verify

```powershell
py -3.14 libssc\build.py          # MinGW gcc -> libssc\build\libssc.dll
py -3.14 libssc\test\twin.py      # 17 checks against the blob, golden frames in full
py -3.14 libssc\test\corpus.py    # whole frames: 14 bitrates × 10 signals
py -3.14 libssc\test\edge.py      # 216 edge scenarios (--only NAME, --list)
py -3.14 libssc\test\replay.py    # libssc functions on real calls recorded in the blob
py -3.14 libssc\test\stages.py    # per-frame checkpoints along the chain
# replay.py and stages.py: --rates all — all 14 bitrates instead of the 6 profiles

go test ./internal/codec/ssc      # the cgo build against blob hashes (testdata/oracle.txt)
py -3.14 libssc\test\cgo_ref.py   # re-take those hashes
```

| Bench | Compares |
|---|---|
| `test/twin.py` | math functions, range coder, modes, state after init, golden frames |
| `test/replay.py` | recorded calls of a blob function (inputs, outputs, globals) → the same libssc function |
| `test/stages.py` | both encoders frame by frame: checkpoints, frame, state and shared buffers |
| `test/corpus.py` | whole frames on every bitrate and `test/signals.py` signal |
| `test/edge.py` | long runs, unknown and changing bitrates, extreme signals, 16 bit, 44.1 kHz |
| `test/cgo_ref.py` | blob frame hashes for the Go test |

After adding files to `src/`, regenerate the wrappers: `go run ./tools/genwrap`.

## Oracle

`oracle/ssc_oracle.py` loads the blob (aarch64 ELF) into Unicorn: own relocations, 8 libc
stubs, stack guard. It is the reference for step-by-step comparison.

```powershell
py -3.14 -m pip install unicorn          # once (tested with 2.1.4)
py -3.14 libssc\oracle\ssc_oracle.py check-golden
py -3.14 libssc\oracle\ssc_oracle.py make-golden   # re-take the goldens
py -3.14 libssc\oracle\ssc_oracle.py trace --bitrate 229000 --frame 1
py -3.14 libssc\oracle\ssc_oracle.py trace --rate 96000 --bitrate 584000 --max-depth 1
```

```python
from ssc_oracle import Oracle, golden_pcm
o = Oracle(trace=True).open(48000, 2, 229000)
o.probes_exit["ssc_compute_band_energies"] = lambda o, rec: print(rec.args[:4], rec.ret)
frame = o.encode(golden_pcm(0x5A5C2026, 0, 48000))
for rec in o.calls: ...                               # call tree of the last frame
```

One `Oracle` is one "process" (the blob keeps its state in `.bss`); `malloc` is a bump
allocator, `free` does nothing.

## research/

```powershell
py -3.14 -m pip install capstone
py -3.14 libssc\research\disasm.py ssc_encoder_create   # disassembler with symbols
py -3.14 libssc\research\dump_mode.py [--json F]        # modes and tables
py -3.14 libssc\research\header_model.py                # header model vs the goldens
# diff bench: Opus (git clone xiph/opus, checkout v1.1.5) + MinGW gcc
py -3.14 libssc\research\difftest\build_ref.py <opus-dir> --tag v1.1.5 --patch ec24
py -3.14 libssc\research\difftest\difftest.py
# decompilation (JDK 21 + portable Ghidra in D:\2\tools)
pwsh libssc\research\ghidra\decompile.ps1      # -> research\decomp\*.c
pwsh libssc\research\ghidra\decompile_bt.ps1   # the phone's BT stack -> research\decomp_bt (~15 min)
```

`libssc/` has no `.go` files; `go build` does not touch it.
