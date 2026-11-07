package app

// onResume invalidates the pre-sleep status immediately. USB/HCI state cannot
// be trusted across suspend, even if the child process still reports streaming.
// Only the automatic-resume notification is used: Windows may subsequently
// send a second notification when the user becomes active.
func (a *App) onResume() {
	a.mu.Lock()
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

func (a *App) recoverAfterResume(p *engineProc) {
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
	a.stopForRestart(p, false)
	a.startEngineLocked()
}
