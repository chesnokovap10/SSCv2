package bt

/*
#include "goshim.h"
*/
import "C"

import (
	"sync/atomic"
	"unsafe"

	"golang.org/x/sys/windows"
)

// The BLE mouse bridge. While the adapter belongs to BTstack, Windows has
// no Bluetooth, so a BLE mouse paired with Windows would be dead. BTstack
// becomes the mouse's host: it reconnects as LE central with the bonding
// keys imported from Windows, reads HID input reports over GATT and replays
// them with SendInput. A fresh pairing is declined: it would replace the
// bond the mouse shares with Windows (same host address).

type mouseState int32

const (
	mouseOff mouseState = iota
	mouseConnecting
	mouseEncrypting
	mouseDiscovering
	mouseReady
)

func (m mouseState) String() string {
	switch m {
	case mouseConnecting:
		return "ожидание мыши"
	case mouseEncrypting:
		return "шифрование"
	case mouseDiscovering:
		return "поиск HID"
	case mouseReady:
		return "работает"
	}
	return "выкл"
}

type mouseBridge struct {
	configured bool
	addr       Addr
	addrType   C.bd_addr_type_t
	state      atomic.Int32
	handle     uint16
	hidsCid    uint16
	buttons    uint32
	reports    atomic.Uint32
	raw        atomic.Uint32
}

// MouseStatus returns (configured, state text, reports this session).
func MouseStatus() (bool, string, uint32) {
	m := &stack.mouse
	return m.configured, mouseState(m.state.Load()).String(), m.reports.Load()
}

func (m *mouseBridge) set(s *stackT, st mouseState) {
	if mouseState(m.state.Swap(int32(st))) != st {
		s.emit(Event{Kind: EvMouse, Addr: m.addr, Mouse: st.String()})
	}
}

// BTstack thread, before power-on.
func (m *mouseBridge) setup(s *stackT, b *LEBond) {
	C.ssc_hog_init()
	m.addr = b.Addr
	m.addrType = C.BD_ADDR_TYPE_LE_PUBLIC
	if b.Random {
		m.addrType = C.BD_ADDR_TYPE_LE_RANDOM
	}
	ks := b.KeySize
	if ks < 7 || ks > 16 {
		ks = 16
	}
	sc := C.int(0)
	if b.SecureConn {
		sc = 1
	}
	a, irk, ltk, rnd := b.Addr, b.IRK, b.LTK, b.Rand
	idx := C.ssc_le_add_bond(C.int(m.addrType), (*C.uint8_t)(&a[0]), (*C.uint8_t)(&irk[0]),
		(*C.uint8_t)(&ltk[0]), C.uint16_t(b.EDIV), (*C.uint8_t)(&rnd[0]), C.int(ks), sc)
	if idx < 0 {
		s.logf("mouse: LE device DB full")
		return
	}
	m.configured = true
	m.handle = 0xFFFF
	kind := "legacy"
	if b.SecureConn {
		kind = "LE Secure Connections"
	}
	s.logf("mouse: %s, %s keys loaded", b.Addr, kind)
}

func (m *mouseBridge) onHCIWorking(s *stackT) {
	if m.configured {
		m.connect(s)
	}
}

func (m *mouseBridge) connect(s *stackT) {
	if !m.configured || !s.hciReady.Load() || m.handle != 0xFFFF {
		return
	}
	m.set(s, mouseConnecting)
	a := m.addr
	st := uint8(C.gap_connect((*C.uint8_t)(&a[0]), m.addrType))
	if st != 0 && st != C.ERROR_CODE_COMMAND_DISALLOWED {
		s.logf("mouse: gap_connect failed (0x%02X)", st)
		C.ssc_timer_set(timerMouseRetry, 2000)
		return
	}
	s.logf("mouse: waiting for %s to advertise", m.addr)
}

func (m *mouseBridge) onGapMeta(s *stackT, cp *C.uint8_t) {
	if !m.configured || uint8(C.hci_event_gap_meta_get_subevent_code(cp)) != C.GAP_SUBEVENT_LE_CONNECTION_COMPLETE {
		return
	}
	var peer C.bd_addr_t
	C.gap_subevent_le_connection_complete_get_peer_address(cp, &peer[0])
	if addrFromC(&peer[0]) != m.addr {
		return
	}
	if st := uint8(C.gap_subevent_le_connection_complete_get_status(cp)); st != 0 {
		s.logf("mouse: LE connection failed (0x%02X), retrying", st)
		C.ssc_timer_set(timerMouseRetry, 1000)
		return
	}
	m.handle = uint16(C.gap_subevent_le_connection_complete_get_connection_handle(cp))
	m.set(s, mouseEncrypting)
	s.logf("mouse: connected (handle 0x%04X), encrypting", m.handle)
	C.sm_request_pairing(C.hci_con_handle_t(m.handle))
}

// onDisconnect returns true when the handle was the mouse's.
func (m *mouseBridge) onDisconnect(s *stackT, h uint16, reason uint8) bool {
	if !m.configured || h != m.handle {
		return false
	}
	s.logf("mouse: disconnected (0x%02X), %d reports", reason, m.reports.Load())
	m.releaseButtons()
	m.handle = 0xFFFF
	m.hidsCid = 0
	m.reports.Store(0)
	m.set(s, mouseOff)
	C.ssc_timer_set(timerMouseRetry, 300)
	return true
}

func (m *mouseBridge) connectHIDS(s *stackT) {
	m.set(s, mouseDiscovering)
	var cid C.uint16_t
	if st := C.ssc_hids_connect(C.uint16_t(m.handle), &cid); st != 0 {
		s.logf("mouse: hids_host_connect failed (0x%02X)", uint8(st))
		return
	}
	m.hidsCid = uint16(cid)
}

func (m *mouseBridge) onSM(s *stackT, cp *C.uint8_t) {
	if !m.configured {
		return
	}
	switch uint8(C.hci_event_packet_get_type(cp)) {
	case C.SM_EVENT_JUST_WORKS_REQUEST, C.SM_EVENT_NUMERIC_COMPARISON_REQUEST:
		h := C.sm_event_just_works_request_get_handle(cp)
		s.logf("mouse: new pairing requested - declined to keep the Windows bond intact")
		C.sm_bonding_decline(h)
	case C.SM_EVENT_REENCRYPTION_COMPLETE:
		if uint16(C.sm_event_reencryption_complete_get_handle(cp)) != m.handle {
			return
		}
		if st := uint8(C.sm_event_reencryption_complete_get_status(cp)); st == 0 {
			s.logf("mouse: link encrypted with imported key")
			m.connectHIDS(s)
		} else {
			s.logf("mouse: re-encryption failed (0x%02X) - imported key not accepted", st)
		}
	case C.SM_EVENT_PAIRING_COMPLETE:
		if uint16(C.sm_event_pairing_complete_get_handle(cp)) != m.handle {
			return
		}
		st := uint8(C.sm_event_pairing_complete_get_status(cp))
		s.logf("mouse: pairing complete, status 0x%02X", st)
		if st == 0 {
			m.connectHIDS(s)
		}
	}
}

func (m *mouseBridge) onHIDS(s *stackT, cp *C.uint8_t) {
	if uint8(C.hci_event_packet_get_type(cp)) != C.HCI_EVENT_GATTSERVICE_META {
		return
	}
	switch uint8(C.hci_event_gattservice_meta_get_subevent_code(cp)) {
	case C.GATTSERVICE_SUBEVENT_HID_SERVICE_CONNECTED:
		if st := uint8(C.gattservice_subevent_hid_service_connected_get_status(cp)); st == 0 {
			m.set(s, mouseReady)
			s.logf("mouse: HID service ready (%d instance(s), descriptor %d bytes)",
				int(C.gattservice_subevent_hid_service_connected_get_num_instances(cp)),
				int(C.hids_host_descriptor_storage_get_descriptor_len(C.uint16_t(m.hidsCid), 0)))
		} else {
			s.logf("mouse: HID discovery failed (0x%02X), disconnecting", st)
			C.gap_disconnect(C.hci_con_handle_t(m.handle))
		}
	case C.GATTSERVICE_SUBEVENT_HID_SERVICE_DISCONNECTED:
		s.logf("mouse: HID service disconnected")
	case C.GATTSERVICE_SUBEVENT_HID_REPORT:
		idx := C.gattservice_subevent_hid_report_get_service_index(cp)
		rep := C.gattservice_subevent_hid_report_get_report(cp)
		n := C.gattservice_subevent_hid_report_get_report_len(cp)
		var dx, dy, wh, hw C.int32_t
		var btn C.uint32_t
		ok := C.ssc_hog_parse(C.uint16_t(m.hidsCid), idx, rep, n, C.uint32_t(m.buttons),
			&dx, &dy, &wh, &hw, &btn)
		if m.raw.Add(1) <= 8 {
			b := unsafe.Slice((*byte)(unsafe.Pointer(rep)), int(n))
			s.logf("mouse: report #%d svc=%d len=%d % X -> mouse=%d dx=%d dy=%d btn=%d desc=%d",
				m.raw.Load(), int(idx), int(n), b, int(ok), int(dx), int(dy), int(btn),
				int(C.hids_host_descriptor_storage_get_descriptor_len(C.uint16_t(m.hidsCid), idx)))
		}
		if ok == 0 {
			return
		}
		if m.reports.Add(1) == 1 {
			s.logf("mouse: first input report - mouse is live")
		}
		m.send(int32(dx), int32(dy), int32(wh), int32(hw), uint32(btn))
	}
}

// ---- Windows input -----------------------------------------------------------

var (
	user32        = windows.NewLazySystemDLL("user32.dll")
	procSendInput = user32.NewProc("SendInput")
)

const (
	inputMouse          = 0
	mouseeventfMove     = 0x0001
	mouseeventfLeftDown = 0x0002
	mouseeventfLeftUp   = 0x0004
	mouseeventfRightDn  = 0x0008
	mouseeventfRightUp  = 0x0010
	mouseeventfMidDown  = 0x0020
	mouseeventfMidUp    = 0x0040
	mouseeventfXDown    = 0x0080
	mouseeventfXUp      = 0x0100
	mouseeventfWheel    = 0x0800
	mouseeventfHWheel   = 0x1000
	wheelDelta          = 120
)

// INPUT for x64: type(4) + pad(4) + MOUSEINPUT(32).
type mouseInput struct {
	typ       uint32
	_         uint32
	dx, dy    int32
	mouseData uint32
	flags     uint32
	time      uint32
	_         uint32
	extra     uintptr
}

func (m *mouseBridge) send(dx, dy, wheel, hwheel int32, buttons uint32) {
	var in [8]mouseInput
	n := 0
	add := func(flags uint32, x, y int32, data uint32) {
		in[n] = mouseInput{typ: inputMouse, dx: x, dy: y, mouseData: data, flags: flags}
		n++
	}
	if dx != 0 || dy != 0 {
		add(mouseeventfMove, dx, dy, 0)
	}
	btn := [5]struct{ down, up, data uint32 }{
		{mouseeventfLeftDown, mouseeventfLeftUp, 0},
		{mouseeventfRightDn, mouseeventfRightUp, 0},
		{mouseeventfMidDown, mouseeventfMidUp, 0},
		{mouseeventfXDown, mouseeventfXUp, 1},
		{mouseeventfXDown, mouseeventfXUp, 2},
	}
	changed := buttons ^ m.buttons
	for b := 0; b < 5; b++ {
		if changed&(1<<b) == 0 {
			continue
		}
		if buttons&(1<<b) != 0 {
			add(btn[b].down, 0, 0, btn[b].data)
		} else {
			add(btn[b].up, 0, 0, btn[b].data)
		}
	}
	m.buttons = buttons
	if wheel != 0 {
		add(mouseeventfWheel, 0, 0, uint32(wheel*wheelDelta))
	}
	if hwheel != 0 {
		add(mouseeventfHWheel, 0, 0, uint32(hwheel*wheelDelta))
	}
	if n > 0 {
		procSendInput.Call(uintptr(n), uintptr(unsafe.Pointer(&in[0])), unsafe.Sizeof(in[0]))
	}
}

func (m *mouseBridge) releaseButtons() {
	if m.buttons != 0 {
		m.send(0, 0, 0, 0, 0)
	}
}
