package engine

import (
	"fmt"

	"sscv2/internal/bt"
	"sscv2/internal/codec/aac"
	"sscv2/internal/codec/ssc"
)

type aacEnc struct {
	e   *aac.Encoder
	buf []int16
}

func (a *aacEnc) FrameLen() int { return a.e.FrameLen }
func (a *aacEnc) Encode(pcm []float32) ([]byte, error) {
	a.buf = a.buf[:0]
	for _, v := range pcm {
		a.buf = append(a.buf, clamp16(v))
	}
	return a.e.Encode(a.buf)
}
func (a *aacEnc) BitrateKbps() int { return a.e.Bitrate / 1000 }
func (a *aacEnc) Close()           { a.e.Close() }
func (a *aacEnc) Bandwidth() int   { return a.e.Bandwidth() }

// AAC packetisation:
//   - "fit" (default): every LATM frame fits one AVDTP packet, the bitrate is
//     capped by the headphones' MTU (Galaxy Buds: 250 kbps at 48 kHz) - what
//     Android does;
//   - "over" ("AAC 256" in the menu): 256 kbps in whole frames; the media
//     channel is treated as overMTU bytes instead of the MTU the headphones
//     announce. Galaxy Buds2 Pro announce 679 bytes (250 kbps) but play
//     frames of up to ~960 bytes cleanly (verified by ear). Not universal:
//     other headphones may drop such packets - opt-in;
//   - "frag": 256 kbps, frames larger than one packet are split over two RTP
//     packets (RFC 3016, marker bit on the last fragment). Diagnostics only:
//     Galaxy Buds2 Pro receive every packet (all acknowledged) but cannot
//     decode split frames - the sound stutters badly.
var aacMode = "fit"

// overMTU: our own AVDTP media MTU; 256 kbps CBR frames peak at ~960 bytes.
const overMTU = 1017

func newAAC(sampleRate, mtu int) (Encoder, error) {
	// mtu is the media payload of one packet (already raised in "over"
	// mode), so "fit" and "over" both cap the frame to one packet.
	budget := mtu
	if aacMode == "frag" {
		budget = 0
	}
	e, err := aac.New(sampleRate, 2, 256000, budget)
	if err != nil {
		return nil, err
	}
	return &aacEnc{e: e}, nil
}

type sscEnc struct{ e *ssc.Encoder }

// framePerPacket: SSC packets like the phone (a2dp_vendor_ssc_send_frames),
// one frame per packet, RTP timestamp = packet counter.
func (s *sscEnc) framePerPacket() {}

func (s *sscEnc) FrameLen() int                        { return ssc.FrameLen }
func (s *sscEnc) Encode(pcm []float32) ([]byte, error) { return s.e.Encode(pcm) }
func (s *sscEnc) BitrateKbps() int                     { return s.e.Bitrate / 1000 }
func (s *sscEnc) Close()                               { s.e.Close() }

// SSC bitrate like the phone (SscBitrateByBusyLevel, 24-bit 48 kHz): 192k,
// 128k when the headphones lack the "no bitrate limit" bit (0x08). The phone
// steps down to 128k/88k when the controller reports a busy link; we stay
// at the top. 229/256/328k exist in the encoder but the phone does not use
// them at 48 kHz.
const (
	sscBitrateFull    = 192000
	sscBitrateLimited = 128000
)

// sscRateOK: SSC goes 24-bit 48 kHz (the phone's 16-bit mode is 44.1 kHz
// only, and we capture float).
func sscRateOK(sampleRate int) error {
	if sampleRate != 48000 {
		return fmt.Errorf("SSC: частота вывода %d Гц, нужна 48000 Гц - выберите её в настройках звука", sampleRate)
	}
	return nil
}

// sscForced: bitrate from the settings (bps, 0 = like the phone).
var sscForced int

// budsMTU: the media payload Galaxy Buds announce.
const budsMTU = 667

// sscNeedsOver: a forced bitrate whose frames exceed the Buds' packet goes
// with our own larger media MTU (as "AAC 256").
func sscNeedsOver(kbps int) bool {
	return kbps > 0 && ssc.FrameBytes(48000, kbps*1000) > budsMTU
}

// sscBitrate: the forced bitrate or the phone's choice for this
// configuration byte, lowered if a frame (CBR, 4-byte header included)
// would not fit one packet.
func sscBitrate(sampleRate, mtu int, cfg uint8) (int, error) {
	top := sscBitrateFull
	if cfg != 0 && cfg&0x08 == 0 {
		top = sscBitrateLimited
	}
	if sscForced > 0 {
		top = sscForced
	}
	best := 0
	for _, b := range ssc.BasicBitrates {
		if ssc.FrameBytes(sampleRate, b) <= mtu && b <= top && b > best {
			best = b
		}
	}
	if best == 0 {
		return 0, fmt.Errorf("SSC: канал %d байт меньше самого малого кадра", mtu)
	}
	return best, nil
}

func newSSC(sampleRate, mtu int) (Encoder, error) {
	if err := sscRateOK(sampleRate); err != nil {
		return nil, err
	}
	br, err := sscBitrate(sampleRate, mtu, bt.SSCConfig())
	if err != nil {
		return nil, err
	}
	e, err := ssc.New(sampleRate, br)
	if err != nil {
		return nil, err
	}
	logf("ssc: %d bps (config 0x%02X), frame %d bytes / %d ms, payload %d", br, bt.SSCConfig(),
		ssc.FrameBytes(sampleRate, br), ssc.FrameLen*1000/sampleRate, mtu)
	return &sscEnc{e}, nil
}
