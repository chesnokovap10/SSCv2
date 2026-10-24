package bt

/*
#include "goshim.h"
*/
import "C"

import (
	"encoding/binary"
	"fmt"
	"strings"
	"time"

	"sscv2/internal/logx"
)

// Debug journal of everything exchanged with the controller and the
// devices: HCI commands/events, L2CAP signalling, AVDTP, AVRCP (AV/C),
// SDP, ATT, SMP. Audio media packets, completed-packet counts, mouse
// notifications and advertising reports are summarised every 5 s instead
// of logged one by one. Link keys / LTKs are masked.

// SetDebug switches the packet journal on/off (any thread).
func SetDebug(on bool) {
	s := stack
	if !s.loopRunning.Load() {
		s.opts.Debug = on
		return
	}
	s.call(func() { applyDebug(s, on) })
}

func applyDebug(s *stackT, on bool) {
	s.opts.Debug = on
	p, v := C.int(0), C.int(0)
	if on {
		p, v = 1, 1
	}
	if s.opts.Verbose {
		v = 1
	}
	C.ssc_set_debug(p, v)
	s.logf("bt: packet journal %v", on)
}

type chanInfo struct {
	psm  uint16
	kind string
}

type hciDump struct {
	addr    map[uint16]Addr // handle -> remote
	local   map[uint32]chanInfo
	remote  map[uint32]chanInfo
	pending map[uint32]uint16 // requester CID (+dir) -> PSM
	avdtpN  map[uint16]int
	last    map[uint32]string // kind of the last L2CAP start fragment per handle+dir

	// summarised traffic
	since                           time.Time
	mediaOut, mediaBytes, completed int
	notifs, adv, other              int
}

var dump = hciDump{
	addr: map[uint16]Addr{}, local: map[uint32]chanInfo{}, remote: map[uint32]chanInfo{},
	pending: map[uint32]uint16{}, avdtpN: map[uint16]int{}, last: map[uint32]string{},
}

func ck(h, cid uint16) uint32 { return uint32(h)<<16 | uint32(cid) }

func hexs(b []byte, max int) string {
	if len(b) > max {
		return fmt.Sprintf("% X …(+%d)", b[:max], len(b)-max)
	}
	return fmt.Sprintf("% X", b)
}

func dir(in bool) string {
	if in {
		return "<-"
	}
	return "->"
}

func (d *hciDump) peer(h uint16) string {
	if a, ok := d.addr[h]; ok {
		return a.String()
	}
	return fmt.Sprintf("h%03X", h)
}

func (d *hciDump) summary(force bool) {
	if d.since.IsZero() {
		d.since = time.Now()
		return
	}
	if !force && time.Since(d.since) < 5*time.Second {
		return
	}
	if d.mediaOut+d.completed+d.notifs+d.adv > 0 {
		logx.Dbgf("media", "last %.1fs: audio packets out %d (%d KB), completed-packets events %d, mouse notifications %d, adv reports %d",
			time.Since(d.since).Seconds(), d.mediaOut, d.mediaBytes/1024, d.completed, d.notifs, d.adv)
	}
	d.since = time.Now()
	d.mediaOut, d.mediaBytes, d.completed, d.notifs, d.adv = 0, 0, 0, 0, 0
}

// onHCI runs on the BTstack thread for every packet (debug mode only).
func (d *hciDump) onHCI(t uint8, in bool, p []byte) {
	defer func() { _ = recover() }() // a decoder bug must not take the stack down
	d.summary(false)
	switch t {
	case C.HCI_COMMAND_DATA_PACKET:
		d.cmd(p)
	case C.HCI_EVENT_PACKET:
		d.event(p)
	case C.HCI_ACL_DATA_PACKET:
		d.acl(in, p)
	case C.LOG_MESSAGE_PACKET:
	default:
		logx.Dbgf("hci", "%s type 0x%02X %s", dir(in), t, hexs(p, 32))
	}
}

var cmdNames = map[uint16]string{
	0x0401: "Inquiry", 0x0402: "Inquiry Cancel", 0x0405: "Create Connection", 0x0406: "Disconnect",
	0x0408: "Create Connection Cancel", 0x0409: "Accept Connection Request", 0x040A: "Reject Connection Request",
	0x040B: "Link Key Request Reply", 0x040C: "Link Key Request Negative Reply", 0x040D: "PIN Code Request Reply",
	0x0411: "Authentication Requested", 0x0413: "Set Connection Encryption", 0x0419: "Remote Name Request",
	0x041A: "Remote Name Request Cancel", 0x041B: "Read Remote Supported Features", 0x041C: "Read Remote Extended Features",
	0x041D: "Read Remote Version", 0x042B: "IO Capability Request Reply", 0x042C: "User Confirmation Request Reply",
	0x0434: "IO Capability Request Negative Reply",
	0x0803: "Sniff Mode", 0x0804: "Exit Sniff Mode", 0x0809: "Role Discovery", 0x080B: "Switch Role",
	0x080D: "Write Link Policy Settings", 0x080F: "Write Default Link Policy Settings", 0x0811: "Sniff Subrating",
	0x0C01: "Set Event Mask", 0x0C03: "Reset", 0x0C13: "Write Local Name", 0x0C14: "Read Local Name",
	0x0C18: "Write Page Timeout", 0x0C1A: "Write Scan Enable", 0x0C24: "Write Class of Device",
	0x0C33: "Host Buffer Size", 0x0C45: "Write Inquiry Mode", 0x0C52: "Write EIR", 0x0C56: "Write SSP Mode",
	0x0C6D: "Write LE Host Supported", 0x0C7A: "Write Secure Connections Host Support",
	0x1001: "Read Local Version", 0x1002: "Read Local Supported Commands", 0x1003: "Read Local Supported Features",
	0x1005: "Read Buffer Size", 0x1009: "Read BD_ADDR",
	0x1405: "Read RSSI",
	0x2001: "LE Set Event Mask", 0x2002: "LE Read Buffer Size", 0x2005: "LE Set Random Address",
	0x2006: "LE Set Adv Params", 0x200B: "LE Set Scan Params", 0x200C: "LE Set Scan Enable",
	0x200D: "LE Create Connection", 0x200E: "LE Create Connection Cancel", 0x2011: "LE Add To Filter Accept List",
	0x2013: "LE Connection Update", 0x2016: "LE Read Remote Features", 0x2019: "LE Enable Encryption",
	0x201A: "LE LTK Request Reply", 0x201B: "LE LTK Request Negative Reply", 0x2020: "LE Remote Conn Param Request Reply",
	0x2027: "LE Add Device To Resolving List", 0x202D: "LE Set Address Resolution Enable",
	0x2041: "LE Set Ext Scan Params", 0x2042: "LE Set Ext Scan Enable", 0x2043: "LE Ext Create Connection",
}

var evtNames = map[uint8]string{
	0x01: "Inquiry Complete", 0x02: "Inquiry Result", 0x03: "Connection Complete", 0x04: "Connection Request",
	0x05: "Disconnection Complete", 0x06: "Authentication Complete", 0x07: "Remote Name Request Complete",
	0x08: "Encryption Change", 0x0B: "Read Remote Features Complete", 0x0C: "Read Remote Version Complete",
	0x0E: "Command Complete", 0x0F: "Command Status", 0x10: "Hardware Error", 0x12: "Role Change",
	0x13: "Number Of Completed Packets", 0x14: "Mode Change", 0x16: "PIN Code Request", 0x17: "Link Key Request",
	0x18: "Link Key Notification", 0x1B: "Max Slots Change", 0x22: "Inquiry Result With RSSI",
	0x23: "Read Remote Extended Features Complete", 0x2C: "Synchronous Connection Complete", 0x2E: "Sniff Subrating",
	0x2F: "Extended Inquiry Result", 0x0D: "QoS Setup Complete", 0x20: "Page Scan Repetition Mode Change",
	0x1D: "Connection Packet Type Changed", 0x38: "Link Supervision Timeout Changed", 0x48: "Authenticated Payload Timeout Expired", 0x30: "Encryption Key Refresh Complete", 0x31: "IO Capability Request",
	0x32: "IO Capability Response", 0x33: "User Confirmation Request", 0x36: "Simple Pairing Complete",
	0x3E: "LE Meta", 0xFF: "Vendor",
}

var leSubNames = map[uint8]string{
	0x01: "Connection Complete", 0x02: "Advertising Report", 0x03: "Connection Update Complete",
	0x04: "Read Remote Features Complete", 0x05: "LTK Request", 0x06: "Remote Conn Param Request",
	0x07: "Data Length Change", 0x0A: "Enhanced Connection Complete", 0x0C: "PHY Update Complete",
	0x0D: "Extended Advertising Report",
}

var modeNames = map[uint8]string{0: "active", 1: "hold", 2: "sniff"}

func name(m map[uint16]string, k uint16) string {
	if n, ok := m[k]; ok {
		return n
	}
	return fmt.Sprintf("0x%04X", k)
}

func addrLE(b []byte) Addr { // HCI little-endian -> display order
	var a Addr
	for i := 0; i < 6 && i < len(b); i++ {
		a[5-i] = b[i]
	}
	return a
}

func (d *hciDump) cmd(p []byte) {
	if len(p) < 3 {
		return
	}
	op := binary.LittleEndian.Uint16(p)
	par := p[3:]
	switch op {
	case 0x040B: // addr + link key
		logx.Dbgf("hci", "-> CMD %s %s key=**", cmdNames[op], addrLE(par))
		return
	case 0x2019, 0x201A: // LTK
		logx.Dbgf("hci", "-> CMD %s h%03X ltk=**", cmdNames[op], binary.LittleEndian.Uint16(par)&0xFFF)
		return
	}
	extra := ""
	switch op {
	case 0x0405, 0x0409, 0x0419, 0x040C, 0x042B, 0x042C, 0x041A, 0x0408:
		if len(par) >= 6 {
			extra = " " + addrLE(par).String()
			par = par[6:]
		}
	case 0x0406:
		if len(par) >= 3 {
			h := binary.LittleEndian.Uint16(par) & 0xFFF
			extra = fmt.Sprintf(" %s reason 0x%02X (%s)", d.peer(h), par[2], hciErr(par[2]))
			par = nil
		}
	case 0x0803, 0x0804, 0x0809, 0x080D, 0x0811, 0x0411, 0x0413, 0x041B, 0x041C, 0x041D, 0x1405:
		if len(par) >= 2 {
			h := binary.LittleEndian.Uint16(par) & 0xFFF
			extra = " " + d.peer(h)
			par = par[2:]
		}
	}
	logx.Dbgf("hci", "-> CMD %s%s %s", name(cmdNames, op), extra, hexs(par, 24))
}

func (d *hciDump) event(p []byte) {
	if len(p) < 2 {
		return
	}
	code := p[0]
	par := p[2:]
	n, ok := evtNames[code]
	if !ok {
		n = fmt.Sprintf("0x%02X", code)
	}
	switch code {
	case 0x13:
		d.completed++
		return
	case 0x0E: // Command Complete: ncmd, opcode, status
		if len(par) >= 4 {
			op := binary.LittleEndian.Uint16(par[1:])
			st := par[3]
			rest := par[4:]
			if op == 0x1009 && len(rest) >= 6 {
				logx.Dbgf("hci", "<- EVT Command Complete %s status 0x%02X addr %s", name(cmdNames, op), st, addrLE(rest))
				return
			}
			logx.Dbgf("hci", "<- EVT Command Complete %s status 0x%02X %s", name(cmdNames, op), st, hexs(rest, 16))
		}
		return
	case 0x0F:
		if len(par) >= 4 {
			op := binary.LittleEndian.Uint16(par[2:])
			logx.Dbgf("hci", "<- EVT Command Status %s status 0x%02X (%s)", name(cmdNames, op), par[0], hciErr(par[0]))
		}
		return
	case 0x03: // status, handle, addr, link type, enc
		if len(par) >= 10 {
			h := binary.LittleEndian.Uint16(par[1:]) & 0xFFF
			a := addrLE(par[3:])
			if par[0] == 0 {
				d.addr[h] = a
			}
			logx.Dbgf("hci", "<- EVT Connection Complete %s h%03X status 0x%02X (%s) link %d", a, h, par[0], hciErr(par[0]), par[9])
		}
		return
	case 0x04:
		if len(par) >= 10 {
			logx.Dbgf("hci", "<- EVT Connection Request from %s CoD %02X%02X%02X link %d", addrLE(par), par[8], par[7], par[6], par[9])
		}
		return
	case 0x05:
		if len(par) >= 4 {
			h := binary.LittleEndian.Uint16(par[1:]) & 0xFFF
			logx.Dbgf("hci", "<- EVT Disconnection Complete %s status 0x%02X reason 0x%02X (%s)", d.peer(h), par[0], par[3], hciErr(par[3]))
			d.forget(h)
		}
		return
	case 0x14: // status, handle, mode, interval
		if len(par) >= 6 {
			h := binary.LittleEndian.Uint16(par[1:]) & 0xFFF
			iv := binary.LittleEndian.Uint16(par[4:])
			logx.Dbgf("hci", "<- EVT Mode Change %s -> %s interval %.1f ms", d.peer(h), modeNames[par[3]], float64(iv)*0.625)
		}
		return
	case 0x12:
		if len(par) >= 8 {
			logx.Dbgf("hci", "<- EVT Role Change %s status 0x%02X role %s", addrLE(par[1:]), par[0], map[uint8]string{0: "central", 1: "peripheral"}[par[7]])
		}
		return
	case 0x18:
		if len(par) >= 23 {
			logx.Dbgf("hci", "<- EVT Link Key Notification %s key=** type %d", addrLE(par), par[22])
		}
		return
	case 0x17, 0x31, 0x33, 0x16, 0x36, 0x32:
		if len(par) >= 6 {
			logx.Dbgf("hci", "<- EVT %s %s %s", n, addrLE(par), hexs(par[6:], 8))
		}
		return
	case 0x06, 0x08, 0x30, 0x0B, 0x0C, 0x23, 0x1B:
		if len(par) >= 3 {
			h := binary.LittleEndian.Uint16(par[1:]) & 0xFFF
			logx.Dbgf("hci", "<- EVT %s %s status 0x%02X %s", n, d.peer(h), par[0], hexs(par[3:], 12))
		}
		return
	case 0x3E:
		if len(par) < 1 {
			return
		}
		sub := par[0]
		switch sub {
		case 0x02, 0x0D:
			d.adv++
			return
		case 0x01, 0x0A: // status, handle, role, addr type, addr
			if len(par) >= 11 {
				h := binary.LittleEndian.Uint16(par[2:]) & 0xFFF
				a := addrLE(par[6:])
				if par[1] == 0 {
					d.addr[h] = a
				}
				logx.Dbgf("hci", "<- EVT LE %s %s h%03X status 0x%02X", leSubNames[sub], a, h, par[1])
			}
			return
		case 0x05:
			if len(par) >= 3 {
				h := binary.LittleEndian.Uint16(par[1:]) & 0xFFF
				logx.Dbgf("hci", "<- EVT LE LTK Request %s", d.peer(h))
			}
			return
		}
		ln, ok := leSubNames[sub]
		if !ok {
			ln = fmt.Sprintf("0x%02X", sub)
		}
		logx.Dbgf("hci", "<- EVT LE %s %s", ln, hexs(par[1:], 16))
		return
	}
	logx.Dbgf("hci", "<- EVT %s %s", n, hexs(par, 24))
}

func (d *hciDump) forget(h uint16) {
	delete(d.addr, h)
	delete(d.avdtpN, h)
	for k := range d.local {
		if uint16(k>>16) == h {
			delete(d.local, k)
		}
	}
	for k := range d.remote {
		if uint16(k>>16) == h {
			delete(d.remote, k)
		}
	}
}

var psmNames = map[uint16]string{0x0001: "SDP", 0x0003: "RFCOMM", 0x0011: "HID-ctrl", 0x0013: "HID-intr",
	0x0017: "AVCTP", 0x0019: "AVDTP", 0x001B: "AVCTP-browse", 0x001F: "ATT"}

func (d *hciDump) acl(in bool, p []byte) {
	if len(p) < 4 {
		return
	}
	hf := binary.LittleEndian.Uint16(p)
	h := hf & 0xFFF
	pb := (hf >> 12) & 3
	data := p[4:]
	lk := uint32(h)
	if in {
		lk |= 1 << 16
	}
	if pb == 1 { // continuation fragment
		if d.last[lk] == "AVDTP-media" {
			return
		}
		logx.Dbgf("l2cap", "%s %s continuation %d bytes", dir(in), d.peer(h), len(data))
		return
	}
	if len(data) < 4 {
		return
	}
	cid := binary.LittleEndian.Uint16(data[2:])
	pl := data[4:]
	switch cid {
	case 0x0001:
		d.l2capSig(h, in, pl)
		return
	case 0x0004:
		d.att(h, in, pl)
		return
	case 0x0005:
		logx.Dbgf("l2cap", "%s %s LE signalling %s", dir(in), d.peer(h), hexs(pl, 16))
		return
	case 0x0006:
		code := uint8(0)
		if len(pl) > 0 {
			code = pl[0]
		}
		if code == 0x06 || code == 0x07 || code == 0x08 { // encryption info / master id / identity info: keys
			logx.Dbgf("smp", "%s %s code 0x%02X (key material, masked)", dir(in), d.peer(h), code)
			return
		}
		logx.Dbgf("smp", "%s %s %s", dir(in), d.peer(h), hexs(pl, 20))
		return
	}
	ci, ok := d.lookup(h, cid, in)
	d.last[lk] = ci.kind
	if !ok {
		logx.Dbgf("l2cap", "%s %s cid 0x%04X %d bytes %s", dir(in), d.peer(h), cid, len(pl), hexs(pl, 24))
		return
	}
	switch ci.kind {
	case "AVDTP-media":
		if !in {
			d.mediaOut++
			d.mediaBytes += len(pl)
		} else {
			logx.Dbgf("avdtp", "<- %s media packet %d bytes", d.peer(h), len(pl))
		}
	case "AVDTP":
		d.avdtp(h, in, pl)
	case "AVCTP":
		d.avctp(h, in, pl)
	case "SDP":
		d.sdp(h, in, pl)
	default:
		logx.Dbgf("l2cap", "%s %s %s %d bytes %s", dir(in), d.peer(h), ci.kind, len(pl), hexs(pl, 24))
	}
}

// lookup: incoming packets carry our (local) CID, outgoing the remote one.
func (d *hciDump) lookup(h, cid uint16, in bool) (chanInfo, bool) {
	if cid == 0 {
		return chanInfo{}, false
	}
	if in {
		ci, ok := d.local[ck(h, cid)]
		return ci, ok
	}
	ci, ok := d.remote[ck(h, cid)]
	return ci, ok
}

var sigNames = map[uint8]string{0x01: "Command Reject", 0x02: "Connection Request", 0x03: "Connection Response",
	0x04: "Configure Request", 0x05: "Configure Response", 0x06: "Disconnection Request", 0x07: "Disconnection Response",
	0x08: "Echo Request", 0x09: "Echo Response", 0x0A: "Information Request", 0x0B: "Information Response"}

func (d *hciDump) l2capSig(h uint16, in bool, pl []byte) {
	for len(pl) >= 4 {
		code, id := pl[0], pl[1]
		ln := int(binary.LittleEndian.Uint16(pl[2:]))
		if 4+ln > len(pl) {
			ln = len(pl) - 4
		}
		b := pl[4 : 4+ln]
		pl = pl[4+ln:]
		n := sigNames[code]
		if n == "" {
			n = fmt.Sprintf("0x%02X", code)
		}
		dirKey := uint32(0)
		if in {
			dirKey = 1 << 31
		}
		switch code {
		case 0x02:
			if len(b) >= 4 {
				psm := binary.LittleEndian.Uint16(b)
				scid := binary.LittleEndian.Uint16(b[2:])
				d.pending[dirKey|ck(h, scid)] = psm
				logx.Dbgf("l2cap", "%s %s %s #%d PSM 0x%04X (%s) scid 0x%04X", dir(in), d.peer(h), n, id, psm, psmNames[psm], scid)
				continue
			}
		case 0x03:
			if len(b) >= 8 {
				dcid := binary.LittleEndian.Uint16(b)
				scid := binary.LittleEndian.Uint16(b[2:])
				res := binary.LittleEndian.Uint16(b[4:])
				// the requester sent the opposite direction
				reqKey := uint32(0)
				if !in {
					reqKey = 1 << 31
				}
				psm, ok := d.pending[reqKey|ck(h, scid)]
				if ok && res == 0 {
					delete(d.pending, reqKey|ck(h, scid))
					kind := psmNames[psm]
					if psm == 0x19 {
						d.avdtpN[h]++
						if d.avdtpN[h] > 1 {
							kind = "AVDTP-media"
						}
					}
					if kind == "" {
						kind = fmt.Sprintf("PSM 0x%04X", psm)
					}
					ci := chanInfo{psm: psm, kind: kind}
					if in { // we requested: scid is ours
						d.local[ck(h, scid)] = ci
						d.remote[ck(h, dcid)] = ci
					} else {
						d.local[ck(h, dcid)] = ci
						d.remote[ck(h, scid)] = ci
					}
					logx.Dbgf("l2cap", "%s %s %s #%d %s open (dcid 0x%04X scid 0x%04X)", dir(in), d.peer(h), n, id, kind, dcid, scid)
					continue
				}
				logx.Dbgf("l2cap", "%s %s %s #%d dcid 0x%04X scid 0x%04X result %d status %d", dir(in), d.peer(h), n, id, dcid, scid, res, binary.LittleEndian.Uint16(b[6:]))
				continue
			}
		case 0x06, 0x07:
			if len(b) >= 4 {
				dcid := binary.LittleEndian.Uint16(b)
				scid := binary.LittleEndian.Uint16(b[2:])
				kind := ""
				if ci, ok := d.lookup(h, dcid, in); ok {
					kind = ci.kind
				}
				if code == 0x07 {
					if in {
						delete(d.local, ck(h, scid))
						delete(d.remote, ck(h, dcid))
					} else {
						delete(d.local, ck(h, dcid))
						delete(d.remote, ck(h, scid))
					}
					if kind == "AVDTP-media" || kind == "AVDTP" {
						if d.avdtpN[h] > 0 {
							d.avdtpN[h]--
						}
					}
				}
				logx.Dbgf("l2cap", "%s %s %s #%d %s dcid 0x%04X scid 0x%04X", dir(in), d.peer(h), n, id, kind, dcid, scid)
				continue
			}
		}
		logx.Dbgf("l2cap", "%s %s %s #%d %s", dir(in), d.peer(h), n, id, hexs(b, 16))
	}
}

var avdtpSig = map[uint8]string{1: "DISCOVER", 2: "GET_CAPABILITIES", 3: "SET_CONFIGURATION", 4: "GET_CONFIGURATION",
	5: "RECONFIGURE", 6: "OPEN", 7: "START", 8: "CLOSE", 9: "SUSPEND", 0x0A: "ABORT", 0x0B: "SECURITY_CONTROL",
	0x0C: "GET_ALL_CAPABILITIES", 0x0D: "DELAYREPORT"}
var avdtpMsg = []string{"cmd", "general-reject", "accept", "reject"}

func (d *hciDump) avdtp(h uint16, in bool, pl []byte) {
	if len(pl) < 1 {
		return
	}
	label, pt, mt := pl[0]>>4, (pl[0]>>2)&3, pl[0]&3
	if pt != 0 && pt != 1 {
		logx.Dbgf("avdtp", "%s %s fragment %d bytes", dir(in), d.peer(h), len(pl))
		return
	}
	off := 1
	if pt == 1 {
		off = 2 // number of signal packets
	}
	if len(pl) <= off {
		return
	}
	sig := pl[off] & 0x3F
	n := avdtpSig[sig]
	if n == "" {
		n = fmt.Sprintf("0x%02X", sig)
	}
	extra := ""
	if sig == 0x0D && len(pl) >= off+4 { // delay report: seid, delay (1/10 ms)
		extra = fmt.Sprintf(" delay %.1f ms", float64(binary.BigEndian.Uint16(pl[off+2:]))/10)
	}
	logx.Dbgf("avdtp", "%s %s %s %s #%d%s %s", dir(in), d.peer(h), n, avdtpMsg[mt], label, extra, hexs(pl[off+1:], 24))
}

var avcType = map[uint8]string{0: "CONTROL", 1: "STATUS", 2: "SPECIFIC_INQUIRY", 3: "NOTIFY", 4: "GENERAL_INQUIRY",
	8: "NOT_IMPLEMENTED", 9: "ACCEPTED", 0xA: "REJECTED", 0xB: "IN_TRANSITION", 0xC: "STABLE", 0xD: "CHANGED", 0xF: "INTERIM"}
var avrcpPDU = map[uint8]string{0x10: "GetCapabilities", 0x20: "GetElementAttributes", 0x30: "GetPlayStatus",
	0x31: "RegisterNotification", 0x40: "RequestContinuingResponse", 0x50: "SetAbsoluteVolume", 0x60: "SetAddressedPlayer"}
var avrcpEvt = map[uint8]string{1: "PLAYBACK_STATUS", 2: "TRACK_CHANGED", 5: "PLAYBACK_POS", 9: "NOW_PLAYING",
	0x0A: "AVAILABLE_PLAYERS", 0x0B: "ADDRESSED_PLAYER", 0x0D: "VOLUME_CHANGED"}
var passOps = map[uint8]string{0x41: "VOLUME_UP", 0x42: "VOLUME_DOWN", 0x43: "MUTE", 0x44: "PLAY", 0x45: "STOP",
	0x46: "PAUSE", 0x4B: "FORWARD", 0x4C: "BACKWARD"}

func vol127(v uint8) string { return fmt.Sprintf("%d/127 (%.0f%%)", v&0x7F, float64(v&0x7F)*100/127) }

func (d *hciDump) avctp(h uint16, in bool, pl []byte) {
	if len(pl) < 6 {
		logx.Dbgf("avrcp", "%s %s %s", dir(in), d.peer(h), hexs(pl, 16))
		return
	}
	label := pl[0] >> 4
	cr := "cmd"
	if pl[0]&2 != 0 {
		cr = "rsp"
	}
	ct := pl[3] & 0x0F
	op := pl[5]
	head := fmt.Sprintf("%s %s #%d %s %s", dir(in), d.peer(h), label, cr, avcType[ct])
	switch op {
	case 0x7C: // PASS THROUGH
		if len(pl) >= 7 {
			state := "press"
			if pl[6]&0x80 != 0 {
				state = "release"
			}
			o := passOps[pl[6]&0x7F]
			if o == "" {
				o = fmt.Sprintf("0x%02X", pl[6]&0x7F)
			}
			logx.Dbgf("avrcp", "%s PASS_THROUGH %s %s", head, o, state)
			return
		}
	case 0x00: // VENDOR DEPENDENT (BT SIG company 0x001958)
		if len(pl) >= 13 {
			pdu := pl[9]
			par := pl[13:]
			n := avrcpPDU[pdu]
			if n == "" {
				n = fmt.Sprintf("PDU 0x%02X", pdu)
			}
			switch pdu {
			case 0x50:
				if len(par) >= 1 {
					logx.Dbgf("avrcp", "%s SetAbsoluteVolume %s", head, vol127(par[0]))
					return
				}
			case 0x31:
				if len(par) >= 1 {
					ev := avrcpEvt[par[0]]
					if ev == "" {
						ev = fmt.Sprintf("0x%02X", par[0])
					}
					if par[0] == 0x0D && len(par) >= 2 && cr == "rsp" {
						logx.Dbgf("avrcp", "%s RegisterNotification %s %s", head, ev, vol127(par[1]))
						return
					}
					logx.Dbgf("avrcp", "%s RegisterNotification %s %s", head, ev, hexs(par[1:], 12))
					return
				}
			}
			logx.Dbgf("avrcp", "%s %s %s", head, n, hexs(par, 20))
			return
		}
	case 0x30, 0x31:
		logx.Dbgf("avrcp", "%s %s", head, map[uint8]string{0x30: "UNIT_INFO", 0x31: "SUBUNIT_INFO"}[op])
		return
	}
	logx.Dbgf("avrcp", "%s opcode 0x%02X %s", head, op, hexs(pl[6:], 16))
}

var sdpPDU = map[uint8]string{1: "ErrorResponse", 2: "ServiceSearchRequest", 3: "ServiceSearchResponse",
	4: "ServiceAttributeRequest", 5: "ServiceAttributeResponse", 6: "ServiceSearchAttributeRequest", 7: "ServiceSearchAttributeResponse"}

func (d *hciDump) sdp(h uint16, in bool, pl []byte) {
	if len(pl) < 5 {
		return
	}
	logx.Dbgf("sdp", "%s %s %s tid %d %d bytes", dir(in), d.peer(h), sdpPDU[pl[0]], binary.BigEndian.Uint16(pl[1:]), len(pl))
}

var attOps = map[uint8]string{0x01: "Error", 0x02: "Exchange MTU Req", 0x03: "Exchange MTU Rsp", 0x04: "Find Info Req",
	0x05: "Find Info Rsp", 0x08: "Read By Type Req", 0x09: "Read By Type Rsp", 0x0A: "Read Req", 0x0B: "Read Rsp",
	0x0C: "Read Blob Req", 0x0D: "Read Blob Rsp", 0x10: "Read By Group Type Req", 0x11: "Read By Group Type Rsp",
	0x12: "Write Req", 0x13: "Write Rsp", 0x1B: "Notification", 0x1D: "Indication", 0x1E: "Confirmation", 0x52: "Write Cmd"}

func (d *hciDump) att(h uint16, in bool, pl []byte) {
	if len(pl) < 1 {
		return
	}
	if pl[0] == 0x1B {
		d.notifs++
		return
	}
	n := attOps[pl[0]]
	if n == "" {
		n = fmt.Sprintf("0x%02X", pl[0])
	}
	logx.Dbgf("att", "%s %s %s %s", dir(in), d.peer(h), n, hexs(pl[1:], 20))
}

// flushDump writes the pending traffic summary (on stop).
func flushDump() { dump.summary(true) }

var _ = strings.TrimSpace
