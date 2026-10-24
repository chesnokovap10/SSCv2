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
	ModeSSC Mode = "ssc" // Samsung Scalable Codec (placeholder)
)

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
	// AACMode: "" / "fit" (default: bitrate from the headphones' MTU, every
	// frame fits one packet), "over" (256 kbps above their announced MTU,
	// menu "AAC 256") or "frag" (diagnostics: frames split over two packets).
	AACMode string `json:"aacMode,omitempty"`
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
	return fmt.Sprintf("mode=%s headphones=%s mouse=%s debug=%v aac=%q", s.Mode, dev(s.Headphones), dev(s.Mouse), s.Debug, s.AACMode)
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
	if s.Mode == "" {
		s.Mode = ModeOff
	}
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
