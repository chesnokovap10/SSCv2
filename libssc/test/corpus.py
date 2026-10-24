#!/usr/bin/env python3
"""Corpus bench: whole frames, libssc vs the blob, per bitrate and signal.

  py -3.14 libssc/build.py && py -3.14 libssc/test/corpus.py [--frames 12] [--rates all]

Prints one line per profile (bit-exact frames per signal, first differing
frame and byte) and the total; exit code 1 if any frame differs.
"""

import argparse
import ctypes
import os
import sys
from pathlib import Path

LIBSSC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(LIBSSC / "oracle"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from ssc_oracle import Oracle  # noqa: E402
import signals  # noqa: E402

FRAME = 864


def lib_encoder(lib, rate, bitrate):
    st = ctypes.create_string_buffer(lib.ssc_encoder_get_size(2, rate))
    assert lib.ssc_encoder_init(st, rate, 2, 24) == 0
    out = ctypes.create_string_buffer(4096)

    def encode(pcm):
        buf = ctypes.create_string_buffer(pcm, len(pcm))  # DRC writes in place
        n = lib.ssc_encode(st, buf, FRAME, out, bitrate)
        return out.raw[:max(n, 0)]
    return encode


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--frames", type=int, default=12)
    ap.add_argument("--signals", default=",".join(signals.NAMES))
    ap.add_argument("--rates", choices=["basic", "all"], default="all")
    a = ap.parse_args()
    lib = ctypes.CDLL(str(LIBSSC / "build" / "libssc.dll"))
    lib.ssc_encode.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int, ctypes.c_void_p,
                               ctypes.c_int]
    lib.ssc_encoder_init.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int]
    same = total = 0
    for rate, bitrate in signals.profiles(a.rates):
        cells = []
        for sig in a.signals.split(","):
            o = Oracle().open(rate, 2, bitrate)
            enc = lib_encoder(lib, rate, bitrate)
            ok, first = 0, None
            for i, pcm in enumerate(signals.frames(sig, rate, a.frames)):
                want, got = o.encode(pcm), enc(pcm)
                if want == got:
                    ok += 1
                elif first is None:
                    k = next((j for j in range(min(len(want), len(got))) if want[j] != got[j]),
                             min(len(want), len(got)))
                    first = f"f{i}@{k}"
            same += ok
            total += a.frames
            cells.append(f"{sig}:{ok}" + (f"({first})" if first else ""))
        print(f"{rate // 1000}k {bitrate // 1000:>3}k  " + " ".join(cells), flush=True)
    print(f"bit-exact frames: {same}/{total}")
    sys.stdout.flush()
    os._exit(0 if same == total else 1)


if __name__ == "__main__":
    main()
