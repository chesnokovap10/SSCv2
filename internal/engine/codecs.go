package engine

import (
	"fmt"
	"os"
	"sscv2/internal/i18n"
	"strconv"

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
//   - "over" (Settings > Max MTU): 256 kbps in whole frames; the media
//     channel is treated as overMTU bytes instead of the MTU the headphones
//     announce. Galaxy Buds2 Pro announce 679 bytes (250 kbps) but play
//     frames of up to ~960 bytes cleanly (verified by ear). Not universal:
//     other headphones may drop such packets - opt-in;
//   - "frag": 256 kbps, frames larger than one packet are split over two RTP
//     packets (RFC 3016, marker bit on the last fragment). Diagnostics only:
//     Galaxy Buds2 Pro receive every packet (all acknowledged) but cannot
//     decode split frames - the sound stutters badly.
var aacMode = "fit"

// aacForced: AAC bitrate from the settings (bps, 0 = as high as a packet allows).
var aacForced int

// overMTU: our own AVDTP media MTU; 256 kbps CBR frames peak at ~960 bytes.
const overMTU = 1017

func newAAC(sampleRate, mtu int) (Encoder, error) {
	// mtu is the media payload of one packet (already raised in "over"
	// mode), so "fit" and "over" both cap the frame to one packet.
	budget := mtu
	if aacMode == "frag" {
		budget = 0
	}
	br := 256000
	if aacForced > 0 && aacForced < br {
		br = aacForced
	}
	e, err := aac.New(sampleRate, 2, br, budget)
	if err != nil {
		return nil, err
	}
	return &aacEnc{e: e}, nil
}

// sscEnc: SSC at the capture rate (48 kHz), or UHQ at 96 kHz with the
// capture upsampled 2x (up != nil): then one Encode takes 432 capture frames.
type sscEnc struct {
	e  *ssc.Encoder
	up *upsampler2x
}

// framePerPacket: SSC packets like the phone (a2dp_vendor_ssc_send_frames),
// one frame per packet, RTP timestamp = packet counter.
func (s *sscEnc) framePerPacket() {}

// streamInfo: what the status shows (codec label, encoder rate).
func (s *sscEnc) streamInfo() (string, int) {
	if s.up != nil {
		return "SSC UHQ", s.e.SampleRate
	}
	return "SSC", s.e.SampleRate
}

func (s *sscEnc) FrameLen() int {
	if s.up != nil {
		return ssc.FrameLen / 2
	}
	return ssc.FrameLen
}

func (s *sscEnc) Encode(pcm []float32) ([]byte, error) {
	if s.up != nil {
		return s.e.Encode(s.up.process(pcm))
	}
	return s.e.Encode(pcm)
}
func (s *sscEnc) BitrateKbps() int { return s.e.Bitrate / 1000 }
func (s *sscEnc) Close()           { s.e.Close() }

// SSC "Auto" (24-bit 48 kHz): the highest rate whose frame fits one packet
// - 256k in the Buds' 667-byte payload, 328k with Max MTU (1005). Headphones
// without the "no bitrate limit" bit (0x08) get 128k, as from the phone.
// (The phone itself sends 192k at most: SscBitrateByBusyLevel.)
const (
	sscBitrateFull    = 328000
	sscBitrateLimited = 128000
)

// sscRateOK: SSC goes 24-bit 48 kHz (the phone's 16-bit mode is 44.1 kHz
// only, and we capture float).
func sscRateOK(sampleRate int) error {
	if sampleRate != 48000 {
		return fmt.Errorf(i18n.T("SSC: частота вывода %d Гц, нужна 48000 Гц - выберите её в настройках звука", "SSC: the output runs at %d Hz, 48000 Hz is needed - choose it in the Sound settings"), sampleRate)
	}
	return nil
}

// sscForced: bitrate from the settings (bps, 0 = like the phone).
var sscForced int

// budsMTU: the media payload Galaxy Buds announce.
const budsMTU = 667

// sscUHQMode: the SSC UHQ codec was chosen (96 kHz).
var sscUHQMode bool

// sscUHQ: stream SSC UHQ (96 kHz): chosen, or a UHQ bitrate forced.
func sscUHQ() bool { return sscUHQMode || sscForced > 0 && ssc.Valid(96000, sscForced) }

// sscEncodeRate: the SSC encoder's rate for this capture rate.
func sscEncodeRate(captureRate int) int {
	if sscUHQ() {
		return 96000
	}
	return captureRate
}

// sscMaxMTU: Settings > Max MTU is on (1005-byte payload).
var sscMaxMTU bool

// maxPayload: the media payload with Max MTU on / off (Galaxy Buds).
func maxPayload(maxMTU bool) int {
	if maxMTU {
		return overMTU - 12
	}
	return budsMTU
}

// BitrateFits reports whether kbps can be streamed for the codec ("aac",
// "ssc", "ssc_uhq") with Max MTU on or off: frames must fit one packet.
func BitrateFits(codec string, kbps int, maxMTU bool) bool {
	if kbps <= 0 {
		return true
	}
	switch codec {
	case "aac":
		// whole frames in one packet: payload x 8 bits x 48000 / 1024 samples
		return kbps*1000 <= maxPayload(maxMTU)*8*48000/1024
	case "ssc_uhq":
		return ssc.FrameBytes(96000, kbps*1000) <= maxPayload(maxMTU)
	}
	return ssc.FrameBytes(48000, kbps*1000) <= maxPayload(maxMTU)
}

// sscNeedsOver: a bitrate whose frames exceed the Buds' packet needs Max MTU.
func sscNeedsOver(kbps int) bool {
	if kbps <= 0 {
		return false
	}
	rate := 48000
	if ssc.Valid(96000, kbps*1000) {
		rate = 96000
	}
	return ssc.FrameBytes(rate, kbps*1000) > budsMTU
}

// sscBitrate: the forced bitrate or the phone's choice for this
// configuration byte, lowered if a frame (CBR, 4-byte header included)
// would not fit one packet.
func sscBitrate(sampleRate, mtu int, cfg uint8) (int, error) {
	top := sscBitrateFull
	if cfg != 0 && cfg&0x08 == 0 {
		top = sscBitrateLimited
	}
	list := ssc.BasicBitrates
	if sampleRate == 96000 {
		list, top = ssc.UHQBitrates, ssc.UHQBitrates[len(ssc.UHQBitrates)-1]
	}
	if sscForced > 0 {
		top = sscForced
	}
	best := 0
	for _, b := range list {
		if ssc.FrameBytes(sampleRate, b) <= mtu && b <= top && b > best {
			best = b
		}
	}
	if best == 0 {
		return 0, fmt.Errorf(i18n.T("SSC: канал %d байт меньше самого малого кадра", "SSC: a %d-byte channel is smaller than the smallest frame"), mtu)
	}
	return best, nil
}

func newSSC(sampleRate, mtu int) (Encoder, error) {
	if err := sscRateOK(sampleRate); err != nil {
		return nil, err
	}
	rate := sscEncodeRate(sampleRate)
	br, err := sscBitrate(rate, mtu, bt.SSCConfig())
	if err != nil {
		return nil, err
	}
	e, err := ssc.New(rate, br)
	if err != nil {
		return nil, err
	}
	s := &sscEnc{e: e}
	if rate != sampleRate {
		s.up = newUpsampler2x()
	}
	// experiments: SSCV2_SSC_SHIFT=8 feeds full scale 2^31 instead of 2^23
	if v, err := strconv.Atoi(os.Getenv("SSCV2_SSC_SHIFT")); err == nil && v > 0 && v <= 8 {
		e.Shift = uint(v)
		logf("ssc: input shifted by %d bits (full scale 2^%d)", v, 23+v)
	}
	logf("ssc: %d Hz %d bps (config 0x%02X), frame %d bytes / %.1f ms, payload %d", rate, br, bt.SSCConfig(),
		ssc.FrameBytes(rate, br), float64(ssc.FrameLen)*1000/float64(rate), mtu)
	return s, nil
}
