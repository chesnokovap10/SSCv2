package app

import (
	"testing"

	"sscv2/internal/buds"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

func TestBudsBatteryMenu(t *testing.T) {
	const addr = "00:11:22:33:44:55"
	a := App{
		s:   &config.Settings{Headphones: &config.Device{Addr: addr}},
		eng: &workerProcess{},
		st:  ipc.EngineStatus{Connected: true, Headphones: addr, Battery: &buds.Level{Left: 0, Right: 87}},
	}
	if text := a.batteryMenuTextLocked(); text != "0%|87%" {
		t.Fatalf("battery text = %q", text)
	}
	a.st.Battery.Right = -1
	if text := a.batteryMenuTextLocked(); text != "0%|—" {
		t.Fatalf("battery text with one missing level = %q", text)
	}
	a.st.Connected = false
	if text := a.batteryMenuTextLocked(); text != "" {
		t.Fatalf("battery text after disconnect = %q", text)
	}
}
