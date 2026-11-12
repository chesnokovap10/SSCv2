package app

import (
	"bytes"
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
			var input bytes.Buffer
			p := &workerProcess{done: make(chan struct{}), in: ipc.NewWriter(&input)}
			close(p.done)
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
			var command ipc.Command
			if err := ipc.NewReader(&input).Read(&command); err != nil {
				t.Fatal(err)
			}
			if command.Cmd != "stop" || command.Keep != tc.keep {
				t.Fatalf("unexpected stop command: %+v", command)
			}
		})
	}
}
