// Package tray is a minimal Win32 notification-area icon with a context
// menu built on demand (no main window).
package tray

import (
	"runtime"
	"sync"
	"sync/atomic"
	"syscall"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
	"sscv2/internal/logx"
)

// Item is one menu entry. ID 0 + no Sub + !Separator = disabled label.
type Item struct {
	SubRevision string `json:"-"`
	LiveLabel   bool   `json:"-"`
	MinWidth    int32  `json:"-"`
	Slider      bool
	Text        string
	ID          int
	Checked     bool
	Radio       bool
	Disabled    bool
	Separator   bool
	Sub         []Item
	infoID      uint32
}

func (it Item) informational() bool {
	return it.ID == 0 && it.Sub == nil && !it.Separator && !it.Slider
}

// Tray drives the icon. Menu is called on every click to build the
// menu; Command receives the chosen ID (on the UI thread - keep it short).
type Tray struct {
	Menu                        func() []Item
	Command                     func(id int)
	DismissBefore               func(id int) bool
	afterDismiss                int
	Volume                      func() (uint8, bool, bool)
	SetVolume                   func(uint8)
	ToggleMute                  func()
	Resume                      func() // must return promptly; called on the UI thread
	volumeRow                   *menuSlider
	openMenu                    *liveMenu
	selectedMenu, selectedFlags uintptr
	selectedID                  int
	activeMenus                 []uintptr
	menuButtonUp                uintptr
	menuMouseCommand            int
	menuIconBounds              menuRect
	infoRows                    map[uint32]*menuInfoRow
	nextInfoID                  uint32
	infoHover                   menuInfoHover
	VolumeKey                   func(uint32)
	volumeKeys                  atomic.Bool
	menuOpen                    atomic.Bool
	rendered                    atomic.Pointer[[]Item]

	mu           sync.Mutex
	hwnd         uintptr
	icons        map[trayIconKey]uintptr
	color        Color
	iconMode     IconMode
	pulseFrame   int
	pulseStarted time.Time
	tip          string
	created      uint32 // TaskbarCreated message id
	ready        chan struct{}
}

const callbackMsg = wmApp + 1

var current *Tray

// Run creates the icon and pumps messages until Quit. Blocks.
func (t *Tray) Run(initial Color, tip string) error {
	runtime.LockOSThread()
	defer runtime.UnlockOSThread()
	pSetDpiAwarenessCtx.Call(^uintptr(3)) // DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 (-4)
	current = t
	t.icons = map[trayIconKey]uintptr{}
	t.color, t.tip = initial, tip
	if t.ready == nil {
		t.ready = make(chan struct{})
	}

	hinst, _, _ := pGetModuleHandleW.Call(0)
	cls, _ := windows.UTF16PtrFromString("SSCv2TrayWindow")
	wc := wndClassEx{lpfnWndProc: syscall.NewCallback(wndProc), hInstance: hinst, lpszClassName: cls}
	wc.cbSize = uint32(unsafe.Sizeof(wc))
	pRegisterClassExW.Call(uintptr(unsafe.Pointer(&wc)))
	name, _ := windows.UTF16PtrFromString("SSCv2")
	hwnd, _, err := pCreateWindowExW.Call(0, uintptr(unsafe.Pointer(cls)), uintptr(unsafe.Pointer(name)),
		0, 0, 0, 0, 0, 0, 0, hinst, 0)
	if hwnd == 0 {
		return err
	}
	tc, _ := windows.UTF16PtrFromString("TaskbarCreated")
	c, _, _ := pRegisterWindowMessage.Call(uintptr(unsafe.Pointer(tc)))
	t.mu.Lock()
	t.hwnd = hwnd
	t.created = uint32(c)
	t.mu.Unlock()
	if t.Resume != nil {
		notify, _, err := user32.NewProc("RegisterSuspendResumeNotification").Call(hwnd, 0)
		if notify != 0 {
			defer user32.NewProc("UnregisterSuspendResumeNotification").Call(notify)
		} else {
			logx.Printf("power: register suspend/resume notifications: %v", err)
		}
	}
	t.addIcon()
	close(t.ready)
	if t.VolumeKey != nil {
		hook, _, err := setWindowsHook.Call(13, volumeHookCallback, hinst, 0) // WH_KEYBOARD_LL
		if hook != 0 {
			defer unhookWindowsHook.Call(hook)
		} else {
			logx.Printf("volume keys: %v", err)
		}
	}

	var m msgT
	for {
		r, _, _ := pGetMessageW.Call(uintptr(unsafe.Pointer(&m)), 0, 0, 0)
		if int32(r) <= 0 {
			break
		}
		pTranslateMessage.Call(uintptr(unsafe.Pointer(&m)))
		pDispatchMessageW.Call(uintptr(unsafe.Pointer(&m)))
	}
	t.notify(nimDelete, 0)
	t.mu.Lock()
	t.hwnd = 0
	for _, icon := range t.icons {
		pDestroyIcon.Call(icon)
	}
	t.mu.Unlock()
	return nil
}

type trayIconKey struct {
	color Color
	mode  IconMode
	size  int
}

func (t *Tray) iconFor(c Color) uintptr {
	px, _, _ := pGetSystemMetrics.Call(smCxSmIcon)
	key := trayIconKey{color: c, mode: t.iconMode, size: int(max(px, 16))}
	if h, ok := t.icons[key]; ok {
		return h
	}
	h := makeIcon(key.color, key.mode, key.size)
	t.icons[key] = h
	return h
}

func (t *Tray) nid(flags uint32) notifyIconData {
	n := notifyIconData{hWnd: t.hwnd, uID: 1, uFlags: flags, uCallbackMessage: callbackMsg}
	n.cbSize = uint32(unsafe.Sizeof(n))
	return n
}

func (t *Tray) notify(op uint32, flags uint32) {
	t.mu.Lock()
	defer t.mu.Unlock()
	if t.hwnd == 0 {
		return
	}
	n := t.nid(flags)
	n.hIcon = t.iconFor(volumePulseColor(t.color, t.pulseFrame))
	copyUTF16(n.szTip[:], t.tip)
	pShellNotifyIconW.Call(uintptr(op), uintptr(unsafe.Pointer(&n)))
}

func (t *Tray) addIcon() {
	t.notify(nimAdd, nifMessage|nifIcon|nifTip|nifShowTip)
	t.mu.Lock()
	n := t.nid(0)
	n.uVersion = 4
	pShellNotifyIconW.Call(nimSetVersion, uintptr(unsafe.Pointer(&n)))
	t.mu.Unlock()
}

// Set updates the glyph color and tooltip (any goroutine).
func (t *Tray) Set(c Color, mode IconMode, tip string) {
	t.mu.Lock()
	changed := t.color != c || t.iconMode != mode || t.tip != tip
	t.color, t.iconMode, t.tip = c, mode, tip
	t.mu.Unlock()
	if changed {
		t.notify(nimModify, nifIcon|nifTip|nifShowTip)
	}
}

// Balloon shows a notification (any goroutine). kind: 0 info, 1 warn, 2 error.
func (t *Tray) Balloon(title, text string, kind int) {
	t.mu.Lock()
	defer t.mu.Unlock()
	if t.hwnd == 0 {
		return
	}
	n := t.nid(nifInfo)
	copyUTF16(n.szInfoTitle[:], title)
	copyUTF16(n.szInfo[:], text)
	n.dwInfoFlags = [...]uint32{niifInfo, niifWarning, niifError}[kind%3]
	pShellNotifyIconW.Call(nimModify, uintptr(unsafe.Pointer(&n)))
}

// Quit closes the icon and ends Run.
func (t *Tray) Quit() {
	t.mu.Lock()
	h := t.hwnd
	t.mu.Unlock()
	if h != 0 {
		pPostMessageW.Call(h, wmClose, 0, 0)
	}
}

const (
	menuOpenMsg    = wmApp + 4
	menuCloseMsg   = wmApp + 5
	menuRefreshMsg = wmApp + 6
)

var endMenu = user32.NewProc("EndMenu")

func (t *Tray) RenderedMenu() []Item {
	if items := t.rendered.Load(); items != nil {
		return *items
	}
	return nil
}
func (t *Tray) OpenMenu()               { t.postMenuMessage(menuOpenMsg, 0) }
func (t *Tray) CloseMenu()              { t.postMenuMessage(menuCloseMsg, 0) }
func (t *Tray) ActivateMenuItem(id int) { t.postMenuMessage(menuActionMsg, uintptr(id)) }
func (t *Tray) RefreshMenu() {
	if t.menuOpen.Load() {
		t.postMenuMessage(menuRefreshMsg, 0)
	}
}

func (t *Tray) postMenuMessage(msg, arg uintptr) {
	t.mu.Lock()
	h := t.hwnd
	t.mu.Unlock()
	if h != 0 {
		pPostMessageW.Call(h, msg, arg, 0)
	}
}

func (t *Tray) buildMenu(items []Item) *liveMenu {
	h, _, _ := pCreatePopupMenu.Call()
	m := &liveMenu{handle: h}
	t.updateMenu(m, items)
	return m
}

func (t *Tray) showMenu() {
	if t.Menu == nil || !t.menuOpen.CompareAndSwap(false, true) {
		return
	}
	defer t.menuOpen.Store(false)
	items := t.Menu()
	t.infoRows = make(map[uint32]*menuInfoRow)
	t.nextInfoID = 0x7000
	m := t.buildMenu(items)
	t.rendered.Store(&items)
	t.openMenu = m
	t.activeMenus = append(t.activeMenus[:0], m.handle)
	defer func() {
		t.infoHover = menuInfoHover{}
		t.infoRows = nil
		t.rendered.Store(nil)
		t.openMenu, t.volumeRow = nil, nil
		t.selectedMenu, t.selectedID = 0, 0
		t.activeMenus = t.activeMenus[:0]
		t.menuButtonUp, t.menuMouseCommand = 0, 0
		pDestroyMenu.Call(m.handle)
	}()
	thread := windows.GetCurrentThreadId()
	hook, _, err := setWindowsHook.Call(0xffffffff, menuFilterCallback, 0, uintptr(thread)) // WH_MSGFILTER
	if hook != 0 {
		defer unhookWindowsHook.Call(hook)
	} else {
		logx.Printf("menu input: %v", err)
	}
	instance, _, _ := pGetModuleHandleW.Call(0)
	mouseHook, _, mouseErr := setWindowsHook.Call(14, menuMouseCallback, instance, 0) // WH_MOUSE_LL
	if mouseHook != 0 {
		defer unhookWindowsHook.Call(mouseHook)
	} else {
		logx.Printf("tray icon mouse input: %v", mouseErr)
	}
	setTimer.Call(t.hwnd, 1, 40, 0)
	defer killTimer.Call(t.hwnd, 1)
	setTimer.Call(t.hwnd, 2, 300, 0)
	defer killTimer.Call(t.hwnd, 2)

	x, y, alignment := t.menuAnchor()
	t.menuIconBounds, _ = t.iconBounds()
	pSetForegroundWindow.Call(t.hwnd)
	id, _, _ := pTrackPopupMenu.Call(m.handle, tpmReturnCmd|tpmRightButton|alignment,
		uintptr(x), uintptr(y), 0, t.hwnd, 0)
	pPostMessageW.Call(t.hwnd, wmNull, 0, 0)
	if t.afterDismiss != 0 {
		t.ActivateMenuItem(t.afterDismiss)
		t.afterDismiss = 0
		return
	}
	if id != 0 && t.Command != nil && (t.volumeRow == nil || int(id) != t.volumeRow.id) {
		logx.Dbgf("ui", "native popup returned command %d", id)
		t.Command(int(id))
	}
}

func wndProc(hwnd, msg, wparam, lparam uintptr) uintptr {
	t := current
	if t != nil && msg == wmTimer && wparam == 1 && t.openMenu != nil {
		t.refreshInfoHover()
	}
	if t != nil && (t.infoMessage(msg, lparam) || t.sliderMessage(msg, wparam, lparam)) {
		return 1
	}
	switch uint32(msg) {
	case 0x0218: // WM_POWERBROADCAST
		if wparam == 0x0012 && t != nil && t.Resume != nil { // PBT_APMRESUMEAUTOMATIC
			t.Resume()
		}
		return 1
	case 0x0117: // WM_INITMENUPOPUP
		if t.openMenu != nil && wparam != t.openMenu.handle {
			t.prepareSubmenu(t.openMenu, t.Menu(), wparam)
			t.activeMenus = append(t.activeMenus, wparam)
		}
	case 0x0125: // WM_UNINITMENUPOPUP
		for i := len(t.activeMenus) - 1; i >= 0; i-- {
			if t.activeMenus[i] == wparam {
				t.activeMenus = t.activeMenus[:i]
				break
			}
		}
	case wmMenuSelect:
		t.selectedMenu, t.selectedFlags, t.selectedID = lparam, wparam>>16, int(wparam&0xffff)
	case menuOpenMsg:
		t.showMenu()
		return 0
	case menuCloseMsg:
		endMenu.Call()
		return 0
	case menuRefreshMsg:
		t.refreshOpenMenu()
		return 0
	case volumePulseMsg:
		t.startVolumePulse(wparam != 0)
		return 0
	case menuActionMsg:
		if t.openMenu != nil && t.DismissBefore != nil && t.DismissBefore(int(wparam)) {
			t.afterDismiss = int(wparam)
			endMenu.Call()
			return 0
		}
		if t.Command != nil {
			t.Command(int(wparam))
		}
		return 0
	case wmTimer:
		if wparam == volumePulseTimer {
			t.advanceVolumePulse()
			return 0
		}
		if wparam == 2 && t.openMenu != nil {
			t.refreshOpenMenu()
			return 0
		}
	case callbackMsg:
		switch uint32(lparam & 0xFFFF) { // NOTIFYICON_VERSION_4: event in LOWORD
		case wmContextMenu, wmLButtonUp, 0x0401: // NIN_KEYSELECT
			if t.menuOpen.Load() {
				endMenu.Call()
			} else {
				t.showMenu()
			}
		}
		return 0
	case volumeKeyMsg:
		if t.VolumeKey != nil && t.volumeKeys.Load() {
			t.VolumeKey(uint32(wparam))
		}
		return 0
	case wmClose:
		pDestroyWindow.Call(hwnd)
		return 0
	case wmDestroy:
		pPostQuitMessage.Call(0)
		return 0
	}
	if t != nil && t.created != 0 && uint32(msg) == t.created {
		t.addIcon() // Explorer restarted
		return 0
	}
	r, _, _ := pDefWindowProcW.Call(hwnd, msg, wparam, lparam)
	return r
}
