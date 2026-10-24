#!/usr/bin/env python3
"""Build libssc/build/libssc.dll with MinGW gcc (test bench; the Go app will
compile the same sources through cgo).

  py -3.14 libssc/build.py
"""

import subprocess
import sys
from pathlib import Path

LIBSSC = Path(__file__).resolve().parent
SRC = LIBSSC / "src"
# The defines the Opus sources need; keep in sync with the cgo flags (phase 5).
DEFINES = ["-DFIXED_POINT=1", "-DOPUS_BUILD=1", "-DVAR_ARRAYS=1", "-DDISABLE_FLOAT_API=1"]


# Opus files compiled through a wrapper (renamed symbols), not on their own.
INCLUDED_BY_WRAPPER = {"pitch.c", "celt_lpc.c"}


def sources():
    opus = [p for p in sorted((SRC / "opus").glob("*.c")) if p.name not in INCLUDED_BY_WRAPPER]
    return sorted(SRC.glob("*.c")) + opus


def main():
    out = LIBSSC / "build"
    out.mkdir(exist_ok=True)
    dll = out / "libssc.dll"
    # -ffp-contract=off: the float transient detector must not get fused multiply-adds
    # (the blob uses plain fmul/fadd); keep it in the cgo flags too.
    # -include ssc_names.h: exported symbols get the blob's names (ssc_quant_all_bands, ...).
    cmd = ["gcc", "-std=gnu11", "-O2", "-ffp-contract=off", "-Wall", "-Wno-unused-function", "-shared",
           "-include", "ssc_names.h",
           "-o", str(dll), *DEFINES, f"-I{SRC}", f"-I{SRC / 'opus'}",
           *map(str, sources())]
    r = subprocess.run(cmd, capture_output=True, text=True)
    sys.stderr.write(r.stderr)
    if r.returncode:
        return r.returncode
    print(dll)
    return 0


if __name__ == "__main__":
    sys.exit(main())
