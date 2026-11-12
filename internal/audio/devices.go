package audio

import (
	"strings"
	"unsafe"

	"golang.org/x/sys/windows"
)

// Data flow / roles / states (mmdeviceapi.h)
const (
	eRender     = 0
	eCapture    = 1
	eConsole    = 0
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

func (e Endpoint) MatchesAdapter(name string) bool {
	return strings.EqualFold(e.AdapterName, name) || strings.Contains(e.Name, "("+name+")")
}

// FindRenderEndpoint keeps the preferred endpoint while it is present, or
// finds its replacement when Windows republishes the adapter's output.
func FindRenderEndpoint(adapter, preferred string, states uint32) Endpoint {
	return findRenderEndpoint(List(false, states), adapter, preferred)
}

func findRenderEndpoint(endpoints []Endpoint, adapter, preferred string) Endpoint {
	var match Endpoint
	for _, endpoint := range endpoints {
		if !endpoint.MatchesAdapter(adapter) {
			continue
		}
		if endpoint.ID == preferred {
			return endpoint
		}
		if match.ID == "" {
			match = endpoint
		}
	}
	return match
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
	return DefaultRenderRole(eConsole)
}

func DefaultRenderRole(role int) (Endpoint, error) {
	en, err := enumerator()
	if err != nil {
		return Endpoint{}, err
	}
	defer release(en)
	var dev uintptr
	err = hr(vcall(en, 4, eRender, uintptr(role), uintptr(unsafe.Pointer(&dev))))
	if err == hresult(0x80070490) {
		return Endpoint{}, nil
	}
	if err != nil {
		return Endpoint{}, err
	}
	defer release(dev)
	return describe(dev, false), nil
}

func containsFold(s, sub string) bool {
	return strings.Contains(strings.ToLower(s), strings.ToLower(sub))
}

// SetDefaultRenderRole switches the Windows audio policy for one output role.
func SetDefaultRenderRole(id string, role int) error {
	return setRenderPolicy(id, 13, uintptr(role))
}

// SetRenderVisible controls endpoint availability without restarting the PnP driver.
func SetRenderVisible(id string, visible bool) error {
	var value uintptr
	if visible {
		value = 1
	}
	return setRenderPolicy(id, 14, value)
}

func setRenderPolicy(id string, method int, value uintptr) error {
	if err := InitCOM(); err != nil {
		return err
	}
	clsid := guid("{870AF99C-171D-4F9E-AF0D-E63DF40C2BC9}")
	iid := guid("{F8679F50-850A-41CF-9C72-430F290290C8}")
	policy, err := coCreate(&clsid, &iid)
	if err != nil {
		return err
	}
	defer release(policy)
	name, err := windows.UTF16PtrFromString(id)
	if err != nil {
		return err
	}
	return hr(vcall(policy, method, uintptr(unsafe.Pointer(name)), value))
}
