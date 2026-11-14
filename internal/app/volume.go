package app

import (
	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

// volumeLocked requires a.mu.
func (a *App) volumeLocked() uint8 {
	if a.s.HeadphonesVolume == nil {
		return audio.ScalarTo127(audio.FallbackLevel)
	}
	return min(*a.s.HeadphonesVolume, 127)
}

func (a *App) volumeKey(key uint32) {
	switch key {
	case 0xae:
		a.adjustVolume(idVolDown)
	case 0xaf:
		a.adjustVolume(idVolUp)
	case 0xad:
		a.adjustVolume(idVolMute)
	}
}

func (a *App) adjustVolume(action int) {
	a.mu.Lock()
	defer a.mu.Unlock()
	levelValue, muted, available := a.sliderVolumeLocked()
	if !available {
		return
	}
	level := int(levelValue)
	switch action {
	case idVolDown:
		level = max(0, level-4)
	case idVolUp:
		level = min(127, level+4)
		muted = false
	case idVolMute:
		muted = !muted
	}
	a.setVolumeLocked(uint8(level), muted)
}

func (a *App) sliderVolume() (uint8, bool, bool) {
	a.mu.Lock()
	defer a.mu.Unlock()
	return a.sliderVolumeLocked()
}

func (a *App) sliderVolumeLocked() (uint8, bool, bool) {
	if p := a.native; p != nil && a.mode.Streaming() {
		v := p.volume
		if update := p.volumePending; update != nil && update.Endpoint == v.Endpoint {
			v = *update
		}
		return v.Level, v.Muted, v.Endpoint != ""
	}
	return a.volumeLocked(), a.s.HeadphonesMuted, a.eng != nil && a.mode.Streaming()
}

func (a *App) setSliderVolume(value uint8) {
	a.mu.Lock()
	defer a.mu.Unlock()
	if level, muted, available := a.sliderVolumeLocked(); available && (level != value || muted) {
		a.setVolumeLocked(value, false)
	}
}

func (a *App) setVolumeLocked(value uint8, muted bool) {
	if p := a.native; p != nil && p.volume.Endpoint != "" && a.mode.Streaming() {
		p.volumePending = &ipc.NativeVolume{Endpoint: p.volume.Endpoint, Level: value, Muted: muted}
		if !p.volumeWriting {
			p.volumeWriting = true
			go a.writeNativeVolume(p)
		}
		return
	}
	if a.eng == nil {
		return
	}
	changed := a.volumeLocked() != value || a.s.HeadphonesMuted != muted
	a.eng.queueVolume(ipc.Command{Cmd: "volume", Volume: value, On: muted})
	a.s.HeadphonesVolume, a.s.HeadphonesMuted = &value, muted
	_ = config.Save(a.s)
	if changed && !a.s.DisableAnimations {
		a.t.PulseVolume()
	}
}

func (a *App) writeNativeVolume(p *nativeProcess) {
	// Finish writes before restoring Windows routing or opening another worker.
	a.opMu.Lock()
	defer a.opMu.Unlock()
	for {
		a.mu.Lock()
		update := p.volumePending
		if a.native != p || update == nil || update.Endpoint != p.volume.Endpoint {
			p.volumePending = nil
			p.volumeWriting = false
			a.mu.Unlock()
			return
		}
		a.mu.Unlock()
		err := audio.SetEndpointVolume(update.Endpoint, float32(update.Level)/127, update.Muted)
		a.mu.Lock()
		if p.volumePending == update {
			p.volumePending = nil
		}
		if err == nil && p.volume.Endpoint == update.Endpoint {
			p.volume = *update
		}
		pulse := err == nil && !a.s.DisableAnimations
		a.mu.Unlock()
		if err != nil {
			logf("Buds volume: %v", err)
		} else if pulse {
			a.t.PulseVolume()
		}
	}
}
