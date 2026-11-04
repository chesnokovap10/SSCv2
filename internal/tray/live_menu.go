package tray

import (
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
)

const (
	mfByPosition  = 0x0400
	menuActionMsg = wmApp + 3
)

var (
	insertMenu      = user32.NewProc("InsertMenuW")
	setMenuItemInfo = user32.NewProc("SetMenuItemInfoW")
	checkMenuItem   = user32.NewProc("CheckMenuItem")
	enableMenuItem  = user32.NewProc("EnableMenuItem")
	deleteMenu      = user32.NewProc("DeleteMenu")
	mapWindowPoints = user32.NewProc("MapWindowPoints")
)

type menuItemInfo struct {
	size, mask, typ, state, id    uint32
	sub, checked, unchecked, data uintptr
	text                          *uint16
	length                        uint32
	bitmap                        uintptr
}

type liveMenu struct {
	handle   uintptr
	items    []Item
	children []*liveMenu
}

func sameMenuSlot(a, b Item) bool {
	if (a.Sub == nil) != (b.Sub == nil) {
		return false
	}
	if a.Sub != nil {
		return a.Text == b.Text || len(a.Sub) > 0 && len(b.Sub) > 0 && a.Sub[0].ID != 0 && a.Sub[0].ID == b.Sub[0].ID
	}
	return a.ID == b.ID && a.Separator == b.Separator
}

func (t *Tray) writeMenuItem(m *liveMenu, position int, it *Item, sub *liveMenu, replace bool) {
	flags, id := uintptr(mfByPosition), uintptr(it.ID)
	label, _ := windows.UTF16PtrFromString(it.Text)
	if it.informational() || it.LiveLabel {
		if replace {
			row := t.infoRows[it.infoID]
			row.text, row.scrollPeriod = it.Text, 0
			if t.infoHover.id == it.infoID {
				t.infoHover.offset, t.infoHover.start = 0, time.Now()
			}
			t.redrawMenuItem(m.handle, position)
			return
		}
		it.infoID = t.nextInfoID
		t.nextInfoID++
		t.infoRows[it.infoID] = &menuInfoRow{text: it.Text, informational: it.informational()}
		flags |= mfOwnerDraw
		if it.informational() || it.Disabled {
			flags |= mfGrayed
		}
		id = uintptr(it.infoID)
		if sub != nil {
			id, flags = sub.handle, flags|mfPopup
		}
		insertMenu.Call(m.handle, uintptr(position), flags, id, uintptr(it.infoID))
		return
	} else if it.Slider && t.Volume != nil && t.SetVolume != nil {
		if t.volumeRow == nil {
			dpi, _, _ := getDpiForWindow.Call(t.hwnd)
			level, muted, available := t.Volume()
			t.volumeRow = &menuSlider{id: it.ID, label: it.Text, menu: m.handle, scale: int32(max(dpi, 96)), level: level, muted: muted, available: available}
		}
		flags |= mfOwnerDraw
		label = nil
	} else if it.Separator {
		flags |= mfSeparator
	} else {
		if it.Checked {
			flags |= mfChecked
		}
		if it.Radio {
			flags |= mfRadioChk
		}
		if it.Disabled || it.ID == 0 && sub == nil {
			flags |= mfGrayed
		}
		if sub != nil {
			id, flags = sub.handle, flags|mfPopup
		}
	}
	if replace {
		info := menuItemInfo{mask: 0x40, text: label} // MIIM_STRING preserves native selection state
		info.size = uint32(unsafe.Sizeof(info))
		setMenuItemInfo.Call(m.handle, uintptr(position), 1, uintptr(unsafe.Pointer(&info)))
		t.redrawMenuItem(m.handle, position)
		return
	}
	insertMenu.Call(m.handle, uintptr(position), flags, id, uintptr(unsafe.Pointer(label)))
}

func (t *Tray) updateMenuState(m *liveMenu, i int, item Item) {
	old := &m.items[i]
	if old.Checked != item.Checked {
		flags := uintptr(mfByPosition)
		if item.Checked {
			flags |= mfChecked
		}
		checkMenuItem.Call(m.handle, uintptr(i), flags)
		old.Checked = item.Checked
		t.redrawMenuItem(m.handle, i)
	}
	if old.Disabled != item.Disabled {
		flags := uintptr(mfByPosition)
		if item.Disabled {
			flags |= mfGrayed
		}
		enableMenuItem.Call(m.handle, uintptr(i), flags)
		old.Disabled = item.Disabled
		t.redrawMenuItem(m.handle, i)
	}
}

// Refresh a submenu before Windows measures and paints its popup.
func (t *Tray) prepareSubmenu(m *liveMenu, next []Item, handle uintptr) {
	for i, sub := range m.children {
		if sub == nil {
			continue
		}
		for _, item := range next {
			if !sameMenuSlot(m.items[i], item) {
				continue
			}
			if sub.handle == handle {
				t.updateMenu(sub, item.Sub)
				return
			}
			if sub.find(handle) != nil {
				t.prepareSubmenu(sub, item.Sub, handle)
				return
			}
			break
		}
	}
}

func (t *Tray) hasOpenChild(m *liveMenu) bool {
	for _, handle := range t.activeMenus {
		if handle != m.handle && m.find(handle) != nil {
			return true
		}
	}
	return false
}

func (t *Tray) updateMenu(m *liveMenu, next []Item) {
	if t.hasOpenChild(m) {
		// Renaming or removing the parent row while its popup is open
		// cancels native menu tracking. Refresh children in place and
		// apply parent layout changes when the pointer returns to it.
		for i, item := range next {
			if i >= len(m.items) || !sameMenuSlot(m.items[i], item) {
				continue
			}
			old, sub := m.items[i], m.children[i]
			if old.infoID != 0 && old.Text != item.Text {
				item.infoID = old.infoID
				t.writeMenuItem(m, i, &item, sub, true)
				m.items[i].Text = item.Text
			}
			if sub != nil {
				t.updateMenu(sub, item.Sub)
			}
		}
		return
	}
	// Native Windows popups can move when a label changes their measured size.
	// Keep the visible bitrate popup's layout and update its check marks in place.
	for _, handle := range t.activeMenus {
		if handle == m.handle && m.handle != t.openMenu.handle {
			for i, item := range next {
				if i < len(m.items) && sameMenuSlot(m.items[i], item) {
					t.updateMenuState(m, i, item)
				}
			}
			return
		}
	}
	for i, item := range next {
		if i < len(m.items) && !sameMenuSlot(m.items[i], item) {
			for j := i + 1; j < len(m.items); j++ {
				if sameMenuSlot(m.items[j], item) {
					for j > i {
						t.removeMenuItem(m, i)
						j--
					}
					break
				}
			}
		}
		if i < len(m.items) && sameMenuSlot(m.items[i], item) {
			old, sub := m.items[i], m.children[i]
			item.infoID = old.infoID
			if sub != nil {
				t.updateMenu(sub, item.Sub)
			}
			t.updateMenuState(m, i, item)
			if old.Text != item.Text && !item.Slider {
				t.writeMenuItem(m, i, &item, sub, true)
			}
			m.items[i] = item
		} else {
			var sub *liveMenu
			if item.Sub != nil {
				sub = t.buildMenu(item.Sub)
			}
			t.writeMenuItem(m, i, &item, sub, false)
			m.items = append(m.items, Item{})
			copy(m.items[i+1:], m.items[i:])
			m.items[i] = item
			m.children = append(m.children, nil)
			copy(m.children[i+1:], m.children[i:])
			m.children[i] = sub
		}
		if item.Slider && t.volumeRow != nil {
			t.volumeRow.position, t.volumeRow.label = i, item.Text
		}
	}
	for len(m.items) > len(next) {
		t.removeMenuItem(m, len(next))
	}
}

func (t *Tray) refreshOpenMenu() {
	m := t.openMenu
	if m == nil {
		return
	}
	next := t.Menu()
	if t.hasOpenChild(m) {
		for i, item := range next {
			if item.LiveLabel && i < len(m.items) && !sameMenuSlot(m.items[i], item) {
				// Adding or removing a submenu while Windows tracks a child
				// cancels tracking. Reopen with the new layout immediately.
				endMenu.Call()
				t.postMenuMessage(menuOpenMsg, 0)
				return
			}
		}
	}
	t.updateMenu(m, next)
	t.rendered.Store(&next)
}

func (t *Tray) redrawMenuItem(menu uintptr, position int) {
	var r menuRect
	ok, _, _ := getMenuItemRect.Call(0, menu, uintptr(position), uintptr(unsafe.Pointer(&r)))
	if ok != 0 {
		x, y := (r.left+r.right)/2, (r.top+r.bottom)/2
		hwnd, _, _ := windowFromPoint.Call(uintptr(uint64(uint32(x)) | uint64(uint32(y))<<32))
		if hwnd != 0 {
			mapWindowPoints.Call(0, hwnd, uintptr(unsafe.Pointer(&r)), 2)
			invalidateRect.Call(hwnd, uintptr(unsafe.Pointer(&r)), 0)
		}
	}
}

func (t *Tray) removeMenuItem(m *liveMenu, i int) {
	delete(t.infoRows, m.items[i].infoID)
	if m.items[i].Slider {
		t.volumeRow = nil
	}
	deleteMenu.Call(m.handle, uintptr(i), mfByPosition)
	m.items = append(m.items[:i], m.items[i+1:]...)
	m.children = append(m.children[:i], m.children[i+1:]...)
}

func (m *liveMenu) find(handle uintptr) *liveMenu {
	if m.handle == handle {
		return m
	}
	for _, child := range m.children {
		if child != nil {
			if found := child.find(handle); found != nil {
				return found
			}
		}
	}
	return nil
}

func (t *Tray) menuCommandAt(x, y int32) int {
	for i := len(t.activeMenus) - 1; i >= 0; i-- {
		m := t.openMenu.find(t.activeMenus[i])
		if m == nil {
			continue
		}
		for pos, item := range m.items {
			var r menuRect
			ok, _, _ := getMenuItemRect.Call(0, m.handle, uintptr(pos), uintptr(unsafe.Pointer(&r)))
			if ok == 0 || x < r.left || x >= r.right || y < r.top || y >= r.bottom {
				continue
			}
			if item.Sub != nil || item.Disabled || item.Slider {
				return 0
			}
			return item.ID
		}
	}
	return 0
}

func (t *Tray) selectedMenuAction(m *msgT) bool {
	var id int
	switch m.message {
	case 0x0201, 0x0204: // WM_LBUTTONDOWN, WM_RBUTTONDOWN
		return t.menuCommandAt(m.pt.x, m.pt.y) != 0
	case wmLButtonUp, wmRButtonUp:
		id = t.menuCommandAt(m.pt.x, m.pt.y)
	case 0x0100: // WM_KEYDOWN
		if (m.wParam == 0x0d || m.wParam == 0x20) && t.selectedMenu != 0 &&
			t.selectedFlags&(mfPopup|mfGrayed|2|mfSeparator) == 0 &&
			(t.volumeRow == nil || t.selectedID != t.volumeRow.id) {
			id = t.selectedID
		}
	}
	if id == 0 {
		return false
	}
	t.ActivateMenuItem(id)
	return true
}
