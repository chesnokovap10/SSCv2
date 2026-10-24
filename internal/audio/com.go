// Package audio talks to the Windows audio stack through raw COM calls:
// WASAPI loopback/capture, endpoint volume (with change notifications),
// IPolicyConfig (default device, endpoint visibility, rename) and the
// VB-CABLE based "virtual headphones" device.
package audio

import (
	"errors"
	"fmt"
	"runtime"
	"sync"
	"syscall"
	"unsafe"

	"golang.org/x/sys/windows"
)

var (
	ole32                = windows.NewLazySystemDLL("ole32.dll")
	procCoCreateInstance = ole32.NewProc("CoCreateInstance")
	procCoTaskMemFree    = ole32.NewProc("CoTaskMemFree")
	procPropVariantClear = ole32.NewProc("PropVariantClear")
	procCoInitializeEx   = ole32.NewProc("CoInitializeEx")
)

const (
	clsctxAll         = 0x17
	coinitMultithread = 0x0
	sOK               = 0
	sFalse            = 1
)

func guid(s string) windows.GUID {
	g, err := windows.GUIDFromString(s)
	if err != nil {
		panic(err)
	}
	return g
}

var (
	clsidMMDeviceEnumerator   = guid("{BCDE0395-E52F-467C-8E3D-C4579291692E}")
	iidIMMDeviceEnumerator    = guid("{A95664D2-9614-4F35-A746-DE8DB63617E6}")
	iidIAudioClient           = guid("{1CB9AD4C-DBFA-4c32-B178-C2F568A703B2}")
	iidIAudioCaptureClient    = guid("{C8ADBD64-E71E-48a0-A4DE-185C395CD317}")
	iidIAudioEndpointVolume   = guid("{5CDF2C82-841E-4546-9722-0CF74078229A}")
	iidIAudioEndpointVolumeCb = guid("{657804FA-D6AD-4496-8A60-352752AF4F89}")
	iidIMMEndpoint            = guid("{1BE09788-6894-4089-8586-9A2A6C265AC5}")
	iidIUnknown               = guid("{00000000-0000-0000-C000-000000000046}")
	clsidPolicyConfigClient   = guid("{870af99c-171d-4f9e-af0d-e63df40c2bc9}")
	iidIPolicyConfig10        = guid("{568b9108-44bf-40b4-92d0-968cf737f7d7}")
	iidIPolicyConfig7         = guid("{f8679f50-850a-41cf-9c72-430f290290c8}")
	subtypeFloat              = guid("{00000003-0000-0010-8000-00aa00389b71}")
)

// PROPERTYKEY
type propKey struct {
	fmtid windows.GUID
	pid   uint32
}

var (
	pkeyDeviceFriendlyName          = propKey{guid("{a45c254e-df1c-4efd-8020-67d146a850e0}"), 14}
	pkeyDeviceDesc                  = propKey{guid("{a45c254e-df1c-4efd-8020-67d146a850e0}"), 2}
	pkeyDeviceInterfaceFriendlyName = propKey{guid("{026e516e-b814-414b-83cd-856d6fef4822}"), 2}
)

// PROPVARIANT (x64: 24 bytes)
type propVariant struct {
	vt       uint16
	_        [3]uint16
	val      uintptr
	_        uintptr
}

const vtLPWSTR = 31

func (p *propVariant) str() string {
	if p.vt != vtLPWSTR || p.val == 0 {
		return ""
	}
	return windows.UTF16PtrToString((*uint16)(unsafe.Pointer(p.val)))
}

func (p *propVariant) clear() { procPropVariantClear.Call(uintptr(unsafe.Pointer(p))) }

// HRESULT helpers
type hresult uint32

func (h hresult) Error() string { return fmt.Sprintf("HRESULT 0x%08X", uint32(h)) }

func hr(r uintptr) error {
	if int32(r) < 0 {
		return hresult(uint32(r))
	}
	return nil
}

// vcall invokes vtable entry idx of the COM object obj.
func vcall(obj uintptr, idx int, args ...uintptr) uintptr {
	vtbl := *(*uintptr)(unsafe.Pointer(obj))
	fn := *(*uintptr)(unsafe.Pointer(vtbl + uintptr(idx)*unsafe.Sizeof(uintptr(0))))
	all := make([]uintptr, 0, len(args)+1)
	all = append(all, obj)
	all = append(all, args...)
	r, _, _ := syscall.SyscallN(fn, all...)
	return r
}

func release(obj uintptr) {
	if obj != 0 {
		vcall(obj, 2)
	}
}

func coCreate(clsid, iid *windows.GUID) (uintptr, error) {
	var obj uintptr
	r, _, _ := procCoCreateInstance.Call(uintptr(unsafe.Pointer(clsid)), 0, clsctxAll,
		uintptr(unsafe.Pointer(iid)), uintptr(unsafe.Pointer(&obj)))
	if err := hr(r); err != nil {
		return 0, err
	}
	return obj, nil
}

func taskFree(p uintptr) { procCoTaskMemFree.Call(p) }

var (
	mtaOnce sync.Once
	mtaErr  error
)

// InitCOM makes the whole process a member of the multithreaded apartment:
// one parked thread keeps the MTA alive, so every other thread (whatever
// goroutine runs there) is an implicit MTA member and may use our objects.
func InitCOM() error {
	mtaOnce.Do(func() {
		ready := make(chan error)
		go func() {
			runtime.LockOSThread()
			r, _, _ := procCoInitializeEx.Call(0, coinitMultithread)
			if int32(r) < 0 {
				ready <- hresult(uint32(r))
				return
			}
			ready <- nil
			select {} // park forever
		}()
		mtaErr = <-ready
	})
	return mtaErr
}

var errNoDevice = errors.New("аудиоустройство не найдено")
