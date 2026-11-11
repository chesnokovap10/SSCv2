package bt

import "testing"

func TestVolumeConfirmationKeepsHardwareGainDuringAdjustments(t *testing.T) {
	var volume volPump
	volume.sent = 102
	if !volume.accept(102) {
		t.Fatal("initial hardware level was rejected")
	}
	readyAt := volume.hardwareAfter.Load()
	volume.sent = 5
	if !volume.accept(5) || volume.hardwareAfter.Load() != readyAt {
		t.Fatal("changing the level restarted hardware volume settling")
	}
	if volume.accept(127) || volume.hardwareAfter.Load() != 0 {
		t.Fatal("unexpected maximum level did not disable hardware gain")
	}
	if !volume.accept(5) || volume.hardwareAfter.Load() == 0 {
		t.Fatal("hardware gain was not restored after confirming the correct level")
	}
	volume.reset()
	if volume.hardwareAfter.Load() != 0 {
		t.Fatal("hardware volume remained active after disconnect")
	}
}
