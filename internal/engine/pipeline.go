package engine

import (
	"math"
	"sync"
	"sync/atomic"
	"time"

	"sscv2/internal/bt"
)

// Encoder turns fixed-size blocks of interleaved int16 PCM into codec frames.
type Encoder interface {
	FrameLen() int // PCM frames consumed per Encode call
	Encode(pcm []int16) ([]byte, error)
	BitrateKbps() int
	Close()
}

// pipeline: captured float32 -> stereo downmix -> int16 -> encoder ->
// MTU-sized RTP payloads -> bt.SendMedia. Called on the capture thread.
type pipeline struct {
	mu      sync.Mutex
	enc     Encoder
	maxRaw  int
	ts      uint32
	pcm     []int16 // pending samples (residual between callbacks)
	stereo  []float32
	accum   []byte
	active  atomic.Bool
	// muted: send silence (headphones' volume not settled yet)
	muted   atomic.Bool

	encBytes atomic.Uint64
	frames   atomic.Uint64
	peak     atomic.Uint32 // float32 bits of the last window's peak
	lastLoud atomic.Int64  // unix ms of the last non-silent capture block
}

// set installs a new encoder (nil pauses the pipeline).
func (p *pipeline) set(enc Encoder, mtu int) {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.enc = enc
	// Payload budget: media payload minus 12 bytes of margin, like the
	// verified C++ build.
	p.maxRaw = mtu - 12
	if p.maxRaw < 100 {
		p.maxRaw = 100
	}
	p.ts = 0
	p.pcm = p.pcm[:0]
	p.active.Store(enc != nil)
}

func clamp16(v float32) int16 {
	if v > 1 {
		v = 1
	} else if v < -1 {
		v = -1
	}
	return int16(v * 32767)
}

// onCapture receives `frames` interleaved frames of `ch` channels.
func (p *pipeline) onCapture(s []float32, frames, ch int) {
	p.frames.Add(uint64(frames))
	for _, v := range s[:frames*ch] {
		if v > 0.003 || v < -0.003 { // above ~-50 dB: something is playing
			p.lastLoud.Store(time.Now().UnixMilli())
			break
		}
	}
	if !p.active.Load() {
		return
	}
	p.mu.Lock()
	defer p.mu.Unlock()
	if p.enc == nil {
		return
	}

	if p.muted.Load() {
		clear(s[:frames*ch])
	}

	// Downmix to stereo (ITU-R BS.775, LFE at -6 dB) so centre/surround are
	// mixed in rather than dropped.
	var peak float32
	switch {
	case ch == 2:
		for _, v := range s[:frames*2] {
			p.pcm = append(p.pcm, clamp16(v))
			if a := float32(math.Abs(float64(v))); a > peak {
				peak = a
			}
		}
	case ch == 1:
		for _, v := range s[:frames] {
			x := clamp16(v)
			p.pcm = append(p.pcm, x, x)
		}
	default:
		for f := 0; f < frames; f++ {
			c := s[f*ch : f*ch+ch]
			at := func(i int) float32 {
				if i < ch {
					return c[i]
				}
				return 0
			}
			fc, lfe := at(2), at(3)
			l := c[0] + 0.707107*fc + 0.707107*(at(4)+at(6)) + 0.5*lfe
			r := c[1] + 0.707107*fc + 0.707107*(at(5)+at(7)) + 0.5*lfe
			p.pcm = append(p.pcm, clamp16(l), clamp16(r))
		}
	}
	if peak > math.Float32frombits(p.peak.Load()) {
		p.peak.Store(math.Float32bits(peak))
	}

	block := p.enc.FrameLen() * 2
	off := 0
	p.accum = p.accum[:0]
	firstTS := p.ts
	nframes := 0
	for off+block <= len(p.pcm) {
		out, err := p.enc.Encode(p.pcm[off : off+block])
		if err == nil && len(out) > 0 {
			p.encBytes.Add(uint64(len(out)))
			if len(p.accum)+len(out) > p.maxRaw && nframes > 0 {
				bt.SendMedia(p.accum, firstTS)
				p.accum = p.accum[:0]
				nframes = 0
				firstTS = p.ts
			}
			p.accum = append(p.accum, out...)
			nframes++
		}
		p.ts += uint32(p.enc.FrameLen())
		off += block
	}
	if nframes > 0 {
		bt.SendMedia(p.accum, firstTS)
	}
	// keep the residual for the next callback
	n := copy(p.pcm, p.pcm[off:])
	p.pcm = p.pcm[:n]
}

// loudWithin reports audio above silence during the last d.
func (p *pipeline) loudWithin(d time.Duration) bool {
	return time.Now().UnixMilli()-p.lastLoud.Load() < d.Milliseconds()
}

// takePeak returns and resets the peak level since the last call.
func (p *pipeline) takePeak() float32 {
	return math.Float32frombits(p.peak.Swap(0))
}
