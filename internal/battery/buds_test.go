package battery

import (
	"encoding/hex"
	"testing"
)

func TestBudsDecoderExtendedStatus(t *testing.T) {
	// Captured Buds2 SPPNew status from omarchy-headphones/PROTOCOL.md.
	frame, err := hex.DecodeString("fd2a00610b031212010111000000bf22010040014001030003660002001000000000110200010000400000993ddd")
	if err != nil {
		t.Fatal(err)
	}
	for split := range len(frame) + 1 {
		var d BudsDecoder
		var got []BudsLevel
		report := func(level BudsLevel) { got = append(got, level) }
		d.Feed(frame[:split], report)
		d.Feed(frame[split:], report)
		if len(got) != 1 || got[0] != (BudsLevel{Left: 18, Right: 18}) {
			t.Fatalf("split %d: reports = %v, want [{18 18}]", split, got)
		}
	}
}

func TestBudsDecoderBasicStatus(t *testing.T) {
	var d BudsDecoder
	var got []BudsLevel
	report := func(level BudsLevel) { got = append(got, level) }
	// Basic status for a depleted left earbud and an unavailable right earbud.
	body := []byte{0x60, 0x02, 0, 0xff}
	crc := budsCRC(body)
	frame := []byte{0xfd, 6, 0, body[0], body[1], body[2], body[3], byte(crc), byte(crc >> 8), 0xdd}
	d.Feed([]byte{1, 2, 3}, report)
	d.Feed(append([]byte{0xfd, 6, 0, 0x60, 0, 80, 90, 0, 0, 0xdd}, frame...), report)
	if len(got) != 1 || got[0] != (BudsLevel{Left: 0, Right: -1}) {
		t.Fatalf("reports = %v, want [{0 -1}]", got)
	}
}
