package app

import (
	"fmt"
	"strings"

	"sscv2/internal/config"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
)

func (a *App) syncKeyToWindows(addr, key string) {
	if _, running := helper.ServiceState(); !running {
		a.t.Balloon(T("Новый ключ сопряжения", "New pairing key"), fmt.Sprintf(T("Запустите службу (Настройки), чтобы устройство %s осталось сопряжённым и в Bluetooth Windows.",
			"Start the service (Settings) so that %s stays paired in Windows Bluetooth too."), addr), 1)
		return
	}
	a.mu.Lock()
	adapter := a.st.AdapterAddr
	a.mu.Unlock()
	if adapter == "" {
		return
	}
	if _, err := helper.Call(ipc.Request{Op: "keys-write", Adapter: adapter, Device: addr, Key: key}); err != nil {
		logf("keys-write: %v", err)
		return
	}
	logf("link key for %s copied to Windows", addr)
}

func (a *App) importWindows() {
	a.setBusy(T("импорт ключей Windows", "importing Windows keys"))
	defer a.setBusy("")
	resp, err := helper.Call(ipc.Request{Op: "keys-read"})
	if err != nil {
		a.t.Balloon(T("Импорт не удался", "Import failed"), err.Error(), 2)
		return
	}
	var bonds []keys.AdapterBonds
	if err := jsonUnmarshal(resp.Data, &bonds); err != nil || len(bonds) == 0 {
		a.t.Balloon(T("Импорт", "Import"), T("Windows не хранит ключей Bluetooth.", "Windows keeps no Bluetooth keys."), 1)
		return
	}
	store, _ := keys.Open()
	known := map[string]bool{}
	a.mu.Lock()
	known[a.st.AdapterAddr] = true
	a.mu.Unlock()
	previous := store.Snapshot()
	known[previous.Adapter] = true
	if r, _ := windowsRadio(); r != "" {
		known[r] = true
	}
	best, bestScore := -1, -1
	for i, b := range bonds {
		score := len(b.Classic) + len(b.LE)
		if known[b.Adapter] {
			score += 1000
		}
		if score > bestScore {
			best, bestScore = i, score
		}
	}
	b := bonds[best]
	b.File.Adapter = b.Adapter // shadowed by the outer field in JSON
	if err := store.ImportWindows(b.File); err != nil {
		a.t.Balloon(T("Импорт не удался", "Import failed"), err.Error(), 2)
		return
	}
	a.afterImport(store, previous.LE, fmt.Sprintf(T("Адаптер %s: устройств %d, мышей %d.", "Adapter %s: %d device(s), %d mouse/mice."), b.Adapter, len(b.Classic), len(b.LE)))
}

func (a *App) afterImport(store *keys.Store, previousLE []keys.LE, msg string) {
	a.mu.Lock()
	if a.s.Headphones == nil {
		if c, ok := store.FindClassic(""); ok {
			a.s.Headphones = &config.Device{Addr: c.Addr, Name: c.Name}
			msg += T(" Наушники: ", " Headphones: ") + nz(c.Name, c.Addr) + "."
		}
	}
	if a.s.Mouse == nil {
		if l, ok := store.FindLE(""); ok {
			a.s.Mouse = &config.Device{Addr: l.Addr, Name: l.Name}
			msg += T(" Мышь: ", " Mouse: ") + nz(l.Name, l.Addr) + "."
		} else if c, ok := store.FindClassicMouse(); ok {
			a.s.Mouse = &config.Device{Addr: c.Addr, Name: c.Name}
			msg += T(" Мышь: ", " Mouse: ") + nz(c.Name, c.Addr) + "."
		}
	} else if _, ok := store.FindLE(a.s.Mouse.Addr); !ok {
		for _, old := range previousLE {
			if !strings.EqualFold(old.Addr, a.s.Mouse.Addr) {
				continue
			}
			a.s.Mouse = replacementLEMouse(old, store.Snapshot().LE)
			break
		}
	}
	_ = config.Save(a.s)
	running := a.eng != nil
	a.mu.Unlock()
	a.t.Balloon(T("Ключи импортированы", "Keys imported"), msg, 0)
	if running {
		a.restartWinUSB()
	}
}

func replacementLEMouse(old keys.LE, current []keys.LE) *config.Device {
	var replacement *config.Device
	for _, bond := range current {
		if old.Name == "" || !strings.EqualFold(old.Name, bond.Name) {
			continue
		}
		if replacement != nil {
			return nil
		}
		replacement = &config.Device{Addr: bond.Addr, Name: bond.Name}
	}
	return replacement
}

// headphonesName returns the selected headphones name.
func (a *App) headphonesName() string {
	a.mu.Lock()
	h := a.s.Headphones
	a.mu.Unlock()
	if h == nil {
		return "Bluetooth Headphones"
	}
	if h.Name != "" {
		return h.Name
	}
	if store, err := keys.Open(); err == nil {
		if c, ok := store.FindClassic(h.Addr); ok && c.Name != "" {
			return c.Name
		}
	}
	return "Bluetooth Headphones"
}
