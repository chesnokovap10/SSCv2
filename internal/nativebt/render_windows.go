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
	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

type renderPCM struct {
	consumedPCM  bool
	onPCM        func()
	trimSource   func(int) int
	lastFill     time.Time
	session      *avdtpSession
	gain         func() float32
	read         func([]byte) (int, error)
	out          io.Writer
	buffer       []byte
	head         int
	queued       int
	shortRun     int
	reserveBytes int
	playing      bool
	primingSince time.Time
	lastSample   [2]float32
	previousPCM  bool
	lastShortLog time.Time
	activity     *audio.Activity
}

const (
	renderReserveStep  = 48000 * 4 * 4 / 1000  // 4 ms of stereo PCM
	renderReserve      = 48000 * 4 * 30 / 1000 // 30 ms of stereo S16LE
	renderPrimeTimeout = 50 * time.Millisecond
	renderFadeFrames   = 96 // 2 ms at 48 kHz
)

func (r *renderPCM) stream(ctx context.Context, path string, stream ipc.NativeStream, ready func(int) error, linkLost func(bool), capabilities func(ipc.CodecCapabilities)) error {
	if err := requireTestSigning(); err != nil {
		return err
	}
	run := runAVDTP
	if r.session != nil {
		run = r.session.run
	}
	return run(ctx, path, r.out, true, stream, func(media io.Writer, kbps int) error {
		link := &renderMedia{Writer: media, sourcePCM: &r.consumedPCM, onPCM: r.onPCM, onExpired: func() {
			r.queued = 0
			r.consumedPCM = false
			r.playing = false
			r.previousPCM = false
			r.primingSince = time.Time{}
			if r.trimSource != nil {
				r.trimSource(0)
			}
		}}
		var onReady func() error
		if ready != nil {
			onReady = func() error { return ready(kbps) }
		}
		var err error
		if stream.Mode == config.ModeAAC {
			var scratch []float32
			err = sendAAC(link, r.out, kbps, 0, "Buds WaveRT", true, func(dst []int16, _ int) error {
				if scratch == nil {
					scratch = make([]float32, len(dst))
				}
				return r.fillBlock(ctx, scratch, dst)
			}, onReady)
		} else {
			err = sendSSCLive(link, stream.Mode, kbps, func(pcm []float32) error { return r.fill(ctx, pcm) }, onReady)
		}
		if linkLost != nil && ctx.Err() == nil && link.lost {
			linkLost(r.activity.PlayingOnLinkLoss())
		}
		return err
	}, capabilities)
}

type renderMedia struct {
	sourcePCM *bool
	onPCM     func()
	onExpired func()
	io.Writer
	sent bool
	lost bool
}

func (m *renderMedia) Write(packet []byte) (int, error) {
	n, err := m.Writer.Write(packet)
	if errors.Is(err, errExpiredMedia) && m.onExpired != nil {
		m.onExpired()
	}
	m.lost = m.sent && (errors.Is(err, windows.ERROR_NETNAME_DELETED) || errors.Is(err, windows.ERROR_DEVICE_NOT_CONNECTED))
	if err == nil && n == len(packet) {
		m.sent = true
		if m.onPCM != nil && m.sourcePCM != nil && *m.sourcePCM {
			m.onPCM()
			m.onPCM = nil
		}
	}
	return n, err
}

func (r *renderPCM) fill(ctx context.Context, pcm []float32) error {
	return r.fillBlock(ctx, pcm, nil)
}

func convertRenderS16(dst []int16, pcm []float32) {
	for i := range dst {
		dst[i] = int16(max(-1, min(1, pcm[i])) * 32767)
	}
}
func (r *renderPCM) fillBlock(ctx context.Context, pcm []float32, raw []int16) error {
	frameBytes := 2 * len(pcm)
	if r.buffer == nil {
		r.buffer = make([]byte, frameBytes+renderReserve)
		r.reserveBytes = renderReserveStep
	}
	if r.trimSource != nil {
		now := time.Now()
		period := time.Second * time.Duration(frameBytes) / (48000 * 4)
		if !r.lastFill.IsZero() && now.Sub(r.lastFill) >= period+period/2 {
			target := frameBytes + r.reserveBytes
			fresh := r.trimSource(target)
			if excess := fresh + r.queued - target; excess > 0 {
				r.head = (r.head + excess) % len(r.buffer)
				r.queued -= excess
				r.previousPCM = false
			}
		}
		r.lastFill = now
	}
	queuedBeforeRead := r.queued
	for r.queued < len(r.buffer) {
		if err := ctx.Err(); err != nil {
			return err
		}
		tail := (r.head + r.queued) % len(r.buffer)
		n := min(len(r.buffer)-r.queued, len(r.buffer)-tail, 4096)
		size, err := r.read(r.buffer[tail : tail+n])
		if err != nil {
			return err
		}
		if size == 0 {
			break
		}
		r.queued += size
	}
	if r.queued < frameBytes {
		r.shortRun++
		if r.playing && r.queued > 0 {
			r.reserveBytes = min(renderReserve, r.reserveBytes+renderReserveStep)
		}
		if r.playing && r.out != nil && time.Since(r.lastShortLog) >= time.Second {
			r.lastShortLog = time.Now()
			fmt.Fprintf(r.out, "WaveRT PCM buffer ran short: %d/%d samples per channel\n", r.queued/4, frameBytes/4)
		}
		if r.queued == 0 || r.shortRun > 1 {
			r.playing = false
		}
	} else {
		r.shortRun = 0
	}
	if r.queued == 0 {
		r.primingSince = time.Time{}
		r.silence(pcm)
		convertRenderS16(raw, pcm)
		return nil
	}
	if !r.playing && r.queued < frameBytes+r.reserveBytes {
		now := time.Now()
		// Keep building the reserve while PCM arrives. If nothing arrived
		// since the previous fill, emit the short sound on this codec tick.
		waitForInput := r.queued > queuedBeforeRead || (r.primingSince.IsZero() && !r.previousPCM)
		if r.primingSince.IsZero() {
			r.primingSince = now
		}
		if waitForInput && now.Sub(r.primingSince) < renderPrimeTimeout {
			r.silence(pcm)
			convertRenderS16(raw, pcm)
			return nil
		}
	}
	// Bound the wait for short sounds and for the tail of a stopped stream.
	r.consumedPCM = true
	size := min(r.queued, frameBytes)
	r.playing = r.playing || size == frameBytes
	r.primingSince = time.Time{}
	gain := float32(1)
	if r.gain != nil {
		gain = r.gain()
	}
	if raw != nil && gain == 1 && r.previousPCM && size == frameBytes {
		offset := r.head
		for i := range raw {
			raw[i] = int16(binary.LittleEndian.Uint16(r.buffer[offset:]))
			offset += 2
			if offset == len(r.buffer) {
				offset = 0
			}
		}
		if r.activity != nil {
			r.activity.ObserveS16(raw)
		}
		r.lastSample = [2]float32{float32(raw[len(raw)-2]) / 32768, float32(raw[len(raw)-1]) / 32768}
		r.head = offset
		r.queued -= size
		return nil
	}
	samples := pcm[:size/2]
	offset := r.head
	for i := range samples {
		samples[i] = float32(int16(binary.LittleEndian.Uint16(r.buffer[offset:]))) / 32768
		offset += 2
		if offset == len(r.buffer) {
			offset = 0
		}
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
	convertRenderS16(raw, pcm)
	r.head = offset
	r.queued -= size
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
