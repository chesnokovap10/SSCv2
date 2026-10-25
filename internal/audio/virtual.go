package audio

import "time"

// The virtual "headphones" output device: a VB-CABLE endpoint (driver by
// VB-Audio, Microsoft-signed) renamed after the headphones. While streaming
// it is the default output, audio is captured from its recording side and
// its volume slider drives the headphones. Hidden outside streaming so the
// real headphones are not duplicated in the Windows sound list.

const (
	CableHardwareID = "VBAudioVACWDM"
	CableAdapter    = "VB-Audio Virtual Cable"
)

// cableEndpoint finds the cable endpoint of one direction; the stereo one is
// preferred over VB-CABLE 4.x's "CABLE In 16 Ch".
func cableEndpoint(capture bool, states uint32) (Endpoint, bool) {
	var found, fallback *Endpoint
	list := List(capture, states)
	for i := range list {
		e := &list[i]
		if !containsFold(e.AdapterName, CableAdapter) {
			continue
		}
		if containsFold(e.Desc, "16 Ch") {
			if fallback == nil {
				fallback = e
			}
			continue
		}
		if found == nil {
			found = e
		}
	}
	if found != nil {
		return *found, true
	}
	if fallback != nil {
		return *fallback, true
	}
	return Endpoint{}, false
}

func cable16ch(states uint32) (Endpoint, bool) {
	for _, e := range List(false, states) {
		if containsFold(e.AdapterName, CableAdapter) && containsFold(e.Desc, "16 Ch") {
			return e, true
		}
	}
	return Endpoint{}, false
}

const anyState = StateActive | StateDisabled

// VirtualInstalled reports whether the cable driver exposes an endpoint.
func VirtualInstalled() bool {
	_, ok := cableEndpoint(false, anyState)
	return ok
}

// VirtualRender / VirtualCapture return the active cable endpoints.
func VirtualRender() (Endpoint, bool)  { return cableEndpoint(false, StateActive) }
func VirtualCapture() (Endpoint, bool) { return cableEndpoint(true, StateActive) }

// HeadphonesName is the name the virtual device was branded with ("" for an
// unbranded "CABLE Input").
func HeadphonesName() string {
	e, ok := cableEndpoint(false, anyState)
	if !ok || containsFold(e.Desc, "CABLE") {
		return ""
	}
	return e.Desc
}

// SetVirtualVisible shows or hides the cable's render endpoint (the virtual
// headphones). The recording side ("CABLE Output") always stays hidden: the
// engine captures the render endpoint by loopback, and a visible recording
// endpoint in use lights the microphone indicator. When showing it waits
// until the endpoint is usable.
func SetVirtualVisible(visible bool) error {
	r, ok := cableEndpoint(false, anyState)
	if !ok {
		return errNoDevice
	}
	HideVirtualCapture()
	if s, ok := cable16ch(anyState); ok && s.ID != r.ID {
		_ = SetVisible(s.ID, false)
	}
	err := SetVisible(r.ID, visible)
	if visible {
		for i := 0; i < 20; i++ {
			if _, r1 := VirtualRender(); r1 {
				break
			}
			time.Sleep(100 * time.Millisecond)
		}
	}
	return err
}

// HideVirtualCapture hides the cable's recording endpoint if it is shown.
func HideVirtualCapture() {
	if c, ok := cableEndpoint(true, StateActive); ok {
		_ = SetVisible(c.ID, false)
	}
}

// BrandVirtual renames the cable's render endpoint after the headphones.
func BrandVirtual(name string) error {
	r, ok := cableEndpoint(false, anyState)
	if !ok {
		return errNoDevice
	}
	return Rename(r.ID, name)
}

// IsVirtual reports whether e is an endpoint of the virtual cable.
func IsVirtual(e Endpoint) bool { return containsFold(e.AdapterName, CableAdapter) }
