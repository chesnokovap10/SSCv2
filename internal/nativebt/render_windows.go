package nativebt

import (
	"context"
	"encoding/binary"
	"fmt"
	"io"
	"time"

	"sscv2/internal/config"
	"sscv2/internal/driver"
)

type renderPCM struct {
	kbps         int
	gain         func() float32
	read         func([]byte) (int, error)
	buffer       []byte
	queued       int
	playing      bool
	primingSince time.Time
}

const (
	renderReserve      = 48000 * 4 * 30 / 1000 // 30 ms of stereo S16LE
	renderPrimeTimeout = 50 * time.Millisecond
)

// RunRenderDiagnostic streams PCM from the Buds WaveRT filter over native AVDTP.
func RunRenderDiagnostic(ctx context.Context, address, wavePath string, out io.Writer, mode config.Mode) error {
	if mode != config.ModeAAC && mode != config.ModeSSC {
		return fmt.Errorf("WaveRT diagnostic supports AAC and SSC")
	}
	path, err := LocalProfilePath(address)
	if err != nil {
		return err
	}
	return runRender(ctx, []string{path}, wavePath, out, mode)
}

func runRender(ctx context.Context, args []string, wavePath string, out io.Writer, mode config.Mode) error {
	device, err := driver.OpenBudsPCM(wavePath)
	if err != nil {
		return err
	}
	defer device.Close()
	return runRenderPCM(ctx, args, out, mode, DefaultBitrate(mode), device.Read, nil)
}

func runRenderPCM(ctx context.Context, args []string, out io.Writer, mode config.Mode, kbps int, read func([]byte) (int, error), gain func() float32) error {
	render := &renderPCM{kbps: kbps, read: read, gain: gain}
	return runWithRender(ctx, args, out, true, mode, render)
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
		r.playing = false
	}
	if r.queued == 0 {
		r.primingSince = time.Time{}
		clear(pcm)
		return nil
	}
	if !r.playing && r.queued < len(r.buffer) {
		now := time.Now()
		if r.primingSince.IsZero() {
			r.primingSince = now
		}
		if now.Sub(r.primingSince) < renderPrimeTimeout {
			clear(pcm)
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
	for i := range size / 2 {
		pcm[i] = float32(int16(binary.LittleEndian.Uint16(r.buffer[2*i:]))) * (gain / 32768)
	}
	clear(pcm[size/2:])
	r.queued = copy(r.buffer, r.buffer[size:r.queued])
	return nil
}
