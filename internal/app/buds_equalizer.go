package app

import (
	"strconv"
	"strings"
	"time"

	"sscv2/internal/battery"
	"sscv2/internal/driver"
	"sscv2/internal/ipc"
	"sscv2/internal/nativebt"
	"sscv2/internal/tray"
)

const equalizerCount = battery.BudsEqualizerCount

type equalizerRequest struct {
	preset, baseline uint8
	address          string
	engine           *workerProcess
	native           *nativeProcess
}

func isEqualizerBuds(name string) bool {
	return strings.Contains(strings.ToLower(name), "buds2 pro")
}

func (a *App) equalizerLocked() *uint8 {
	h := a.s.Headphones
	if h == nil || !isEqualizerBuds(h.Name) {
		return nil
	}
	switch {
	case a.eng != nil:
		if a.st.Connected && strings.EqualFold(a.st.Headphones, h.Addr) {
			return a.st.Equalizer
		}
	case a.native != nil:
		if a.native.ready {
			return a.native.budsEqualizer
		}
	case a.adapter.Mode == driver.BthUSB && strings.EqualFold(a.windowsBattery.addr, h.Addr) &&
		time.Since(a.windowsBattery.read) < battery.MaxAge:
		return a.windowsBattery.equalizer
	}
	return nil
}

func (a *App) equalizerMenuLocked(busy bool) tray.Item {
	labels := [equalizerCount]string{
		T("Обычный", "Normal"), T("Усиление басов", "Bass boost"), T("Мягкий", "Soft"),
		T("Динамичный", "Dynamic"), T("Чёткий", "Clear"), T("Усиление высоких", "Treble boost"),
	}
	current := a.equalizerLocked()
	if current != nil && *current >= equalizerCount {
		current = nil
	}
	if request := a.pendingEqualizer; a.equalizerRequestCurrentLocked(request) && a.equalizerLinkAvailableLocked() {
		current = &request.preset
	}
	item := tray.Item{ID: idEqualizerMenu, Text: T("Эквалайзер: ", "Equalizer: "), LiveLabel: true, Disabled: current == nil || busy}
	if current == nil {
		item.Text += "—"
	} else {
		item.Text += labels[*current]
	}
	for i, label := range labels {
		item.Sub = append(item.Sub, tray.Item{
			ID: idEqualizerBase + i, Text: label, Radio: true,
			Checked: current != nil && int(*current) == i, Disabled: item.Disabled,
		})
	}
	return item
}

func (a *App) equalizerLinkAvailableLocked() bool {
	switch {
	case a.eng != nil:
		return a.st.Connected && strings.EqualFold(a.st.Headphones, a.s.Headphones.Addr)
	case a.native != nil:
		return a.native.ready
	default:
		return a.adapter.Mode == driver.BthUSB
	}
}

func (a *App) equalizerRequestCurrentLocked(request *equalizerRequest) bool {
	return request != nil && a.pendingEqualizer == request && a.s.Headphones != nil &&
		strings.EqualFold(request.address, a.s.Headphones.Addr) && request.engine == a.eng && request.native == a.native
}

func (a *App) stageEqualizerLocked(preset uint8) *equalizerRequest {
	current := a.equalizerLocked()
	if current == nil || preset >= equalizerCount || a.quitting || a.busy != "" {
		return nil
	}
	shown := *current
	if request := a.pendingEqualizer; a.equalizerRequestCurrentLocked(request) {
		shown = request.preset
	}
	if shown == preset {
		return nil
	}
	request := &equalizerRequest{
		preset: preset, baseline: *current, address: a.s.Headphones.Addr,
		engine: a.eng, native: a.native,
	}
	a.pendingEqualizer = request
	return request
}

func (a *App) reconcileEqualizerLocked() {
	if request := a.pendingEqualizer; request != nil {
		current := a.equalizerLocked()
		if !a.equalizerRequestCurrentLocked(request) || !a.equalizerLinkAvailableLocked() ||
			(current != nil && *current == request.preset && *current != request.baseline) {
			a.pendingEqualizer = nil
		}
	}
}

func (a *App) clearPendingEqualizer(request *equalizerRequest) {
	a.mu.Lock()
	changed := a.pendingEqualizer == request
	if changed {
		a.pendingEqualizer = nil
	}
	a.mu.Unlock()
	if changed {
		a.t.RefreshMenu()
	}
}

func (a *App) setEqualizer(preset uint8) {
	a.mu.Lock()
	request := a.stageEqualizerLocked(preset)
	a.mu.Unlock()
	if request == nil {
		return
	}
	a.t.RefreshMenu()
	timeout := 4 * time.Second
	if request.engine == nil && request.native == nil {
		timeout = 8 * time.Second // one-shot Windows RFCOMM has to open the socket first
	}
	time.AfterFunc(timeout, func() { a.clearPendingEqualizer(request) })
	go a.sendEqualizer(request)
}

func (a *App) sendEqualizer(request *equalizerRequest) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	current := a.equalizerRequestCurrentLocked(request) && !a.quitting
	a.mu.Unlock()
	if !current {
		a.clearPendingEqualizer(request)
		return
	}
	address, preset, eng, native := request.address, request.preset, request.engine, request.native
	command := ipc.Command{Cmd: ipc.CommandEqualizer, Addr: address, Equalizer: &preset}
	if eng != nil {
		if err := eng.in.Write(command); err != nil {
			logf("Buds equalizer: %v", err)
			a.clearPendingEqualizer(request)
		}
		return
	}
	if native != nil {
		if err := native.in.Write(command); err != nil {
			logf("Buds equalizer: %v", err)
			a.clearPendingEqualizer(request)
		}
		return
	}
	addr, err := strconv.ParseUint(strings.ReplaceAll(address, ":", ""), 16, 48)
	if err != nil || !driver.WindowsHeadphonesConnected(addr) {
		a.clearPendingEqualizer(request)
		return
	}
	a.budsIOMu.Lock()
	defer a.budsIOMu.Unlock()
	status, confirmed := nativebt.ReadBudsStatus(addr, &preset)
	a.mu.Lock()
	if status.Equalizer != nil && strings.EqualFold(a.windowsBattery.addr, address) {
		a.windowsBattery.equalizer, a.windowsBattery.read = status.Equalizer, time.Now()
	}
	a.mu.Unlock()
	if !confirmed {
		logf("Buds equalizer: headphones did not confirm preset %d", preset)
	}
	a.clearPendingEqualizer(request)
}
