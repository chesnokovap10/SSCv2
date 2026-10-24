package app

import (
	"fmt"
	"unsafe"

	"golang.org/x/sys/windows"
)

var (
	bthprops           = windows.NewLazySystemDLL("bthprops.cpl")
	pFindFirstRadio    = bthprops.NewProc("BluetoothFindFirstRadio")
	pFindRadioClose    = bthprops.NewProc("BluetoothFindRadioClose")
	pGetRadioInfo      = bthprops.NewProc("BluetoothGetRadioInfo")
)

type radioInfo struct {
	size         uint32
	_            uint32
	address      uint64
	name         [248]uint16
	cod          uint32
	lmpSubver    uint16
	manufacturer uint16
}

// windowsRadio returns the BD_ADDR and name of the radio Windows currently
// uses ("" when Windows has no Bluetooth, e.g. adapter in WinUSB mode).
func windowsRadio() (string, string) {
	if pFindFirstRadio.Find() != nil {
		return "", ""
	}
	params := uint32(4)
	var radio windows.Handle
	h, _, _ := pFindFirstRadio.Call(uintptr(unsafe.Pointer(&params)), uintptr(unsafe.Pointer(&radio)))
	if h == 0 {
		return "", ""
	}
	defer pFindRadioClose.Call(h)
	defer windows.CloseHandle(radio)
	var info radioInfo
	info.size = uint32(unsafe.Sizeof(info))
	if r, _, _ := pGetRadioInfo.Call(uintptr(radio), uintptr(unsafe.Pointer(&info))); r != 0 {
		return "", ""
	}
	a := info.address
	addr := fmt.Sprintf("%02X:%02X:%02X:%02X:%02X:%02X",
		byte(a>>40), byte(a>>32), byte(a>>24), byte(a>>16), byte(a>>8), byte(a))
	return addr, windows.UTF16ToString(info.name[:])
}
