package app

import (
	"fmt"
	"strings"

	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
	"sscv2/internal/logx"
	"sscv2/internal/tray"
)

func (a *App) setBusy(s string) {
	a.mu.Lock()
	changed := a.busy != s
	a.busy = s
	a.mu.Unlock()
	if changed {
		logx.Dbgf("mode", "busy: %q", s)
	}
	a.refresh()
}

// modeName is the codec as the menu shows it.
func modeName(m config.Mode) string {
	switch m {
	case config.ModeAAC:
		return "AAC"
	case config.ModeSSC:
		return "SSC"
	case config.ModeSSCUHQ:
		return "SSC UHQ"
	}
	return T("Выкл", "Off")
}

// state: color and text for the icon and the menu header.
func (a *App) state() (tray.Color, string) {
	a.mu.Lock()
	defer a.mu.Unlock()
	return a.stateLocked()
}

func (a *App) stateLocked() (tray.Color, string) {
	if a.busy != "" {
		return tray.Amber, a.busy
	}
	if a.adapter.Mode == driver.NotPresent {
		return tray.Red, T("адаптер не найден", "adapter not found")
	}
	if a.native != nil {
		if a.native.ready {
			return tray.Green, modeName(a.native.Mode) + " (Windows Bluetooth)"
		}
		return tray.Amber, modeName(a.native.Mode) + " (Windows Bluetooth)..."
	}
	if a.nativeWaiting != nil {
		return tray.Blue, T("ожидание наушников", "waiting for headphones")
	}
	if a.mode == config.ModeOff {
		if a.adapter.Mode == driver.WinUSB {
			return tray.Blue, T("выкл (адаптер в WinUSB)", "off (adapter in WinUSB)")
		}
		return tray.Gray, T("выкл - Bluetooth Windows", "off - Windows Bluetooth")
	}
	if a.eng == nil {
		if a.st.StreamStartFailed {
			return tray.Red, fmt.Sprintf(T("%s не запустился", "%s failed to start"), modeName(a.mode))
		}
		if a.noBitrate(a.mode) {
			return tray.Red, a.unsupportedText(a.mode)
		}
		return tray.Red, T("движок не запущен", "engine not running")
	}
	st := a.st
	if a.resumeEngine != nil && a.resumeEngine == a.eng {
		return tray.Amber, T("восстановление после сна", "recovering after sleep")
	}
	name := st.HeadphonesName
	if name == "" {
		name = st.Headphones
	}
	switch st.Phase {
	case "streaming":
		if !st.Connected || !st.Streaming {
			return tray.Blue, T("ожидание наушников", "waiting for headphones")
		}
		return tray.Green, fmt.Sprintf("%s → %s", st.Codec, name)
	case "error":
		return tray.Red, T("ошибка: ", "error: ") + st.Message
	case "waiting", "idle":
		return tray.Blue, st.Message
	case "":
		return tray.Amber, T("запуск", "starting")
	}
	if st.Message != "" {
		return tray.Amber, st.Message
	}
	return tray.Amber, st.Phase
}

func (a *App) refresh() {
	a.mu.Lock()
	c, s := a.stateLocked()
	icon := tray.IconOff
	switch a.mode {
	case config.ModeAAC:
		icon = tray.IconAAC
	case config.ModeSSC:
		icon = tray.IconSSC
	case config.ModeSSCUHQ:
		icon = tray.IconSSCPlus
	}
	a.t.Set(c, icon, "SSCv2: "+s)
	a.mu.Unlock()
	a.t.RefreshMenu()
}

func (a *App) showInfo() {
	tray.Info(T("SSCv2 — устройства", "SSCv2 - devices"), a.infoText())
}

func (a *App) infoText() string {
	st := a.refreshAdapter()
	installed, running := helper.ServiceState()
	store, _ := keys.Open()
	snap := store.Snapshot()
	a.mu.Lock()
	es, mode, s := a.st, a.mode, *a.s
	engineUp := a.eng != nil
	a.mu.Unlock()

	var b strings.Builder
	w := func(f string, args ...any) { fmt.Fprintf(&b, f+"\n", args...) }

	w("SSCv2 %s", ipc.Version)
	if mode == config.ModeOff {
		w(T("Кодек: выкл (Bluetooth Windows)", "Codec: off (Windows Bluetooth)"))
	} else {
		a.mu.Lock()
		policy, _ := a.bitratePolicy(mode, a.prefersNativeBitrates())
		br := policy.Selected(mode, a.s.Bitrate(mode))
		a.mu.Unlock()
		w(T("Кодек: %s, битрейт %s", "Codec: %s, bitrate %s"), modeName(mode), bitrateText(br))
	}
	w("")
	if st.Mode == driver.NotPresent {
		w(T("Адаптер: MediaTek MT79xx не найден", "Adapter: MediaTek MT79xx not found"))
	} else {
		w(T("Адаптер: %s (%s)", "Adapter: %s (%s)"), nz(st.Name, "MediaTek"), st.ID)
		w(T("    драйвер: %s [%s]", "    driver: %s [%s]"), st.Mode, st.Service)
		if engineUp && es.Chip != "" {
			w(T("    чип: %s, прошивка %s", "    chip: %s, firmware %s"), es.Chip, es.Firmware)
		}
		addr := es.AdapterAddr
		if addr == "" {
			addr, _ = windowsRadio()
		}
		if addr == "" {
			addr = snap.Adapter
		}
		if addr != "" {
			w(T("    адрес: %s", "    address: %s"), addr)
		}
	}
	w("")
	if s.Headphones == nil {
		w(T("Наушники: не выбраны", "Headphones: none chosen"))
	} else {
		w(T("Наушники: %s (%s)", "Headphones: %s (%s)"), nz(s.Headphones.Name, "—"), s.Headphones.Addr)
		if engineUp {
			switch {
			case es.Streaming:
				w(T("    поток: %s, %d кбит/с, %d Гц", "    stream: %s, %d kbps, %d Hz"), es.Codec, es.BitrateKbps, es.SampleRate)
			case es.Connected:
				w(T("    подключены, поток не идёт", "    connected, not streaming"))
			default:
				w("    %s", nz(es.Message, es.Phase))
			}
			if es.AVRCP && es.Volume >= 0 {
				w(T("    громкость: %d%%", "    volume: %d%%"), es.Volume*100/127)
			}
			if es.CaptureDevice != "" {
				w(T("    источник: %s [%s]", "    source: %s [%s]"), es.CaptureDevice, es.CaptureFormat)
			}
			if es.Fails > 0 || es.Queue > 8 {
				w(T("    очередь %d, потерь за 2 с: %d", "    queue %d, lost in 2 s: %d"), es.Queue, es.Fails)
			}
		} else if mode == config.ModeOff {
			w(T("    работают через Bluetooth Windows", "    work through Windows Bluetooth"))
		}
	}
	w("")
	if s.Mouse == nil {
		w(T("Мышь: не выбрана", "Mouse: none chosen"))
	} else {
		w(T("Мышь: %s (%s)", "Mouse: %s (%s)"), nz(s.Mouse.Name, "—"), s.Mouse.Addr)
		if engineUp && es.MouseState != "" {
			w(T("    мост: %s, отчётов: %d", "    bridge: %s, reports: %d"), es.MouseState, es.MouseReports)
		} else if mode == config.ModeOff {
			w(T("    работает через Bluetooth Windows", "    works through Windows Bluetooth"))
		}
	}
	w("")
	svc := T("не установлена", "not installed")
	if installed {
		svc = T("остановлена", "stopped")
		if running {
			svc = T("работает", "running")
		}
	}
	w(T("Служба: %s", "Service: %s"), svc)
	w(T("Ключи: устройств %d, мышей %d", "Keys: %d device(s), %d mouse/mice"), len(snap.Classic), len(snap.LE))
	w(T("Журналы: %s", "Logs: %s"), config.LogDir())
	return b.String()
}
