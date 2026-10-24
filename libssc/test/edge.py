#!/usr/bin/env python3
"""Phase 4 bench: libssc vs the blob on long runs, unknown and switching
bitrates, extreme signals and other input formats.

  py -3.14 libssc/build.py && py -3.14 libssc/test/edge.py [--only NAME,...] [--list]

Every frame compares: ssc_encode's return value, the frame bytes, the PCM after
the in-place DRC, the whole encoder state (mode pointer excluded) and the
process globals the blob keeps (drc_struct, previous_uhq_index, in_shared,
_pre_shared, _pcmpower). The blob runs under an instruction limit, so a
scenario that hangs it is reported instead of hanging the bench.
"""

import argparse
import ctypes
import math
import os
import random
import struct
import sys
import time
from pathlib import Path

LIBSSC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(LIBSSC / "oracle"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from ssc_oracle import IO_BASE, IO_SIZE, MAX_ENCODE, BlobError, Oracle  # noqa: E402
import signals  # noqa: E402

FRAME = 864
FS = 1 << 23           # 24-bit full scale
I32_MAX, I32_MIN = (1 << 31) - 1, -(1 << 31)
RATES48 = [88000, 96000, 128000, 192000, 229000, 256000, 328000]
RATES96 = [152000, 250000, 291000, 308000, 442000, 584000, 886000]
GLOBALS = {"drc_struct": 24, "previous_uhq_index": 4, "in_shared": 2 * (FRAME + 108) * 4,
           "_pre_shared": 2 * (FRAME + 1024) * 4, "_pcmpower": FRAME * 2 * 4}
MAX_INSNS = 200_000_000  # ~20x a normal frame
OUT_SIZE = 1 << 16  # ec_enc_done writes at the end of the whole budget, even past 1275 bytes


# ------------------------------------------------------------------ signals
def _pack(vals):
    return struct.pack("<%di" % len(vals), *[max(I32_MIN, min(I32_MAX, int(v))) for v in vals])


def gen(kind, rate, frames, n=FRAME, scale=FS, seed=1):
    """Frames of interleaved stereo int32 for the extreme / long-run signals."""
    rng = random.Random(seed)
    t0 = 0
    for f in range(frames):
        v = []
        for i in range(n):
            t = (t0 + i) / rate
            if kind == "i32max":
                l = r = I32_MAX
            elif kind == "i32min":
                l = r = I32_MIN
            elif kind == "i32alt":       # +max / min every sample: Nyquist square
                l = r = I32_MAX if (t0 + i) & 1 else I32_MIN
            elif kind == "i32noise":     # the whole int32 range
                l, r = rng.randrange(I32_MIN, I32_MAX + 1), rng.randrange(I32_MIN, I32_MAX + 1)
            elif kind == "fs_square":    # 24-bit full scale square, 1 kHz
                l = r = (scale - 1) if math.sin(2 * math.pi * 1000 * t) >= 0 else -scale
            elif kind == "fs_sine":      # 0 dBFS sine, L/R in quadrature
                l = (scale - 1) * math.sin(2 * math.pi * 997 * t)
                r = (scale - 1) * math.cos(2 * math.pi * 997 * t)
            elif kind == "dc_half":
                l, r = scale // 2, -scale // 2
            elif kind == "dc_full":
                l = r = scale - 1
            elif kind == "dc_i32":
                l, r = I32_MAX, I32_MIN
            elif kind == "impulse_min":  # one INT_MIN sample per frame in silence
                l = r = I32_MIN if i == 100 else 0
            elif kind == "lsb":          # +-1 LSB noise: almost silence
                l, r = rng.choice((-1, 0, 1)), rng.choice((-1, 0, 1))
            elif kind == "burst":        # silence, then loud noise, then silence
                on = 3 <= f % 8 < 5
                l = rng.gauss(0, 0.5) * scale if on else 0
                r = rng.gauss(0, 0.5) * scale if on else 0
            elif kind == "music":        # long-run material: drifting chords + noise + clicks
                w = 0.25 * scale
                fr = 110 * (1 + (f // 40) % 5)
                l = w * (math.sin(2 * math.pi * fr * t) + 0.5 * math.sin(2 * math.pi * 2.01 * fr * t)
                         + 0.3 * math.sin(2 * math.pi * 7 * fr * t)) + rng.gauss(0, 0.02) * scale
                r = w * (math.sin(2 * math.pi * 1.5 * fr * t + 1) + 0.4 * math.sin(2 * math.pi * 5 * fr * t)) \
                    + rng.gauss(0, 0.02) * scale
                if (t0 + i) % 9000 < 4:
                    l += 0.6 * scale
            else:
                raise ValueError(kind)
            v += [l, r]
        t0 += n
        yield _pack(v)


def corpus_frames(name, rate, frames, shift=0):
    """signals.py material (2^29 scale for most), optionally shifted down."""
    for pcm in signals.frames(name, rate, frames):
        if shift:
            vals = struct.unpack("<%di" % (len(pcm) // 4), pcm)
            pcm = struct.pack("<%di" % len(vals), *[x >> shift for x in vals])
        yield pcm


# ---------------------------------------------------------------- scenarios
def S(name, rate, bitrates, source, frames, bit_depth=24, channels=2, frame_size=FRAME):
    return dict(name=name, rate=rate, bitrates=bitrates, source=source, frames=frames,
                bit_depth=bit_depth, channels=channels, frame_size=frame_size)


def cycle(rates, every):
    return lambda i: rates[(i // every) % len(rates)]


def scenarios():
    out = []
    # long runs: the frame counter wraps at 256 (header byte 2, UHQ byte 1)
    for br in (229000, 128000, 328000):
        out.append(S(f"long {br // 1000}k", 48000, br, ("gen", "music"), 600))
    for br in (584000, 152000, 250000):
        out.append(S(f"long {br // 1000}k", 96000, br, ("gen", "music"), 600))
    # unknown / odd bitrates on both modes
    for br in (0, 1, -1, 64000, 100000, 229001, 300000, 600000, 1000000, 1275 * 8 * 50,
               4000000, 0x7FFFFFFF, -229000):
        out.append(S(f"unknown {br}@48k", 48000, br, ("corpus", "golden"), 6))
    for br in (0, 200000, 500000, 1000000, 229000, 128000):
        out.append(S(f"unknown {br}@96k", 96000, br, ("corpus", "golden"), 6))
    # bitrate switching on one encoder (the phone adapts to link load)
    out.append(S("switch 48k every frame", 48000, cycle(RATES48, 1), ("gen", "music"), 70))
    out.append(S("switch 48k every 5", 48000, cycle(RATES48[::-1], 5), ("gen", "music"), 70))
    out.append(S("switch 96k every frame", 96000, cycle(RATES96, 1), ("gen", "music"), 70))
    out.append(S("switch 96k every 5", 96000, cycle(RATES96[::-1], 5), ("gen", "music"), 70))
    out.append(S("switch 96k <-> 48k-rates", 96000, cycle([584000, 229000, 152000, 88000], 3),
                 ("gen", "music"), 36))
    out.append(S("switch 48k <-> UHQ rates", 48000, cycle([229000, 584000, 128000, 250000], 3),
                 ("gen", "music"), 36))
    # extreme signals at every bitrate
    kinds = ["i32max", "i32min", "i32alt", "i32noise", "fs_square", "fs_sine", "dc_half",
             "dc_full", "dc_i32", "impulse_min", "lsb", "burst"]
    for kind in kinds:
        for rate, rates in ((48000, RATES48), (96000, RATES96)):
            for br in rates:
                out.append(S(f"{kind} {br // 1000}k", rate, br, ("gen", kind), 8))
    # other input formats
    for br in (88000, 128000, 229000, 328000):
        out.append(S(f"44.1k {br // 1000}k", 44100, br, ("corpus", "noise"), 8))
        out.append(S(f"16-bit {br // 1000}k", 48000, br, ("corpus16", "noise"), 8, bit_depth=16))
        out.append(S(f"16-bit fs {br // 1000}k", 48000, br, ("gen16", "fs_sine"), 8, bit_depth=16))
    for br in (152000, 584000):
        out.append(S(f"16-bit {br // 1000}k", 96000, br, ("corpus16", "noise"), 8, bit_depth=16))
    # mono (channels = 1) is not covered: ssc_encode still handles two channels
    # and the blob writes past its mono-sized state (PLAN.md, phase 4)
    out.append(S("channels 3", 48000, 229000, ("corpus", "noise"), 2, channels=3))
    out.append(S("fs 32000", 32000, 229000, ("corpus", "noise"), 2))
    out.append(S("frame_size 0", 48000, 229000, ("corpus", "noise"), 3, frame_size=0))
    return out


def frames_of(sc):
    kind, name = sc["source"]
    rate, n = sc["rate"], sc["frames"]
    if kind == "gen":
        return gen(name, rate, n)
    if kind == "gen16":
        return gen(name, rate, n, scale=1 << 15)
    if kind == "corpus":
        return corpus_frames(name, rate, n)
    if kind == "corpus16":
        return corpus_frames(name, rate, n, shift=14)  # 2^29 -> 2^15
    raise ValueError(kind)


# ----------------------------------------------------------------- encoders
class Blob:
    def __init__(self, rate, channels, bit_depth):
        self.o = o = Oracle()
        size = Oracle.s32(o.call("ssc_encoder_get_size", channels, rate))
        warm = o._alloc(size)
        o.call("ssc_encoder_init", warm, rate, channels, bit_depth)
        err = IO_BASE + IO_SIZE - 16
        o.uc.mem_write(err, struct.pack("<i", -1))
        self.st = o.call("ssc_encoder_create", rate, channels, bit_depth, err)
        self.err = struct.unpack("<i", o.read(err, 4))[0]
        self.size = size

    def encode(self, pcm, frame_size, bitrate):
        o, pcm_addr, out = self.o, IO_BASE, IO_BASE + 0x80000
        o.uc.mem_write(pcm_addr, pcm)
        o.uc.mem_write(out, b"\0" * OUT_SIZE)
        ret = Oracle.s32(o.call("ssc_encode", self.st, pcm_addr, frame_size, out,
                                bitrate & 0xFFFFFFFF, max_insns=MAX_INSNS))
        n = ret if 0 < ret <= OUT_SIZE else 0
        return ret, o.read(out, n), o.read(pcm_addr, len(pcm))

    def state(self):
        return self.o.read(self.st + 8, self.size - 8)

    def glob(self, name):
        return self.o.read(self.o.exports[name], GLOBALS[name])


class Lib:
    def __init__(self, lib, rate, channels, bit_depth):
        self.lib = lib
        for g, n in GLOBALS.items():  # a fresh oracle starts with zeroed .bss: do the same
            ctypes.memset(ctypes.addressof(ctypes.c_char.in_dll(lib, g)), 0, n)
        err = ctypes.c_int(-1)
        self.size = lib.ssc_encoder_get_size(channels, rate)
        self.st = lib.ssc_encoder_create(rate, channels, bit_depth, ctypes.byref(err))
        self.err = err.value
        self.out = ctypes.create_string_buffer(OUT_SIZE)

    def encode(self, pcm, frame_size, bitrate):
        buf = ctypes.create_string_buffer(pcm, max(1, len(pcm)))
        ctypes.memset(self.out, 0, OUT_SIZE)
        ret = self.lib.ssc_encode(self.st, buf, frame_size, self.out, bitrate)
        n = ret if 0 < ret <= OUT_SIZE else 0
        return ret, self.out.raw[:n], buf.raw[:len(pcm)]

    def state(self):
        return ctypes.string_at(self.st + 8, self.size - 8) if self.st else b""

    def glob(self, name):
        return ctypes.string_at(ctypes.addressof(ctypes.c_char.in_dll(self.lib, name)),
                                GLOBALS[name])


def load_lib():
    lib = ctypes.CDLL(str(LIBSSC / "build" / "libssc.dll"))
    lib.ssc_encoder_get_size.argtypes = [ctypes.c_int, ctypes.c_int]
    lib.ssc_encoder_create.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_void_p]
    lib.ssc_encoder_create.restype = ctypes.c_void_p
    lib.ssc_encode.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int, ctypes.c_void_p,
                               ctypes.c_int]
    return lib


def first_diff(a, b):
    return next((k for k in range(min(len(a), len(b))) if a[k] != b[k]), min(len(a), len(b)))


def run(lib, sc):
    """-> (ok, frames compared, note)"""
    try:
        b = Blob(sc["rate"], sc["channels"], sc["bit_depth"])
    except BlobError as e:
        return None, 0, f"blob failed to create ({e}); libssc not compared"
    l = Lib(lib, sc["rate"], sc["channels"], sc["bit_depth"])
    if (b.st == 0) != (l.st is None) or b.err != l.err or b.size != l.size:
        return False, 0, f"create: blob st={b.st:#x} err={b.err} size={b.size}, " \
                         f"libssc st={l.st} err={l.err} size={l.size}"
    if not b.st:
        return True, 0, f"create fails on both sides (err {b.err})"
    br_of = sc["bitrates"] if callable(sc["bitrates"]) else (lambda i, v=sc["bitrates"]: v)
    rets = set()
    for i, pcm in enumerate(frames_of(sc)):
        br = br_of(i)
        try:
            rb, fb, pb = b.encode(pcm, sc["frame_size"], br)
        except BlobError as e:
            return None, i, f"frame {i}: blob failed ({e}); libssc not compared"
        rl, fl, pl = l.encode(pcm, sc["frame_size"], br)
        rets.add(rb)
        where = f"frame {i} @{br}"
        if rb != rl:
            return False, i, f"{where}: return {rb} vs {rl}"
        if fb != fl:
            return False, i, f"{where}: frame byte {first_diff(fb, fl)} of {len(fb)}"
        if pb != pl:
            return False, i, f"{where}: PCM after DRC byte {first_diff(pb, pl)}"
        sb, sl = b.state(), l.state()
        if sb != sl:
            return False, i, f"{where}: state +{first_diff(sb, sl) + 8:#x}"
        for g in GLOBALS:
            gb, gl = b.glob(g), l.glob(g)
            if gb != gl:
                return False, i, f"{where}: {g} byte {first_diff(gb, gl)}"
    return True, sc["frames"], "returns " + ",".join(map(str, sorted(rets)))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--only", help="comma-separated substrings of scenario names")
    ap.add_argument("--list", action="store_true")
    a = ap.parse_args()
    scs = scenarios()
    if a.only:
        keys = a.only.split(",")
        scs = [s for s in scs if any(k in s["name"] for k in keys)]
    if a.list:
        for s in scs:
            print(s["name"])
        return
    lib = load_lib()
    fails = blocked = frames = 0
    t = time.time()
    for sc in scs:
        ok, n, note = run(lib, sc)
        frames += n
        status = {True: "PASS", False: "FAIL", None: "BLOB"}[ok]
        fails += ok is False
        blocked += ok is None
        print(f"{status}  {sc['name']}: {n} frames, {note}", flush=True)
    print(f"{len(scs) - fails - blocked}/{len(scs)} passed, {blocked} blob failures, "
          f"{frames} frames, {time.time() - t:.0f} s")
    sys.stdout.flush()
    os._exit(1 if fails else 0)


if __name__ == "__main__":
    main()
