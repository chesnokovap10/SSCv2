// Package driver detects and switches the Bluetooth adapter's function
// driver: WinUSB (BTstack streaming mode) or BTHUSB (Windows Bluetooth).
package driver

import (
	"fmt"
	"sscv2/internal/i18n"
	"strings"

	"golang.org/x/sys/windows"
)

// USBID is a USB vendor/product pair.
type USBID struct{ VID, PID uint16 }

func (u USBID) String() string { return fmt.Sprintf("%04X:%04X", u.VID, u.PID) }

// KnownMediaTek lists USB ids of MediaTek MT79xx Bluetooth functions found
// in laptops. The chip id register is checked at runtime, so this only
// drives auto-detection.
var KnownMediaTek = []USBID{
	{0x0489, 0xE0E2}, // Foxconn MT7922 (ASUS Zenbook UM3504)
	{0x0489, 0xE0D8}, {0x0489, 0xE0D9}, {0x0489, 0xE0F2},
	{0x0489, 0xE0C8}, {0x0489, 0xE0CD}, {0x0489, 0xE0E0}, {0x0489, 0xE0F6},
	{0x13D3, 0x3568}, {0x13D3, 0x3585}, {0x13D3, 0x3584}, {0x13D3, 0x3563},
	{0x0E8D, 0x7922}, {0x0E8D, 0x7961}, {0x0E8D, 0x7902},
}

// Mode of the adapter's driver.
type Mode int

const (
	NotPresent Mode = iota
	WinUSB          // streaming mode (BTstack)
	BthUSB          // Windows Bluetooth
	Other
)

func (m Mode) String() string {
	switch m {
	case WinUSB:
		return i18n.T("WinUSB (поток)", "WinUSB (streaming)")
	case BthUSB:
		return "Windows Bluetooth"
	case Other:
		return i18n.T("другой драйвер", "another driver")
	}
	return i18n.T("не найден", "not found")
}

// Status describes the adapter devnode.
type Status struct {
	ID         USBID
	Mode       Mode
	Service    string // "WinUSB", "BTHUSB", "usbccgp", ...
	Name       string
	InstanceID string // PnP instance id of the whole-device node
}

func hwidMatches(hwid string, id USBID) bool {
	u := strings.ToUpper(hwid)
	return strings.Contains(u, fmt.Sprintf("VID_%04X", id.VID)) &&
		strings.Contains(u, fmt.Sprintf("PID_%04X", id.PID))
}

func strProp(set windows.DevInfo, d *windows.DevInfoData, p windows.SPDRP) string {
	v, err := set.DeviceRegistryProperty(d, p)
	if err != nil {
		return ""
	}
	switch t := v.(type) {
	case string:
		return t
	case []string:
		if len(t) > 0 {
			return t[0]
		}
	}
	return ""
}

func modeOf(service string) Mode {
	switch strings.ToUpper(service) {
	case "WINUSB":
		return WinUSB
	case "BTHUSB":
		return BthUSB
	case "":
		return NotPresent
	}
	return Other
}

// Detect finds the present devnode for id and reports its driver.
//
// Composite chips (MT7922) appear as a parent node (usbccgp, or WinUSB once
// switched) plus "&MI_xx" interface children (BTHUSB on MI_00). The switch
// targets the parent, so the parent is reported; a usbccgp parent with a
// BTHUSB child counts as Windows Bluetooth mode.
func Detect(id USBID) Status {
	st := Status{ID: id}
	set, err := windows.SetupDiGetClassDevsEx(nil, "", 0,
		windows.DIGCF_ALLCLASSES|windows.DIGCF_PRESENT, 0, "")
	if err != nil {
		return st
	}
	defer set.Close()

	var parent, lastChild Status
	haveParent, childBth := false, false
	for i := 0; ; i++ {
		d, err := set.EnumDeviceInfo(i)
		if err != nil {
			break
		}
		v, err := set.DeviceRegistryProperty(d, windows.SPDRP_HARDWAREID)
		if err != nil {
			continue
		}
		ids, _ := v.([]string)
		matched := false
		for _, h := range ids {
			if hwidMatches(h, id) {
				matched = true
				break
			}
		}
		if !matched {
			continue
		}
		cur := Status{ID: id}
		cur.InstanceID, _ = set.DeviceInstanceID(d)
		cur.Name = strProp(set, d, windows.SPDRP_FRIENDLYNAME)
		if cur.Name == "" {
			cur.Name = strProp(set, d, windows.SPDRP_DEVICEDESC)
		}
		cur.Service = strProp(set, d, windows.SPDRP_SERVICE)
		cur.Mode = modeOf(cur.Service)

		if strings.Contains(strings.ToUpper(cur.InstanceID), "&MI_") {
			if cur.Mode == BthUSB {
				childBth = true
			}
			lastChild = cur
			continue
		}
		parent, haveParent = cur, true
		if cur.Mode == WinUSB || cur.Mode == BthUSB {
			break
		}
	}
	if !haveParent {
		return lastChild
	}
	if parent.Mode == Other && childBth {
		parent.Mode = BthUSB
	}
	return parent
}

// FindAdapter returns the first known MediaTek adapter that is present,
// preferring `want` when it is non-zero.
func FindAdapter(want USBID) (Status, bool) {
	if want.VID != 0 {
		if st := Detect(want); st.Mode != NotPresent {
			return st, true
		}
	}
	for _, id := range KnownMediaTek {
		if st := Detect(id); st.Mode != NotPresent {
			return st, true
		}
	}
	return Status{}, false
}
