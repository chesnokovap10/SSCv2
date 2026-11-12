package app

import (
	"testing"

	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/ipc"
	"sscv2/internal/tray"
)

func TestStreamingIconRequiresCurrentConnection(t *testing.T) {
	p := &workerProcess{}
	for _, tc := range []struct {
		name                           string
		connected, streaming, resuming bool
		want                           tray.Color
	}{
		{"live", true, true, false, tray.Green},
		{"disconnected", false, true, false, tray.Blue},
		{"suspended stream", true, false, false, tray.Blue},
		{"stale after sleep", true, true, true, tray.Amber},
	} {
		t.Run(tc.name, func(t *testing.T) {
			a := &App{mode: config.ModeAAC, eng: p,
				adapter: driver.Status{Mode: driver.WinUSB},
				st:      ipc.EngineStatus{Phase: "streaming", Connected: tc.connected, Streaming: tc.streaming}}
			if tc.resuming {
				a.resumeEngine = p
			}
			got, _ := a.stateLocked()
			if got != tc.want {
				t.Fatalf("color = %v, want %v", got, tc.want)
			}
		})
	}
}

func TestResumeIgnoresOffAndDuplicateNotifications(t *testing.T) {
	p := &workerProcess{}
	for _, a := range []*App{
		{mode: config.ModeOff, eng: p},
		{mode: config.ModeAAC},
		{mode: config.ModeAAC, eng: p, quitting: true},
		{mode: config.ModeAAC, eng: p, resumeEngine: p},
	} {
		before := a.resumeEngine
		a.onResume() // no tray or process needed: must not schedule recovery
		if a.resumeEngine != before {
			t.Fatal("unexpected resume recovery")
		}
	}
}
