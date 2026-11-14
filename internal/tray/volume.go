package tray

import (
	"syscall"
	"unsafe"
)

const volumeKeyMsg = wmApp + 2

var (
	setWindowsHook     = user32.NewProc("SetWindowsHookExW")
	unhookWindowsHook  = user32.NewProc("UnhookWindowsHookEx")
	callNextHook       = user32.NewProc("CallNextHookEx")
	volumeHookCallback = syscall.NewCallback(volumeHook)
)

func (t *Tray) SetVolumeKeys(enabled bool) {
	t.volumeKeys.Store(enabled)
}

// The hook only intercepts the three volume keys while loopback owns audio.
// Post to the window so the hook never waits for IPC or file I/O.
func volumeHook(code, message uintptr, data *uint32) uintptr {
	t := current
	if int32(code) == 0 && t != nil && t.volumeKeys.Load() {
		key := *data
		if key == 0xad || key == 0xae || key == 0xaf {
			if message == 0x100 || message == 0x104 {
				pPostMessageW.Call(t.hwnd, volumeKeyMsg, uintptr(key), 0)
			}
			return 1
		}
	}
	result, _, _ := callNextHook.Call(0, code, message, uintptr(unsafe.Pointer(data)))
	return result
}
