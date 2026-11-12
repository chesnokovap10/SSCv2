package app

import (
	"fmt"
	"os/exec"
	"strings"

	"sscv2/internal/bitrate"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/helper"
	"sscv2/internal/i18n"
	"sscv2/internal/install"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
	"sscv2/internal/logx"
	"sscv2/internal/tray"
)

const (
	idModeOff = 101 + iota
	idModeAAC
	idModeSSC
	idModeUHQ
	idImportWin
	idWinSettings
	idScan
	idNoMouse
	idInfo
	idSvcInstall
	idSvcRemove
	idOpenLogs
	idDebug
	idMaxMTU
	idLangRU
	idLangEN
	idUninstall
	idAllBitrates
	idExit
	idVolume
	idVolDown
	idVolUp
	idVolMute
	idAnimations
	idRepository
	idAutoStart
	idTestSigning

	idBitrateBase = 500 // + kbps (0 = auto)
	idDeviceBase  = 2000
)

func (a *App) menu() []tray.Item {
	_, s := a.state()
	store, _ := keys.Open()
	snap := store.Snapshot()
	installed, running := helper.ServiceState()
	autoStart, autoStartErr := install.AutoStart()
	testSigning, testSigningErr := driver.TestSigning()

	a.mu.Lock()
	defer a.mu.Unlock()
	busy := a.busy != "" || a.pendingUHQ
	mode := a.mode
	engineUp := a.eng != nil

	items := []tray.Item{
		{Text: "SSCv2 " + ipc.Version + " — " + s, ID: idRepository, LiveLabel: true},
		{Separator: true},
		{Text: T("Громкость наушников", "Headphone volume"), ID: idVolume, Slider: true},
	}
	// codec + bitrate
	codecs := []tray.Item{
		{Text: T("Выкл (Bluetooth Windows)", "Off (Windows Bluetooth)"), ID: idModeOff, Radio: true, Checked: mode == config.ModeOff, Disabled: busy},
		{Text: "AAC", ID: idModeAAC, Radio: true, Checked: mode == config.ModeAAC, Disabled: busy},
		{Text: T("SSC (24 бит / 48 кГц)", "SSC (24 bit / 48 kHz)"), ID: idModeSSC, Radio: true, Checked: mode == config.ModeSSC, Disabled: busy},
		{Text: T("SSC UHQ (96 кГц)", "SSC UHQ (96 kHz)"), ID: idModeUHQ, Radio: true, Checked: mode == config.ModeSSCUHQ, Disabled: busy || a.uhqUnavailable()},
	}
	items = append(items, tray.Item{Text: T("Кодек: ", "Codec: ") + modeName(mode), Sub: codecs, LiveLabel: true})
	if a.noBitrate(mode) {
		items = append(items, tray.Item{Text: T("Битрейт: — (", "Bitrate: - (") + a.unsupportedText(mode) + ")", LiveLabel: true})
	} else if mode.Streaming() {
		policy, model := a.bitratePolicy(mode, a.prefersNativeBitrates())
		choices := bitrate.Choices(mode)
		cur := policy.Selected(mode, a.s.Bitrate(mode))
		label := T("Битрейт: ", "Bitrate: ") + bitrateText(cur)
		autoRate := ""
		var activeRate int
		if p := a.native; p != nil && p.Mode == mode && p.ready {
			activeRate = p.BitrateKbps
		} else if a.st.Streaming && a.st.Codec == modeName(mode) {
			activeRate = a.st.BitrateKbps
		}
		if activeRate > 0 && cur == 0 {
			autoRate = fmt.Sprintf(T("%d кбит/с", "%d kbps"), activeRate)
			label += " (" + autoRate + ")"
		}
		var sub []tray.Item
		showLimit := false
		for _, b := range choices {
			if policy.WorkingMax > 0 && b > policy.WorkingMax && policy.Offered(mode, b) {
				showLimit = true
				break
			}
		}
		for _, b := range choices {
			if !policy.Offered(mode, b) {
				continue // needs Max MTU / above the working maximum
			}
			t := bitrateText(b)
			if b == 0 {
				hint := autoRate
				if hint == "" {
					hint = autoHint(mode, policy, model, showLimit)
				}
				t += " (" + hint + ")"
			} else if policy.Experimental(mode, b) {
				t += T(" - не проверен", " - not checked")
			}
			sub = append(sub, tray.Item{Text: t, ID: idBitrateBase + b, Radio: true, Checked: b == cur, Disabled: busy})
		}
		items = append(items, tray.Item{Text: label, Sub: sub, SubRevision: string(mode), LiveLabel: true})
	} else {
		items = append(items, tray.Item{Text: T("Битрейт: —", "Bitrate: -"), LiveLabel: true})
	}
	items = append(items, tray.Item{Separator: true})

	// pairing submenu
	pair := []tray.Item{
		{Text: T("Импорт сопряжённых в Windows", "Import devices paired in Windows"), ID: idImportWin, Disabled: busy},
		{Text: T("Параметры Bluetooth Windows…", "Windows Bluetooth settings…"), ID: idWinSettings, Disabled: mode != config.ModeOff},
		{Separator: true},
	}
	scanText := T("Искать рядом (когда кодек включён)", "Search nearby (codec on)")
	if a.scanning {
		scanText = T("Поиск…", "Searching…")
	}
	pair = append(pair, tray.Item{Text: scanText, ID: idScan, Disabled: !engineUp || a.scanning})
	for _, d := range a.scan {
		label := fmt.Sprintf("    %s (%s)", nz(d.Name, T("без имени", "no name")), d.Addr)
		if d.Audio {
			label += " ♪"
		}
		pair = append(pair, tray.Item{Text: label, ID: a.menuDeviceID(menuFound, d.Addr, d.Name)})
	}
	pair = append(pair, tray.Item{Separator: true}, tray.Item{Text: T("Наушники:", "Headphones:")})
	nh := 0
	for _, c := range snap.Classic {
		if c.IsPeripheral() {
			continue // mice and keyboards are listed below
		}
		sel := a.s.Headphones != nil && strings.EqualFold(a.s.Headphones.Addr, c.Addr)
		pair = append(pair, tray.Item{Text: "    " + nz(c.Name, c.Addr), ID: a.menuDeviceID(menuHeadphones, c.Addr, c.Name), Radio: true, Checked: sel})
		nh++
	}
	if nh == 0 {
		pair = append(pair, tray.Item{Text: T("    (нет ключей — сделайте импорт)", "    (no keys - import them)")})
	}
	pair = append(pair, tray.Item{Text: T("Мышь:", "Mouse:")})
	pair = append(pair, tray.Item{Text: T("    Без мыши", "    No mouse"), ID: idNoMouse, Radio: true, Checked: a.s.Mouse == nil})
	for _, l := range snap.LE {
		sel := a.s.Mouse != nil && strings.EqualFold(a.s.Mouse.Addr, l.Addr)
		pair = append(pair, tray.Item{Text: "    " + nz(l.Name, l.Addr), ID: a.menuDeviceID(menuLEMouse, l.Addr, l.Name), Radio: true, Checked: sel})
	}
	for _, c := range snap.Classic {
		if !c.IsPointing() {
			continue
		}
		sel := a.s.Mouse != nil && strings.EqualFold(a.s.Mouse.Addr, c.Addr)
		pair = append(pair, tray.Item{Text: "    " + nz(c.Name, c.Addr) + T(" (классическая)", " (classic)"),
			ID: a.menuDeviceID(menuClassicMouse, c.Addr, c.Name), Radio: true, Checked: sel})
	}
	items = append(items, tray.Item{Text: T("Сопрячь устройство", "Pair a device"), Sub: pair, LiveLabel: true})
	items = append(items, tray.Item{Text: T("Инфо об устройствах…", "Device info…"), ID: idInfo, LiveLabel: true})
	items = append(items, tray.Item{Separator: true})

	// settings submenu
	svcState := T("не установлена", "not installed")
	if installed {
		svcState = T("остановлена", "stopped")
		if running {
			svcState = T("работает", "running")
		}
	}
	lang := i18n.Lang()
	testSigningState := T("неизвестно", "unknown")
	if testSigningErr == nil {
		testSigningState = T("выключена", "off")
		if testSigning {
			testSigningState = T("включена", "on")
		}
		if testSigning != a.s.WindowsTestSigning {
			testSigningState += T(" (отличается от выбора)", " (differs from selection)")
		}
	}
	settings := []tray.Item{
		{LiveLabel: true, MinWidth: 370, Text: T("Язык", "Language"), Sub: []tray.Item{
			{Text: "Русский", ID: idLangRU, LiveLabel: true, Checked: lang == i18n.RU},
			{Text: "English", ID: idLangEN, LiveLabel: true, Checked: lang == i18n.EN},
		}},
		{LiveLabel: true, MinWidth: 370, Text: T("Запускать при входе в Windows", "Start at Windows sign-in"), ID: idAutoStart, Checked: autoStart, Disabled: autoStartErr != nil},
		{LiveLabel: true, MinWidth: 370, Text: T("Анимации", "Animations"), ID: idAnimations, Checked: !a.s.DisableAnimations},
		{Separator: true},
		{LiveLabel: true, MinWidth: 370, Text: T("Макс. MTU для Samsung Galaxy Buds2 Pro (1017 байт)", "Max MTU for Samsung Galaxy Buds2 Pro (1017 bytes)"), ID: idMaxMTU, Checked: a.s.MaxMTU, Disabled: busy},
		{LiveLabel: true, MinWidth: 370, Text: T("Показывать все битрейты", "Show all bitrates"), ID: idAllBitrates, Checked: a.s.AllBitrates, Disabled: busy},
		{Separator: true},
		{LiveLabel: true, MinWidth: 370, Text: T("Тестовый режим Windows…", "Windows test mode…"), ID: idTestSigning, Checked: a.s.WindowsTestSigning, Disabled: busy},
		{LiveLabel: true, MinWidth: 370, Text: T("Текущая тестовая подпись Windows: ", "Current Windows test signing: ") + testSigningState, Disabled: true},
		{Separator: true},
		{LiveLabel: true, MinWidth: 370, Text: T("Отладка и API интерфейса", "Debug and UI API"), ID: idDebug, Checked: a.s.Debug},
		{LiveLabel: true, MinWidth: 370, Text: T("Открыть папку журналов", "Open the log folder"), ID: idOpenLogs},
		{Separator: true},
		{LiveLabel: true, MinWidth: 370, Text: T("Служба: ", "Service: ") + svcState},
		{LiveLabel: true, MinWidth: 370, Text: T("Запустить службу", "Start the service"), ID: idSvcInstall, Disabled: busy || running},
		{LiveLabel: true, MinWidth: 370, Text: T("Удалить службу", "Remove the service"), ID: idSvcRemove, Disabled: busy || !installed},
		{Separator: true},
		{LiveLabel: true, MinWidth: 370, Text: T("Удалить программу…", "Uninstall…"), ID: idUninstall, Disabled: busy},
	}
	items = append(items, tray.Item{Text: T("Настройки", "Settings"), LiveLabel: true, Sub: settings})
	items = append(items, tray.Item{Text: T("Выход", "Exit"), ID: idExit, LiveLabel: true})

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

func (a *App) command(id int) {
	a.mu.Lock()
	label := a.menuText[id]
	a.mu.Unlock()
	logx.Dbgf("ui", "menu: %q (id %d)", strings.TrimSpace(label), id)
	switch {
	case id == idRepository:
		openTarget("https://github.com/chesnokovap10/SSCv2")
	case id == idVolMute:
		a.adjustVolume(id)
	case id == idModeOff:
		go a.switchMode(config.ModeOff)
	case id == idModeAAC:
		go a.switchMode(config.ModeAAC)
	case id == idModeSSC:
		go a.switchMode(config.ModeSSC)
	case id == idModeUHQ:
		go a.switchMode(config.ModeSSCUHQ)
	case id >= idBitrateBase && id < idDeviceBase:
		go a.setBitrate(id - idBitrateBase)
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
			a.t.Balloon(T("Поиск устройств", "Searching for devices"), T("10 секунд… Переведите наушники в режим сопряжения.",
				"10 seconds… Put the headphones into pairing mode."), 0)
		}
	case id == idNoMouse || id >= idDeviceBase:
		a.selectMenuDevice(id)
	case id == idInfo:
		go a.showInfo()
	case id == idSvcInstall:
		go a.installService()
	case id == idSvcRemove:
		go a.removeService()
	case id == idOpenLogs:
		openTarget(config.LogDir())
	case id == idTestSigning:
		go a.toggleTestSigning()
	case id == idAutoStart:
		on, err := install.AutoStart()
		if err == nil {
			err = install.SetAutoStart(!on)
		}
		if err != nil {
			logf("autostart: %v", err)
			a.t.Balloon("SSCv2", T("Не удалось изменить автозапуск", "Could not change startup setting"), 2)
		}
		a.t.RefreshMenu()
	case id == idMaxMTU:
		a.mu.Lock()
		on := !a.s.MaxMTU
		a.mu.Unlock()
		go a.setMaxMTU(on)
	case id == idLangRU:
		a.setLang(i18n.RU)
	case id == idLangEN:
		a.setLang(i18n.EN)
	case id == idDebug:
		a.mu.Lock()
		on := !a.s.Debug
		a.mu.Unlock()
		go a.setDebug(on)
	case id == idAllBitrates:
		a.mu.Lock()
		on := !a.s.AllBitrates
		a.mu.Unlock()
		go a.setAllBitrates(on)
	case id == idAnimations:
		a.mu.Lock()
		a.s.DisableAnimations = !a.s.DisableAnimations
		_ = config.Save(a.s)
		if a.s.DisableAnimations {
			a.t.StopVolumePulse()
		}
		a.mu.Unlock()
		a.t.RefreshMenu()
	case id == idUninstall:
		go a.uninstall(false)
	case id == idExit:
		go a.exit(false)
	}
}
