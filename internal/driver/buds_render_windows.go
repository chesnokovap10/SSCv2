package driver

import (
	"errors"
	"fmt"
	"strings"
	"unsafe"

	"golang.org/x/sys/windows"
)

const budsRenderID = `ROOT\SSCBUDSRENDER`
const BudsRenderName = "SSCv2 Buds WaveRT"
const budsRenderService = "SscBudsRender"

func findBudsRender(set windows.DevInfo) (*windows.DevInfoData, error) {
	for i := 0; ; i++ {
		dev, err := set.EnumDeviceInfo(i)
		if errors.Is(err, windows.ERROR_NO_MORE_ITEMS) {
			return nil, nil
		}
		if err != nil {
			return nil, err
		}
		value, _ := set.DeviceRegistryProperty(dev, windows.SPDRP_HARDWAREID)
		ids, _ := value.([]string)
		for _, id := range ids {
			if strings.EqualFold(id, budsRenderID) {
				return dev, nil
			}
		}
	}
}

// EnsureBudsRender registers the independent audio device once.
func EnsureBudsRender() error {
	nativeProfileMu.Lock()
	defer nativeProfileMu.Unlock()
	stereoMu.Lock()
	defer stereoMu.Unlock()
	set, err := windows.SetupDiGetClassDevsEx(&mediaClass, "", 0, windows.DIGCF_PRESENT, 0, "")
	if err != nil {
		return err
	}
	defer set.Close()
	dev, err := findBudsRender(set)
	if err != nil {
		return err
	}
	version, err := waveRTPackage.version()
	if err != nil {
		return err
	}
	if dev != nil && strings.EqualFold(strProp(set, dev, windows.SPDRP_SERVICE), budsRenderService) {
		versionKey := driverINFProperty
		versionKey.PID = 3
		if installed, _ := windows.SetupDiGetDeviceProperty(set, dev, &versionKey); installed == version {
			return nil
		}
	}
	active, err := TestSigning()
	if err != nil {
		return err
	}
	if !active {
		return errors.New("Windows must be running in test-signing mode")
	}
	staged, err := stageBudsRender()
	if err != nil {
		return err
	}
	if dev == nil {
		dev, err = set.CreateDeviceInfo("SSCBUDSRENDER", &mediaClass, BudsRenderName, 0, windows.DICD_GENERATE_ID)
		if err != nil {
			return err
		}
		id := append(windows.StringToUTF16(budsRenderID), 0)
		if err := set.SetDeviceRegistryProperty(dev, windows.SPDRP_HARDWAREID, unsafe.Slice((*byte)(unsafe.Pointer(&id[0])), len(id)*2)); err != nil {
			return err
		}
		if err := set.CallClassInstaller(windows.DIF_REGISTERDEVICE, dev); err != nil {
			return err
		}
	}
	return installStereo(set, dev, staged, false)
}

func stageBudsRender() (string, error) {
	key, err := openProfileState()
	if err != nil {
		return "", err
	}
	defer key.Close()
	if err := installNativeDriverTrust(key); err != nil {
		return "", err
	}
	var staged string
	err = waveRTPackage.withINF(func(path string) error {
		var err error
		staged, err = stageStereoINF(path)
		return err
	})
	return staged, err
}

// removeBudsRender deletes the independent render device and its staged INF versions.
func removeBudsRender(packages []string) error {
	stereoMu.Lock()
	defer stereoMu.Unlock()
	set, err := windows.SetupDiGetClassDevsEx(&mediaClass, "", 0, 0, 0, "")
	if err != nil {
		return err
	}
	defer set.Close()
	dev, err := findBudsRender(set)
	if err != nil {
		return err
	}
	if dev != nil {
		id, err := set.DeviceInstanceID(dev)
		if err != nil {
			return err
		}
		if err := nativePnP("/remove-device", id); err != nil {
			return err
		}
	}
	for _, name := range packages {
		if err := nativePnP("/delete-driver", name, "/uninstall"); err != nil {
			return err
		}
	}
	return nil
}

// BudsRenderInterface finds the WaveRT interface on the independent Buds render device.
func BudsRenderInterface() (string, error) {
	set, err := windows.SetupDiGetClassDevsEx(&mediaClass, "", 0, windows.DIGCF_PRESENT, 0, "")
	if err != nil {
		return "", err
	}
	defer set.Close()
	dev, err := findBudsRender(set)
	if err != nil {
		return "", err
	}
	if dev == nil || !strings.EqualFold(strProp(set, dev, windows.SPDRP_SERVICE), budsRenderService) {
		return "", errors.New("SscBudsRender is not installed")
	}
	id, err := set.DeviceInstanceID(dev)
	if err != nil {
		return "", err
	}
	category := windows.GUID{Data1: 0x65e8773e, Data2: 0x8f56, Data3: 0x11d0,
		Data4: [8]byte{0xa3, 0xb9, 0, 0xa0, 0xc9, 0x22, 0x31, 0x96}}
	paths, err := windows.CM_Get_Device_Interface_List(id, &category, windows.CM_GET_DEVICE_INTERFACE_LIST_PRESENT)
	if err != nil {
		return "", err
	}
	if len(paths) != 1 {
		return "", fmt.Errorf("expected one Buds WaveRT interface, found %d", len(paths))
	}
	return paths[0], nil
}
