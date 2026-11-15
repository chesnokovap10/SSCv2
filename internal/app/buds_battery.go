package app

import (
	"fmt"
	"strconv"
	"strings"
	"time"

	"sscv2/internal/battery"
	"sscv2/internal/driver"
	"sscv2/internal/nativebt"
)

type windowsBattery struct {
	addr  string
	level *battery.BudsLevel
	tried time.Time
	read  time.Time
}

func (a *App) pollWindowsBattery() {
	a.mu.Lock()
	h := a.s.Headphones
	if a.eng != nil || h == nil || !battery.IsBuds(h.Name) || a.adapter.Mode != driver.BthUSB {
		a.windowsBattery = windowsBattery{}
		a.mu.Unlock()
		return
	}
	prev := a.windowsBattery
	a.mu.Unlock()

	addr, err := strconv.ParseUint(strings.ReplaceAll(h.Addr, ":", ""), 16, 48)
	if err != nil || addr == 0 {
		return
	}
	var next windowsBattery
	if driver.WindowsHeadphonesConnected(addr) {
		if strings.EqualFold(prev.addr, h.Addr) {
			next = prev
		}
		next.addr = h.Addr
		if time.Since(next.tried) >= battery.PollInterval {
			next.tried = time.Now()
			if level, ok := nativebt.ReadBudsBattery(addr); ok {
				next.level, next.read = &level, time.Now()
			}
		}
	}

	a.mu.Lock()
	defer a.mu.Unlock()
	if a.eng == nil && a.s.Headphones == h && a.adapter.Mode == driver.BthUSB {
		a.windowsBattery = next
	}
}

func (a *App) batteryMenuSuffixLocked() string {
	h := a.s.Headphones
	if h == nil {
		return ""
	}
	var level *battery.BudsLevel
	if a.eng != nil && a.st.Connected && strings.EqualFold(a.st.Headphones, h.Addr) {
		level = a.st.Battery
	} else if a.eng == nil && a.adapter.Mode == driver.BthUSB && strings.EqualFold(a.windowsBattery.addr, h.Addr) &&
		time.Since(a.windowsBattery.read) < battery.MaxAge {
		level = a.windowsBattery.level
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
	return fmt.Sprintf(T(" · Л %s / П %s", " · L %s / R %s"), percent(level.Left), percent(level.Right))
}
