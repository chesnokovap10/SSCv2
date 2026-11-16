package tray

import (
	"testing"
	"unsafe"
)

func TestOwnerDrawMeasuresSlider(t *testing.T) {
	tr := &Tray{volumeRow: &menuSlider{id: 7, scale: 96}}
	item := measureMenuItem{kind: 1, id: 7}
	if !tr.ownerDrawMessage(wmMeasureItem, uintptr(unsafe.Pointer(&item))) {
		t.Fatal("slider measure was not handled")
	}
	if item.width != 236 || item.height != 48 {
		t.Fatalf("slider size = %dx%d, want 236x48", item.width, item.height)
	}
}

func TestRefreshUpdatesHeaderBatteryWithoutChangingTitle(t *testing.T) {
	header := Item{ID: 1, Text: "SSCv2 — connected headphones", LiveLabel: true}
	tr := &Tray{infoRows: make(map[uint32]*menuInfoRow), nextInfoID: 0x7000}
	root := tr.buildMenu([]Item{header})
	defer pDestroyMenu.Call(root.handle)
	tr.openMenu = root
	rowID := root.items[0].infoID
	for _, right := range []string{"100%|100%", "87%|92%", ""} {
		header.RightText = right
		tr.updateMenu(root, []Item{header})
		if root.items[0].infoID != rowID || tr.infoRows[rowID].rightText != right {
			t.Fatalf("updating battery to %q did not repaint the existing header", right)
		}
	}
}

func TestRefreshWhileOldBitratePopupIsOpen(t *testing.T) {
	bitrates := Item{ID: 1, Text: "Bitrate", LiveLabel: true, SubRevision: "ssc_uhq",
		Sub: []Item{{ID: 2, Text: "Auto", Radio: true}}}
	off := Item{ID: 1, Text: "Bitrate unavailable", LiveLabel: true, Disabled: true, Sub: []Item{}}
	tr := &Tray{
		Menu:     func() []Item { return []Item{off} },
		infoRows: make(map[uint32]*menuInfoRow), nextInfoID: 0x7000,
	}
	root := tr.buildMenu([]Item{bitrates})
	defer pDestroyMenu.Call(root.handle)
	popup := root.children[0]
	tr.openMenu = root
	tr.activeMenus = []uintptr{root.handle, popup.handle}
	tr.refreshOpenMenu()
	row := tr.RenderedMenu()[0]
	if row.Disabled || len(row.Sub) != 1 || !row.Sub[0].Disabled {
		t.Fatalf("tracked popup must keep its parent and disable the old choice: %+v", row)
	}
	tr.activeMenus = tr.activeMenus[:1]
	tr.refreshOpenMenu()
	row = tr.RenderedMenu()[0]
	if !row.Disabled || len(row.Sub) != 0 || root.children[0] != popup {
		t.Fatalf("bitrate row did not settle after leaving the popup: %+v", row)
	}
}

func TestRefreshKeepsCodecPopupDuringBitrateLayoutChange(t *testing.T) {
	for _, startWithBitrates := range []bool{false, true} {
		codec := Item{Text: "Codec", LiveLabel: true, Sub: []Item{
			{ID: 1, Text: "Off", Radio: true, Checked: !startWithBitrates},
			{ID: 2, Text: "AAC", Radio: true, Checked: startWithBitrates},
		}}
		unavailable := Item{ID: 4, Text: "Bitrate unavailable", LiveLabel: true, Sub: []Item{}, Disabled: true}
		available := Item{ID: 4, Text: "Bitrate", LiveLabel: true, Sub: []Item{{ID: 3, Text: "Auto", Radio: true}}}
		before, after := unavailable, available
		if startWithBitrates {
			before, after = available, unavailable
		}
		nextCodec := codec
		nextCodec.Sub = append([]Item(nil), codec.Sub...)
		for i := range nextCodec.Sub {
			nextCodec.Sub[i].Checked = !nextCodec.Sub[i].Checked
		}
		tr := &Tray{
			Menu:     func() []Item { return []Item{nextCodec, after} },
			infoRows: make(map[uint32]*menuInfoRow), nextInfoID: 0x7000,
		}
		root := tr.buildMenu([]Item{codec, before})
		popup := root.children[0]
		bitrates := root.children[1]
		tr.openMenu = root
		tr.activeMenus = []uintptr{root.handle, popup.handle}
		tr.refreshOpenMenu()
		if root.children[0] != popup || root.children[1] != bitrates {
			t.Error("menu layout changed while the codec popup was open")
		}
		for i, item := range popup.items {
			if item.Checked != nextCodec.Sub[i].Checked {
				t.Errorf("codec item %d: check mark did not update", item.ID)
			}
		}
		row := root.items[1]
		if row.Text != after.Text || row.Disabled != after.Disabled || len(bitrates.items) != len(after.Sub) {
			t.Error("bitrate row did not update while the codec popup was open")
		}
		pDestroyMenu.Call(root.handle)
	}
}

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
