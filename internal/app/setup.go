package app

import (
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"os/exec"
	"strings"
	"syscall"
	"time"

	"sscv2/internal/config"
	"sscv2/internal/helper"
	"sscv2/internal/install"
	"sscv2/internal/ipc"
	"sscv2/internal/logx"
	"sscv2/internal/tray"
)

// installOrUpdate runs before the tray starts. A copy started from anywhere
// but Program Files installs itself there (first run) or updates the
// installed one, makes the desktop shortcut and starts the installed copy;
// true = done, this process should exit. SSCV2_PORTABLE=1 skips it.
func installOrUpdate() bool {
	if os.Getenv("SSCV2_PORTABLE") == "1" || install.RunningInstalled() {
		return false
	}
	if install.UpToDate() {
		logf("setup: the installed copy is the same - starting it")
		if err := install.Launch(); err != nil {
			logf("setup: start %s: %v", install.Exe(), err)
			return false
		}
		return true
	}
	update := install.Installed()
	logf("setup: %s %s -> %s (version %s)", map[bool]string{true: "updating", false: "installing"}[update], selfPath(), install.Exe(), ipc.Version)
	// A running tray (old version) hands the adapter back and quits first;
	// it keeps the chosen codec so the new version resumes it.
	if out, err := Ctl([]string{"quit", "keep"}); err == nil {
		if out != "ok" {
			stopLegacyTray() // a version without "quit"
		}
		for i := 0; i < 120; i++ {
			if _, err := Ctl([]string{"status"}); err != nil {
				break
			}
			time.Sleep(250 * time.Millisecond)
		}
		time.Sleep(300 * time.Millisecond)
	}
	code, err := helper.RunElevated("install")
	if err == nil && code != 0 {
		err = fmt.Errorf(T("код %d, см. журнал helper.log", "code %d, see helper.log"), code)
	}
	if err != nil {
		logf("setup: %v", err)
		if errors.Is(err, helper.ErrCancelled) {
			tray.Warn("SSCv2", T("Установка в Program Files отменена. Программа запущена без установки.",
				"Installing to Program Files was cancelled. The program runs without being installed."))
		} else {
			tray.Warn("SSCv2", T("Не удалось установить программу: ", "Could not install the program: ")+err.Error())
		}
		return false
	}
	if err := install.CreateShortcut(); err != nil {
		logf("setup: shortcut: %v", err)
	}
	if err := install.Launch(); err != nil {
		tray.Warn("SSCv2", T("Программа установлена, но не запустилась: ", "Installed, but could not start: ")+err.Error())
		return true
	}
	return true
}

// stopLegacyTray closes a running tray of a version that has no "quit"
// command: codec off through its control pipe (Bluetooth back to Windows),
// then the process is ended; the saved codec is put back afterwards.
func stopLegacyTray() {
	saved, _ := config.Load()
	logf("setup: stopping an older tray (saved mode %s)", saved.Mode)
	if _, err := Ctl([]string{"mode", "off"}); err == nil {
		for i := 0; i < 240; i++ {
			out, err := Ctl([]string{"status"})
			if err != nil {
				break
			}
			var st struct {
				Mode config.Mode `json:"mode"`
				Busy string      `json:"busy"`
			}
			if json.Unmarshal([]byte(out), &st) == nil && st.Mode == config.ModeOff && st.Busy == "" {
				break
			}
			time.Sleep(250 * time.Millisecond)
		}
	}
	kill := exec.Command("taskkill.exe", "/F", "/IM", "ssc.exe", "/FI", fmt.Sprintf("PID ne %d", os.Getpid()))
	kill.SysProcAttr = &syscall.SysProcAttr{HideWindow: true, CreationFlags: 0x08000000}
	out, err := kill.CombinedOutput()
	logf("setup: taskkill: %v %s", err, strings.TrimSpace(string(out)))
	if s, err := config.Load(); err == nil && saved.Mode != config.ModeOff {
		s.Mode = saved.Mode
		_ = config.Save(s)
	}
}

// uninstall removes the program: gives Bluetooth back to Windows, removes
// the virtual headphones, the service, Program Files\SSCv2, ProgramData,
// the user's settings, keys and logs and the desktop shortcut. The file the
// program was first started from (the "installer") is left alone.
func (a *App) uninstall(confirmed bool) {
	if !confirmed && !tray.Ask(T("Удаление SSCv2", "Uninstall SSCv2"), T(
		"Удалить SSCv2?\n\nBluetooth вернётся Windows, будут удалены служба, виртуальные наушники, папка в Program Files, настройки, ключи сопряжения и журналы, ярлык на рабочем столе.\nФайл, из которого программа была установлена, останется.",
		"Uninstall SSCv2?\n\nBluetooth goes back to Windows; the service, the virtual headphones, the Program Files folder, settings, pairing keys, logs and the desktop shortcut are removed.\nThe file the program was installed from stays.")) {
		return
	}
	logf("uninstall: start")
	a.mu.Lock()
	a.quitting = true
	mode := a.mode
	a.mu.Unlock()
	if mode != config.ModeOff {
		a.disable()
	}
	a.setBusy(T("удаление виртуальных наушников", "removing the virtual headphones"))
	a.removeVirtual()
	a.setBusy(T("удаление программы", "uninstalling"))
	code, err := helper.RunElevated(fmt.Sprintf("uninstall-system --pid %d", os.Getpid()))
	if err == nil && code != 0 {
		err = fmt.Errorf(T("код %d, см. журнал helper.log", "code %d, see helper.log"), code)
	}
	if err != nil {
		logf("uninstall: %v", err)
		a.mu.Lock()
		a.quitting = false
		a.mu.Unlock()
		a.setBusy("")
		a.t.Balloon(T("Программа не удалена", "Not uninstalled"), err.Error(), 2)
		return
	}
	logf("uninstall: done, removing user data after exit")
	install.RemoveUserData(os.Getpid())
	logx.Close()
	a.t.Quit()
}

// UninstallSystem is the elevated "uninstall-system --pid N" step: the
// service, then the machine-wide files (see install.UninstallSystem).
func UninstallSystem(pid int) int {
	logx.Open(config.LogDir(), "helper.log", "helper")
	if err := helper.UninstallService(); err != nil {
		logf("uninstall: service: %v", err)
	}
	helper.Handle(ipc.Request{Op: "virtual-uninstall"})
	if err := install.UninstallSystem(pid); err != nil {
		logf("uninstall: %v", err)
		return 1
	}
	return 0
}
