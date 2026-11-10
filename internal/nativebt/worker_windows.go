package nativebt

import (
	"bufio"
	"context"
	"errors"
	"fmt"
	"io"
	"sync/atomic"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
)

// RunWorker keeps the process alive across codec changes. Each change releases
// the old AVDTP stream before negotiating the next one.
func RunWorker(input io.Reader, out io.Writer, args []string, mode config.Mode) error {
	if len(args) != 3 || args[1] == "" {
		return errors.New("native worker requires a profile path, render endpoint and device address")
	}
	endpoint, address := args[1], args[2]
	args = args[:1]
	controlCtx, stopControl := context.WithCancel(context.Background())
	defer stopControl()
	var volumeReady atomic.Bool
	control := make(chan error, 1)
	go func() {
		control <- runAVRCP(controlCtx, args[0], endpoint, func() { volumeReady.Store(true) }, out)
	}()
	// Arm the incoming control channel before releasing the Windows A2DP endpoint.
	select {
	case err := <-control:
		return err
	case <-time.After(500 * time.Millisecond):
	}
	if _, err := helper.Call(ipc.Request{Op: "native-a2dp-release", Device: address}); err != nil {
		return err
	}
	fallback, stopVolume, err := audio.WatchEndpointPCMGain(endpoint)
	if err != nil {
		return err
	}
	defer stopVolume()
	readGain := func() float32 {
		if volumeReady.Load() {
			return 1
		}
		return fallback()
	}
	pcm, err := helper.OpenBudsPCM()
	if err != nil {
		return err
	}
	defer pcm.Close()
	commands := make(chan config.Mode)
	stop := make(chan struct{})
	defer close(stop)
	var readErr error
	go func() {
		defer close(commands)
		scanner := bufio.NewScanner(input)
		for scanner.Scan() {
			next := config.Mode(scanner.Text())
			if !next.Streaming() {
				readErr = fmt.Errorf("invalid native codec %q", next)
				return
			}
			select {
			case commands <- next:
			case <-stop:
				return
			}
		}
		readErr = scanner.Err()
	}()

	for {
		ctx, cancel := context.WithCancel(context.Background())
		done := make(chan error, 1)
		go func(mode config.Mode) { done <- runRenderPCM(ctx, args, out, mode, pcm.Read, readGain) }(mode)
		for {
			select {
			case err := <-control:
				control = nil
				if volumeReady.Load() {
					cancel()
					<-done
					return err
				}
				fmt.Fprintf(out, "Buds AVRCP unavailable: %v\n", err)
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
				mode = next
			}
			break
		}
	}
}
