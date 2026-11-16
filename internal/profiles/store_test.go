package profiles

import (
	"os"
	"path/filepath"
	"testing"

	"sscv2/internal/bitrate"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

func TestWorkingMax(t *testing.T) {
	b2p := DevID{1, 0x0075, 0xA013}
	store, err := OpenProfiles(filepath.Join(t.TempDir(), ProfileFilename))
	if err != nil {
		t.Fatal(err)
	}
	if k, m := store.WorkingMax(config.ModeSSC, b2p, "Galaxy Buds2 Pro JK08", false); k != 229 || m != "Samsung Galaxy Buds2 Pro" {
		t.Errorf("Buds2 Pro by model and id: %d %q", k, m)
	}
	if k, _ := store.WorkingMax(config.ModeSSC, b2p, "renamed", false); k != 0 {
		t.Errorf("a shared Device ID must not inherit a limit: %d", k)
	}
	if k, _ := store.WorkingMax(config.ModeSSC, b2p, "Galaxy Buds2", false); k != 0 {
		t.Errorf("Buds2 inherited the Buds2 Pro limit: %d", k)
	}
	if k, _ := store.WorkingMax(config.ModeSSC, DevID{}, "Buds2 Pro JK08", false); k != 229 {
		t.Errorf("Buds2 Pro by name (no id): %d", k)
	}
	if k, _ := store.WorkingMax(config.ModeSSC, DevID{1, 0x0075, 0xA0FF}, "Buds2 Pro JK08", false); k != 0 {
		t.Errorf("another Samsung product id named like Buds2 Pro: %d", k)
	}
	if k, _ := store.WorkingMax(config.ModeSSCUHQ, b2p, "Buds2 Pro", true); k != bitrate.Unsupported {
		t.Errorf("UHQ on Buds2 Pro: %d, want Unsupported", k)
	}
	if k, _ := store.WorkingMax(config.ModeAAC, b2p, "", false); k != 0 {
		t.Errorf("AAC not profiled: %d", k)
	}
}

func TestLegacyProfileMigrationAndFactoryCommands(t *testing.T) {
	dir := t.TempDir()
	oldPath := filepath.Join(dir, "bitrate-profiles.json")
	legacy := `[{"model":"Samsung Galaxy Buds2 Pro","nameMatch":"buds2 pro",
		"deviceId":{"source":1,"vendor":117,"product":40979},
		"commands":{"equalizer":144},"verifiedMaxKbps":{"ssc":192}}]`
	if err := os.WriteFile(oldPath, []byte(legacy), 0o600); err != nil {
		t.Fatal(err)
	}
	store, err := OpenProfiles(filepath.Join(dir, ProfileFilename))
	if err != nil {
		t.Fatal(err)
	}
	if _, err := os.Stat(oldPath); !os.IsNotExist(err) {
		t.Fatalf("legacy file was not moved: %v", err)
	}
	if len(store.current()) != len(defaultProfiles) {
		t.Fatalf("factory catalog contains %d profiles, want %d", len(store.current()), len(defaultProfiles))
	}
	id := DevID{1, 0x0075, 0xA013}
	if k, _ := store.WorkingMax(config.ModeSSC, id, "Buds2 Pro", false); k != 192 {
		t.Fatalf("migration changed manual limit to %d", k)
	}
	if got := store.Commands(id, "Buds2 Pro").Equalizer; got != 144 {
		t.Fatalf("migration changed manual command to %#x", got)
	}
	if got := store.Commands(id, "Galaxy Buds Live (AA11)"); got.Noise != 0x98 || got.NoiseUpdate != 0x9b || got.NoiseModes != 2 {
		t.Fatalf("Buds Live factory commands = %+v", got)
	}
	if got := store.Commands(id, "Galaxy Buds 4 Pro"); got.Noise != 0x78 || got.NoiseModes != 4 {
		t.Fatalf("Buds4 Pro factory commands = %+v", got)
	}
	newID := DevID{1, 0x0075, 0xA014}
	stream := StreamInfo{Kbps: 224}
	if err := store.Observe(newID, "Galaxy Buds3 Pro (AA11)", true, nil, config.ModeAAC, stream); err != nil {
		t.Fatal(err)
	}
	entry := findProfile(store.current(), newID, "renamed")
	if entry == nil || entry.Commands.NoiseModes != 4 || entry.Transports["windows"].Streams[config.ModeAAC] != stream {
		t.Fatalf("discovered stream did not fill the factory profile: %+v", entry)
	}
}

func TestManualEditsSurviveAutomaticProfileUpdates(t *testing.T) {
	path := filepath.Join(t.TempDir(), ProfileFilename)
	store, err := OpenProfiles(path)
	if err != nil {
		t.Fatal(err)
	}
	newID := DevID{Source: 1, Vendor: 117, Product: 4321}
	if err := os.WriteFile(path, []byte("["), 0o600); err != nil {
		t.Fatal(err)
	}
	caps := ipc.CodecCapabilities{AAC: true, SSC: true, AACMaxBps: 250000}
	stream := StreamInfo{Kbps: 256, PayloadBytes: 667, FitsPacketKbps: 256}
	if err := store.Observe(newID, "Buds Test", false, &caps, config.ModeSSC, stream); err == nil {
		t.Fatal("incomplete manual edit should postpone the automatic write")
	}
	if data, err := os.ReadFile(path); err != nil || string(data) != "[" {
		t.Fatalf("incomplete manual edit was overwritten: %q, %v", data, err)
	}
	data := `[{"model":"Buds Test","deviceId":{"source":1,"vendor":117,"product":4321},
		"commands":{"equalizer":145,"noise":146,"noiseModes":2},
		"transports":{"windows":{"verifiedMaxKbps":{"ssc":192}}},"verifiedMaxKbps":{"ssc":229}}]`
	if err := os.WriteFile(path, []byte(data), 0o600); err != nil {
		t.Fatal(err)
	}
	if err := store.Refresh(); err != nil {
		t.Fatal(err)
	}
	reloaded, err := OpenProfiles(path)
	if err != nil {
		t.Fatal(err)
	}
	if got, _ := reloaded.WorkingMax(config.ModeSSC, newID, "arbitrary name", true); got != 192 {
		t.Fatalf("Windows manual limit = %d, want 192", got)
	}
	if got, _ := reloaded.WorkingMax(config.ModeSSC, newID, "", false); got != 229 {
		t.Fatalf("WinUSB manual limit = %d, want 229", got)
	}
	if commands := reloaded.Commands(newID, "renamed"); commands.Equalizer != 145 || commands.Noise != 146 || commands.NoiseModes != 2 {
		t.Fatalf("manual command IDs were lost: %+v", commands)
	}
	entry := findProfile(reloaded.current(), newID, "").Transports["winusb"]
	if entry.Advertised == nil || *entry.Advertised != caps || entry.Streams[config.ModeSSC] != stream {
		t.Fatalf("deferred observations were not saved: %+v", entry)
	}
}

func TestSimulatedHeadphoneConnections(t *testing.T) {
	for _, tc := range []struct {
		name      string
		model     string
		id        DevID
		wantModes uint8
		native    bool
	}{
		{"known commands without codec data", "Galaxy Buds 4 Pro (A1B2)", DevID{1, 0x75, 0xA014}, 4, true},
		{"unknown model with unique ID", "Test Earbuds X", DevID{1, 0x456, 0x123}, 0, false},
		{"unknown model with shared ID", "Test Earbuds Y", DevID{1, 0x75, 0xA013}, 0, false},
	} {
		t.Run(tc.name, func(t *testing.T) {
			path := filepath.Join(t.TempDir(), ProfileFilename)
			store, err := OpenProfiles(path)
			if err != nil {
				t.Fatal(err)
			}
			before := findProfile(store.current(), tc.id, tc.model)
			if tc.wantModes != 0 {
				if before == nil || before.ID.Valid() || len(before.Transports) != 0 || before.Commands.NoiseModes != tc.wantModes {
					t.Fatalf("expected a command-only factory profile: %+v", before)
				}
			} else if before != nil {
				t.Fatalf("unknown headphones matched an existing profile: %+v", before)
			}

			caps := ipc.CodecCapabilities{AAC: true, AACMaxBps: 256000, SSC: true}
			if err := store.Observe(tc.id, tc.model, tc.native, &caps, config.ModeOff, StreamInfo{}); err != nil {
				t.Fatal(err)
			}
			stream := StreamInfo{Kbps: 224}
			if !tc.native {
				stream.PayloadBytes, stream.FitsPacketKbps = 667, 250
			}
			if err := store.Observe(tc.id, tc.model, tc.native, nil, config.ModeAAC, stream); err != nil {
				t.Fatal(err)
			}
			reopened, err := OpenProfiles(path)
			if err != nil {
				t.Fatal(err)
			}
			record := findProfile(reopened.current(), tc.id, tc.model)
			if record == nil || record.ID != tc.id {
				t.Fatalf("saved profile was not found: %+v", record)
			}
			if record.Commands.Equalizer != 0x86 || record.Commands.Noise != 0x78 || record.Commands.NoiseModes != tc.wantModes {
				t.Fatalf("unexpected command IDs: %+v", record.Commands)
			}
			entry := record.Transports[transportName(tc.native)]
			if entry.Advertised == nil || *entry.Advertised != caps || entry.Streams[config.ModeAAC] != stream {
				t.Fatalf("observations did not survive reload: %+v", entry)
			}
			if k, _ := reopened.WorkingMax(config.ModeAAC, tc.id, tc.model, tc.native); k != 0 {
				t.Fatalf("automatic observation created a verified limit: %d", k)
			}
		})
	}
}
