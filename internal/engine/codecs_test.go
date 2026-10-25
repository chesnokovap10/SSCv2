package engine

import "testing"

func TestSSCBitrate(t *testing.T) {
	for _, c := range []struct {
		mtu  int
		cfg  uint8
		want int
	}{
		{667, 0x0C, 256000}, // Galaxy Buds: 630-byte frames
		{1005, 0x0C, 328000}, // Max MTU: 806-byte frames
		{667, 0x04, 128000}, // sink without the "no bitrate limit" bit
		{667, 0, 256000},
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

func TestMaxMTUAuto(t *testing.T) {
	defer func() { sscMaxMTU = false }()
	sscMaxMTU = true
	if got, _ := sscBitrate(48000, 1005, 0x0C); got != 328000 {
		t.Errorf("max MTU auto: %d, want 328000", got)
	}
	if got, _ := sscBitrate(48000, 1005, 0x04); got != 128000 {
		t.Errorf("max MTU auto, limited sink: %d, want 128000", got)
	}
	if got, _ := sscBitrate(96000, 1005, 0x0A); got != 886000 {
		t.Errorf("max MTU UHQ auto: %d, want 886000", got)
	}
}

func TestBitrateFits(t *testing.T) {
	for _, c := range []struct {
		codec  string
		kbps   int
		maxMTU bool
		want   bool
	}{
		{"aac", 0, false, true}, {"aac", 224, false, true}, {"aac", 256, false, false}, {"aac", 256, true, true},
		{"ssc", 256, false, true}, {"ssc", 328, false, false}, {"ssc", 328, true, true},
		{"ssc_uhq", 584, false, true}, {"ssc_uhq", 886, false, false}, {"ssc_uhq", 886, true, true},
	} {
		if got := BitrateFits(c.codec, c.kbps, c.maxMTU); got != c.want {
			t.Errorf("%s %d maxMTU=%v: %v", c.codec, c.kbps, c.maxMTU, got)
		}
	}
}

func TestWorkingMax(t *testing.T) {
	b2p := DevID{1, 0x0075, 0xA013}
	if k, m := WorkingMax("ssc", b2p, "renamed"); k != 229 || m != "Samsung Galaxy Buds2 Pro" {
		t.Errorf("Buds2 Pro by id: %d %q", k, m)
	}
	if k, _ := WorkingMax("ssc", DevID{}, "Buds2 Pro JK08"); k != 229 {
		t.Errorf("Buds2 Pro by name (no id): %d", k)
	}
	if k, _ := WorkingMax("ssc", DevID{1, 0x0075, 0xA0FF}, "Buds2 Pro JK08"); k != 0 {
		t.Errorf("another Samsung product id named like Buds2 Pro: %d", k)
	}
	if k, _ := WorkingMax("aac", b2p, ""); k != 0 {
		t.Errorf("AAC not profiled: %d", k)
	}
	defer func() { sscWorking, sscMaxMTU = 0, false }()
	sscWorking, sscMaxMTU = 229000, true
	if got, _ := sscBitrate(48000, 1005, 0x0C); got != 229000 {
		t.Errorf("Auto on Buds2 Pro: %d, want 229000", got)
	}
}
