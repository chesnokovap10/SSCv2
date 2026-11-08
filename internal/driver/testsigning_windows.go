package driver

import (
	"fmt"
	"path/filepath"
	"strings"
	"sync"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
)

// TestSigning reports the running kernel's code-integrity policy. The BCD
// setting can already be different when a reboot is pending.
func TestSigning() (bool, error) {
	const testSigning = 0x02
	info := struct {
		Length  uint32
		Options uint32
	}{Length: 8}
	if err := windows.NtQuerySystemInformation(windows.SystemCodeIntegrityInformation,
		unsafe.Pointer(&info), info.Length, nil); err != nil {
		return false, fmt.Errorf("query Windows code integrity: %w", err)
	}
	return info.Options&testSigning != 0, nil
}

// SetTestSigning changes the current Windows boot entry. Windows applies
// the new policy on the next boot.
func SetTestSigning(enabled bool) error {
	systemDir, err := windows.GetSystemDirectory()
	if err != nil {
		return err
	}
	value := "off"
	if enabled {
		value = "on"
	}

	testSigningMu.Lock()
	defer testSigningMu.Unlock()
	out, err := run(15*time.Second, filepath.Join(systemDir, "bcdedit.exe"), "/set", "{current}", "testsigning", value)
	if err != nil {
		return fmt.Errorf("set Windows test signing %s: %w (%s)", value, err, strings.TrimSpace(out))
	}
	return nil
}

var testSigningMu sync.Mutex
