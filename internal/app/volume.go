package app

import (
	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/driver"
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
	if id := a.nativeVolumeEndpointLocked(); id != "" {
		level, muted, err := audio.EndpointVolume(id)
		return audio.ScalarTo127(level), muted, err == nil
	}
	return a.volumeLocked(), a.s.HeadphonesMuted, a.eng != nil && a.mode.Streaming()
}

func (a *App) nativeVolumeEndpointLocked() string {
	if a.native != nil && a.mode.Streaming() {
		saved := a.s.NativeRenderEndpoint
		if endpoint := audio.FindRenderEndpoint(driver.BudsRenderName, saved, audio.StateActive); endpoint.ID != "" {
			return endpoint.ID
		}
		return saved
	}
	return ""
}

func (a *App) setSliderVolume(value uint8) {
	a.mu.Lock()
	defer a.mu.Unlock()
	if level, muted, available := a.sliderVolumeLocked(); available && (level != value || muted) {
		a.setVolumeLocked(value, false)
	}
}

func (a *App) setVolumeLocked(value uint8, muted bool) {
	if id := a.nativeVolumeEndpointLocked(); id != "" {
		if err := audio.SetEndpointVolume(id, float32(value)/127, muted); err != nil {
			logf("Buds volume: %v", err)
			return
		}
		if !a.s.DisableAnimations {
			a.t.PulseVolume()
		}
		return
	}
	changed := a.volumeLocked() != value || a.s.HeadphonesMuted != muted
	if err := a.eng.in.Write(ipc.Command{Cmd: "volume", Volume: value, On: muted}); err != nil {
		logf("headphone volume: %v", err)
		return
	}
	a.s.HeadphonesVolume, a.s.HeadphonesMuted = &value, muted
	_ = config.Save(a.s)
	if changed && !a.s.DisableAnimations {
		a.t.PulseVolume()
	}
}
