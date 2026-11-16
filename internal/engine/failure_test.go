package engine

import (
	"errors"
	"testing"
)

type failingEncoder struct{ calls int }

func (e *failingEncoder) FrameLen() int { return 4 }
func (e *failingEncoder) Encode([]float32) ([]byte, error) {
	e.calls++
	return nil, errors.New("encoder failure")
}
func (e *failingEncoder) BitrateKbps() int { return 192 }
func (e *failingEncoder) Close()           {}

func TestEncodingFailureStopsBothPacketModes(t *testing.T) {
	for _, perPacket := range []bool{false, true} {
		var p pipeline
		enc := &failingEncoder{}
		p.set(enc, 667, false)
		p.perPacket = perPacket
		p.onCapture(make([]float32, 80), 40, 2, 48000, false, nil)
		p.onCapture(make([]float32, 80), 40, 2, 48000, false, nil)
		if enc.calls != 1 || p.active.Load() {
			t.Fatalf("perPacket=%v calls=%d active=%v", perPacket, enc.calls, p.active.Load())
		}
		select {
		case err := <-p.errors:
			if err == nil {
				t.Fatal("nil failure")
			}
		default:
			t.Fatal("no session error")
		}
	}
}

func TestPeakIncludesMonoAndSurroundCapture(t *testing.T) {
	for _, ch := range []int{1, 4, 6} {
		var p pipeline
		p.set(captureGapEncoder{}, 667, false)
		samples := make([]float32, ch)
		samples[0] = 0.5
		p.onCapture(samples, 1, ch, 48000, false, stereoMix(ch, 0))
		if peak := p.takePeak(); peak != 0.5 {
			t.Fatalf("channels=%d peak=%f", ch, peak)
		}
	}
}
