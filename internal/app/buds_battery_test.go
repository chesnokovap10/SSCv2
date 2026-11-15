package app

import (
	"testing"

	"sscv2/internal/battery"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

func TestBudsBatteryMenu(t *testing.T) {
	const addr = "00:11:22:33:44:55"
	a := App{
		s:   &config.Settings{Headphones: &config.Device{Addr: addr}},
		eng: &workerProcess{},
		st:  ipc.EngineStatus{Connected: true, Headphones: addr, Battery: &battery.BudsLevel{Left: 0, Right: 87}},
	}
	want := T(" · Л 0% / П 87%", " · L 0% / R 87%")
	if suffix := a.batteryMenuSuffixLocked(); suffix != want {
		t.Fatalf("suffix = %q, want %q", suffix, want)
	}
	a.st.Battery.Right = -1
	want = T(" · Л 0% / П —", " · L 0% / R —")
	if suffix := a.batteryMenuSuffixLocked(); suffix != want {
		t.Fatalf("suffix = %q, want %q", suffix, want)
	}
	a.st.Connected = false
	if suffix := a.batteryMenuSuffixLocked(); suffix != "" {
		t.Fatalf("suffix after disconnect = %q", suffix)
	}
}
