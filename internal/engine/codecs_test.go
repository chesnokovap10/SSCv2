package engine

import "testing"

func TestSSCBitrate(t *testing.T) {
	for _, c := range []struct {
		mtu  int
		cfg  uint8
		want int
	}{
		{667, 0x0C, 192000}, // Galaxy Buds: 484-byte frames
		{1017, 0x0C, 192000},
		{667, 0x04, 128000}, // sink without the "no bitrate limit" bit
		{667, 0, 192000},
		{484, 0x0C, 192000},
		{483, 0x0C, 128000},
	} {
		got, err := sscBitrate(48000, c.mtu, c.cfg)
		if err != nil || got != c.want {
			t.Errorf("mtu %d cfg 0x%02X: %d %v, want %d", c.mtu, c.cfg, got, err, c.want)
		}
	}
	if _, err := sscBitrate(48000, 100, 0x0C); err == nil {
		t.Error("mtu 100: no error")
	}
}
