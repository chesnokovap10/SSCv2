package app

import (
	"testing"

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
	if a.equalizerMenuLocked(false) != nil {
		t.Fatal("EQ menu appeared before the device reported a preset")
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
	a.clearPendingEqualizer(first)
	check(3)
	a.st.Equalizer = &first.preset // delayed confirmation of the first choice
	a.reconcileEqualizerLocked()
	check(3)
	a.clearPendingEqualizer(second)
	check(1)

	third := a.stageEqualizerLocked(4)
	a.st.Equalizer = &third.preset
	a.reconcileEqualizerLocked()
	if a.pendingEqualizer != nil {
		t.Fatal("confirmed choice is still pending")
	}
	a.clearPendingEqualizer(third)
	check(4)

	a.eng = nil
	if row := a.equalizerMenuLocked(false); row == nil || !row.Disabled || !row.Sub[4].Disabled || !row.Sub[4].Checked {
		t.Fatal("known EQ should stay visible and disabled when the transport stops")
	}
	a.s.Headphones = &config.Device{Addr: "00:11:22:33:44:66"}
	if a.equalizerMenuLocked(false) != nil {
		t.Fatal("EQ support leaked to another device")
	}
}
