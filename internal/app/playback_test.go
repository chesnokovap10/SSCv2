package app

import (
	"bytes"
	"io"
	"os"
	"testing"

	"sscv2/internal/config"
	"sscv2/internal/ipc"
	"sscv2/internal/tray"
)

func TestStopWinUSBEngineTransfersMutedOutputOnlyForRestart(t *testing.T) {
	for _, tc := range []struct {
		name string
		keep bool
	}{
		{"switch transport", false},
		{"restart WinUSB", true},
	} {
		t.Run(tc.name, func(t *testing.T) {
			input, writer := io.Pipe()
			defer input.Close()
			defer writer.Close()
			p := &workerProcess{done: make(chan struct{}), in: ipc.NewWriter(writer)}
			commands := make(chan ipc.Command, 1)
			go func() {
				var command ipc.Command
				_ = ipc.NewReader(input).Read(&command)
				commands <- command
				close(p.done)
			}()
			a := &App{
				t:          &tray.Tray{},
				eng:        p,
				pendingUHQ: true,
				st:         ipc.EngineStatus{MuteEndpoint: "render"},
			}
			a.stopWinUSBEngineLocked(tc.keep)
			if a.eng != nil || a.pendingUHQ {
				t.Fatal("stopped engine still owns playback state")
			}
			if tc.keep {
				if a.carry == nil || a.carry.MuteEndpoint != "render" {
					t.Fatalf("restart carry = %+v, want muted render endpoint", a.carry)
				}
			} else if a.carry != nil {
				t.Fatalf("output carried across a transport change: %+v", a.carry)
			}
			command := <-commands
			if command.Cmd != "stop" || command.Keep != tc.keep {
				t.Fatalf("unexpected stop command: %+v", command)
			}
		})
	}
}

func TestQueuedModeKeepsLastSelection(t *testing.T) {
	a := &App{}
	a.opMu.Lock()
	a.switchMode(config.ModeSSC)
	a.switchMode(config.ModeAAC)
	a.mu.Lock()
	if a.queuedMode != config.ModeAAC || !a.modeDispatch {
		t.Error("latest request lost")
	}
	a.quitting = true
	a.mu.Unlock()
	a.opMu.Unlock()
}

func TestRequestNativeCodecWhileAnotherStartIsPending(t *testing.T) {
	var output bytes.Buffer
	p := &nativeProcess{workerProcess: &workerProcess{in: ipc.NewWriter(&output), done: make(chan struct{}), process: &os.Process{}}, started: make(chan struct{})}
	defer close(p.done)
	a := &App{t: &tray.Tray{}, s: &config.Settings{AllBitrates: true}, native: p}
	old := p.started
	for _, m := range []config.Mode{config.ModeSSC, config.ModeAAC, config.ModeSSC} {
		changed, err := a.requestNativeCodec(p, m)
		if err != nil || !changed {
			t.Fatal(m, changed, err)
		}
	}
	select {
	case <-old:
	default:
		t.Fatal("superseded watchdog still running")
	}
	rd := ipc.NewReader(&output)
	var first, last ipc.NativeStream
	for i := 1; i <= 3; i++ {
		var command ipc.Command
		if err := rd.Read(&command); err != nil || command.Native.Generation != uint64(i) {
			t.Fatal(i, command, err)
		}
		if i == 1 {
			first = *command.Native
		}
		last = *command.Native
	}
	a.onNativeEvent(p, ipc.Event{Ev: ipc.EventNativeReady, Native: &first})
	if p.ready {
		t.Fatal("obsolete SSC event acknowledged later SSC request")
	}
	a.onNativeEvent(p, ipc.Event{Ev: ipc.EventNativeReady, Native: &last})
	if !p.ready {
		t.Fatal("current request did not become ready")
	}
	a.mode = config.ModeSSC
	a.invalidateNativeAfterResumeLocked()
	if changed, err := a.requestNativeCodec(p, config.ModeAAC); err != nil || !changed || p.Generation != 3 {
		t.Fatal("resume sent a command to the retiring worker")
	}
}

func TestRejectUnsupportedNativeUHQKeepsPlaying(t *testing.T) {
	supported := false
	p := &nativeProcess{workerProcess: &workerProcess{done: make(chan struct{})}, ready: true, uhqSupported: &supported, NativeStream: ipc.NativeStream{Mode: config.ModeAAC}}
	a := &App{t: &tray.Tray{}, s: &config.Settings{}, native: p}
	changed, err := a.requestNativeCodec(p, config.ModeSSCUHQ)
	if err != nil || changed || !p.ready || p.Mode != config.ModeAAC {
		t.Fatal("preflight disturbed active playback", err)
	}
}
