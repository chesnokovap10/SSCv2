// Package logx is a tiny file logger shared by the tray, engine and service.
//
// Debug mode (menu "Отладка", "ssc.exe ctl debug on", or SSCV2_DEBUG=1):
// Dbgf lines are written too, and every line of every process (tray, engine,
// helper) is also appended to logs\debug.log - one time-ordered journal of
// mode switches, device exchanges and volume changes.
package logx

import (
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
	"sync"
	"sync/atomic"
	"time"
)

var (
	mu       sync.Mutex
	out      io.Writer = os.Stderr
	tag      string
	dir      string
	dbgFile  *os.File
	capture  *[]string
	debugOn  atomic.Bool
	startPID = os.Getpid()
)

const (
	rotateSize      = 4 << 20
	debugRotateSize = 64 << 20
	DebugLogName    = "debug.log"
)

// Open directs the log to dir\name (rotated once at 4 MB). tag prefixes
// every line ("tray", "engine").
func Open(d, name, t string) {
	mu.Lock()
	defer mu.Unlock()
	tag, dir = t, d
	path := filepath.Join(d, name)
	if fi, err := os.Stat(path); err == nil && fi.Size() > rotateSize {
		_ = os.Rename(path, path+".old")
	}
	f, err := os.OpenFile(path, os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0o600)
	if err != nil {
		return
	}
	out = f
	if os.Getenv("SSCV2_DEBUG") == "1" {
		setDebugLocked(true)
	}
}

// SetDebug turns the debug journal on or off for this process.
func SetDebug(on bool) {
	mu.Lock()
	defer mu.Unlock()
	setDebugLocked(on)
}

func setDebugLocked(on bool) {
	if on == debugOn.Load() {
		return
	}
	if on && dir != "" {
		path := filepath.Join(dir, DebugLogName)
		if fi, err := os.Stat(path); err == nil && fi.Size() > debugRotateSize {
			_ = os.Rename(path, path+".old") // another process may hold it: then keep appending
		}
		// O_APPEND: every line is one write at the end of the file, so the
		// tray and the engine can share it.
		if f, err := os.OpenFile(path, os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0o600); err == nil {
			dbgFile = f
		}
	}
	debugOn.Store(on)
	line := fmt.Sprintf("%s [%s] debug journal %s (pid %d)\n", now(), tag, map[bool]string{true: "on", false: "off"}[on], startPID)
	if dbgFile != nil {
		_, _ = io.WriteString(dbgFile, line)
	}
	_, _ = io.WriteString(out, line)
	if !on && dbgFile != nil {
		dbgFile.Close()
		dbgFile = nil
	}
}

// Debug reports whether debug mode is on.
func Debug() bool { return debugOn.Load() }

func now() string { return time.Now().Format("2006-01-02 15:04:05.000") }

func write(kind, msg string) {
	mu.Lock()
	defer mu.Unlock()
	line := now() + " [" + tag + "]" + kind + " " + msg + "\n"
	_, _ = io.WriteString(out, line)
	if dbgFile != nil {
		_, _ = io.WriteString(dbgFile, line)
	}
	if capture != nil {
		*capture = append(*capture, strings.TrimRight(line, "\n"))
	}
}

// Printf writes one timestamped line.
func Printf(format string, args ...any) { write("", fmt.Sprintf(format, args...)) }

// Dbgf writes a line only in debug mode. cat groups lines ("mode", "vol",
// "dev", "hci", "avrcp", ...) so the journal can be filtered with findstr.
func Dbgf(cat, format string, args ...any) {
	if !debugOn.Load() {
		return
	}
	write(" "+cat+":", fmt.Sprintf(format, args...))
}

// Capture collects the lines written until the returned function is
// called (the helper service hands them back to the tray in debug mode).
func Capture() func() []string {
	mu.Lock()
	var lines []string
	capture = &lines
	mu.Unlock()
	return func() []string {
		mu.Lock()
		defer mu.Unlock()
		capture = nil
		return lines
	}
}

// Writer returns the current destination (for redirecting other loggers).
func Writer() io.Writer {
	mu.Lock()
	defer mu.Unlock()
	return out
}
