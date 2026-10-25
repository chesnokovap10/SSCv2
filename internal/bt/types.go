package bt

import (
	"fmt"
	"sscv2/internal/i18n"
	"strings"
)

// Addr is a Bluetooth device address in BTstack (big-endian, display)
// order: Addr{0x40,0x5E,...} prints as "40:5E:...".
type Addr [6]byte

func (a Addr) String() string {
	return fmt.Sprintf("%02X:%02X:%02X:%02X:%02X:%02X", a[0], a[1], a[2], a[3], a[4], a[5])
}

// ParseAddr accepts "AA:BB:CC:DD:EE:FF", "AA-BB-..." or "aabbccddeeff".
func ParseAddr(s string) (Addr, error) {
	var a Addr
	h := strings.NewReplacer(":", "", "-", "", " ", "").Replace(strings.TrimSpace(s))
	if len(h) != 12 {
		return a, fmt.Errorf(i18n.T("неверный адрес %q", "invalid address %q"), s)
	}
	for i := 0; i < 6; i++ {
		var b byte
		if _, err := fmt.Sscanf(h[i*2:i*2+2], "%02x", &b); err != nil {
			return a, fmt.Errorf(i18n.T("неверный адрес %q", "invalid address %q"), s)
		}
		a[i] = b
	}
	return a, nil
}

// LinkKey is a BR/EDR link key in HCI (little-endian) order, as BTstack
// and the Windows registry store it.
type LinkKey [16]byte

// KeyStore persists BR/EDR link keys. Called on the BTstack thread.
type KeyStore interface {
	Get(a Addr) (LinkKey, int, bool)
	Put(a Addr, k LinkKey, typ int)
	Delete(a Addr)
	At(i int) (Addr, LinkKey, int, bool)
}

// Codec of the A2DP stream.
type Codec int

const (
	CodecSBC Codec = iota
	CodecAAC
	CodecSSC
)

func (c Codec) String() string {
	switch c {
	case CodecAAC:
		return "AAC"
	case CodecSSC:
		return "SSC"
	}
	return "SBC"
}

// RemoteCaps are the codecs the sink advertised.
type RemoteCaps struct {
	SBC, AAC, SSC             bool
	SBCSeid, AACSeid, SSCSeid uint8
	SSCCap                    uint8
	SSCUHQ                    bool
	AACBitrate                uint32
}

// Found is an inquiry result.
type Found struct {
	Addr Addr
	Name string
	CoD  uint32
	RSSI int8
}

// IsAudio reports a Class-of-Device in the Audio/Video major class.
func (f Found) IsAudio() bool { return (f.CoD>>8)&0x1F == 0x04 }

// EventKind enumerates asynchronous notifications.
type EventKind int

const (
	EvDisconnected   EventKind = iota // audio link to the headphones lost
	EvVolume                          // headphones changed their volume
	EvLinkKey                         // a new BR/EDR link key was stored
	EvMouse                           // mouse state changed (MouseState)
	EvAVRCPConnected                  // AVRCP is up (volume can be sent)
	EvVolumeApplied                   // headphones confirmed our level (again)
	EvACLUp                           // a BR/EDR link came up (e.g. headphones reconnecting)
	EvA2DPReady                       // A2DP signalling + codec discovery done (any direction)
	EvMediaKey                        // a button on the headphones (Key: MediaPlayPause, MediaNext, ...)
)

// Media keys the headphones send (AVRCP PASS_THROUGH, button pressed).
const (
	MediaPlayPause = iota + 1 // PLAY or PAUSE (one tap)
	MediaNext                 // FORWARD (double tap)
	MediaPrev                 // BACKWARD (triple tap)
	MediaStop
)

// Event is delivered on Events().
type Event struct {
	Kind    EventKind
	Addr    Addr
	Volume  uint8
	Key     LinkKey
	KeyType int
	Mouse   string
	Media   int // EvMediaKey: MediaPlayPause, MediaNext, MediaPrev, MediaStop
}

// Options for Start.
type Options struct {
	Keys      KeyStore
	Logf      func(string, ...any)
	Verbose   bool // forward BTstack log_info lines
	USBIDs    [][2]uint16
	LocalName string
	Mouse     *LEBond // nil = no LE mouse bridge
	// ClassicMouse: a BR/EDR HID mouse (link key from Keys) instead of an LE one.
	ClassicMouse *Addr
	EnableSSC bool    // offer the SSC endpoint (only when SSC can be encoded)
	SSCCap    uint8   // SSC configuration byte to send (0 = like the phone)
	Debug     bool    // packet journal (logx debug mode)
	// ForceMediaMTU: treat the headphones' media channel MTU as this many
	// bytes instead of what they announced (Settings > Max MTU).
	ForceMediaMTU int
}

// LEBond is an imported LE bond (mouse).
type LEBond struct {
	Addr       Addr
	Random     bool // random (static) address
	LTK        [16]byte
	IRK        [16]byte
	EDIV       uint16
	Rand       [8]byte
	KeySize    int
	SecureConn bool
}
