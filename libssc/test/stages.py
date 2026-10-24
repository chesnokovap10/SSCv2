#!/usr/bin/env python3
"""Stage bench: run the blob and libssc encoders side by side on the same frames
and compare named checkpoints after every frame. Checkpoints are added as the
port of the ssc_encode chain advances (see libssc/PLAN.md, phase 3).

  py -3.14 libssc/build.py && py -3.14 libssc/test/stages.py [--frames 12]
"""

import argparse
import ctypes
import os
import sys
from pathlib import Path

LIBSSC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(LIBSSC / "oracle"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from ssc_oracle import IO_BASE, Oracle  # noqa: E402
import signals  # noqa: E402

FRAME = 864
PCM_BYTES = FRAME * 2 * 4


class LibEncoder:
    def __init__(self, lib, rate, bitrate):
        self.lib, self.bitrate = lib, bitrate
        lib.ssc_encoder_get_size.restype = ctypes.c_int
        size = lib.ssc_encoder_get_size(2, rate)
        self.st = ctypes.create_string_buffer(size)
        lib.ssc_encoder_init.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int]
        assert lib.ssc_encoder_init(self.st, rate, 2, 24) == 0
        lib.ssc_encode.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int,
                                   ctypes.c_void_p, ctypes.c_int]
        self.out = ctypes.create_string_buffer(4096)

    def encode(self, pcm):
        self.pcm = ctypes.create_string_buffer(pcm, len(pcm))
        n = self.lib.ssc_encode(self.st, self.pcm, FRAME, self.out, self.bitrate)
        return self.out.raw[:max(n, 0)]

    def glob(self, name, size):
        return ctypes.string_at(ctypes.addressof(ctypes.c_char.in_dll(self.lib, name)), size)


def hdr_fixed(f):
    """Header without the flags set inside the CELT part (byte2 bits 2-3, byte3 bits 5-7)."""
    return bytes([f[0], f[1], f[2] & 0xF3, f[3] & 0x1F])


def hdr_flags(f):
    return bytes([f[2] & 0x0C, f[3] & 0xE0])


# Checkpoints that depend on code not ported yet: reported, but not a failure.
PENDING = {"frame header (CELT flags)", "CELT payload"}

# name -> (blob reader, lib reader); each returns bytes
CHECKPOINTS = {
    "pcm after DRC": (lambda o: o.read(IO_BASE, PCM_BYTES), lambda l: l.pcm.raw),
    "_pcmpower (biquad out)": (lambda o: o.read(o.exports["_pcmpower"], PCM_BYTES),
                               lambda l: l.glob("_pcmpower", PCM_BYTES)),
    "drc_struct": (lambda o: o.read(o.exports["drc_struct"], 24),
                   lambda l: l.glob("drc_struct", 24)),
    "state biquad (+0xd8)": (lambda o: o.read(o.state + 0xd8, 80), lambda l: l.st.raw[0xd8:0x128]),
    "frame header (fixed bits)": (lambda o: hdr_fixed(o.last), lambda l: hdr_fixed(l.last)),
    "frame length": (lambda o: len(o.last).to_bytes(4, "little"),
                     lambda l: len(l.last).to_bytes(4, "little")),
    "frame header (CELT flags)": (lambda o: hdr_flags(o.last), lambda l: hdr_flags(l.last)),
    "CELT payload": (lambda o: o.last[4:], lambda l: l.last[4:]),
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--frames", type=int, default=12)
    ap.add_argument("--signals", default=",".join(signals.NAMES))
    a = ap.parse_args()
    lib = ctypes.CDLL(str(LIBSSC / "build" / "libssc.dll"))
    first_fail = {k: None for k in CHECKPOINTS}
    payload_same = payload_total = frames = 0
    for sig in a.signals.split(","):
        for rate, bitrate in signals.PROFILES:
            o = Oracle().open(rate, 2, bitrate)
            l = LibEncoder(lib, rate, bitrate)
            for i, pcm in enumerate(signals.frames(sig, rate, a.frames)):
                o.last = o.encode(pcm)
                l.last = l.encode(pcm)
                frames += 1
                for name, (rb, rl) in CHECKPOINTS.items():
                    if first_fail[name] is None and rb(o) != rl(l):
                        first_fail[name] = f"{sig}@{bitrate // 1000}k frame {i}"
                payload_same += sum(x == y for x, y in zip(o.last[4:], l.last[4:]))
                payload_total += len(o.last) - 4
    fails = 0
    for name, where in first_fail.items():
        status = "PASS" if where is None else ("PEND" if name in PENDING else "FAIL")
        fails += status == "FAIL"
        print(f"{status}  {name}" + ("" if where is None else f"  (first: {where})"))
    print(f"frames: {frames}; CELT payload bytes equal: {payload_same}/{payload_total}")
    sys.stdout.flush()
    os._exit(1 if fails else 0)


if __name__ == "__main__":
    main()
