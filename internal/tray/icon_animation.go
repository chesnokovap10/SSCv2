package tray

import "time"

const (
	volumePulseMsg   = wmApp + 7
	volumePulseTimer = 3
	volumePulseStep  = 36 * time.Millisecond
)

// One short rise and fall, expressed as a percentage blend with white.
var volumePulseFrames = [...]uint32{0, 18, 34, 24, 13, 5}

func volumePulseColor(color Color, frame int) Color {
	strength := volumePulseFrames[frame]
	blend := func(channel uint32) uint32 {
		return channel + (255-channel)*strength/100
	}
	c := uint32(color)
	return Color(blend(c>>16&255)<<16 | blend(c>>8&255)<<8 | blend(c&255))
}

func (t *Tray) PulseVolume() { t.postMenuMessage(volumePulseMsg, 1) }

func (t *Tray) StopVolumePulse() { t.postMenuMessage(volumePulseMsg, 0) }

func (t *Tray) startVolumePulse(start bool) {
	if start {
		t.pulseStarted = time.Now()
		t.setPulseFrame(1)
		setTimer.Call(t.hwnd, volumePulseTimer, uintptr(volumePulseStep/time.Millisecond), 0)
		return
	}
	killTimer.Call(t.hwnd, volumePulseTimer)
	t.pulseStarted = time.Time{}
	t.setPulseFrame(0)
}

func (t *Tray) advanceVolumePulse() {
	if t.pulseStarted.IsZero() {
		return
	}
	frame := 1 + int(time.Since(t.pulseStarted)/volumePulseStep)
	if frame >= len(volumePulseFrames) {
		t.startVolumePulse(false)
		return
	}
	t.setPulseFrame(frame)
}

func (t *Tray) setPulseFrame(frame int) {
	t.mu.Lock()
	changed := t.pulseFrame != frame
	t.pulseFrame = frame
	t.mu.Unlock()
	if changed {
		t.notify(nimModify, nifIcon)
	}
}
