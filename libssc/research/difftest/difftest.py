#!/usr/bin/env python3
"""Differential test: blob (via the Unicorn oracle) vs libopus CELT reference DLLs.

Same random inputs go to the blob function and to ref_<tag>.dll (build_ref.py);
any mismatch is printed with the first failing input.

  py -3.14 libssc/research/difftest/difftest.py                 # all tags in build/
  py -3.14 libssc/research/difftest/difftest.py --tags v1.3.1 -n 20000
"""

import argparse
import ctypes
import os
import random
import struct
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parents[1] / "oracle"))
from ssc_oracle import IO_BASE, Oracle  # noqa: E402

S32 = Oracle.s32


def s16(v):
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


class Ref:
    def __init__(self, path):
        self.dll = ctypes.CDLL(str(path))
        i32, u32 = ctypes.c_int32, ctypes.c_uint32
        sig = {
            "ref_ec_ilog": ([u32], i32), "ref_celt_rcp": ([i32], i32),
            "ref_celt_sqrt": ([i32], i32), "ref_celt_rsqrt_norm": ([i32], i32),
            "ref_celt_cos_norm": ([i32], i32), "ref_frac_div32": ([i32, i32], i32),
            "ref_lcg_rand": ([u32], u32),
            "ref_haar1": ([ctypes.c_void_p, ctypes.c_int, ctypes.c_int], None),
            "ref_ec_script": ([ctypes.c_void_p, ctypes.c_int, ctypes.c_void_p, ctypes.c_int,
                               ctypes.c_void_p], ctypes.c_int),
        }
        for name, (args, res) in sig.items():
            f = getattr(self.dll, name)
            f.argtypes, f.restype = args, res
            setattr(self, name[4:], f)


# ----------------------------------------------------------------- scalar
def scalar_cases(rng, n):
    """(blob name, ref attr, arg generator, result normaliser)."""
    pos31 = lambda: (rng.randrange(1, 1 << 31),)           # noqa: E731
    small = lambda: (rng.choice([rng.randrange(1, 1 << rng.randrange(1, 32)),  # noqa: E731
                                 rng.randrange(1, 1 << 31)]),)
    return [
        ("ec_ilog", "ec_ilog", lambda: (rng.randrange(0, 1 << 32),), S32),
        ("ssc_rcp", "celt_rcp", small, S32),
        ("ssc_sqrt", "celt_sqrt", small, S32),
        ("ssc_rsqrt_norm", "celt_rsqrt_norm", lambda: (rng.randrange(16384, 65536),), s16),
        ("ssc_cos_norm", "celt_cos_norm", lambda: (rng.randrange(-(1 << 17), 1 << 17),), s16),
        ("frac_div32", "frac_div32",
         lambda: (rng.randrange(-(1 << 30), 1 << 30), rng.randrange(1 << 20, 1 << 31)), S32),
        ("ssc_lcg_rand", "lcg_rand", pos31, lambda v: v & 0xFFFFFFFF),
    ]


def run_scalar(o, ref, rng, n):
    rows = []
    for blob_name, ref_name, gen, norm in scalar_cases(rng, n):
        fn = getattr(ref, ref_name)
        bad = None
        for _ in range(n):
            args = gen()
            b = norm(o.call(blob_name, *[a & 0xFFFFFFFF for a in args], max_insns=1_000_000))
            r = norm(fn(*args))
            if b != r:
                bad = (args, b, r)
                break
        rows.append((blob_name, ref_name, bad))
    return rows


# ------------------------------------------------------------------ haar1
def run_haar1(o, ref, rng, n):
    bad = None
    for _ in range(max(1, n // 20)):
        stride = rng.choice([1, 2, 4, 8])
        n0 = rng.choice([2, 4, 8, 16, 36, 54])  # per-stride count; buffer is n0*stride
        x = [rng.randrange(-32768, 32768) for _ in range(n0 * stride)]
        raw = struct.pack(f"<{n0 * stride}h", *x)
        o.uc.mem_write(IO_BASE, raw)
        o.call("haar1", IO_BASE, n0, stride)
        b = o.read_i16(IO_BASE, n0 * stride)
        buf = ctypes.create_string_buffer(raw, len(raw))
        ref.haar1(buf, n0, stride)
        r = list(struct.unpack(f"<{n0 * stride}h", buf.raw))
        if b != r:
            bad = ((n0, stride), b[:6], r[:6])
            break
    return [("haar1", "haar1", bad)]


# ------------------------------------------------------------ range coder
ICDF = [bytes([25, 23, 2, 0]), bytes([2, 1, 0]), bytes([127, 0])]
ICDF_FTB = [5, 2, 7]
ICDF_NSYM = [4, 3, 2]


def random_script(rng, nops, kinds):
    ops = []
    for _ in range(nops):
        k = rng.choice(kinds)
        if k == 0:
            ft = rng.randrange(2, 1 << 15)  # 24-bit coder: rng > 2^15
            fl = rng.randrange(0, ft)
            fh = rng.randrange(fl + 1, ft + 1)
            ops.append((0, fl, fh, ft))
        elif k == 1:
            bits = rng.randrange(1, 16)
            ft = 1 << bits
            fl = rng.randrange(0, ft)
            fh = rng.randrange(fl + 1, ft + 1)
            ops.append((1, fl, fh, bits))
        elif k == 2:
            ops.append((2, rng.randrange(2), rng.randrange(1, 16), 0))
        elif k == 3:
            t = rng.randrange(3)
            ops.append((3, rng.randrange(ICDF_NSYM[t]), t, ICDF_FTB[t]))
        elif k == 4:
            ft = rng.choice([rng.randrange(2, 256), rng.randrange(2, 1 << 31)])
            ops.append((4, rng.randrange(ft), ft, 0))
        elif k == 5:
            bits = rng.randrange(1, 25)
            ops.append((5, rng.randrange(1 << bits), bits, 0))
        elif k == 6:
            v = int(rng.gauss(0, 4))
            ops.append((6, v, rng.randrange(1, 160) << 7, rng.randrange(1, 180) << 6))
    return ops


def blob_script(o, size, ops):
    ec, buf, val, icdf = IO_BASE + 0x100, IO_BASE + 0x1000, IO_BASE + 0x80, IO_BASE + 0xC0
    o.uc.mem_write(ec, b"\0" * 0x100)
    o.uc.mem_write(buf, b"\0" * size)
    off = 0
    icdf_addr = []
    for t in ICDF:
        o.uc.mem_write(icdf + off, t)
        icdf_addr.append(icdf + off)
        off += 8
    o.call("ec_enc_init", ec, buf, size, max_insns=200_000)
    tells = []
    for k, a, b, c in ops:
        if k == 0:
            o.call("ec_encode", ec, a, b, c, max_insns=200_000)
        elif k == 1:
            o.call("ec_encode_bin", ec, a, b, c, max_insns=200_000)
        elif k == 2:
            o.call("ec_enc_bit_logp", ec, a, b, max_insns=200_000)
        elif k == 3:
            o.call("ec_enc_icdf", ec, a, icdf_addr[b], c, max_insns=200_000)
        elif k == 4:
            o.call("ec_enc_uint", ec, a, b, max_insns=200_000)
        elif k == 5:
            o.call("ec_enc_bits", ec, a, b, max_insns=200_000)
        elif k == 6:
            o.uc.mem_write(val, struct.pack("<i", a))
            o.call("ec_laplace_encode", ec, val, b, c, max_insns=200_000)
        tells.append(S32(o.call("ec_tell_frac", ec, max_insns=200_000)))
    o.call("ec_enc_done", ec, max_insns=200_000)
    return o.read(buf, size), tells


def ref_script(ref, size, ops):
    buf = ctypes.create_string_buffer(size)
    flat = (ctypes.c_int * (4 * len(ops)))(*[x for op in ops for x in op])
    tells = (ctypes.c_int * len(ops))()
    ref.ec_script(buf, size, flat, len(ops), tells)
    return buf.raw, list(tells)


def run_ec(o, ref, rng, n):
    rows = []
    groups = [("ec_encode", [0]), ("ec_encode_bin", [1]), ("ec_enc_bit_logp", [2]),
              ("ec_enc_icdf", [3]), ("ec_enc_uint", [4]), ("ec_enc_bits", [5]),
              ("ec_laplace_encode", [6]), ("ec mix + ec_enc_done", [0, 1, 2, 3, 4, 5, 6])]
    for label, kinds in groups:
        bad = None
        for _ in range(max(1, n // 200)):
            size = rng.choice([64, 200, 572, 1200])
            ops = random_script(rng, rng.randrange(1, 60), kinds)
            b = blob_script(o, size, ops)
            r = ref_script(ref, size, ops)
            if b != r:
                where = "tell" if b[0] == r[0] else "bytes"
                bad = (where, ops[:3], len(ops))
                break
        rows.append((label, "entenc/laplace", bad))
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tags", nargs="*")
    ap.add_argument("-n", type=int, default=5000)
    ap.add_argument("--seed", type=int, default=1)
    a = ap.parse_args()
    dlls = sorted((HERE / "build").glob("ref_*.dll"))
    if a.tags:
        dlls = [d for d in dlls if d.stem[4:] in a.tags]
    o = Oracle()
    results = {}
    for d in dlls:
        ref = Ref(d)
        rows = []
        for runner in (run_scalar, run_haar1, run_ec):
            rows += runner(o, ref, random.Random(a.seed), a.n)
        results[d.stem[4:]] = rows
    tags = list(results)
    names = [r[0] for r in results[tags[0]]]
    w = max(10, max(len(t) for t in tags) + 2)
    print(f"{'blob function':28s}" + "".join(f"{t:>{w}s}" for t in tags))
    for i, name in enumerate(names):
        print(f"{name:28s}" + "".join(
            f"{('same' if results[t][i][2] is None else 'DIFF'):>{w}s}" for t in tags))
    for t in tags:
        for name, _ref, bad in results[t]:
            if bad:
                print(f"  {t} {name}: first diff {bad}")
    sys.stdout.flush()
    os._exit(0)  # skip Unicorn teardown (crashes at interpreter exit on Windows)


if __name__ == "__main__":
    main()
