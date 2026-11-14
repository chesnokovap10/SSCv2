package app

import (
	"errors"
	"fmt"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/engine"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
	"sscv2/internal/logx"
)

func (a *App) adapterID() driver.USBID {
	a.mu.Lock()
	defer a.mu.Unlock()
	if a.adapter.ID.VID != 0 {
		return a.adapter.ID
	}
	return driver.USBID{VID: a.s.VID, PID: a.s.PID}
}

func (a *App) refreshAdapter() driver.Status {
	a.mu.Lock()
	want := driver.USBID{VID: a.s.VID, PID: a.s.PID}
	a.mu.Unlock()
	st, ok := driver.FindAdapter(want)
	a.mu.Lock()
	if ok {
		a.adapter = st
		if a.s.VID != st.ID.VID || a.s.PID != st.ID.PID {
			a.s.VID, a.s.PID = st.ID.VID, st.ID.PID
			_ = config.Save(a.s)
		}
	} else {
		a.adapter = driver.Status{}
	}
	a.mu.Unlock()
	return st
}

func (a *App) initializePlayback() {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	st := a.refreshAdapter()
	_, svcRunning := helper.ServiceState()
	a.mu.Lock()
	want, restoreA2DP, nativeRequested := a.s.Mode, a.s.NativeA2DPAddress != "", a.s.WindowsTestSigning
	quitting := a.quitting
	a.mu.Unlock()
	if quitting {
		return
	}
	logf("adapter %s mode %s, saved mode %s, service running %v", st.ID, st.Mode, want, svcRunning)

	if st.Mode != driver.NotPresent && want.Streaming() && (st.Mode == driver.WinUSB || svcRunning) {
		a.switchModeLocked(want)
		return
	}

	if restoreA2DP || want == config.ModeOff {
		if err := a.stopNativePlaybackLocked(); err != nil {
			a.reportNativeError(err)
			want = config.ModeOff
		}
	}

	if nativeRequested && svcRunning && want == config.ModeOff && st.Mode == driver.BthUSB {
		if active, err := driver.TestSigning(); err == nil && active {
			if _, err := helper.Call(ipc.Request{Op: "native-profile-sync"}); err != nil {
				logf("initialize native Bluetooth: %v", err)
			}
		}
	}

	switch {
	case st.Mode == driver.NotPresent:
		a.t.Balloon("SSCv2", T("Встроенный адаптер MediaTek не найден.", "The built-in MediaTek adapter was not found."), 1)
	case want.Streaming():
		a.setMode(config.ModeOff)
	case st.Mode == driver.WinUSB:
		a.t.Balloon("SSCv2", T("Адаптер остался в режиме WinUSB. Выберите «Кодек > Выкл», чтобы вернуть Bluetooth Windows.",
			"The adapter is still in WinUSB mode. Choose \"Codec > Off\" to give Bluetooth back to Windows."), 1)
	}
}

func (a *App) setMode(m config.Mode) {
	a.mu.Lock()
	a.mode = m
	a.s.Mode = m
	_ = config.Save(a.s)
	a.mu.Unlock()
	a.refresh()
}

// switchMode serializes changes requested by the tray and the control pipe.
func (a *App) switchMode(mode config.Mode) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.switchModeLocked(mode)
}

func (a *App) switchModeLocked(mode config.Mode) {
	defer a.setBusy("")
	if mode == config.ModeOff {
		a.stopPlaybackLocked()
		return
	}
	a.cancelVolumeRestoreLocked()

	a.mu.Lock()
	current, eng, streaming, pendingUHQ := a.mode, a.eng, a.st.Streaming, a.pendingUHQ
	native, preferNative, quitting := a.native, a.s.WindowsTestSigning, a.quitting
	a.mu.Unlock()
	if quitting || pendingUHQ {
		return
	}
	if preferNative && native != nil {
		if native.Mode != mode {
			a.changeNativeCodecLocked(native, mode)
		}
		return
	}
	if !preferNative && current == mode && eng != nil && eng.running() {
		return
	}

	if err := a.stopNativePlaybackLocked(); err != nil {
		a.reportNativeError(err)
		return
	}
	if !preferNative {
		a.startWinUSBPlaybackLocked(mode, eng, streaming)
		return
	}
	if eng != nil {
		a.stopWinUSBEngineLocked(false)
	}
	a.releaseWinUSBCarryLocked()
	if st := a.refreshAdapter(); st.Mode == driver.WinUSB {
		if _, err := helper.Call(ipc.Request{Op: "driver", VID: st.ID.VID, PID: st.ID.PID}); err != nil {
			a.reportNativeError(err)
			return
		}
	}
	a.startNativePlaybackLocked(mode)
}

// beginShutdown serializes the last transition to Off with other playback work.
func (a *App) beginShutdown(keepMode bool) bool {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	if a.quitting {
		a.mu.Unlock()
		return false
	}
	a.quitting = true
	mode := a.mode
	needsRestore := a.needsPlaybackRestore()
	a.mu.Unlock()

	a.t.CloseMenu()
	if needsRestore {
		ok := a.stopPlaybackLocked()
		a.setBusy("")
		if !ok {
			a.mu.Lock()
			a.quitting = false
			a.mu.Unlock()
			return false
		}
	}
	if keepMode && mode.Streaming() {
		a.mu.Lock()
		a.s.Mode = mode
		_ = config.Save(a.s)
		a.mu.Unlock()
	}
	return true
}

// needsPlaybackRestore requires a.mu.
func (a *App) needsPlaybackRestore() bool {
	return a.mode.Streaming() || a.eng != nil || a.native != nil ||
		a.s.NativeA2DPAddress != "" || a.adapter.Mode == driver.WinUSB
}

// stopPlaybackLocked gives the radio and audio output back to Windows.
func (a *App) stopPlaybackLocked() bool {
	a.cancelVolumeRestoreLocked()
	if err := a.stopNativePlaybackLocked(); err != nil {
		a.reportNativeError(err)
		return false
	}

	a.mu.Lock()
	want := float32(a.volumeLocked()) / 127
	muted := a.s.HeadphonesMuted
	a.mode = config.ModeOff
	running := a.eng != nil
	restore := a.restoreMode
	a.mu.Unlock()
	if running {
		a.setBusy(T("остановка потока", "stopping the stream"))
	}
	a.stopWinUSBEngineLocked(false)
	a.setMode(config.ModeOff)
	st := a.refreshAdapter()
	if st.Mode == driver.WinUSB {
		a.setBusy(T("возврат адаптера Windows", "giving the adapter back to Windows"))
		// The headphones reconnect to Windows at their own level (Galaxy
		// Buds: 100 %) as soon as the radio is back - often before the
		// switch script has finished. Watch for them from now on, so the
		// jump is answered within ~50 ms.
		name := a.headphonesName()
		a.mu.Lock()
		variant := a.driverVariant
		a.mu.Unlock()
		logx.Dbgf("mode", "returning the adapter to Windows; volume restore for %q (mode %q)", name, nz(restore, "default"))
		if restore != "off" {
			settled, cancel, done := make(chan struct{}), make(chan struct{}), make(chan struct{})
			a.stopVolumeRestore = func() { close(cancel); <-done }
			a.mu.Lock()
			a.volSettled = settled
			a.mu.Unlock()
			go func() {
				defer close(done)
				if !audio.RestoreHeadphonesVolume(name, want, muted, 40*time.Second, logf, settled, cancel) {
					logf("volume: headphones %q did not come to Windows", name)
				}
			}()
		}
		if _, err := helper.Call(ipc.Request{Op: "driver", VID: st.ID.VID, PID: st.ID.PID, WinUSB: false, Variant: variant}); err != nil {
			logf("driver bthusb: %v", err)
			a.t.Balloon(T("Не удалось вернуть Bluetooth Windows", "Could not give Bluetooth back to Windows"), err.Error(), 2)
			a.refreshAdapter()
			return false
		}
		a.refreshAdapter()
	}
	return true
}

func (a *App) cancelVolumeRestoreLocked() {
	if a.stopVolumeRestore != nil {
		a.stopVolumeRestore()
		a.stopVolumeRestore = nil
		a.mu.Lock()
		a.volSettled = nil
		a.mu.Unlock()
	}
}

// stopWinUSBEngineLocked can transfer the muted output to the next engine.
func (a *App) stopWinUSBEngineLocked(keep bool) {
	a.mu.Lock()
	eng, st, carry := a.eng, a.st, a.carry
	a.eng, a.carry = nil, nil
	if eng == nil && keep {
		a.carry = carry
	}
	a.pendingUHQ = false
	if eng != nil {
		a.scanning = false
		a.t.SetVolumeKeys(false)
	}
	a.mu.Unlock()
	if eng == nil {
		if !keep && carry != nil {
			engine.RestoreAudio(ipc.EngineStatus{MuteEndpoint: carry.MuteEndpoint})
		}
		return
	}

	forced := eng.stop(15*time.Second, keep)
	if !keep && (forced || eng.waitErr != nil) {
		engine.RestoreAudio(st)
	}
	if keep && st.MuteEndpoint != "" {
		a.mu.Lock()
		a.carry = &ipc.AudioCarry{MuteEndpoint: st.MuteEndpoint}
		a.mu.Unlock()
	}
}

func (a *App) releaseWinUSBCarryLocked() {
	a.mu.Lock()
	carry := a.carry
	a.carry = nil
	a.mu.Unlock()
	if carry != nil {
		engine.RestoreAudio(ipc.EngineStatus{MuteEndpoint: carry.MuteEndpoint})
	}
}

// restartWinUSB applies settings, keys and mouse changes to the running engine.
func (a *App) restartWinUSB() {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.restartWinUSBLocked()
}

func (a *App) restartWinUSBLocked() {
	a.mu.Lock()
	running := a.eng != nil && !a.quitting
	keep := running && !a.noBitrate(a.mode)
	a.mu.Unlock()
	if !running {
		return
	}
	defer a.setBusy("")
	a.setBusy(T("перезапуск потока", "restarting the stream"))
	a.stopWinUSBEngineLocked(keep)
	a.launchWinUSBLocked()
}

func (a *App) launchWinUSBLocked() {
	if err := a.startWinUSBEngineLocked(); err != nil {
		defer a.setBusy("")
		logf("start engine: %v", err)
		a.t.Balloon("SSCv2", T("Не удалось запустить движок: ", "Could not start the engine: ")+err.Error(), 2)
		a.markStreamStartFailed()
	}
}

func (a *App) markStreamStartFailed() {
	a.mu.Lock()
	a.st.StreamStartFailed = true
	a.mu.Unlock()
	a.refresh()
}

func (a *App) startNativePlaybackLocked(mode config.Mode) {
	a.setBusy(fmt.Sprintf(T("Запуск %s через Bluetooth Windows", "Starting %s through Windows Bluetooth"), modeName(mode)))
	if err := a.openNativePlaybackLocked(mode); err != nil {
		a.failNativePlaybackLocked(mode, err)
		return
	}
	a.setMode(mode)
}

func (a *App) changeNativeCodecLocked(p *nativeProcess, mode config.Mode) {
	changed, err := a.requestNativeCodec(p, mode)
	if err != nil {
		a.failNativePlaybackLocked(mode, err)
	} else if changed {
		a.setMode(mode)
	}
}

func (a *App) stopNativePlaybackLocked() error {
	a.stopNativeWorker()
	return a.resumeNativeStereo()
}

// disableNativePlaybackLocked leaves a running WinUSB session alone.
func (a *App) disableNativePlaybackLocked() bool {
	a.mu.Lock()
	wasNative := a.native != nil || a.nativeWaiting != nil
	a.mu.Unlock()
	if err := a.stopNativePlaybackLocked(); err != nil {
		a.reportNativeError(err)
		return false
	}
	if wasNative {
		a.setMode(config.ModeOff)
	}
	return true
}

func (a *App) failNativePlaybackLocked(mode config.Mode, err error) {
	if restoreErr := a.stopNativePlaybackLocked(); restoreErr != nil {
		a.reportNativeError(errors.Join(err, restoreErr))
		return
	}
	logf("native %s: %v", mode, err)
	a.mu.Lock()
	a.st.StreamStartFailed = true
	a.mu.Unlock()
	a.setMode(mode)
}

func (a *App) reportNativeError(err error) {
	logf("native Bluetooth: %v", err)
	a.setMode(config.ModeOff)
	a.t.Balloon(T("Ошибка через Bluetooth Windows", "Windows Bluetooth failed"), err.Error(), 2)
}

func (a *App) onEngineExit(p *workerProcess, err error) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	if p.stopReq.Load() {
		logf("engine stopped")
		return
	}
	a.mu.Lock()
	last := a.st
	current := a.eng == p
	if current {
		a.eng = nil
		a.scanning = false
		a.pendingUHQ = false
		if last.StreamStartFailed && last.MuteEndpoint != "" {
			a.carry = &ipc.AudioCarry{MuteEndpoint: last.MuteEndpoint}
		}
		a.t.SetVolumeKeys(false)
	}
	mode, quitting := a.mode, a.quitting
	a.mu.Unlock()
	logf("engine exited unexpectedly: %v (phase %s: %s)", err, last.Phase, last.Message)
	if current && !last.StreamStartFailed {
		engine.RestoreAudio(last)
	}
	if !current || quitting || mode == config.ModeOff || last.StreamStartFailed {
		a.refresh()
		return
	}
	// Restart with back-off; give up after 4 crashes in 2 minutes.
	a.mu.Lock()
	now := time.Now()
	keep := a.crashes[:0]
	for _, t := range a.crashes {
		if now.Sub(t) < 2*time.Minute {
			keep = append(keep, t)
		}
	}
	a.crashes = append(keep, now)
	n := len(a.crashes)
	a.mu.Unlock()
	if n > 4 {
		msg := last.Message
		if msg == "" {
			msg = T("движок несколько раз завершился с ошибкой", "the engine failed several times")
		}
		a.t.Balloon(T("SSCv2 остановлен", "SSCv2 stopped"), msg+T(" — подробности в журнале.", " - see the log for details."), 2)
		a.refresh()
		return
	}
	go func() {
		time.Sleep(3 * time.Second)
		a.opMu.Lock()
		defer a.opMu.Unlock()
		a.mu.Lock()
		still := a.mode == mode && a.eng == nil && a.native == nil && !a.quitting
		a.mu.Unlock()
		if still && a.refreshAdapter().Mode == driver.WinUSB {
			a.launchWinUSBLocked()
		}
	}()
	a.refresh()
}

func (a *App) nativeWorkerExited(p *nativeProcess, err error, last string) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	current, quitting := a.native == p, a.quitting
	a.mu.Unlock()
	if !current {
		return
	}
	if err == nil {
		err = fmt.Errorf("native %s worker stopped", p.Mode)
	}
	if last != "" {
		err = fmt.Errorf("%w: %s", err, last)
	}
	if !quitting && p.linkLost {
		if cleanupErr := a.stopNativePlaybackLocked(); cleanupErr != nil {
			a.reportNativeError(errors.Join(err, cleanupErr))
			return
		}
		a.mu.Lock()
		a.nativeWaiting = p
		a.mu.Unlock()
		logf("native %s: link lost, waiting for headphones", p.Mode)
		a.refresh()
		go a.waitForNativeHeadphones(p)
		return
	}
	a.failNativePlaybackLocked(p.Mode, err)
}
