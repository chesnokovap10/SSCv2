package bt

/*
#include "goshim.h"
*/
import "C"

import (
	"strings"
	"sync/atomic"
	"time"
	"unsafe"

	"sscv2/internal/battery"
)

type budsBattery struct {
	// Only the BTstack thread touches the probe state.
	peer      Addr
	next      time.Time
	querying  bool
	channel   uint8
	cid       C.uint16_t
	open      bool
	cancelled bool
	decoder   battery.BudsDecoder
	removal   battery.BudsRemoval
	lastPause time.Time
	pendingEQ *uint8
	equalizer battery.BudsEqualizerState

	sample atomic.Pointer[budsSample]
}

type budsSample struct {
	peer      string
	level     battery.BudsLevel
	at        time.Time
	equalizer *uint8
}

// PollBudsStatus returns the latest report and ensures the status channel
// is open on the existing headphone connection.
func PollBudsStatus(address, name string) (*battery.BudsLevel, *uint8) {
	s := stack
	if !s.loopRunning.Load() || !s.connected.Load() || !battery.IsBuds(name) {
		return nil, nil
	}
	if s.streaming.Load() {
		s.call(func() {
			if s.streaming.Load() && s.hasRemote && strings.EqualFold(address, s.remote.String()) {
				s.openBudsStatus()
			}
		})
	}
	if sample := s.buds.sample.Load(); sample != nil && strings.EqualFold(sample.peer, address) {
		if time.Since(sample.at) < battery.MaxAge && sample.level.Known() {
			return &sample.level, sample.equalizer
		}
		return nil, sample.equalizer
	}
	return nil, nil
}

func SetBudsEqualizer(address string, preset uint8) {
	if preset >= battery.BudsEqualizerCount {
		return
	}
	s := stack
	s.call(func() {
		b := &s.buds
		if b.open && strings.EqualFold(b.peer.String(), address) {
			b.pendingEQ = &preset
			C.rfcomm_request_can_send_now_event(b.cid)
		}
	})
}

func (s *stackT) openBudsStatus() {
	b := &s.buds
	now := time.Now()
	if b.querying || b.cid != 0 || s.inquiring || (b.peer == s.remote && now.Before(b.next)) {
		return
	}
	b.peer, b.next = s.remote, now.Add(5*time.Second)
	b.querying, b.cancelled = true, false
	b.channel = 0
	peer := b.peer
	if C.ssc_buds_query((*C.uint8_t)(unsafe.Pointer(&peer[0]))) != 0 {
		b.querying = false
		b.next = now.Add(5 * time.Second) // SDP is shared with the audio profiles.
		return
	}
	C.ssc_timer_set(timerBudsRead, 8000)
}

func (s *stackT) closeBudsProbe() {
	b := &s.buds
	b.cancelled = true
	b.decoder = battery.BudsDecoder{}
	b.removal = battery.BudsRemoval{}
	b.lastPause = time.Time{}
	b.pendingEQ = nil
	b.equalizer = battery.BudsEqualizerState{}
	b.sample.Store(nil)
	C.ssc_timer_stop(timerBudsRead)
	C.ssc_timer_stop(timerBudsRemoval)
	if b.open {
		b.open = false
		C.rfcomm_disconnect(b.cid)
	}
}

func (s *stackT) clearBudsBattery() {
	s.closeBudsProbe()
	s.buds.sample.Store(nil)
	s.buds.next = time.Time{}
}

func (s *stackT) onBudsPacket(kind uint8, channel uint16, packet []byte, p *C.uint8_t) {
	b := &s.buds
	if kind == C.RFCOMM_DATA_PACKET && b.open && b.cid == C.uint16_t(channel) {
		b.decoder.FeedStatus(packet, func(status battery.BudsStatus) {
			now := time.Now()
			sample := budsSample{peer: b.peer.String()}
			if previous := b.sample.Load(); previous != nil {
				sample = *previous
			}
			if status.Level.Known() {
				sample.level, sample.at = status.Level, now
			}
			eq := b.equalizer.Observe(status, now)
			if eq != nil {
				sample.equalizer = eq
			}
			b.sample.Store(&sample)
			if eq != nil {
				s.emit(Event{Kind: EvBudsEqualizer, Addr: b.peer})
			}
			if status.EqualizerAck {
				return
			}
			C.ssc_timer_stop(timerBudsRead)
			previous := b.removal.Deadline()
			next := b.removal.Observe(status.Placement, now)
			if next != previous {
				if next.IsZero() {
					C.ssc_timer_stop(timerBudsRemoval)
				} else {
					C.ssc_timer_set(timerBudsRemoval, C.uint32_t(battery.BudsRemovalDelay.Milliseconds()))
				}
			}
		})
		return
	}
	if kind != C.HCI_EVENT_PACKET || len(packet) < 2 {
		return
	}
	switch packet[0] {
	case C.SDP_EVENT_QUERY_RFCOMM_SERVICE:
		b.channel = uint8(C.sdp_event_query_rfcomm_service_get_rfcomm_channel(p))
	case C.SDP_EVENT_QUERY_COMPLETE:
		b.querying = false
		if b.cancelled || b.channel == 0 || C.sdp_event_query_complete_get_status(p) != 0 {
			s.closeBudsProbe()
			return
		}
		peer := b.peer
		var cid C.uint16_t
		if C.ssc_buds_open((*C.uint8_t)(unsafe.Pointer(&peer[0])), C.uint8_t(b.channel), &cid) != 0 {
			s.closeBudsProbe()
			return
		}
		b.cid = cid
	case C.RFCOMM_EVENT_CHANNEL_OPENED:
		if C.rfcomm_event_channel_opened_get_rfcomm_cid(p) != b.cid {
			return
		}
		if C.rfcomm_event_channel_opened_get_status(p) != 0 {
			b.cid = 0
			s.closeBudsProbe()
			return
		}
		b.open = true
		if b.cancelled {
			s.closeBudsProbe()
			return
		}
		C.ssc_timer_set(timerBudsRead, 3000)
		C.rfcomm_request_can_send_now_event(b.cid)
	case C.RFCOMM_EVENT_CAN_SEND_NOW:
		if b.open && C.rfcomm_event_can_send_now_get_rfcomm_cid(p) == b.cid {
			if preset := b.pendingEQ; preset != nil {
				b.pendingEQ = nil
				frame := battery.BudsEqualizerRequest(*preset)
				if code := C.rfcomm_send(b.cid, (*C.uint8_t)(unsafe.Pointer(&frame[0])), C.uint16_t(len(frame))); code != 0 {
					s.logf("Buds equalizer send failed: %#x", code)
				}
			} else {
				query := battery.ManagerInfo()
				C.rfcomm_send(b.cid, (*C.uint8_t)(unsafe.Pointer(&query[0])), C.uint16_t(len(query)))
			}
		}
	case C.RFCOMM_EVENT_CHANNEL_CLOSED:
		if C.rfcomm_event_channel_closed_get_rfcomm_cid(p) == b.cid {
			b.cid, b.open = 0, false
			s.closeBudsProbe()
		}
	}
}

// BudsEqualizer returns the latest accepted device value for address.
func BudsEqualizer(address string) *uint8 {
	if sample := stack.buds.sample.Load(); sample != nil && strings.EqualFold(sample.peer, address) {
		return sample.equalizer
	}
	return nil
}

func (s *stackT) confirmBudsRemoval() {
	b := &s.buds
	now := time.Now()
	if remaining := b.removal.Deadline().Sub(now); remaining > 0 {
		C.ssc_timer_set(timerBudsRemoval, C.uint32_t(remaining.Milliseconds()+1))
		return
	}
	if b.open && b.removal.Confirm(now) && s.streaming.Load() && now.Sub(b.lastPause) >= 2*time.Second {
		s.emit(Event{Kind: EvBudsRemoved, Addr: b.peer})
	}
}
