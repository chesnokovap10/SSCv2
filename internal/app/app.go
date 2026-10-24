// Package app is the tray application: modes (Windows Bluetooth / AAC /
// SSC placeholder), the engine child process, pairing/key import, the
// helper service and the device info box.
package app

import (
	"errors"
	"fmt"
	"os/exec"
	"strings"
	"sync"
	"time"

	"golang.org/x/sys/windows"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/engine"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
	"sscv2/internal/logx"
	"sscv2/internal/tray"
)

const (
	idModeOff = 101 + iota
	idModeAAC
	idModeSSC
	idImportWin
	idWinSettings
	idScan
	idNoMouse
	idInfo
	idSvcInstall
	idSvcRemove
	idOpenLogs
	idDebug
	idAAC256
	idExit

	idFoundBase      = 1000
	idHeadphonesBase = 2000
	idMouseBase      = 3000
)

// App is the tray application state.
type App struct {
	t *tray.Tray

	opMu sync.Mutex // one mode switch / privileged op at a time

	mu       sync.Mutex
	s        *config.Settings
	mode     config.Mode // effective mode
	busy     string
	eng      *engineProc
	st       ipc.EngineStatus
	scan     []ipc.Found
	scanning bool
	adapter  driver.Status
	crashes  []time.Time
	quitting bool
	// restoreMode: how the headphones' level is restored after "Выкл"
	// (ctl "restore <mode>", for diagnostics; not persisted).
	restoreMode   string
	driverVariant string
	menuText      map[int]string
}

func logf(f string, a ...any) { logx.Printf(f, a...) }

// Run starts the tray. Returns the process exit code.
func Run() int {
	logx.Open(config.LogDir(), "tray.log", "tray")
	name, _ := windows.UTF16PtrFromString(`Local\SSCv2Tray`)
	h, err := windows.CreateMutex(nil, true, name)
	if err == windows.ERROR_ALREADY_EXISTS {
		tray.Info("SSCv2", "SSCv2 уже запущена - значок в области уведомлений.")
		return 0
	}
	defer windows.CloseHandle(h)
	logf("tray start, version %s", ipc.Version)

	a := &App{mode: config.ModeOff}
	a.s, err = config.Load()
	if err != nil {
		logf("settings: %v", err)
	}
	if a.s.Debug {
		logx.SetDebug(true)
	}
	a.t = &tray.Tray{Menu: a.menu, Command: a.command, Click: func() { go a.showInfo() }}
	go a.startup()
	go a.serveCtl()
	if err := a.t.Run(tray.Gray, "SSCv2"); err != nil {
		logf("tray: %v", err)
		return 1
	}
	return 0
}

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

func (a *App) startup() {
	if err := audio.InitCOM(); err != nil {
		logf("COM: %v", err)
	}
	if logx.Debug() {
		a.startMonitor()
	}
	st := a.refreshAdapter()
	_, svcRunning := helper.ServiceState()
	a.mu.Lock()
	want := a.s.Mode
	a.mu.Unlock()
	logf("adapter %s mode %s, saved mode %s, service running %v", st.ID, st.Mode, want, svcRunning)

	switch {
	case st.Mode == driver.NotPresent:
		a.t.Balloon("SSCv2", "Встроенный адаптер MediaTek не найден.", 1)
	case want != config.ModeOff && (st.Mode == driver.WinUSB || svcRunning):
		// resume: no UAC prompt needed (driver already switched or service)
		go a.enable(want)
	case want != config.ModeOff:
		a.setMode(config.ModeOff)
	case st.Mode == driver.WinUSB:
		a.t.Balloon("SSCv2", "Адаптер остался в режиме WinUSB. Выберите «Выкл», чтобы вернуть Bluetooth Windows.", 1)
	}
	a.refresh()

	for {
		time.Sleep(10 * time.Second)
		a.mu.Lock()
		idle := a.busy == ""
		a.mu.Unlock()
		if idle {
			a.refreshAdapter()
			a.refresh()
		}
	}
}

func (a *App) setMode(m config.Mode) {
	a.mu.Lock()
	a.mode = m
	a.s.Mode = m
	_ = config.Save(a.s)
	a.mu.Unlock()
}

func (a *App) setBusy(s string) {
	a.mu.Lock()
	changed := a.busy != s
	a.busy = s
	a.mu.Unlock()
	if changed {
		logx.Dbgf("mode", "busy: %q", s)
	}
	a.refresh()
}

// stateText / color for the icon and the menu header.
func (a *App) state() (tray.Color, string) {
	a.mu.Lock()
	defer a.mu.Unlock()
	if a.busy != "" {
		return tray.Amber, a.busy
	}
	if a.adapter.Mode == driver.NotPresent {
		return tray.Red, "адаптер не найден"
	}
	if a.mode == config.ModeOff {
		if a.adapter.Mode == driver.WinUSB {
			return tray.Blue, "выкл (адаптер в WinUSB)"
		}
		return tray.Gray, "выкл - Bluetooth Windows"
	}
	if a.eng == nil {
		return tray.Red, "движок не запущен"
	}
	st := a.st
	name := st.HeadphonesName
	if name == "" {
		name = st.Headphones
	}
	switch st.Phase {
	case "streaming":
		return tray.Green, fmt.Sprintf("%s → %s", st.Codec, name)
	case "error":
		return tray.Red, "ошибка: " + st.Message
	case "waiting", "idle":
		return tray.Blue, st.Message
	case "":
		return tray.Amber, "запуск"
	}
	if st.Message != "" {
		return tray.Amber, st.Message
	}
	return tray.Amber, st.Phase
}

func (a *App) refresh() {
	c, s := a.state()
	a.t.Set(c, "SSCv2: "+s)
}

// ---- modes ----------------------------------------------------------------

// enable switches the adapter to WinUSB (if needed) and starts the engine.
func (a *App) enable(m config.Mode) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	defer a.setBusy("")

	a.mu.Lock()
	cur, eng := a.mode, a.eng
	a.mu.Unlock()
	if cur == m && eng != nil && eng.running() {
		return
	}
	if eng != nil {
		a.setBusy("остановка потока")
		eng.stop(15 * time.Second)
	}

	st := a.refreshAdapter()
	if st.Mode == driver.NotPresent {
		a.t.Balloon("SSCv2", "Адаптер MediaTek не найден", 2)
		a.setMode(config.ModeOff)
		return
	}
	a.ensureVirtual() // before the switch: the headphones are still visible to Windows
	if st.Mode != driver.WinUSB {
		a.setBusy("переключение адаптера в WinUSB")
		_, err := helper.Call(ipc.Request{Op: "driver", VID: st.ID.VID, PID: st.ID.PID, WinUSB: true})
		if err != nil {
			logf("driver winusb: %v", err)
			a.t.Balloon("Не удалось включить режим потока", err.Error(), 2)
			a.refreshAdapter()
			a.setMode(config.ModeOff)
			return
		}
		for i := 0; i < 40 && driver.Detect(st.ID).Mode != driver.WinUSB; i++ {
			time.Sleep(250 * time.Millisecond)
		}
		time.Sleep(200 * time.Millisecond) // let the WinUSB interface settle
		a.refreshAdapter()
	}
	a.setMode(m)
	a.startEngineLocked()
}

// startEngineLocked starts the engine for the current mode (opMu held).
func (a *App) startEngineLocked() {
	a.mu.Lock()
	cfg := ipc.EngineConfig{
		Codec:        string(a.mode),
		VID:          a.adapter.ID.VID,
		PID:          a.adapter.ID.PID,
		MuteSpeakers: a.s.MuteSpeakersOrDefault(),
		Debug:        a.s.Debug,
		AACMode:      a.s.AACMode,
		SSCBitrate:   a.s.SSCBitrate,
		SSCCap:       a.s.SSCCap,
	}
	if a.s.Headphones != nil {
		cfg.Headphones = a.s.Headphones.Addr
	}
	if a.s.Mouse != nil {
		cfg.Mouse = a.s.Mouse.Addr
	}
	a.st = ipc.EngineStatus{Volume: -1}
	a.mu.Unlock()
	p, err := startEngine(cfg, a.onEngineEvent, a.onEngineExit)
	if err != nil {
		logf("start engine: %v", err)
		a.t.Balloon("SSCv2", "Не удалось запустить движок: "+err.Error(), 2)
		return
	}
	a.mu.Lock()
	a.eng = p
	a.mu.Unlock()
	logf("engine started (pid %d)", p.cmd.Process.Pid)
	a.refresh()
}

// disable stops the engine and gives the adapter back to Windows.
func (a *App) disable() {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	defer a.setBusy("")
	// One volume for both modes: the level used in AAC mode (virtual device)
	// goes to the real headphones in Windows mode.
	want := float32(-1)
	if r, ok := audio.VirtualRender(); ok {
		if l, err := audio.Level(r.ID); err == nil {
			want = l
		}
	}
	logf("mode off: carrying level %.1f%% to the headphones in Windows", want*100)
	a.mu.Lock()
	eng := a.eng
	a.eng = nil
	a.mode = config.ModeOff
	restore := a.restoreMode
	a.mu.Unlock()
	if eng != nil {
		a.setBusy("остановка потока")
		eng.stop(15 * time.Second)
	}
	a.setMode(config.ModeOff)
	st := a.refreshAdapter()
	if st.Mode == driver.WinUSB {
		a.setBusy("возврат адаптера Windows")
		// The headphones reconnect to Windows at their own level (Galaxy
		// Buds: 100 %) as soon as the radio is back - often before the
		// switch script has finished. Watch for them from now on, so the
		// jump is answered within ~50 ms.
		name := audio.HeadphonesName()
		a.mu.Lock()
		if name == "" && a.s.Headphones != nil {
			name = a.s.Headphones.Name
		}
		variant := a.driverVariant
		a.mu.Unlock()
		logx.Dbgf("mode", "returning the adapter to Windows; volume restore for %q (mode %q)", name, nz(restore, "default"))
		if restore != "off" {
			go func() {
				if !audio.RestoreHeadphonesVolume(name, want, 40*time.Second, logf) {
					logf("volume: headphones %q did not come to Windows", name)
				}
			}()
		}
		if _, err := helper.Call(ipc.Request{Op: "driver", VID: st.ID.VID, PID: st.ID.PID, WinUSB: false, Variant: variant}); err != nil {
			logf("driver bthusb: %v", err)
			a.t.Balloon("Не удалось вернуть Bluetooth Windows", err.Error(), 2)
			a.refreshAdapter()
			return
		}
		a.refreshAdapter()
	}
}

func endpointName(id string) string {
	if id == "" {
		return "(none)"
	}
	for _, e := range audio.List(false, audio.StateActive|audio.StateDisabled) {
		if e.ID == id {
			return e.Name
		}
	}
	return id
}

func (a *App) onEngineEvent(p *engineProc, ev ipc.Event) {
	if ev.Ev != "status" {
		logx.Dbgf("ipc", "engine -> tray: %s %s %s", ev.Ev, ev.Addr, ev.Msg)
	}
	switch ev.Ev {
	case "status":
		a.mu.Lock()
		if a.eng != p {
			a.mu.Unlock()
			return
		}
		prev := a.st
		a.st = *ev.Status
		a.mu.Unlock()
		if ev.Status.Phase == "streaming" && prev.Phase != "streaming" {
			a.t.Balloon("SSCv2", fmt.Sprintf("%s: %s, %d кбит/с", nz(ev.Status.HeadphonesName, ev.Status.Headphones),
				ev.Status.Codec, ev.Status.BitrateKbps), 0)
		}
		if ev.Status.Phase == "error" && prev.Phase != "error" {
			a.t.Balloon("SSCv2: ошибка", ev.Status.Message, 2)
		}
		if ev.Status.AdapterAddr != "" && prev.AdapterAddr == "" {
			if s, err := keys.Open(); err == nil && s.Snapshot().Adapter == "" {
				_ = s.Merge(keys.File{Adapter: ev.Status.AdapterAddr})
			}
		}
		a.refresh()
	case "scan":
		a.mu.Lock()
		a.scan, a.scanning = ev.Devices, false
		a.mu.Unlock()
		n := 0
		for _, d := range ev.Devices {
			if d.Audio {
				n++
			}
		}
		a.t.Balloon("Поиск завершён", fmt.Sprintf("Найдено устройств: %d (аудио: %d). Выберите в меню «Сопрячь устройство».", len(ev.Devices), n), 0)
	case "linkkey":
		go a.syncKeyToWindows(ev.Addr, ev.Key)
	case "log":
		a.t.Balloon("SSCv2", ev.Msg, 1)
	}
}

func (a *App) onEngineExit(p *engineProc, err error) {
	a.mu.Lock()
	last := a.st
	current := a.eng == p
	if current {
		a.eng = nil
	}
	mode, quitting := a.mode, a.quitting
	a.mu.Unlock()
	if p.stopReq.Load() {
		logf("engine stopped")
		return
	}
	logf("engine exited unexpectedly: %v (phase %s: %s)", err, last.Phase, last.Message)
	engine.RestoreAudio(last) // undo default-device / mute changes it made
	if !current || quitting || mode == config.ModeOff {
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
			msg = "движок несколько раз завершился с ошибкой"
		}
		a.t.Balloon("SSCv2 остановлен", msg+" — подробности в журнале.", 2)
		a.refresh()
		return
	}
	go func() {
		time.Sleep(3 * time.Second)
		a.opMu.Lock()
		defer a.opMu.Unlock()
		a.mu.Lock()
		still := a.mode == mode && a.eng == nil && !a.quitting
		a.mu.Unlock()
		if still {
			a.refreshAdapter()
			a.startEngineLocked()
		}
	}()
	a.refresh()
}

func nz(a, b string) string {
	if a != "" {
		return a
	}
	return b
}

// restartEngine applies new keys / mouse choice to a running engine.
func (a *App) restartEngine() {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	eng := a.eng
	a.mu.Unlock()
	if eng == nil {
		return
	}
	a.setBusy("перезапуск потока")
	eng.stop(15 * time.Second)
	a.mu.Lock()
	a.eng = nil
	a.mu.Unlock()
	a.startEngineLocked()
	a.setBusy("")
}

// ---- keys ------------------------------------------------------------------

func (a *App) syncKeyToWindows(addr, key string) {
	if _, running := helper.ServiceState(); !running {
		a.t.Balloon("Новый ключ сопряжения", "Установите службу, чтобы устройство "+addr+" осталось сопряжённым и в Bluetooth Windows.", 1)
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
	a.setBusy("импорт ключей Windows")
	defer a.setBusy("")
	resp, err := helper.Call(ipc.Request{Op: "keys-read"})
	if err != nil {
		a.t.Balloon("Импорт не удался", err.Error(), 2)
		return
	}
	var bonds []keys.AdapterBonds
	if err := jsonUnmarshal(resp.Data, &bonds); err != nil || len(bonds) == 0 {
		a.t.Balloon("Импорт", "Windows не хранит ключей Bluetooth.", 1)
		return
	}
	store, _ := keys.Open()
	known := map[string]bool{}
	a.mu.Lock()
	known[a.st.AdapterAddr] = true
	a.mu.Unlock()
	known[store.Snapshot().Adapter] = true
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
	if err := store.Merge(b.File); err != nil {
		a.t.Balloon("Импорт не удался", err.Error(), 2)
		return
	}
	a.afterImport(store, fmt.Sprintf("Адаптер %s: устройств %d, мышей %d.", b.Adapter, len(b.Classic), len(b.LE)))
}

// afterImport auto-selects headphones / mouse when none is chosen yet.
func (a *App) afterImport(store *keys.Store, msg string) {
	a.mu.Lock()
	if a.s.Headphones == nil {
		if c, ok := store.FindClassic(""); ok {
			a.s.Headphones = &config.Device{Addr: c.Addr, Name: c.Name}
			msg += " Наушники: " + nz(c.Name, c.Addr) + "."
		}
	}
	if a.s.Mouse == nil {
		if l, ok := store.FindLE(""); ok {
			a.s.Mouse = &config.Device{Addr: l.Addr, Name: l.Name}
			msg += " Мышь: " + nz(l.Name, l.Addr) + "."
		}
	}
	_ = config.Save(a.s)
	running := a.eng != nil
	a.mu.Unlock()
	a.t.Balloon("Ключи импортированы", msg, 0)
	if running {
		a.restartEngine()
	}
}

// ---- service / virtual device ----------------------------------------------

func (a *App) installService() {
	a.setBusy("установка службы")
	defer a.setBusy("")
	code, err := helper.RunElevated("service-install --owner " + helper.CurrentUserSID())
	if err == nil && code != 0 {
		err = fmt.Errorf("код %d, см. журнал helper.log", code)
	}
	if err != nil {
		a.t.Balloon("Служба не установлена", err.Error(), 2)
		return
	}
	a.t.Balloon("SSCv2", "Служба установлена и запущена: переключения больше не требуют подтверждения UAC.", 0)
}

func (a *App) removeService() {
	// Removing the service = cleaning up: give Bluetooth back to Windows and
	// remove the virtual headphones while the service can still do it.
	a.mu.Lock()
	mode := a.mode
	a.mu.Unlock()
	if mode != config.ModeOff {
		a.disable()
	}
	a.setBusy("удаление виртуальных наушников")
	a.removeVirtual()
	a.setBusy("удаление службы")
	defer a.setBusy("")
	code, err := helper.RunElevated("service-uninstall")
	if err == nil && code != 0 {
		err = fmt.Errorf("код %d", code)
	}
	if err != nil {
		a.t.Balloon("Служба не удалена", err.Error(), 2)
		return
	}
	a.t.Balloon("SSCv2", "Служба удалена.", 0)
}

// headphonesName is the name the virtual device should carry.
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

// ensureVirtual silently installs the embedded virtual headphones device
// (or renames it after the current headphones). Failure is not fatal: the
// engine then captures the speakers via loopback.
// Call it while the adapter is still in Windows mode: the virtual device
// takes the level Windows keeps for the real headphones (one volume for both
// modes; a fresh device would otherwise start at Windows' 100 %).
func (a *App) ensureVirtual() {
	name := a.headphonesName()
	fresh := !audio.VirtualInstalled()
	level, known := audio.HeadphonesLevel(name)
	if known && level >= 0.99 {
		known = false // most likely the Buds' own jump, not a chosen level
	}
	if fresh || audio.HeadphonesName() != name {
		a.setBusy("подготовка виртуальных наушников")
		resp, err := helper.Call(ipc.Request{Op: "virtual-install", Name: name})
		if err != nil {
			logf("virtual-install: %v", err)
			a.t.Balloon("Виртуальные наушники", "Не удалось установить: "+err.Error()+". Звук пойдёт с динамиков.", 1)
			return
		}
		logf("virtual-install: %s", resp.Message)
	}
	if !known && !fresh {
		return // keep the virtual device's own level
	}
	if !known {
		level = audio.FallbackLevel
	}
	_ = audio.SetVirtualVisible(true)
	if r, ok := audio.VirtualRender(); ok {
		err := audio.SetLevel(r.ID, level)
		logf("volume: virtual device set to %.0f%% (from headphones in Windows: %v): %v", level*100, known, err)
	}
	_ = audio.SetVirtualVisible(false)
}

func (a *App) removeVirtual() {
	if !audio.VirtualInstalled() {
		return
	}
	if resp, err := helper.Call(ipc.Request{Op: "virtual-uninstall"}); err != nil {
		logf("virtual-uninstall: %v", err)
	} else {
		logf("virtual-uninstall: %s", resp.Message)
	}
}

// ---- menu --------------------------------------------------------------------

func (a *App) menu() []tray.Item {
	_, s := a.state()
	store, _ := keys.Open()
	snap := store.Snapshot()
	installed, running := helper.ServiceState()

	a.mu.Lock()
	defer a.mu.Unlock()
	busy := a.busy != ""
	mode := a.mode
	engineUp := a.eng != nil

	items := []tray.Item{
		{Text: "SSCv2 — " + s},
		{Separator: true},
		{Text: "Выкл (Bluetooth Windows)", ID: idModeOff, Radio: true, Checked: mode == config.ModeOff, Disabled: busy},
		{Text: "Режим AAC", ID: idModeAAC, Radio: true, Checked: mode == config.ModeAAC, Disabled: busy},
		{Text: "Режим SSC", ID: idModeSSC, Radio: true, Checked: mode == config.ModeSSC, Disabled: busy},
		{Text: "AAC 256 кбит/с (выше лимита наушников)", ID: idAAC256, Checked: a.s.AACMode == "over", Disabled: busy},
		{Separator: true},
	}

	// pairing submenu
	pair := []tray.Item{
		{Text: "Импорт сопряжённых в Windows", ID: idImportWin, Disabled: busy},
		{Text: "Параметры Bluetooth Windows…", ID: idWinSettings, Disabled: mode != config.ModeOff},
		{Separator: true},
	}
	scanText := "Искать рядом (в режиме AAC)"
	if a.scanning {
		scanText = "Поиск…"
	}
	pair = append(pair, tray.Item{Text: scanText, ID: idScan, Disabled: !engineUp || a.scanning})
	for i, d := range a.scan {
		label := fmt.Sprintf("    %s (%s)", nz(d.Name, "без имени"), d.Addr)
		if d.Audio {
			label += " ♪"
		}
		pair = append(pair, tray.Item{Text: label, ID: idFoundBase + i})
	}
	pair = append(pair, tray.Item{Separator: true}, tray.Item{Text: "Наушники:"})
	nh := 0
	for i, c := range snap.Classic {
		sel := a.s.Headphones != nil && strings.EqualFold(a.s.Headphones.Addr, c.Addr)
		pair = append(pair, tray.Item{Text: "    " + nz(c.Name, c.Addr), ID: idHeadphonesBase + i, Radio: true, Checked: sel})
		nh++
	}
	if nh == 0 {
		pair = append(pair, tray.Item{Text: "    (нет ключей — сделайте импорт)"})
	}
	pair = append(pair, tray.Item{Text: "Мышь:"})
	pair = append(pair, tray.Item{Text: "    Без мыши", ID: idNoMouse, Radio: true, Checked: a.s.Mouse == nil})
	for i, l := range snap.LE {
		sel := a.s.Mouse != nil && strings.EqualFold(a.s.Mouse.Addr, l.Addr)
		pair = append(pair, tray.Item{Text: "    " + nz(l.Name, l.Addr), ID: idMouseBase + i, Radio: true, Checked: sel})
	}
	items = append(items, tray.Item{Text: "Сопрячь устройство", Sub: pair})
	items = append(items, tray.Item{Text: "Инфо об устройствах…", ID: idInfo})
	items = append(items, tray.Item{Separator: true})

	svcState := "не установлена"
	if installed {
		svcState = "остановлена"
		if running {
			svcState = "работает"
		}
	}
	items = append(items,
		tray.Item{Text: "Служба: " + svcState},
		tray.Item{Text: "Запустить службу", ID: idSvcInstall, Disabled: busy || running},
		tray.Item{Text: "Удалить службу", ID: idSvcRemove, Disabled: busy || !installed},
		tray.Item{Separator: true},
	)
	items = append(items, tray.Item{Text: "Открыть папку журналов", ID: idOpenLogs})
	items = append(items, tray.Item{Text: "Отладочный журнал (debug.log)", ID: idDebug, Checked: a.s.Debug})
	items = append(items, tray.Item{Text: "Выход", ID: idExit})
	a.menuText = map[int]string{}
	var walk func([]tray.Item)
	walk = func(l []tray.Item) {
		for _, it := range l {
			if it.ID != 0 {
				a.menuText[it.ID] = it.Text
			}
			walk(it.Sub)
		}
	}
	walk(items)
	return items
}

// setDebug turns the debug journal on/off for the tray, the running engine
// and (through the request flag) the helper service.
func (a *App) setDebug(on bool) {
	a.mu.Lock()
	a.s.Debug = on
	_ = config.Save(a.s)
	eng := a.eng
	a.mu.Unlock()
	logx.SetDebug(on)
	if on {
		a.startMonitor()
		a.mu.Lock()
		st, mode := a.st, a.mode
		a.mu.Unlock()
		logx.Dbgf("mode", "mode %s, engine phase %q, adapter %s %s, version %s", mode, st.Phase, a.adapterID(), a.refreshAdapter().Mode, ipc.Version)
	} else {
		audio.StopMonitor()
	}
	if eng != nil {
		eng.send(ipc.Command{Cmd: "debug", On: on})
	}
	if on {
		a.t.Balloon("SSCv2", "Отладочный журнал включён: "+config.LogDir()+`\`+logx.DebugLogName, 0)
	}
}

func (a *App) startMonitor() {
	if err := audio.StartMonitor(func(f string, args ...any) {
		cat, rest, ok := strings.Cut(fmt.Sprintf(f, args...), ": ")
		if !ok {
			cat, rest = "audio", cat
		}
		logx.Dbgf(cat, "%s", rest)
	}); err != nil {
		logf("audio monitor: %v", err)
	}
}

func (a *App) command(id int) {
	a.mu.Lock()
	label := a.menuText[id]
	a.mu.Unlock()
	logx.Dbgf("ui", "menu: %q (id %d)", strings.TrimSpace(label), id)
	switch {
	case id == idModeOff:
		go a.disable()
	case id == idModeAAC:
		go a.enable(config.ModeAAC)
	case id == idModeSSC:
		go a.enable(config.ModeSSC)
	case id == idImportWin:
		go a.importWindows()
	case id == idWinSettings:
		_ = exec.Command("explorer.exe", "ms-settings:bluetooth").Start()
	case id == idScan:
		a.mu.Lock()
		eng := a.eng
		if eng != nil {
			a.scanning, a.scan = true, nil
		}
		a.mu.Unlock()
		if eng != nil {
			eng.send(ipc.Command{Cmd: "scan"})
			a.t.Balloon("Поиск устройств", "10 секунд… Переведите наушники в режим сопряжения.", 0)
		}
	case id >= idFoundBase && id < idFoundBase+500:
		a.mu.Lock()
		i := id - idFoundBase
		if i >= len(a.scan) {
			a.mu.Unlock()
			return
		}
		d := a.scan[i]
		a.s.Headphones = &config.Device{Addr: d.Addr, Name: d.Name}
		_ = config.Save(a.s)
		eng := a.eng
		a.mu.Unlock()
		if eng != nil {
			eng.send(ipc.Command{Cmd: "connect", Addr: d.Addr})
		}
	case id >= idHeadphonesBase && id < idHeadphonesBase+500:
		store, _ := keys.Open()
		snap := store.Snapshot()
		i := id - idHeadphonesBase
		if i >= len(snap.Classic) {
			return
		}
		c := snap.Classic[i]
		a.mu.Lock()
		a.s.Headphones = &config.Device{Addr: c.Addr, Name: c.Name}
		_ = config.Save(a.s)
		eng := a.eng
		a.mu.Unlock()
		if eng != nil {
			eng.send(ipc.Command{Cmd: "connect", Addr: c.Addr})
		}
	case id == idNoMouse || (id >= idMouseBase && id < idMouseBase+500):
		var dev *config.Device
		if id != idNoMouse {
			store, _ := keys.Open()
			snap := store.Snapshot()
			i := id - idMouseBase
			if i >= len(snap.LE) {
				return
			}
			dev = &config.Device{Addr: snap.LE[i].Addr, Name: snap.LE[i].Name}
		}
		a.mu.Lock()
		a.s.Mouse = dev
		_ = config.Save(a.s)
		a.mu.Unlock()
		go a.restartEngine()
	case id == idInfo:
		go a.showInfo()
	case id == idSvcInstall:
		go a.installService()
	case id == idSvcRemove:
		go a.removeService()
	case id == idOpenLogs:
		openFolder(config.LogDir())
	case id == idAAC256:
		a.mu.Lock()
		if a.s.AACMode == "over" {
			a.s.AACMode = ""
		} else {
			a.s.AACMode = "over"
		}
		_ = config.Save(a.s)
		a.mu.Unlock()
		go a.restartEngine()
	case id == idDebug:
		a.mu.Lock()
		on := !a.s.Debug
		a.mu.Unlock()
		go a.setDebug(on)
	case id == idExit:
		go a.exit()
	}
}

func (a *App) exit() {
	a.mu.Lock()
	a.quitting = true
	mode := a.mode
	a.mu.Unlock()
	if mode != config.ModeOff {
		a.disable()
	}
	logf("tray exit")
	a.t.Quit()
}

// ---- info --------------------------------------------------------------------

func (a *App) showInfo() { tray.Info("SSCv2 — устройства", a.infoText()) }

func (a *App) infoText() string {
	st := a.refreshAdapter()
	installed, running := helper.ServiceState()
	store, _ := keys.Open()
	snap := store.Snapshot()
	a.mu.Lock()
	es, mode, s := a.st, a.mode, *a.s
	engineUp := a.eng != nil
	a.mu.Unlock()

	var b strings.Builder
	w := func(f string, args ...any) { fmt.Fprintf(&b, f+"\n", args...) }

	w("Режим: %s", map[config.Mode]string{config.ModeOff: "выкл (Bluetooth Windows)", config.ModeAAC: "AAC", config.ModeSSC: "SSC"}[mode])
	w("")
	if st.Mode == driver.NotPresent {
		w("Адаптер: MediaTek MT79xx не найден")
	} else {
		w("Адаптер: %s (%s)", nz(st.Name, "MediaTek"), st.ID)
		w("    драйвер: %s [%s]", st.Mode, st.Service)
		if engineUp && es.Chip != "" {
			w("    чип: %s, прошивка %s", es.Chip, es.Firmware)
		}
		addr := es.AdapterAddr
		if addr == "" {
			addr, _ = windowsRadio()
		}
		if addr == "" {
			addr = snap.Adapter
		}
		if addr != "" {
			w("    адрес: %s", addr)
		}
	}
	w("")
	if s.Headphones == nil {
		w("Наушники: не выбраны")
	} else {
		w("Наушники: %s (%s)", nz(s.Headphones.Name, "—"), s.Headphones.Addr)
		if engineUp {
			switch {
			case es.Streaming:
				w("    поток: %s, %d кбит/с, %d Гц", es.Codec, es.BitrateKbps, es.SampleRate)
			case es.Connected:
				w("    подключены, поток не идёт")
			default:
				w("    %s", nz(es.Message, es.Phase))
			}
			if es.AVRCP && es.Volume >= 0 {
				w("    громкость: %d%%", es.Volume*100/127)
			}
			if es.CaptureDevice != "" {
				w("    источник: %s [%s]", es.CaptureDevice, es.CaptureFormat)
			}
			if es.Fails > 0 || es.Queue > 8 {
				w("    очередь %d, потерь за 2 с: %d", es.Queue, es.Fails)
			}
		} else if mode == config.ModeOff {
			w("    работают через Bluetooth Windows")
		}
	}
	w("")
	if s.Mouse == nil {
		w("Мышь: не выбрана")
	} else {
		w("Мышь: %s (%s)", nz(s.Mouse.Name, "—"), s.Mouse.Addr)
		if engineUp && es.MouseState != "" {
			w("    мост: %s, отчётов: %d", es.MouseState, es.MouseReports)
		} else if mode == config.ModeOff {
			w("    работает через Bluetooth Windows")
		}
	}
	w("")
	svc := "не установлена"
	if installed {
		svc = "остановлена"
		if running {
			svc = "работает"
		}
	}
	w("Служба: %s", svc)
	w("Ключи: устройств %d, мышей %d", len(snap.Classic), len(snap.LE))
	if hn := audio.HeadphonesName(); hn != "" {
		w("Виртуальные наушники: %s", hn)
	} else if audio.VirtualInstalled() {
		w("Виртуальные наушники: установлены")
	}
	w("Журналы: %s", config.LogDir())
	return b.String()
}

var _ = errors.New
