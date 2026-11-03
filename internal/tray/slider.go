package tray

import (
	"fmt"
	"syscall"
	"unsafe"

	"golang.org/x/sys/windows"
)

const (
	wmDrawItem    = 0x002b
	wmMeasureItem = 0x002c
	wmTimer       = 0x0113
	wmMenuSelect  = 0x011f
	mfOwnerDraw   = 0x0100
)

var (
	getMenuItemRect    = user32.NewProc("GetMenuItemRect")
	windowFromPoint    = user32.NewProc("WindowFromPoint")
	invalidateRect     = user32.NewProc("InvalidateRect")
	setTimer           = user32.NewProc("SetTimer")
	killTimer          = user32.NewProc("KillTimer")
	fillRect           = user32.NewProc("FillRect")
	getSysColorBrush   = user32.NewProc("GetSysColorBrush")
	getSysColor        = user32.NewProc("GetSysColor")
	createSolidBrush   = gdi32.NewProc("CreateSolidBrush")
	roundRect          = gdi32.NewProc("RoundRect")
	selectObject       = gdi32.NewProc("SelectObject")
	getStockObject     = gdi32.NewProc("GetStockObject")
	setBkMode          = gdi32.NewProc("SetBkMode")
	setTextColor       = gdi32.NewProc("SetTextColor")
	drawText           = user32.NewProc("DrawTextW")
	menuFilterCallback = syscall.NewCallback(menuFilter)
	getDpiForWindow    = user32.NewProc("GetDpiForWindow")
)

type menuRect struct{ left, top, right, bottom int32 }

type menuSlider struct {
	id, position                                      int
	label                                             string
	menu                                              uintptr
	scale                                             int32
	level                                             uint8
	available, dragging, selected, muted, mutePressed bool
}

type measureMenuItem struct {
	kind, control, id, width, height uint32
	data                             uintptr
}

type drawMenuItem struct {
	kind, control, id, action, state uint32
	menu, dc                         uintptr
	rect                             menuRect
	data                             uintptr
}

func (s *menuSlider) px(n int32) int32 { return (n*s.scale + 48) / 96 }

func (s *menuSlider) track(r menuRect) (int32, int32) {
	return r.left + s.px(58), r.right - s.px(24)
}

func (s *menuSlider) draw(it *drawMenuItem) {
	r, dc := it.rect, it.dc
	background, _, _ := getSysColorBrush.Call(4) // COLOR_MENU
	fillRect.Call(dc, uintptr(unsafe.Pointer(&r)), background)

	textRect := menuRect{r.left + s.px(20), r.top + s.px(5), r.right - s.px(20), r.top + s.px(24)}
	colorIndex := uintptr(7) // COLOR_MENUTEXT
	if !s.available {
		colorIndex = 17 // COLOR_GRAYTEXT
	}
	color, _, _ := getSysColor.Call(colorIndex)
	oldColor, _, _ := setTextColor.Call(dc, color)
	oldMode, _, _ := setBkMode.Call(dc, 1) // TRANSPARENT
	for _, entry := range []struct {
		label     string
		alignment uintptr
	}{
		{s.label, 0},
		{fmt.Sprintf("%d%%", (int(s.level)*100+63)/127), 2},
	} {
		label, _ := windows.UTF16PtrFromString(entry.label)
		drawText.Call(dc, uintptr(unsafe.Pointer(label)), ^uintptr(0), uintptr(unsafe.Pointer(&textRect)), 0x820|entry.alignment)
	}

	left, right := s.track(r)
	center := r.top + s.px(34)
	pos := left + (right-left)*int32(s.level)/127
	highlight, _, _ := getSysColor.Call(13) // COLOR_HIGHLIGHT
	shadow, _, _ := getSysColor.Call(16)    // COLOR_BTNSHADOW
	if !s.available || s.muted {
		highlight = shadow
	}
	pen, _, _ := getStockObject.Call(8) // NULL_PEN
	oldPen, _, _ := selectObject.Call(dc, pen)
	paint := func(x1, y1, x2, y2, diameter int32, color uintptr) {
		brush, _, _ := createSolidBrush.Call(color)
		old, _, _ := selectObject.Call(dc, brush)
		roundRect.Call(dc, uintptr(x1), uintptr(y1), uintptr(x2), uintptr(y2), uintptr(diameter), uintptr(diameter))
		selectObject.Call(dc, old)
		pDeleteObject.Call(brush)
	}
	paint(left, center-s.px(2), right, center+s.px(2), s.px(4), shadow)
	if pos > left {
		paint(left, center-s.px(2), pos, center+s.px(2), s.px(4), highlight)
	}
	radius := s.px(6)
	if s.dragging || s.selected {
		radius = s.px(7)
	}
	paint(pos-radius, center-radius, pos+radius, center+radius, radius*2, highlight)
	button := s.muteBounds(r)
	buttonColor, _, _ := getSysColor.Call(15) // COLOR_BTNFACE
	if s.muted || s.mutePressed {
		buttonColor, _, _ = getSysColor.Call(13)
		textColor, _, _ := getSysColor.Call(14) // COLOR_HIGHLIGHTTEXT
		setTextColor.Call(dc, textColor)
	}
	paint(button.left, button.top, button.right, button.bottom, s.px(7), buttonColor)
	icon := "🔊"
	if s.muted {
		icon = "🔇"
	}
	glyph, _ := windows.UTF16PtrFromString(icon)
	drawText.Call(dc, uintptr(unsafe.Pointer(glyph)), ^uintptr(0), uintptr(unsafe.Pointer(&button)), 0x825)
	selectObject.Call(dc, oldPen)
	setTextColor.Call(dc, oldColor)
	setBkMode.Call(dc, oldMode)
}

func (s *menuSlider) muteBounds(r menuRect) menuRect {
	return menuRect{r.left + s.px(16), r.top + s.px(23), r.left + s.px(46), r.top + s.px(45)}
}

func (s *menuSlider) bounds() (menuRect, bool) {
	var r menuRect
	ok, _, _ := getMenuItemRect.Call(0, s.menu, uintptr(s.position), uintptr(unsafe.Pointer(&r)))
	return r, ok != 0
}

func (s *menuSlider) redraw() {
	r, ok := s.bounds()
	if ok {
		x, y := (r.left+r.right)/2, (r.top+r.bottom)/2
		hwnd, _, _ := windowFromPoint.Call(uintptr(uint64(uint32(x)) | uint64(uint32(y))<<32))
		if hwnd != 0 {
			invalidateRect.Call(hwnd, 0, 0)
		}
	}
}

func (t *Tray) refreshMenuSlider() {
	s := t.volumeRow
	level, muted, available := t.Volume()
	if s.level != level || s.available != available || s.muted != muted {
		s.level, s.muted, s.available = level, muted, available
		s.redraw()
	}
}

// TrackPopupMenu consumes its own input. Intercept only the slider gesture
// so the native menu still handles submenus, dismissal and other commands.
func menuFilter(code, wparam, lparam uintptr) uintptr {
	t := current
	if int32(code) == 2 && t.openMenu != nil { // MSGF_MENU
		s := t.volumeRow
		m := (*msgT)(unsafe.Pointer(lparam))
		if (s == nil || !s.dragging && !s.mutePressed) && t.handleIconClick(m) {
			return 1
		}
		if s != nil {
			switch m.message {
			case 0x0201, wmLButtonUp, 0x0200: // button down, button up, mouse move
				r, ok := s.bounds()
				if ok {
					x, y := m.pt.x, m.pt.y
					hit := x >= r.left && x < r.right && y >= r.top && y < r.bottom
					button := s.muteBounds(r)
					onMute := x >= button.left && x < button.right && y >= button.top && y < button.bottom
					if m.message == 0x0201 && hit {
						s.mutePressed = onMute
						s.dragging = !onMute
					}
					if s.mutePressed {
						if m.message == wmLButtonUp {
							s.mutePressed = false
							if onMute && s.available && t.ToggleMute != nil {
								t.ToggleMute()
								t.refreshMenuSlider()
							}
						}
						s.redraw()
						return 1
					}
					if s.dragging {
						left, right := s.track(r)
						if s.available && right > left {
							level := uint8((min(max(x, left), right) - left) * 127 / (right - left))
							t.SetVolume(level)
							t.refreshMenuSlider()
						}
						if m.message == wmLButtonUp {
							s.dragging = false
						}
						s.redraw()
						return 1
					}
				}
			case 0x0100: // WM_KEYDOWN
				if s.selected && s.available && m.wParam == 0x20 && t.ToggleMute != nil {
					t.ToggleMute()
					t.refreshMenuSlider()
					return 1
				}
				if s.selected && s.available && (m.wParam == 0x25 || m.wParam == 0x27) {
					step := 3
					if m.wParam == 0x25 {
						step = -step
					}
					t.SetVolume(uint8(min(127, max(0, int(s.level)+step))))
					t.refreshMenuSlider()
					return 1
				}
			}
		}
		if t.selectedMenuAction(m) {
			return 1
		}
	}

	result, _, _ := callNextHook.Call(0, code, wparam, lparam)
	return result
}

func (t *Tray) sliderMessage(msg, wp, lp uintptr) bool {
	s := t.volumeRow
	if s == nil {
		return false
	}
	switch msg {
	case wmMeasureItem:
		it := (*measureMenuItem)(unsafe.Pointer(lp))
		if it.kind == 1 && int(it.id) == s.id {
			it.width, it.height = uint32(s.px(236)), uint32(s.px(48))
			return true
		}
	case wmDrawItem:
		it := (*drawMenuItem)(unsafe.Pointer(lp))
		if it.kind == 1 && int(it.id) == s.id {
			s.selected = it.state&1 != 0
			s.draw(it)
			return true
		}
	case wmMenuSelect:
		if lp != s.menu || int(wp&0xffff) != s.id {
			s.selected = false
		}
	case wmTimer:
		if wp == 1 {
			t.refreshMenuSlider()
			return true
		}
	}
	return false
}

// Handle the click before the menu loop passes it on to Explorer.
func (t *Tray) handleIconClick(m *msgT) bool {
	const wmLButtonDown, wmRButtonDown = 0x0201, 0x0204
	switch m.message {
	case wmLButtonDown, wmRButtonDown, wmLButtonUp, wmRButtonUp:
	default:
		return false
	}
	r := t.menuIconBounds
	if m.pt.x < r.left || m.pt.x >= r.right || m.pt.y < r.top || m.pt.y >= r.bottom {
		return false
	}
	if m.message == wmLButtonUp || m.message == wmRButtonUp {
		endMenu.Call()
	}
	return true
}
