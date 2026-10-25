// Package config holds file locations and the persisted user settings.
package config

import (
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"runtime"
	"sync"

	"sscv2/internal/logx"
)

const AppName = "SSCv2"

// Mode is the selected operating mode of the tray app.
type Mode string

const (
	ModeOff Mode = "off" // adapter belongs to Windows Bluetooth
	ModeAAC Mode = "aac" // adapter in WinUSB mode, AAC to the headphones
	ModeSSC Mode = "ssc" // adapter in WinUSB mode, SSC (libssc) to the headphones
	// ModeSSCUHQ: SSC UHQ, 96 kHz (the capture upsampled 2x)
	ModeSSCUHQ Mode = "ssc_uhq"
)

// Streaming reports a mode that owns the adapter (not "off").
func (m Mode) Streaming() bool { return m == ModeAAC || m == ModeSSC || m == ModeSSCUHQ }

// EngineCodec is the codec the engine streams in this mode.
func (m Mode) EngineCodec() string {
	if m == ModeAAC {
		return "aac"
	}
	return "ssc"
}

// UHQBitrates (kbps) are the SSC UHQ (96 kHz) rates; the rest are basic.
var UHQBitrates = []int{152, 250, 291, 308, 442, 584, 886}

func isUHQ(kbps int) bool {
	for _, b := range UHQBitrates {
		if b == kbps {
			return true
		}
	}
	return false
}

// Device is a remembered Bluetooth peer.
type Device struct {
	Addr string `json:"addr"` // "AA:BB:CC:DD:EE:FF"
	Name string `json:"name,omitempty"`
}

// Settings are per-user and live in %APPDATA%\SSCv2\settings.json.
type Settings struct {
	Mode       Mode    `json:"mode"`
	Headphones *Device `json:"headphones,omitempty"`
	Mouse      *Device `json:"mouse,omitempty"`
	// Adapter USB id; zero means "first known MediaTek adapter found".
	VID uint16 `json:"vid,omitempty"`
	PID uint16 `json:"pid,omitempty"`
	// Mute the laptop speakers while streaming from the default output
	// (only used when the virtual headphones device is not installed).
	MuteSpeakers *bool `json:"muteSpeakers,omitempty"`
	// Debug: detailed journal (logs\debug.log) of switches, device
	// exchanges and volume.
	Debug bool `json:"debug,omitempty"`
	// Lang: "ru" | "en"; "" = the Windows UI language.
	Lang string `json:"lang,omitempty"`
	// MaxMTU: media packets of up to 1017 bytes instead of the 679 the
	// Galaxy Buds2 Pro announce (they play them cleanly; other headphones
	// may not): AAC 256 kbps, larger SSC frames.
	MaxMTU bool `json:"maxMTU,omitempty"`
	// AACMode: "" / "fit" (every frame fits one packet) or "frag"
	// (diagnostics: frames split over two packets). The old "over" is
	// MaxMTU now.
	AACMode string `json:"aacMode,omitempty"`
	// AACBitrate: AAC kbps; 0 = as high as one packet allows.
	AACBitrate int `json:"aacBitrate,omitempty"`
	// SSCBitrate: SSC kbps (88..328); 0 = like the phone (192, 128 when the
	// headphones announce a limit). Frames above the headphones' packet
	// size go in larger packets, as MaxMTU does.
	SSCBitrate int `json:"sscBitrate,omitempty"`
	// SSCUHQBitrate: SSC UHQ kbps (152..886); 0 = as high as one packet allows.
	SSCUHQBitrate int `json:"sscUhqBitrate,omitempty"`
	// SSCCap: SSC configuration byte sent to the headphones (experiments,
	// "ctl ssccap"); 0 = like the phone (0x04 | their 0x08 bit, UHQ 0x02 |
	// their 0x08). Not saved: a leftover experiment (0x0E: the UHQ bit on a
	// 48 kHz stream) made the sound stutter.
	SSCCap int `json:"-"`
}

// Bitrate is the chosen kbps for a mode's codec (0 = auto).
func (s *Settings) Bitrate(m Mode) int {
	switch m {
	case ModeAAC:
		return s.AACBitrate
	case ModeSSC:
		return s.SSCBitrate
	case ModeSSCUHQ:
		return s.SSCUHQBitrate
	}
	return 0
}

// SetBitrate stores the kbps for a mode's codec (0 = auto).
func (s *Settings) SetBitrate(m Mode, kbps int) {
	switch m {
	case ModeAAC:
		s.AACBitrate = kbps
	case ModeSSC:
		s.SSCBitrate = kbps
	case ModeSSCUHQ:
		s.SSCUHQBitrate = kbps
	}
}

// migrate converts settings written by older versions.
func (s *Settings) migrate() {
	if s.AACMode == "over" {
		s.AACMode, s.MaxMTU = "", true
	}
	if isUHQ(s.SSCBitrate) {
		// UHQ used to be "SSC with a UHQ bitrate"
		s.SSCUHQBitrate, s.SSCBitrate = s.SSCBitrate, 0
		if s.Mode == ModeSSC {
			s.Mode = ModeSSCUHQ
		}
	}
	switch s.Mode {
	case ModeOff, ModeAAC, ModeSSC, ModeSSCUHQ:
	default:
		s.Mode = ModeOff
	}
}

func (s *Settings) MuteSpeakersOrDefault() bool {
	return s.MuteSpeakers == nil || *s.MuteSpeakers
}

// UserDir is %APPDATA%\SSCv2 (created on demand).
func UserDir() string {
	base := os.Getenv("APPDATA")
	if base == "" {
		base = "."
	}
	d := filepath.Join(base, AppName)
	_ = os.MkdirAll(d, 0o700)
	return d
}

// LogDir is %LOCALAPPDATA%\SSCv2\logs for the tray and the engine.
func LogDir() string {
	base := os.Getenv("LOCALAPPDATA")
	if base == "" {
		base = UserDir()
	}
	d := filepath.Join(base, AppName, "logs")
	_ = os.MkdirAll(d, 0o700)
	return d
}

// ServiceDir is %ProgramData%\SSCv2 for the helper service's own files.
func ServiceDir() string {
	base := os.Getenv("ProgramData")
	if base == "" {
		base = `C:\ProgramData`
	}
	d := filepath.Join(base, AppName)
	_ = os.MkdirAll(d, 0o755)
	return d
}

func SettingsPath() string { return filepath.Join(UserDir(), "settings.json") }
func KeysPath() string     { return filepath.Join(UserDir(), "keys.json") }

var mu sync.Mutex

// summary is one log line describing the settings (no secrets in them).
func (s *Settings) summary() string {
	dev := func(d *Device) string {
		if d == nil {
			return "-"
		}
		return d.Addr
	}
	return fmt.Sprintf("mode=%s lang=%q headphones=%s mouse=%s debug=%v maxmtu=%v aac=%d/%q ssc=%d uhq=%d cap=0x%02X",
		s.Mode, s.Lang, dev(s.Headphones), dev(s.Mouse), s.Debug, s.MaxMTU, s.AACBitrate, s.AACMode, s.SSCBitrate, s.SSCUHQBitrate, s.SSCCap)
}

// caller names the function that called Load/Save (who reset the choice?).
func caller() string {
	if pc, file, line, ok := runtime.Caller(2); ok {
		name := filepath.Base(file)
		if f := runtime.FuncForPC(pc); f != nil {
			name = f.Name()
		}
		return fmt.Sprintf("%s:%d", name, line)
	}
	return "?"
}

// Load reads the settings; a missing file yields defaults.
func Load() (*Settings, error) {
	mu.Lock()
	defer mu.Unlock()
	path := SettingsPath()
	s := &Settings{Mode: ModeOff}
	b, err := os.ReadFile(path)
	if errors.Is(err, os.ErrNotExist) {
		logx.Printf("settings: %s not found - defaults (pid %d)", path, os.Getpid())
		return s, nil
	}
	if err != nil {
		return s, err
	}
	if err := json.Unmarshal(b, s); err != nil {
		return &Settings{Mode: ModeOff}, err
	}
	s.migrate()
	logx.Printf("settings: loaded %s (%d bytes): %s", path, len(b), s.summary())
	return s, nil
}

// Save writes the settings atomically. Every save is logged with its caller.
func Save(s *Settings) error {
	mu.Lock()
	defer mu.Unlock()
	err := WriteJSONAtomic(SettingsPath(), s)
	logx.Printf("settings: saved %s by %s: %v", s.summary(), caller(), err)
	return err
}

// WriteJSONAtomic marshals v and replaces path via a temp file.
func WriteJSONAtomic(path string, v any) error {
	b, err := json.MarshalIndent(v, "", "  ")
	if err != nil {
		return err
	}
	tmp := path + ".tmp"
	if err := os.WriteFile(tmp, b, 0o600); err != nil {
		return err
	}
	return os.Rename(tmp, path)
}
