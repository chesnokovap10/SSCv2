// Package mtk downloads the RAM firmware into MediaTek MT79xx Bluetooth
// chips (MT7921/MT7922/MT7902) over WinUSB.
//
// These combo chips boot from ROM and need "BT_RAM_CODE_MT7922_1_1_hdr.bin"
// pushed on every power-up. Under BTHUSB the vendor filter driver does that;
// in WinUSB mode we do it before BTstack sends its first HCI Reset.
//
// Wire protocol (reimplemented from the documented behaviour of the Linux
// btmtk driver, no code shared):
//
//	HCI command  : control OUT 0x20/0x00, data = opcode(2) len(1) params
//	WMT command  : HCI opcode 0xFC6F, params = {dir=1, op, dlen16=n+1, flag} + n bytes
//	WMT event    : control IN 0xC0/0x01 wValue 0x30, 64 bytes; empty = not ready
//	               event = 0xE4 len {dir op dlen16 flag} [status16 BE]
//	Register read: control IN 0xC0/0x63, wValue=reg>>16, wIndex=reg&0xFFFF
//	UHW reg write: control OUT 0x40/0x02 (Linux uses 0x5E, rejected by WinUSB)
//
// Firmware image ("*_hdr.bin"): 32-byte header (build time[16]...), 64-byte
// global descriptor (section count at +12), then 64-byte section maps:
// +4 file offset, +16 download size, +12..+63 "bin info" sent as the query.
package mtk

import (
	"bytes"
	"encoding/binary"
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"time"
)

const (
	wmtOpcode      = 0xFC6F
	wmtEvtCode     = 0xE4
	wmtOpPatch     = 0x01
	wmtOpFuncCtrl  = 0x06
	wmtPktStart    = 1
	wmtPktContinue = 2
	wmtPktEnd      = 3
	wmtChunk       = 250
	wmtTimeout     = 5 * time.Second

	fwHdrSize    = 32
	fwGDSize     = 64
	fwSecMapSize = 64
	fwSecCommon  = 12
	fwSecSend    = 52

	regChipIDLegacy = 0x80000008
	regChipID       = 0x70010200
	regFwVersion    = 0x80021004
	regFwFlavor     = 0x70010020
	regEpRstOpt     = 0x74011890
	epRstInOutOpt   = 0x00010001
	regBtMisc       = 0x70002510
	regBtSubsysRst  = 0x70002610
	regUdmaIntStaBt = 0x74000024
	btRstDone       = 0x00000100
)

type wmtStatus int

const (
	stInvalid wmtStatus = iota
	stPatchUndone
	stPatchProgress
	stPatchDone
	stOnUndone
	stOnDone
	stOnProgress
)

var (
	ErrUnsupported = errors.New("неподдерживаемый чип MediaTek")
	ErrFirmware    = errors.New("файл прошивки не найден или повреждён")
	ErrTimeout     = errors.New("адаптер не отвечает (WMT timeout)")
	ErrProtocol    = errors.New("неожиданный ответ адаптера")
	ErrNotFound    = errNotFound
)

// ChipInfo describes the probed chip.
type ChipInfo struct {
	DevID     uint32 // e.g. 0x7922
	FwVersion uint32
	FwFlavor  uint32
	FwName    string // expected firmware file name
	FwPath    string // file actually used (after Setup)
	FwBuild   string // 16-char build stamp of the image
}

func (c ChipInfo) String() string {
	return fmt.Sprintf("MT%04X (fw reg 0x%08X)", c.DevID&0xFFFF, c.FwVersion)
}

func (d *usbDev) regRead(reg uint32) (uint32, error) {
	b := make([]byte, 4)
	n, err := d.ctrl(0xC0, 0x63, uint16(reg>>16), uint16(reg), b)
	if err != nil {
		return 0, err
	}
	if n != 4 {
		return 0, ErrProtocol
	}
	return binary.LittleEndian.Uint32(b), nil
}

func (d *usbDev) uhwWrite(reg, val uint32) error {
	b := make([]byte, 4)
	binary.LittleEndian.PutUint32(b, val)
	_, err := d.ctrl(0x40, 0x02, uint16(reg>>16), uint16(reg), b)
	return err
}

func (d *usbDev) uhwRead(reg uint32) (uint32, error) {
	b := make([]byte, 4)
	n, err := d.ctrl(0xDE, 0x01, uint16(reg>>16), uint16(reg), b)
	if err != nil {
		n, err = d.ctrl(0xC0, 0x01, uint16(reg>>16), uint16(reg), b)
	}
	if err != nil {
		return 0, err
	}
	if n != 4 {
		return 0, ErrProtocol
	}
	return binary.LittleEndian.Uint32(b), nil
}

// subsysReset is the MT7922 Bluetooth subsystem reset; the chip drops its
// RAM firmware, so a full download follows.
func (d *usbDev) subsysReset() error {
	v, err := d.uhwRead(regBtSubsysRst)
	if err != nil {
		return err
	}
	if err := d.uhwWrite(regBtSubsysRst, v|0x00002020); err != nil {
		return err
	}
	if err := d.uhwWrite(regEpRstOpt, epRstInOutOpt); err != nil {
		return err
	}
	if v, err = d.uhwRead(regBtSubsysRst); err != nil {
		return err
	}
	if err := d.uhwWrite(regBtSubsysRst, v|0x1); err != nil {
		return err
	}
	time.Sleep(100 * time.Millisecond)
	done := false
	for i := 0; i < 50 && !done; i++ {
		if m, err := d.uhwRead(regBtMisc); err == nil && m&btRstDone != 0 {
			done = true
		} else {
			time.Sleep(20 * time.Millisecond)
		}
	}
	if !done {
		d.logf("MTK: subsystem reset: no RST_DONE (continuing)")
	}
	_ = d.uhwWrite(regUdmaIntStaBt, 0xFF)
	id, err := d.regRead(regChipID)
	if err != nil || id == 0 {
		d.logf("MTK: subsystem reset: chip id unreadable afterwards")
		if err == nil {
			err = ErrProtocol
		}
		return err
	}
	d.logf("MTK: Bluetooth subsystem reset done (chip 0x%04X)", id)
	return nil
}

// wmtSync sends one WMT command and waits for its event.
func (d *usbDev) wmtSync(op, flag uint8, data []byte) (wmtStatus, error) {
	plen := 5 + len(data)
	if plen > 255 {
		return stInvalid, ErrProtocol
	}
	cmd := make([]byte, 3+plen)
	binary.LittleEndian.PutUint16(cmd, wmtOpcode)
	cmd[2] = byte(plen)
	cmd[3] = 1 // host -> chip
	cmd[4] = op
	binary.LittleEndian.PutUint16(cmd[5:], uint16(len(data)+1))
	cmd[7] = flag
	copy(cmd[8:], data)
	if _, err := d.ctrl(0x20, 0x00, 0, 0, cmd); err != nil {
		return stInvalid, err
	}

	ev := make([]byte, 64)
	deadline := time.Now().Add(wmtTimeout)
	var got int
	for {
		n, err := d.ctrl(0xC0, 0x01, 0x30, 0x00, ev)
		if err != nil {
			return stInvalid, err
		}
		if n > 0 {
			got = n
			break
		}
		if time.Now().After(deadline) {
			d.logf("MTK: WMT op 0x%02X: no event within %s", op, wmtTimeout)
			return stInvalid, ErrTimeout
		}
		time.Sleep(300 * time.Microsecond)
	}
	if got < 7 || ev[0] != wmtEvtCode {
		d.logf("MTK: unexpected event (len=%d code=0x%02X)", got, ev[0])
		return stInvalid, ErrProtocol
	}
	if ev[3] != op {
		d.logf("MTK: WMT op mismatch (got 0x%02X, sent 0x%02X)", ev[3], op)
		return stInvalid, ErrProtocol
	}
	eFlag := ev[6]
	switch op {
	case wmtOpPatch:
		switch eFlag {
		case 2:
			return stPatchDone, nil
		case 1:
			return stPatchProgress, nil
		}
		return stPatchUndone, nil
	case wmtOpFuncCtrl:
		if got >= 9 {
			switch uint16(ev[7])<<8 | uint16(ev[8]) {
			case 0x404:
				return stOnDone, nil
			case 0x420:
				return stOnProgress, nil
			}
			return stOnUndone, nil
		}
		if eFlag != 0 {
			return stOnUndone, nil
		}
		return stOnDone, nil
	}
	return stInvalid, nil
}

// drainEvents discards anything queued on the HCI event pipe so BTstack
// starts from a clean slate.
func (d *usbDev) drainEvents() {
	buf := make([]byte, 260)
	n := 0
	for i := 0; i < 16; i++ {
		if d.readEvent(buf) == 0 {
			break
		}
		n++
	}
	if n > 0 {
		d.logf("MTK: drained %d stale event(s)", n)
	}
}

type fwImage struct {
	data     []byte
	sections int
}

func loadImage(path string) (*fwImage, error) {
	b, err := os.ReadFile(path)
	if err != nil || len(b) < fwHdrSize+fwGDSize || len(b) > 16<<20 {
		return nil, ErrFirmware
	}
	n := int(binary.LittleEndian.Uint32(b[fwHdrSize+12:]))
	if n == 0 || n > 64 || len(b) < fwHdrSize+fwGDSize+fwSecMapSize*n {
		return nil, ErrFirmware
	}
	for i := 0; i < n; i++ {
		sm := b[fwHdrSize+fwGDSize+fwSecMapSize*i:]
		off := binary.LittleEndian.Uint32(sm[4:])
		dl := binary.LittleEndian.Uint32(sm[16:])
		if dl != 0 && (uint64(off) > uint64(len(b)) || uint64(dl) > uint64(len(b))-uint64(off)) {
			return nil, ErrFirmware
		}
	}
	return &fwImage{data: b, sections: n}, nil
}

// findInDriverStore returns the newest copy of name in
// DriverStore\FileRepository\mtkbt*\, judged by the 16-byte build stamp.
func findInDriverStore(name string) string {
	pattern := filepath.Join(os.Getenv("WINDIR"), `System32\DriverStore\FileRepository\mtkbt*`)
	dirs, _ := filepath.Glob(pattern)
	best, bestStamp := "", ""
	for _, dir := range dirs {
		cand := filepath.Join(dir, name)
		f, err := os.Open(cand)
		if err != nil {
			continue
		}
		stamp := make([]byte, 16)
		n, _ := f.Read(stamp)
		f.Close()
		if n != 16 {
			continue
		}
		if best == "" || string(stamp) > bestStamp {
			best, bestStamp = cand, string(stamp)
		}
	}
	return best
}

func locateFirmware(fwPath, name string) string {
	if fwPath != "" {
		if fi, err := os.Stat(fwPath); err == nil {
			if !fi.IsDir() {
				return fwPath
			}
			if c := filepath.Join(fwPath, name); fileExists(c) {
				return c
			}
		}
	}
	return findInDriverStore(name)
}

func fileExists(p string) bool { _, err := os.Stat(p); return err == nil }

func (d *usbDev) probe() (ChipInfo, error) {
	var info ChipInfo
	id, err := d.regRead(regChipIDLegacy)
	if err != nil {
		return info, err
	}
	if id != 0x7663 {
		if id, err = d.regRead(regChipID); err != nil {
			return info, err
		}
		if info.FwVersion, err = d.regRead(regFwVersion); err != nil {
			return info, err
		}
		fl, err := d.regRead(regFwFlavor)
		if err != nil {
			return info, err
		}
		info.FwFlavor = (fl & 0x80) >> 7
	}
	info.DevID = id
	chip := id & 0xFFFF
	rev := (info.FwVersion & 0xFF) + 1
	if chip == 0x7961 && info.FwFlavor != 0 {
		info.FwName = fmt.Sprintf("BT_RAM_CODE_MT%04x_1a_%x_hdr.bin", chip, rev)
	} else {
		info.FwName = fmt.Sprintf("BT_RAM_CODE_MT%04x_1_%x_hdr.bin", chip, rev)
	}
	d.logf("MTK: chip 0x%04X fw_version 0x%08X flavor %d -> %s", id, info.FwVersion, info.FwFlavor, info.FwName)
	if chip != 0x7922 && chip != 0x7961 && chip != 0x7902 {
		return info, ErrUnsupported
	}
	return info, nil
}

// download returns cold=true when at least one section had to be sent.
func (d *usbDev) download(img *fwImage) (cold bool, err error) {
	base := img.data
	d.logf("MTK: firmware build %s, %d section(s)", string(bytes.TrimRight(base[:16], "\x00")), img.sections)
	for i := 0; i < img.sections; i++ {
		sm := base[fwHdrSize+fwGDSize+fwSecMapSize*i:]
		off := binary.LittleEndian.Uint32(sm[4:])
		left := binary.LittleEndian.Uint32(sm[16:])
		if left == 0 {
			continue
		}
		q := make([]byte, 1+fwSecSend) // legacy mode byte + bin info
		copy(q[1:], sm[fwSecCommon:fwSecCommon+fwSecSend])

		var st wmtStatus
		var err error
		for tries := 20; ; tries-- {
			if st, err = d.wmtSync(wmtOpPatch, 0, q); err != nil {
				return cold, err
			}
			if st != stPatchProgress {
				break
			}
			if tries == 1 {
				return cold, ErrTimeout
			}
			time.Sleep(100 * time.Millisecond)
		}
		if st == stPatchDone {
			d.logf("MTK: section %d already loaded", i)
			continue
		}
		if st != stPatchUndone {
			return cold, ErrProtocol
		}
		d.logf("MTK: section %d: %d bytes", i, left)
		cold = true
		p := base[off:]
		first := true
		for left > 0 {
			n := left
			if n > wmtChunk {
				n = wmtChunk
			}
			flag := uint8(wmtPktContinue)
			if first {
				flag = wmtPktStart
			} else if left == n {
				flag = wmtPktEnd
			}
			first = false
			st, err := d.wmtSync(wmtOpPatch, flag, p[:n])
			if err != nil {
				return cold, err
			}
			if st == stPatchProgress {
				return cold, ErrProtocol
			}
			p = p[n:]
			left -= n
		}
	}
	if cold {
		time.Sleep(110 * time.Millisecond) // let the chip activate the new firmware
	}
	return cold, nil
}

// Probe reads the chip id / firmware registers only.
func Probe(vid, pid uint16, logf func(string, ...any)) (ChipInfo, error) {
	d, err := openDev(vid, pid, logf)
	if err != nil {
		return ChipInfo{}, err
	}
	defer d.close()
	return d.probe()
}

// SubsysReset resets the Bluetooth subsystem (next Setup is a cold load).
func SubsysReset(vid, pid uint16, logf func(string, ...any)) error {
	d, err := openDev(vid, pid, logf)
	if err != nil {
		return err
	}
	defer d.close()
	return d.subsysReset()
}

// Setup is the full bring-up: probe, firmware download (skipped per section
// when already loaded), endpoint reset option, function enable, event drain.
// fwPath may be a file, a directory holding the expected file, or empty to
// search the Windows driver store (newest MediaTek package wins). On failure
// it resets the Bluetooth subsystem and retries once from a cold chip.
func Setup(vid, pid uint16, fwPath string, logf func(string, ...any)) (ChipInfo, error) {
	if logf == nil {
		logf = func(string, ...any) {}
	}
	t0 := time.Now()
	inner := logf
	logf = func(f string, a ...any) { inner("[+%4dms] "+f, append([]any{time.Since(t0).Milliseconds()}, a...)...) }
	d, err := openDev(vid, pid, logf)
	if err != nil {
		return ChipInfo{}, err
	}
	defer d.close()

	info, err := d.probe()
	if err != nil {
		return info, err
	}
	path := locateFirmware(fwPath, info.FwName)
	if path == "" {
		logf("MTK: firmware %s not found", info.FwName)
		return info, ErrFirmware
	}
	info.FwPath = path
	logf("MTK: firmware file %s", path)
	img, err := loadImage(path)
	if err != nil {
		return info, err
	}
	info.FwBuild = string(bytes.TrimRight(img.data[:16], "\x00"))

	for attempt := 0; attempt < 2; attempt++ {
		if attempt > 0 {
			logf("MTK: bring-up failed (%v) - resetting Bluetooth subsystem and retrying", err)
			if err = d.subsysReset(); err != nil {
				break
			}
		}
		var cold bool
		if cold, err = d.download(img); err != nil {
			continue
		}
		// The endpoint reset option belongs to a fresh download. On a warm
		// chip (firmware still loaded by the Windows driver) the write only
		// completes after the 5 s USB control timeout, so skip it there.
		if cold {
			if e := d.uhwWrite(regEpRstOpt, epRstInOutOpt); e != nil {
				logf("MTK: warning: endpoint reset option not written (%v), continuing", e)
			} else {
				logf("MTK: endpoint reset option written")
			}
		} else {
			logf("MTK: firmware already running, endpoint reset option skipped")
		}
		var st wmtStatus
		if st, err = d.wmtSync(wmtOpFuncCtrl, 0, []byte{1}); err != nil {
			continue
		}
		if st == stOnDone {
			logf("MTK: Bluetooth function enabled")
		} else {
			logf("MTK: Bluetooth function enable requested")
		}
		break
	}
	if err != nil {
		logf("MTK: failed: %v", err)
		return info, err
	}
	d.drainEvents()
	logf("MTK: bring-up complete")
	return info, nil
}
