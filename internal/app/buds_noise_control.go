package app

import (
	"strconv"
	"strings"
	"time"

	"sscv2/internal/buds"
	"sscv2/internal/driver"
	"sscv2/internal/ipc"
	"sscv2/internal/nativebt"
	"sscv2/internal/tray"
)

func (a *App) noiseControlLocked() *buds.NoiseControl {
	h := a.s.Headphones
	if h == nil {
		return nil
	}
	switch {
	case a.eng != nil:
		if a.st.Connected && strings.EqualFold(a.st.Headphones, h.Addr) {
			return a.st.NoiseControl
		}
	case a.native != nil:
		if a.native.ready && !a.native.linkLost {
			return a.native.budsNoiseControl
		}
	case a.adapter.Mode == driver.BthUSB && strings.EqualFold(a.windowsBuds.addr, h.Addr) &&
		time.Since(a.windowsBuds.noiseRead) < buds.MaxAge:
		return a.windowsBuds.noiseControl
	}
	return nil
}

func (a *App) noiseControlMenuLocked(busy bool) *tray.Item {
	control := a.noiseControlLocked()
	a.rememberNoiseControlLocked(control)
	available := control != nil
	if !available {
		control = a.lastNoiseControl
	}
	if control == nil {
		control = &buds.NoiseControl{Mode: buds.NoiseUnknown, Modes: 3}
	}
	shown := control.Mode
	if request := a.pendingNoiseControl; request.matchesLocked(a) && a.budsLinkAvailableLocked() && control.Allows(request.value) {
		shown, available = request.value, true
	}
	labels := [...]string{
		T("Выкл", "Off"), T("Вкл", "On"), T("Прозрачность", "Ambient sound"), T("Адаптивное", "Adaptive"),
	}
	label := "—"
	if control.Allows(shown) {
		label = labels[shown]
	}
	item := &tray.Item{
		ID: idNoiseControlMenu, Text: T("Шумоподавление: ", "Noise control: ") + label,
		LiveLabel: true, Disabled: busy || !available,
	}
	for mode, label := range labels {
		if control.Allows(uint8(mode)) {
			item.Sub = append(item.Sub, tray.Item{
				ID: idNoiseControlBase + mode, Text: label, Radio: true,
				Checked: uint8(mode) == shown, Disabled: item.Disabled,
			})
		}
	}
	return item
}

func (a *App) rememberNoiseControlLocked(control *buds.NoiseControl) {
	address := ""
	if h := a.s.Headphones; h != nil {
		address = h.Addr
	}
	if !strings.EqualFold(address, a.noiseDevice) {
		a.noiseDevice, a.lastNoiseControl = address, nil
	}
	if address != "" && control != nil {
		a.lastNoiseControl = control
	}
}

func (a *App) stageNoiseControlLocked(mode uint8) *budsSettingRequest {
	current := a.noiseControlLocked()
	if !current.Allows(mode) || a.quitting || a.busy != "" || a.pendingUHQ {
		return nil
	}
	shown := current.Mode
	if request := a.pendingNoiseControl; request.matchesLocked(a) {
		shown = request.value
	}
	if shown == mode {
		return nil
	}
	a.rememberNoiseControlLocked(current)
	request := a.budsSettingRequestLocked(mode, current.Mode, false)
	a.pendingNoiseControl = request
	return request
}

func (a *App) reconcileNoiseControlLocked() {
	current := a.noiseControlLocked()
	a.rememberNoiseControlLocked(current)
	if request := a.pendingNoiseControl; request != nil {
		if !request.matchesLocked(a) || !a.budsLinkAvailableLocked() ||
			(current != nil && current.Mode == request.value && current.Mode != request.baseline) {
			a.pendingNoiseControl = nil
		}
	}
}

func (a *App) finishNoiseControl(request *budsSettingRequest) {
	a.mu.Lock()
	changed := a.pendingNoiseControl == request
	if changed {
		a.pendingNoiseControl = nil
	}
	a.mu.Unlock()
	if changed {
		a.t.RefreshMenu()
	}
}

func (a *App) setNoiseControl(mode uint8) {
	a.mu.Lock()
	request := a.stageNoiseControlLocked(mode)
	a.mu.Unlock()
	if request == nil {
		return
	}
	a.t.RefreshMenu()
	go a.sendNoiseControl(request)
}

func (a *App) sendNoiseControl(request *budsSettingRequest) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	current := a.pendingNoiseControl == request && request.matchesLocked(a) &&
		a.budsLinkAvailableLocked() && !a.quitting
	a.mu.Unlock()
	if !current {
		a.finishNoiseControl(request)
		return
	}
	time.AfterFunc(request.timeout(), func() { a.finishNoiseControl(request) })
	command := ipc.Command{Cmd: ipc.CommandNoiseControl, Addr: request.address, NoiseMode: &request.value}
	var err error
	switch {
	case request.engine != nil:
		err = request.engine.in.Write(command)
	case request.native != nil:
		err = request.native.in.Write(command)
	default:
		a.setWindowsNoiseControl(request)
		a.finishNoiseControl(request)
	}
	if err != nil {
		logf("Buds noise control: %v", err)
		a.finishNoiseControl(request)
	}
}

func (a *App) setWindowsNoiseControl(request *budsSettingRequest) {
	address, mode := request.address, request.value
	addr, err := strconv.ParseUint(strings.ReplaceAll(address, ":", ""), 16, 48)
	if err != nil || !driver.WindowsHeadphonesConnected(addr) {
		return
	}
	a.budsIOMu.Lock()
	status, confirmed := nativebt.ReadBudsStatus(addr, request.protocol, request.commands, nil, &mode)
	a.mu.Lock()
	if status.NoiseControl != nil && strings.EqualFold(a.windowsBuds.addr, address) {
		a.windowsBuds.noiseControl, a.windowsBuds.noiseRead = status.NoiseControl, time.Now()
	}
	a.mu.Unlock()
	a.budsIOMu.Unlock()
	if !confirmed {
		logf("Buds noise control: headphones did not confirm mode %d", mode)
	}
}
