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

const equalizerCount = buds.EqualizerCount

type budsSettingRequest struct {
	value, baseline uint8
	fallback        bool
	address         string
	protocol        buds.Protocol
	commands        buds.ControlCommands
	engine          *workerProcess
	native          *nativeProcess
}

func (a *App) budsSettingRequestLocked(value, baseline uint8, fallback bool) *budsSettingRequest {
	h := a.s.Headphones
	return &budsSettingRequest{
		value: value, baseline: baseline, fallback: fallback, address: h.Addr,
		protocol: buds.ProtocolForName(h.Name), engine: a.eng, native: a.native,
		commands: a.profileCommands(h),
	}
}

func (r *budsSettingRequest) matchesLocked(a *App) bool {
	return r != nil && a.s.Headphones != nil && strings.EqualFold(r.address, a.s.Headphones.Addr) &&
		r.engine == a.eng && r.native == a.native
}

func (r *budsSettingRequest) timeout() time.Duration {
	if r.engine == nil && r.native == nil {
		return 8 * time.Second // Windows RFCOMM has to open the socket first.
	}
	return 4 * time.Second
}

func (a *App) equalizerLocked() *uint8 {
	h := a.s.Headphones
	if h == nil {
		return nil
	}
	switch {
	case a.eng != nil:
		if a.st.Connected && strings.EqualFold(a.st.Headphones, h.Addr) {
			return a.st.Equalizer
		}
	case a.native != nil:
		if a.native.ready && !a.native.linkLost {
			return a.native.budsEqualizer
		}
	case a.adapter.Mode == driver.BthUSB && strings.EqualFold(a.windowsBuds.addr, h.Addr) &&
		time.Since(a.windowsBuds.read) < buds.MaxAge:
		return a.windowsBuds.equalizer
	}
	return nil
}

func (a *App) equalizerMenuLocked(busy bool) *tray.Item {
	labels := [equalizerCount]string{
		T("Обычный", "Normal"), T("Усиление басов", "Bass boost"), T("Мягкий", "Soft"),
		T("Динамичный", "Dynamic"), T("Чёткий", "Clear"), T("Усиление высоких", "Treble boost"),
	}
	current := a.equalizerLocked()
	a.rememberEqualizerLocked(current)
	available := current != nil || a.noiseControlLocked().UsesFallback()
	if current == nil {
		current = a.lastEqualizer
	}
	if request := a.pendingEqualizer; request.matchesLocked(a) && a.budsLinkAvailableLocked() {
		current = &request.value
		available = true
	}
	label := "—"
	if current != nil && *current == buds.EqualizerCustom {
		label = T("Пользовательский", "Custom")
	} else if current != nil && *current < equalizerCount {
		label = labels[*current]
	}
	item := &tray.Item{ID: idEqualizerMenu, Text: T("Эквалайзер: ", "Equalizer: ") + label, LiveLabel: true,
		Disabled: busy || !available || a.failedEqualizer.matchesLocked(a)}
	for i, label := range labels {
		item.Sub = append(item.Sub, tray.Item{
			ID: idEqualizerBase + i, Text: label, Radio: true,
			Checked: current != nil && int(*current) == i, Disabled: item.Disabled,
		})
	}
	return item
}

// Remember support across a transport change for the selected headphones.
// The remembered value is only used to draw a disabled menu row.
func (a *App) rememberEqualizerLocked(preset *uint8) {
	address := ""
	if h := a.s.Headphones; h != nil {
		address = h.Addr
	}
	if !strings.EqualFold(address, a.equalizerDevice) {
		a.equalizerDevice, a.lastEqualizer = address, nil
	}
	if address != "" && preset != nil {
		a.lastEqualizer = preset
	}
}

func (a *App) budsLinkAvailableLocked() bool {
	if a.s.Headphones == nil {
		return false
	}
	switch {
	case a.eng != nil:
		return a.st.Connected && strings.EqualFold(a.st.Headphones, a.s.Headphones.Addr)
	case a.native != nil:
		return a.native.ready && !a.native.linkLost
	default:
		return a.adapter.Mode == driver.BthUSB && strings.EqualFold(a.windowsBuds.addr, a.s.Headphones.Addr)
	}
}

func (a *App) stageEqualizerLocked(preset uint8) *budsSettingRequest {
	current := a.equalizerLocked()
	fallback := a.noiseControlLocked().UsesFallback()
	if (current == nil && !fallback) || preset >= equalizerCount || a.quitting || a.busy != "" ||
		a.pendingUHQ || a.failedEqualizer.matchesLocked(a) {
		return nil
	}
	baseline := uint8(0xff)
	if current != nil {
		baseline = *current
	}
	shown := baseline
	if request := a.pendingEqualizer; request.matchesLocked(a) {
		shown = request.value
	}
	if shown == preset {
		return nil
	}
	request := a.budsSettingRequestLocked(preset, baseline, fallback)
	a.pendingEqualizer = request
	return request
}

func (a *App) reconcileEqualizerLocked() {
	current := a.equalizerLocked()
	a.rememberEqualizerLocked(current)
	if failed := a.failedEqualizer; failed != nil && (!failed.matchesLocked(a) || !a.budsLinkAvailableLocked() ||
		(current != nil && *current == failed.value && *current != failed.baseline)) {
		a.failedEqualizer = nil
	}
	if request := a.pendingEqualizer; request != nil {
		if !request.matchesLocked(a) || !a.budsLinkAvailableLocked() ||
			(current != nil && *current == request.value && *current != request.baseline) {
			a.pendingEqualizer = nil
		}
	}
}

func (a *App) finishEqualizer(request *budsSettingRequest, unconfirmed bool) {
	a.mu.Lock()
	changed := a.pendingEqualizer == request
	if changed {
		a.pendingEqualizer = nil
		current := a.equalizerLocked()
		if unconfirmed && request.fallback && request.matchesLocked(a) && a.budsLinkAvailableLocked() &&
			(current == nil || *current != request.value) {
			a.failedEqualizer = request
		}
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
	go a.sendEqualizer(request)
}

func (a *App) sendEqualizer(request *budsSettingRequest) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	current := a.pendingEqualizer == request && request.matchesLocked(a) && a.budsLinkAvailableLocked() && !a.quitting
	a.mu.Unlock()
	if !current {
		a.finishEqualizer(request, false)
		return
	}
	time.AfterFunc(request.timeout(), func() { a.finishEqualizer(request, true) })
	address, preset, eng, native := request.address, request.value, request.engine, request.native
	command := ipc.Command{Cmd: ipc.CommandEqualizer, Addr: address, Equalizer: &preset}
	if eng != nil {
		if err := eng.in.Write(command); err != nil {
			logf("Buds equalizer: %v", err)
			a.finishEqualizer(request, true)
		}
		return
	}
	if native != nil {
		if err := native.in.Write(command); err != nil {
			logf("Buds equalizer: %v", err)
			a.finishEqualizer(request, true)
		}
		return
	}
	addr, err := strconv.ParseUint(strings.ReplaceAll(address, ":", ""), 16, 48)
	if err != nil || !driver.WindowsHeadphonesConnected(addr) {
		a.finishEqualizer(request, false)
		return
	}
	a.budsIOMu.Lock()
	defer a.budsIOMu.Unlock()
	status, confirmed := nativebt.ReadBudsStatus(addr, request.protocol, request.commands, &preset, nil)
	a.mu.Lock()
	if status.Equalizer != nil && strings.EqualFold(a.windowsBuds.addr, address) {
		a.windowsBuds.equalizer, a.windowsBuds.read = status.Equalizer, time.Now()
	}
	a.mu.Unlock()
	if !confirmed {
		logf("Buds equalizer: headphones did not confirm preset %d", preset)
	}
	a.finishEqualizer(request, !confirmed)
}
