#!/usr/bin/env python3
"""Model of the SSC frame header and byte budget (from ssc_encode @0xd168..0xd504),
checked against every frame of libssc/testdata/*.golden.

Header (4 bytes):
  byte0 = 0xFF
  byte1 = 0xEE (basic) | UHQ: 0xE0 | (frame_counter >> 4)
  byte2 = (frame_counter << 4) | flags  (bits 0-1: state+0xd6, bits 2-3 set later in encode)
  byte3 = (top3 << 5) | rate_index  (rate_index from the table below; top 3 bits can be
          rewritten later in encode, 0b111 in every golden so far)
Budget:
  n = bitrate * frame_size // (mode_Fs * 8)      mode_Fs = 44100 for 44.1/48 kHz, 96000 for UHQ
  if not wide: n += (3 * n) >> 7                 (wide = 256k, 328k and all UHQ rates)
  n |= 1  (round up to odd)
  ec budget = n - 1, frame = 4 + ec budget
frame_counter: 8-bit, +1 per frame (state+0xd4).
"""

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "oracle"))
from ssc_oracle import TESTDATA, read_golden  # noqa: E402

# bitrate -> (byte3, uhq, wide, DRC limit gain passed to set_DRC_limit_gain)
RATES = {
    88000: (0xF0, False, False, 0x76F200),
    96000: (0xF1, False, False, 0x76F200),
    128000: (0xF2, False, False, 0x78B400),
    192000: (0xF3, False, False, 0x7A9400),
    229000: (0xF4, False, False, 0x7A9400),
    328000: (0xF5, False, True, 0x7B4C00),
    256000: (0xF6, False, True, 0x79F800),
    291000: (0xE0, True, True, 0x7B4C00),
    308000: (0xE1, True, True, 0x7B4C00),
    442000: (0xE2, True, True, 0x7B4C00),
    584000: (0xE3, True, True, 0x7B4C00),
    886000: (0xE4, True, True, 0x7B4C00),
    250000: (0xE5, True, True, 0x79F800),
    152000: (0xE6, True, True, 0x79F800),
}
# Note: the DRC gains above are for 24-bit input (state+0x6c == 24); other bit depths
# use different constants (0x76f2 / 0x78b4 / 0x7a94 ...), see ssc_encode @0xd25c.


def budget(bitrate, mode_fs, frame_size=864):
    _b3, _uhq, wide, _g = RATES[bitrate]
    n = bitrate * frame_size // (mode_fs * 8)
    if not wide:
        n += (3 * n) >> 7
    n |= 1
    return n - 1


def header(bitrate, counter):
    b3, uhq, _wide, _g = RATES[bitrate]
    b1 = (0xE0 | ((counter >> 4) & 0xF)) if uhq else 0xEE
    return bytes([0xFF, b1, (counter << 4) & 0xFF, b3])


def main():
    bad = 0
    for path in sorted(TESTDATA.glob("*.golden")):
        g = read_golden(path)
        mode_fs = 96000 if g["rate"] == 96000 else 44100
        ec = budget(g["bitrate"], mode_fs)
        for i, frame in enumerate(g["payloads"]):
            want = header(g["bitrate"], i)
            ok = (len(frame) == 4 + ec and frame[0:2] == want[0:2]
                  and frame[2] & 0xF0 == want[2] & 0xF0 and frame[3] == want[3])
            if not ok:
                bad += 1
                print(f"FAIL {path.name} frame {i}: got {frame[:4].hex()} len {len(frame)}, "
                      f"model {want.hex()} len {4 + ec}")
        flags = sorted({f[2] & 0x0F for f in g["payloads"]})
        print(f"{path.name}: {len(g['payloads'])} frames, budget {ec} bytes, "
              f"byte2 low-nibble flags seen {flags}")
    print("header model:", "OK" if not bad else f"{bad} mismatches")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
