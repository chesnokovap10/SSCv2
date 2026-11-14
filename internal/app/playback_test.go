package app

import (
	"io"
	"testing"

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
