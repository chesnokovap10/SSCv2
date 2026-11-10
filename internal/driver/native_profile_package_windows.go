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
	"unsafe"

	"golang.org/x/sys/windows"
	"golang.org/x/sys/windows/registry"

	packagefiles "sscv2/driver/native-bt"
)

const (
	nativeProfileKey = `SOFTWARE\SSCv2\NativeBluetooth`
	profileRequested = "Requested"
	profileINF       = "SscAvdtpLocal.inf"
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
		return nil
	}
	active, err := TestSigning()
	if err != nil || !active {
		return err
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
	return SetLocalProfile(true)
}

func stageNativeProfile(key registry.Key) error {
	cert, err := profileCertificate()
	if err != nil {
		return err
	}
	defer windows.CertFreeCertificateContext(cert)
	for _, store := range []string{"Root", "TrustedPublisher"} {
		if err := manageProfileTrust(key, store, cert, true); err != nil {
			return err
		}
	}
	programFiles, err := windows.KnownFolderPath(windows.FOLDERID_ProgramFiles, 0)
	if err != nil {
		return err
	}
	dir, err := os.MkdirTemp(filepath.Join(programFiles, "SSCv2"), "native-driver-")
	if err != nil {
		return err
	}
	defer os.RemoveAll(dir)
	for _, name := range []string{profileINF, "SscAvdtpLocal.sys", "sscavdtplocal.cat"} {
		data, err := packagefiles.Files.ReadFile("local-package/" + name)
		if err != nil {
			return err
		}
		if err := os.WriteFile(filepath.Join(dir, name), data, 0600); err != nil {
			return err
		}
	}
	return nativePnP("/add-driver", filepath.Join(dir, profileINF), "/install")
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
	var packages []string
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
	cert, err := profileCertificate()
	if err != nil {
		return err
	}
	defer windows.CertFreeCertificateContext(cert)
	return errors.Join(
		manageProfileTrust(key, "TrustedPublisher", cert, false),
		manageProfileTrust(key, "Root", cert, false),
	)
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

func profileCertificate() (*windows.CertContext, error) {
	data, err := packagefiles.Files.ReadFile("local-package/signer.cer")
	if err != nil {
		return nil, err
	}
	return windows.CertCreateCertificateContext(windows.X509_ASN_ENCODING, &data[0], uint32(len(data)))
}

func manageProfileTrust(key registry.Key, name string, cert *windows.CertContext, enable bool) error {
	value := "Added" + name
	if !enable {
		_, _, err := key.GetIntegerValue(value)
		if errors.Is(err, registry.ErrNotExist) {
			return nil
		}
		if err != nil {
			return err
		}
	}
	store, err := windows.CertOpenStore(windows.CERT_STORE_PROV_SYSTEM, 0, 0,
		windows.CERT_SYSTEM_STORE_LOCAL_MACHINE|windows.CERT_STORE_OPEN_EXISTING_FLAG,
		uintptr(unsafe.Pointer(windows.StringToUTF16Ptr(name))))
	if err != nil {
		return err
	}
	defer windows.CertCloseStore(store, 0)
	if enable {
		var added *windows.CertContext
		err := windows.CertAddCertificateContextToStore(store, cert, windows.CERT_STORE_ADD_NEW, &added)
		if errors.Is(err, windows.Errno(windows.CRYPT_E_EXISTS)) {
			return nil
		}
		if err != nil {
			return err
		}
		if err := key.SetDWordValue(value, 1); err != nil {
			return errors.Join(err, windows.CertDeleteCertificateFromStore(added))
		}
		return windows.CertFreeCertificateContext(added)
	}
	match, err := windows.CertFindCertificateInStore(store, windows.X509_ASN_ENCODING, 0,
		windows.CERT_FIND_EXISTING, unsafe.Pointer(cert), nil)
	if err == nil {
		if err := windows.CertDeleteCertificateFromStore(match); err != nil {
			return err
		}
	} else if !errors.Is(err, windows.Errno(windows.CRYPT_E_NOT_FOUND)) {
		return err
	}
	return key.DeleteValue(value)
}
