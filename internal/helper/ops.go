// Package helper performs the privileged operations (driver switch, reading
// and writing the Windows Bluetooth keys, installing the virtual headphones
// driver). They run inside the helper service (LocalSystem, no UAC prompts)
// or, when the service is not installed, in a UAC-elevated copy of ssc.exe.
package helper

import (
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"

	"sscv2/internal/audio"
	"sscv2/internal/driver"
	"sscv2/internal/i18n"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
	"sscv2/internal/logx"
	"sscv2/internal/vbcable"
)

// Handle executes one request. Inputs are validated: the service must not
// become a way to rebind arbitrary devices or write arbitrary registry data.
func Handle(req ipc.Request) (resp ipc.Response) {
	if req.Debug {
		stop := logx.Capture()
		defer func() { resp.Log = stop() }()
	}
	defer func() {
		if r := recover(); r != nil {
			resp = ipc.Response{Error: fmt.Sprintf(i18n.T("внутренняя ошибка: %v", "internal error: %v"), r)}
		}
	}()
	if req.Lang != "" {
		i18n.Set(req.Lang)
	}
	logx.Printf("helper: op=%s", req.Op)
	resp = ipc.Response{Version: ipc.Version}
	fail := func(err error) ipc.Response {
		logx.Printf("helper: %s failed: %v", req.Op, err)
		resp.Error = err.Error()
		return resp
	}
	switch req.Op {
	case "ping":
		resp.OK = true
	case "driver":
		driver.Logf = logx.Printf
		t0 := time.Now()
		defer func() { logx.Printf("helper: driver op took %s", time.Since(t0).Round(time.Millisecond)) }()
		id := driver.USBID{VID: req.VID, PID: req.PID}
		known := false
		for _, k := range driver.KnownMediaTek {
			if k == id {
				known = true
			}
		}
		if !known {
			return fail(fmt.Errorf(i18n.T("устройство %s не из списка поддерживаемых MediaTek", "device %s is not a supported MediaTek adapter"), id))
		}
		driver.Variant = req.Variant
		r, err := driver.Switch(id, req.WinUSB)
		if err != nil {
			return fail(err)
		}
		resp.OK, resp.Message = true, r.Message
	case "keys-read":
		bonds, err := keys.ReadWindows()
		if err != nil {
			return fail(err)
		}
		resp.Data, _ = json.Marshal(bonds)
		resp.OK = true
	case "keys-write":
		if err := keys.WriteWindowsClassic(req.Adapter, req.Device, req.Key); err != nil {
			return fail(err)
		}
		resp.OK = true
	case "virtual-install":
		msg, err := installVirtual(req.Name)
		if err != nil {
			return fail(err)
		}
		resp.OK, resp.Message = true, msg
	case "virtual-uninstall":
		msg, err := uninstallVirtual()
		if err != nil {
			return fail(err)
		}
		resp.OK, resp.Message = true, msg
	case "virtual-brand":
		if err := audio.InitCOM(); err != nil {
			return fail(err)
		}
		if err := brandVirtual(req.Name); err != nil {
			return fail(err)
		}
		resp.OK = true
	default:
		return fail(fmt.Errorf(i18n.T("неизвестная операция %q", "unknown operation %q"), req.Op))
	}
	return resp
}

// ---- virtual headphones device (VB-CABLE) ------------------------------------

var (
	guidDevClassMedia = windows.GUID{Data1: 0x4d36e96c, Data2: 0xe325, Data3: 0x11ce, Data4: [8]byte{0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18}}
	newdev            = windows.NewLazySystemDLL("newdev.dll")
	procUpdateDriver  = newdev.NewProc("UpdateDriverForPlugAndPlayDevicesW")
	setupapi          = windows.NewLazySystemDLL("setupapi.dll")
	procUninstallOEM  = setupapi.NewProc("SetupUninstallOEMInfW")
	cableFiles        = vbcable.Files
)

func verifySignature(path string) error {
	p, _ := windows.UTF16PtrFromString(path)
	fi := &windows.WinTrustFileInfo{Size: uint32(unsafe.Sizeof(windows.WinTrustFileInfo{})), FilePath: p}
	data := &windows.WinTrustData{
		Size:                            uint32(unsafe.Sizeof(windows.WinTrustData{})),
		UIChoice:                        windows.WTD_UI_NONE,
		RevocationChecks:                windows.WTD_REVOKE_NONE,
		UnionChoice:                     windows.WTD_CHOICE_FILE,
		StateAction:                     windows.WTD_STATEACTION_VERIFY,
		FileOrCatalogOrBlobOrSgnrOrCert: unsafe.Pointer(fi),
	}
	err := windows.WinVerifyTrustEx(windows.InvalidHWND, &windows.WINTRUST_ACTION_GENERIC_VERIFY_V2, data)
	data.StateAction = windows.WTD_STATEACTION_CLOSE
	windows.WinVerifyTrustEx(windows.InvalidHWND, &windows.WINTRUST_ACTION_GENERIC_VERIFY_V2, data)
	return err
}

// cableNodes calls fn for every devnode carrying the cable hardware id.
func cableNodes(includeAbsent bool, fn func(set windows.DevInfo, d *windows.DevInfoData)) int {
	flags := windows.DIGCF(0)
	if !includeAbsent {
		flags = windows.DIGCF_PRESENT
	}
	set, err := windows.SetupDiGetClassDevsEx(&guidDevClassMedia, "", 0, flags, 0, "")
	if err != nil {
		return 0
	}
	defer set.Close()
	n := 0
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
		for _, h := range ids {
			if strings.EqualFold(h, audio.CableHardwareID) {
				n++
				fn(set, d)
				break
			}
		}
	}
	return n
}

// installVirtual installs the embedded VB-CABLE driver (or, when the device
// already exists, only renames it after the headphones).
func installVirtual(name string) (string, error) {
	if err := audio.InitCOM(); err == nil && audio.VirtualInstalled() {
		if name == "" || audio.HeadphonesName() == name {
			return i18n.T("виртуальные наушники уже установлены", "the virtual headphones are already installed"), nil
		}
		if err := brandVirtual(name); err != nil {
			return "", fmt.Errorf(i18n.T("переименование: %w", "renaming: %w"), err)
		}
		return i18n.T("виртуальные наушники переименованы в ", "the virtual headphones were renamed to ") + name, nil
	}
	dir, err := vbcable.Extract()
	if err != nil {
		return "", fmt.Errorf(i18n.T("распаковка драйвера: %w", "unpacking the driver: %w"), err)
	}
	defer os.RemoveAll(dir)
	if err := verifySignature(filepath.Join(dir, cableFiles[2])); err != nil {
		return "", fmt.Errorf(i18n.T("подпись каталога драйвера не доверена: %v", "the driver catalog signature is not trusted: %v"), err)
	}
	if cableNodes(false, func(windows.DevInfo, *windows.DevInfoData) {}) == 0 {
		set, err := windows.SetupDiCreateDeviceInfoListEx(&guidDevClassMedia, 0, "")
		if err != nil {
			return "", err
		}
		d, err := set.CreateDeviceInfo("MEDIA", &guidDevClassMedia, audio.CableAdapter, 0, windows.DICD_GENERATE_ID)
		if err == nil {
			hwid := windows.StringToUTF16(audio.CableHardwareID)
			hwid = append(hwid, 0) // REG_MULTI_SZ double NUL
			buf := unsafe.Slice((*byte)(unsafe.Pointer(&hwid[0])), len(hwid)*2)
			if err = set.SetDeviceRegistryProperty(d, windows.SPDRP_HARDWAREID, buf); err == nil {
				err = set.CallClassInstaller(windows.DIF_REGISTERDEVICE, d)
			}
		}
		set.Close()
		if err != nil {
			return "", fmt.Errorf(i18n.T("создание виртуального устройства: %w", "creating the virtual device: %w"), err)
		}
	}
	hw, _ := windows.UTF16PtrFromString(audio.CableHardwareID)
	inf, _ := windows.UTF16PtrFromString(filepath.Join(dir, cableFiles[0]))
	var reboot int32
	r, _, e := procUpdateDriver.Call(0, uintptr(unsafe.Pointer(hw)), uintptr(unsafe.Pointer(inf)), 1 /* INSTALLFLAG_FORCE */, uintptr(unsafe.Pointer(&reboot)))
	if r == 0 {
		return "", fmt.Errorf(i18n.T("установка драйвера: %v", "installing the driver: %v"), e)
	}
	msg := i18n.T("виртуальное устройство установлено", "virtual device installed")
	if err := audio.InitCOM(); err == nil {
		for i := 0; i < 40; i++ {
			if audio.VirtualInstalled() {
				break
			}
			time.Sleep(250 * time.Millisecond)
		}
		if name != "" {
			if err := brandVirtual(name); err != nil {
				msg += i18n.T("; переименовать не удалось: ", "; renaming failed: ") + err.Error()
			}
		}
		_ = audio.SetVirtualVisible(false)
	}
	if reboot != 0 {
		msg += i18n.T(" (нужна перезагрузка)", " (restart needed)")
	}
	return msg, nil
}

func brandVirtual(name string) error {
	if strings.TrimSpace(name) == "" {
		return errors.New(i18n.T("пустое имя", "empty name"))
	}
	_ = audio.SetVirtualVisible(true)
	defer audio.SetVirtualVisible(false)
	return audio.BrandVirtual(name)
}

func uninstallVirtual() (string, error) {
	removed := cableNodes(true, func(set windows.DevInfo, d *windows.DevInfoData) {
		_ = set.CallClassInstaller(windows.DIF_REMOVE, d)
	})
	infs, _ := filepath.Glob(filepath.Join(os.Getenv("WINDIR"), "INF", "oem*.inf"))
	pk := 0
	for _, f := range infs {
		b, err := os.ReadFile(f)
		if err != nil || !strings.Contains(string(b), audio.CableHardwareID) {
			continue
		}
		n, _ := windows.UTF16PtrFromString(filepath.Base(f))
		if r, _, _ := procUninstallOEM.Call(uintptr(unsafe.Pointer(n)), 1 /* SUOI_FORCEDELETE */, 0); r != 0 {
			pk++
		}
	}
	return fmt.Sprintf(i18n.T("удалено устройств: %d, пакетов драйвера: %d", "removed devices: %d, driver packages: %d"), removed, pk), nil
}
