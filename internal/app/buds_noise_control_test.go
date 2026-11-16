package app

import (
	"testing"
	"time"

	"sscv2/internal/buds"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/ipc"
	"sscv2/internal/tray"
)

func TestNoiseControlMenuAcrossBluetoothTransports(t *testing.T) {
	headphones := &config.Device{Addr: "00:11:22:33:44:55"}
	a := &App{s: &config.Settings{Headphones: headphones}, t: &tray.Tray{}}
	off := &buds.NoiseControl{Mode: buds.NoiseOff, Modes: 3}
	anc := &buds.NoiseControl{Mode: buds.NoiseANC, Modes: 3}
	ambient := &buds.NoiseControl{Mode: buds.NoiseAmbient, Modes: 3}
	checkMenu := func(want uint8, disabled bool) {
		t.Helper()
		row := a.noiseControlMenuLocked(false)
		if row == nil || row.ID != idNoiseControlMenu || row.Disabled != disabled || len(row.Sub) != 3 {
			t.Fatalf("unexpected noise control row: %+v", row)
		}
		for i, item := range row.Sub {
			if !item.Radio || item.Disabled != disabled || item.Checked != (uint8(i) == want) {
				t.Fatalf("unexpected noise control option: %+v", item)
			}
		}
	}

	a.eng = &workerProcess{}
	a.st = ipc.EngineStatus{Connected: true, Headphones: headphones.Addr, NoiseControl: off}
	checkMenu(buds.NoiseOff, false)
	first := a.stageNoiseControlLocked(buds.NoiseANC)
	checkMenu(buds.NoiseANC, false)
	second := a.stageNoiseControlLocked(buds.NoiseAmbient)
	a.finishNoiseControl(first)
	a.st.NoiseControl = anc // Delayed confirmation of the previous choice.
	a.reconcileNoiseControlLocked()
	checkMenu(buds.NoiseAmbient, false)
	a.finishNoiseControl(second) // Timeout restores the last confirmed mode.
	checkMenu(buds.NoiseANC, false)
	a.eng = nil
	a.native = &nativeProcess{}
	checkMenu(buds.NoiseANC, true)
	a.native.ready, a.native.budsNoiseControl = true, anc
	checkMenu(buds.NoiseANC, false)
	a.stageNoiseControlLocked(buds.NoiseOff)
	checkMenu(buds.NoiseOff, false)
	a.native.budsNoiseControl = off
	a.reconcileNoiseControlLocked()
	if a.pendingNoiseControl != nil {
		t.Fatal("confirmed choice is still pending")
	}
	checkMenu(buds.NoiseOff, false)
	a.native = nil
	a.adapter.Mode = driver.BthUSB
	a.windowsBuds = windowsBudsStatus{addr: headphones.Addr, noiseControl: ambient, noiseRead: time.Now()}
	checkMenu(buds.NoiseAmbient, false)
	a.stageNoiseControlLocked(buds.NoiseANC)
	checkMenu(buds.NoiseANC, false)
	a.s.Headphones = &config.Device{Addr: "00:11:22:33:44:66"}
	a.reconcileNoiseControlLocked()
	if a.pendingNoiseControl != nil {
		t.Fatal("changing headphones did not discard the pending mode")
	}
	if row := a.noiseControlMenuLocked(false); !row.Disabled || row.Sub[buds.NoiseAmbient].Checked {
		t.Fatalf("noise control leaked to a different headset: %+v", row)
	}
}
