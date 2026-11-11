package nativebt

import (
	"bufio"
	"context"
	"errors"
	"fmt"
	"io"
	"slices"
	"strconv"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
)

// RunWorker keeps the process alive across codec changes. Each change releases
// the old AVDTP stream before negotiating the next one.
func RunWorker(input io.Reader, out io.Writer, args []string, mode config.Mode, handleMediaKey func(int)) error {
	if len(args) != 5 || args[1] == "" {
		return errors.New("native worker requires a profile path, render endpoint, device address, stereo endpoint and bitrate")
	}
	kbps, err := strconv.Atoi(args[4])
	if err != nil || kbps <= 0 {
		return fmt.Errorf("invalid native bitrate %q", args[4])
	}
	endpoint, address, stereo := args[1], args[2], args[3]
	args = args[:1]
	controlCtx, stopControl := context.WithCancel(context.Background())
	defer stopControl()
	go watchAVRCP(controlCtx, args[0], out, handleMediaKey)
	started := time.Now()
	released := make(chan error, 1)
	go func(completed chan<- error) {
		_, err := helper.Call(ipc.Request{Op: "native-a2dp-release", Device: address})
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
			if stereo == "" || slices.ContainsFunc(audio.List(false, audio.StateActive), func(e audio.Endpoint) bool { return e.ID == stereo }) {
				time.Sleep(20 * time.Millisecond)
				continue
			}
		}
		break
	}
	fmt.Fprintf(out, "A2DP endpoint released in %v\n", time.Since(started).Round(time.Millisecond))
	readGain, stopVolume, err := audio.WatchEndpointPCMGain(endpoint)
	if err != nil {
		return err
	}
	defer stopVolume()
	pcm, err := helper.OpenBudsPCM()
	if err != nil {
		return err
	}
	defer pcm.Close()
	type codecSetting struct {
		mode config.Mode
		kbps int
	}
	commands := make(chan codecSetting)
	stop := make(chan struct{})
	defer close(stop)
	var readErr error
	go func() {
		defer close(commands)
		scanner := bufio.NewScanner(input)
		for scanner.Scan() {
			var next codecSetting
			if _, err := fmt.Sscan(scanner.Text(), &next.mode, &next.kbps); err != nil || !next.mode.Streaming() || next.kbps <= 0 {
				readErr = fmt.Errorf("invalid native codec setting %q", scanner.Text())
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
		go func(mode config.Mode, kbps int) { done <- runRenderPCM(ctx, args, out, mode, kbps, pcm.Read, readGain) }(mode, kbps)
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
				mode, kbps = next.mode, next.kbps
			}
			break
		}
	}
}
