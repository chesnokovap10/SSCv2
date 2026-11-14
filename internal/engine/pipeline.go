package engine

import (
	"math"
	"math/bits"
	"sync"
	"sync/atomic"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/bt"
)

// Encoder turns fixed-size blocks of interleaved stereo float PCM (-1..1)
// into codec frames; each codec converts to its own sample format (AAC
// int16, SSC 24 bit).
type Encoder interface {
	FrameLen() int // PCM frames consumed per Encode call
	Encode(pcm []float32) ([]byte, error)
	BitrateKbps() int
	Close()
}

// pipeline: captured float32 -> stereo downmix (clipped to -1..1) -> encoder ->
// MTU-sized RTP payloads -> bt.SendMedia. Called on the capture thread.
type pipeline struct {
	mu              sync.Mutex
	enc             Encoder
	maxRaw          int
	ts              uint32
	pcm             []float32 // pending stereo samples (residual between callbacks)
	stereo          []float32
	accum           []byte
	active          atomic.Bool
	volumeStartedAt atomic.Int64 // Unix milliseconds at A2DP stream startup
	// volume holds the PCM level in bits 0..6 and mute in bit 7.
	volume atomic.Uint32
	// frag: split frames larger than one packet (RFC 3016)
	frag bool
	// perPacket: one frame per packet and the RTP timestamp counts packets,
	// not samples (SSC, as the phone sends it)
	perPacket bool

	maxFrame atomic.Int32 // largest encoded frame in the stats window
	split    atomic.Int32 // frames larger than one packet in the window

	encBytes atomic.Uint64
	frames   atomic.Uint64
	peak     atomic.Uint32 // float32 bits of the last window's peak
	activity audio.Activity
}

// set installs a new encoder (nil pauses the pipeline).
func (p *pipeline) set(enc Encoder, mtu int, frag bool) {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.enc = enc
	p.frag = frag
	// Payload budget: the media payload BTstack reports (L2CAP MTU minus
	// the RTP header).
	p.maxRaw = mtu
	if p.maxRaw < 100 {
		p.maxRaw = 100
	}
	p.ts = 0
	p.pcm = p.pcm[:0]
	_, p.perPacket = enc.(interface{ framePerPacket() })
	p.active.Store(enc != nil)
}

func clip(v float32) float32 {
	if v > 1 {
		return 1
	} else if v < -1 {
		return -1
	}
	return v
}

func clamp16(v float32) int16 { return int16(clip(v) * 32767) }

// onCapture receives `frames` interleaved frames of `ch` channels.
func (p *pipeline) onCapture(s []float32, frames, ch, rate int, discontinuity bool, mix [][2]float32) {
	p.frames.Add(uint64(frames))
	p.activity.Observe(s[:frames*ch])
	if !p.active.Load() {
		return
	}
	p.mu.Lock()
	defer p.mu.Unlock()
	if p.enc == nil {
		return
	}
	if discontinuity {
		// The residual belongs to the stream before the capture gap.
		p.pcm = p.pcm[:0]
	}

	// Downmix to stereo (ITU-R BS.775, LFE at -6 dB) so centre/surround are
	// mixed in rather than dropped.
	var peak float32
	switch {
	case ch == 2 && mix == nil:
		for _, v := range s[:frames*2] {
			p.pcm = append(p.pcm, clip(v))
			if a := float32(math.Abs(float64(v))); a > peak {
				peak = a
			}
		}
	case ch == 1 && mix == nil:
		for _, v := range s[:frames] {
			x := clip(v)
			p.pcm = append(p.pcm, x, x)
		}
	default:
		for f := 0; f < frames; f++ {
			c := s[f*ch : f*ch+ch]
			var l, r float32
			for i, gain := range mix {
				l += c[i] * gain[0]
				r += c[i] * gain[1]
			}
			p.pcm = append(p.pcm, clip(l), clip(r))
		}
	}
	if discontinuity {
		fade := min(frames, rate*2/1000)
		for frame := range fade {
			level := float32(frame) / float32(fade)
			p.pcm[2*frame] *= level
			p.pcm[2*frame+1] *= level
		}
	}
	if peak > math.Float32frombits(p.peak.Load()) {
		p.peak.Store(math.Float32bits(peak))
	}

	block := p.enc.FrameLen() * 2
	off := 0
	if p.perPacket {
		p.encodePerPacket(block, &off)
		n := copy(p.pcm, p.pcm[off:])
		p.pcm = p.pcm[:n]
		return
	}
	p.accum = p.accum[:0]
	firstTS := p.ts
	nframes := 0
	for off+block <= len(p.pcm) {
		out, err := p.encode(p.pcm[off : off+block])
		if err == nil && len(out) > 0 {
			p.encBytes.Add(uint64(len(out)))
			if int32(len(out)) > p.maxFrame.Load() {
				p.maxFrame.Store(int32(len(out)))
			}
			if len(out) > p.maxRaw {
				p.split.Add(1)
				if nframes > 0 {
					bt.SendMedia(p.accum, firstTS)
					p.accum = p.accum[:0]
					nframes = 0
				}
				if p.frag {
					// RFC 3016: same timestamp, marker on the last fragment.
					for o := 0; o < len(out); o += p.maxRaw {
						end := min(o+p.maxRaw, len(out))
						bt.SendMediaMarker(out[o:end], p.ts, end == len(out))
					}
				} else {
					bt.SendMedia(out, p.ts) // too big: counted as a send failure
				}
				p.ts += uint32(p.enc.FrameLen())
				off += block
				firstTS = p.ts
				continue
			}
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

// stereoMix maps the Windows speaker order to left and right gains.
func stereoMix(channels int, mask uint32) [][2]float32 {
	if bits.OnesCount32(mask) != channels {
		switch channels {
		case 1, 2:
			return nil
		case 4:
			mask = 0x33 // Quad
		case 5:
			mask = 0x37 // FL, FR, FC, BL, BR
		default:
			order := [...]uint32{1, 2, 4, 8, 16, 32, 512, 1024}
			mask = 0
			for _, speaker := range order[:min(channels, len(order))] {
				mask |= speaker
			}
		}
	}
	if channels == 2 && mask == 3 || channels == 1 && mask == 4 {
		return nil
	}
	const surround = float32(0.707107)
	mix := make([][2]float32, channels)
	for i := 0; mask != 0; i++ {
		position := bits.TrailingZeros32(mask)
		mask &= mask - 1
		switch position {
		case 0:
			mix[i][0] = 1
		case 1:
			mix[i][1] = 1
		case 2, 8, 11, 13, 16:
			mix[i] = [2]float32{surround, surround}
		case 3:
			mix[i] = [2]float32{0.5, 0.5}
		case 4, 6, 9, 12, 15:
			mix[i][0] = surround
		case 5, 7, 10, 14, 17:
			mix[i][1] = surround
		}
	}
	return mix
}

func (p *pipeline) setVolume(level uint8, muted bool) {
	state := uint32(min(level, 127))
	if muted {
		state |= 128
	}
	p.volume.Store(state)
}

func (p *pipeline) pcmGain(hardware bool, now int64) float32 {
	elapsed := now - p.volumeStartedAt.Load()
	if elapsed < 250 {
		return 0
	}
	if hardware {
		return 1
	}
	level := p.volume.Load()
	if elapsed < 4000 || level >= 128 {
		return 0
	}
	gain := float32(level) / 127
	return gain * gain
}

func (p *pipeline) encode(pcm []float32) ([]byte, error) {
	switch gain := p.pcmGain(bt.HardwareVolumeActive(), time.Now().UnixMilli()); gain {
	case 0:
		clear(pcm)
	case 1:
	default:
		for i := range pcm {
			pcm[i] *= gain
		}
	}
	return p.enc.Encode(pcm)
}

// encodePerPacket: one frame per packet, the RTP timestamp counts packets.
func (p *pipeline) encodePerPacket(block int, off *int) {
	for *off+block <= len(p.pcm) {
		out, err := p.encode(p.pcm[*off : *off+block])
		*off += block
		if err != nil || len(out) == 0 {
			continue
		}
		p.encBytes.Add(uint64(len(out)))
		if int32(len(out)) > p.maxFrame.Load() {
			p.maxFrame.Store(int32(len(out)))
		}
		if len(out) > p.maxRaw {
			p.split.Add(1) // too big: counted as a send failure
		}
		p.ts++
		bt.SendMedia(out, p.ts)
	}
}

// takeFrameStats returns and resets the largest frame and the number of
// frames that did not fit one packet since the last call.
func (p *pipeline) takeFrameStats() (int, int) {
	return int(p.maxFrame.Swap(0)), int(p.split.Swap(0))
}

// takePeak returns and resets the peak level since the last call.
func (p *pipeline) takePeak() float32 {
	return math.Float32frombits(p.peak.Swap(0))
}
