#!/usr/bin/env python3
"""Reference hashes for the Go package internal/codec/ssc (phase 5).

Encodes the integer test signal of internal/codec/ssc/ssc_test.go (same
generator, see `signal()`) with the blob under the oracle, on all 14 bitrates,
and writes one line per bitrate: `<rate> <bitrate> <frames> <sha256 of the
frames, each prefixed by its 2-byte LE length>`. The Go test encodes the same
signal through cgo and compares.

  py -3.14 libssc/test/cgo_ref.py      # -> internal/codec/ssc/testdata/oracle.txt
"""

import hashlib
import struct
import sys
from pathlib import Path

LIBSSC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(LIBSSC / "oracle"))
from ssc_oracle import Oracle  # noqa: E402

OUT = LIBSSC.parent / "internal" / "codec" / "ssc" / "testdata" / "oracle.txt"
FRAME = 864
FRAMES = 40
RATES = [(48000, b) for b in (88000, 96000, 128000, 192000, 229000, 256000, 328000)] + \
        [(96000, b) for b in (152000, 250000, 291000, 308000, 442000, 584000, 886000)]


def signal(frame):
    """Interleaved stereo int32, 24-bit scale. Integer only, so Go and Python
    agree exactly: two triangle waves plus LCG noise; every 7th frame is driven
    to full scale (DRC), every 11th is silent."""
    x = (0x1234567 + frame * 0x9E3779B9) & 0xFFFFFFFF
    out = []
    for i in range(FRAME):
        t = frame * FRAME + i
        x = (x * 1103515245 + 12345) & 0xFFFFFFFF
        noise = ((x >> 8) & 0xFFFFFF) - 0x800000  # 24-bit
        for period, amp in ((109, 1 << 21), (251, 1 << 20)):
            p = t % period
            tri = (4 * p * amp) // period - amp if p < period // 2 else 3 * amp - (4 * p * amp) // period
            v = tri + (noise >> 5)
            if frame % 7 == 3:
                v *= 4
            if frame % 11 == 5:
                v = 0
            out.append(max(-(1 << 23), min((1 << 23) - 1, v)))
    return out


def main():
    lines = []
    for rate, bitrate in RATES:
        o = Oracle().open(rate, 2, bitrate)
        h = hashlib.sha256()
        for f in range(FRAMES):
            frame = o.encode(struct.pack("<%di" % (2 * FRAME), *signal(f)))
            h.update(struct.pack("<H", len(frame)) + frame)
        lines.append(f"{rate} {bitrate} {FRAMES} {h.hexdigest()}")
        print(lines[-1], flush=True)
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text("\n".join(lines) + "\n")
    print(OUT)


if __name__ == "__main__":
    main()
