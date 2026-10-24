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

func TestSSCUHQ(t *testing.T) {
	defer func() { sscForced = 0 }()
	sscForced = 584000
	if !sscUHQ() || sscEncodeRate(48000) != 96000 {
		t.Fatal("584k is not UHQ")
	}
	if got, err := sscBitrate(96000, 667, 0x0A); err != nil || got != 584000 {
		t.Errorf("584k mtu 667: %d %v", got, err)
	}
	sscForced = 886000
	if got, _ := sscBitrate(96000, 667, 0x0A); got != 584000 {
		t.Errorf("886k mtu 667: %d, want 584000", got)
	}
	if !sscNeedsOver(886) || sscNeedsOver(584) {
		t.Error("sscNeedsOver UHQ")
	}
	e, err := newSSC(48000, 1005)
	if err != nil {
		t.Fatal(err)
	}
	defer e.Close()
	if e.FrameLen() != 432 {
		t.Fatalf("FrameLen %d", e.FrameLen())
	}
	out, err := e.Encode(make([]float32, 864))
	if err != nil || len(out) != 1000 || out[0] != 0xFF || out[1]&0xF0 != 0xE0 {
		t.Fatalf("UHQ frame: %d % X %v", len(out), out[:4], err)
	}
}
