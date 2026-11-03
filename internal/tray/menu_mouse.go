package tray

import (
	"syscall"
	"unsafe"
)

var menuMouseCallback = syscall.NewCallback(menuMouseHook)

const (
	wmLButtonDown = 0x0201
	wmRButtonDown = 0x0204
)

// Capture commands before the popup can dismiss itself or replay an icon
// click to Explorer. Leave hover, submenus and outside clicks to Windows.
func menuMouseHook(code, message, data uintptr) uintptr {
	t := current
	if int32(code) == 0 && t.openMenu != nil {
		switch message {
		case wmLButtonDown, wmRButtonDown:
			if t.volumeRow == nil || !t.volumeRow.dragging && !t.volumeRow.mutePressed {
				pt := (*struct{ x, y int32 })(unsafe.Pointer(data))
				r := t.menuIconBounds
				if pt.x >= r.left && pt.x < r.right && pt.y >= r.top && pt.y < r.bottom {
					t.menuButtonUp, t.menuMouseCommand = message+1, 0
					return 1
				}
				if id := t.menuCommandAt(pt.x, pt.y); id != 0 {
					t.menuButtonUp, t.menuMouseCommand = message+1, id
					return 1
				}
			}
		case wmLButtonUp, wmRButtonUp:
			if t.menuButtonUp == message {
				id := t.menuMouseCommand
				t.menuButtonUp, t.menuMouseCommand = 0, 0
				if id == 0 {
					pPostMessageW.Call(t.hwnd, menuCloseMsg, 0, 0)
				} else {
					pt := (*struct{ x, y int32 })(unsafe.Pointer(data))
					if t.menuCommandAt(pt.x, pt.y) == id {
						pPostMessageW.Call(t.hwnd, menuActionMsg, uintptr(id), 0)
					}
				}
				return 1
			}
		}
	}
	result, _, _ := callNextHook.Call(0, code, message, data)
	return result
}
