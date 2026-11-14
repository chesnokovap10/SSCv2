package engine

import "testing"

type captureGapEncoder struct{ Encoder }

func (captureGapEncoder) FrameLen() int { return 1024 }

func TestCaptureDiscontinuityDoesNotJoinOldAndNewAudio(t *testing.T) {
	var p pipeline
	p.set(captureGapEncoder{}, 600, false)
	p.onCapture([]float32{-1, -1}, 1, 2, 48000, false, nil)
	p.onCapture([]float32{1, 1, 1, 1}, 2, 2, 48000, true, nil)
	if len(p.pcm) != 4 || p.pcm[0] != 0 || p.pcm[1] != 0 || p.pcm[2] != 0.5 || p.pcm[3] != 0.5 {
		t.Fatalf("PCM after the gap = %v, want [0 0 0.5 0.5]", p.pcm)
	}
}

func TestQuadRearRightStaysOnRight(t *testing.T) {
	var p pipeline
	p.set(captureGapEncoder{}, 600, false)
	p.onCapture([]float32{0, 0, 0, 1}, 1, 4, 48000, false, stereoMix(4, 0x33))
	if p.pcm[0] != 0 || p.pcm[1] != 0.707107 {
		t.Fatalf("quad rear right produced %v", p.pcm)
	}
}
