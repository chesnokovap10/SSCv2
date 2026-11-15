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

	sample atomic.Pointer[budsSample]
}

type budsSample struct {
	peer  string
	level battery.BudsLevel
	at    time.Time
}

// PollBudsBattery reads the last report and schedules a refresh on the
// existing headphone connection when due.
func PollBudsBattery(address, name string) *battery.BudsLevel {
	s := stack
	if !s.loopRunning.Load() || !s.connected.Load() || !battery.IsBuds(name) {
		return nil
	}
	if s.streaming.Load() {
		s.call(func() {
			if s.streaming.Load() && s.hasRemote && strings.EqualFold(address, s.remote.String()) {
				s.probeBudsBattery()
			}
		})
	}
	if sample := s.buds.sample.Load(); sample != nil && strings.EqualFold(sample.peer, address) &&
		time.Since(sample.at) < battery.MaxAge && sample.level.Known() {
		return &sample.level
	}
	return nil
}

func (s *stackT) probeBudsBattery() {
	b := &s.buds
	now := time.Now()
	if b.querying || b.cid != 0 || s.inquiring || (b.peer == s.remote && now.Before(b.next)) {
		return
	}
	b.peer, b.next = s.remote, now.Add(battery.PollInterval)
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
	C.ssc_timer_stop(timerBudsRead)
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
		var level *battery.BudsLevel
		b.decoder.Feed(packet, func(report battery.BudsLevel) { level = &report })
		if level != nil {
			b.sample.Store(&budsSample{peer: b.peer.String(), level: *level, at: time.Now()})
			s.logf("bt: Buds battery left=%d right=%d", level.Left, level.Right)
			s.closeBudsProbe()
		}
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
			query := battery.ManagerInfo()
			C.rfcomm_send(b.cid, (*C.uint8_t)(unsafe.Pointer(&query[0])), C.uint16_t(len(query)))
		}
	case C.RFCOMM_EVENT_CHANNEL_CLOSED:
		if C.rfcomm_event_channel_closed_get_rfcomm_cid(p) == b.cid {
			b.cid, b.open = 0, false
			s.closeBudsProbe()
		}
	}
}
