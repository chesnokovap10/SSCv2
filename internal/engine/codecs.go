package engine

import (
	"errors"

	"sscv2/internal/codec/aac"
)

type aacEnc struct{ e *aac.Encoder }

func (a *aacEnc) FrameLen() int                      { return a.e.FrameLen }
func (a *aacEnc) Encode(pcm []int16) ([]byte, error) { return a.e.Encode(pcm) }
func (a *aacEnc) BitrateKbps() int                   { return a.e.Bitrate / 1000 }
func (a *aacEnc) Close()                             { a.e.Close() }
func (a *aacEnc) Bandwidth() int                     { return a.e.Bandwidth() }

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
	return &aacEnc{e}, nil
}

// ErrSSCNotReady: the Samsung Scalable Codec mode is a placeholder for now.
var ErrSSCNotReady = errors.New("режим SSC пока не реализован (заготовка)")

// newSSC is the hook for the future SSC encoder.
func newSSC(sampleRate, mtu int) (Encoder, error) { return nil, ErrSSCNotReady }
