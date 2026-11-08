package driver

import (
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"sync"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
)

const (
	budsStereoHardwareID = `BTHENUM\{0000110b-0000-1000-8000-00805f9b34fb}_VID&00010075_PID&a013`
	windowsStereoINF     = "microsoft_bluetooth_a2dp_src.inf"
	probeStereoService   = "SscAvdtpProbe"
)

var (
	stereoMu          sync.Mutex
	mediaClass        = windows.GUID{Data1: 0x4d36e96c, Data2: 0xe325, Data3: 0x11ce, Data4: [8]byte{0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18}}
	driverINFProperty = windows.DEVPROPKEY{FmtID: windows.DEVPROPGUID{Data1: 0xa8b865dd, Data2: 0x2e3d, Data3: 0x4094, Data4: [8]byte{0xad, 0x97, 0xe5, 0x93, 0xa7, 0x0c, 0x75, 0xd6}}, PID: 5}
	copyOEMInf        = windows.NewLazySystemDLL("setupapi.dll").NewProc("SetupCopyOEMInfW")
	installDevice     = windows.NewLazySystemDLL("newdev.dll").NewProc("DiInstallDevice")
)

// SwitchNativeStereo changes only the Buds2 Pro Stereo devnode. The package
// must have been provisioned by an administrator in the SSCv2 install folder.
func SwitchNativeStereo(enable bool) error {
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
	current, err := stereoINF(set, dev)
	if err != nil {
		return err
	}
	if !enable {
		if strings.EqualFold(current, windowsStereoINF) {
			return setStereoState(set, dev, windows.DICS_ENABLE)
		}
		if !strings.EqualFold(strProp(set, dev, windows.SPDRP_SERVICE), probeStereoService) {
			return fmt.Errorf("refusing to remove unexpected stereo driver %q", current)
		}
		return restoreStereo(set, dev, current)
	}
	if !strings.EqualFold(current, windowsStereoINF) {
		return fmt.Errorf("expected Windows A2DP before switching, found %q", current)
	}
	active, err := TestSigning()
	if err != nil {
		return err
	}
	if !active {
		return errors.New("Windows must be running in test-signing mode")
	}
	programFiles, err := windows.KnownFolderPath(windows.FOLDERID_ProgramFiles, 0)
	if err != nil {
		return err
	}
	source := filepath.Join(programFiles, "SSCv2", "native-bt", "SscAvdtpProbe.inf")
	staged, err := stageStereoINF(source)
	if err != nil {
		return err
	}
	if err := bindStereo(set, dev, staged); err != nil {
		return errors.Join(err, restoreStereo(set, dev, filepath.Base(staged)))
	}
	return nil
}

func findBudsStereo(set windows.DevInfo) (*windows.DevInfoData, error) {
	var match *windows.DevInfoData
	for i := 0; ; i++ {
		dev, err := set.EnumDeviceInfo(i)
		if errors.Is(err, windows.ERROR_NO_MORE_ITEMS) {
			break
		}
		if err != nil {
			return nil, err
		}
		value, err := set.DeviceRegistryProperty(dev, windows.SPDRP_HARDWAREID)
		ids, _ := value.([]string)
		if err != nil {
			continue
		}
		for _, id := range ids {
			if strings.EqualFold(id, budsStereoHardwareID) {
				if match != nil {
					return nil, errors.New("multiple Buds2 Pro Stereo devices are present")
				}
				match = dev
				break
			}
		}
	}
	if match == nil {
		return nil, errors.New("Buds2 Pro Stereo device is not present")
	}
	return match, nil
}

func stereoINF(set windows.DevInfo, dev *windows.DevInfoData) (string, error) {
	value, err := windows.SetupDiGetDeviceProperty(set, dev, &driverINFProperty)
	if err != nil {
		return "", err
	}
	inf, ok := value.(string)
	if !ok || inf == "" {
		return "", errors.New("stereo device has no driver INF")
	}
	return inf, nil
}

func stageStereoINF(source string) (string, error) {
	if _, err := os.Stat(source); err != nil {
		return "", fmt.Errorf("native Bluetooth package: %w", err)
	}
	path, err := windows.UTF16PtrFromString(source)
	if err != nil {
		return "", err
	}
	var destination [windows.MAX_PATH]uint16
	const sourceMediaPath = 1
	result, _, callErr := copyOEMInf.Call(uintptr(unsafe.Pointer(path)), 0, sourceMediaPath, 0,
		uintptr(unsafe.Pointer(&destination[0])), uintptr(len(destination)), 0, 0)
	if result == 0 {
		return "", fmt.Errorf("stage native Bluetooth package: %w", callErr)
	}
	return windows.UTF16ToString(destination[:]), nil
}

func setStereoState(set windows.DevInfo, dev *windows.DevInfoData, state windows.DICS_STATE) error {
	change := windows.PropChangeParams{
		ClassInstallHeader: *windows.MakeClassInstallHeader(windows.DIF_PROPERTYCHANGE),
		StateChange:        state, Scope: windows.DICS_FLAG_GLOBAL,
	}
	if err := set.SetClassInstallParams(dev, &change.ClassInstallHeader, uint32(unsafe.Sizeof(change))); err != nil {
		return err
	}
	return set.CallClassInstaller(windows.DIF_PROPERTYCHANGE, dev)
}

func bindStereo(set windows.DevInfo, dev *windows.DevInfoData, inf string) error {
	params, err := set.DeviceInstallParams(dev)
	if err != nil {
		return err
	}
	params.Flags |= windows.DI_ENUMSINGLEINF | windows.DI_QUIETINSTALL
	params.FlagsEx |= windows.DI_FLAGSEX_ALLOWEXCLUDEDDRVS
	if err := params.SetDriverPath(inf); err != nil {
		return err
	}
	if err := set.SetDeviceInstallParams(dev, params); err != nil {
		return err
	}
	if err := set.BuildDriverInfoList(dev, windows.SPDIT_COMPATDRIVER); err != nil {
		return err
	}
	candidate, err := set.EnumDriverInfo(dev, windows.SPDIT_COMPATDRIVER, 0)
	if err != nil {
		return err
	}
	if err := setStereoState(set, dev, windows.DICS_DISABLE); err != nil {
		return fmt.Errorf("disable Buds stereo: %w", err)
	}
	var reboot uint32
	result, _, callErr := installDevice.Call(0, uintptr(set), uintptr(unsafe.Pointer(dev)),
		uintptr(unsafe.Pointer(candidate)), 0, uintptr(unsafe.Pointer(&reboot)))
	if result == 0 {
		return fmt.Errorf("bind native Bluetooth driver: %w", callErr)
	}
	if reboot != 0 {
		return errors.New("Windows requested a restart to switch the stereo driver")
	}
	if err := setStereoState(set, dev, windows.DICS_ENABLE); err != nil {
		return fmt.Errorf("enable Buds stereo: %w", err)
	}
	current, err := stereoINF(set, dev)
	if err != nil {
		return err
	}
	if !strings.EqualFold(current, filepath.Base(inf)) {
		return fmt.Errorf("native driver did not bind: %s", current)
	}
	return nil
}

func restoreStereo(set windows.DevInfo, dev *windows.DevInfoData, published string) error {
	name := strings.ToLower(published)
	if len(name) < 8 || !strings.HasPrefix(name, "oem") || !strings.HasSuffix(name, ".inf") ||
		strings.Trim(name[3:len(name)-4], "0123456789") != "" {
		return fmt.Errorf("invalid published driver name: %q", published)
	}
	systemDir, err := windows.GetSystemDirectory()
	if err != nil {
		return err
	}
	pnp := filepath.Join(systemDir, "pnputil.exe")
	out, removeErr := run(45*time.Second, pnp, "/delete-driver", name, "/uninstall")
	if removeErr != nil {
		removeErr = fmt.Errorf("remove native Bluetooth package: %w (%s)", removeErr, strings.TrimSpace(out))
	}
	_, scanErr := run(30*time.Second, pnp, "/scan-devices")
	enableErr := setStereoState(set, dev, windows.DICS_ENABLE)
	restored, readErr := stereoINF(set, dev)
	if readErr == nil && !strings.EqualFold(restored, windowsStereoINF) {
		readErr = fmt.Errorf("expected Windows A2DP after rollback, found %q", restored)
	}
	return errors.Join(removeErr, scanErr, enableErr, readErr)
}
