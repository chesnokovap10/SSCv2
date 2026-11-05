package tray

import (
	"testing"
	"unsafe"
)

func TestRadioMenuItem(t *testing.T) {
	handle, _, err := user32.NewProc("CreatePopupMenu").Call()
	if handle == 0 {
		t.Fatal(err)
	}
	defer user32.NewProc("DestroyMenu").Call(handle)

	tr := &Tray{}
	m := &liveMenu{handle: handle, items: []Item{
		{ID: 1, Text: "Radio", Radio: true},
		{ID: 2, Text: "Checkbox", Checked: true},
	}}
	for i := range m.items {
		tr.writeMenuItem(m, i, &m.items[i], nil, false)
	}
	item := m.items[0]
	item.Checked = true
	tr.updateMenuState(m, 0, item)

	getMenuItemInfo := user32.NewProc("GetMenuItemInfoW")
	for i, want := range []uint32{mfRadioChk, 0} {
		info := menuItemInfo{mask: miimFType | 0x01} // MIIM_FTYPE | MIIM_STATE
		info.size = uint32(unsafe.Sizeof(info))
		ok, _, err := getMenuItemInfo.Call(handle, uintptr(i), 1, uintptr(unsafe.Pointer(&info)))
		if ok == 0 {
			t.Fatal(err)
		}
		if info.typ&mfRadioChk != want || info.state&mfChecked == 0 {
			t.Errorf("item %d: type %#x, state %#x; want radio bit %#x and checked state", i, info.typ, info.state, want)
		}
	}
}
