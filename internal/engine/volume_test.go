package engine

import "testing"

func TestWinUSBStartupAndHardwareVolumeHandoff(t *testing.T) {
	var p pipeline
	p.setVolume(32, false)
	pcm := make([]float32, 2*128)
	fill := func() {
		for i := range pcm {
			pcm[i] = 1
		}
	}
	fill()
	p.applyVolume(pcm, false)
	gain := float32(32) / 127
	gain *= gain
	for _, sample := range pcm {
		if sample != gain {
			t.Fatalf("startup sample = %v, want %v", sample, gain)
		}
	}
	fill()
	p.applyVolume(pcm, true)
	previous := gain
	for i := 0; i < len(pcm); i += 2 {
		if pcm[i] < previous || pcm[i] > 1 || pcm[i] != pcm[i+1] {
			t.Fatalf("hardware handoff at frame %d: %v", i/2, pcm[i:i+2])
		}
		previous = pcm[i]
	}
	if pcm[0] <= gain || pcm[0] >= 1 || pcm[190] != 1 {
		t.Fatal("handoff failed to ramp to unity within 96 frames")
	}
	p.setVolume(5, false)
	fill()
	p.applyVolume(pcm, true)
	for _, sample := range pcm {
		if sample != 1 {
			t.Fatal("hardware adjustment applied a second gain stage")
		}
	}
	fill()
	p.applyVolume(pcm, false)
	gain = float32(5) / 127
	if pcm[0] != gain*gain {
		t.Fatal("missing software attenuation after loss of AVRCP")
	}
}

func TestWinUSBMuteAndZeroVolumeSilencePCM(t *testing.T) {
	var p pipeline
	for _, hardware := range []bool{false, true} {
		for _, level := range []uint8{0, 80} {
			p.setVolume(level, level != 0)
			pcm := []float32{1, -1}
			p.applyVolume(pcm, hardware)
			if pcm[0] != 0 || pcm[1] != 0 {
				t.Fatalf("audible sample at level %d, hardware=%t", level, hardware)
			}
		}
	}
}
