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
// level carried to the virtual device) - visible in the debug journal.
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

// VolumeSync keeps a render endpoint's volume and the headphones' AVRCP
// absolute volume in step. Audio is captured before the endpoint volume is
// applied, so the Windows volume keys would otherwise do nothing for the
// headphones.
type VolumeSync struct {
	mu       sync.Mutex
	vol      uintptr
	cb       *volCallback
	id       string
	send     func(uint8) bool
	lastSent atomic.Int32
	pending  atomic.Bool
}

// FallbackLevel is used when a device has no stored volume.
const FallbackLevel = 0.15

// StartVolumeSync attaches to endpoint id ("" = default output). send pushes
// a 0..127 volume to the headphones; the current level is sent at once.
func StartVolumeSync(id string, send func(uint8) bool) (*VolumeSync, error) {
	vol, err := endpointVolume(id)
	if err != nil {
		return nil, err
	}
	vs := &VolumeSync{vol: vol, send: send, id: id}
	vs.lastSent.Store(-1)
	vs.cb = newVolCallback(func(ctx windows.GUID, muted bool, level float32) {
		if ctx == selfContext {
			return // our own echo
		}
		vs.onLocal(level)
	})
	if err := hr(vcall(vol, 3, uintptr(unsafe.Pointer(vs.cb)))); err != nil {
		release(vol)
		liveCbs.Delete(vs.cb)
		return nil, err
	}
	s, err := getScalar(vol)
	if err != nil {
		s = FallbackLevel
		_ = setScalar(vol, s, &selfContext)
	}
	v := ScalarTo127(s)
	vs.lastSent.Store(int32(v))
	ok := send(v)
	vs.pending.Store(!ok)
	logx.Dbgf("vol", "sync start: endpoint %s level %.1f%% -> headphones %d/127 (AVRCP up: %v)", nzs(id, "default"), s*100, v, ok)
	return vs, nil
}

func (vs *VolumeSync) onLocal(level float32) {
	v := ScalarTo127(level)
	if int32(v) == vs.lastSent.Load() {
		logx.Dbgf("vol", "Windows level %.1f%% = %d/127 already sent", level*100, v)
		return // mute toggles etc.
	}
	logx.Dbgf("vol", "Windows level %.1f%% -> headphones %d/127", level*100, v)
	vs.lastSent.Store(int32(v))
	if vs.send != nil {
		vs.send(v)
	}
}

// Resync delivers the initial level if it could not be sent yet (AVRCP was
// not up). Cheap no-op afterwards.
func (vs *VolumeSync) Resync() {
	if vs == nil || !vs.pending.Load() {
		return
	}
	vs.mu.Lock()
	defer vs.mu.Unlock()
	if vs.vol == 0 {
		return
	}
	s, err := getScalar(vs.vol)
	if err != nil {
		return
	}
	v := ScalarTo127(s)
	if vs.send(v) {
		logx.Dbgf("vol", "resync: initial level %d/127 delivered", v)
		vs.pending.Store(false)
		vs.lastSent.Store(int32(v))
	}
}

// Push sends the endpoint's current level to the headphones again (after
// every AVRCP (re)connect - they come back at their own level).
func (vs *VolumeSync) Push() (float32, bool) {
	if vs == nil {
		return 0, false
	}
	vs.mu.Lock()
	defer vs.mu.Unlock()
	if vs.vol == 0 {
		return 0, false
	}
	s, err := getScalar(vs.vol)
	if err != nil {
		return 0, false
	}
	v := ScalarTo127(s)
	vs.lastSent.Store(int32(v))
	ok := vs.send(v)
	vs.pending.Store(!ok)
	logx.Dbgf("vol", "push: Windows level %.1f%% -> headphones %d/127 (sent: %v)", s*100, v, ok)
	return s, ok
}

// OnRemote applies a volume reported by the headphones to the endpoint.
func (vs *VolumeSync) OnRemote(v uint8) {
	if vs == nil {
		return
	}
	if v > 127 {
		v = 127
	}
	vs.mu.Lock()
	defer vs.mu.Unlock()
	if vs.vol == 0 {
		return
	}
	vs.lastSent.Store(int32(v))
	err := setScalar(vs.vol, float32(v)/127, &selfContext)
	logx.Dbgf("vol", "headphones %d/127 -> Windows level %.1f%%: %v", v, float32(v)/127*100, err)
}

// Level returns the endpoint level 0..1.
func (vs *VolumeSync) Level() float32 {
	if vs == nil {
		return 0
	}
	vs.mu.Lock()
	defer vs.mu.Unlock()
	s, _ := getScalar(vs.vol)
	return s
}

// Stop detaches the callback.
func (vs *VolumeSync) Stop() {
	if vs == nil {
		return
	}
	vs.mu.Lock()
	defer vs.mu.Unlock()
	if vs.vol != 0 {
		vcall(vs.vol, 4, uintptr(unsafe.Pointer(vs.cb)))
		release(vs.vol)
		vs.vol = 0
	}
	vs.cb.on.Store(nil)
	logx.Dbgf("vol", "sync stopped")
	// keep vs.cb in liveCbs: the audio service may still hold a reference
}

// headphonesEndpoint finds the active A2DP render endpoint of the named
// headphones (adapter name contains name; not hands-free, not the cable).
func headphonesEndpoint(name string) (Endpoint, bool) {
	for _, e := range List(false, StateActive) {
		if containsFold(e.AdapterName, name) && !containsFold(e.AdapterName, "Hands-Free") &&
			!containsFold(e.AdapterName, "VB-Audio") {
			return e, true
		}
	}
	return Endpoint{}, false
}

// HeadphonesLevel is the level Windows stores for the real headphones
// (only while they are connected to Windows).
func HeadphonesLevel(name string) (float32, bool) {
	if name == "" {
		return 0, false
	}
	e, ok := headphonesEndpoint(name)
	if !ok {
		return 0, false
	}
	vol, err := endpointVolume(e.ID)
	if err != nil {
		return 0, false
	}
	defer release(vol)
	s, err := getScalar(vol)
	return s, err == nil
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

// RestoreHeadphonesVolume runs after the adapter returned to Windows.
// While the headphones connect, their endpoint can vanish and come back,
// and Galaxy Buds jump to 100 %. Touching the volume needlessly in that
// phase makes the output audibly bounce, so:
//   - from the first moment, only a jump to ~100 % is answered (within
//     ~0.1 s, one plain set back to the target, no wiggle);
//   - once the endpoint has been present for 3 s, `want` (0..1; <0 = keep
//     Windows' level) is applied once if it differs;
//   - then 15 s more of the jump guard. Touches no other device.
func RestoreHeadphonesVolume(name string, want float32, timeout time.Duration, logf func(string, ...any)) bool {
	if name == "" {
		return false
	}
	var vol uintptr
	curID := ""
	var stableSince, settledAt time.Time
	appears, jumps := 0, 0
	stored := float32(-1)
	defer func() {
		if vol != 0 {
			release(vol)
		}
	}()
	target := func() float32 { // level used against jumps before settling
		if want >= 0 && want < 0.99 {
			return want
		}
		if stored >= 0 && stored < 0.99 {
			return stored
		}
		return FallbackLevel
	}
	deadline := time.Now().Add(timeout)
	for time.Now().Before(deadline) {
		if !settledAt.IsZero() && time.Since(settledAt) > 15*time.Second {
			return true
		}
		e, ok := headphonesEndpoint(name)
		switch {
		case !ok:
			if vol != 0 {
				release(vol)
				vol = 0
			}
			curID, stableSince = "", time.Time{}
		case e.ID != curID || vol == 0:
			if vol != 0 {
				release(vol)
				vol = 0
			}
			if v, err := endpointVolume(e.ID); err == nil {
				vol, curID, stableSince = v, e.ID, time.Now()
				appears++
				if stored < 0 {
					if st, err := getScalar(vol); err == nil && st < 0.99 {
						stored = st
					}
				}
			}
		}
		if vol != 0 {
			cur, err := getScalar(vol)
			if err == nil && cur >= 0.99 && target() < 0.95 {
				jumps++
				_ = setScalar(vol, target(), &trayContext) // Buds' jump: answer at once
			} else if err == nil && settledAt.IsZero() && time.Since(stableSince) >= 3*time.Second {
				settledAt = time.Now()
				t := target()
				if absf(cur-t) > 0.015 {
					_ = setScalar(vol, t, &trayContext)
				}
				logf("volume: headphones settled in Windows (appeared %d time(s), 100%% jumps answered %d); level %.0f%% -> %.0f%%",
					appears, jumps, cur*100, t*100)
			} else if err == nil && !settledAt.IsZero() && absf(cur-target()) > 0.015 && cur < 0.99 {
				return true // the user changed it
			}
		}
		time.Sleep(50 * time.Millisecond)
	}
	return !settledAt.IsZero()
}

func absf(f float32) float32 {
	if f < 0 {
		return -f
	}
	return f
}

func nzs(a, b string) string {
	if a != "" {
		return a
	}
	return b
}
