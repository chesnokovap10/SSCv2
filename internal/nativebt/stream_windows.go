package nativebt

import (
	"encoding/binary"
	"fmt"
	"io"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/bitrate"
	"sscv2/internal/codec/aac"
	"sscv2/internal/codec/ssc"
	"sscv2/internal/config"
)

// sendPCM encodes interleaved 48 kHz stereo PCM independently of its source.
func sendPCM(media io.Writer, out io.Writer, mode config.Mode, kbps, frames int, source string, pace bool, fill func([]float32) error, ready func() error) error {
	if mode == config.ModeSSC || mode == config.ModeSSCUHQ {
		return sendSSCLive(media, mode, kbps, fill, ready)
	}
	var stereo []float32
	return sendAAC(media, out, kbps, frames, source, pace, func(pcm []int16, _ int) error {
		if stereo == nil {
			stereo = make([]float32, len(pcm))
		}
		if err := fill(stereo); err != nil {
			return err
		}
		for i, sample := range stereo {
			pcm[i] = int16(max(-1, min(1, sample)) * 32767)
		}
		return nil
	}, ready)
}

// packetPacer keeps the sample clock during small scheduling delays. Rebase
// after a larger stall so queued packets are not sent in a burst.
type packetPacer struct {
	next time.Time
}

func (p *packetPacer) wait(period time.Duration) {
	time.Sleep(time.Until(p.next))
	now := time.Now()
	if p.next.IsZero() || now.Sub(p.next) >= period/2 {
		p.next = now
	}
	p.next = p.next.Add(period)
}

// SSC uses one raw frame per RTP packet, with a packet-count timestamp.
func sendSSCLive(media io.Writer, mode config.Mode, kbps int, fill func([]float32) error, ready func() error) error {
	rate, frames := 48000, ssc.FrameLen
	var up *audio.Upsampler2x
	if mode == config.ModeSSCUHQ {
		rate, frames = 96000, ssc.FrameLen/2
		up = audio.NewUpsampler2x()
	}
	encoder, err := ssc.New(rate, kbps*1000)
	if err != nil {
		return err
	}
	defer encoder.Close()

	pcm := make([]float32, 2*frames)
	packet := make([]byte, 12, 12+ssc.FrameBytes(rate, kbps*1000))
	packet[0], packet[1] = 0x80, 0x60
	binary.BigEndian.PutUint32(packet[8:12], 1)
	var pacer packetPacer
	frameDuration := time.Second * time.Duration(ssc.FrameLen) / time.Duration(rate)
	for count := uint32(0); ; count++ {
		if err := fill(pcm); err != nil {
			return err
		}
		samples := pcm
		if up != nil {
			samples = up.Process(pcm)
		}
		frame, err := encoder.Encode(samples)
		if err != nil {
			return err
		}
		binary.BigEndian.PutUint16(packet[2:4], uint16(count))
		binary.BigEndian.PutUint32(packet[4:8], count+1)
		packet = append(packet[:12], frame...)
		pacer.wait(frameDuration)
		n, err := media.Write(packet)
		if err != nil {
			return fmt.Errorf("write SSC packet %d: %w", count, err)
		}
		if n != len(packet) {
			return io.ErrShortWrite
		}
		if count == 0 && ready != nil {
			if err := ready(); err != nil {
				return err
			}
		}
	}
}

func sendAAC(media io.Writer, out io.Writer, kbps, samples int, source string, pace bool, fill func([]int16, int) error, ready func() error) error {
	const sampleRate = 48000
	budget := bitrate.NativeAACBudget(kbps)
	encoder, err := aac.New(sampleRate, 2, kbps*1000, budget)
	if err != nil {
		return fmt.Errorf("initialize AAC encoder: %w", err)
	}
	defer encoder.Close()

	pcm := make([]int16, encoder.FrameLen*2)
	packet := make([]byte, 12+budget)
	packet[0], packet[1] = 0x80, 0xe0 // RTP v2, marker, dynamic payload type 96.
	binary.BigEndian.PutUint32(packet[8:12], 1)
	started := time.Now()
	var pacer packetPacer
	frameDuration := time.Second * time.Duration(encoder.FrameLen) / sampleRate
	var sequence uint16
	var timestamp uint64
	if samples == 0 {
		defer func() { fmt.Fprintf(out, "Sent %d AAC RTP packets (%s)\n", timestamp/uint64(encoder.FrameLen), source) }()
	}
	for offset := 0; samples == 0 || offset < samples; offset += encoder.FrameLen {
		if err := fill(pcm, offset); err != nil {
			return err
		}
		payload, err := encoder.Encode(pcm)
		if err != nil {
			return err
		}
		if len(payload) == 0 {
			continue
		}
		if len(payload) > len(packet)-12 {
			return fmt.Errorf("AAC frame exceeds packet budget: %d", len(payload))
		}
		binary.BigEndian.PutUint16(packet[2:4], sequence)
		binary.BigEndian.PutUint32(packet[4:8], uint32(timestamp))
		copy(packet[12:], payload)
		if pace {
			pacer.wait(frameDuration)
		}
		size := 12 + len(payload)
		n, err := media.Write(packet[:size])
		if err != nil {
			return fmt.Errorf("write AAC packet %d (%d bytes): %w", sequence, size, err)
		}
		if n != size {
			return io.ErrShortWrite
		}
		if timestamp == 0 && ready != nil {
			if err := ready(); err != nil {
				return err
			}
		}
		sequence++
		timestamp += uint64(encoder.FrameLen)
	}
	if timestamp == 0 {
		return fmt.Errorf("AAC encoder produced no packets")
	}
	finished := started.Add(time.Duration(timestamp) * time.Second / sampleRate)
	if pace {
		finished = pacer.next
	}
	time.Sleep(time.Until(finished.Add(150 * time.Millisecond)))
	fmt.Fprintf(out, "Sent %d AAC RTP packets (%s)\n", timestamp/uint64(encoder.FrameLen), source)
	return nil
}
