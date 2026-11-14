package engine

import "testing"

func TestWinUSBVolumeUsesOneGainStage(t *testing.T) {
	var p pipeline
	p.volumeStartedAt.Store(10000)
	p.setVolume(102, false)
	if got := p.pcmGain(true, 10100); got != 0 {
		t.Fatalf("audio was not muted during startup: gain %v", got)
	}
	if got := p.pcmGain(false, 10300); got != 0 {
		t.Fatalf("audio started before volume confirmation: gain %v", got)
	}
	p.setVolume(5, false)
	if got := p.pcmGain(true, 10300); got != 1 {
		t.Fatalf("an AVRCP volume decrease changed PCM gain to %v", got)
	}
	if got := p.pcmGain(false, 11249); got != 0 {
		t.Fatalf("software fallback started before the AVRCP settling period: gain %v", got)
	}
	if got := p.pcmGain(false, 11250); got <= 0 || got >= 1 {
		t.Fatalf("software fallback did not attenuate PCM: gain %v", got)
	}
	p.setVolume(5, true)
	if got := p.pcmGain(false, 11250); got != 0 {
		t.Fatalf("software fallback did not mute PCM: gain %v", got)
	}
}
