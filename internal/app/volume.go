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
	if a.eng == nil || !a.mode.Streaming() {
		return
	}
	level := int(a.volumeLocked())
	muted := a.s.HeadphonesMuted
	switch action {
	case idVolDown:
		level = max(0, level-6)
	case idVolUp:
		level = min(127, level+6)
		muted = false
	case idVolMute:
		muted = !muted
	}
	value := uint8(level)
	if err := a.eng.in.Write(ipc.Command{Cmd: "volume", Volume: value, On: muted}); err != nil {
		logf("headphone volume: %v", err)
		return
	}
	a.s.HeadphonesVolume, a.s.HeadphonesMuted = &value, muted
	_ = config.Save(a.s)
}
