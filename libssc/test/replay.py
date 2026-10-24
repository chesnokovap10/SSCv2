#!/usr/bin/env python3
"""Replay bench: record real calls of a blob function during encoding (inputs at
entry, outputs at exit, globals both times), then call the libssc twin with the
same inputs and compare byte for byte.

  py -3.14 libssc/test/replay.py                       # all specced functions
  py -3.14 libssc/test/replay.py SoundBooster_DRC_Exe  # one function
  py -3.14 libssc/test/replay.py --signals golden,noise,loud --frames 12

Spec syntax per argument: "int" (32-bit value), or "<dir>:<size>" where dir is
in / out / inout and size is a Python expression over a0..a7 (the int args).
"""

import argparse
import ctypes
import os
import struct
import sys
from pathlib import Path

LIBSSC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(LIBSSC / "oracle"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from ssc_oracle import Oracle  # noqa: E402
import signals  # noqa: E402

S32 = Oracle.s32

SPECS = {
    "Biquad_Narrow_int2int_stereo": dict(args=["out:8*a4", "in:8*a4", "in:20", "inout:80", "int"]),
    "powercalc": dict(args=["in:8*a1", "int", "out:4"]),
    "CalculateLimitGain": dict(args=["int"] * 4, ret=True),
    "set_DRC_limit_gain": dict(args=["int"], globals=["drc_struct"]),
    "SoundBooster_DRC_Exe": dict(args=["inout:8*a1", "int"], globals=["drc_struct", "DRC_ChNum"]),
}
GLOBAL_SIZES = {"drc_struct": 24, "DRC_ChNum": 4, "Soundbooster_DRC_Fs": 4, "DRC_ModeFlag": 4,
                "_pcmpower": 6912, "previous_uhq_index": 4}


def parse(spec_arg):
    if spec_arg == "int":
        return ("int", None)
    d, size = spec_arg.split(":", 1)
    return (d, size)


def size_of(expr, ints):
    env = {f"a{i}": v for i, v in enumerate(ints)}
    return int(eval(expr, {}, env))  # noqa: S307 (our own spec strings)


class Recorder:
    def __init__(self, oracle, names):
        self.o = oracle
        self.calls = {n: [] for n in names}
        self._open = {}
        for n in names:
            oracle.probes_enter[n] = self._enter
            oracle.probes_exit[n] = self._exit

    def _snapshot(self, rec, spec):
        ints = [S32(a) for a in rec.args]
        mem = {}
        for i, sa in enumerate(spec["args"]):
            d, size = parse(sa)
            if d != "int":
                mem[i] = self.o.read(rec.args[i], size_of(size, ints))
        glob = {g: self.o.read(self.o.exports[g], GLOBAL_SIZES[g]) for g in spec.get("globals", [])}
        return ints, mem, glob

    def _enter(self, o, rec):
        self._open[id(rec)] = self._snapshot(rec, SPECS[rec.name])

    def _exit(self, o, rec):
        ints, mem_in, glob_in = self._open.pop(id(rec))
        _, mem_out, glob_out = self._snapshot(rec, SPECS[rec.name])
        self.calls[rec.name].append(dict(ints=ints, mem_in=mem_in, mem_out=mem_out,
                                         glob_in=glob_in, glob_out=glob_out, ret=S32(rec.ret)))


def record(names, sig_names, frames):
    """Encode each signal with a fresh oracle per (signal, profile)."""
    out = {n: [] for n in names}
    for sig in sig_names:
        for rate, bitrate in signals.PROFILES:
            o = Oracle(trace=True).open(rate, 2, bitrate)
            r = Recorder(o, names)
            for pcm in signals.frames(sig, rate, frames):
                o.encode(pcm)
            for n in names:
                for c in r.calls[n]:
                    c["where"] = f"{sig}@{bitrate // 1000}k"
                out[n] += r.calls[n]
    return out


def replay(lib, name, call):
    spec = SPECS[name]
    fn = getattr(lib, name)
    bufs, args, argtypes = {}, [], []
    for i, sa in enumerate(spec["args"]):
        d, _ = parse(sa)
        if d == "int":
            args.append(call["ints"][i])
            argtypes.append(ctypes.c_int32)
        else:
            raw = call["mem_in"][i]
            bufs[i] = ctypes.create_string_buffer(raw, len(raw))
            args.append(bufs[i])
            argtypes.append(ctypes.c_void_p)
    fn.argtypes = argtypes
    fn.restype = ctypes.c_int32 if spec.get("ret") else None
    for g, raw in call["glob_in"].items():
        ctypes.memmove(ctypes.addressof(ctypes.c_char.in_dll(lib, g)), raw, len(raw))
    ret = fn(*args)
    problems = []
    for i, buf in bufs.items():
        want = call["mem_out"][i]
        got = buf.raw[:len(want)]
        if got != want:
            k = next(j for j in range(len(want)) if got[j] != want[j])
            problems.append(f"arg{i} byte {k}: got {got[k & ~3:(k & ~3) + 4].hex()} "
                            f"want {want[k & ~3:(k & ~3) + 4].hex()}")
    for g, want in call["glob_out"].items():
        got = ctypes.string_at(ctypes.addressof(ctypes.c_char.in_dll(lib, g)), len(want))
        if got != want:
            problems.append(f"global {g}: got {got.hex()} want {want.hex()}")
    if spec.get("ret") and ret != call["ret"]:
        problems.append(f"ret {ret} want {call['ret']}")
    return problems


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("names", nargs="*")
    ap.add_argument("--signals", default=",".join(signals.NAMES))
    ap.add_argument("--frames", type=int, default=8)
    a = ap.parse_args()
    names = a.names or list(SPECS)
    lib = ctypes.CDLL(str(LIBSSC / "build" / "libssc.dll"))
    recs = record(names, a.signals.split(","), a.frames)
    fails = 0
    for n in names:
        bad = None
        for c in recs[n]:
            p = replay(lib, n, c)
            if p:
                bad = (c["where"], p)
                break
        print(f"{'PASS' if not bad else 'FAIL'}  {n}: {len(recs[n])} calls"
              + ("" if not bad else f"\n      {bad[0]}: {bad[1]}"))
        fails += bad is not None
    print(f"{len(names) - fails}/{len(names)} passed")
    sys.stdout.flush()
    os._exit(1 if fails else 0)


if __name__ == "__main__":
    main()
