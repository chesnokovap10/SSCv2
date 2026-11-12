// Package app runs the SSCv2 tray and coordinates Windows playback.
package app

import (
	"os"
	"sync"
	"time"

	"golang.org/x/sys/windows"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/i18n"
	"sscv2/internal/ipc"
	"sscv2/internal/logx"
	"sscv2/internal/tray"
)

// T is the text in the chosen language.
var T = i18n.T

// App is the tray application state.
type App struct {
	t *tray.Tray

	opMu sync.Mutex // one mode switch / privileged op at a time

	mu           sync.Mutex
	s            *config.Settings
	mode         config.Mode // effective mode
	busy         string
	pendingUHQ   bool
	eng          *workerProcess
	native       *nativeProcess
	resumeEngine *workerProcess // old process being replaced after system sleep
	st           ipc.EngineStatus
	scan         []ipc.Found
	scanning     bool
	adapter      driver.Status
	crashes      []time.Time
	quitting     bool
	// restoreMode: how the headphones' level is restored after "Off"
	// (ctl "restore <mode>", for diagnostics; not persisted).
	restoreMode   string
	driverVariant string
	// volSettled: closed when the level carried to the headphones in
	// Windows was applied (exit waits for it)
	volSettled        chan struct{}
	stopVolumeRestore func() // guarded by opMu
	// carry: audio routing left by an engine stopped for a restart
	carry             *ipc.AudioCarry
	menuText          map[int]string
	menuDeviceIDs     map[menuDeviceKey]int
	menuDeviceTargets []menuDevice
}

func logf(f string, a ...any) { logx.Printf(f, a...) }

// Run starts the tray. Returns the process exit code.
func Run() int {
	logx.Open(config.LogDir(), "tray.log", "tray")
	s, err := config.Load()
	if err != nil {
		logf("settings: %v", err)
	}
	i18n.Set(s.Lang)
	if installOrUpdate() {
		return 0 // the installed copy runs now
	}
	name, _ := windows.UTF16PtrFromString(`Local\SSCv2Tray`)
	h, err := windows.CreateMutex(nil, true, name)
	if err == windows.ERROR_ALREADY_EXISTS {
		tray.Info("SSCv2", T("SSCv2 уже запущена - значок в области уведомлений.", "SSCv2 is already running - see the icon in the notification area."))
		return 0
	}
	defer windows.CloseHandle(h)
	logf("tray start, version %s, %s", ipc.Version, selfPath())

	a := &App{mode: config.ModeOff, s: s}
	if a.s.Debug {
		logx.SetDebug(true)
	}
	a.t = &tray.Tray{Menu: a.menu, Command: a.command, Resume: a.onResume, DismissBefore: func(id int) bool {
		switch id {
		case idExit, idInfo, idRepository, idTestSigning:
			return true
		default:
			return false
		}
	}, VolumeKey: a.volumeKey, Volume: a.sliderVolume, SetVolume: a.setSliderVolume, ToggleMute: func() { a.adjustVolume(idVolMute) }}
	go a.startup()
	go a.serveCtl()
	if err := a.t.Run(tray.Gray, "SSCv2"); err != nil {
		logf("tray: %v", err)
		return 1
	}
	return 0
}

func selfPath() string {
	p, _ := os.Executable()
	return p
}

func (a *App) startup() {
	if err := audio.InitCOM(); err != nil {
		logf("COM: %v", err)
	}
	if logx.Debug() {
		a.startMonitor()
	}
	a.initializePlayback()
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
