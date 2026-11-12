package nativebt

import "sync/atomic"

// Allow a nearby step when the headphones round an absolute volume request.
const budsVolumeStepTolerance = 2

type budsVolume struct {
	wanted   atomic.Int32 // -1 when Windows already applies the level to PCM
	hardware atomic.Bool  // AVRCP volume is working on the current connection
	wake     chan struct{}
}

func newBudsVolume() *budsVolume {
	v := &budsVolume{wake: make(chan struct{}, 1)}
	v.wanted.Store(-1)
	return v
}

func (v *budsVolume) set(level int32) {
	if v.wanted.Swap(level) != level {
		select {
		case v.wake <- struct{}{}:
		default:
		}
	}
}

func (v *budsVolume) target() int32 {
	if level := v.wanted.Load(); level >= 0 {
		return level
	}
	return 127
}

func (v *budsVolume) gain(fallback func() float32) float32 {
	level := v.wanted.Load()
	// Keep one gain stage while AVRCP is healthy. Changing PCM gain while
	// waiting for an acknowledgment would queue doubly attenuated audio.
	if level >= 0 && v.hardware.Load() {
		return 1
	}
	if level == 0 {
		return 0
	}
	return fallback()
}
