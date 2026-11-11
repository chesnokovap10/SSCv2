package driver

import (
	"crypto/sha1"
	"embed"
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"regexp"
	"unsafe"

	"golang.org/x/sys/windows"
	"golang.org/x/sys/windows/registry"
)

//go:embed payload/avdtp/SscAvdtpLocal.inf payload/avdtp/SscAvdtpLocal.sys payload/avdtp/sscavdtplocal.cat
//go:embed payload/wavert/SscBudsRender.inf payload/wavert/SscBudsRender.sys payload/wavert/sscbudsrender.cat
var nativeDriverFiles embed.FS

//go:embed payload/signer.cer
var nativeDriverSigner []byte

const nativeSignerTrustPrefix = "DriverSigner"

var (
	avdtpPackage = nativeDriverPackage{
		directory: "avdtp", inf: "SscAvdtpLocal.inf",
		sys: "SscAvdtpLocal.sys", catalog: "sscavdtplocal.cat",
	}
	waveRTPackage = nativeDriverPackage{
		directory: "wavert", inf: "SscBudsRender.inf",
		sys: "SscBudsRender.sys", catalog: "sscbudsrender.cat",
	}
	driverVersion = regexp.MustCompile(`(?im)^DriverVer[ \t]*=[^,\r\n]+,[ \t]*([0-9.]+)[ \t]*\r?$`)
	trustStores   = [...]string{"Root", "TrustedPublisher"}

	// Match the certificates by their Windows thumbprints when removing
	// trust recorded by versions with separate signers.
	legacyAVDTPSigner  = [...]byte{0x22, 0x50, 0x14, 0x46, 0x04, 0x28, 0x9d, 0x75, 0x50, 0x1d, 0xee, 0x18, 0x49, 0xff, 0x12, 0xea, 0x73, 0x63, 0xd7, 0xda}
	legacyWaveRTSigner = [...]byte{0xbb, 0xff, 0xc6, 0xfc, 0x41, 0xf3, 0x83, 0xc6, 0x42, 0x10, 0xcb, 0xfd, 0x2c, 0xca, 0x51, 0xe7, 0x59, 0x0a, 0x57, 0x89}
)

type nativeDriverPackage struct {
	directory, inf, sys, catalog string
}

func (p nativeDriverPackage) read(name string) ([]byte, error) {
	return nativeDriverFiles.ReadFile("payload/" + p.directory + "/" + name)
}

func (p nativeDriverPackage) version() (string, error) {
	data, err := p.read(p.inf)
	if err != nil {
		return "", err
	}
	match := driverVersion.FindSubmatch(data)
	if match == nil {
		return "", fmt.Errorf("missing DriverVer in embedded %s", p.inf)
	}
	return string(match[1]), nil
}

func (p nativeDriverPackage) extract(dir string) (string, error) {
	for _, name := range []string{p.inf, p.sys, p.catalog} {
		data, err := p.read(name)
		if err != nil {
			return "", err
		}
		if err := os.WriteFile(filepath.Join(dir, name), data, 0600); err != nil {
			return "", err
		}
	}
	return filepath.Join(dir, p.inf), nil
}

// withINF stages from a temporary directory under Program Files so unprivileged
// processes cannot replace the package before Windows imports it.
func (p nativeDriverPackage) withINF(stage func(string) error) error {
	programFiles, err := windows.KnownFolderPath(windows.FOLDERID_ProgramFiles, 0)
	if err != nil {
		return err
	}
	dir, err := os.MkdirTemp(programFiles, "SSCv2-native-driver-")
	if err != nil {
		return err
	}
	defer os.RemoveAll(dir)
	inf, err := p.extract(dir)
	if err != nil {
		return err
	}
	return stage(inf)
}

func installNativeDriverTrust(key registry.Key) error {
	if len(nativeDriverSigner) == 0 {
		return errors.New("empty native driver signer certificate")
	}
	cert, err := windows.CertCreateCertificateContext(windows.X509_ASN_ENCODING, &nativeDriverSigner[0], uint32(len(nativeDriverSigner)))
	if err != nil {
		return err
	}
	defer windows.CertFreeCertificateContext(cert)
	for _, name := range trustStores {
		if err := addNativeSignerTrust(key, name, cert); err != nil {
			return err
		}
	}
	return nil
}

func addNativeSignerTrust(key registry.Key, name string, cert *windows.CertContext) error {
	store, err := openNativeTrustStore(name)
	if err != nil {
		return err
	}
	defer windows.CertCloseStore(store, 0)
	var added *windows.CertContext
	err = windows.CertAddCertificateContextToStore(store, cert, windows.CERT_STORE_ADD_NEW, &added)
	if errors.Is(err, windows.Errno(windows.CRYPT_E_EXISTS)) {
		return nil
	}
	if err != nil {
		return err
	}
	if err := key.SetDWordValue(nativeSignerTrustPrefix+"Added"+name, 1); err != nil {
		return errors.Join(err, windows.CertDeleteCertificateFromStore(added))
	}
	return windows.CertFreeCertificateContext(added)
}

func removeNativeDriverTrust(key registry.Key) error {
	current := sha1.Sum(nativeDriverSigner)
	var err error
	for _, name := range trustStores {
		err = errors.Join(err,
			removeNativeSignerTrust(key, name, nativeSignerTrustPrefix+"Added"+name, current),
			removeNativeSignerTrust(key, name, "Added"+name, legacyAVDTPSigner),
			removeNativeSignerTrust(key, name, "WaveRTAdded"+name, legacyWaveRTSigner),
		)
	}
	return err
}

func removeNativeSignerTrust(key registry.Key, name, value string, thumbprint [sha1.Size]byte) error {
	_, _, err := key.GetIntegerValue(value)
	if errors.Is(err, registry.ErrNotExist) {
		return nil
	}
	if err != nil {
		return err
	}
	store, err := openNativeTrustStore(name)
	if err != nil {
		return err
	}
	defer windows.CertCloseStore(store, 0)
	hash := windows.CryptHashBlob{Size: uint32(len(thumbprint)), Data: &thumbprint[0]}
	match, err := windows.CertFindCertificateInStore(store, windows.X509_ASN_ENCODING, 0,
		windows.CERT_FIND_SHA1_HASH, unsafe.Pointer(&hash), nil)
	if err == nil {
		if err := windows.CertDeleteCertificateFromStore(match); err != nil {
			return err
		}
	} else if !errors.Is(err, windows.Errno(windows.CRYPT_E_NOT_FOUND)) {
		return err
	}
	return key.DeleteValue(value)
}

func openNativeTrustStore(name string) (windows.Handle, error) {
	return windows.CertOpenStore(windows.CERT_STORE_PROV_SYSTEM, 0, 0,
		windows.CERT_SYSTEM_STORE_LOCAL_MACHINE|windows.CERT_STORE_OPEN_EXISTING_FLAG,
		uintptr(unsafe.Pointer(windows.StringToUTF16Ptr(name))))
}
