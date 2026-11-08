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
)

func sendAACLoopback(ctx context.Context, media io.Writer, out io.Writer, duration time.Duration) error {

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
		fmt.Fprintln(out, "native-aac-ready")
	}
	timeout := time.NewTimer(interval)
	defer timeout.Stop()
	var pending []float32
	var peak float32
	channels := capture.Format.Channels
	err = sendAAC(media, out, int(duration/time.Second)*48000, "WASAPI loopback", live, func(pcm []int16, _ int) error {
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
						timeout.Reset(time.Second * 1024 / 48000)
						return nil
					}
					return fmt.Errorf("timed out waiting for WASAPI samples")
				}
			}
			for ch := 0; ch < 2; ch++ {
				sample := pending[min(ch, channels-1)]
				peak = max(peak, sample, -sample)
				pcm[i+ch] = int16(max(-1, min(1, sample)) * 32767)
			}
			pending = pending[channels:]
		}
		return nil
	})
	if err != nil {
		return err
	}
	if playback != nil && (!<-playback || peak < 0.003) {
		return fmt.Errorf("loopback test tone was not captured (peak %.4f)", peak)
	}
	fmt.Fprintf(out, "WASAPI capture peak %.4f\n", peak)
	return nil
}

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
