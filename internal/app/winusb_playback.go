package app

import (
	"fmt"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/engine"
	"sscv2/internal/helper"
	"sscv2/internal/i18n"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
	"sscv2/internal/logx"
	"sscv2/internal/mtk"
)

// startWinUSBPlaybackLocked applies a codec change or starts the WinUSB engine.
func (a *App) startWinUSBPlaybackLocked(m config.Mode, eng *workerProcess, streaming bool) {
	a.mu.Lock()
	blocked := a.noBitrate(m)
	if m == config.ModeSSCUHQ && a.uhqUnavailable() {
		a.mu.Unlock()
		a.t.Balloon("SSCv2", T("Наушники не поддерживают SSC UHQ", "SSC UHQ is unavailable on these headphones"), 1)
		return
	}
	codec := a.codecChange(m)
	a.mu.Unlock()
	a.setMode(m)
	if !blocked && eng != nil && eng.running() && streaming {
		if m == config.ModeSSCUHQ {
			a.mu.Lock()
			a.pendingUHQ = true
			a.mu.Unlock()
		}
		if err := eng.in.Write(ipc.Command{Cmd: ipc.CommandCodec, Codec: &codec}); err == nil {
			return
		}
		a.mu.Lock()
		a.pendingUHQ = false
		a.mu.Unlock()
	}
	if eng != nil {
		a.setBusy(T("остановка потока", "stopping the stream"))
		a.stopWinUSBEngineLocked(!blocked)
		defer a.releaseWinUSBCarryLocked()
	}
	a.mu.Lock()
	blocked = a.noBitrate(m)
	a.mu.Unlock()
	if blocked {
		// codec chosen, but not supported by these headphones: no stream
		// until Settings > All bitrates
		a.mu.Lock()
		msg := a.unsupportedText(m)
		a.mu.Unlock()
		logf("mode %s: %s", m, msg)
		a.t.Balloon("SSCv2", msg, 1)
		return
	}

	st := a.refreshAdapter()
	if st.Mode == driver.NotPresent {
		a.t.Balloon("SSCv2", T("Адаптер MediaTek не найден", "MediaTek adapter not found"), 2)
		a.markStreamStartFailed()
		return
	}
	if st.Mode == driver.BthUSB {
		if level, muted, ok := audio.HeadphonesVolume(a.headphonesName()); ok {
			a.mu.Lock()
			// An unsolicited Buds reset to 100% must not replace a saved level.
			if level < 0.99 {
				value := audio.ScalarTo127(level)
				a.s.HeadphonesVolume = &value
			}
			a.s.HeadphonesMuted = muted
			a.mu.Unlock()
		}
	}
	if st.Mode != driver.WinUSB {
		a.setBusy(T("переключение адаптера в WinUSB", "switching the adapter to WinUSB"))
		a.mu.Lock()
		variant := a.driverVariant
		a.mu.Unlock()
		_, err := helper.Call(ipc.Request{Op: "driver", VID: st.ID.VID, PID: st.ID.PID, WinUSB: true, Variant: variant})
		if err != nil {
			logf("driver winusb: %v", err)
			a.t.Balloon(T("Не удалось включить поток", "Could not start streaming"), err.Error(), 2)
			a.refreshAdapter()
			a.markStreamStartFailed()
			return
		}
		deadline := time.Now().Add(10 * time.Second)
		for {
			err := mtk.CheckWinUSB(st.ID.VID, st.ID.PID)
			if err == nil {
				break
			}
			if time.Now().After(deadline) {
				logf("WinUSB interface not ready: %v", err)
				if _, restoreErr := helper.Call(ipc.Request{Op: "driver", VID: st.ID.VID, PID: st.ID.PID, Variant: variant}); restoreErr != nil {
					logf("restore Bluetooth after WinUSB readiness failure: %v", restoreErr)
				}
				a.t.Balloon(T("Не удалось включить поток", "Could not start streaming"), err.Error(), 2)
				a.refreshAdapter()
				a.markStreamStartFailed()
				return
			}
			time.Sleep(50 * time.Millisecond)
		}
		a.refreshAdapter()
	}
	a.launchWinUSBLocked()
}

// startWinUSBEngineLocked starts the engine for the current mode (opMu held).
func (a *App) startWinUSBEngineLocked() error {
	a.mu.Lock()
	if a.noBitrate(a.mode) {
		a.mu.Unlock()
		a.releaseWinUSBCarryLocked()
		a.refresh()
		return nil
	}
	cfg := ipc.EngineConfig{
		Codec:           a.mode.EngineCodec(),
		VID:             a.adapter.ID.VID,
		PID:             a.adapter.ID.PID,
		Volume:          a.volumeLocked(),
		HeadphonesMuted: a.s.HeadphonesMuted,
		Debug:           a.s.Debug,
		Lang:            i18n.Lang(),
		MaxMTU:          a.s.MaxMTU,
		AACMode:         a.s.AACMode,
		SSCUHQ:          a.mode == config.ModeSSCUHQ,
		TryUHQ:          a.mode == config.ModeSSCUHQ && a.s.AllBitrates,
		SSCCap:          a.s.SSCCap,
		Carry:           a.carry,
	}
	a.carry = nil
	cfg.AACBitrate = a.winUSBBitrate(config.ModeAAC)
	if a.mode == config.ModeSSC {
		cfg.SSCMaxKbps, _ = a.workingMax(config.ModeSSC)
	}
	if a.mode != config.ModeAAC {
		cfg.SSCBitrate = a.winUSBBitrate(a.mode)
	}
	if a.s.Headphones != nil {
		cfg.Headphones = a.s.Headphones.Addr
	}
	if a.s.Mouse != nil {
		cfg.Mouse = a.s.Mouse.Addr
	}
	a.st = ipc.EngineStatus{Volume: -1}
	a.mu.Unlock()
	p, err := startWorkerProcess("engine", "engine-stderr.log", cfg)
	if err != nil {
		if cfg.Carry != nil {
			engine.RestoreAudio(ipc.EngineStatus{MuteEndpoint: cfg.Carry.MuteEndpoint})
		}
		return err
	}
	a.mu.Lock()
	a.eng = p
	a.mu.Unlock()
	logf("engine started (pid %d)", p.process.Pid)
	p.watch(func(event ipc.Event) { a.onEngineEvent(p, event) }, func(err error) { a.onEngineExit(p, err) })
	a.refresh()
	return nil
}

func (a *App) onEngineEvent(p *workerProcess, ev ipc.Event) {
	if ev.Ev != ipc.EventStatus {
		logx.Dbgf("ipc", "engine -> tray: %s %s %s", ev.Ev, ev.Addr, ev.Msg)
	}
	switch ev.Ev {
	case "codec":
		a.mu.Lock()
		current := a.eng == p && a.pendingUHQ && ev.Codec != nil && ev.Codec.SSCUHQ
		if current {
			a.pendingUHQ = false
		}
		a.mu.Unlock()
		if current {
			a.refresh()
		}
	case "volume":
		if ev.Volume != nil {
			a.mu.Lock()
			if a.eng == p && a.volumeLocked() != *ev.Volume {
				a.s.HeadphonesVolume = ev.Volume
				_ = config.Save(a.s)
			}
			a.mu.Unlock()
		}
	case ipc.EventStatus:
		if ev.Status == nil {
			return
		}
		a.mu.Lock()
		if a.eng != p {
			a.mu.Unlock()
			return
		}
		prev := a.st
		a.st = *ev.Status
		if !ev.Status.Connected {
			a.pendingUHQ = false
		}
		a.t.SetVolumeKeys(ev.Status.CaptureDevice != "")
		a.mu.Unlock()
		if ev.Status.Phase == "streaming" && prev.Phase != "streaming" {
			a.t.Balloon("SSCv2", fmt.Sprintf(T("%s: %s, %d кбит/с", "%s: %s, %d kbps"), nz(ev.Status.HeadphonesName, ev.Status.Headphones),
				ev.Status.Codec, ev.Status.BitrateKbps), 0)
		}
		if ev.Status.Phase == "error" && prev.Phase != "error" {
			a.t.Balloon(T("SSCv2: ошибка", "SSCv2: error"), ev.Status.Message, 2)
		}
		if ev.Status.AdapterAddr != "" && prev.AdapterAddr == "" {
			if s, err := keys.Open(); err == nil && s.Snapshot().Adapter == "" {
				_ = s.Merge(keys.File{Adapter: ev.Status.AdapterAddr})
			}
		}
		a.refresh()
	case "scan":
		a.mu.Lock()
		if a.eng != p {
			a.mu.Unlock()
			return
		}
		a.scan, a.scanning = ev.Devices, false
		a.mu.Unlock()
		n := 0
		for _, d := range ev.Devices {
			if d.Audio {
				n++
			}
		}
		a.t.Balloon(T("Поиск завершён", "Search finished"), fmt.Sprintf(T("Найдено устройств: %d (аудио: %d). Выберите в меню «Сопрячь устройство».",
			"Devices found: %d (audio: %d). Choose one in \"Pair a device\"."), len(ev.Devices), n), 0)
	case "linkkey":
		go a.syncKeyToWindows(ev.Addr, ev.Key)
	case "log":
		a.t.Balloon("SSCv2", ev.Msg, 1)
	}
}
