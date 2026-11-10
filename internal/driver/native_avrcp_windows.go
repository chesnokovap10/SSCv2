package driver

import (
	"errors"
	"fmt"
	"strconv"
	"strings"
	"sync"
	"unsafe"

	"golang.org/x/sys/windows"
	"golang.org/x/sys/windows/registry"
)

const avrcpNodesValue = "ReleasedAVRCPNodes"

var avrcpMu sync.Mutex
var avrcpNodeStatus = windows.NewLazySystemDLL("cfgmgr32.dll").NewProc("CM_Get_DevNode_Status")

// ReleaseNativeAVRCP releases the Windows transport for the selected paired device.
func ReleaseNativeAVRCP(device string) error {
	avrcpMu.Lock()
	defer avrcpMu.Unlock()
	key, err := openProfileState()
	if err != nil {
		return err
	}
	defer key.Close()
	if err := restoreNativeAVRCP(key); err != nil {
		return err
	}
	addr := strings.ToUpper(strings.ReplaceAll(device, ":", ""))
	if n, err := strconv.ParseUint(addr, 16, 48); err != nil || n == 0 || len(addr) != 12 {
		return errors.New("invalid AVRCP Bluetooth address")
	}
	class := windows.GUID{Data1: 0xe0cbf06c, Data2: 0xcd8b, Data3: 0x4647, Data4: [8]byte{0xbb, 0x8a, 0x26, 0x3b, 0x43, 0xf0, 0xf9, 0x74}}
	set, err := windows.SetupDiGetClassDevsEx(&class, "", 0, windows.DIGCF_PRESENT, 0, "")
	if err != nil {
		return err
	}
	defer set.Close()
	var nodes []string
	for i := 0; ; i++ {
		info, err := set.EnumDeviceInfo(i)
		if errors.Is(err, windows.ERROR_NO_MORE_ITEMS) {
			break
		}
		if err != nil {
			return err
		}
		id, err := set.DeviceInstanceID(info)
		if err != nil {
			return err
		}
		upper := strings.ToUpper(id)
		if !(strings.HasPrefix(upper, `BTHENUM\{0000110C-`) || strings.HasPrefix(upper, `BTHENUM\{0000110E-`)) || !strings.Contains(upper, "&"+addr+"_") {
			continue
		}
		var status, problem uint32
		result, _, _ := avrcpNodeStatus.Call(uintptr(unsafe.Pointer(&status)), uintptr(unsafe.Pointer(&problem)), uintptr(info.DevInst), 0)
		if result != 0 {
			return fmt.Errorf("query Windows AVRCP node: CR %#x", result)
		}
		if status&8 != 0 {
			nodes = append(nodes, id)
		} // DN_STARTED
	}
	if len(nodes) == 0 {
		return errors.New("no active Windows AVRCP transport for selected headphones")
	}
	if err := key.SetStringsValue(avrcpNodesValue, nodes); err != nil {
		return err
	}
	for _, id := range nodes {
		if err := nativePnP("/disable-device", id); err != nil {
			return errors.Join(err, restoreNativeAVRCP(key))
		}
	}
	return nil
}

func RestoreNativeAVRCP() error {
	avrcpMu.Lock()
	defer avrcpMu.Unlock()
	key, err := openProfileState()
	if err != nil {
		return err
	}
	defer key.Close()
	return restoreNativeAVRCP(key)
}

func restoreNativeAVRCP(key registry.Key) error {
	nodes, _, err := key.GetStringsValue(avrcpNodesValue)
	if errors.Is(err, registry.ErrNotExist) {
		return nil
	}
	if err != nil {
		return err
	}
	var pending []string
	var failures error
	for _, id := range nodes {
		if err := nativePnP("/enable-device", id); err != nil {
			pending = append(pending, id)
			failures = errors.Join(failures, err)
		}
	}
	if len(pending) > 0 {
		return errors.Join(failures, key.SetStringsValue(avrcpNodesValue, pending))
	}
	return key.DeleteValue(avrcpNodesValue)
}
