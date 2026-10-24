#!/usr/bin/env python3
"""Stage bench: run the blob and libssc encoders side by side on the same frames
and compare named checkpoints after every frame. Checkpoints are added as the
port of the ssc_encode chain advances (see libssc/PLAN.md, phase 3).

  py -3.14 libssc/build.py && py -3.14 libssc/test/stages.py [--frames 12] [--rates all]
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
from ssc_oracle import IO_BASE, Oracle  # noqa: E402
from unicorn.arm64_const import UC_ARM64_REG_SP  # noqa: E402
import signals  # noqa: E402

FRAME = 864
PCM_BYTES = FRAME * 2 * 4
IN_SHARED = 2 * (FRAME + 108) * 4
PRE_SHARED = 2 * (FRAME + 1024) * 4
EC_FIELDS = slice(8, 0x34)   # ec_ctx without the buffer pointer
OUT_OFF = 0x80000            # oracle's output buffer is IO_BASE + OUT_OFF

# Stage points: libssc calls ssc_stage_hook(id, st, enc); in the blob the same
# moment is the entry (or, with "exit", the return) of the named function, first
# call in the frame.
STAGES = {1: ("pre-MDCT", "ssc_mdct_forward", "enter"),
          2: ("post-MDCT", "compute_band_energies", "enter"),  # long MDCT + headroom
          3: ("post-normalise", "normalise_bands", "exit"),   # 3d: analysis done
          4: ("pre-PVQ", "quant_all_bands", "enter")}         # 3e: energy + allocation
BASE_VIEWS = ("in_shared", "_pre_shared", "state", "range coder", "bytes written")
# Extra views at pre-PVQ: SscStageAlloc in libssc, the quant_all_bands arguments
# (registers + stack) and the allocation/energy arrays in the blob.
ALLOC_VIEWS = ("qab scalars", "tf_res", "pulses", "fine_quant", "fine_priority", "bandE",
               "error (coded bands)")
STAGE_VIEWS = {s: BASE_VIEWS + (ALLOC_VIEWS if s == 4 else ()) for s in STAGES}


def alloc_views(raw, end):
    """Split an SscStageAlloc image (8 int32, 4 x 22 int32, 44 int32, 44 int16)."""
    ints = struct.unpack_from("<8i", raw)
    arr = lambda k: raw[32 + 88 * k: 32 + 88 * (k + 1)]  # noqa: E731
    err = raw[32 + 88 * 4 + 176:]
    return {
        "qab scalars": raw[:32],
        # beyond `end` the blob's arrays hold leftovers of reused locals (unused)
        "tf_res": arr(0), "pulses": arr(1)[:4 * end], "fine_quant": arr(2)[:4 * end],
        "fine_priority": arr(3)[:4 * end],
        "bandE": raw[32 + 88 * 4: 32 + 88 * 4 + 176],
        # error beyond `end` may be stack garbage in the blob (intra copy)
        "error (coded bands)": err[:2 * end] + err[44:44 + 2 * end],
    }


def snapshot(read, st, st_size, ec, out, glob):
    """Named byte views of one encoder at a stage point (same for both sides)."""
    storage = int.from_bytes(read(ec + 8, 4), "little")
    return {
        "in_shared": glob("in_shared", IN_SHARED),
        "_pre_shared": glob("_pre_shared", PRE_SHARED),
        "state": bytes(8) + read(st + 8, st_size - 8),  # mode pointer zeroed
        "range coder": read(ec + EC_FIELDS.start, EC_FIELDS.stop - EC_FIELDS.start),
        "bytes written": read(out + 4, storage),
    }


class LibEncoder:
    def __init__(self, lib, rate, bitrate):
        self.lib, self.bitrate = lib, bitrate
        lib.ssc_encoder_get_size.restype = ctypes.c_int
        self.size = lib.ssc_encoder_get_size(2, rate)
        self.st = ctypes.create_string_buffer(self.size)
        lib.ssc_encoder_init.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int]
        assert lib.ssc_encoder_init(self.st, rate, 2, 24) == 0
        lib.ssc_encode.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int,
                                   ctypes.c_void_p, ctypes.c_int]
        self.out = ctypes.create_string_buffer(4096)
        self.snaps = {}
        hook_t = ctypes.CFUNCTYPE(None, ctypes.c_int, ctypes.c_void_p, ctypes.c_void_p)
        self._hook = hook_t(self._on_stage)  # keep a reference
        ctypes.c_void_p.in_dll(lib, "ssc_stage_hook").value = \
            ctypes.cast(self._hook, ctypes.c_void_p).value

    def _on_stage(self, stage, st, enc):
        read = lambda p, n: ctypes.string_at(p, n)  # noqa: E731
        self.snaps[stage] = snapshot(read, st, self.size, enc, ctypes.addressof(self.out), self.glob)
        if stage == 4:
            raw = self.glob("ssc_stage_alloc", 648)
            self.snaps[stage].update(alloc_views(raw, struct.unpack_from("<i", raw)[0]))

    def encode(self, pcm):
        self.snaps = {}
        ctypes.memset(self.out, 0, len(self.out))  # the blob helper clears `out` too
        self.pcm = ctypes.create_string_buffer(pcm, len(pcm))
        n = self.lib.ssc_encode(self.st, self.pcm, FRAME, self.out, self.bitrate)
        return self.out.raw[:max(n, 0)]

    def glob(self, name, size):
        return ctypes.string_at(ctypes.addressof(ctypes.c_char.in_dll(self.lib, name)), size)


class BlobEncoder:
    """Oracle with probes that snapshot the blob at the stage points."""

    def __init__(self, rate, bitrate):
        self.o = Oracle(trace=True).open(rate, 2, bitrate)
        self.size = Oracle.s32(self.o.call("ssc_encoder_get_size", 2, rate))
        self.snaps, self.ec = {}, None
        self.o.probes_enter["ec_enc_init"] = lambda o, rec: setattr(self, "ec", rec.args[0])
        for stage, (_name, fn, when) in STAGES.items():
            probes = self.o.probes_exit if when == "exit" else self.o.probes_enter
            probes[fn] = lambda o, rec, s=stage: self._on_stage(s, rec)
        # pointers to arrays that quant_all_bands does not receive
        self.ptrs = {}
        self.o.probes_enter["quant_fine_energy"] = lambda o, rec: self.ptrs.update(
            error=rec.args[3], fine_quant=rec.args[4])
        self.o.probes_enter["compute_allocation"] = lambda o, rec: self.ptrs.update(
            fine_priority=self.stack_arg(11))

    def glob(self, name, size):
        return self.o.read(self.o.exports[name], size)

    def stack_arg(self, k):
        """Argument k (>= 8) at function entry (AAPCS64: 8-byte slots at sp)."""
        sp = self.o.uc.reg_read(UC_ARM64_REG_SP)
        return int.from_bytes(self.o.read(sp + 8 * (k - 8), 8), "little")

    def _on_stage(self, stage, rec):
        if stage in self.snaps:
            return
        self.snaps[stage] = snapshot(self.o.read, self.o.state, self.size, self.ec,
                                     IO_BASE + OUT_OFF, self.glob)
        if stage == 4:
            a = rec.args
            s32 = Oracle.s32
            end = s32(a[1])
            scal = [end, s32(a[6]), s32(a[7])] + [s32(self.stack_arg(k)) for k in (8, 9, 11, 12, 14)]
            rd = lambda p, n: self.o.read(p, n)  # noqa: E731
            raw = (struct.pack("<8i", *scal) + rd(self.stack_arg(10), 88) + rd(a[5], 88)
                   + rd(self.ptrs["fine_quant"], 88) + rd(self.ptrs["fine_priority"], 88)
                   + rd(a[4], 176) + rd(self.ptrs["error"], 88))
            self.snaps[stage].update(alloc_views(raw, end))

    def encode(self, pcm):
        self.snaps = {}
        return self.o.encode(pcm)

    def read(self, addr, n):
        return self.o.read(addr, n)

    @property
    def exports(self):
        return self.o.exports

    @property
    def state(self):
        return self.o.state


def hdr_fixed(f):
    """Header without the flags set inside the CELT part (byte2 bits 2-3, byte3 bits 5-7)."""
    return bytes([f[0], f[1], f[2] & 0xF3, f[3] & 0x1F])


def hdr_flags(f):
    return bytes([f[2] & 0x0C, f[3] & 0xE0])


# Checkpoints that depend on code not ported yet: reported, but not a failure.
PENDING = set()

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
    # everything the next frame depends on
    "state after frame": (lambda o: o.read(o.state + 8, o.size - 8), lambda l: l.st.raw[8:]),
    "in_shared after frame": (lambda o: o.read(o.exports["in_shared"], IN_SHARED),
                              lambda l: l.glob("in_shared", IN_SHARED)),
    "_pre_shared after frame": (lambda o: o.read(o.exports["_pre_shared"], PRE_SHARED),
                                lambda l: l.glob("_pre_shared", PRE_SHARED)),
    "previous_uhq_index": (lambda o: o.read(o.exports["previous_uhq_index"], 4),
                           lambda l: l.glob("previous_uhq_index", 4)),
    "CELT payload": (lambda o: o.last[4:], lambda l: l.last[4:]),
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--frames", type=int, default=12)
    ap.add_argument("--signals", default=",".join(signals.NAMES))
    ap.add_argument("--rates", choices=["basic", "all"], default="basic",
                    help="basic: the 6 golden profiles; all: all 14 bitrates")
    a = ap.parse_args()
    lib = ctypes.CDLL(str(LIBSSC / "build" / "libssc.dll"))
    stage_names = [f"{label}: {view}" for stage, (label, _fn, _when) in STAGES.items()
                   for view in STAGE_VIEWS[stage]]
    first_fail = {k: None for k in list(CHECKPOINTS) + stage_names}
    payload_same = payload_total = frames = 0
    for sig in a.signals.split(","):
        for rate, bitrate in signals.profiles(a.rates):
            o = BlobEncoder(rate, bitrate)
            l = LibEncoder(lib, rate, bitrate)
            for i, pcm in enumerate(signals.frames(sig, rate, a.frames)):
                o.last = o.encode(pcm)
                l.last = l.encode(pcm)
                frames += 1
                where = f"{sig}@{bitrate // 1000}k frame {i}"
                for name, (rb, rl) in CHECKPOINTS.items():
                    if first_fail[name] is None and rb(o) != rl(l):
                        first_fail[name] = where
                for stage, (label, _fn, _when) in STAGES.items():
                    bs, ls = o.snaps.get(stage), l.snaps.get(stage)
                    for view in STAGE_VIEWS[stage]:
                        key = f"{label}: {view}"
                        if first_fail[key] is not None:
                            continue
                        if bs is None or ls is None:
                            if bs is not ls:
                                first_fail[key] = f"{where}: stage reached only on one side"
                            continue
                        b, x = bs[view], ls[view]
                        if b != x:
                            k = next((j for j in range(min(len(b), len(x))) if b[j] != x[j]),
                                     min(len(b), len(x)))
                            first_fail[key] = f"{where}, byte {k:#x}"
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
