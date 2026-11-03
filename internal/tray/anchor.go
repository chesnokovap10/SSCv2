package tray

import "unsafe"

var (
	getTrayIconRect = shell32.NewProc("Shell_NotifyIconGetRect")
	monitorFromRect = user32.NewProc("MonitorFromRect")
	getMonitorInfo  = user32.NewProc("GetMonitorInfoW")
)

type trayIconIdentifier struct {
	size   uint32
	window uintptr
	id     uint32
	guid   [16]byte
}

type menuMonitorInfo struct {
	size         uint32
	screen, work menuRect
	flags        uint32
}

func (t *Tray) menuAnchor() (x, y int32, alignment uintptr) {
	const (
		rightAlign            = 0x0008
		monitorDefaultPrimary = 1
		monitorDefaultNearest = 2
	)
	icon, found := t.iconBounds()
	fallback := uintptr(monitorDefaultNearest)
	if !found {
		icon = menuRect{}
		fallback = monitorDefaultPrimary
	}
	monitor, _, _ := monitorFromRect.Call(uintptr(unsafe.Pointer(&icon)), fallback)
	info := menuMonitorInfo{size: uint32(unsafe.Sizeof(menuMonitorInfo{}))}
	ok, _, _ := getMonitorInfo.Call(monitor, uintptr(unsafe.Pointer(&info)))
	if ok == 0 {
		return icon.right, icon.top, rightAlign | tpmBottomAlign
	}
	work, screen := info.work, info.screen
	x = work.right
	switch {
	case work.bottom < screen.bottom:
		return x, work.bottom, rightAlign | tpmBottomAlign
	case work.top > screen.top:
		return x, work.top, rightAlign
	case work.left > screen.left:
		return work.left, max(work.top, icon.top), 0
	case work.right < screen.right:
		return work.right, max(work.top, icon.top), rightAlign
	default: // Auto-hidden taskbar or no reserved taskbar space on this monitor.
		y = work.bottom
		if icon.bottom > icon.top {
			y = min(max(icon.top, work.top), work.bottom)
		}
		return x, y, rightAlign | tpmBottomAlign
	}
}

func (t *Tray) iconBounds() (menuRect, bool) {
	id := trayIconIdentifier{window: t.hwnd, id: t.nid(0).uID}
	id.size = uint32(unsafe.Sizeof(id))
	var icon menuRect
	hr, _, _ := getTrayIconRect.Call(uintptr(unsafe.Pointer(&id)), uintptr(unsafe.Pointer(&icon)))
	return icon, int32(hr) >= 0
}
