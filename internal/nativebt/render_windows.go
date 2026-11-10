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
	gain   func() float32
	read   func([]byte) (int, error)
	buffer [4096]byte
}

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
	return runRenderPCM(ctx, args, out, mode, device.Read, nil)
}

func runRenderPCM(ctx context.Context, args []string, out io.Writer, mode config.Mode, read func([]byte) (int, error), gain func() float32) error {
	render := &renderPCM{read: read, gain: gain}
	if _, err := render.read(render.buffer[:4]); err != nil {
		return err
	}
	return runWithRender(ctx, args, out, true, mode, render)
}

func (r *renderPCM) fill(ctx context.Context, pcm []float32) error {
	gain := float32(1)
	if r.gain != nil {
		gain = r.gain()
	}
	deadline := time.NewTimer(time.Second * time.Duration(len(pcm)/2) / 48000)
	defer deadline.Stop()
	for len(pcm) != 0 {
		if err := ctx.Err(); err != nil {
			return err
		}
		size, err := r.read(r.buffer[:min(len(r.buffer), 2*len(pcm))])
		if err != nil {
			return err
		}
		if size != 0 {
			for i := range size / 2 {
				pcm[i] = float32(int16(binary.LittleEndian.Uint16(r.buffer[2*i:]))) * (gain / 32768)
			}
			pcm = pcm[size/2:]
			continue
		}
		select {
		case <-ctx.Done():
			return ctx.Err()
		case <-deadline.C:
			clear(pcm)
			return nil
		case <-time.After(time.Millisecond):
		}
	}
	return nil
}
