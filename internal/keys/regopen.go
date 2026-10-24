package keys

import (
	"sync"
	"unsafe"

	"golang.org/x/sys/windows"
	"golang.org/x/sys/windows/registry"
)

// BTHPORT\Parameters\Keys is readable only by SYSTEM. The helper service
// runs as SYSTEM; when it is not installed the UAC-elevated helper (an
// administrator) opens the keys with backup/restore semantics instead.

const regOptionBackupRestore = 0x4

var privOnce sync.Once

func enableBackupPrivileges() {
	privOnce.Do(func() {
		var tok windows.Token
		if err := windows.OpenProcessToken(windows.CurrentProcess(),
			windows.TOKEN_ADJUST_PRIVILEGES|windows.TOKEN_QUERY, &tok); err != nil {
			return
		}
		defer tok.Close()
		for _, name := range []string{"SeBackupPrivilege", "SeRestorePrivilege"} {
			var luid windows.LUID
			n, _ := windows.UTF16PtrFromString(name)
			if windows.LookupPrivilegeValue(nil, n, &luid) != nil {
				continue
			}
			tp := windows.Tokenprivileges{PrivilegeCount: 1}
			tp.Privileges[0] = windows.LUIDAndAttributes{Luid: luid, Attributes: windows.SE_PRIVILEGE_ENABLED}
			_ = windows.AdjustTokenPrivileges(tok, false, &tp, 0, nil, nil)
		}
	})
}

// openKey opens parent\path normally, falling back to backup semantics.
func openKey(parent registry.Key, path string, access uint32) (registry.Key, error) {
	k, err := registry.OpenKey(parent, path, access)
	if err == nil || err != windows.ERROR_ACCESS_DENIED {
		return k, err
	}
	enableBackupPrivileges()
	p, _ := windows.UTF16PtrFromString(path)
	var h windows.Handle
	if e := windows.RegOpenKeyEx(windows.Handle(parent), p, regOptionBackupRestore, access, &h); e != nil {
		return 0, err
	}
	return registry.Key(h), nil
}

var procRegCreateKeyExW = windows.NewLazySystemDLL("advapi32.dll").NewProc("RegCreateKeyExW")

// createKey creates/opens parent\path for writing, with the same fallback.
func createKey(parent registry.Key, path string, access uint32) (registry.Key, error) {
	k, _, err := registry.CreateKey(parent, path, access)
	if err == nil || err != windows.ERROR_ACCESS_DENIED {
		return k, err
	}
	enableBackupPrivileges()
	p, _ := windows.UTF16PtrFromString(path)
	var h windows.Handle
	var disp uint32
	r, _, _ := procRegCreateKeyExW.Call(uintptr(parent), uintptr(unsafePtr(p)), 0, 0,
		regOptionBackupRestore, uintptr(access), 0, uintptr(unsafePtr(&h)), uintptr(unsafePtr(&disp)))
	if r != 0 {
		return 0, err
	}
	return registry.Key(h), nil
}

func unsafePtr[T any](p *T) unsafe.Pointer { return unsafe.Pointer(p) }
