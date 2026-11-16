package buds

import (
	"bytes"
	"encoding/hex"
	"testing"
	"time"
)

func TestBudsPlacementFromBothStatusFrames(t *testing.T) {
	for _, body := range [][]byte{
		{0x60, 0x02, 98, 97, 1, 0, 0x22},
		{0x61, 0x0b, 0x03, 98, 97, 1, 0, 0x22},
	} {
		crc := budsCRC(body)
		frame := append([]byte{0xfd, byte(len(body) + 2), 0}, body...)
		frame = append(frame, byte(crc), byte(crc>>8), 0xdd)
		var d Decoder
		var got Status
		d.FeedStatus(frame[:5], func(status Status) { got = status })
		d.FeedStatus(frame[5:], func(status Status) { got = status })
		if want := (Status{Level: Level{Left: 98, Right: 97}, Placement: 0x22}); got != want {
			t.Fatalf("message %#x: %+v, want %+v", body[0], got, want)
		}
	}
}

func TestBudsEqualizerStatusAndRequest(t *testing.T) {
	// Extended status reports the preset after the case level and sync flag.
	body := []byte{0x61, 0x0e, 0x04, 98, 97, 1, 0, 0x11, 84, 0, 3}
	crc := budsCRC(body)
	frame := append([]byte{0xfd, byte(len(body) + 2), 0}, body...)
	frame = append(frame, byte(crc), byte(crc>>8), 0xdd)
	var d Decoder
	var got *uint8
	d.FeedStatus(frame, func(status Status) { got = status.Equalizer })
	if got == nil || *got != 3 {
		t.Fatalf("extended report did not decode Dynamic preset: %v", got)
	}

	request := SPPNew.EqualizerRequest(0)
	if !bytes.Equal(request, []byte{0xfd, 0x04, 0x10, 0x86, 0, 0x3e, 0xb1, 0xdd}) {
		t.Fatalf("Normal request %x", request)
	}
	// Actual reply captured from Buds2 Pro after selecting Normal.
	ack, _ := hex.DecodeString("fd0550428600f3c2dd")
	d.FeedStatus(ack, func(status Status) {
		if !status.EqualizerAck || status.Equalizer == nil || *status.Equalizer != 0 || status.Level.Known() {
			t.Fatalf("unexpected EQ confirmation: %+v", status)
		}
		got = status.Equalizer
	})
	if *got != 0 {
		t.Fatal("missing Normal confirmation")
	}
}

func TestEqualizerAcrossProtocolLayouts(t *testing.T) {
	cases := []struct {
		name     string
		protocol Protocol
		payload  []byte
		want     uint8
	}{
		{"Renamed headset", SPPNew, []byte{14, 4, 98, 97, 1, 0, 0x11, 84, 0, EqualizerCustom}, EqualizerCustom},
		{"Galaxy Buds Pro(ABCD)", SPPStandard, []byte{14, 4, 98, 97, 1, 0, 0x11, 84, 0, 3}, 3},
		{"Galaxy Buds+ (ABCD)", PlusSPP, []byte{14, 4, 98, 97, 1, 0, 0x11, 84, 0, 0, 0, 4}, 4},
		{"Galaxy Buds (ABCD)", LegacySPP, []byte{2, 1, 98, 97, 1, 0, 0x11, 0, 0, 0, 1, 7}, 3},
	}
	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			protocol := ProtocolForName(tc.name)
			if protocol != tc.protocol {
				t.Fatalf("protocol = %v, want %v", protocol, tc.protocol)
			}
			decoder := Decoder{Protocol: protocol}
			var value *uint8
			decoder.FeedStatus(protocol.request(0x61, tc.payload...), func(s Status) { value = s.Equalizer })
			if value == nil || *value != tc.want {
				t.Fatalf("reported preset = %v, want %d", value, tc.want)
			}
		})
	}
	if got := LegacySPP.EqualizerRequest(3); !bytes.Equal(got[:6], []byte{0xfe, 0, 5, 0x86, 1, 7}) || got[len(got)-1] != 0xee {
		t.Fatalf("legacy EQ request = %x", got)
	}
	if got := SPPNew.ManagerInfo(); !bytes.Equal(got, []byte{0xfd, 6, 0x10, 0x88, 1, 1, 0x22, 0xda, 0x58, 0xdd}) {
		t.Fatalf("manager request = %x", got)
	}
}

func TestBudsEqualizerIgnoresStaleStatusAfterAck(t *testing.T) {
	var eq EqualizerState
	now := time.Now()
	old, next := uint8(1), uint8(3)
	eq.Observe(Status{Equalizer: &old}, now)
	eq.Observe(Status{Equalizer: &next, EqualizerAck: true}, now)
	if stale := eq.Observe(Status{Equalizer: &old}, now.Add(time.Second)); stale != nil {
		t.Fatalf("stale status overrode command acknowledgement: %d", *stale)
	}
	if latest := eq.Observe(Status{Equalizer: &old}, now.Add(3*time.Second)); latest == nil || *latest != old {
		t.Fatal("EQ changed outside SSCv2 but the later status was ignored")
	}
}

func TestBudsRemovalRequiresKnownTransitionAndDebounces(t *testing.T) {
	var r Removal
	now := time.Now()
	for _, state := range []byte{0x22, 0x11, 0x12, 0x02, 0x20} {
		if deadline := r.Observe(state, now); !deadline.IsZero() {
			t.Fatalf("unexpected pending pause for %#x", state)
		}
	}
	r.Observe(0x22, now)
	if r.Confirm(now.Add(RemovalDelay / 2)) {
		t.Fatal("paused before debounce elapsed")
	}
	r.Observe(0x12, now.Add(RemovalDelay/2))
	if r.Confirm(now.Add(RemovalDelay)) {
		t.Fatal("worn report did not cancel pause")
	}
	r.Observe(0x23, now)
	r.Observe(0x33, now.Add(RemovalDelay/2))
	if !r.Confirm(now.Add(RemovalDelay)) {
		t.Fatal("case update postponed or lost pause")
	}
	if !r.Observe(0x44, now).IsZero() || r.Confirm(now.Add(RemovalDelay)) {
		t.Fatal("case closure repeated pause")
	}
}

func TestBudsDecoderExtendedStatus(t *testing.T) {
	// Captured Buds2 SPPNew status from omarchy-headphones/PROTOCOL.md.
	frame, err := hex.DecodeString("fd2a00610b031212010111000000bf22010040014001030003660002001000000000110200010000400000993ddd")
	if err != nil {
		t.Fatal(err)
	}
	for split := range len(frame) + 1 {
		var d Decoder
		var got []Level
		report := func(level Level) { got = append(got, level) }
		d.Feed(frame[:split], report)
		d.Feed(frame[split:], report)
		if len(got) != 1 || got[0] != (Level{Left: 18, Right: 18}) {
			t.Fatalf("split %d: reports = %v, want [{18 18}]", split, got)
		}
	}
}

func TestBudsDecoderBasicStatus(t *testing.T) {
	var d Decoder
	var got []Level
	report := func(level Level) { got = append(got, level) }
	// Basic status for a depleted left earbud and an unavailable right earbud.
	body := []byte{0x60, 0x02, 0, 0xff}
	crc := budsCRC(body)
	frame := []byte{0xfd, 6, 0, body[0], body[1], body[2], body[3], byte(crc), byte(crc >> 8), 0xdd}
	d.Feed([]byte{1, 2, 3}, report)
	d.Feed(append([]byte{0xfd, 6, 0, 0x60, 0, 80, 90, 0, 0, 0xdd}, frame...), report)
	if len(got) != 1 || got[0] != (Level{Left: 0, Right: -1}) {
		t.Fatalf("reports = %v, want [{0 -1}]", got)
	}
}
