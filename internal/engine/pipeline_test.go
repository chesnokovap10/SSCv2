package engine

import (
	"testing"
	"time"
)

type captureGapEncoder struct{ Encoder }

func (captureGapEncoder) FrameLen() int { return 1024 }

func TestCaptureDiscontinuityDoesNotJoinOldAndNewAudio(t *testing.T) {
	var p pipeline
	p.set(captureGapEncoder{}, 600, false)
	p.onCapture([]float32{-1, -1}, 1, 2, 48000, false, nil, time.Now(), p.generation.Load())
	p.onCapture([]float32{1, 1, 1, 1}, 2, 2, 48000, true, nil, time.Now(), p.generation.Load())
	if len(p.pcm) != 4 || p.pcm[0] != 0 || p.pcm[1] != 0 || p.pcm[2] != 0.5 || p.pcm[3] != 0.5 {
		t.Fatalf("PCM after the gap = %v, want [0 0 0.5 0.5]", p.pcm)
	}
}

func TestQuadRearRightStaysOnRight(t *testing.T) {
	var p pipeline
	p.set(captureGapEncoder{}, 600, false)
	p.onCapture([]float32{0, 0, 0, 1}, 1, 4, 48000, false, stereoMix(4, 0x33), time.Now(), p.generation.Load())
	if p.pcm[0] != 0 || p.pcm[1] != 0.707107 {
		t.Fatalf("quad rear right produced %v", p.pcm)
	}
}

func TestCaptureQueueDropsOldBlocksWithoutBlockingCapture(t *testing.T) {
	entered := make(chan struct{})
	resume := make(chan struct{})
	var seen []int
	q := newCaptureQueue(func(b *captureBlock) {
		if b.sequence == 1 {
			close(entered)
			<-resume
		}
		if b.sequence == 3 && !b.gap {
			t.Error("missing gap")
		}
		seen = append(seen, int(b.sequence))
	})
	q.push(nil, 0, false, time.Now(), 0)
	<-entered
	for range 5 {
		q.push(nil, 0, false, time.Now(), 0)
	}
	close(resume)
	q.close()
	if len(seen) != 5 || seen[1] != 3 || seen[4] != 6 {
		t.Fatal(seen)
	}
}
