package app

import (
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

type nativeProcess struct {
	*workerProcess
	ipc.NativeStream
	started      chan struct{}
	ready        bool
	linkLost     bool
	uhqSupported *bool
	lastMessage  string
}

func (a *App) startNativeWorker(mode config.Mode, path, endpoint, address, stereo string) error {
	a.mu.Lock()
	stream := a.nativeStreamLocked(mode)
	a.mu.Unlock()
	worker, err := startWorkerProcess("native-worker", "native-stderr.log", ipc.NativeConfig{
		Path: path, RenderEndpoint: endpoint, Device: address, StereoEndpoint: stereo, Stream: stream,
	})
	if err != nil {
		return err
	}

	p := &nativeProcess{workerProcess: worker, NativeStream: stream, started: make(chan struct{})}
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
	// Wait for the previous command's acknowledgment before replacing it.
	select {
	case <-p.done:
		return false, nil
	case <-p.started:
	}
	if !p.running() {
		return false, nil
	}
	started := make(chan struct{})
	a.mu.Lock()
	stream := a.nativeStreamLocked(mode)
	if p.NativeStream == stream {
		a.mu.Unlock()
		return false, nil
	}
	p.NativeStream, p.ready, p.started = stream, false, started
	a.mu.Unlock()
	if err := p.in.Write(ipc.Command{Cmd: ipc.CommandCodec, Native: &stream}); err != nil {
		return false, err
	}
	logf("native worker: switching to %s at %d kbps on PID %d", mode, stream.BitrateKbps, p.process.Pid)
	go a.watchNativeStartup(p, started)
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
	if a.native != p {
		a.mu.Unlock()
		return
	}
	stream := p.NativeStream
	switch event.Ev {
	case ipc.EventNativeCaps:
		if event.Status != nil {
			p.uhqSupported = event.Status.SSCUHQSupported
		}
		a.mu.Unlock()
		a.refresh()
	case ipc.EventNativeReady:
		if p.ready || event.Native == nil || *event.Native != stream {
			a.mu.Unlock()
			return
		}
		p.ready = true
		close(p.started)
		a.mu.Unlock()
		logf("native %s: ready", stream.Mode)
		logf("native %s: streaming at %d kbps", stream.Mode, stream.BitrateKbps)
		a.refresh()
	case ipc.EventNativeLinkLost:
		p.linkLost = true
		a.mu.Unlock()
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
