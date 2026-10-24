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

func TestSSCForced(t *testing.T) {
	defer func() { sscForced = 0 }()
	for _, c := range []struct{ kbps, mtu, want int }{
		{328, 1017, 328000},
		{328, 667, 256000}, // not raised: steps down to what fits
		{256, 667, 256000},
		{229, 667, 229000},
	} {
		sscForced = c.kbps * 1000
		if got, err := sscBitrate(48000, c.mtu, 0x04); err != nil || got != c.want {
			t.Errorf("%d kbps mtu %d: %d %v, want %d", c.kbps, c.mtu, got, err, c.want)
		}
	}
	if sscNeedsOver(256) || !sscNeedsOver(328) || sscNeedsOver(0) {
		t.Error("sscNeedsOver")
	}
}
