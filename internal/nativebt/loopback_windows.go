package nativebt

import (
	"context"
	"encoding/binary"
	"fmt"
	"io"
	"runtime"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"

	"sscv2/internal/audio"
	"sscv2/internal/codec/ssc"
	"sscv2/internal/config"
)

func sendLoopback(ctx context.Context, media io.Writer, out io.Writer, duration time.Duration, mode config.Mode) error {

	if err := audio.InitCOM(); err != nil {
		return err
	}

	capture, err := audio.OpenCapture("")
	if err != nil {
		return err
	}
	defer capture.Close()
	if capture.Format.SampleRate != 48000 || capture.Format.Channels < 1 || capture.Format.Channels > 2 {
		return fmt.Errorf("probe requires a 48 kHz mono or stereo render endpoint, got %s", capture.Format)
	}
	fmt.Fprintf(out, "WASAPI loopback: %s\n", capture.Format)
	blocks := make(chan []float32, 16)
	overflow := make(chan struct{}, 1)
	if err := capture.Start(func(samples []float32, _ int) {
		select {
		case blocks <- append([]float32(nil), samples...):
		default:
			select {
			case overflow <- struct{}{}:
			default:
			}
		}
	}); err != nil {
		return err
	}

	var playback chan bool
	if duration < 0 {
		duration = -duration
		playback = make(chan bool, 1)
		go func() { playback <- playLoopbackTone() }()
	}
	live := duration == time.Nanosecond
	interval := 5 * time.Second
	if live {
		interval = 100 * time.Millisecond
	}
	timeout := time.NewTimer(interval)
	defer timeout.Stop()
	var pending []float32
	var peak float32
	channels := capture.Format.Channels
	fill := func(pcm []float32, frameLen int) error {
		if err := ctx.Err(); err != nil {
			return err
		}
		for i := 0; i < len(pcm); i += 2 {
			for len(pending) == 0 {
				select {
				case pending = <-blocks:
					timeout.Reset(interval)
				case <-overflow:
					return fmt.Errorf("WASAPI capture queue overflow")
				case err := <-capture.Errors():
					return err
				case <-ctx.Done():
					return ctx.Err()
				case <-timeout.C:
					if live {
						clear(pcm[i:])
						timeout.Reset(time.Second * time.Duration(frameLen) / 48000)
						return nil
					}
					return fmt.Errorf("timed out waiting for WASAPI samples")
				}
			}
			for ch := 0; ch < 2; ch++ {
				sample := pending[min(ch, channels-1)]
				peak = max(peak, sample, -sample)
				pcm[i+ch] = sample
			}
			pending = pending[channels:]
		}
		return nil
	}
	err = sendPCM(media, out, mode, DefaultBitrate(mode), int(duration/time.Second)*48000, "WASAPI loopback", live, fill)
	if err != nil {
		return err
	}
	if playback != nil && (!<-playback || peak < 0.003) {
		return fmt.Errorf("loopback test tone was not captured (peak %.4f)", peak)
	}
	fmt.Fprintf(out, "WASAPI capture peak %.4f\n", peak)
	return nil
}

// sendPCM encodes interleaved 48 kHz stereo PCM independently of its source.
func sendPCM(media io.Writer, out io.Writer, mode config.Mode, kbps, frames int, source string, pace bool, fill func([]float32, int) error) error {
	if mode == config.ModeSSC || mode == config.ModeSSCUHQ {
		return sendSSCLive(media, out, mode, kbps, fill)
	}
	var stereo []float32
	return sendAAC(media, out, kbps, frames, source, pace, func(pcm []int16, _ int) error {
		if stereo == nil {
			stereo = make([]float32, len(pcm))
		}
		if err := fill(stereo, len(pcm)/2); err != nil {
			return err
		}
		for i, sample := range stereo {
			pcm[i] = int16(max(-1, min(1, sample)) * 32767)
		}
		return nil
	})
}

// SSC uses one raw frame per RTP packet, with a packet-count timestamp.
func sendSSCLive(media io.Writer, out io.Writer, mode config.Mode, kbps int, fill func([]float32, int) error) error {
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
	var started time.Time
	frameDuration := time.Second * time.Duration(ssc.FrameLen) / time.Duration(rate)
	for count := uint32(0); ; count++ {
		if err := fill(pcm, frames); err != nil {
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
		if count == 0 {
			started = time.Now()
		}
		time.Sleep(time.Until(started.Add(time.Duration(count) * frameDuration)))
		n, err := media.Write(packet)
		if err != nil {
			return fmt.Errorf("write SSC packet %d: %w", count, err)
		}
		if n != len(packet) {
			return io.ErrShortWrite
		}
		if count == 0 {
			fmt.Fprintf(out, "native-%s-ready\n", mode)
		}
	}
}

const (
	SSCProbeKbps = 128
	SSCUHQKbps   = 152
)

// Render a fixture to the default output so WASAPI must capture it before AAC encoding.
func playLoopbackTone() bool {
	const samples = 48000 * 5 / 2
	wav := make([]byte, 44+2*samples)
	copy(wav, "RIFF")
	binary.LittleEndian.PutUint32(wav[4:], uint32(len(wav)-8))
	copy(wav[8:], "WAVEfmt ")
	binary.LittleEndian.PutUint32(wav[16:], 16)
	binary.LittleEndian.PutUint16(wav[20:], 1)
	binary.LittleEndian.PutUint16(wav[22:], 1)
	binary.LittleEndian.PutUint32(wav[24:], 48000)
	binary.LittleEndian.PutUint32(wav[28:], 96000)
	binary.LittleEndian.PutUint16(wav[32:], 2)
	binary.LittleEndian.PutUint16(wav[34:], 16)
	copy(wav[36:], "data")
	binary.LittleEndian.PutUint32(wav[40:], 2*samples)
	for i := 0; i < samples; i++ {
		binary.LittleEndian.PutUint16(wav[44+i*2:], uint16(toneSample(i, samples)))
	}
	play := windows.NewLazySystemDLL("winmm.dll").NewProc("PlaySoundW")
	result, _, _ := play.Call(uintptr(unsafe.Pointer(&wav[0])), 0, 0x0006) // SND_MEMORY | SND_NODEFAULT
	runtime.KeepAlive(wav)
	return result != 0
}

func DefaultBitrate(mode config.Mode) int {
	switch mode {
	case config.ModeSSC:
		return SSCProbeKbps
	case config.ModeSSCUHQ:
		return SSCUHQKbps
	default:
		return probeAACBitrate / 1000
	}
}
