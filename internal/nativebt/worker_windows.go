package nativebt

import (
	"context"
	"errors"
	"fmt"
	"io"
	"slices"
	"strings"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/driver"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
)

// RunWorker keeps the process alive across codec changes. Each change releases
// the old AVDTP stream before negotiating the next one.
func RunWorker(input io.Reader, output io.Writer, handleMediaKey func(int)) int {
	reader, events := ipc.NewReader(input), ipc.NewWriter(output)
	var cfg ipc.NativeConfig
	err := reader.Read(&cfg)
	if err == nil {
		if cfg.Path == "" || cfg.RenderEndpoint == "" || cfg.Device == "" || !cfg.Stream.Valid() {
			err = errors.New("invalid native worker configuration")
		} else {
			err = runWorker(cfg, reader, events, handleMediaKey)
		}
	} else {
		err = fmt.Errorf("read native worker configuration: %w", err)
	}
	if err != nil {
		_ = events.Write(ipc.Event{Ev: ipc.EventNativeError, Msg: err.Error()})
		return 1
	}
	return 0
}

type workerLog struct{ events *ipc.Writer }

func (w workerLog) Write(p []byte) (int, error) {
	err := w.events.Write(ipc.Event{Ev: ipc.EventNativeLog, Msg: strings.TrimRight(string(p), "\r\n")})
	if err != nil {
		return 0, err
	}
	return len(p), nil
}

func runWorker(cfg ipc.NativeConfig, reader *ipc.Reader, events *ipc.Writer, handleMediaKey func(int)) error {
	out := workerLog{events: events}
	volume := newBudsVolume()
	readGain, stopVolume, err := audio.WatchEndpointPCMGain(cfg.RenderEndpoint, driver.BudsRenderName, volume.set)
	if err != nil {
		return err
	}
	defer stopVolume()
	controlCtx, stopControl := context.WithCancel(context.Background())
	defer stopControl()
	go watchAVRCP(controlCtx, cfg.Path, out, handleMediaKey, volume)
	started := time.Now()
	released := make(chan error, 1)
	go func(completed chan<- error) {
		_, err := helper.Call(ipc.Request{Op: "native-a2dp-release", Device: cfg.Device})
		completed <- err
		close(completed)
	}(released)
	defer func(completed <-chan error) { <-completed }(released)
	for {
		select {
		case err := <-released:
			if err != nil {
				return err
			}
			released = nil
		default:
			if cfg.StereoEndpoint == "" || slices.ContainsFunc(audio.List(false, audio.StateActive), func(e audio.Endpoint) bool { return e.ID == cfg.StereoEndpoint }) {
				time.Sleep(20 * time.Millisecond)
				continue
			}
		}
		break
	}
	fmt.Fprintf(out, "A2DP endpoint released in %v\n", time.Since(started).Round(time.Millisecond))
	pcm, err := helper.OpenBudsPCM()
	if err != nil {
		return err
	}
	defer pcm.Close()
	commands := make(chan ipc.NativeStream)
	stop := make(chan struct{})
	defer close(stop)
	var readErr error
	go func() {
		defer close(commands)
		for {
			var command ipc.Command
			if err := reader.Read(&command); err != nil {
				if !errors.Is(err, io.EOF) {
					readErr = err
				}
				return
			}
			if command.Cmd == ipc.CommandStop {
				return
			}
			if command.Cmd != ipc.CommandCodec || command.Native == nil || !command.Native.Valid() {
				readErr = fmt.Errorf("invalid native worker command %q", command.Cmd)
				return
			}
			select {
			case commands <- *command.Native:
			case <-stop:
				return
			}
		}
	}()
	stream := cfg.Stream

	for {
		ctx, cancel := context.WithCancel(context.Background())
		done := make(chan error, 1)
		go func(stream ipc.NativeStream) {
			ready := func() error {
				return events.Write(ipc.Event{Ev: ipc.EventNativeReady, Native: &stream})
			}
			done <- runRenderPCM(ctx, cfg.Path, out, stream.Mode, stream.BitrateKbps, pcm.Read, func() float32 {
				return volume.gain(readGain)
			}, ready)
		}(stream)
		for {
			select {
			case err := <-released:
				if err != nil {
					cancel()
					<-done
					return err
				}
				released = nil
				continue
			case err := <-done:
				cancel()
				return err
			case next, open := <-commands:
				cancel()
				if err := <-done; err != nil && !errors.Is(err, context.Canceled) {
					return err
				}
				if !open {
					return readErr
				}
				stream = next
			}
			break
		}
	}
}
