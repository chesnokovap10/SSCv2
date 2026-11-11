package nativebt

import (
	"context"
	"encoding/binary"
	"testing"
	"time"
)

func TestRenderPCMRebuffersWithoutConsumingPartialFrame(t *testing.T) {
	const frames = 480 // 10 ms
	var input []byte
	appendFrames := func(n int) {
		for range n * 2 {
			input = binary.LittleEndian.AppendUint16(input, 16384)
		}
	}
	render := renderPCM{read: func(dst []byte) (int, error) {
		n := copy(dst, input)
		input = input[n:]
		return n, nil
	}}
	pcm := make([]float32, frames*2)
	checkFrame := func(audible int) {
		t.Helper()
		if err := render.fill(context.Background(), pcm); err != nil {
			t.Fatal(err)
		}
		for i, sample := range pcm {
			var want float32
			if i < audible*2 {
				want = 0.5
			}
			if sample != want {
				t.Fatalf("sample %d = %v, want %v", i, sample, want)
			}
		}
	}

	appendFrames(frames / 2)
	checkFrame(0)
	appendFrames(frames*4 - frames/2)
	for range 4 {
		checkFrame(frames)
	}
	appendFrames(frames / 2)
	checkFrame(0)
	appendFrames(frames*4 - frames/2)
	for range 4 {
		checkFrame(frames)
	}
	appendFrames(frames / 2)
	checkFrame(0)
	render.primingSince = time.Now().Add(-renderPrimeTimeout)
	checkFrame(frames / 2)
	checkFrame(0)
}

func TestPacketPacerRebasesAfterStall(t *testing.T) {
	const period = 10 * time.Millisecond
	start := time.Now()
	pacer := packetPacer{next: start.Add(-5 * period)}
	pacer.wait(period)
	if pacer.next.Before(start.Add(period)) {
		t.Fatal("next packet still scheduled on the clock from before the stall")
	}
}
