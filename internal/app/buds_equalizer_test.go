package app

import (
	"testing"

	"sscv2/internal/buds"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
	"sscv2/internal/tray"
)

func TestEqualizerShowsLatestChoiceAndRollsBackOnFailure(t *testing.T) {
	const addr = "00:11:22:33:44:55"
	normal := uint8(0)
	a := App{
		s:   &config.Settings{Headphones: &config.Device{Addr: addr, Name: "Переименованные наушники"}},
		eng: &workerProcess{}, t: &tray.Tray{},
		st: ipc.EngineStatus{Headphones: addr, Connected: true, Equalizer: &normal},
	}
	a.st.Equalizer = nil
	if row := a.equalizerMenuLocked(false); !row.Disabled || row.Sub[0].Checked {
		t.Fatal("EQ should be visible, disabled, and unchecked before the device reports a preset")
	}
	a.st.Equalizer = &normal
	check := func(want int) {
		t.Helper()
		for i, row := range a.equalizerMenuLocked(false).Sub {
			if row.Checked != (i == want) {
				t.Fatalf("preset %d marked %v; want only %d", i, row.Checked, want)
			}
		}
	}
	first := a.stageEqualizerLocked(1)
	check(1)
	a.st.Equalizer = nil
	a.reconcileEqualizerLocked()
	check(1)
	a.st.Equalizer = &normal
	second := a.stageEqualizerLocked(3)
	a.finishEqualizer(first, true)
	check(3)
	a.st.Equalizer = &first.value // delayed confirmation of the first choice
	a.reconcileEqualizerLocked()
	check(3)
	a.finishEqualizer(second, true)
	check(1)

	third := a.stageEqualizerLocked(4)
	a.st.Equalizer = &third.value
	a.reconcileEqualizerLocked()
	if a.pendingEqualizer != nil {
		t.Fatal("confirmed choice is still pending")
	}
	a.finishEqualizer(third, true)
	check(4)

	a.eng = nil
	if row := a.equalizerMenuLocked(false); row == nil || !row.Disabled || !row.Sub[4].Disabled || !row.Sub[4].Checked {
		t.Fatal("known EQ should stay visible and disabled when the transport stops")
	}
	a.s.Headphones = &config.Device{Addr: "00:11:22:33:44:66"}
	if row := a.equalizerMenuLocked(false); !row.Disabled || row.Sub[4].Checked {
		t.Fatal("EQ support leaked to another device")
	}
}

func TestUnknownBudsEqualizerAndNoiseControlFailures(t *testing.T) {
	const addr = "00:11:22:33:44:55"
	controls := &buds.NoiseControl{Mode: buds.NoiseOff, Modes: 4, Fallback: true}
	a := App{
		s:   &config.Settings{Headphones: &config.Device{Addr: addr}},
		eng: &workerProcess{}, t: &tray.Tray{},
		st: ipc.EngineStatus{Headphones: addr, Connected: true, NoiseControl: controls},
	}
	eq := a.stageEqualizerLocked(1)
	if eq == nil || !a.equalizerMenuLocked(false).Sub[1].Checked {
		t.Fatal("the generic EQ request did not mark the selected preset")
	}
	a.finishEqualizer(eq, true)
	if row := a.equalizerMenuLocked(false); !row.Disabled || row.Sub[1].Checked || a.stageEqualizerLocked(2) != nil {
		t.Fatal("unconfirmed EQ request did not disable the row and roll back the selection")
	}
	noise := a.stageNoiseControlLocked(buds.NoiseAdaptive)
	if row := a.noiseControlMenuLocked(false); noise == nil || len(row.Sub) != 4 || !row.Sub[buds.NoiseAdaptive].Checked {
		t.Fatal("the generic noise control request did not select Adaptive")
	}
	a.finishNoiseControl(noise)
	if row := a.noiseControlMenuLocked(false); row.Disabled || !row.Sub[buds.NoiseOff].Checked ||
		row.Sub[buds.NoiseAdaptive].Checked || row.Sub[buds.NoiseAdaptive].Disabled {
		t.Fatal("unconfirmed noise control request did not restore Off and keep Adaptive available")
	}
	if a.stageNoiseControlLocked(buds.NoiseAdaptive) == nil {
		t.Fatal("could not retry Adaptive after an unconfirmed request")
	}
	a.st.Connected = false
	a.reconcileEqualizerLocked()
	a.reconcileNoiseControlLocked()
	a.st.Connected = true
	if a.equalizerMenuLocked(false).Disabled || a.noiseControlMenuLocked(false).Disabled {
		t.Fatal("reconnecting did not make the generic controls available again")
	}
}
