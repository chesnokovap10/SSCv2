package app

import (
	"fmt"
	"strings"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/i18n"
	"sscv2/internal/ipc"
	"sscv2/internal/logx"
)

func (a *App) setLang(lang string) {
	a.mu.Lock()
	a.s.Lang = lang
	_ = config.Save(a.s)
	eng := a.eng
	a.mu.Unlock()
	i18n.Set(lang)
	if eng != nil {
		eng.send(ipc.Command{Cmd: "lang", Lang: i18n.Lang()})
	}
	a.refresh()
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
		a.t.Balloon("SSCv2", T("Отладочный журнал включён: ", "Debug journal on: ")+config.LogDir()+`\`+logx.DebugLogName, 0)
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
