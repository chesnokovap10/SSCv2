package nativebt

import (
	"context"
	"encoding/binary"
	"testing"
	"time"
)

func TestRenderPCMPrimesThenConcealsAnIsolatedShortFrame(t *testing.T) {
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
	var previousFull bool
	checkFrame := func(audible int) {
		t.Helper()
		if err := render.fill(context.Background(), pcm); err != nil {
			t.Fatal(err)
		}
		fade := min(audible, renderFadeFrames)
		for i, sample := range pcm {
			frame := i / 2
			var want float32
			if frame < audible {
				want = 0.5
				if !previousFull && frame < fade {
					want *= float32(frame) / float32(fade)
				}
				if audible < frames && frame >= audible-fade {
					want *= float32(audible-frame-1) / float32(fade)
				}
			} else if audible == 0 && previousFull && frame < renderFadeFrames {
				want = 0.5 * float32(renderFadeFrames-frame-1) / renderFadeFrames
			}
			if sample != want {
				t.Fatalf("sample %d = %v, want %v", i, sample, want)
			}
		}
		previousFull = audible == frames
	}

	appendFrames(frames / 2)
	checkFrame(0)
	appendFrames(frames*4 - frames/2)
	for range 4 {
		checkFrame(frames)
	}
	appendFrames(frames / 2)
	checkFrame(frames / 2)
	appendFrames(frames * 4)
	for range 4 {
		checkFrame(frames)
	}
	appendFrames(frames / 2)
	checkFrame(frames / 2)
	checkFrame(0)
}

func TestShortNotificationEmittedOnSecondCodecTick(t *testing.T) {
	for _, codec := range []struct {
		name   string
		frames int
	}{{"AAC", 1024}, {"SSC", 864}, {"SSC UHQ", 432}} {
		t.Run(codec.name, func(t *testing.T) {
			input := make([]byte, 480*4) // 10 ms stereo at 48 kHz
			for i := 0; i < len(input); i += 2 {
				binary.LittleEndian.PutUint16(input[i:], 16384)
			}
			r := renderPCM{read: func(dst []byte) (int, error) {
				n := copy(dst, input)
				input = input[n:]
				return n, nil
			}}
			pcm := make([]float32, 2*codec.frames)
			for tick := 1; tick <= 2; tick++ {
				if err := r.fill(context.Background(), pcm); err != nil {
					t.Fatal(err)
				}
				audible := pcm[2*renderFadeFrames] > 0
				if audible != (tick == 2) {
					t.Fatalf("tick %d: audible=%t", tick, audible)
				}
			}
			if want := max(480-codec.frames, 0) * 4; r.queued != want {
				t.Fatalf("queued %d bytes, want %d", r.queued, want)
			}
			if r.queued > 0 {
				if err := r.fill(context.Background(), pcm); err != nil {
					t.Fatal(err)
				}
				if pcm[0] == 0 || r.queued != 0 {
					t.Fatal("lost or delayed the notification tail")
				}
			}
		})
	}
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

func TestContinuousPCMStartsWithSmallReserve(t *testing.T) {
	input := make([]byte, 480*4+renderReserveStep)
	r := renderPCM{read: func(b []byte) (int, error) { n := copy(b, input); input = input[n:]; return n, nil }}
	if err := r.fill(context.Background(), make([]float32, 960)); err != nil || !r.playing || r.queued != renderReserveStep {
		t.Fatal(r.queued, err)
	}
}

func TestWaveRTFrameAcrossRingBoundary(t *testing.T) {
	const frames = 480
	r := renderPCM{playing: true, previousPCM: true, buffer: make([]byte, frames*4+renderReserve), queued: frames * 4, read: func([]byte) (int, error) { return 0, nil }}
	r.head = len(r.buffer) - 4
	for i := range frames * 2 {
		binary.LittleEndian.PutUint16(r.buffer[(r.head+2*i)%len(r.buffer):], uint16(i))
	}
	pcm := make([]float32, frames*2)
	if err := r.fill(context.Background(), pcm); err != nil {
		t.Fatal(err)
	}
	for i, v := range pcm {
		if v != float32(i)/32768 {
			t.Fatal(i, v)
		}
	}
}

func TestPCMSourceDropsOldestFramesWhenSenderStalls(t *testing.T) {
	var s pcmSource
	for i := byte(1); i <= 3; i++ {
		b := make([]byte, 4096)
		for j := range b {
			b[j] = i
		}
		s.store(b, time.Now())
	}
	for _, want := range []byte{2, 3} {
		b := make([]byte, 4096)
		n, err := s.read(b)
		if err != nil || n != 4096 || b[0] != want || b[n-1] != want {
			t.Fatal(n, err, b[0])
		}
	}
}
