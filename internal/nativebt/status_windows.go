package nativebt

import (
	"fmt"
	"unsafe"

	"golang.org/x/sys/windows"
)

// TestSigning reports the running kernel's code-integrity policy. The BCD
// setting can already be different when a reboot is pending.
func TestSigning() (bool, error) {
	const testSigning = 0x02
	info := struct {
		Length  uint32
		Options uint32
	}{Length: 8}
	if err := windows.NtQuerySystemInformation(windows.SystemCodeIntegrityInformation,
		unsafe.Pointer(&info), info.Length, nil); err != nil {
		return false, fmt.Errorf("query Windows code integrity: %w", err)
	}
	return info.Options&testSigning != 0, nil
}

func Interfaces() ([]string, error) {
	// Matches the device interface registered by SscAvdtpProbe.sys.
	class := windows.GUID{Data1: 0x105bdfd9, Data2: 0x73ce, Data3: 0x4bcf,
		Data4: [8]byte{0xb2, 0xe9, 0xc5, 0xd6, 0x11, 0xf6, 0x9a, 0x23}}
	paths, err := windows.CM_Get_Device_Interface_List("", &class, windows.CM_GET_DEVICE_INTERFACE_LIST_PRESENT)
	if err == windows.ERROR_NO_SUCH_DEVICE_INTERFACE {
		return nil, nil
	}
	return paths, err
}

func singleInterface() (string, error) {
	paths, err := Interfaces()
	if err != nil {
		return "", fmt.Errorf("find native Bluetooth driver: %w", err)
	}
	switch len(paths) {
	case 0:
		return "", fmt.Errorf("the native Bluetooth driver has no active interface")
	case 1:
		return paths[0], nil
	default:
		return "", fmt.Errorf("found %d native Bluetooth interfaces; specify the device path", len(paths))
	}
}
