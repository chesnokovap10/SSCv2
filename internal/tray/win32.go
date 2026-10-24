package tray

import (
	"unsafe"

	"golang.org/x/sys/windows"
)

var (
	user32   = windows.NewLazySystemDLL("user32.dll")
	shell32  = windows.NewLazySystemDLL("shell32.dll")
	gdi32    = windows.NewLazySystemDLL("gdi32.dll")
	kernel32 = windows.NewLazySystemDLL("kernel32.dll")

	pRegisterClassExW      = user32.NewProc("RegisterClassExW")
	pCreateWindowExW       = user32.NewProc("CreateWindowExW")
	pDefWindowProcW        = user32.NewProc("DefWindowProcW")
	pGetMessageW           = user32.NewProc("GetMessageW")
	pTranslateMessage      = user32.NewProc("TranslateMessage")
	pDispatchMessageW      = user32.NewProc("DispatchMessageW")
	pPostQuitMessage       = user32.NewProc("PostQuitMessage")
	pPostMessageW          = user32.NewProc("PostMessageW")
	pCreatePopupMenu       = user32.NewProc("CreatePopupMenu")
	pAppendMenuW           = user32.NewProc("AppendMenuW")
	pTrackPopupMenu        = user32.NewProc("TrackPopupMenu")
	pDestroyMenu           = user32.NewProc("DestroyMenu")
	pSetForegroundWindow   = user32.NewProc("SetForegroundWindow")
	pGetCursorPos          = user32.NewProc("GetCursorPos")
	pRegisterWindowMessage = user32.NewProc("RegisterWindowMessageW")
	pCreateIconIndirect    = user32.NewProc("CreateIconIndirect")
	pDestroyIcon           = user32.NewProc("DestroyIcon")
	pMessageBoxW           = user32.NewProc("MessageBoxW")
	pDestroyWindow         = user32.NewProc("DestroyWindow")
	pGetSystemMetrics      = user32.NewProc("GetSystemMetrics")
	pSetDpiAwarenessCtx    = user32.NewProc("SetProcessDpiAwarenessContext")
	pShellNotifyIconW      = shell32.NewProc("Shell_NotifyIconW")
	pCreateDIBSection      = gdi32.NewProc("CreateDIBSection")
	pCreateBitmap          = gdi32.NewProc("CreateBitmap")
	pDeleteObject          = gdi32.NewProc("DeleteObject")
	pGetModuleHandleW      = kernel32.NewProc("GetModuleHandleW")
)

const (
	wmDestroy     = 0x0002
	wmClose       = 0x0010
	wmCommand     = 0x0111
	wmNull        = 0x0000
	wmApp         = 0x8000
	wmLButtonUp   = 0x0202
	wmRButtonUp   = 0x0205
	wmContextMenu = 0x007B

	nimAdd        = 0
	nimModify     = 1
	nimDelete     = 2
	nimSetVersion = 4
	nifMessage    = 0x1
	nifIcon       = 0x2
	nifTip        = 0x4
	nifInfo       = 0x10
	nifShowTip    = 0x80
	niifInfo      = 0x1
	niifWarning   = 0x2
	niifError     = 0x3

	mfString    = 0x0
	mfGrayed    = 0x1
	mfChecked   = 0x8
	mfPopup     = 0x10
	mfSeparator = 0x800
	mfRadioChk  = 0x200 // MFT_RADIOCHECK

	tpmReturnCmd   = 0x0100
	tpmRightButton = 0x0002
	tpmBottomAlign = 0x0020

	smCxSmIcon = 49

	mbOK          = 0x0
	mbIconInfo    = 0x40
	mbIconWarning = 0x30
	mbYesNo       = 0x4
	mbIconQuestion = 0x20
	mbSetForeground = 0x10000
	mbTopMost       = 0x40000
	idYes           = 6
)

type wndClassEx struct {
	cbSize        uint32
	style         uint32
	lpfnWndProc   uintptr
	cbClsExtra    int32
	cbWndExtra    int32
	hInstance     uintptr
	hIcon         uintptr
	hCursor       uintptr
	hbrBackground uintptr
	lpszMenuName  *uint16
	lpszClassName *uint16
	hIconSm       uintptr
}

type msgT struct {
	hwnd    uintptr
	message uint32
	wParam  uintptr
	lParam  uintptr
	time    uint32
	pt      struct{ x, y int32 }
	private uint32
}

type notifyIconData struct {
	cbSize           uint32
	hWnd             uintptr
	uID              uint32
	uFlags           uint32
	uCallbackMessage uint32
	hIcon            uintptr
	szTip            [128]uint16
	dwState          uint32
	dwStateMask      uint32
	szInfo           [256]uint16
	uVersion         uint32
	szInfoTitle      [64]uint16
	dwInfoFlags      uint32
	guidItem         windows.GUID
	hBalloonIcon     uintptr
}

type iconInfo struct {
	fIcon    int32
	xHotspot uint32
	yHotspot uint32
	hbmMask  uintptr
	hbmColor uintptr
}

type bitmapInfoHeader struct {
	biSize          uint32
	biWidth         int32
	biHeight        int32
	biPlanes        uint16
	biBitCount      uint16
	biCompression   uint32
	biSizeImage     uint32
	biXPelsPerMeter int32
	biYPelsPerMeter int32
	biClrUsed       uint32
	biClrImportant  uint32
}

func copyUTF16(dst []uint16, s string) {
	u, _ := windows.UTF16FromString(s)
	if len(u) > len(dst) {
		u = u[:len(dst)]
		u[len(u)-1] = 0
	}
	copy(dst, u)
}

// MessageBox shows a modal message (blocking; call from a goroutine).
func MessageBox(title, text string, flags uint32) int {
	t, _ := windows.UTF16PtrFromString(title)
	x, _ := windows.UTF16PtrFromString(text)
	r, _, _ := pMessageBoxW.Call(0, uintptr(unsafe.Pointer(x)), uintptr(unsafe.Pointer(t)), uintptr(flags|mbSetForeground|mbTopMost))
	return int(r)
}

// Info / Warn / Ask are MessageBox shortcuts.
func Info(title, text string) { MessageBox(title, text, mbOK|mbIconInfo) }
func Warn(title, text string) { MessageBox(title, text, mbOK|mbIconWarning) }
func Ask(title, text string) bool {
	return MessageBox(title, text, mbYesNo|mbIconQuestion) == idYes
}
