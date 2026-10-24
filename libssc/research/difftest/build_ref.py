#!/usr/bin/env python3
"""Build ref_<tag>[+patches].dll: libopus CELT (FIXED_POINT) + ref.c wrappers, MinGW gcc.

Sources are copied to build/src_<name>/ and named patches (Samsung deltas we have
confirmed) are applied as literal text replacements before compiling.

  py -3.14 build_ref.py <opus-source-dir> --tag v1.3.1 [--patch ec24 ...]
"""

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
CELT_SOURCES = ["bands.c", "celt.c", "celt_lpc.c", "cwrs.c", "entcode.c", "entdec.c",
                "entenc.c", "kiss_fft.c", "laplace.c", "mathops.c", "mdct.c", "modes.c",
                "pitch.c", "quant_bands.c", "rate.c", "vq.c"]

# name -> [(file, old, new)]
PATCHES = {
    # Samsung range coder: 24-bit code registers (EC_CODE_BOT 0x8000, carry at bit 23).
    "ec24": [("mfrngcod.h", "# define EC_CODE_BITS  (32)", "# define EC_CODE_BITS  (24)")],
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("opus")
    ap.add_argument("--tag", required=True)
    ap.add_argument("--patch", nargs="*", default=[])
    ap.add_argument("--out", default=str(HERE / "build"))
    a = ap.parse_args()
    opus = Path(a.opus)
    out = Path(a.out)
    name = a.tag + "".join("+" + p for p in a.patch)
    src = out / f"src_{name}"
    if src.exists():
        shutil.rmtree(src)
    shutil.copytree(opus / "celt", src / "celt",
                    ignore=shutil.ignore_patterns("arm", "x86", "mips", "tests", "dump_modes"))
    shutil.copytree(opus / "include", src / "include")
    for p in a.patch:
        for fname, old, new in PATCHES[p]:
            f = src / "celt" / fname
            text = f.read_text()
            if old not in text:
                print(f"patch {p}: '{old}' not found in {fname}", file=sys.stderr)
                return 1
            f.write_text(text.replace(old, new))
    dll = out / f"ref_{name}.dll"
    cmd = ["gcc", "-O2", "-shared", "-o", str(dll),
           "-DFIXED_POINT=1", "-DOPUS_BUILD=1", "-DVAR_ARRAYS=1", "-DDISABLE_FLOAT_API=1",
           "-DHAVE_LRINTF=1", "-DCUSTOM_MODES=1",
           f"-I{src / 'celt'}", f"-I{src / 'include'}",
           str(HERE / "ref.c")] + [str(src / "celt" / s) for s in CELT_SOURCES]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stderr, file=sys.stderr)
        return 1
    print(dll)
    return 0


if __name__ == "__main__":
    sys.exit(main())
