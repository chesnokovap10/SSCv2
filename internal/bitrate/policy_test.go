package bitrate

import (
	"testing"

	"sscv2/internal/config"
)

func TestOfferedByTransport(t *testing.T) {
	for _, tt := range []struct {
		name    string
		policy  Policy
		mode    config.Mode
		kbps    int
		offered bool
	}{
		{"WinUSB AAC standard", Policy{}, config.ModeAAC, 224, true},
		{"WinUSB AAC 256", Policy{}, config.ModeAAC, 256, false},
		{"WinUSB AAC Max MTU", Policy{MaxMTU: true}, config.ModeAAC, 256, true},
		{"WinUSB All bitrates keeps MTU", Policy{AllBitrates: true}, config.ModeSSC, 328, false},
		{"WinUSB SSC extended", Policy{MaxMTU: true}, config.ModeSSC, 328, true},
		{"WinUSB UHQ standard", Policy{}, config.ModeSSCUHQ, 584, true},
		{"WinUSB UHQ 886", Policy{}, config.ModeSSCUHQ, 886, false},
		{"WinUSB UHQ extended", Policy{MaxMTU: true}, config.ModeSSCUHQ, 886, true},
		{"native AAC standard", Policy{Native: true}, config.ModeAAC, 224, true},
		{"native Max MTU ignored", Policy{Native: true, MaxMTU: true}, config.ModeAAC, 256, false},
		{"native AAC experimental", Policy{Native: true, AllBitrates: true}, config.ModeAAC, 256, true},
		{"native SSC experimental", Policy{Native: true, AllBitrates: true}, config.ModeSSC, 328, true},
		{"profile blocks Auto", Policy{WorkingMax: Unsupported}, config.ModeSSCUHQ, 0, false},
		{"All bitrates bypasses profile", Policy{AllBitrates: true, WorkingMax: Unsupported}, config.ModeSSCUHQ, 0, true},
	} {
		t.Run(tt.name, func(t *testing.T) {
			if got := tt.policy.Offered(tt.mode, tt.kbps); got != tt.offered {
				t.Fatalf("Offered(%s, %d) = %t, want %t", tt.mode, tt.kbps, got, tt.offered)
			}
		})
	}
}

func TestAutoAndExperimentalRates(t *testing.T) {
	p := Policy{Native: true, AllBitrates: true, MaxMTU: true, WorkingMax: 229}
	if got := p.NativeAuto(config.ModeAAC); got != 224 {
		t.Errorf("native AAC Auto = %d, want 224", got)
	}
	if got := p.NativeAuto(config.ModeSSC); got != 229 {
		t.Errorf("native SSC Auto = %d, want 229", got)
	}
	if !p.Experimental(config.ModeAAC, 256) || !p.Experimental(config.ModeSSC, 256) || p.Experimental(config.ModeSSC, 229) {
		t.Fatal("incorrect experimental rates")
	}
	if got := (Policy{}).WinUSBAutoCeiling(config.ModeAAC); got != 250 {
		t.Errorf("standard WinUSB AAC ceiling = %d, want 250", got)
	}
	if got := (Policy{MaxMTU: true}).WinUSBAutoCeiling(config.ModeSSCUHQ); got != 886 {
		t.Errorf("extended WinUSB UHQ ceiling = %d, want 886", got)
	}
}

func TestWorkingMax(t *testing.T) {
	b2p := DevID{1, 0x0075, 0xA013}
	if k, m := WorkingMax(config.ModeSSC, b2p, "renamed"); k != 229 || m != "Samsung Galaxy Buds2 Pro" {
		t.Errorf("Buds2 Pro by id: %d %q", k, m)
	}
	if k, _ := WorkingMax(config.ModeSSC, DevID{}, "Buds2 Pro JK08"); k != 229 {
		t.Errorf("Buds2 Pro by name (no id): %d", k)
	}
	if k, _ := WorkingMax(config.ModeSSC, DevID{1, 0x0075, 0xA0FF}, "Buds2 Pro JK08"); k != 0 {
		t.Errorf("another Samsung product id named like Buds2 Pro: %d", k)
	}
	if k, _ := WorkingMax(config.ModeSSCUHQ, b2p, ""); k != Unsupported {
		t.Errorf("UHQ on Buds2 Pro: %d, want Unsupported", k)
	}
	if k, _ := WorkingMax(config.ModeAAC, b2p, ""); k != 0 {
		t.Errorf("AAC not profiled: %d", k)
	}
}

func TestSavedInvalidSSCBitrateFallsBackToAuto(t *testing.T) {
	for _, native := range []bool{false, true} {
		p := Policy{Native: native}
		if got := p.Selected(config.ModeSSC, 123); got != 0 {
			t.Fatalf("native=%v: selected %d kbps, want Auto", native, got)
		}
	}
}
