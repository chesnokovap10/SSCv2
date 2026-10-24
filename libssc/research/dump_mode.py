#!/usr/bin/env python3
"""Dump the blob's two static CELT modes and named data tables.

ssc_custom_mode_create(Fs, 864, &err): 44100/48000 -> va 0x28a18, 96000 -> va 0x28aa0.

Samsung's struct differs from libopus OpusCustomMode (no preemph[], no maxLM,
a second 11x22 allocation table, 2 FFT states, int32 caps per band):
    0 Fs            4 overlap        8 nbEBands       12 effEBands
   16 eBands*      24 nbShortMdcts  28 shortMdctSize  32 nbAllocVectors
   40 allocVectors* (u8 11x22)      48 allocVectors2* (u8 11x22, Samsung)
   56 logN*  (i16 x22)              64 window* (i32 Q31 x overlap)
   72 mdct { n, maxshift, kfft[2]*, trig* }          (72..103)
  104 cache { size, index*, bits*, caps* (i32 x22) } (104..135)

  py -3.14 libssc/research/dump_mode.py            # human-readable
  py -3.14 libssc/research/dump_mode.py --json F   # all tables for phase 2
"""

import argparse
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "oracle"))
from ssc_oracle import IMAGE_BASE, Oracle  # noqa: E402

MODES = {"48k": 0x28A18, "96k": 0x28AA0}
NAMED = {  # exported data objects: name -> (element format, count)
    "eMeans": ("b", 25), "tf_select_table": ("b", 8), "coeffs": ("i", 5),
    "coeffs96andbelow": ("i", 5), "cutoff_start_index": ("i", 2),
    "cutoff_start_uhq_index": ("i", 16), "win_square": ("i", 108), "margin": ("i", 1),
    "headroom_gain": ("i", 240),
}


def va(p):
    return p - IMAGE_BASE


def read_mode(o, mode_va):
    r = o.read(IMAGE_BASE + mode_va, 136)
    Fs, overlap, nb, eff = struct.unpack_from("<4i", r, 0)
    eBands_p, = struct.unpack_from("<Q", r, 16)
    nbShort, shortSize, nbAlloc = struct.unpack_from("<3i", r, 24)
    alloc_p, alloc2_p, logN_p, window_p = struct.unpack_from("<4Q", r, 40)
    n, maxshift = struct.unpack_from("<2i", r, 72)
    kfft_p = struct.unpack_from("<2Q", r, 80)
    trig_p, = struct.unpack_from("<Q", r, 96)
    csize, = struct.unpack_from("<i", r, 104)
    cidx_p, cbits_p, ccaps_p = struct.unpack_from("<3Q", r, 112)
    kfft = []
    for k in kfft_p:
        nfft, shift = struct.unpack_from("<2i", o.read(k, 8), 0)
        pa, pb = struct.unpack_from("<2Q", o.read(k + 8, 16), 0)
        kfft.append(dict(va=va(k), nfft=nfft, shift=shift, bitrev_va=va(pa), twiddles_va=va(pb)))
    # Shared MDCT/FFT tables (extents = distance to the next known table).
    tw_va, br144_va = va(struct.unpack_from("<Q", o.read(kfft_p[0] + 16, 8))[0]),         va(struct.unpack_from("<Q", o.read(kfft_p[0] + 8, 8))[0])
    br18_va = va(struct.unpack_from("<Q", o.read(kfft_p[1] + 8, 8))[0])
    shared = dict(
        trig=o.read_i32(trig_p, 433),          # 0x14dc0..0x15484
        bitrev144=o.read_i16(IMAGE_BASE + br144_va, 144),
        twiddles=o.read_i32(IMAGE_BASE + tw_va, 864),   # 432 x (re, im)
        bitrev18=o.read_i16(IMAGE_BASE + br18_va, 18),
    )
    return dict(
        shared=shared,
        va=mode_va, Fs=Fs, overlap=overlap, nbEBands=nb, effEBands=eff,
        nbShortMdcts=nbShort, shortMdctSize=shortSize, nbAllocVectors=nbAlloc,
        eBands=o.read_i16(eBands_p, nb + 1), eBands_va=va(eBands_p),
        allocVectors=list(o.read(alloc_p, nbAlloc * nb)), allocVectors_va=va(alloc_p),
        allocVectors2=list(o.read(alloc2_p, nbAlloc * nb)), allocVectors2_va=va(alloc2_p),
        logN=o.read_i16(logN_p, nb), logN_va=va(logN_p),
        window=o.read_i32(window_p, overlap), window_va=va(window_p),
        mdct=dict(n=n, maxshift=maxshift, trig_va=va(trig_p), kfft=kfft),
        cache=dict(size=csize, index=o.read_i16(cidx_p, 5 * nb), index_va=va(cidx_p),
                   bits=list(o.read(cbits_p, csize)), bits_va=va(cbits_p),
                   caps=o.read_i32(ccaps_p, nb), caps_va=va(ccaps_p)),
    )


def print_mode(label, m):
    nb = m["nbEBands"]
    print(f"=== mode {label} @ va {m['va']:#x}")
    print(f"Fs={m['Fs']} overlap={m['overlap']} nbEBands={nb} effEBands={m['effEBands']} "
          f"nbShortMdcts={m['nbShortMdcts']} shortMdctSize={m['shortMdctSize']} "
          f"nbAllocVectors={m['nbAllocVectors']}")
    print(f"eBands  @{m['eBands_va']:#x}: {m['eBands']}")
    print(f"logN    @{m['logN_va']:#x}: {m['logN']}")
    for key in ("allocVectors", "allocVectors2"):
        print(f"{key} @{m[key + '_va']:#x}:")
        av = m[key]
        for i in range(m["nbAllocVectors"]):
            print("   ", av[i * nb:(i + 1) * nb])
    w = m["window"]
    print(f"window  @{m['window_va']:#x} (i32 Q31): {w[:4]} ... {w[-3:]}")
    md = m["mdct"]
    print(f"mdct n={md['n']} maxshift={md['maxshift']} trig @{md['trig_va']:#x}")
    for i, k in enumerate(md["kfft"]):
        print(f"  kfft[{i}] @{k['va']:#x}: nfft={k['nfft']} shift={k['shift']} "
              f"bitrev @{k['bitrev_va']:#x} twiddles @{k['twiddles_va']:#x}")
    c = m["cache"]
    print(f"cache size={c['size']} index @{c['index_va']:#x} bits @{c['bits_va']:#x} "
          f"caps @{c['caps_va']:#x}")
    print(f"  index (5x{nb}): {c['index'][:nb]} ...")
    print(f"  caps:  {c['caps']}")


def read_named(o):
    out = {}
    for name, (fmt, count) in NAMED.items():
        addr = o.exports[name]
        size = struct.calcsize(fmt)
        out[name] = list(struct.unpack(f"<{count}{fmt}", o.read(addr, size * count)))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--json")
    a = ap.parse_args()
    o = Oracle()
    modes = {label: read_mode(o, mva) for label, mva in MODES.items()}
    shared = modes["48k"].pop("shared")
    assert shared == modes["96k"].pop("shared")
    named = read_named(o)
    if a.json:
        Path(a.json).write_text(json.dumps(dict(modes=modes, shared=shared, named=named), indent=1))
        print(a.json)
        return
    for label, m in modes.items():
        print_mode(label, m)
        print()
    for name, vals in named.items():
        print(f"{name}: {vals if len(vals) <= 25 else vals[:12] + ['...']}")


if __name__ == "__main__":
    main()
