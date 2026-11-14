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
	if update {
		current := installedVersion()
		if current == "" {
			current = T("неизвестна", "unknown")
		}
		if !tray.Ask(T("Обновление SSCv2", "SSCv2 update"), fmt.Sprintf(
			T("Текущая версия: %s\nНовая версия: %s\n\nУстановить обновление?",
				"Installed version: %s\nNew version: %s\n\nInstall the update?"), current, ipc.Version)) {
			return true
		}
	}
	logf("setup: %s %s -> %s (version %s)", map[bool]string{true: "updating", false: "installing"}[update], selfPath(), install.Exe(), ipc.Version)
	// A running tray (old version) hands the adapter back and quits first;
	// it keeps the chosen codec so the new version resumes it.
	if out, err := Ctl([]string{"quit", "keep"}); err == nil {
		if out != "ok" {
			stopLegacyTray() // a version without "quit"
		}
		stopped := false
		for deadline := time.Now().Add(30 * time.Second); time.Now().Before(deadline); {
			if _, err := Ctl([]string{"status"}); err != nil {
				stopped = true
				break
			}
			time.Sleep(250 * time.Millisecond)
		}
		if !stopped {
			tray.Warn("SSCv2", T("Обновление отложено. Запущенный SSCv2 ещё не завершился.",
				"Update postponed. The running SSCv2 instance has not exited."))
			return true
		}
	}
	code, err := helper.RunElevated("install --owner " + helper.CurrentUserSID())
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

// Query the installed executable so the version is available with the tray closed.
func installedVersion() string {
	cmd := exec.Command(install.Exe(), "status")
	cmd.SysProcAttr = &syscall.SysProcAttr{HideWindow: true, CreationFlags: 0x08000000}
	out, err := cmd.Output()
	if err != nil {
		return ""
	}
	for _, line := range strings.Split(string(out), "\n") {
		if version, ok := strings.CutPrefix(line, "version "); ok {
			return strings.TrimSpace(version)
		}
	}
	return ""
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
// the service, Program Files\SSCv2, ProgramData,
// the user's settings, keys and logs and the desktop shortcut. The file the
// program was first started from (the "installer") is left alone.
func (a *App) uninstall(confirmed bool) {
	if !confirmed && !tray.Ask(T("Удаление SSCv2", "Uninstall SSCv2"), T(
		"Удалить SSCv2?\n\nBluetooth вернётся Windows, будут удалены служба, папка в Program Files, настройки, ключи сопряжения и журналы, ярлык на рабочем столе.\nФайл, из которого программа была установлена, останется.",
		"Uninstall SSCv2?\n\nBluetooth goes back to Windows; the service, the Program Files folder, settings, pairing keys, logs and the desktop shortcut are removed.\nThe file the program was installed from stays.")) {
		return
	}
	logf("uninstall: start")
	if !a.beginShutdown(false) {
		return
	}
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
	if err := install.UninstallSystem(pid); err != nil {
		logf("uninstall: %v", err)
		return 1
	}
	return 0
}

func (a *App) installService() {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.installServiceLocked()
}

func (a *App) installServiceLocked() {
	a.setBusy(T("установка службы", "installing the service"))
	defer a.setBusy("")
	code, err := helper.RunElevated("service-install --owner " + helper.CurrentUserSID())
	if err == nil && code != 0 {
		err = fmt.Errorf(T("код %d, см. журнал helper.log", "code %d, see helper.log"), code)
	}
	if err != nil {
		a.t.Balloon(T("Служба не установлена", "Service not installed"), err.Error(), 2)
		return
	}
	a.t.Balloon("SSCv2", T("Служба установлена и запущена: переключения больше не требуют подтверждения UAC.",
		"The service is installed and running: switching no longer asks for UAC."), 0)
}

func (a *App) removeService() {
	// Give Bluetooth back to Windows while the helper can still do it.
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	needsRestore := a.needsPlaybackRestore()
	quitting := a.quitting
	a.mu.Unlock()
	if quitting {
		return
	}
	a.t.CloseMenu()
	if needsRestore && !a.stopPlaybackLocked() {
		a.setBusy("")
		return
	}
	a.setBusy(T("удаление службы", "removing the service"))
	defer a.setBusy("")
	code, err := helper.RunElevated("service-uninstall")
	if err == nil && code != 0 {
		err = fmt.Errorf(T("код %d", "code %d"), code)
	}
	if err != nil {
		a.t.Balloon(T("Служба не удалена", "Service not removed"), err.Error(), 2)
		return
	}
	a.t.Balloon("SSCv2", T("Служба удалена.", "Service removed."), 0)
}

// exit quits the tray. keepMode (update): the adapter goes back to Windows
// as usual, but the saved codec stays so the new version resumes it.
func (a *App) exit(keepMode bool) {
	if !a.beginShutdown(keepMode) {
		return
	}
	// Wait for the Windows endpoint to receive the carried volume and mute.
	a.mu.Lock()
	settled := a.volSettled
	a.mu.Unlock()
	if settled != nil {
		a.setBusy(T("перенос громкости в Windows", "carrying the volume to Windows"))
		select {
		case <-settled:
		case <-time.After(8 * time.Second):
			logf("exit: volume carry-over not finished in 8 s")
		}
	}
	logf("tray exit (keep mode %v)", keepMode)
	a.t.Quit()
}
