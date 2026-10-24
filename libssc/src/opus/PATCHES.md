# Samsung changes applied to the vendored Opus 1.1.5 sources

Everything in this directory is libopus 1.1.5 (BSD, see `COPYING`), unchanged
except for the edits below. Every edit is marked with a `libssc:` comment.
Each one was found by diffing the blob against Opus with `test/replay.py` and
confirmed bit-exact on real calls.

| File | Change | Found in |
|---|---|---|
| `mfrngcod.h` | `EC_CODE_BITS 32 → 24`: 24-bit range coder registers | phase 1 |
| `pitch.c` | `ssc_pitch_gain()` replaces `compute_pitch_gain()`: gain = `xy·rsqrt(1 + (xx·yy >> s))` from the 64-bit product, s = 32 for g0 and 31 in the k loop | 3b |
| `pitch.c` | `remove_doubling`: `yy_lookup[i] = yy` (no `MAX32(0, yy)`) | 3b |
| `pitch.c` | `remove_doubling`: `xy = xy + xy2` and `yy = yy[T1] + yy[T1b]` without `HALF32`; the yy sum is 64-bit for the gain and truncated to 32 bits for `best_yy` | 3b |

Files compiled through a wrapper instead of on their own (see `build.py`
`INCLUDED_BY_WRAPPER`): `pitch.c` and `celt_lpc.c` are included by
`../ssc_pitch.c`, which renames the Opus entry points and exports the blob's
specialised signatures.
