package engine

import (
	"unsafe"

	"golang.org/x/sys/windows"
)

var procSendInput = windows.NewLazySystemDLL("user32.dll").NewProc("SendInput")

// keyboard INPUT for x64: type(4) + pad(4) + KEYBDINPUT(24) + pad to 40.
type keyInput struct {
	typ   uint32
	_     uint32
	vk    uint16
	scan  uint16
	flags uint32
	time  uint32
	_     uint32
	extra uintptr
	_     [8]byte
}

// Windows media keys (VK_MEDIA_*).
const (
	vkMediaNext      = 0xB0
	vkMediaPrev      = 0xB1
	vkMediaStop      = 0xB2
	vkMediaPlayPause = 0xB3
)

// pressKey presses and releases a virtual key (media keys go to the player
// that owns the Windows media session: browsers, Spotify, players).
func pressKey(vk uint16) {
	const keyUp = 0x0002
	in := [2]keyInput{
		{typ: 1, vk: vk},
		{typ: 1, vk: vk, flags: keyUp},
	}
	procSendInput.Call(2, uintptr(unsafe.Pointer(&in[0])), unsafe.Sizeof(in[0]))
}

// mediaPlayPause presses the system Play/Pause media key (browsers and
// players pause on it, like when Bluetooth headphones go into their case).
func mediaPlayPause() { pressKey(vkMediaPlayPause) }
