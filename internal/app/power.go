package app

// onResume invalidates the pre-sleep status immediately. USB/HCI state cannot
// be trusted across suspend, even if the child process still reports streaming.
// Only the automatic-resume notification is used: Windows may subsequently
// send a second notification when the user becomes active.
func (a *App) onResume() {
	a.mu.Lock()
	if p := a.invalidateNativeAfterResumeLocked(); p != nil {
		a.mu.Unlock()
		a.refresh()
		go a.recoverNativeAfterResume(p)
		return
	}
	p := a.eng
	if a.quitting || !a.mode.Streaming() || p == nil || a.resumeEngine == p {
		a.mu.Unlock()
		return
	}
	a.resumeEngine = p
	a.mu.Unlock()
	logf("power: resumed; invalidating pre-sleep engine status")
	a.refresh()
	go a.recoverAfterResume(p)
}

func (a *App) invalidateNativeAfterResumeLocked() *nativeProcess {
	p := a.native
	if p == nil || a.quitting || !a.mode.Streaming() || a.resumeNative == p {
		return nil
	}
	a.resumeNative, p.ready = p, false
	return p
}

func (a *App) recoverNativeAfterResume(p *nativeProcess) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	defer func() {
		a.mu.Lock()
		if a.resumeNative == p {
			a.resumeNative = nil
		}
		a.mu.Unlock()
		a.refresh()
	}()
	a.mu.Lock()
	current, mode := a.native == p && !a.quitting && a.mode.Streaming(), a.mode
	a.mu.Unlock()
	if !current {
		return
	}
	a.setBusy(T("восстановление после сна", "recovering after sleep"))
	defer a.setBusy("")
	if err := a.stopNativePlaybackLocked(); err != nil {
		a.failNativePlaybackLocked(mode, err)
		return
	}
	a.startNativePlaybackLocked(mode)
}

func (a *App) recoverAfterResume(p *workerProcess) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	defer func() {
		a.mu.Lock()
		if a.resumeEngine == p {
			a.resumeEngine = nil
		}
		a.mu.Unlock()
		a.refresh()
	}()
	a.mu.Lock()
	current := !a.quitting && a.mode.Streaming() && a.eng == p
	a.mu.Unlock()
	if !current {
		return // a user operation has already stopped or replaced this process
	}
	a.setBusy(T("восстановление после сна", "recovering after sleep"))
	defer a.setBusy("")
	// Release the physical output: the headphones may now be in their case.
	// A fresh engine reinitializes USB, firmware, Bluetooth and WASAPI.
	a.stopWinUSBEngineLocked(false)
	a.launchWinUSBLocked()
}
