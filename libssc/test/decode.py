#!/usr/bin/env python3
"""Decoder bench (phase 6): libssc encode -> libssc decode, all 14 bitrates.

  py -3.14 libssc/build.py && py -3.14 libssc/test/decode.py [--frames 40] [--signals a,b]
  py -3.14 libssc/test/decode.py --golden          # the blob's golden frames
  py -3.14 libssc/test/decode.py --wav song.wav [--rates 229,256] [--out DIR]
        # listen: song.wav (48 kHz: basic rates, 96 kHz: UHQ) -> SSC -> song.ssc229k.wav

Per bitrate and signal:
  sync  frames whose decoded quantised energies equal the encoder's oldBandE
        (the parse is exact only if every frame matches)
  snr   decoded PCM vs the encoder's input (after its DRC), dB, delay 108,
        first 3 frames skipped
Exit code 1 if any frame is out of sync.
"""

import argparse
import ctypes
import wave
import math
import random
import struct
import sys
from pathlib import Path

LIBSSC = Path(__file__).resolve().parents[1]
FRAME, DELAY = 864, 108
FS24 = 1 << 23
RATES = [(48000, b) for b in (88000, 96000, 128000, 192000, 229000, 256000, 328000)] + [
    (96000, b) for b in (152000, 250000, 291000, 308000, 442000, 584000, 886000)]
# encoder state: in_mem at 0xe0, oldBandE at in_mem + (overlap + 1024) * C int32
OLDBANDE_OFF = 0xE0 + (108 + 1024) * 2 * 4


class Info(ctypes.Structure):
    _fields_ = [(n, ctypes.c_int32) for n in (
        "bitrate", "fs", "counter", "payload", "silence", "transient", "pf_on", "pf_period", "pf_qg",
        "intra", "spread", "intensity", "dual_stereo", "alloc_trim", "codedBands", "drop",
        "anti_collapse", "bits_used")] + [("oldBandE", ctypes.c_int16 * 44),
                                          ("pulses", ctypes.c_int32 * 22),
                                          ("fine_quant", ctypes.c_int32 * 22),
                                          ("offsets", ctypes.c_int32 * 22)]


def load():
    lib = ctypes.CDLL(str(LIBSSC / "build" / "libssc.dll"))
    lib.ssc_encoder_init.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int]
    lib.ssc_encode.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int, ctypes.c_void_p,
                               ctypes.c_int]
    lib.ssc_decoder_create.restype = ctypes.c_void_p
    lib.ssc_decoder_create.argtypes = [ctypes.c_int, ctypes.c_void_p]
    lib.ssc_decoder_destroy.argtypes = [ctypes.c_void_p]
    lib.ssc_decode.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int, ctypes.c_void_p]
    lib.ssc_decoder_info.argtypes = [ctypes.c_void_p, ctypes.POINTER(Info)]
    lib.ssc_decoder_synth_snr.restype = ctypes.c_double
    return lib


# ---- signals (interleaved stereo int32, 2^23 full scale) ----------------------

def signal(name, rate, frames):
    rng = random.Random(sum(map(ord, name)))
    n = frames * FRAME
    out = []
    for i in range(n):
        t = i / rate
        if name == "tone":
            l = r = 0.3 * math.sin(2 * math.pi * 1000 * t)
        elif name == "chord":
            l = sum(0.12 * math.sin(2 * math.pi * f * t) for f in (220, 277.2, 329.6, 440))
            r = sum(0.12 * math.sin(2 * math.pi * f * t + 0.5) for f in (220, 277.2, 329.6, 440))
        elif name == "music":  # harmonic notes with decay, a bass line, hats
            note = int(t * 4)
            f = 110 * 2 ** ((note * 5 % 12) / 12)
            env = math.exp(-6 * (t * 4 - note))
            tone = sum(math.sin(2 * math.pi * f * k * t) / k for k in range(1, 12))
            bass = 0.3 * math.sin(2 * math.pi * 55 * t)
            hat = (rng.random() * 2 - 1) * math.exp(-60 * ((t * 8) % 1)) * 0.3
            l = 0.2 * env * tone + bass + hat
            r = 0.2 * env * tone * 0.8 + bass + hat * 0.6
        elif name == "noise":
            l, r = rng.gauss(0, 0.15), rng.gauss(0, 0.15)
        elif name == "sweep":
            f0, f1, T = 50, rate / 2.2, n / rate
            ph = 2 * math.pi * f0 * T / math.log(f1 / f0) * (math.exp(t / T * math.log(f1 / f0)) - 1)
            l = r = 0.25 * math.sin(ph)
        elif name == "clicks":
            l = r = 0.6 if i % 4410 < 3 else 0.0
        else:
            raise SystemExit("unknown signal " + name)
        out.append(int(max(-1, min(1, l)) * (FS24 - 1)))
        out.append(int(max(-1, min(1, r)) * (FS24 - 1)))
    return out


SIGNALS = ["music", "chord", "tone", "noise", "sweep", "clicks"]


def run(lib, rate, bitrate, sig, frames):
    st = ctypes.create_string_buffer(lib.ssc_encoder_get_size(2, rate) + 16)
    assert lib.ssc_encoder_init(st, rate, 2, 24) == 0
    dec = lib.ssc_decoder_create(rate, None)
    out = ctypes.create_string_buffer(4096)
    pcm_out = (ctypes.c_int32 * (2 * FRAME))()
    info = Info()
    x = signal(sig, rate, frames)
    ref, got = [], []
    sync, first_bad, sizes = 0, None, set()
    for f in range(frames):
        buf = (ctypes.c_int32 * (2 * FRAME))(*x[f * 2 * FRAME:(f + 1) * 2 * FRAME])
        nb = lib.ssc_encode(st, buf, FRAME, out, bitrate)
        assert nb > 0, nb
        sizes.add(nb)
        ref.extend(buf)  # after the DRC
        enc_e = struct.unpack_from("<44h", st.raw, OLDBANDE_OFF)
        r = lib.ssc_decode(dec, out.raw[:nb], nb, pcm_out)
        assert r == FRAME, r
        lib.ssc_decoder_info(dec, ctypes.byref(info))
        if tuple(info.oldBandE) == enc_e:
            sync += 1
        elif first_bad is None:
            first_bad = f
        got.extend(pcm_out)
    lib.ssc_decoder_destroy(dec)
    # SNR with the 108-sample delay, skipping 3 frames
    s = 3 * FRAME
    num = den = 0.0
    for i in range(s, frames * FRAME - DELAY):
        for c in range(2):
            a = ref[2 * i + c]
            b = got[2 * (i + DELAY) + c]
            num += a * a
            den += (a - b) * (a - b)
    snr = 10 * math.log10(num / den) if den > 0 else 200.0
    return sync, first_bad, snr, sorted(sizes)


def goldens(lib):
    """Blob frames (testdata/*.golden): every frame decodes, the parse ends
    inside the frame's budget, output level."""
    sys.path.insert(0, str(LIBSSC / "oracle"))
    from ssc_oracle import read_golden
    pcm = (ctypes.c_int32 * (2 * FRAME))()
    info = Info()
    ok = True
    for path in sorted((LIBSSC / "testdata").glob("*.golden")):
        g = read_golden(path)
        dec = lib.ssc_decoder_create(g["rate"], None)
        spare, peak, n = [], 0, 0
        for fr in g["payloads"]:
            r = lib.ssc_decode(dec, fr, len(fr), pcm)
            lib.ssc_decoder_info(dec, ctypes.byref(info))
            if r != FRAME or info.bits_used > info.payload * 8:
                ok = False
            n += r == FRAME
            spare.append(info.payload * 8 - info.bits_used)
            peak = max(peak, max(abs(v) for v in pcm))
        lib.ssc_decoder_destroy(dec)
        print("%-12s %2d/%d frames, unused bits %d..%d, peak %.2f FS" % (
            path.name, n, len(g["payloads"]), min(spare), max(spare), peak / FS24))
    return ok


def read_wav(path):
    """Stereo PCM (16/24/32 bit) -> interleaved int32 at 2^23 full scale, rate."""
    with wave.open(str(path), "rb") as w:
        ch, width, rate, n = w.getnchannels(), w.getsampwidth(), w.getframerate(), w.getnframes()
        raw = w.readframes(n)
    if width not in (2, 3, 4):
        raise SystemExit("%s: %d-bit PCM not supported" % (path, 8 * width))
    vals = []
    for i in range(0, len(raw), width):
        b = raw[i:i + width]
        v = int.from_bytes(b, "little", signed=True)
        vals.append(v << 8 if width == 2 else v >> 8 if width == 4 else v)
    if ch == 1:
        vals = [v for v in vals for _ in (0, 1)]
    elif ch > 2:
        vals = [v for i, v in enumerate(vals) if i % ch < 2]
    return vals, rate


def write_wav(path, vals, rate):
    with wave.open(str(path), "wb") as w:
        w.setnchannels(2)
        w.setsampwidth(3)
        w.setframerate(rate)
        w.writeframes(b"".join(int(v).to_bytes(3, "little", signed=True) for v in vals))


def wav_mode(lib, src, rates, outdir):
    x, rate = read_wav(src)
    if rate not in (48000, 96000):
        raise SystemExit("%s: %d Hz (48000 for SSC, 96000 for UHQ)" % (src, rate))
    frames = len(x) // (2 * FRAME)
    outdir = Path(outdir) if outdir else Path(src).parent
    for r, bitrate in RATES:
        if r != rate or (rates and str(bitrate // 1000) not in rates):
            continue
        st = ctypes.create_string_buffer(lib.ssc_encoder_get_size(2, rate) + 16)
        lib.ssc_encoder_init(st, rate, 2, 24)
        dec = lib.ssc_decoder_create(rate, None)
        out = ctypes.create_string_buffer(4096)
        pcm = (ctypes.c_int32 * (2 * FRAME))()
        y = []
        for f in range(frames):
            buf = (ctypes.c_int32 * (2 * FRAME))(*x[f * 2 * FRAME:(f + 1) * 2 * FRAME])
            nb = lib.ssc_encode(st, buf, FRAME, out, bitrate)
            lib.ssc_decode(dec, out.raw[:nb], nb, pcm)
            y.extend(pcm)
        lib.ssc_decoder_destroy(dec)
        dst = outdir / ("%s.ssc%dk.wav" % (Path(src).stem, bitrate // 1000))
        write_wav(dst, y[2 * DELAY:], rate)  # drop the codec delay
        print(dst)
    return 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--wav", help="encode + decode this WAV at the --rates (default: all of its rate)")
    ap.add_argument("--out", help="folder for the decoded WAVs (default: next to --wav)")
    ap.add_argument("--golden", action="store_true", help="decode the blob's golden frames")
    ap.add_argument("--frames", type=int, default=40)
    ap.add_argument("--signals", default=",".join(SIGNALS))
    ap.add_argument("--rates", default="")
    a = ap.parse_args()
    lib = load()
    if a.golden:
        return 0 if goldens(lib) else 1
    if a.wav:
        return wav_mode(lib, a.wav, [r for r in a.rates.split(",") if r], a.out)
    sigs = a.signals.split(",")
    rates = [r for r in RATES if not a.rates or str(r[1] // 1000) in a.rates.split(",")]
    d = lib.ssc_decoder_create(48000, None)
    lib.ssc_decoder_destroy(d)
    print("synthesis fit: long %.1f dB, short %.1f dB" % (lib.ssc_decoder_synth_snr(0),
                                                          lib.ssc_decoder_synth_snr(3)))
    print("%-12s" % "rate" + "".join("%16s" % s for s in sigs))
    bad = 0
    for rate, bitrate in rates:
        cells = []
        for sig in sigs:
            sync, first, snr, sizes = run(lib, rate, bitrate, sig, a.frames)
            mark = "" if sync == a.frames else "!%d" % first
            bad += sync != a.frames
            cells.append("%5.1f dB %3d%s" % (snr, sync, mark))
        print("%-12s" % ("%d/%dk" % (rate // 1000, bitrate // 1000)) + "".join("%16s" % c for c in cells))
    print("frames per cell %d; 'N!f' = N in sync, first out of sync at f" % a.frames)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
