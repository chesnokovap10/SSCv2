package tray

import (
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
)

const infoWidth = 236

var (
	getTextExtent = gdi32.NewProc("GetTextExtentPoint32W")
	extTextOut    = gdi32.NewProc("ExtTextOutW")
)

type menuInfoRow struct {
	text          string
	minWidth      int32
	scrollPeriod  int32
	informational bool
	radio         bool
	checked       bool
}

type menuInfoHover struct {
	id     uint32
	menu   uintptr
	pos    int
	start  time.Time
	offset int32
}

func (t *Tray) menuPixels(n int32) int32 {
	dpi, _, _ := getDpiForWindow.Call(t.hwnd)
	return (n*int32(max(dpi, 96)) + 48) / 96
}

func (t *Tray) infoMessage(msg, lp uintptr) bool {
	switch msg {
	case wmMeasureItem:
		it := (*measureMenuItem)(unsafe.Pointer(lp))
		if row := t.infoRows[uint32(it.data)]; it.kind == 1 && row != nil {
			it.width = uint32(t.menuPixels(max(infoWidth, row.minWidth)))
			it.height = uint32(t.menuPixels(22))
			return true
		}
	case wmDrawItem:
		it := (*drawMenuItem)(unsafe.Pointer(lp))
		if row := t.infoRows[uint32(it.data)]; it.kind == 1 && row != nil {
			t.drawInfoRow(it, row)
			return true
		}
	}
	return false
}

func (t *Tray) drawInfoRow(it *drawMenuItem, row *menuInfoRow) {
	r := it.rect
	background, foreground := uintptr(4), uintptr(7) // COLOR_MENU, COLOR_MENUTEXT
	if row.informational || it.state&6 != 0 {
		foreground = 17 // COLOR_GRAYTEXT
	}
	if row.informational && t.infoHover.id == uint32(it.data) || it.state&1 != 0 {
		background, foreground = 13, 14 // COLOR_HIGHLIGHT, COLOR_HIGHLIGHTTEXT
	}
	brush, _, _ := getSysColorBrush.Call(background)
	fillRect.Call(it.dc, uintptr(unsafe.Pointer(&r)), brush)
	r.left += t.menuPixels(20)
	r.right -= t.menuPixels(20)

	const textFlags = 0x0820 // DT_SINGLELINE | DT_NOPREFIX
	label, _ := windows.UTF16FromString(row.text)
	if len(label) == 0 {
		return
	}
	var extent struct{ width, height int32 }
	getTextExtent.Call(it.dc, uintptr(unsafe.Pointer(&label[0])), uintptr(len(label)-1), uintptr(unsafe.Pointer(&extent)))
	row.scrollPeriod = 0
	if extent.width > r.right-r.left {
		row.scrollPeriod = extent.width + t.menuPixels(24)
	}
	color, _, _ := getSysColor.Call(foreground)
	oldColor, _, _ := setTextColor.Call(it.dc, color)
	oldMode, _, _ := setBkMode.Call(it.dc, 1)
	if row.checked {
		mark := it.rect
		mark.right = r.left
		dot := uint16('✓')
		if row.radio {
			dot = '●'
		}
		drawText.Call(it.dc, uintptr(unsafe.Pointer(&dot)), 1, uintptr(unsafe.Pointer(&mark)), textFlags|0x5) // DT_CENTER | DT_VCENTER
	}
	if t.infoHover.id == uint32(it.data) && row.scrollPeriod > 0 {
		x := r.left - t.infoHover.offset%row.scrollPeriod
		y := r.top + (r.bottom-r.top-extent.height)/2
		for ; x < r.right; x += row.scrollPeriod {
			extTextOut.Call(it.dc, uintptr(x), uintptr(y), 4, uintptr(unsafe.Pointer(&r)), // ETO_CLIPPED
				uintptr(unsafe.Pointer(&label[0])), uintptr(len(label)-1), 0)
		}
	} else {
		drawText.Call(it.dc, uintptr(unsafe.Pointer(&label[0])), uintptr(len(label)-1), uintptr(unsafe.Pointer(&r)), textFlags|0x8004) // DT_END_ELLIPSIS | DT_VCENTER
	}
	setTextColor.Call(it.dc, oldColor)
	setBkMode.Call(it.dc, oldMode)
}

func (t *Tray) infoAtCursor() (uint32, uintptr, int) {
	var pt struct{ x, y int32 }
	ok, _, _ := pGetCursorPos.Call(uintptr(unsafe.Pointer(&pt)))
	if ok != 0 {
		for i := len(t.activeMenus) - 1; i >= 0; i-- {
			m := t.openMenu.find(t.activeMenus[i])
			if m == nil {
				continue
			}
			for pos, item := range m.items {
				var r menuRect
				ok, _, _ := getMenuItemRect.Call(0, m.handle, uintptr(pos), uintptr(unsafe.Pointer(&r)))
				if ok != 0 && pt.x >= r.left && pt.x < r.right && pt.y >= r.top && pt.y < r.bottom {
					// Windows handles hover repainting for native rows.
					if item.infoID == 0 {
						return 0, 0, 0
					}
					return item.infoID, m.handle, pos
				}
			}
		}
	}
	return 0, 0, 0
}

func (t *Tray) refreshInfoHover() {
	h := &t.infoHover
	id, menu, pos := t.infoAtCursor()
	now := time.Now()
	if h.id != id {
		oldMenu, oldPos := h.menu, h.pos
		*h = menuInfoHover{id: id, menu: menu, pos: pos, start: now}
		if oldMenu != 0 {
			t.redrawMenuItem(oldMenu, oldPos)
		}
		if id != 0 {
			t.redrawMenuItem(menu, pos)
		}
		return
	}
	row := t.infoRows[id]
	if row == nil || row.scrollPeriod == 0 {
		return
	}
	h.menu, h.pos = menu, pos
	distance := now.Sub(h.start) * time.Duration(t.menuPixels(55)) / time.Second
	offset := int32(distance % time.Duration(row.scrollPeriod))
	if h.offset != offset {
		h.offset = offset
		t.redrawMenuItem(menu, pos)
	}
}
