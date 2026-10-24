package audio

import (
	"strings"
	"unsafe"

	"golang.org/x/sys/windows"
)

// Data flow / roles / states (mmdeviceapi.h)
const (
	eRender  = 0
	eCapture = 1
	eConsole = 0
	eMultimedia = 1

	StateActive   = 0x1
	StateDisabled = 0x2
	stgmRead      = 0
)

// Endpoint describes one audio endpoint.
type Endpoint struct {
	ID          string
	Name        string // PKEY_Device_FriendlyName ("Speakers (Realtek...)")
	Desc        string // PKEY_Device_DeviceDesc ("Speakers")
	AdapterName string // PKEY_DeviceInterface_FriendlyName (KS filter name)
	Capture     bool
}

func enumerator() (uintptr, error) {
	if err := InitCOM(); err != nil {
		return 0, err
	}
	return coCreate(&clsidMMDeviceEnumerator, &iidIMMDeviceEnumerator)
}

func deviceByID(en uintptr, id string) (uintptr, error) {
	p, _ := windows.UTF16PtrFromString(id)
	var dev uintptr
	if err := hr(vcall(en, 5, uintptr(unsafe.Pointer(p)), uintptr(unsafe.Pointer(&dev)))); err != nil {
		return 0, err
	}
	return dev, nil
}

func defaultDevice(en uintptr, flow int) (uintptr, error) {
	var dev uintptr
	if err := hr(vcall(en, 4, uintptr(flow), eConsole, uintptr(unsafe.Pointer(&dev)))); err != nil {
		return 0, err
	}
	return dev, nil
}

func deviceID(dev uintptr) string {
	var p uintptr
	if hr(vcall(dev, 5, uintptr(unsafe.Pointer(&p)))) != nil || p == 0 {
		return ""
	}
	defer taskFree(p)
	return windows.UTF16PtrToString((*uint16)(unsafe.Pointer(p)))
}

func propString(ps uintptr, key *propKey) string {
	var v propVariant
	if hr(vcall(ps, 5, uintptr(unsafe.Pointer(key)), uintptr(unsafe.Pointer(&v)))) != nil {
		return ""
	}
	defer v.clear()
	return v.str()
}

func describe(dev uintptr, capture bool) Endpoint {
	e := Endpoint{ID: deviceID(dev), Capture: capture}
	var ps uintptr
	if hr(vcall(dev, 4, stgmRead, uintptr(unsafe.Pointer(&ps)))) == nil {
		e.Name = propString(ps, &pkeyDeviceFriendlyName)
		e.Desc = propString(ps, &pkeyDeviceDesc)
		e.AdapterName = propString(ps, &pkeyDeviceInterfaceFriendlyName)
		release(ps)
	}
	return e
}

// List returns endpoints of one direction in the given state mask.
func List(capture bool, states uint32) []Endpoint {
	en, err := enumerator()
	if err != nil {
		return nil
	}
	defer release(en)
	flow := eRender
	if capture {
		flow = eCapture
	}
	var col uintptr
	if hr(vcall(en, 3, uintptr(flow), uintptr(states), uintptr(unsafe.Pointer(&col)))) != nil {
		return nil
	}
	defer release(col)
	var n uint32
	vcall(col, 3, uintptr(unsafe.Pointer(&n)))
	out := make([]Endpoint, 0, n)
	for i := uint32(0); i < n; i++ {
		var dev uintptr
		if hr(vcall(col, 4, uintptr(i), uintptr(unsafe.Pointer(&dev)))) != nil {
			continue
		}
		out = append(out, describe(dev, capture))
		release(dev)
	}
	return out
}

// DefaultRender returns the default output endpoint.
func DefaultRender() (Endpoint, error) {
	en, err := enumerator()
	if err != nil {
		return Endpoint{}, err
	}
	defer release(en)
	dev, err := defaultDevice(en, eRender)
	if err != nil {
		return Endpoint{}, err
	}
	defer release(dev)
	return describe(dev, false), nil
}

// ---- IPolicyConfig (undocumented, used by the Sound control panel) --------

func policy() (uintptr, error) {
	if err := InitCOM(); err != nil {
		return 0, err
	}
	p, err := coCreate(&clsidPolicyConfigClient, &iidIPolicyConfig10)
	if err != nil {
		p, err = coCreate(&clsidPolicyConfigClient, &iidIPolicyConfig7)
	}
	return p, err
}

// SetDefault makes id the default output for the console and multimedia roles.
func SetDefault(id string) error {
	p, err := policy()
	if err != nil {
		return err
	}
	defer release(p)
	s, _ := windows.UTF16PtrFromString(id)
	if err := hr(vcall(p, 13, uintptr(unsafe.Pointer(s)), eConsole)); err != nil {
		return err
	}
	return hr(vcall(p, 13, uintptr(unsafe.Pointer(s)), eMultimedia))
}

// SetVisible enables (shows) or disables (hides) an endpoint.
func SetVisible(id string, visible bool) error {
	p, err := policy()
	if err != nil {
		return err
	}
	defer release(p)
	s, _ := windows.UTF16PtrFromString(id)
	v := uintptr(0)
	if visible {
		v = 1
	}
	return hr(vcall(p, 14, uintptr(unsafe.Pointer(s)), v))
}

// Rename sets the endpoint's DeviceDesc like the Sound control panel does
// (writing the property store directly makes Windows rebuild the endpoint).
func Rename(id, name string) error {
	p, err := policy()
	if err != nil {
		return err
	}
	defer release(p)
	s, _ := windows.UTF16PtrFromString(id)
	n, _ := windows.UTF16PtrFromString(name)
	v := propVariant{vt: vtLPWSTR, val: uintptr(unsafe.Pointer(n))}
	return hr(vcall(p, 12, uintptr(unsafe.Pointer(s)), 0, uintptr(unsafe.Pointer(&pkeyDeviceDesc)), uintptr(unsafe.Pointer(&v))))
}

func containsFold(s, sub string) bool {
	return strings.Contains(strings.ToLower(s), strings.ToLower(sub))
}
