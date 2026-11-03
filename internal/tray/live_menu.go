package tray

import (
	"reflect"
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
	deleteMenu      = user32.NewProc("DeleteMenu")
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

func (t *Tray) writeMenuItem(m *liveMenu, position int, it Item, sub *liveMenu, replace bool) {
	flags, id := uintptr(mfByPosition), uintptr(it.ID)
	label, _ := windows.UTF16PtrFromString(it.Text)
	if it.Slider && t.Volume != nil && t.SetVolume != nil {
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
		info := menuItemInfo{mask: 0x141, typ: uint32(flags & (mfOwnerDraw | mfRadioChk | mfSeparator)),
			state: uint32(flags & (mfChecked | mfGrayed)), text: label}
		info.size = uint32(unsafe.Sizeof(info))
		setMenuItemInfo.Call(m.handle, uintptr(position), 1, uintptr(unsafe.Pointer(&info)))
		t.redrawMenuItem(m.handle, position)
		return
	}
	insertMenu.Call(m.handle, uintptr(position), flags, id, uintptr(unsafe.Pointer(label)))
}

func (t *Tray) updateMenu(m *liveMenu, next []Item) {
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
			if sub != nil {
				t.updateMenu(sub, item.Sub)
			}
			old.Sub = item.Sub
			if !reflect.DeepEqual(old, item) {
				t.writeMenuItem(m, i, item, sub, true)
			}
			m.items[i] = item
		} else {
			var sub *liveMenu
			if item.Sub != nil {
				sub = t.buildMenu(item.Sub)
			}
			t.writeMenuItem(m, i, item, sub, false)
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

func (t *Tray) redrawMenuItem(menu uintptr, position int) {
	var r menuRect
	ok, _, _ := getMenuItemRect.Call(0, menu, uintptr(position), uintptr(unsafe.Pointer(&r)))
	if ok != 0 {
		x, y := (r.left+r.right)/2, (r.top+r.bottom)/2
		hwnd, _, _ := windowFromPoint.Call(uintptr(uint64(uint32(x)) | uint64(uint32(y))<<32))
		if hwnd != 0 {
			invalidateRect.Call(hwnd, 0, 0)
		}
	}
}

func (t *Tray) removeMenuItem(m *liveMenu, i int) {
	if m.items[i].Slider {
		t.volumeRow = nil
	}
	deleteMenu.Call(m.handle, uintptr(i), mfByPosition)
	m.items = append(m.items[:i], m.items[i+1:]...)
	m.children = append(m.children[:i], m.children[i+1:]...)
}

func (t *Tray) selectedMenuAction(m *msgT) bool {
	if t.selectedMenu == 0 || t.selectedID == 0 || t.selectedFlags&(mfPopup|mfGrayed|2|mfSeparator) != 0 ||
		t.volumeRow != nil && t.selectedID == t.volumeRow.id {
		return false
	}
	switch m.message {
	case wmLButtonUp, wmRButtonUp:
		// Resolve the highlighted command's rectangle on the active submenu.
		var r menuRect
		position := uintptr(0)
		for {
			ok, _, _ := getMenuItemRect.Call(0, t.selectedMenu, position, uintptr(unsafe.Pointer(&r)))
			if ok == 0 {
				return false
			}
			id, _, _ := getMenuItemID.Call(t.selectedMenu, position)
			if int(id) == t.selectedID {
				break
			}
			position++
		}
		if m.pt.x < r.left || m.pt.x >= r.right || m.pt.y < r.top || m.pt.y >= r.bottom {
			return false
		}
	case 0x0100: // WM_KEYDOWN
		if m.wParam != 0x0d && m.wParam != 0x20 {
			return false
		}
	default:
		return false
	}
	pPostMessageW.Call(t.hwnd, menuActionMsg, uintptr(t.selectedID), 0)
	return true
}

var getMenuItemID = user32.NewProc("GetMenuItemID")
