#!/usr/bin/env python3
"""Deterministic test signals: interleaved stereo int32 frames of 864 samples at
the encoder's 2^29 scale (what the app feeds after WASAPI float -> int32)."""

import math
import random
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "oracle"))
from ssc_oracle import FRAME_SAMPLES, GOLDEN_SEED, golden_pcm  # noqa: E402

SCALE = 1 << 29
# (encoder sample rate, bitrate) — the 6 golden profiles plus the other basic rates
PROFILES = [(48000, 128000), (48000, 192000), (48000, 229000), (96000, 250000),
            (96000, 442000), (96000, 584000)]
NAMES = ["golden", "silence", "noise", "loud", "sweep", "chirp_lr", "clicks"]


def _pack(vals):
    return struct.pack("<%di" % len(vals), *vals)


def _clip(v):
    return max(-(1 << 31), min((1 << 31) - 1, int(v)))


def frames(name, rate, count):
    rng = random.Random(hash(name) & 0xFFFF)
    t0 = 0
    for f in range(count):
        if name == "golden":
            yield golden_pcm(GOLDEN_SEED, f, rate)
            continue
        vals = []
        for i in range(FRAME_SAMPLES):
            t = (t0 + i) / rate
            if name == "silence":
                l = r = 0
            elif name == "noise":
                l, r = rng.gauss(0, 0.15) * SCALE, rng.gauss(0, 0.15) * SCALE
            elif name == "loud":   # near/over full scale: exercises the DRC limiter
                l = 0.98 * SCALE * math.sin(2 * math.pi * 100 * t) + rng.uniform(-0.2, 0.2) * SCALE
                r = 0.98 * SCALE * math.sin(2 * math.pi * 3000 * t)
            elif name == "sweep":  # 20 Hz -> 20 kHz log sweep over ~0.5 s
                f0 = 20 * (1000 ** min(1.0, t / 0.5))
                l = r = 0.5 * SCALE * math.sin(2 * math.pi * f0 * t)
            elif name == "chirp_lr":  # different content per channel
                l = 0.4 * SCALE * math.sin(2 * math.pi * (200 + 4000 * t) * t)
                r = 0.3 * SCALE * math.sin(2 * math.pi * 1500 * t) * math.sin(2 * math.pi * 3 * t)
            elif name == "clicks":  # sparse transients
                k = (t0 + i) % 4000
                l = r = (0.9 * SCALE if k < 8 else 0) + rng.gauss(0, 0.002) * SCALE
            vals += [_clip(l), _clip(r)]
        t0 += FRAME_SAMPLES
        yield _pack(vals)
