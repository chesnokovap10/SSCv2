package bt

/*
#include "goshim.h"
*/
import "C"

import (
	"sscv2/internal/i18n"

	"fmt"
	"sscv2/internal/logx"
	"sync/atomic"
	"time"
)

var errRejected = i18n.Error("команда отклонена наушниками", "the headphones rejected the command")

func errFromStatus(st uint8) error {
	return fmt.Errorf(i18n.T("статус 0x%02X (%s)", "status 0x%02X (%s)"), st, hciErr(st))
}

// volPump coalesces AVRCP absolute volume commands: a dragged slider makes
// dozens of values per second; only the latest wanted value is kept and it
// is sent when the previous SET_ABSOLUTE_VOLUME is answered (or after 1 s).
type volPump struct {
	desired  atomic.Int32 // -1 = none
	remote   atomic.Uint32
	kick     atomic.Bool
	inFlight bool // BTstack thread only
	// ready: our level (from Windows) was confirmed by the headphones. Until
	// then their own reports (e.g. the interim answer to the notification
	// subscription, often 100 % after reconnect) are not mirrored to Windows.
	ready   bool
	readyAt time.Time
	sent    int
	sentAt  time.Time
}

func (v *volPump) reset() {
	v.inFlight = false
	v.sent = -1
	v.ready = false
}

func (v *volPump) isEcho(vol uint8) bool {
	return v.inFlight || int(vol) == v.sent || time.Since(v.sentAt) < 1500*time.Millisecond
}

// BTstack thread.
func (v *volPump) pump(s *stackT) {
	if s.avrcpCid == 0 {
		return
	}
	want := int(v.desired.Load())
	if want < 0 || want == v.sent {
		return
	}
	if v.inFlight && time.Since(v.sentAt) < time.Second {
		return
	}
	if C.avrcp_controller_set_absolute_volume(C.uint16_t(s.avrcpCid), C.uint8_t(want)) == 0 {
		logx.Dbgf("vol", "AVRCP SetAbsoluteVolume %d/127 sent (ready=%v)", want, v.ready)
		if !v.ready {
			s.logf("volume: sending Windows level %d/127 to the headphones", want)
		}
		v.inFlight = true
		v.sent = want
		v.sentAt = time.Now()
		return
	}
	C.ssc_timer_set(timerVolRetry, 150) // AVRCP busy: retry shortly
}

func init() {
	stack.vol.desired.Store(-1)
	stack.vol.sent = -1
}

// SetVolume sets the headphones' absolute volume (0..127). Returns false
// while AVRCP is not connected (the value is still remembered and sent
// once it is).
func SetVolume(vol uint8) bool {
	if vol > 127 {
		vol = 127
	}
	s := stack
	s.vol.desired.Store(int32(vol))
	s.vol.remote.Store(uint32(vol))
	if !s.loopRunning.Load() {
		return false
	}
	if !s.vol.kick.Swap(true) {
		s.call(func() {
			s.vol.kick.Store(false)
			s.vol.pump(s)
		})
	}
	return s.avrcpUp.Load()
}

// Volume is the last known headphone volume (0..127).
func Volume() uint8 { return uint8(stack.vol.remote.Load()) }

// AVRCPConnected reports whether volume control is available.
func AVRCPConnected() bool { return stack.avrcpUp.Load() }

var lastPlayStatus atomic.Int32 // 0 unknown, 1 playing, 2 paused

// SetPlaying tells the headphones whether something is playing (AVRCP play
// status), so a tap sends PAUSE while playing and PLAY while paused.
func SetPlaying(playing bool) {
	s := stack
	if !s.loopRunning.Load() || !s.avrcpUp.Load() {
		lastPlayStatus.Store(0)
		return
	}
	want := int32(2)
	if playing {
		want = 1
	}
	if lastPlayStatus.Swap(want) == want {
		return
	}
	s.call(func() {
		if s.avrcpCid == 0 {
			return
		}
		st := C.avrcp_playback_status_t(C.AVRCP_PLAYBACK_STATUS_PAUSED)
		if playing {
			st = C.AVRCP_PLAYBACK_STATUS_PLAYING
		}
		C.avrcp_target_set_playback_status(C.uint16_t(s.avrcpCid), st)
	})
}
