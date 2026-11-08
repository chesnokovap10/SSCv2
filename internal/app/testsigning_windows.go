package app

import (
	"fmt"
	"os/exec"
	"path/filepath"
	"syscall"

	"golang.org/x/sys/windows"

	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
	"sscv2/internal/tray"
)

func (a *App) toggleTestSigning() {
	a.opMu.Lock()
	defer a.opMu.Unlock()

	a.mu.Lock()
	if a.quitting {
		a.mu.Unlock()
		return
	}
	enable := !a.s.WindowsTestSigning
	a.mu.Unlock()

	title := T("Тестовый режим Windows", "Windows test mode")
	prompt := T(
		"Выключить тестовую подпись Windows? Изменение действует на весь компьютер и применяется после перезагрузки.",
		"Turn off Windows test signing? This affects the whole computer and applies after restart.")
	if enable {
		prompt = T(
			"Включить тестовую подпись Windows? Она позволяет загружать драйверы с тестовой подписью. Режим действует на весь компьютер и сохраняется при последующих загрузках, пока его не отключат.",
			"Turn on Windows test signing? This allows test-signed drivers to load. The setting applies to the whole computer and persists across restarts until turned off.")
	}
	if !tray.Ask(title, prompt) {
		return
	}
	a.setBusy(title)
	defer a.setBusy("")
	if _, err := helper.Call(ipc.Request{Op: "test-signing", TestSigning: &enable}); err != nil {
		tray.Info(title, fmt.Sprintf(T("Не удалось изменить режим загрузки Windows.\n\n%v", "Could not change the Windows boot setting.\n\n%v"), err))
		return
	}

	a.mu.Lock()
	a.s.WindowsTestSigning = enable
	err := config.Save(a.s)
	a.mu.Unlock()
	if err != nil {
		tray.Info(title, fmt.Sprintf(T("Режим загрузки Windows изменён, но не удалось сохранить настройку SSCv2.\n\n%v", "The Windows boot setting changed, but the SSCv2 preference could not be saved.\n\n%v"), err))
	}

	if !enable {
		a.mu.Lock()
		wasNative := a.native != nil
		a.mu.Unlock()
		if err := a.stopNativeAAC(); err != nil {
			a.nativeError(err)
			return
		}
		if wasNative {
			a.setMode(config.ModeOff)
		}
	}

	active, err := driver.TestSigning()
	if err == nil && active == enable {
		return
	}
	if !tray.Ask(title, T("Изменение сохранено. Перезагрузить компьютер сейчас?", "The change was saved. Restart the computer now?")) {
		return
	}
	systemDir, err := windows.GetSystemDirectory()
	if err == nil {
		cmd := exec.Command(filepath.Join(systemDir, "shutdown.exe"), "/r", "/t", "0")
		cmd.SysProcAttr = &syscall.SysProcAttr{HideWindow: true, CreationFlags: 0x08000000}
		err = cmd.Run()
	}
	if err != nil {
		tray.Info(title, fmt.Sprintf(T("Не удалось запустить перезагрузку.\n\n%v", "Could not restart Windows.\n\n%v"), err))
	}
}
