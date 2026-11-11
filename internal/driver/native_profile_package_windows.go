package driver

import (
	"bytes"
	"errors"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"regexp"
	"strings"
	"sync"
	"time"

	"golang.org/x/sys/windows"
	"golang.org/x/sys/windows/registry"
)

const (
	nativeProfileKey = `SOFTWARE\SSCv2\NativeBluetooth`
	profileRequested = "Requested"
)

var (
	nativeProfileMu sync.Mutex
	profileStaged   bool
	oemINF          = regexp.MustCompile(`(?i)^oem[0-9]+\.inf$`)
)

func openProfileState() (registry.Key, error) {
	key, _, err := registry.CreateKey(registry.LOCAL_MACHINE, nativeProfileKey, registry.QUERY_VALUE|registry.SET_VALUE)
	return key, err
}

// ConfigureNativeProfile persists the request for the automatic helper at boot.
func ConfigureNativeProfile(enable bool) error {
	nativeProfileMu.Lock()
	defer nativeProfileMu.Unlock()
	key, err := openProfileState()
	if err != nil {
		return err
	}
	defer key.Close()
	if !enable {
		if err := removeNativeProfile(key); err != nil {
			return err
		}
	}
	if err := SetTestSigning(enable); err != nil {
		return err
	}
	var requested uint32
	if enable {
		requested = 1
	}
	return key.SetDWordValue(profileRequested, requested)
}

// SyncNativeProfile runs from the automatic helper and before a native stream.
// adopt records the preference of installations upgraded from before this state
// was stored in HKLM. An explicit disable always takes precedence.
func SyncNativeProfile(adopt bool) error {
	nativeProfileMu.Lock()
	defer nativeProfileMu.Unlock()
	key, err := openProfileState()
	if err != nil {
		return err
	}
	defer key.Close()
	requested, _, err := key.GetIntegerValue(profileRequested)
	if errors.Is(err, registry.ErrNotExist) {
		if !adopt {
			return nil
		}
		if err := key.SetDWordValue(profileRequested, 1); err != nil {
			return err
		}
		requested = 1
	} else if err != nil {
		return err
	}
	if requested == 0 {
		if adopt {
			return errors.New("native Bluetooth driver is disabled")
		}
		// An earlier version could leave the WaveRT device installed after
		// recording an explicit disable. Finish the cleanup on service startup.
		return removeNativeProfile(key)
	}
	active, err := TestSigning()
	if err != nil || !active {
		return err
	}
	if adapter, ok := FindAdapter(USBID{}); ok && adapter.Mode == WinUSB {
		if !adopt {
			return nil // the tray will sync after handing the radio back to Windows
		}
		return errors.New("the adapter is still in WinUSB mode")
	}
	if !profileStaged {
		if err := stageNativeProfile(key); err != nil {
			return err
		}
		profileStaged = true
	}
	paths, err := LocalProfileInterfaces()
	if err != nil || len(paths) > 0 {
		return err
	}
	// The USB driver can be restored before Windows exposes its Bluetooth radio.
	deadline := time.Now().Add(3 * time.Second)
	for {
		err := SetLocalProfile(true)
		if (!errors.Is(err, windows.ERROR_BAD_UNIT) && !errors.Is(err, windows.ERROR_DEVICE_NOT_CONNECTED)) || time.Now().After(deadline) {
			return err
		}
		time.Sleep(100 * time.Millisecond)
	}
}

func stageNativeProfile(key registry.Key) error {
	if err := installNativeDriverTrust(key); err != nil {
		return err
	}
	return avdtpPackage.withINF(func(path string) error {
		err := nativePnP("/add-driver", path, "/install")
		var exit *exec.ExitError
		if errors.As(err, &exit) && exit.ExitCode() == int(windows.ERROR_NO_MORE_ITEMS) {
			// Registering the Bluetooth profile creates the matching PnP node.
			return nativePnP("/add-driver", path)
		}
		return err
	})
}

func removeNativeProfile(key registry.Key) error {
	profileStaged = false
	systemDir, err := windows.GetSystemDirectory()
	if err != nil {
		return err
	}
	infDir := filepath.Join(systemDir, "..", "INF")
	files, err := os.ReadDir(infDir)
	if err != nil {
		return err
	}
	var packages, renderPackages []string
	for _, file := range files {
		if !oemINF.MatchString(file.Name()) {
			continue
		}
		data, err := os.ReadFile(filepath.Join(infDir, file.Name()))
		if err != nil {
			return err
		}
		// Windows may store the published INF as UTF-16. The identity
		// fields in this package are ASCII in either encoding.
		inf := strings.ToLower(string(bytes.ReplaceAll(data, []byte{0}, nil)))
		if strings.Contains(inf, `bthenum\{80cbb510-404f-4d4e-94a7-255e052fb31b}`) &&
			strings.Contains(inf, "addservice=sscavdtplocal,") {
			packages = append(packages, file.Name())
		}
		if strings.Contains(inf, strings.ToLower(budsRenderID)) && strings.Contains(inf, "addservice=sscbudsrender,") {
			renderPackages = append(renderPackages, file.Name())
		}
	}
	if err := removeBudsRender(renderPackages); err != nil {
		return err
	}
	if len(packages) != 0 {
		if err := SetLocalProfile(false); err != nil {
			return err
		}
		for _, name := range packages {
			if err := nativePnP("/delete-driver", name, "/uninstall"); err != nil {
				return err
			}
		}
	}
	return removeNativeDriverTrust(key)
}

func nativePnP(args ...string) error {
	systemDir, err := windows.GetSystemDirectory()
	if err != nil {
		return err
	}
	out, err := run(60*time.Second, filepath.Join(systemDir, "pnputil.exe"), args...)
	var exit *exec.ExitError
	if err == nil || errors.As(err, &exit) && exit.ExitCode() == 3010 {
		return nil
	}
	return fmt.Errorf("pnputil %s: %w (%s)", args[0], err, strings.TrimSpace(out))
}
