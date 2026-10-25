# libssc — plan

**English** · [Русский](PLAN.ru.md)

Our own Samsung Scalable Codec library for SSCv2: the encoder (done, bit-exact) and a decoder
(ahead). Started 2026-10-24. The detailed step-by-step journal is in git history
(`libssc/PLAN.md` before 2026-10-25).

## Status

| Phase | What | Status |
|---|---|---|
| 0 | Reference: the blob under Unicorn | ✅ |
| 1 | Map of differences from CELT, modes, header | ✅ |
| 2 | libssc skeleton — an ABI twin of the blob | ✅ |
| 3 | Bit-exactness stage by stage (3a–3g) | ✅ |
| 4 | Full verification: long runs, extreme signals | ✅ |
| 5 | Integration into SSCv2 (cgo), tested on Samsung Galaxy Buds2 Pro | ✅ |
| 6 | Decoder | ⏳ next |

## Decisions

| Question | Decision |
|---|---|
| Goal | Bit-exact output with `libScalable_Encoder.so` from the **current phone firmware** (clang 14, NDK r25) on all 14 bitrates. The older build (clang 8, from a third-party program) is no longer the reference and was removed in 3g |
| Distribution | Private only, for our own hardware (Samsung Galaxy Buds2 Pro / Buds3 FE). No public release |
| Location | `libssc/` in SSCv2; in the app — cgo package `internal/codec/ssc`, entry `internal/engine/codecs.go` → `newSSC` |
| Pace | One phase at a time; review after each, then the next |

## What SSC is

SSC is a modified **CELT from libopus 1.1.5** (fixed-point). A frame is 864 = 8 × 108 (custom
mode: 8 short MDCTs of 108), 22 bands, overlap 108, LM = 3. Samsung's additions:
preprocessing (biquad + SoundBooster DRC limiter), `normal_headroom` / `uhq_headroom`,
`tone_detect`, its own transient decision, cutting of the top bands, UHQ 96 kHz, 32-bit
MDCT/FFT, a second bit allocation table for bitrates above 192k.

**Frame header** (4 bytes): `FF`, `EE` (48k) or `E0 | counter>>4` (UHQ),
`counter<<4 | band flags`, `flags<<5 | bitrate index` (48k `F0..F6`, UHQ `E0..E6`).

**Frame size (CBR):** `n = bitrate·864 / (Fs_mode·8)` with `Fs_mode = 44100` for 44.1/48 kHz;
for "narrow" bitrates (not UHQ, not 256/328k) `n += 3n>>7`; `n |= 1`; the frame is `4 + n − 1`,
at most 1275 + 4.

## Phases

### 0 — Reference

`oracle/ssc_oracle.py`: own ELF loader on Unicorn 2.1.4 (relocations, 8 libc stubs, stack guard
through `tpidr_el0`), tracing of exported functions. Goldens: 6 profiles × 16 frames.

### 1 — Map of differences

All mode tables are in `research/tables.json` (`dump_mode.py`); the header model
(`header_model.py`) matches every golden frame. Diff bench against Opus (`difftest/`): the math
matches; the range coder matches after patch **ec24** (`EC_CODE_BITS 32 → 24`); Samsung's
`haar1` truncates each term.

### 2 — Skeleton

libssc is an ABI twin: the same names, signatures and layouts (offsets pinned with
`_Static_assert`), so the benches give both sides the same memory. The Opus sources in
`src/opus/` are untouched except for the patches in `PATCHES.md`.

### 3 — Bit-exactness along `ssc_encode`

Order as in Opus 1.1 `celt_encode_with_ec`; every function is checked by `replay.py`, every
stage by `stages.py`.

- **3a — input.** Biquad (Q28, 64-bit accumulator), `powercalc`, `CalculateLimitGain`, the
  SoundBooster DRC in place on the input PCM, 8 blocks of 108.
- **3b — pitch and prefilter.** Opus 1.1.5 nearly unchanged, Samsung changes in
  `remove_doubling`, its own `comb_filter` (Q31 window, 64-bit sums). No pre-emphasis.
- **3c — MDCT/FFT/headroom.** All 32-bit (Q31 window and trig), kiss FFT unrolled for 432 and
  54 points. A blob bug: one radix-3 stage runs an extra pass and writes into an unused part
  of the buffer — repeated, otherwise the buffers differ.
- **3d — energies and decisions.** Transient detection from band 13, top-band flags in the
  header, `tone_detect` inside `pitch_search`; work arrays live in the shared `in_shared`, as
  in the blob.
- **3e — energy quantisation and bit allocation.** Own signatures of `quant_coarse_energy` and
  `compute_allocation`, a rewritten `spreading_decision`, Samsung boosts in dynalloc.
- **3f — PVQ and frame end.** Own `quant_all_bands` without folding, arithmetic differences
  (`stereo_itheta`, `exp_rotation`, PVQ search metric). Goldens and corpus match in full.
- **3g — switch to the phone firmware blob.** A different build: names prefixed `ssc_`, a
  128-byte mode, a shorter state, one `SscAlloc` struct, the float transient detector removed,
  small rounding differences (biquad, `powercalc`, DRC, headroom, dynalloc). Goldens re-taken;
  1680/1680 corpus frames match.

### 4 — Full verification

`test/edge.py`: 216 scenarios, 5525 frames; after each — the frame, PCM after DRC, state and
globals. 215/216; the exception is 32 kHz, where the blob itself crashes. Found and fixed:
frames cut at 1275 + 4, an own `_ssc_autocorr`, the blob reading past `headroom_gain` at
96 kHz with a narrow bitrate (repeated), the boost budget is always stereo. Not supported: mono
(the blob corrupts its own memory) and rates other than 44.1/48/96 kHz.

### 5 — Integration into SSCv2

The phone's behaviour, taken from `ref/libbluetooth_jni.so` (Ghidra, `research/decomp_bt`):

- capability byte: `0xF0` rates, `0x08` no bitrate limit, `0x04` 24 bit 48 kHz, `0x02` UHQ;
  the phone configures `(peer & 0x08) | 0x04` (UHQ: `0x02 | 0x08`);
- PCM: 24 bit 48 kHz at **2^23 full scale**; 16 bit only at 44.1 kHz; UHQ at 96 kHz;
- bitrate by link busy level: 48 kHz 192/192/128/88k (limited: 128/128/128/88k),
  UHQ 584/584/291/152k; the phone never uses 229/256/328k at 48 kHz;
- packet: the frame right after the RTP header, **the RTP timestamp counts packets**.

In SSCv2: cgo package `internal/codec/ssc` (float → 24 bit, `FrameBytes`, one encoder per
process); `go test` checks the frames' sha256 against the blob on all 14 bitrates. The tray
offers the SSC and SSC UHQ codecs and a bitrate choice.

**On Samsung Galaxy Buds2 Pro (cap 0x3C, configuration 0x0C):** 192k and 229k sound fine, 256k and 328k bad:
these are the "wide" bitrates the phone never sends at 48 kHz, and our frames are bit-exact, so
the headphones' decoder handles them poorly. The practical maximum is 229k.
**Forced UHQ:** the 48 kHz capture upsampled 2× (half-band FIR, `engine/upsample.go`), the
encoder at 96 kHz; Samsung Galaxy Buds2 Pro accept configuration 0x0A, 584k runs without errors.

### 6 — Decoder (next)

Based on the Opus 1.1.5 CELT decoder with Samsung's differences from phases 3–4. Check:
decode(libssc) ≈ the source PCM, and decoding the blob's frames. Needed to judge quality without
headphones — first of all, to find out what is wrong with 256k/328k.

## Open

- Lowering the bitrate by link load (the phone uses the controller's busy level).
- A real 96 kHz capture for UHQ instead of upsampling.
- Input scale at 96 kHz: the phone passes the HAL's 32-bit PCM unchanged; we feed 2^23
  (experiment: `SSCV2_SSC_SHIFT`).
- Several encoders per process: move the globals (DRC, `in_shared`, `_pre_shared`) into
  `SscEncoder`.
