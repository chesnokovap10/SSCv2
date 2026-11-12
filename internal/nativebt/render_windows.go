package nativebt

import (
	"context"
	"encoding/binary"
	"errors"
	"fmt"
	"io"
	"time"

	"golang.org/x/sys/windows"

	"sscv2/internal/audio"
	"sscv2/internal/ipc"
)

type renderPCM struct {
	gain         func() float32
	read         func([]byte) (int, error)
	out          io.Writer
	buffer       []byte
	queued       int
	playing      bool
	primingSince time.Time
	lastSample   [2]float32
	previousPCM  bool
	lastShortLog time.Time
	activity     *audio.Activity
}

const (
	renderReserve      = 48000 * 4 * 30 / 1000 // 30 ms of stereo S16LE
	renderPrimeTimeout = 50 * time.Millisecond
	renderFadeFrames   = 96 // 2 ms at 48 kHz
)

func (r *renderPCM) stream(ctx context.Context, path string, stream ipc.NativeStream, ready func() error, linkLost, capabilities func(bool)) error {
	if err := requireTestSigning(); err != nil {
		return err
	}
	return runAVDTP(ctx, path, r.out, true, stream, func(media io.Writer) error {
		link := &renderMedia{Writer: media}
		err := sendPCM(link, r.out, stream.Mode, stream.BitrateKbps, 0, "Buds WaveRT", true, func(pcm []float32) error {
			return r.fill(ctx, pcm)
		}, ready)
		if linkLost != nil && ctx.Err() == nil && link.lost {
			linkLost(r.activity.PlayingOnLinkLoss())
		}
		return err
	}, capabilities)
}

type renderMedia struct {
	io.Writer
	sent bool
	lost bool
}

func (m *renderMedia) Write(packet []byte) (int, error) {
	n, err := m.Writer.Write(packet)
	m.lost = m.sent && (errors.Is(err, windows.ERROR_NETNAME_DELETED) || errors.Is(err, windows.ERROR_DEVICE_NOT_CONNECTED))
	m.sent = m.sent || err == nil && n == len(packet)
	return n, err
}

func (r *renderPCM) fill(ctx context.Context, pcm []float32) error {
	frameBytes := 2 * len(pcm)
	if r.buffer == nil {
		r.buffer = make([]byte, frameBytes+renderReserve)
	}
	for r.queued < len(r.buffer) {
		if err := ctx.Err(); err != nil {
			return err
		}
		end := min(len(r.buffer), r.queued+4096)
		size, err := r.read(r.buffer[r.queued:end])
		if err != nil {
			return err
		}
		if size == 0 {
			break
		}
		r.queued += size
	}
	if r.queued < frameBytes {
		if r.playing && r.out != nil && time.Since(r.lastShortLog) >= time.Second {
			r.lastShortLog = time.Now()
			fmt.Fprintf(r.out, "WaveRT PCM buffer ran short: %d/%d samples per channel\n", r.queued/4, frameBytes/4)
		}
		r.playing = false
	}
	if r.queued == 0 {
		r.primingSince = time.Time{}
		r.silence(pcm)
		return nil
	}
	if !r.playing && r.queued < len(r.buffer) {
		now := time.Now()
		if r.primingSince.IsZero() {
			r.primingSince = now
		}
		if now.Sub(r.primingSince) < renderPrimeTimeout {
			r.silence(pcm)
			return nil
		}
	}
	// Bound the wait for short sounds and for the tail of a stopped stream.
	size := min(r.queued, frameBytes)
	r.playing = size == frameBytes
	if r.playing {
		r.primingSince = time.Time{}
	}
	gain := float32(1)
	if r.gain != nil {
		gain = r.gain()
	}
	samples := pcm[:size/2]
	for i := range samples {
		samples[i] = float32(int16(binary.LittleEndian.Uint16(r.buffer[2*i:]))) / 32768
	}
	if r.activity != nil {
		r.activity.Observe(samples)
	}
	if gain != 1 {
		for i := range samples {
			samples[i] *= gain
		}
	}
	frames := len(samples) / 2
	fade := min(frames, renderFadeFrames)
	if !r.previousPCM {
		for frame := range fade {
			level := float32(frame) / float32(fade)
			samples[2*frame] *= level
			samples[2*frame+1] *= level
		}
	}
	if size < frameBytes {
		// End an incomplete frame at zero before padding its tail.
		for frame := range fade {
			level := float32(frame) / float32(fade)
			samples[len(samples)-2*frame-2] *= level
			samples[len(samples)-2*frame-1] *= level
		}
	}
	r.previousPCM = size == frameBytes
	copy(r.lastSample[:], samples[len(samples)-2:])
	clear(pcm[size/2:])
	r.queued = copy(r.buffer, r.buffer[size:r.queued])
	return nil
}

func (r *renderPCM) silence(pcm []float32) {
	clear(pcm)
	if !r.previousPCM {
		return
	}
	fade := min(len(pcm)/2, renderFadeFrames)
	for frame := range fade {
		level := float32(fade-frame-1) / float32(fade)
		pcm[2*frame] = r.lastSample[0] * level
		pcm[2*frame+1] = r.lastSample[1] * level
	}
	r.previousPCM = false
}
