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
	generation     atomic.Uint64
	pcmAt          time.Time
	mu             sync.Mutex
	enc            Encoder
	maxRaw         int
	ts             uint32
	pcm            []float32 // pending stereo samples (residual between callbacks)
	stereo         []float32
	accum          []byte
	active         atomic.Bool
	errors         chan error // first failure of the current encoder
	softwareGain   float32    // previous block's gain during software attenuation
	softwareVolume bool
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
	p.generation.Add(1)
	p.enc = enc
	p.softwareVolume = false
	if p.errors == nil {
		p.errors = make(chan error, 1)
	}
	select {
	case <-p.errors:
	default:
	}
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
func (p *pipeline) onCapture(s []float32, frames, ch, rate int, discontinuity bool, mix [][2]float32, captured time.Time, generation uint64) {
	p.frames.Add(uint64(frames))
	p.activity.Observe(s[:frames*ch])
	if !p.active.Load() {
		return
	}
	p.mu.Lock()
	defer p.mu.Unlock()
	if p.enc == nil || p.generation.Load() != generation {
		return
	}
	if discontinuity {
		// The residual belongs to the stream before the capture gap.
		p.pcm = p.pcm[:0]
	}

	if len(p.pcm) == 0 {
		p.pcmAt = captured
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
	if ch != 2 || mix != nil {
		for _, v := range p.pcm[len(p.pcm)-frames*2:] {
			if a := float32(math.Abs(float64(v))); a > peak {
				peak = a
			}
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
		if err := p.encodePerPacket(block, rate, &off); err != nil {
			p.fail(err)
			return
		}
		p.pcmAt = p.sampleTime(off, rate)
		n := copy(p.pcm, p.pcm[off:])
		p.pcm = p.pcm[:n]
		return
	}
	p.accum = p.accum[:0]
	firstTS := p.ts
	firstAt := p.pcmAt
	nframes := 0
	for off+block <= len(p.pcm) {
		out, err := p.encode(p.pcm[off : off+block])
		if err != nil {
			p.fail(err)
			return
		}
		if len(out) > 0 {
			p.encBytes.Add(uint64(len(out)))
			if int32(len(out)) > p.maxFrame.Load() {
				p.maxFrame.Store(int32(len(out)))
			}
			if len(out) > p.maxRaw {
				p.split.Add(1)
				if nframes > 0 {
					bt.SendMedia(p.accum, firstTS, firstAt)
					p.accum = p.accum[:0]
					nframes = 0
				}
				if p.frag {
					// RFC 3016: same timestamp, marker on the last fragment.
					bt.SendMediaFrame(out, p.ts, p.maxRaw, p.sampleTime(off, rate))
				} else {
					bt.SendMedia(out, p.ts, p.sampleTime(off, rate)) // too big: counted as a send failure
				}
				p.ts += uint32(p.enc.FrameLen())
				off += block
				firstTS = p.ts
				firstAt = p.sampleTime(off, rate)
				continue
			}
			if len(p.accum)+len(out) > p.maxRaw && nframes > 0 {
				bt.SendMedia(p.accum, firstTS, firstAt)
				p.accum = p.accum[:0]
				nframes = 0
				firstTS = p.ts
				firstAt = p.sampleTime(off, rate)
			}
			p.accum = append(p.accum, out...)
			nframes++
		}
		p.ts += uint32(p.enc.FrameLen())
		off += block
	}
	if nframes > 0 {
		bt.SendMedia(p.accum, firstTS, firstAt)
	}
	// keep the residual for the next callback
	p.pcmAt = p.sampleTime(off, rate)
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

// applyVolume runs under p.mu on interleaved stereo PCM.
func (p *pipeline) applyVolume(pcm []float32, hardware bool) {
	level := p.volume.Load()
	if level == 0 || level >= 128 {
		clear(pcm)
		p.softwareVolume, p.softwareGain = true, 0
		return
	}
	if !hardware {
		gain := float32(level) / 127
		gain *= gain
		p.softwareVolume, p.softwareGain = true, gain
		if gain == 1 {
			return
		}
		for i := range pcm {
			pcm[i] *= gain
		}
		return
	}
	if p.softwareVolume {
		// AVRCP has settled. Release PCM attenuation over about 2 ms.
		frames := min(len(pcm)/2, 96)
		for frame := range frames {
			gain := 1 - (1-p.softwareGain)*float32(frames-frame-1)/float32(frames)
			pcm[frame*2] *= gain
			pcm[frame*2+1] *= gain
		}
		p.softwareVolume = false
	}
}

func (p *pipeline) encode(pcm []float32) ([]byte, error) {
	p.applyVolume(pcm, bt.HardwareVolumeActive())
	return p.enc.Encode(pcm)
}

// encodePerPacket: one frame per packet, the RTP timestamp counts packets.
func (p *pipeline) encodePerPacket(block, rate int, off *int) error {
	for *off+block <= len(p.pcm) {
		out, err := p.encode(p.pcm[*off : *off+block])
		*off += block
		if err != nil {
			return err
		}
		if len(out) == 0 {
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
		bt.SendMedia(out, p.ts, p.sampleTime(*off-block, rate))
	}
	return nil
}

// fail runs under mu on the capture thread; the session owns teardown.
func (p *pipeline) fail(err error) {
	p.active.Store(false)
	p.pcm = p.pcm[:0]
	select {
	case p.errors <- err:
	default:
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

func (p *pipeline) sampleTime(offset, rate int) time.Time {
	return p.pcmAt.Add(time.Second * time.Duration(offset/2) / time.Duration(rate))
}

func (p *pipeline) resetCaptureSource() {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.generation.Add(1)
	p.pcm = p.pcm[:0]
}
