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
		"Выключить тестовую подпись Windows и удалить драйвер SSCv2? Изменение действует на весь компьютер и применяется после перезагрузки.",
		"Turn off Windows test signing and remove the SSCv2 driver? This affects the whole computer and applies after restart.")
	if enable {
		prompt = T(
			"Включить тестовую подпись Windows? После перезагрузки SSCv2 установит свой драйвер и добавит доверие к его тестовому сертификату. Режим действует на весь компьютер и сохраняется при последующих загрузках, пока его не отключат.",
			"Turn on Windows test signing? After restart, SSCv2 installs its driver and trusts its test certificate. The setting applies to the whole computer and persists across restarts until turned off.")
	}
	if !tray.Ask(title, prompt) {
		return
	}
	a.setBusy(title)
	defer a.setBusy("")
	if enable {
		if _, running := helper.ServiceState(); !running {
			a.installService()
			if _, running := helper.ServiceState(); !running {
				return
			}
			a.setBusy(title)
		}
	}

	if !enable {
		a.mu.Lock()
		wasNative := a.native != nil
		a.mu.Unlock()
		if err := a.stopNativeAudio(); err != nil {
			a.nativeError(err)
			return
		}
		if wasNative {
			a.setMode(config.ModeOff)
		}
	}
	if _, err := helper.Call(ipc.Request{Op: "test-signing", TestSigning: &enable}); err != nil {
		tray.Info(title, fmt.Sprintf(T("Не удалось применить настройки тестового режима.\n\n%v", "Could not apply the Windows test-mode settings.\n\n%v"), err))
		return
	}

	a.mu.Lock()
	a.s.WindowsTestSigning = enable
	err := config.Save(a.s)
	a.mu.Unlock()
	if err != nil {
		tray.Info(title, fmt.Sprintf(T("Режим загрузки Windows изменён, но не удалось сохранить настройку SSCv2.\n\n%v", "The Windows boot setting changed, but the SSCv2 preference could not be saved.\n\n%v"), err))
	}

	active, err := driver.TestSigning()
	// Keep the current codec and USB driver until Windows has booted with test signing.
	if enable && err == nil && active {
		if _, syncErr := helper.Call(ipc.Request{Op: "native-profile-sync"}); syncErr != nil {
			tray.Info(title, syncErr.Error())
			return
		}
		a.mu.Lock()
		mode, legacyRunning := a.mode, a.eng != nil
		a.mu.Unlock()
		if legacyRunning && (mode == config.ModeAAC || mode == config.ModeSSC) {
			go a.enable(mode)
		} else if legacyRunning || a.refreshAdapter().Mode == driver.WinUSB {
			a.disableLocked()
			if a.refreshAdapter().Mode == driver.WinUSB {
				return
			}
			a.setBusy(title)
		}
	}
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
