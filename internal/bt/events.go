package bt

/*
#include "goshim.h"
*/
import "C"

import (
	"time"
	"unsafe"
)

func hciErr(code uint8) string {
	switch code {
	case 0x00:
		return "Success"
	case 0x02:
		return "Unknown Connection Identifier"
	case 0x04:
		return "Page Timeout"
	case 0x05:
		return "Authentication Failure"
	case 0x06:
		return "PIN or Key Missing"
	case 0x08:
		return "Connection Timeout"
	case 0x0B:
		return "ACL Connection Already Exists"
	case 0x0C:
		return "Command Disallowed"
	case 0x0E:
		return "Rejected (Security)"
	case 0x10:
		return "Accept Timeout"
	case 0x13:
		return "Remote User Terminated"
	case 0x16:
		return "Local Host Terminated"
	case 0x22:
		return "LMP/LL Response Timeout"
	}
	return "?"
}

// onPacket runs on the BTstack thread for every event.
func (s *stackT) onPacket(src int, ptype uint8, channel uint16, p []byte, cp *C.uint8_t) {
	if len(p) < 2 {
		return
	}
	// hids_host delivers HID reports with packet_type set to
	// HCI_EVENT_GATTSERVICE_META, not HCI_EVENT_PACKET: don't filter them.
	if src == C.SSC_SRC_HIDS {
		s.mouse.onHIDS(s, cp)
		return
	}
	if ptype != C.HCI_EVENT_PACKET {
		return
	}
	if src == C.SSC_SRC_SM {
		s.mouse.onSM(s, cp)
		return
	}
	ev := uint8(C.hci_event_packet_get_type(cp))
	switch ev {
	case C.BTSTACK_EVENT_STATE:
		st := uint8(C.btstack_event_state_get_state(cp))
		if st == C.HCI_STATE_WORKING {
			s.logf("bt: HCI working after %s", time.Since(s.initTick).Round(time.Millisecond))
			var a C.bd_addr_t
			C.gap_local_bd_addr(&a[0])
			s.localAddr = addrFromC(&a[0])
			s.hciReady.Store(true)
			select {
			case <-s.initCh:
			default:
				close(s.initCh)
			}
			s.mouse.onHCIWorking(s)
		} else if st == C.HCI_STATE_OFF {
			s.logf("bt: HCI off")
			s.hciReady.Store(false)
			select {
			case <-s.offCh:
			default:
				close(s.offCh)
			}
		}

	case C.HCI_EVENT_USER_CONFIRMATION_REQUEST:
		var a C.bd_addr_t
		C.hci_event_user_confirmation_request_get_bd_addr(cp, &a[0])
		s.logf("bt: pairing with %s (Just Works, accepted)", addrFromC(&a[0]))
		C.gap_ssp_confirmation_response(&a[0])

	case C.HCI_EVENT_PIN_CODE_REQUEST:
		var a C.bd_addr_t
		C.hci_event_pin_code_request_get_bd_addr(cp, &a[0])
		pin := C.CString("0000")
		C.gap_pin_code_response(&a[0], pin)
		C.free(unsafe.Pointer(pin))

	case C.HCI_EVENT_CONNECTION_COMPLETE:
		var a C.bd_addr_t
		C.hci_event_connection_complete_get_bd_addr(cp, &a[0])
		st := uint8(C.hci_event_connection_complete_get_status(cp))
		if st != 0 {
			s.logf("bt: ACL to %s failed: 0x%02X (%s)", addrFromC(&a[0]), st, hciErr(st))
		} else {
			s.aclHandle.Store(uint32(C.hci_event_connection_complete_get_connection_handle(cp)))
			s.logf("bt: ACL up to %s", addrFromC(&a[0]))
			s.emit(Event{Kind: EvACLUp, Addr: addrFromC(&a[0])})
		}

	case C.GAP_EVENT_INQUIRY_RESULT:
		var a C.bd_addr_t
		C.gap_event_inquiry_result_get_bd_addr(cp, &a[0])
		f := Found{
			Addr: addrFromC(&a[0]),
			CoD:  uint32(C.gap_event_inquiry_result_get_class_of_device(cp)),
			RSSI: int8(C.gap_event_inquiry_result_get_rssi(cp)),
		}
		if C.gap_event_inquiry_result_get_name_available(cp) != 0 {
			n := int(C.gap_event_inquiry_result_get_name_len(cp))
			f.Name = string(unsafe.Slice((*byte)(unsafe.Pointer(C.gap_event_inquiry_result_get_name(cp))), n))
		}
		if s.inquiring {
			dup := false
			for i := range s.found {
				if s.found[i].Addr == f.Addr {
					if f.Name != "" {
						s.found[i].Name = f.Name
					}
					dup = true
				}
			}
			if !dup {
				s.found = append(s.found, f)
			}
		}

	case C.GAP_EVENT_INQUIRY_COMPLETE:
		s.inquiring = false
		sig(s.inquiryCh, nil)

	case C.HCI_EVENT_DISCONNECTION_COMPLETE:
		h := uint32(C.hci_event_disconnection_complete_get_connection_handle(cp))
		reason := uint8(C.hci_event_disconnection_complete_get_reason(cp))
		if s.mouse.onDisconnect(s, uint16(h), reason) {
			return
		}
		if h != s.aclHandle.Load() {
			return
		}
		s.logf("bt: headphones link down (0x%02X %s)", reason, hciErr(reason))
		s.aclHandle.Store(0xFFFF)
		if s.connected.Load() || s.streaming.Load() {
			s.streaming.Store(false)
			s.connected.Store(false)
			s.resetMedia()
			s.emit(Event{Kind: EvDisconnected, Addr: s.remote})
		}
		// a failed connect never reaches CAPABILITIES_COMPLETE
		sig(s.connectCh, ErrTimeout)

	case C.HCI_EVENT_META_GAP:
		s.mouse.onGapMeta(s, cp)

	case C.HCI_EVENT_A2DP_META:
		s.onA2DP(cp, p)

	case C.HCI_EVENT_AVRCP_META:
		s.onAVRCP(cp, p)
	}
}

func (s *stackT) onA2DP(cp *C.uint8_t, p []byte) {
	switch uint8(C.hci_event_a2dp_meta_get_subevent_code(cp)) {
	case C.A2DP_SUBEVENT_SIGNALING_CONNECTION_ESTABLISHED:
		st := uint8(C.a2dp_subevent_signaling_connection_established_get_status(cp))
		s.a2dpCid = uint16(C.a2dp_subevent_signaling_connection_established_get_a2dp_cid(cp))
		if st != 0 {
			s.logf("bt: A2DP signalling failed (0x%02X %s)", st, hciErr(st))
			sig(s.connectCh, errFromStatus(st))
		} else {
			var a C.bd_addr_t
			C.a2dp_subevent_signaling_connection_established_get_bd_addr(cp, &a[0])
			if !s.hasRemote || s.remote != addrFromC(&a[0]) {
				s.caps = RemoteCaps{} // incoming connection from the headphones
			}
			s.remote, s.hasRemote = addrFromC(&a[0]), true
			s.logf("bt: A2DP signalling up with %s (cid 0x%04X)", s.remote, s.a2dpCid)
		}

	case C.A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CAPABILITY:
		seid := uint8(C.a2dp_subevent_signaling_media_codec_other_capability_get_remote_seid(cp))
		n := int(C.a2dp_subevent_signaling_media_codec_other_capability_get_media_codec_information_len(cp))
		info := unsafe.Slice((*byte)(unsafe.Pointer(C.a2dp_subevent_signaling_media_codec_other_capability_get_media_codec_information(cp))), n)
		if n >= 6 {
			vid := uint32(info[0]) | uint32(info[1])<<8 | uint32(info[2])<<16 | uint32(info[3])<<24
			codec := uint16(info[4]) | uint16(info[5])<<8
			if vid == C.SSC_VENDOR_ID && codec == C.SSC_CODEC_ID {
				s.caps.SSC, s.caps.SSCSeid = true, seid
				if n >= 7 {
					s.caps.SSCCap = info[6]
					s.caps.SSCUHQ = info[6]&0x02 != 0
				}
				s.logf("bt: sink supports SSC (seid %d cap 0x%02X)", seid, s.caps.SSCCap)
			}
		}

	case C.A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION:
		n := int(C.a2dp_subevent_signaling_media_codec_other_configuration_get_media_codec_information_len(cp))
		info := unsafe.Slice((*byte)(unsafe.Pointer(C.a2dp_subevent_signaling_media_codec_other_configuration_get_media_codec_information(cp))), n)
		if n >= 7 {
			vid := uint32(info[0]) | uint32(info[1])<<8 | uint32(info[2])<<16 | uint32(info[3])<<24
			codec := uint16(info[4]) | uint16(info[5])<<8
			if vid == C.SSC_VENDOR_ID && codec == C.SSC_CODEC_ID {
				s.sscCfg.Store(uint32(info[6]))
				s.logf("bt: SSC configured, cap 0x%02X", info[6])
			}
		}

	case C.A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY:
		s.caps.SBC = true
		s.caps.SBCSeid = uint8(C.a2dp_subevent_signaling_media_codec_sbc_capability_get_remote_seid(cp))

	case C.A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_MPEG_AAC_CAPABILITY:
		s.caps.AAC = true
		s.caps.AACSeid = uint8(C.a2dp_subevent_signaling_media_codec_mpeg_aac_capability_get_remote_seid(cp))
		s.caps.AACBitrate = uint32(C.a2dp_subevent_signaling_media_codec_mpeg_aac_capability_get_bit_rate(cp))
		s.logf("bt: sink supports AAC (seid %d, max %d bps)", s.caps.AACSeid, s.caps.AACBitrate)

	case C.A2DP_SUBEVENT_SIGNALING_CAPABILITIES_COMPLETE:
		s.logf("bt: codecs SBC=%v AAC=%v SSC=%v", s.caps.SBC, s.caps.AAC, s.caps.SSC)
		s.connected.Store(true)
		sig(s.connectCh, nil)
		s.emit(Event{Kind: EvA2DPReady, Addr: s.remote})
		// AVRCP for absolute volume.
		if s.hasRemote {
			a := s.remote
			var cid C.uint16_t
			if rc := C.avrcp_connect((*C.uint8_t)(unsafe.Pointer(&a[0])), &cid); rc != 0 {
				s.logf("bt: AVRCP connect failed (0x%02X)", uint8(rc))
			}
		}

	case C.A2DP_SUBEVENT_STREAM_ESTABLISHED:
		st := uint8(C.a2dp_subevent_stream_established_get_status(cp))
		if st != 0 {
			s.logf("bt: stream setup failed (0x%02X)", st)
			sig(s.streamCh, errFromStatus(st))
			s.streamCh = nil
			return
		}
		s.localSeid = uint8(C.a2dp_subevent_stream_established_get_local_seid(cp))
		s.remoteSeid = uint8(C.a2dp_subevent_stream_established_get_remote_seid(cp))
		if s.opts.ForceMediaMTU > 0 {
			old := int(C.ssc_media_force_mtu(C.uint8_t(s.localSeid), C.uint16_t(s.opts.ForceMediaMTU)))
			s.logf("bt: media MTU %d -> %d (above the headphones' announced limit: max MTU / large SSC frames)", old, s.opts.ForceMediaMTU)
		}
		m := int(C.a2dp_max_media_payload_size(C.uint16_t(s.a2dpCid), C.uint8_t(s.localSeid)))
		if m <= 0 {
			m = 667
		}
		s.mtu.Store(uint32(m))
		s.logf("bt: stream established (local %d remote %d, payload %d)", s.localSeid, s.remoteSeid, m)
		if s.streamCh == nil {
			// Not configured by us: the headphones connected and chose.
			codec := CodecSBC
			switch s.localSeid {
			case s.aacSeid:
				codec = CodecAAC
			case s.sscSeid:
				codec = CodecSSC
			}
			s.logf("bt: the headphones configured %s themselves", codec)
			s.remoteCodec.Store(int32(codec))
			s.remoteCfg.Store(true)
			s.connected.Store(true)
			sig(s.connectCh, nil)
			s.emit(Event{Kind: EvA2DPReady, Addr: s.remote})
		}
		sig(s.streamCh, nil)
		s.streamCh = nil

	case C.A2DP_SUBEVENT_STREAM_STARTED:
		s.logf("bt: streaming started")
		s.streaming.Store(true)
		sig(s.startCh, nil)
		C.a2dp_source_stream_endpoint_request_can_send_now(C.uint16_t(s.a2dpCid), C.uint8_t(s.localSeid))

	case C.A2DP_SUBEVENT_STREAMING_CAN_SEND_MEDIA_PACKET_NOW:
		s.canSendNow()

	case C.A2DP_SUBEVENT_STREAM_SUSPENDED:
		s.logf("bt: stream suspended")
		s.streaming.Store(false)

	case C.A2DP_SUBEVENT_STREAM_RELEASED:
		s.logf("bt: stream released")
		s.streaming.Store(false)

	case C.A2DP_SUBEVENT_SIGNALING_CONNECTION_RELEASED:
		s.logf("bt: A2DP signalling released")
		wasUp := s.connected.Load() || s.streaming.Load()
		s.connected.Store(false)
		s.streaming.Store(false)
		s.sscCfg.Store(0)
		s.resetMedia()
		s.a2dpCid = 0
		if s.avrcpCid != 0 {
			C.avrcp_disconnect(C.uint16_t(s.avrcpCid))
			s.avrcpCid = 0
			s.avrcpUp.Store(false)
		}
		sig(s.discCh, nil)
		sig(s.connectCh, ErrTimeout)
		s.streamCh = nil
		s.remoteCfg.Store(false)
		if wasUp {
			s.emit(Event{Kind: EvDisconnected, Addr: s.remote})
		}

	case C.A2DP_SUBEVENT_COMMAND_REJECTED:
		s.logf("bt: A2DP command rejected")
		sig(s.streamCh, errRejected)
		sig(s.startCh, errRejected)
	}
}

func (s *stackT) onAVRCP(cp *C.uint8_t, p []byte) {
	if len(p) < 3 {
		return
	}
	switch p[2] {
	case C.AVRCP_SUBEVENT_CONNECTION_ESTABLISHED:
		st := uint8(C.avrcp_subevent_connection_established_get_status(cp))
		cid := uint16(C.avrcp_subevent_connection_established_get_avrcp_cid(cp))
		if st != 0 {
			s.logf("bt: AVRCP failed (0x%02X)", st)
			return
		}
		s.avrcpCid = cid
		s.avrcpUp.Store(true)
		s.vol.reset()
		C.ssc_timer_set(timerVolReady, 5000)
		s.logf("bt: AVRCP up (cid 0x%04X)", cid)
		C.avrcp_controller_enable_notification(C.uint16_t(cid), C.AVRCP_NOTIFICATION_EVENT_VOLUME_CHANGED)
		s.emit(Event{Kind: EvAVRCPConnected, Addr: s.remote})
		s.vol.pump(s)

	case C.AVRCP_SUBEVENT_CONNECTION_RELEASED:
		s.logf("bt: AVRCP down")
		s.avrcpCid = 0
		s.avrcpUp.Store(false)
		s.vol.reset()
		C.ssc_timer_stop(timerVolRetry)

	case C.AVRCP_SUBEVENT_NOTIFICATION_VOLUME_CHANGED:
		v := uint8(C.avrcp_subevent_notification_volume_changed_get_absolute_volume(cp))
		switch {
		case !s.vol.ready:
			// the headphones' own level before ours was applied: ignore
			s.logf("volume: headphones report %d/127 before the Windows level was applied - ignored", v)
		case int(v) != s.vol.sent && s.vol.sent >= 0 && time.Since(s.vol.readyAt) < 5*time.Second:
			// Buds jump to their own level (often 100 %) right after
			// accepting ours: Windows stays the source of truth.
			s.logf("volume: headphones jumped to %d/127 right after connect - restoring %d/127", v, s.vol.sent)
			s.vol.sent = -1
			s.vol.inFlight = false
			s.vol.pump(s)
		case s.vol.isEcho(v):
			// echo of our own SET_ABSOLUTE_VOLUME
			s.vol.remote.Store(uint32(v))
		default:
			s.vol.remote.Store(uint32(v))
			s.logf("volume: changed on the headphones to %d/127 -> Windows", v)
			s.emit(Event{Kind: EvVolume, Addr: s.remote, Volume: v})
		}
		C.avrcp_controller_enable_notification(C.uint16_t(s.avrcpCid), C.AVRCP_NOTIFICATION_EVENT_VOLUME_CHANGED)

	case C.AVRCP_SUBEVENT_OPERATION:
		// Taps on the headphones: AVRCP PASS_THROUGH (press + release).
		if C.avrcp_subevent_operation_get_button_pressed(cp) == 0 {
			return
		}
		op := uint8(C.avrcp_subevent_operation_get_operation_id(cp))
		key := map[uint8]int{C.AVRCP_OPERATION_ID_PLAY: MediaPlayPause, C.AVRCP_OPERATION_ID_PAUSE: MediaPlayPause,
			C.AVRCP_OPERATION_ID_FORWARD: MediaNext, C.AVRCP_OPERATION_ID_BACKWARD: MediaPrev,
			C.AVRCP_OPERATION_ID_STOP: MediaStop}[op]
		if key == 0 {
			s.logf("bt: headphones button 0x%02X ignored", op)
			return
		}
		s.logf("bt: headphones button 0x%02X -> media key %d", op, key)
		s.emit(Event{Kind: EvMediaKey, Addr: s.remote, Media: key})

	case C.AVRCP_SUBEVENT_SET_ABSOLUTE_VOLUME_RESPONSE:
		v := uint8(C.avrcp_subevent_set_absolute_volume_response_get_absolute_volume(cp))
		s.vol.inFlight = false
		s.vol.remote.Store(uint32(v))
		if !s.vol.ready {
			s.vol.ready = true
			s.vol.readyAt = time.Now()
			C.ssc_timer_stop(timerVolReady)
			s.logf("volume: headphones confirmed %d/127", v)
		}
		if time.Since(s.vol.readyAt) < 6*time.Second {
			s.emit(Event{Kind: EvVolumeApplied, Addr: s.remote, Volume: v})
		}
		s.vol.pump(s)
	}
}
