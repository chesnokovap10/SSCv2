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

	tr := &Tray{infoRows: make(map[uint32]*menuInfoRow), nextInfoID: 0x7000}
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
	if row := tr.infoRows[m.items[0].infoID]; row == nil || !row.radio || !row.checked {
		t.Fatal("radio mark was not updated")
	}

	getMenuItemInfo := user32.NewProc("GetMenuItemInfoW")
	for i, want := range []uint32{0, mfChecked} {
		info := menuItemInfo{mask: 0x01} // MIIM_STATE
		info.size = uint32(unsafe.Sizeof(info))
		ok, _, err := getMenuItemInfo.Call(handle, uintptr(i), 1, uintptr(unsafe.Pointer(&info)))
		if ok == 0 {
			t.Fatal(err)
		}
		if info.state&mfChecked != want {
			t.Errorf("item %d: state %#x, want checked bit %#x", i, info.state, want)
		}
	}
}
