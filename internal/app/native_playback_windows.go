package app

import (
	"errors"
	"strings"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/buds"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
	"sscv2/internal/profiles"
)

type nativeProcess struct {
	*workerProcess
	ipc.NativeStream
	started          chan struct{}
	sourcePCM        bool
	ready            bool
	activeKbps       int
	volume           ipc.NativeVolume
	volumePending    *ipc.NativeVolume
	volumeWriting    bool
	linkLost         bool
	uhqSupported     *bool
	lastMessage      string
	budsBattery      *buds.Level
	budsBatteryAt    time.Time
	budsEqualizer    *uint8
	budsNoiseControl *buds.NoiseControl
	deviceAddress    string
}

func (a *App) startNativeWorker(mode config.Mode, path, endpoint, address, stereo string) error {
	a.mu.Lock()
	if a.noBitrate(mode) {
		err := errors.New(a.unsupportedText(mode))
		a.mu.Unlock()
		return err
	}
	stream := a.nativeStreamLocked(mode)
	protocol := buds.SPPNew
	commands := a.profileCommands(a.s.Headphones)
	if h := a.s.Headphones; h != nil {
		protocol = buds.ProtocolForName(h.Name)
	}
	a.mu.Unlock()
	worker, err := startWorkerProcess("native-worker", "native-stderr.log", ipc.NativeConfig{
		Path: path, RenderEndpoint: endpoint, Device: address, StereoEndpoint: stereo, Stream: stream,
		BudsProtocol: protocol, BudsCommands: commands,
	})
	if err != nil {
		return err
	}

	p := &nativeProcess{workerProcess: worker, NativeStream: stream, started: make(chan struct{}), deviceAddress: address}
	a.mu.Lock()
	a.native = p
	a.st.StreamStartFailed = false
	a.mu.Unlock()
	logf("native worker: started PID %d", p.process.Pid)
	p.watch(func(event ipc.Event) { a.onNativeEvent(p, event) }, func(err error) { a.nativeWorkerExited(p, err, p.lastMessage) })
	go a.watchNativeStartup(p, p.started)
	return nil
}

// requestNativeCodec runs with opMu held, so it cannot race a stop or another command.
func (a *App) requestNativeCodec(p *nativeProcess, mode config.Mode) (bool, error) {
	if !p.running() {
		return false, nil
	}
	started := make(chan struct{})
	a.mu.Lock()
	if a.noBitrate(mode) {
		message := a.unsupportedText(mode)
		a.mu.Unlock()
		a.t.Balloon("SSCv2", message, 1)
		return false, nil
	}
	if mode == config.ModeSSCUHQ && a.uhqUnavailable() {
		a.mu.Unlock()
		a.t.Balloon("SSCv2", T("Наушники не поддерживают SSC UHQ", "SSC UHQ is unavailable on these headphones"), 1)
		return false, nil
	}
	if a.resumeNative == p {
		// Recovery reads the selected mode after it acquires opMu.
		a.mu.Unlock()
		return true, nil
	}
	stream := a.nativeStreamLocked(mode)
	stream.Generation = p.Generation
	if p.NativeStream == stream {
		a.mu.Unlock()
		return false, nil
	}
	stream.Generation++
	// Retire the superseded watchdog.
	if !p.ready {
		close(p.started)
	}
	p.sourcePCM = false
	p.NativeStream, p.ready, p.started = stream, false, started
	a.mu.Unlock()
	go a.watchNativeStartup(p, started)
	if err := p.in.Write(ipc.Command{Cmd: ipc.CommandCodec, Native: &stream}); err != nil {
		return false, err
	}
	logf("native worker: switching to %s at %d kbps on PID %d", mode, stream.BitrateKbps, p.process.Pid)
	return true, nil
}

func (a *App) watchNativeStartup(p *nativeProcess, started <-chan struct{}) {
	timer := time.NewTimer(15 * time.Second)
	defer timer.Stop()
	select {
	case <-started:
	case <-p.done:
	case <-timer.C:
		a.mu.Lock()
		if a.native == p && p.started == started && !p.ready {
			_ = p.process.Kill()
		}
		a.mu.Unlock()
	}
}

func (a *App) onNativeEvent(p *nativeProcess, event ipc.Event) {
	a.mu.Lock()
	if a.native != p || a.resumeNative == p {
		a.mu.Unlock()
		return
	}
	stream := p.NativeStream
	headphones := a.s.Headphones
	if headphones != nil && !strings.EqualFold(headphones.Addr, p.deviceAddress) {
		headphones = nil
	}
	switch event.Ev {
	case ipc.EventNativeCaps:
		if event.Status != nil {
			p.uhqSupported = event.Status.SSCUHQSupported
		}
		a.mu.Unlock()
		if event.Status != nil {
			a.recordBitrateProfile(headphones, true, event.Status.Capabilities, config.ModeOff, profiles.StreamInfo{})
		}
		a.refresh()
	case ipc.EventNativePCM:
		if event.Native == nil || *event.Native != stream {
			a.mu.Unlock()
			return
		}
		p.sourcePCM = true
		a.mu.Unlock()
		logf("native %s: first media write after source PCM", stream.Mode)
		a.refresh()
	case ipc.EventNativeReady:
		if p.ready || event.Native == nil || *event.Native != stream {
			a.mu.Unlock()
			return
		}
		p.ready = true
		p.activeKbps = event.BitrateKbps
		if p.activeKbps == 0 {
			p.activeKbps = stream.BitrateKbps
		}
		kbps := p.activeKbps
		close(p.started)
		a.mu.Unlock()
		a.recordBitrateProfile(headphones, true, nil, stream.Mode, profiles.StreamInfo{Kbps: kbps})
		logf("native %s: ready", stream.Mode)
		logf("native %s: streaming at %d kbps", stream.Mode, kbps)
		a.refresh()
	case ipc.EventNativeVolume:
		if event.NativeVolume != nil {
			p.volume = *event.NativeVolume
		}
		a.mu.Unlock()
	case ipc.EventNativeBattery:
		disconnected := event.Battery == nil && event.Equalizer == nil && event.NoiseControl == nil
		if event.Battery != nil || disconnected {
			p.budsBattery, p.budsBatteryAt = event.Battery, time.Now()
		}
		if event.Equalizer != nil || disconnected {
			p.budsEqualizer = event.Equalizer
		}
		if event.NoiseControl != nil || disconnected {
			p.budsNoiseControl = event.NoiseControl
		}
		a.reconcileEqualizerLocked()
		a.reconcileNoiseControlLocked()
		a.mu.Unlock()
		a.refresh()
	case ipc.EventNativeLinkLost:
		p.linkLost = true
		a.reconcileEqualizerLocked()
		a.reconcileNoiseControlLocked()
		a.mu.Unlock()
		a.t.RefreshMenu()
	case ipc.EventNativeLog, ipc.EventNativeError:
		p.lastMessage = event.Msg
		a.mu.Unlock()
		logf("native %s: %s", stream.Mode, event.Msg)
	default:
		a.mu.Unlock()
	}
}

func (a *App) stopNativeWorker() {
	a.mu.Lock()
	p := a.native
	a.native = nil
	a.nativeWaiting = nil
	a.mu.Unlock()
	if p != nil {
		p.stop(3*time.Second, false)
	}
}

func (a *App) waitForNativeHeadphones(p *nativeProcess) {
	ticker := time.NewTicker(500 * time.Millisecond)
	defer ticker.Stop()
	for {
		a.mu.Lock()
		waiting := a.nativeWaiting == p && !a.quitting
		var name string
		if a.s.Headphones != nil {
			name = a.s.Headphones.Name
		}
		a.mu.Unlock()
		if !waiting {
			return
		}
		if budsStereoOutput(audio.List(false, audio.StateActive), "", name) != "" {
			a.opMu.Lock()
			a.mu.Lock()
			waiting = a.nativeWaiting == p && !a.quitting && a.s.Headphones != nil && a.s.Headphones.Name == name
			mode := a.mode
			a.mu.Unlock()
			if waiting {
				logf("native %s: headphones returned, restoring selected mode", mode)
				a.switchModeLocked(mode)
			}
			a.opMu.Unlock()
			if waiting {
				return
			}
		}
		<-ticker.C
	}
}
