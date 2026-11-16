package app

import (
	"fmt"
	"strconv"
	"strings"
	"time"

	"sscv2/internal/buds"
	"sscv2/internal/driver"
	"sscv2/internal/nativebt"
)

type windowsBudsStatus struct {
	addr      string
	level     *buds.Level
	equalizer *uint8
	tried     time.Time
	read      time.Time
}

func (a *App) pollWindowsBattery() {
	if !a.budsIOMu.TryLock() {
		return
	}
	defer a.budsIOMu.Unlock()
	a.mu.Lock()
	h := a.s.Headphones
	if a.eng != nil || a.native != nil || h == nil || a.adapter.Mode != driver.BthUSB {
		a.windowsBuds = windowsBudsStatus{}
		a.mu.Unlock()
		return
	}
	prev := a.windowsBuds
	a.mu.Unlock()

	addr, err := strconv.ParseUint(strings.ReplaceAll(h.Addr, ":", ""), 16, 48)
	if err != nil || addr == 0 {
		return
	}
	var next windowsBudsStatus
	if driver.WindowsHeadphonesConnected(addr) {
		if strings.EqualFold(prev.addr, h.Addr) {
			next = prev
		}
		next.addr = h.Addr
		if time.Since(next.tried) >= buds.PollInterval {
			next.tried = time.Now()
			status, _ := nativebt.ReadBudsStatus(addr, buds.ProtocolForName(h.Name), nil)
			if status.Level.Known() {
				next.level, next.read = &status.Level, time.Now()
			}
			if status.Equalizer != nil {
				next.equalizer, next.read = status.Equalizer, time.Now()
			}
		}
	}

	a.mu.Lock()
	defer a.mu.Unlock()
	if a.eng == nil && a.native == nil && a.s.Headphones == h && a.adapter.Mode == driver.BthUSB {
		a.windowsBuds = next
		a.reconcileEqualizerLocked()
	}
}

func (a *App) batteryMenuTextLocked() string {
	h := a.s.Headphones
	if h == nil {
		return ""
	}
	var level *buds.Level
	if a.eng != nil && a.st.Connected && strings.EqualFold(a.st.Headphones, h.Addr) {
		level = a.st.Battery
	} else if a.native != nil && a.native.ready && time.Since(a.native.budsBatteryAt) < buds.MaxAge {
		level = a.native.budsBattery
	} else if a.eng == nil && a.adapter.Mode == driver.BthUSB && strings.EqualFold(a.windowsBuds.addr, h.Addr) &&
		time.Since(a.windowsBuds.read) < buds.MaxAge {
		level = a.windowsBuds.level
	}
	if level == nil || !level.Known() {
		return ""
	}
	percent := func(n int) string {
		if n < 0 {
			return "—"
		}
		return fmt.Sprintf("%d%%", n)
	}
	return percent(level.Left) + "|" + percent(level.Right)
}
