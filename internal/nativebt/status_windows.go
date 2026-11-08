package nativebt

import (
	"fmt"

	"golang.org/x/sys/windows"
)

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
