#!/usr/bin/env python3
"""Twin test bench: libssc.dll vs the blob (Unicorn oracle), same function names,
same struct layouts, same inputs.

  py -3.14 libssc/build.py && py -3.14 libssc/test/twin.py [-n 2000]

Checks:
  modes      both SscMode structs field by field, including every pointed-to table
  functions  math helpers, haar1, the whole range coder (random inputs)
  state      ssc_encoder_init: state bytes after init (mode pointer excluded)
  frames     ssc_encode on the goldens: header bytes and frame length (payload: phase 3)
"""

import argparse
import ctypes
import os
import random
import struct
import sys
from pathlib import Path

LIBSSC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(LIBSSC / "oracle"))
sys.path.insert(0, str(LIBSSC / "research" / "difftest"))
from ssc_oracle import IMAGE_BASE, IO_BASE, TESTDATA, Oracle, golden_pcm, read_golden  # noqa
import difftest as dt  # noqa: E402  (random input generators)

S32 = Oracle.s32
VP = ctypes.c_void_p


def load_lib():
    lib = ctypes.CDLL(str(LIBSSC / "build" / "libssc.dll"))
    i32, u32 = ctypes.c_int32, ctypes.c_uint32
    sigs = {
        "ec_ilog": ([u32], i32), "ssc_rcp": ([i32], i32), "ssc_sqrt": ([i32], i32),
        "ssc_rsqrt_norm": ([i32], ctypes.c_int16), "ssc_cos_norm": ([i32], ctypes.c_int16),
        "frac_div32": ([i32, i32], i32), "ssc_lcg_rand": ([u32], u32),
        "haar1": ([VP, i32, i32], None),
        "ec_enc_init": ([VP, VP, u32], None), "ec_encode": ([VP, u32, u32, u32], None),
        "ec_encode_bin": ([VP, u32, u32, u32], None), "ec_enc_bit_logp": ([VP, i32, u32], None),
        "ec_enc_icdf": ([VP, i32, VP, u32], None), "ec_enc_uint": ([VP, u32, u32], None),
        "ec_enc_bits": ([VP, u32, u32], None), "ec_laplace_encode": ([VP, VP, u32, i32], None),
        "ec_tell_frac": ([VP], u32), "ec_enc_done": ([VP], None),
        "ssc_custom_mode_create": ([i32, i32, VP], VP),
        "ssc_encoder_get_size": ([i32, i32], i32),
        "ssc_encoder_init": ([VP, i32, i32, i32], i32),
        "ssc_encode": ([VP, VP, i32, VP, i32], i32),
    }
    for name, (args, res) in sigs.items():
        f = getattr(lib, name)
        f.argtypes, f.restype = args, res
    return lib


# ------------------------------------------------------------------- modes
MODE_ARRAYS = [  # (offset of pointer, element fmt, count(mode) )
    (16, "h", lambda m: m["nb"] + 1, "eBands"),
    (40, "B", lambda m: m["na"] * m["nb"], "allocVectors"),
    (48, "B", lambda m: m["na"] * m["nb"], "allocVectors2"),
    (56, "h", lambda m: m["nb"], "logN"),
    (64, "i", lambda m: m["ov"], "window"),
    (96, "i", lambda m: 433, "mdct.trig"),
    (112, "h", lambda m: 5 * m["nb"], "cache.index"),
    (120, "B", lambda m: m["csize"], "cache.bits"),
    (128, "i", lambda m: m["nb"], "cache.caps"),
]


def mode_view(read, base):
    raw = read(base, 136)
    fs, ov, nb, eff = struct.unpack_from("<4i", raw, 0)
    na, = struct.unpack_from("<i", raw, 32)
    csize, = struct.unpack_from("<i", raw, 104)
    m = dict(nb=nb, na=na, ov=ov, csize=csize)
    scalars = (raw[0:16], raw[24:36], raw[72:80], raw[104:108])
    arrays = {}
    for off, fmt, cnt, name in MODE_ARRAYS:
        p, = struct.unpack_from("<Q", raw, off)
        n = cnt(m)
        arrays[name] = read(p, struct.calcsize(fmt) * n)
    for i in range(2):  # kfft states and their tables
        k, = struct.unpack_from("<Q", raw, 80 + 8 * i)
        ks = read(k, 24)
        nfft, shift, br, tw = struct.unpack("<iiQQ", ks)
        arrays[f"kfft{i}"] = ks[:8]
        arrays[f"kfft{i}.bitrev"] = read(br, 2 * nfft)
        arrays[f"kfft{i}.twiddles"] = read(tw, 4 * 864)
    return scalars, arrays


def test_modes(o, lib):
    bad = []
    lread = lambda p, n: ctypes.string_at(p, n)  # noqa: E731
    for fs in (48000, 96000):
        b = mode_view(o.read, o.call("ssc_custom_mode_create", fs, 864, 0))
        l = mode_view(lread, lib.ssc_custom_mode_create(fs, 864, None))
        if b[0] != l[0]:
            bad.append(f"{fs}: scalar fields differ")
        for name in b[1]:
            if b[1][name] != l[1][name]:
                bad.append(f"{fs}: {name} differs")
    return [("modes 48k+96k (all fields and tables)", bad[0] if bad else None)]


# --------------------------------------------------------------- functions
def test_scalars(o, lib, rng, n):
    rows = []
    for blob_name, _ref, gen, norm in dt.scalar_cases(rng, n):
        fn = getattr(lib, blob_name)
        bad = None
        for _ in range(n):
            args = gen()
            b = norm(o.call(blob_name, *[a & 0xFFFFFFFF for a in args], max_insns=1_000_000))
            l = norm(fn(*args))
            if b != l:
                bad = (args, b, l)
                break
        rows.append((blob_name, bad))
    return rows


def test_haar1(o, lib, rng, n):
    for _ in range(max(1, n // 10)):
        stride = rng.choice([1, 2, 4, 8])
        n0 = rng.choice([2, 4, 8, 16, 36, 54])  # per-stride count; buffer is n0*stride
        raw = struct.pack(f"<{n0 * stride}h", *[rng.randrange(-32768, 32768) for _ in range(n0 * stride)])
        o.uc.mem_write(IO_BASE, raw)
        o.call("haar1", IO_BASE, n0, stride)
        buf = ctypes.create_string_buffer(raw, len(raw))
        lib.haar1(buf, n0, stride)
        if o.read(IO_BASE, len(raw)) != buf.raw:
            return [("haar1", (n0, stride))]
    return [("haar1", None)]


def lib_script(lib, size, ops):
    ec = ctypes.create_string_buffer(0x100)
    buf = ctypes.create_string_buffer(size)
    icdf = [ctypes.create_string_buffer(t, len(t)) for t in dt.ICDF]
    val = ctypes.c_int(0)
    lib.ec_enc_init(ec, buf, size)
    tells = []
    for k, a, b, c in ops:
        if k == 0:
            lib.ec_encode(ec, a, b, c)
        elif k == 1:
            lib.ec_encode_bin(ec, a, b, c)
        elif k == 2:
            lib.ec_enc_bit_logp(ec, a, b)
        elif k == 3:
            lib.ec_enc_icdf(ec, a, icdf[b], c)
        elif k == 4:
            lib.ec_enc_uint(ec, a, b)
        elif k == 5:
            lib.ec_enc_bits(ec, a, b)
        elif k == 6:
            val.value = a
            lib.ec_laplace_encode(ec, ctypes.byref(val), b, c)
        tells.append(S32(lib.ec_tell_frac(ec)))
    lib.ec_enc_done(ec)
    return buf.raw, tells


def test_ec(o, lib, rng, n):
    bad = None
    for _ in range(max(1, n // 50)):
        size = rng.choice([64, 200, 572, 1200])
        ops = dt.random_script(rng, rng.randrange(1, 80), [0, 1, 2, 3, 4, 5, 6])
        if dt.blob_script(o, size, ops) != lib_script(lib, size, ops):
            bad = ops[:3]
            break
    return [("range coder (all ops, random scripts)", bad)]


# ------------------------------------------------------------------- state
def test_state(o, lib):
    rows = []
    for fs in (48000, 96000):
        size = S32(o.call("ssc_encoder_get_size", 2, fs))
        lsize = lib.ssc_encoder_get_size(2, fs)
        st = IO_BASE + 0x10000
        o.uc.mem_write(st, b"\xAA" * size)  # init must clear it
        bret = S32(o.call("ssc_encoder_init", st, fs, 2, 24))
        bstate = o.read(st, size)
        lbuf = ctypes.create_string_buffer(b"\xAA" * lsize, lsize)
        lret = lib.ssc_encoder_init(lbuf, fs, 2, 24)
        lstate = lbuf.raw
        bad = None
        if size != lsize or bret != lret:
            bad = f"size {size}/{lsize} ret {bret}/{lret}"
        elif bstate[8:] != lstate[8:]:
            off = next(i for i in range(8, size) if bstate[i] != lstate[i])
            bad = f"first diff at +{off:#x}"
        rows.append((f"ssc_encoder_init {fs}", bad))
    return rows


# ------------------------------------------------------------------ frames
def test_frames(lib):
    rows = []
    for path in sorted(TESTDATA.glob("*.golden")):
        g = read_golden(path)
        size = lib.ssc_encoder_get_size(g["channels"], g["rate"])
        st = ctypes.create_string_buffer(size)
        lib.ssc_encoder_init(st, g["rate"], g["channels"], 24)
        out = ctypes.create_string_buffer(4096)
        bad, same = None, 0
        total = 0
        for i, want in enumerate(g["payloads"]):
            pcm = golden_pcm(g["seed"], i, g["rate"], g["channels"])
            n = lib.ssc_encode(st, pcm, 864, out, g["bitrate"])
            got = out.raw[:max(n, 0)]
            if n != len(want) or got[:2] != want[:2] or got[3] != want[3] or \
                    (got[2] & 0xF0) != (want[2] & 0xF0):
                bad = bad or f"frame {i}: {got[:4].hex()}/{n} vs {want[:4].hex()}/{len(want)}"
            same += sum(1 for a, b in zip(got[4:], want[4:]) if a == b)
            total += len(want) - 4
        rows.append((f"ssc_encode header+size {path.stem}", bad,
                     f"payload bytes equal {same}/{total} (phase 3)"))
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-n", type=int, default=2000)
    ap.add_argument("--seed", type=int, default=7)
    a = ap.parse_args()
    o = Oracle()
    lib = load_lib()
    rng = random.Random(a.seed)
    rows = []
    rows += test_modes(o, lib)
    rows += test_scalars(o, lib, rng, a.n)
    rows += test_haar1(o, lib, rng, a.n)
    rows += test_ec(o, lib, rng, a.n)
    rows += test_state(o, lib)
    rows += test_frames(lib)
    fails = 0
    for row in rows:
        name, bad = row[0], row[1]
        note = f"  ({row[2]})" if len(row) > 2 else ""
        print(f"{'PASS' if bad is None else 'FAIL'}  {name}{note}" +
              ("" if bad is None else f"\n      {bad}"))
        fails += bad is not None
    print(f"{len(rows) - fails}/{len(rows)} passed")
    sys.stdout.flush()
    os._exit(1 if fails else 0)


if __name__ == "__main__":
    main()
