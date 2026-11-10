package driver

import (
	"errors"
	"fmt"
	"unsafe"

	"golang.org/x/sys/windows"
)

var localProfileService = windows.GUID{Data1: 0x80cbb510, Data2: 0x404f, Data3: 0x4d4e,
	Data4: [8]byte{0x94, 0xa7, 0x25, 0x5e, 0x05, 0x2f, 0xb3, 0x1b}}

func SetLocalProfile(enabled bool) error {
	var token windows.Token
	if err := windows.OpenProcessToken(windows.CurrentProcess(), windows.TOKEN_ADJUST_PRIVILEGES|windows.TOKEN_QUERY, &token); err != nil {
		return err
	}
	defer token.Close()
	name := windows.StringToUTF16Ptr("SeLoadDriverPrivilege")
	privileges := windows.Tokenprivileges{PrivilegeCount: 1}
	privilege := &privileges.Privileges[0]
	if err := windows.LookupPrivilegeValue(nil, name, &privilege.Luid); err != nil {
		return err
	}
	privilege.Attributes = windows.SE_PRIVILEGE_ENABLED
	var previous windows.Tokenprivileges
	var size uint32
	if err := windows.AdjustTokenPrivileges(token, false, &privileges, uint32(unsafe.Sizeof(previous)), &previous, &size); err != nil {
		return err
	}
	defer windows.AdjustTokenPrivileges(token, false, &previous, 0, nil, nil)

	var service struct {
		Enabled uint32
		Address uint64
		Name    [256]uint16
		Device  [256]uint16
	}
	if enabled {
		service.Enabled = 1
	}
	copy(service.Name[:], windows.StringToUTF16("SSCv2 Local AVDTP Probe"))
	proc := windows.NewLazySystemDLL("bthprops.cpl").NewProc("BluetoothSetLocalServiceInfo")
	if err := proc.Find(); err != nil {
		return err
	}
	code, _, _ := proc.Call(0, uintptr(unsafe.Pointer(&localProfileService)), 0, uintptr(unsafe.Pointer(&service)))
	if code != 0 {
		return fmt.Errorf("BluetoothSetLocalServiceInfo: %w", windows.Errno(code))
	}
	return nil
}

var localProfileInterface = windows.GUID{Data1: 0xc713148a, Data2: 0x3218, Data3: 0x4755,
	Data4: [8]byte{0xb1, 0x03, 0x7a, 0xee, 0x51, 0xc9, 0xd3, 0x13}}

func LocalProfileInterfaces() ([]string, error) {
	paths, err := windows.CM_Get_Device_Interface_List("", &localProfileInterface, windows.CM_GET_DEVICE_INTERFACE_LIST_PRESENT)
	// The wrapper reports an empty list as an error. This is expected
	// before the local Bluetooth profile has been registered.
	if errors.Is(err, windows.ERROR_NO_SUCH_DEVICE_INTERFACE) {
		return nil, nil
	}
	if err != nil {
		return nil, fmt.Errorf("enumerate local AVDTP interfaces: %w", err)
	}
	return paths, nil
}
