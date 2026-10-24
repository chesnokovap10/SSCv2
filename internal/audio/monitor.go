package audio

import (
	"fmt"
	"sync"
	"sync/atomic"
	"syscall"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
)

// Monitor (debug journal): every audio endpoint event Windows reports -
// added / removed / state changed / default output changed - and every
// level or mute change of every output, with who made it.

var iidIMMNotificationClient = guid("{7991EEC9-7E89-4D85-8390-6C703CEC60C0}")

type notifyClient struct {
	vtbl *[8]uintptr
	refs int32
}

var (
	ncVtbl     [8]uintptr
	ncVtblOnce sync.Once
)

type monEvent struct {
	kind  string
	id    string
	state uint32
	flow  uint32
	role  uint32
	key   propKey
}

type monitor struct {
	logf  func(string, ...any)
	ev    chan monEvent
	stop  chan struct{}
	en    uintptr
	nc    *notifyClient
	mu    sync.Mutex
	names map[string]string
	vols  map[string]*watchedVol
	last  map[string]string // last logged level/mute per endpoint
	t0    time.Time
}

type watchedVol struct {
	vol uintptr
	cb  *volCallback
}

var (
	monMu  sync.Mutex
	curMon *monitor
	monSeq atomic.Uint64
)

func ptrStr(p uintptr) string {
	if p == 0 {
		return ""
	}
	return windows.UTF16PtrToString((*uint16)(unsafe.Pointer(p)))
}

func (m *monitor) post(e monEvent) {
	select {
	case m.ev <- e:
	default:
	}
}

func initNcVtbl() {
	get := func(this uintptr) *monitor {
		monMu.Lock()
		defer monMu.Unlock()
		return curMon
	}
	ncVtbl[0] = syscall.NewCallback(func(this, riid, out uintptr) uintptr {
		g := (*windows.GUID)(unsafe.Pointer(riid))
		if *g == iidIUnknown || *g == iidIMMNotificationClient {
			*(*uintptr)(unsafe.Pointer(out)) = this
			atomic.AddInt32(&(*notifyClient)(unsafe.Pointer(this)).refs, 1)
			return 0
		}
		*(*uintptr)(unsafe.Pointer(out)) = 0
		return 0x80004002
	})
	ncVtbl[1] = syscall.NewCallback(func(this uintptr) uintptr {
		return uintptr(atomic.AddInt32(&(*notifyClient)(unsafe.Pointer(this)).refs, 1))
	})
	ncVtbl[2] = syscall.NewCallback(func(this uintptr) uintptr {
		return uintptr(atomic.AddInt32(&(*notifyClient)(unsafe.Pointer(this)).refs, -1))
	})
	// OnDeviceStateChanged(LPCWSTR, DWORD)
	ncVtbl[3] = syscall.NewCallback(func(this, id, state uintptr) uintptr {
		if m := get(this); m != nil {
			m.post(monEvent{kind: "state", id: ptrStr(id), state: uint32(state)})
		}
		return 0
	})
	// OnDeviceAdded(LPCWSTR)
	ncVtbl[4] = syscall.NewCallback(func(this, id uintptr) uintptr {
		if m := get(this); m != nil {
			m.post(monEvent{kind: "added", id: ptrStr(id)})
		}
		return 0
	})
	// OnDeviceRemoved(LPCWSTR)
	ncVtbl[5] = syscall.NewCallback(func(this, id uintptr) uintptr {
		if m := get(this); m != nil {
			m.post(monEvent{kind: "removed", id: ptrStr(id)})
		}
		return 0
	})
	// OnDefaultDeviceChanged(EDataFlow, ERole, LPCWSTR)
	ncVtbl[6] = syscall.NewCallback(func(this, flow, role, id uintptr) uintptr {
		if m := get(this); m != nil {
			m.post(monEvent{kind: "default", id: ptrStr(id), flow: uint32(flow), role: uint32(role)})
		}
		return 0
	})
	// OnPropertyValueChanged(LPCWSTR, PROPERTYKEY) - the key is passed by
	// value (20 bytes > 8, so as a pointer on x64).
	ncVtbl[7] = syscall.NewCallback(func(this, id, key uintptr) uintptr {
		if m := get(this); m != nil && key != 0 {
			m.post(monEvent{kind: "prop", id: ptrStr(id), key: *(*propKey)(unsafe.Pointer(key))})
		}
		return 0
	})
}

func stateName(s uint32) string {
	switch s {
	case 1:
		return "ACTIVE"
	case 2:
		return "DISABLED"
	case 4:
		return "NOTPRESENT"
	case 8:
		return "UNPLUGGED"
	}
	return fmt.Sprintf("0x%X", s)
}

// StartMonitor starts the debug audio monitor (idempotent). logf receives
// the lines. StopMonitor ends it.
func StartMonitor(logf func(string, ...any)) error {
	monMu.Lock()
	if curMon != nil {
		monMu.Unlock()
		return nil
	}
	monMu.Unlock()
	en, err := enumerator()
	if err != nil {
		return err
	}
	ncVtblOnce.Do(initNcVtbl)
	m := &monitor{logf: logf, ev: make(chan monEvent, 256), stop: make(chan struct{}), en: en,
		names: map[string]string{}, vols: map[string]*watchedVol{}, last: map[string]string{}, t0: time.Now()}
	m.nc = &notifyClient{vtbl: &ncVtbl, refs: 1}
	liveCbs.Store(m.nc, true)
	monMu.Lock()
	curMon = m
	monMu.Unlock()
	if err := hr(vcall(en, 6, uintptr(unsafe.Pointer(m.nc)))); err != nil {
		monMu.Lock()
		curMon = nil
		monMu.Unlock()
		release(en)
		return err
	}
	// snapshot
	for _, capture := range []bool{false, true} {
		for _, e := range List(capture, StateActive|StateDisabled|4|8) {
			m.names[e.ID] = e.Name
		}
	}
	if d, err := DefaultRender(); err == nil {
		logf("audio: default output %s", d.Name)
	}
	for _, e := range List(false, StateActive) {
		m.watch(e.ID)
	}
	go m.run()
	return nil
}

// StopMonitor stops the debug audio monitor.
func StopMonitor() {
	monMu.Lock()
	m := curMon
	curMon = nil
	monMu.Unlock()
	if m == nil {
		return
	}
	close(m.stop)
	vcall(m.en, 7, uintptr(unsafe.Pointer(m.nc)))
	release(m.en)
	m.mu.Lock()
	for id := range m.vols {
		m.unwatchLocked(id)
	}
	m.mu.Unlock()
}

func (m *monitor) name(id string) string {
	m.mu.Lock()
	n, ok := m.names[id]
	m.mu.Unlock()
	if ok && n != "" {
		return n
	}
	for _, capture := range []bool{false, true} {
		for _, e := range List(capture, StateActive|StateDisabled|4|8) {
			if e.ID == id {
				m.mu.Lock()
				m.names[id] = e.Name
				m.mu.Unlock()
				return e.Name
			}
		}
	}
	return id
}

func isRender(id string) bool { return len(id) > 6 && id[:6] == "{0.0.0" }

// watch subscribes to the level/mute of one output endpoint.
func (m *monitor) watch(id string) {
	if !isRender(id) {
		return
	}
	m.mu.Lock()
	_, have := m.vols[id]
	m.mu.Unlock()
	if have {
		return
	}
	vol, err := endpointVolume(id)
	if err != nil {
		return
	}
	name := m.name(id)
	report := func(ctx windows.GUID, muted bool, level float32, initial bool) {
		s := fmt.Sprintf("%.1f%%", level*100)
		if muted {
			s += " [muted]"
		}
		m.mu.Lock()
		same := m.last[id] == s
		m.last[id] = s
		m.mu.Unlock()
		if same && !initial {
			return
		}
		if initial {
			m.logf("vol: %s = %s", name, s)
		} else {
			m.logf("vol: %s -> %s (by %s)", name, s, WhoChanged(ctx))
		}
	}
	cb := newVolCallback(func(ctx windows.GUID, muted bool, level float32) { report(ctx, muted, level, false) })
	if err := hr(vcall(vol, 3, uintptr(unsafe.Pointer(cb)))); err != nil {
		release(vol)
		return
	}
	m.mu.Lock()
	m.vols[id] = &watchedVol{vol: vol, cb: cb}
	m.mu.Unlock()
	if l, err := getScalar(vol); err == nil {
		var mu int32
		vcall(vol, 15, uintptr(unsafe.Pointer(&mu)))
		report(windows.GUID{}, mu != 0, l, true)
	}
}

func (m *monitor) unwatchLocked(id string) {
	w, ok := m.vols[id]
	if !ok {
		return
	}
	vcall(w.vol, 4, uintptr(unsafe.Pointer(w.cb)))
	release(w.vol)
	w.cb.on.Store(nil)
	delete(m.vols, id)
	delete(m.last, id)
}

func (m *monitor) run() {
	for {
		select {
		case <-m.stop:
			return
		case e := <-m.ev:
			m.handle(e)
		}
	}
}

func (m *monitor) handle(e monEvent) {
	kind := "output"
	if !isRender(e.id) {
		kind = "input"
	}
	switch e.kind {
	case "state":
		m.logf("dev: %s %q -> %s", kind, m.name(e.id), stateName(e.state))
		if e.state == StateActive {
			m.watch(e.id)
		} else {
			m.mu.Lock()
			m.unwatchLocked(e.id)
			m.mu.Unlock()
		}
	case "added":
		m.logf("dev: %s added %q", kind, m.name(e.id))
	case "removed":
		m.logf("dev: %s removed %q", kind, m.name(e.id))
		m.mu.Lock()
		m.unwatchLocked(e.id)
		m.mu.Unlock()
	case "default":
		if e.flow != eRender || e.role != eConsole {
			return // one line per change is enough
		}
		n := "(none)"
		if e.id != "" {
			n = m.name(e.id)
		}
		m.logf("dev: DEFAULT output -> %q", n)
	case "prop":
		// Name changes matter (rename of the virtual device); the rest is noise.
		if e.key == pkeyDeviceFriendlyName || e.key == pkeyDeviceDesc {
			m.mu.Lock()
			delete(m.names, e.id)
			m.mu.Unlock()
			m.logf("dev: %s renamed -> %q", kind, m.name(e.id))
		}
	}
}
