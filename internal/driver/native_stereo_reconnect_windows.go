package driver

import (
	"errors"
	"fmt"
	"strconv"
	"strings"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
)

var (
	stereoBthProps   = windows.NewLazySystemDLL("bthprops.cpl")
	stereoFindRadio  = stereoBthProps.NewProc("BluetoothFindFirstRadio")
	stereoNextRadio  = stereoBthProps.NewProc("BluetoothFindNextRadio")
	stereoCloseFind  = stereoBthProps.NewProc("BluetoothFindRadioClose")
	stereoGetDevice  = stereoBthProps.NewProc("BluetoothGetDeviceInfo")
	stereoSetService = stereoBthProps.NewProc("BluetoothSetServiceState")
)

type stereoBluetoothDevice struct {
	Size          uint32
	_             uint32
	Address       uint64
	Class         uint32
	Connected     int32
	Remembered    int32
	Authenticated int32
	LastSeen      windows.Systemtime
	LastUsed      windows.Systemtime
	Name          [248]uint16
}

// ReconnectNativeStereo cycles the A2DP service only on the supported Buds
// whose Microsoft driver has already been restored.
func ReconnectNativeStereo() error {
	stereoMu.Lock()
	defer stereoMu.Unlock()

	set, err := windows.SetupDiGetClassDevsEx(&mediaClass, "", 0, windows.DIGCF_PRESENT, 0, "")
	if err != nil {
		return err
	}
	defer set.Close()
	dev, err := findBudsStereo(set)
	if err != nil {
		return err
	}
	inf, err := stereoINF(set, dev)
	if err != nil {
		return err
	}
	if !strings.EqualFold(inf, windowsStereoINF) {
		return fmt.Errorf("cannot reconnect stock A2DP while %q is bound", inf)
	}
	id, err := set.DeviceInstanceID(dev)
	if err != nil {
		return err
	}
	// BthEnum's service instance ends in &<remote address>_C<instance>.
	instance := id[strings.LastIndexByte(id, '&')+1:]
	mac, _, ok := strings.Cut(instance, "_")
	if !ok || len(mac) != 12 {
		return errors.New("cannot identify the Buds Bluetooth address")
	}
	address, err := strconv.ParseUint(mac, 16, 48)
	if err != nil || address == 0 {
		return errors.New("invalid Buds Bluetooth address")
	}
	return reconnectStereoService(address)
}

func reconnectStereoService(address uint64) error {
	params := uint32(4)
	var radio windows.Handle
	find, _, callErr := stereoFindRadio.Call(uintptr(unsafe.Pointer(&params)), uintptr(unsafe.Pointer(&radio)))
	if find == 0 {
		return fmt.Errorf("find Bluetooth radio: %w", callErr)
	}
	defer stereoCloseFind.Call(find)
	for {
		info := stereoBluetoothDevice{Address: address}
		info.Size = uint32(unsafe.Sizeof(info))
		result, _, _ := stereoGetDevice.Call(uintptr(radio), uintptr(unsafe.Pointer(&info)))
		if result == 0 && info.Authenticated != 0 {
			err := cycleA2DP(radio, &info)
			windows.CloseHandle(radio)
			return err
		}
		windows.CloseHandle(radio)
		next, _, _ := stereoNextRadio.Call(find, uintptr(unsafe.Pointer(&radio)))
		if next == 0 {
			return errors.New("paired Buds not found on a Windows Bluetooth radio")
		}
	}
}

func cycleA2DP(radio windows.Handle, info *stereoBluetoothDevice) error {
	sink := windows.GUID{Data1: 0x110b, Data3: 0x1000, Data4: [8]byte{0x80, 0, 0, 0x80, 0x5f, 0x9b, 0x34, 0xfb}}
	set := func(enabled uintptr) windows.Errno {
		result, _, _ := stereoSetService.Call(uintptr(radio), uintptr(unsafe.Pointer(info)), uintptr(unsafe.Pointer(&sink)), enabled)
		return windows.Errno(result)
	}
	if result := set(0); result != 0 && uint32(result) != 0x80070057 {
		return fmt.Errorf("disable Buds A2DP: %w", result)
	}
	if result := set(1); result != 0 && uint32(result) != 0x80070057 {
		time.Sleep(500 * time.Millisecond)
		if retry := set(1); retry != 0 && uint32(retry) != 0x80070057 {
			return fmt.Errorf("re-enable Buds A2DP: %w", retry)
		}
	}
	return nil
}
