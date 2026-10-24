// Package tray is a minimal Win32 notification-area icon with a context
// menu built on demand (no main window).
package tray

import (
	"runtime"
	"sync"
	"syscall"
	"unsafe"

	"golang.org/x/sys/windows"
)

// Item is one menu entry. ID 0 + no Sub + !Separator = disabled label.
type Item struct {
	Text      string
	ID        int
	Checked   bool
	Radio     bool
	Disabled  bool
	Separator bool
	Sub       []Item
}

// Tray drives the icon. Menu is called on every right click to build the
// menu; Command receives the chosen ID (on the UI thread - keep it short).
type Tray struct {
	Menu    func() []Item
	Command func(id int)
	Click   func() // left click

	mu      sync.Mutex
	hwnd    uintptr
	icons   map[Color]uintptr
	color   Color
	tip     string
	created uint32 // TaskbarCreated message id
	ready   chan struct{}
}

const callbackMsg = wmApp + 1

var current *Tray

// Run creates the icon and pumps messages until Quit. Blocks.
func (t *Tray) Run(initial Color, tip string) error {
	runtime.LockOSThread()
	defer runtime.UnlockOSThread()
	pSetDpiAwarenessCtx.Call(^uintptr(3)) // DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 (-4)
	current = t
	t.icons = map[Color]uintptr{}
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
	t.addIcon()
	close(t.ready)

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
	return nil
}

func (t *Tray) iconFor(c Color) uintptr {
	if h, ok := t.icons[c]; ok {
		return h
	}
	px, _, _ := pGetSystemMetrics.Call(smCxSmIcon)
	if px < 16 {
		px = 16
	}
	h := makeIcon(c, int(px))
	t.icons[c] = h
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
	n.hIcon = t.iconFor(t.color)
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
func (t *Tray) Set(c Color, tip string) {
	t.mu.Lock()
	changed := t.color != c || t.tip != tip
	t.color, t.tip = c, tip
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

func buildMenu(items []Item) uintptr {
	h, _, _ := pCreatePopupMenu.Call()
	for _, it := range items {
		if it.Separator {
			pAppendMenuW.Call(h, mfSeparator, 0, 0)
			continue
		}
		text, _ := windows.UTF16PtrFromString(it.Text)
		flags := uintptr(mfString)
		if it.Checked {
			flags |= mfChecked
		}
		if it.Radio {
			flags |= mfRadioChk
		}
		if it.Disabled || (it.ID == 0 && it.Sub == nil) {
			flags |= mfGrayed
		}
		if it.Sub != nil {
			sub := buildMenu(it.Sub)
			pAppendMenuW.Call(h, flags|mfPopup, sub, uintptr(unsafe.Pointer(text)))
			continue
		}
		pAppendMenuW.Call(h, flags, uintptr(it.ID), uintptr(unsafe.Pointer(text)))
	}
	return h
}

func (t *Tray) showMenu() {
	if t.Menu == nil {
		return
	}
	h := buildMenu(t.Menu())
	defer pDestroyMenu.Call(h)
	var pt struct{ x, y int32 }
	pGetCursorPos.Call(uintptr(unsafe.Pointer(&pt)))
	pSetForegroundWindow.Call(t.hwnd)
	id, _, _ := pTrackPopupMenu.Call(h, tpmReturnCmd|tpmRightButton|tpmBottomAlign,
		uintptr(pt.x), uintptr(pt.y), 0, t.hwnd, 0)
	pPostMessageW.Call(t.hwnd, wmNull, 0, 0)
	if id != 0 && t.Command != nil {
		t.Command(int(id))
	}
}

func wndProc(hwnd, msg, wparam, lparam uintptr) uintptr {
	t := current
	switch uint32(msg) {
	case callbackMsg:
		switch uint32(lparam & 0xFFFF) { // NOTIFYICON_VERSION_4: event in LOWORD
		case wmContextMenu: // v4 sends this for right click / keyboard menu
			t.showMenu()
		case wmLButtonUp:
			if t.Click != nil {
				t.Click()
			}
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
