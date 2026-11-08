package audio

import (
	"math"
	"sync"
	"sync/atomic"
	"syscall"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"

	"sscv2/internal/logx"
)

// selfContext tags volume changes we make ourselves (from the headphones),
// so their notifications are not echoed back.
var selfContext = guid("{6b1f3a52-2c4e-4d8a-9a51-3e0d715b229c}")

func activateVolume(dev uintptr) (uintptr, error) {
	var v uintptr
	if err := hr(vcall(dev, 3, uintptr(unsafe.Pointer(&iidIAudioEndpointVolume)), clsctxAll, 0, uintptr(unsafe.Pointer(&v)))); err != nil {
		return 0, err
	}
	return v, nil
}

func endpointVolume(id string) (uintptr, error) {
	en, err := enumerator()
	if err != nil {
		return 0, err
	}
	defer release(en)
	var dev uintptr
	if id == "" {
		dev, err = defaultDevice(en, eRender)
	} else {
		dev, err = deviceByID(en, id)
	}
	if err != nil {
		return 0, err
	}
	defer release(dev)
	return activateVolume(dev)
}

func getScalar(vol uintptr) (float32, error) {
	var f float32
	if err := hr(vcall(vol, 9, uintptr(unsafe.Pointer(&f)))); err != nil {
		return 0, err
	}
	return f, nil
}

// Float args travel in XMM registers; Go's syscall layer mirrors the first
// four integer argument registers into XMM0-3, so the bit pattern works.
func setScalar(vol uintptr, f float32, ctx *windows.GUID) error {
	return hr(vcall(vol, 7, uintptr(math.Float32bits(f)), uintptr(unsafe.Pointer(ctx))))
}

// SetMute mutes/unmutes an output endpoint ("" = default output).
func SetMute(id string, mute bool) error {
	vol, err := endpointVolume(id)
	if err != nil {
		return err
	}
	defer release(vol)
	m := uintptr(0)
	if mute {
		m = 1
	}
	return hr(vcall(vol, 14, m, 0))
}

// HoldMute mutes a render endpoint and reasserts mute after external changes.
// Stop the guard before restoring the endpoint's original mute state.
func HoldMute(id string) (stop func(), err error) {
	vol, err := endpointVolume(id)
	if err != nil {
		return nil, err
	}
	wake := make(chan struct{}, 1)
	cb := newVolCallback(func(_ windows.GUID, muted bool, _ float32) {
		if !muted {
			select {
			case wake <- struct{}{}:
			default:
			}
		}
	})
	if err := hr(vcall(vol, 3, uintptr(unsafe.Pointer(cb)))); err != nil {
		liveCbs.Delete(cb)
		release(vol)
		return nil, err
	}
	closeVolume := func() {
		cb.on.Store(nil)
		if hr(vcall(vol, 4, uintptr(unsafe.Pointer(cb)))) == nil {
			liveCbs.Delete(cb)
		}
		release(vol)
	}
	if err := hr(vcall(vol, 14, 1, 0)); err != nil {
		closeVolume()
		return nil, err
	}
	stopCh, done := make(chan struct{}), make(chan struct{})
	go func() {
		defer close(done)
		for {
			select {
			case <-stopCh:
				return
			case <-wake:
				if err := hr(vcall(vol, 14, 1, 0)); err != nil {
					logx.Printf("restore output mute: %v", err)
				}
			}
		}
	}()
	return func() {
		close(stopCh)
		<-done
		closeVolume()
	}, nil
}

func ScalarTo127(s float32) uint8 {
	if s < 0 {
		s = 0
	}
	if s > 1 {
		s = 1
	}
	return uint8(math.Round(float64(s) * 127))
}

// ---- IAudioEndpointVolumeCallback implemented in Go ------------------------

// volCallback is a COM object whose OnNotify calls on (when set).
type volCallback struct {
	vtbl *[4]uintptr
	refs int32
	on   atomic.Pointer[func(ctx windows.GUID, muted bool, level float32)]
}

var (
	cbVtbl     [4]uintptr
	cbVtblOnce sync.Once
	liveCbs    sync.Map // keeps Go-allocated COM objects reachable
)

// AUDIO_VOLUME_NOTIFICATION_DATA
type volNotify struct {
	ctx       windows.GUID
	muted     int32
	master    float32
	nChannels uint32
}

func initVtbl() {
	cbVtbl[0] = syscall.NewCallback(func(this, riid, out uintptr) uintptr {
		g := (*windows.GUID)(unsafe.Pointer(riid))
		if *g == iidIUnknown || *g == iidIAudioEndpointVolumeCb {
			*(*uintptr)(unsafe.Pointer(out)) = this
			atomic.AddInt32(&(*volCallback)(unsafe.Pointer(this)).refs, 1)
			return 0
		}
		*(*uintptr)(unsafe.Pointer(out)) = 0
		return 0x80004002 // E_NOINTERFACE
	})
	cbVtbl[1] = syscall.NewCallback(func(this uintptr) uintptr {
		return uintptr(atomic.AddInt32(&(*volCallback)(unsafe.Pointer(this)).refs, 1))
	})
	cbVtbl[2] = syscall.NewCallback(func(this uintptr) uintptr {
		return uintptr(atomic.AddInt32(&(*volCallback)(unsafe.Pointer(this)).refs, -1))
	})
	cbVtbl[3] = syscall.NewCallback(func(this, data uintptr) uintptr {
		cb := (*volCallback)(unsafe.Pointer(this))
		f := cb.on.Load()
		if data == 0 || f == nil {
			return 0
		}
		d := (*volNotify)(unsafe.Pointer(data))
		(*f)(d.ctx, d.muted != 0, d.master)
		return 0
	})
}

func newVolCallback(on func(ctx windows.GUID, muted bool, level float32)) *volCallback {
	cbVtblOnce.Do(initVtbl)
	cb := &volCallback{vtbl: &cbVtbl, refs: 1}
	cb.on.Store(&on)
	liveCbs.Store(cb, true)
	return cb
}

// trayContext tags the levels the tray sets (restore after a mode switch,
// level carried between modes) - visible in the debug journal.
var trayContext = guid("{3c0f5e8a-77d2-4b0e-9f43-1d6a2b8e5c11}")

// WhoChanged names the origin of a volume change for the debug journal.
func WhoChanged(ctx windows.GUID) string {
	switch ctx {
	case selfContext:
		return "SSCv2 engine (from headphones)"
	case trayContext:
		return "SSCv2 tray"
	case windows.GUID{}:
		return "Windows/driver"
	}
	return "app " + ctx.String()
}

const FallbackLevel = 0.15

// headphonesEndpoint finds the active A2DP render endpoint of the named
// headphones (adapter name contains name; excluding hands-free).
func headphonesEndpoint(name string) (Endpoint, bool) {
	for _, e := range List(false, StateActive) {
		if containsFold(e.AdapterName, name) && !containsFold(e.AdapterName, "Hands-Free") {
			return e, true
		}
	}
	return Endpoint{}, false
}

// HeadphonesStereoActive reports whether Windows can render to these headphones.
func HeadphonesStereoActive(name string) bool {
	_, ok := headphonesEndpoint(name)
	return ok
}

// HeadphonesVolume reads the Windows stereo endpoint's level and mute state.
func HeadphonesVolume(name string) (level float32, muted bool, ok bool) {
	if name == "" {
		return 0, false, false
	}
	e, ok := headphonesEndpoint(name)
	if !ok {
		return 0, false, false
	}
	vol, err := endpointVolume(e.ID)
	if err != nil {
		return 0, false, false
	}
	defer release(vol)
	level, err = getScalar(vol)
	if err != nil {
		return 0, false, false
	}
	var mute int32
	err = hr(vcall(vol, 15, uintptr(unsafe.Pointer(&mute))))
	return level, mute != 0, err == nil
}

// SetLevel sets an endpoint's master level (0..1).
func SetLevel(id string, level float32) error {
	vol, err := endpointVolume(id)
	if err != nil {
		return err
	}
	defer release(vol)
	err = setScalar(vol, level, &trayContext)
	logx.Dbgf("vol", "set %s to %.1f%%: %v", id, level*100, err)
	return err
}

// Level reads an endpoint's master level (0..1).
func Level(id string) (float32, error) {
	vol, err := endpointVolume(id)
	if err != nil {
		return 0, err
	}
	defer release(vol)
	return getScalar(vol)
}

// Muted reports an endpoint's mute state.
func Muted(id string) (bool, error) {
	vol, err := endpointVolume(id)
	if err != nil {
		return false, err
	}
	defer release(vol)
	var m int32
	err = hr(vcall(vol, 15, uintptr(unsafe.Pointer(&m))))
	return m != 0, err
}

// RestoreHeadphonesVolume applies the carried state when Windows exposes the
// stereo endpoint, then briefly guards against reconnect resets to 100%.
func RestoreHeadphonesVolume(name string, want float32, muted bool, timeout time.Duration, logf func(string, ...any), settled chan struct{}, cancel <-chan struct{}) bool {
	applied := false
	defer func() {
		if !applied {
			close(settled)
		}
	}()
	if name == "" {
		return false
	}
	tick := time.NewTicker(50 * time.Millisecond)
	defer tick.Stop()
	deadline := time.NewTimer(timeout)
	defer deadline.Stop()
	curID := ""
	for {
		select {
		case <-cancel:
			return true
		case <-deadline.C:
			return applied
		case <-tick.C:
		}
		e, ok := headphonesEndpoint(name)
		if !ok {
			curID = ""
			continue
		}
		vol, err := endpointVolume(e.ID)
		if err != nil {
			continue
		}
		level, err := getScalar(vol)
		if err != nil {
			release(vol)
			continue
		}
		if curID != e.ID {
			if muted {
				err = hr(vcall(vol, 14, 1, uintptr(unsafe.Pointer(&trayContext))))
			}
			if err == nil {
				err = setScalar(vol, want, &trayContext)
			}
			if err == nil && !muted {
				err = hr(vcall(vol, 14, 0, uintptr(unsafe.Pointer(&trayContext))))
			}
			release(vol)
			if err == nil {
				curID = e.ID
				if !applied {
					applied = true
					close(settled)
					deadline.Reset(5 * time.Second)
				}
				logf("volume: Windows headphones %.0f%% -> %.0f%% (mute=%v)", level*100, want*100, muted)
			}
			continue
		}
		if level >= 0.99 && want < 0.95 {
			_ = setScalar(vol, want, &trayContext)
		} else if math.Abs(float64(level-want)) > 0.015 {
			release(vol)
			return applied // the user changed the level
		}
		release(vol)
	}
}
