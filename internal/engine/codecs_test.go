package engine

import "testing"

func TestAACManualBitrateIsNotClamped(t *testing.T) {
	defer func() { aacForced = 0 }()
	aacForced = 256000
	if enc, err := newAAC(48000, 667); err == nil {
		enc.Close()
		t.Fatal("256 kbps should fail when it does not fit the packet")
	}
	aacForced = 0
	enc, err := newAAC(48000, 667)
	if err != nil {
		t.Fatal(err)
	}
	defer enc.Close()
	if got := enc.BitrateKbps(); got != 250 {
		t.Fatalf("Auto AAC bitrate = %d, want 250", got)
	}
}

func TestSSCBitrate(t *testing.T) {
	for _, c := range []struct {
		mtu  int
		cfg  uint8
		want int
	}{
		{667, 0x0C, 256000},  // Galaxy Buds: 630-byte frames
		{1005, 0x0C, 328000}, // Max MTU: 806-byte frames
		{667, 0x04, 128000},  // sink without the "no bitrate limit" bit
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
		{328, 667, 0}, // the requested frame does not fit
		{256, 667, 256000},
		{229, 667, 229000},
	} {
		sscForced = c.kbps
		if got, err := sscBitrate(48000, c.mtu, 0x04); (err != nil) != (c.want == 0) || got != c.want {
			t.Errorf("%d kbps mtu %d: %d %v, want %d", c.kbps, c.mtu, got, err, c.want)
		}
	}
}

func TestSSCUHQ(t *testing.T) {
	defer func() { sscForced = 0 }()
	sscForced = 584
	if !sscUHQ() || sscEncodeRate(48000) != 96000 {
		t.Fatal("584k is not UHQ")
	}
	if got, err := sscBitrate(96000, 667, 0x0A); err != nil || got != 584000 {
		t.Errorf("584k mtu 667: %d %v", got, err)
	}
	sscForced = 886
	if got, err := sscBitrate(96000, 667, 0x0A); err == nil || got != 0 {
		t.Errorf("886k mtu 667: %d, %v, want an error", got, err)
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

func TestSSCWorkingMax(t *testing.T) {
	defer func() { sscWorking = 0 }()
	sscWorking = 229
	if got, _ := sscBitrate(48000, 1005, 0x0C); got != 229000 {
		t.Errorf("Auto on Buds2 Pro: %d, want 229000", got)
	}
}
