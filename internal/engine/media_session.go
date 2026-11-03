package engine

import (
	"fmt"
	"runtime"
	"syscall"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
	"sscv2/internal/logx"
)

var (
	combase                = windows.NewLazySystemDLL("combase.dll")
	roInitialize           = combase.NewProc("RoInitialize")
	roUninitialize         = combase.NewProc("RoUninitialize")
	roGetActivationFactory = combase.NewProc("RoGetActivationFactory")
	windowsCreateString    = combase.NewProc("WindowsCreateString")
	windowsDeleteString    = combase.NewProc("WindowsDeleteString")
	mediaManagerStaticsIID = windows.GUID{Data1: 0x2050c4ee, Data2: 0x11a0, Data3: 0x57de, Data4: [8]byte{0xae, 0xd7, 0xc9, 0x7c, 0x70, 0x33, 0x82, 0x45}}
	asyncInfoIID           = windows.GUID{Data1: 0x00000036, Data2: 0, Data3: 0, Data4: [8]byte{0xc0, 0, 0, 0, 0, 0, 0, 0x46}}
)

const (
	mediaNextTrack     = 16 // IGlobalSystemMediaTransportControlsSession::TrySkipNextAsync
	mediaPreviousTrack = 17
)

type mediaObject struct {
	vtable *[18]uintptr
}

func mediaResult(hr uintptr) error {
	if int32(hr) < 0 {
		return fmt.Errorf("HRESULT 0x%08x", uint32(hr))
	}
	return nil
}

func (obj *mediaObject) release() {
	syscall.SyscallN(obj.vtable[2], uintptr(unsafe.Pointer(obj)))
}

// WinRT async operations expose status through IAsyncInfo and their typed
// result through IAsyncOperation<T>. Bound the wait on the Bluetooth event loop.
func (obj *mediaObject) await(result unsafe.Pointer) error {
	var info *mediaObject
	hr, _, _ := syscall.SyscallN(obj.vtable[0], uintptr(unsafe.Pointer(obj)), uintptr(unsafe.Pointer(&asyncInfoIID)), uintptr(unsafe.Pointer(&info)))
	if err := mediaResult(hr); err != nil {
		return err
	}
	defer info.release()
	deadline := time.Now().Add(time.Second)
	for {
		var status int32
		hr, _, _ := syscall.SyscallN(info.vtable[7], uintptr(unsafe.Pointer(info)), uintptr(unsafe.Pointer(&status)))
		if err := mediaResult(hr); err != nil {
			return err
		}
		if status != 0 {
			hr, _, _ = syscall.SyscallN(obj.vtable[8], uintptr(unsafe.Pointer(obj)), uintptr(result))
			return mediaResult(hr)
		}
		if time.Now().After(deadline) {
			return fmt.Errorf("media session request timed out")
		}
		time.Sleep(5 * time.Millisecond)
	}
}

func mediaTrackCommand(slot int) {
	if err := skipMediaTrack(slot); err != nil {
		logx.Printf("media track command: %v", err)
	}
}

func skipMediaTrack(slot int) error {
	runtime.LockOSThread()
	defer runtime.UnlockOSThread()
	hr, _, _ := roInitialize.Call(1) // RO_INIT_MULTITHREADED
	if err := mediaResult(hr); err != nil {
		return err
	}
	defer roUninitialize.Call()

	name := windows.StringToUTF16("Windows.Media.Control.GlobalSystemMediaTransportControlsSessionManager")
	var class uintptr
	hr, _, _ = windowsCreateString.Call(uintptr(unsafe.Pointer(&name[0])), uintptr(len(name)-1), uintptr(unsafe.Pointer(&class)))
	if err := mediaResult(hr); err != nil {
		return err
	}
	defer windowsDeleteString.Call(class)

	var factory *mediaObject
	hr, _, _ = roGetActivationFactory.Call(class, uintptr(unsafe.Pointer(&mediaManagerStaticsIID)), uintptr(unsafe.Pointer(&factory)))
	if err := mediaResult(hr); err != nil {
		return err
	}
	defer factory.release()

	var request *mediaObject
	hr, _, _ = syscall.SyscallN(factory.vtable[6], uintptr(unsafe.Pointer(factory)), uintptr(unsafe.Pointer(&request))) // RequestAsync
	if err := mediaResult(hr); err != nil {
		return err
	}
	defer request.release()
	var manager *mediaObject
	if err := request.await(unsafe.Pointer(&manager)); err != nil {
		return err
	}
	defer manager.release()

	var session *mediaObject
	hr, _, _ = syscall.SyscallN(manager.vtable[6], uintptr(unsafe.Pointer(manager)), uintptr(unsafe.Pointer(&session))) // GetCurrentSession
	if err := mediaResult(hr); err != nil {
		return err
	}
	if session == nil {
		return fmt.Errorf("no active Windows media session")
	}
	defer session.release()

	var operation *mediaObject
	hr, _, _ = syscall.SyscallN(session.vtable[slot], uintptr(unsafe.Pointer(session)), uintptr(unsafe.Pointer(&operation)))
	if err := mediaResult(hr); err != nil {
		return err
	}
	defer operation.release()
	var accepted uint8
	if err := operation.await(unsafe.Pointer(&accepted)); err != nil {
		return err
	}
	if accepted == 0 {
		return fmt.Errorf("the player declined the track change")
	}
	logx.Dbgf("media", "track change accepted (slot %d)", slot)
	return nil
}
