// Package install puts ssc.exe into Program Files (first run, updates),
// makes the desktop shortcut and removes all of it again (Settings >
// Uninstall; no "Apps & features" entry). The parts that write Program
// Files and ProgramData run elevated ("ssc.exe install" /
// "ssc.exe uninstall-system").
package install

import (
	"bytes"
	"crypto/sha256"
	"errors"
	"fmt"
	"io"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"syscall"
	"time"

	"golang.org/x/sys/windows"
	"golang.org/x/sys/windows/svc"
	"golang.org/x/sys/windows/svc/mgr"

	"sscv2/internal/config"
	"sscv2/internal/i18n"
	"sscv2/internal/ipc"
	"sscv2/internal/logx"
)

const (
	exeName     = "ssc.exe"
	serviceName = "SSCv2Helper" // = helper.ServiceName (helper imports nothing from here)
)

// Dir is %ProgramFiles%\SSCv2.
func Dir() string {
	pf := os.Getenv("ProgramFiles")
	if pf == "" {
		pf = `C:\Program Files`
	}
	return filepath.Join(pf, config.AppName)
}

// Exe is the installed executable.
func Exe() string { return filepath.Join(Dir(), exeName) }

// Self is this process' executable.
func Self() string {
	p, err := os.Executable()
	if err != nil {
		return ""
	}
	if r, err := filepath.EvalSymlinks(p); err == nil {
		p = r
	}
	return p
}

// RunningInstalled reports that this process runs the installed copy.
func RunningInstalled() bool {
	return strings.EqualFold(filepath.Clean(Self()), filepath.Clean(Exe())) || sameFile(Self(), Exe())
}

// Installed reports that the installed copy exists.
func Installed() bool {
	_, err := os.Stat(Exe())
	return err == nil
}

// UpToDate reports that the installed copy is byte-identical to this one.
func UpToDate() bool {
	a, err1 := fileHash(Self())
	b, err2 := fileHash(Exe())
	return err1 == nil && err2 == nil && bytes.Equal(a, b)
}

func fileHash(p string) ([]byte, error) {
	f, err := os.Open(p)
	if err != nil {
		return nil, err
	}
	defer f.Close()
	h := sha256.New()
	if _, err := io.Copy(h, f); err != nil {
		return nil, err
	}
	return h.Sum(nil), nil
}

func sameFile(a, b string) bool {
	fa, err1 := os.Stat(a)
	fb, err2 := os.Stat(b)
	return err1 == nil && err2 == nil && os.SameFile(fa, fb)
}

// ---- elevated: install / update --------------------------------------------

// Install copies this executable to Program Files. A running helper service is stopped for the copy and
// started again (it runs the same file). Needs admin rights.
func Install() error {
	self := Self()
	if self == "" {
		return errors.New("os.Executable")
	}
	restart := stopService()
	if err := os.MkdirAll(Dir(), 0o755); err != nil {
		return err
	}
	if !sameFile(self, Exe()) {
		if err := copyFile(self, Exe()); err != nil {
			if restart {
				startService()
			}
			return fmt.Errorf(i18n.T("копирование в %s: %w", "copying to %s: %w"), Dir(), err)
		}
	}
	if restart {
		startService()
	}
	logx.Printf("install: %s -> %s (version %s)", self, Exe(), ipc.Version)
	return nil
}

func copyFile(src, dst string) error {
	in, err := os.Open(src)
	if err != nil {
		return err
	}
	defer in.Close()
	tmp := dst + ".new"
	out, err := os.Create(tmp)
	if err != nil {
		return err
	}
	if _, err := io.Copy(out, in); err != nil {
		out.Close()
		os.Remove(tmp)
		return err
	}
	if err := out.Close(); err != nil {
		os.Remove(tmp)
		return err
	}
	// A running image cannot be overwritten but can be renamed.
	var err2 error
	for i := 0; i < 40; i++ {
		_ = os.Remove(dst + ".old")
		_ = os.Rename(dst, dst+".old")
		if err2 = os.Rename(tmp, dst); err2 == nil {
			if os.Remove(dst+".old") != nil {
				deleteOnReboot(dst + ".old")
			}
			return nil
		}
		time.Sleep(250 * time.Millisecond)
	}
	os.Remove(tmp)
	return err2
}

func deleteOnReboot(p string) {
	u, err := windows.UTF16PtrFromString(p)
	if err == nil {
		_ = windows.MoveFileEx(u, nil, windows.MOVEFILE_DELAY_UNTIL_REBOOT)
	}
}

// stopService stops the helper service if it runs; reports whether it did.
func stopService() bool {
	m, err := mgr.Connect()
	if err != nil {
		return false
	}
	defer m.Disconnect()
	s, err := m.OpenService(serviceName)
	if err != nil {
		return false
	}
	defer s.Close()
	q, err := s.Query()
	if err != nil || q.State == svc.Stopped {
		return false
	}
	if _, err := s.Control(svc.Stop); err != nil {
		return false
	}
	for i := 0; i < 50; i++ {
		if q, err := s.Query(); err != nil || q.State == svc.Stopped {
			break
		}
		time.Sleep(200 * time.Millisecond)
	}
	return true
}

func startService() {
	m, err := mgr.Connect()
	if err != nil {
		return
	}
	defer m.Disconnect()
	if s, err := m.OpenService(serviceName); err == nil {
		_ = s.Start()
		s.Close()
	}
}

// ---- elevated: uninstall ---------------------------------------------------

// UninstallSystem removes what needs admin rights: %ProgramData%\SSCv2, leftover driver-switch certificates and -
// once process pid (the tray) has exited - the Program Files folder. The
// service itself is removed by the caller beforehand.
func UninstallSystem(pid int) error {
	logx.Close()
	pd := os.Getenv("ProgramData")
	if pd == "" {
		pd = `C:\ProgramData`
	}
	// Leftover ephemeral signer of the WinUSB switch (normally removed by
	// the switch itself).
	removeLater(0, []string{filepath.Join(pd, config.AppName)},
		`foreach ($st in 'My','Root','TrustedPublisher') { Get-ChildItem "Cert:\LocalMachine\$st" -ErrorAction SilentlyContinue | `+
			`Where-Object { $_.Subject -like '*SSCv2*' } | ForEach-Object { Remove-Item -Path $_.PSPath -DeleteKey -ErrorAction SilentlyContinue } }`)
	removeLater(pid, []string{Dir()}, "")
	return nil
}

// RemoveUserData deletes the user's settings, keys, logs and the desktop
// shortcut once process pid has exited (its log files are still open).
func RemoveUserData(pid int) {
	var dirs []string
	for _, env := range []string{"APPDATA", "LOCALAPPDATA"} {
		if b := os.Getenv(env); b != "" {
			dirs = append(dirs, filepath.Join(b, config.AppName))
		}
	}
	if p := ShortcutPath(); p != "" {
		dirs = append(dirs, p)
	}
	removeLater(pid, dirs, "")
}

func psLit(s string) string { return "'" + strings.ReplaceAll(s, "'", "''") + "'" }

// removeLater starts a hidden, detached PowerShell that waits for process
// pid (0 = none), runs extra and deletes paths (retrying a few seconds,
// files may still be released).
func removeLater(pid int, paths []string, extra string) {
	var b strings.Builder
	if pid > 0 {
		fmt.Fprintf(&b, "Wait-Process -Id %d -Timeout 60 -ErrorAction SilentlyContinue; ", pid)
	}
	if extra != "" {
		b.WriteString(extra + "; ")
	}
	for _, p := range paths {
		fmt.Fprintf(&b, "for ($i=0; $i -lt 20 -and (Test-Path -LiteralPath %s); $i++) { Remove-Item -LiteralPath %s -Recurse -Force -ErrorAction SilentlyContinue; Start-Sleep -Milliseconds 500 }; ",
			psLit(p), psLit(p))
	}
	cmd := exec.Command("powershell.exe", "-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass",
		"-WindowStyle", "Hidden", "-Command", b.String())
	cmd.SysProcAttr = &syscall.SysProcAttr{HideWindow: true,
		CreationFlags: 0x08000000 | 0x00000008 | 0x00000200} // NO_WINDOW | DETACHED | NEW_PROCESS_GROUP
	if err := cmd.Start(); err != nil {
		logx.Printf("uninstall: cleanup process: %v", err)
		return
	}
	_ = cmd.Process.Release()
}

// ---- user: shortcut ---------------------------------------------------------

// ShortcutPath is the desktop shortcut of the current user.
func ShortcutPath() string {
	d, err := windows.KnownFolderPath(windows.FOLDERID_Desktop, 0)
	if err != nil || d == "" {
		return ""
	}
	return filepath.Join(d, config.AppName+".lnk")
}

// CreateShortcut puts "SSCv2" on the user's desktop (pointing at the
// installed copy).
func CreateShortcut() error {
	p := ShortcutPath()
	if p == "" {
		return errors.New("desktop folder not found")
	}
	script := "$s = (New-Object -ComObject WScript.Shell).CreateShortcut(" + psLit(p) + "); " +
		"$s.TargetPath = " + psLit(Exe()) + "; $s.WorkingDirectory = " + psLit(Dir()) + "; " +
		"$s.IconLocation = " + psLit(Exe()+",0") + "; $s.Description = 'SSCv2'; $s.Save()"
	cmd := exec.Command("powershell.exe", "-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-Command", script)
	cmd.SysProcAttr = &syscall.SysProcAttr{HideWindow: true, CreationFlags: 0x08000000}
	out, err := cmd.CombinedOutput()
	if err != nil {
		return fmt.Errorf("%v: %s", err, strings.TrimSpace(string(out)))
	}
	return nil
}

// Launch starts the installed copy (a new tray) and does not wait.
func Launch() error {
	cmd := exec.Command(Exe())
	cmd.Dir = Dir()
	if err := cmd.Start(); err != nil {
		return err
	}
	return cmd.Process.Release()
}
