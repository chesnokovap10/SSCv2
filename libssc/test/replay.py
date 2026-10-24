#!/usr/bin/env python3
"""Replay bench: record real calls of a blob function during encoding (inputs at
entry, outputs at exit, globals both times), then call the libssc twin with the
same inputs and compare byte for byte.

  py -3.14 libssc/test/replay.py                       # all specced functions
  py -3.14 libssc/test/replay.py SoundBooster_DRC_Exe  # one function
  py -3.14 libssc/test/replay.py --signals golden,noise,loud --frames 12

Spec syntax per argument: "int" (32-bit value), "ptr" (a pointer into a shared
global or the mode tables, mapped to libssc's twin object), or "<dir>:<size>"
where dir is in / out / inout and size is a Python expression over a0..a7 (the
int args); "alias:N" passes the same buffer as argument N (in-place functions).
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
from ssc_oracle import IMAGE_BASE, Oracle  # noqa: E402
from unicorn.arm64_const import UC_ARM64_REG_SP  # noqa: E402
import signals  # noqa: E402

S32 = Oracle.s32

BLOB_REGIONS = []
EC_SIZE = 52  # ec_ctx: buf pointer + 11 x uint32 (the 4 padding bytes are not compared)

SPECS = {
    "Biquad_Narrow_int2int_stereo": dict(args=["out:8*a4", "in:8*a4", "in:20", "inout:80", "int"]),
    "powercalc": dict(args=["in:8*a1", "int", "out:4"]),
    "CalculateLimitGain": dict(args=["int"] * 4, ret=True),
    "set_DRC_limit_gain": dict(args=["int"], globals=["drc_struct"]),
    "SoundBooster_DRC_Exe": dict(args=["inout:8*a1", "int"], globals=["drc_struct", "DRC_ChNum"]),
    # 3b: pitch analysis (N = 864, len = N + 1024)
    "_ssc_autocorr": dict(args=["in:1888", "out:20"], ret=True),
    "_ssc_lpc": dict(args=["out:8", "in:20"]),
    "ssc_pitch_xcorr_c1": dict(args=["in:1888", "in:1888", "out:20"]),
    "ssc_pitch_xcorr_c2": dict(args=["in:432", "in:920", "out:976"], ret=True),
    "dual_inner_prod": dict(args=["in:864", "in:864", "in:864", "int", "out:4", "out:4"]),
    "pitch_downsample": dict(args=["pp2in:4*a2", "out:(a2>>1)*2", "int"]),
    # scratch (x_lp4, y_lp4, xcorr) lives in in_shared, so it is compared too
    "pitch_search": dict(args=["ptr", "ptr", "int", "int", "out:4"], globals=["in_shared"]),
    # x is pre[c] + 1024: the history before it is read (x[-T-2..]), hence @4096
    "comb_filter": dict(args=["out:4*a4", "in:4*(a4+1024)@4096", "int", "int", "int", "int", "int",
                              "int"], globals=["win_square"]),
    "remove_doubling": dict(args=["in:((a1+a3)>>1)*2", "int", "int", "int", "inout:4", "int", "int"],
                            ret=16),
    # 3c: MDCT/FFT work inside the shared globals, so their pointers are translated
    "ssc_fft": dict(args=["ptr", "ptr", "ptr"], globals=["_pre_shared"]),
    "ssc_mdct_forward": dict(args=["ptr", "ptr", "ptr", "ptr", "int", "int", "int"],
                             globals=["in_shared", "_pre_shared"]),
    "normal_headroom": dict(args=["inout:6912", "int", "int", "in:46"], globals=["headroom_gain"]),
    "uhq_headroom": dict(args=["inout:6912", "int", "int", "in:46"]),
    # 3d: band analysis (bandE: 2 x 22 int32, bandLogE: 2 x 22 int16)
    "compute_band_energies": dict(args=["ptr", "in:6912", "out:176", "int"]),
    "amp2Log2": dict(args=["ptr", "int", "int", "in:176", "out:88", "int"]),
    # X overwrites freq in place in the blob; separate copies give the same bytes
    "normalise_bands": dict(args=["ptr", "inout:6912", "alias:1", "in:176", "int"]),
    "compute_band_energies_for_lastband": dict(args=["ptr", "in:6912", "out:8*a3", "int", "int",
                                                     "int"]),
    "patch_transient_decision": dict(args=["in:88", "in:88", "int", "int"], ret=True),
    "patch_transient_decision_temporal": dict(args=["ptr", "inout:304", "in:7776"], ret=True),
    # reads xcorr[-1] .. xcorr[n]
    "tone_detect": dict(args=["in:4*a3+8@4", "inout:8", "int", "int"], ret=True),
    # 3e: energy quantisation and allocation ("ec": range coder + its buffer)
    # error[] beyond `end` is copied from an uninitialised stack array when the
    # intra pass wins (never read later): compare only bands < end per channel
    "quant_coarse_energy": dict(args=["ptr", "int", "int", "in:88", "inout:88", "int", "out:88",
                                      "ec", "int", "int", "inout:4"],
                                valid={6: "[(0, 2*a2), (44, 44 + 2*a2)]"}),
    "quant_fine_energy": dict(args=["ptr", "int", "inout:88", "inout:88", "in:88", "ec", "int"]),
    "spreading_decision": dict(args=["ptr", "in:3456", "inout:4", "int", "inout:4", "inout:4",
                                     "int", "int"], ret=True),
    "hysteresis_decision": dict(args=["int", "in:46", "in:46", "int", "int"], ret=True),
    "compute_allocation": dict(args=["ptr", "int", "in:88", "in:88", "int", "inout:4", "inout:4",
                                     "int", "out:4", "out:88", "out:88", "out:88", "ec", "int",
                                     "int", "int"], ret=True),
    # 3f: PVQ
    "encode_pulses": dict(args=["in:4*a1", "int", "int", "ec"]),
    "stereo_itheta": dict(args=["in:2*a3", "in:2*a3", "int", "int"], ret=True),
    "alg_quant": dict(args=["inout:2*a1", "int", "int", "int", "int", "ec"], ret=True,
                      globals=["in_shared"]),
    "quant_energy_finalise": dict(args=["ptr", "int", "inout:88", "in:88", "in:88", "in:88", "int",
                                        "ec", "int"]),
    "quant_all_bands": dict(args=["ptr", "int", "inout:3456", "out:2*a1", "in:176", "in:4*a1",
                                  "int", "int", "int", "int", "in:4*a1", "int", "int", "ec",
                                  "int", "inout:4"], globals=["in_shared"]),
}
GLOBAL_SIZES = {"win_square": 432, "drc_struct": 24, "DRC_ChNum": 4, "Soundbooster_DRC_Fs": 4, "DRC_ModeFlag": 4,
                "_pcmpower": 6912, "previous_uhq_index": 4, "in_shared": 7776, "_pre_shared": 15104,
                "headroom_gain": 960}

# "ptr" args: blob pointers into these objects are mapped to the same offset in
# libssc's object; pointers stored in the mode structs are mapped exactly.
PTR_GLOBALS = ["in_shared", "_pre_shared"]
MODES = {"ssc_mode_48k": 0x28a18, "ssc_mode_96k": 0x28aa0}  # blob va -> libssc symbol
MODE_PTR_FIELDS = [0x10, 0x40, 0x50, 0x58, 0x60]           # eBands, window, kfft[2], trig


def blob_ptr_regions(o):
    """[(blob start, size, (kind, libssc symbol, offset))] for translate()."""
    regions = [(o.exports[g], GLOBAL_SIZES[g], ("global", g, 0)) for g in PTR_GLOBALS]
    for sym, va in MODES.items():
        base = IMAGE_BASE + va
        regions.append((base, 136, ("global", sym, 0)))
        for off in MODE_PTR_FIELDS:
            regions.append((int.from_bytes(o.read(base + off, 8), "little"), 1, ("field", sym, off)))
    return regions


def translate(lib, regions, p):
    for start, size, (kind, sym, off) in sorted(regions, key=lambda r: r[1]):  # exact first
        if start <= p < start + size:
            addr = ctypes.addressof(ctypes.c_char.in_dll(lib, sym))
            if kind == "field":
                return ctypes.c_void_p.from_address(addr + off).value
            return addr + (p - start)
    raise ValueError(f"no libssc twin for blob pointer {p:#x}")


def parse(spec_arg):
    """-> (dir, size expr, offset expr): "in:SIZE@OFF" covers [ptr-OFF, ptr-OFF+SIZE)."""
    if spec_arg in ("int", "ptr", "ec"):
        return (spec_arg, None, "0")
    if spec_arg.startswith("alias:"):   # same pointer as another argument
        return ("alias", spec_arg[6:], "0")
    d, size = spec_arg.split(":", 1)
    size, _, off = size.partition("@")
    return (d, size, off or "0")


def size_of(expr, ints):
    env = {f"a{i}": v for i, v in enumerate(ints)}
    return int(eval(expr, {}, env))  # noqa: S307 (our own spec strings)


class Recorder:
    def __init__(self, oracle, names):
        self.o = oracle
        self.calls = {n: [] for n in names}
        self._open = {}
        self._args = {}
        for n in names:
            oracle.probes_enter[n] = self._enter
            oracle.probes_exit[n] = self._exit

    def _snapshot(self, rec, spec):
        args = self._args[id(rec)]
        ints = [S32(a) for a in args]
        mem = {}
        for i, sa in enumerate(spec["args"]):
            d, size, off = parse(sa)
            if d == "pp2in":
                ptrs = struct.unpack("<2Q", self.o.read(args[i], 16))
                mem[i] = [self.o.read(p, size_of(size, ints)) for p in ptrs]
            elif d == "ec":   # ec_ctx and the bytes of its buffer
                ctx = self.o.read(args[i], EC_SIZE)
                buf, storage = struct.unpack_from("<QI", ctx)
                mem[i] = (ctx, self.o.read(buf, storage))
            elif d not in ("int", "ptr", "alias"):
                mem[i] = self.o.read(args[i] - size_of(off, ints), size_of(size, ints))
        glob = {g: self.o.read(self.o.exports[g], GLOBAL_SIZES[g]) for g in spec.get("globals", [])}
        return ints, mem, glob

    def _enter(self, o, rec):
        # AAPCS64: arguments after x7 sit in 8-byte slots at sp on entry
        n = len(SPECS[rec.name]["args"])
        sp = o.uc.reg_read(UC_ARM64_REG_SP)
        self._args[id(rec)] = list(rec.args) + [int.from_bytes(o.read(sp + 8 * k, 8), "little")
                                                for k in range(max(0, n - 8))]
        self._open[id(rec)] = self._snapshot(rec, SPECS[rec.name])

    def _exit(self, o, rec):
        ints, mem_in, glob_in = self._open.pop(id(rec))
        _, mem_out, glob_out = self._snapshot(rec, SPECS[rec.name])
        full = self._args.pop(id(rec))
        self.calls[rec.name].append(dict(ints=ints, raw=full, mem_in=mem_in, mem_out=mem_out,
                                         glob_in=glob_in, glob_out=glob_out, ret=S32(rec.ret)))


def record(names, sig_names, frames, rates="basic"):
    """Encode each signal with a fresh oracle per (signal, profile)."""
    global BLOB_REGIONS
    out = {n: [] for n in names}
    for sig in sig_names:
        for rate, bitrate in signals.profiles(rates):
            o = Oracle(trace=True).open(rate, 2, bitrate)
            BLOB_REGIONS = blob_ptr_regions(o)  # same layout in every instance
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
    bufs, args, argtypes, keep, ecs = {}, [], [], [], {}
    for i, sa in enumerate(spec["args"]):
        d, _, off = parse(sa)
        if d == "int":
            args.append(call["ints"][i])
            argtypes.append(ctypes.c_int32)
        elif d == "ptr":
            args.append(translate(lib, BLOB_REGIONS, call["raw"][i]))
            argtypes.append(ctypes.c_void_p)
        elif d == "alias":
            args.append(args[int(sa[6:])])
            argtypes.append(ctypes.c_void_p)
        elif d == "ec":
            ctx, raw = call["mem_in"][i]
            buf = ctypes.create_string_buffer(raw, max(1, len(raw)))
            ec = ctypes.create_string_buffer(ctx, EC_SIZE)
            struct.pack_into("<Q", ec, 0, ctypes.addressof(buf))
            ecs[i] = (ec, buf)
            args.append(ctypes.addressof(ec))
            argtypes.append(ctypes.c_void_p)
        elif d == "pp2in":
            chans = [ctypes.create_string_buffer(r, len(r)) for r in call["mem_in"][i]]
            arr = (ctypes.c_void_p * 2)(*[ctypes.addressof(c) for c in chans])
            keep.append((chans, arr))
            args.append(arr)
            argtypes.append(ctypes.c_void_p)
        else:
            raw = call["mem_in"][i]
            bufs[i] = ctypes.create_string_buffer(raw, len(raw))
            args.append(ctypes.addressof(bufs[i]) + size_of(off, call["ints"]))
            argtypes.append(ctypes.c_void_p)
    fn.argtypes = argtypes
    fn.restype = {True: ctypes.c_int32, 16: ctypes.c_int16}.get(spec.get("ret"))
    for g, raw in call["glob_in"].items():
        ctypes.memmove(ctypes.addressof(ctypes.c_char.in_dll(lib, g)), raw, len(raw))
    ret = fn(*args)
    problems = []
    for i, buf in bufs.items():
        want = call["mem_out"][i]
        got = buf.raw[:len(want)]
        if i in spec.get("valid", {}):
            keep_ranges = eval(spec["valid"][i], {}, {f"a{k}": v for k, v in enumerate(call["ints"])})  # noqa: S307
            want = b"".join(want[lo:hi] for lo, hi in keep_ranges)
            got = b"".join(got[lo:hi] for lo, hi in keep_ranges)
        if got != want:
            k = next(j for j in range(len(want)) if got[j] != want[j])
            problems.append(f"arg{i} byte {k}: got {got[k & ~3:(k & ~3) + 4].hex()} "
                            f"want {want[k & ~3:(k & ~3) + 4].hex()}")
    for i, (ec, buf) in ecs.items():
        ctx, raw = call["mem_out"][i]
        if ec.raw[8:EC_SIZE] != ctx[8:EC_SIZE]:
            problems.append(f"arg{i} ec_ctx: got {ec.raw[8:EC_SIZE].hex()} want {ctx[8:EC_SIZE].hex()}")
        elif buf.raw[:len(raw)] != raw:
            k = next(j for j in range(len(raw)) if buf.raw[j] != raw[j])
            problems.append(f"arg{i} ec buffer byte {k}")
    for g, want in call["glob_out"].items():
        got = ctypes.string_at(ctypes.addressof(ctypes.c_char.in_dll(lib, g)), len(want))
        if got != want:
            problems.append(f"global {g}: got {got.hex()} want {want.hex()}")
    want_ret = call["ret"]
    if spec.get("ret") == 16:
        want_ret = ((want_ret & 0xFFFF) ^ 0x8000) - 0x8000
    if spec.get("ret") and ret != want_ret:
        problems.append(f"ret {ret} want {want_ret}")
    return problems


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("names", nargs="*")
    ap.add_argument("--signals", default=",".join(signals.NAMES))
    ap.add_argument("--frames", type=int, default=8)
    ap.add_argument("--rates", choices=["basic", "all"], default="basic")
    a = ap.parse_args()
    names = a.names or list(SPECS)
    lib = ctypes.CDLL(str(LIBSSC / "build" / "libssc.dll"))
    recs = record(names, a.signals.split(","), a.frames, a.rates)
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
