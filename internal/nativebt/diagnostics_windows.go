package nativebt

import (
	"context"
	"encoding/binary"
	"errors"
	"fmt"
	"io"
	"math"
	"runtime"
	"strconv"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"

	"sscv2/internal/audio"
	"sscv2/internal/bitrate"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/ipc"
)

// RunProbe opens the probe driver interface and runs the requested AAC diagnostic.
func RunProbe(args []string, out io.Writer) error {
	var duration time.Duration
	if len(args) >= 2 && args[0] == "-stream-aac" {
		seconds, err := strconv.Atoi(args[1])
		if err != nil || seconds < 1 || seconds > 3600 {
			return fmt.Errorf("stream duration must be 1 to 3600 seconds")
		}
		duration = time.Duration(seconds) * time.Second
		args = args[2:]
	}
	var send func(io.Writer) error
	if duration == 0 && len(args) > 0 {
		switch args[0] {
		case "-loopback-aac":
			duration = -2 * time.Second
			args = args[1:]
		case "-configure-aac":
			send = func(media io.Writer) error { return sendAACTone(media, out) }
			args = args[1:]
		}
	}
	if len(args) > 1 || len(args) == 1 && len(args[0]) > 0 && args[0][0] == '-' {
		return fmt.Errorf("usage: [-configure-aac|-loopback-aac|-stream-aac seconds] [profile-driver device interface path]")
	}
	if duration != 0 {
		send = func(media io.Writer) error { return sendLoopback(media, out, duration) }
	}

	if err := requireTestSigning(); err != nil {
		return err
	}
	ctx := context.Background()
	if len(args) == 1 {
		return runAVDTP(ctx, args[0], out, false, ipc.NativeStream{Mode: config.ModeAAC, BitrateKbps: bitrate.NativeDiagnosticDefault(config.ModeAAC)}, send, nil)
	}
	path, err := singleInterface()
	if err != nil {
		return err
	}
	return runAVDTP(ctx, path, out, false, ipc.NativeStream{Mode: config.ModeAAC, BitrateKbps: bitrate.NativeDiagnosticDefault(config.ModeAAC)}, send, nil)
}

func ProbeLocalProfile(ctx context.Context, address string, out io.Writer) error {
	path, err := LocalProfilePath(address)
	if err != nil {
		return err
	}
	if err := requireTestSigning(); err != nil {
		return err
	}
	return runAVDTP(ctx, path, out, false, ipc.NativeStream{}, nil, nil)
}

func ProbeLocalHandoff(ctx context.Context, address string, out io.Writer) (err error) {
	if err := driver.SetNativeStereoService(address, false); err != nil {
		return fmt.Errorf("release Windows A2DP: %w", err)
	}
	defer func() {
		if restoreErr := driver.SetNativeStereoService(address, true); restoreErr != nil {
			err = errors.Join(err, fmt.Errorf("restore Windows A2DP: %w", restoreErr))
		}
	}()
	return ProbeLocalProfile(ctx, address, out)
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
	device, err := driver.OpenBudsPCM(wavePath)
	if err != nil {
		return err
	}
	defer device.Close()
	render := renderPCM{out: out, read: device.Read}
	return render.stream(ctx, path, ipc.NativeStream{Mode: mode, BitrateKbps: bitrate.NativeDiagnosticDefault(mode)}, func() error {
		_, err := fmt.Fprintf(out, "native-%s-ready\n", mode)
		return err
	}, nil, nil)
}

func sendAACTone(media io.Writer, out io.Writer) error {
	return sendAAC(media, out, bitrate.NativeDiagnosticDefault(config.ModeAAC), 2*48000, "440 Hz test tone", true, func(pcm []int16, offset int) error {
		for i := 0; i < len(pcm)/2; i++ {
			sample := toneSample(offset+i, 2*48000)
			pcm[2*i], pcm[2*i+1] = sample, sample
		}
		return nil
	}, nil)
}

func toneSample(index, samples int) int16 {
	envelope := max(0, min(1, float64(min(index, samples-index))/960))
	return int16(2600 * envelope * math.Sin(2*math.Pi*440*float64(index)/48000))
}

func sendLoopback(media io.Writer, out io.Writer, duration time.Duration) error {
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
	if err := capture.Start(func(samples []float32, _ int, _ bool) {
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
	const interval = 5 * time.Second
	timeout := time.NewTimer(interval)
	defer timeout.Stop()
	var pending []float32
	var peak float32
	channels := capture.Format.Channels
	fill := func(pcm []float32) error {
		for i := 0; i < len(pcm); i += 2 {
			for len(pending) == 0 {
				select {
				case pending = <-blocks:
					timeout.Reset(interval)
				case <-overflow:
					return fmt.Errorf("WASAPI capture queue overflow")
				case err := <-capture.Errors():
					return err
				case <-timeout.C:
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
	err = sendPCM(media, out, config.ModeAAC, bitrate.NativeDiagnosticDefault(config.ModeAAC), int(duration/time.Second)*48000, "WASAPI loopback", false, fill, nil)
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
