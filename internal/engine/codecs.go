package engine

import (
	"errors"

	"sscv2/internal/codec/aac"
)

type aacEnc struct{ e *aac.Encoder }

func (a *aacEnc) FrameLen() int                     { return a.e.FrameLen }
func (a *aacEnc) Encode(pcm []int16) ([]byte, error) { return a.e.Encode(pcm) }
func (a *aacEnc) BitrateKbps() int                  { return a.e.Bitrate / 1000 }
func (a *aacEnc) Close()                            { a.e.Close() }
func (a *aacEnc) Bandwidth() int                    { return a.e.Bandwidth() }

func newAAC(sampleRate, mtu int) (Encoder, error) {
	e, err := aac.New(sampleRate, 2, 256000, mtu)
	if err != nil {
		return nil, err
	}
	return &aacEnc{e}, nil
}

// ErrSSCNotReady: the Samsung Scalable Codec mode is a placeholder for now.
var ErrSSCNotReady = errors.New("режим SSC пока не реализован (заготовка)")

// newSSC is the hook for the future SSC encoder.
func newSSC(sampleRate, mtu int) (Encoder, error) { return nil, ErrSSCNotReady }
