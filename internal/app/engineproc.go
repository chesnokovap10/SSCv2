package app

import (
	"os"
	"os/exec"
	"path/filepath"
	"sync/atomic"
	"syscall"
	"time"

	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

// engineProc is a running "ssc.exe engine" child.
type engineProc struct {
	cmd     *exec.Cmd
	in      *ipc.Writer
	done    chan struct{}
	stopReq atomic.Bool
	started time.Time
}

func startEngine(cfg ipc.EngineConfig, onEvent func(*engineProc, ipc.Event), onExit func(*engineProc, error)) (*engineProc, error) {
	self, err := os.Executable()
	if err != nil {
		return nil, err
	}
	cmd := exec.Command(self, "engine")
	cmd.SysProcAttr = &syscall.SysProcAttr{HideWindow: true, CreationFlags: 0x08000000} // CREATE_NO_WINDOW
	stdin, err := cmd.StdinPipe()
	if err != nil {
		return nil, err
	}
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		return nil, err
	}
	// panics / C runtime messages
	if f, err := os.OpenFile(filepath.Join(config.LogDir(), "engine-stderr.log"),
		os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0o600); err == nil {
		cmd.Stderr = f
	}
	if err := cmd.Start(); err != nil {
		return nil, err
	}
	p := &engineProc{cmd: cmd, in: ipc.NewWriter(stdin), done: make(chan struct{}), started: time.Now()}
	_ = p.in.Write(cfg)
	go func() {
		r := ipc.NewReader(stdout)
		for {
			var ev ipc.Event
			if err := r.Read(&ev); err != nil {
				break
			}
			onEvent(p, ev)
		}
	}()
	go func() {
		err := cmd.Wait()
		if f, ok := cmd.Stderr.(*os.File); ok {
			f.Close()
		}
		close(p.done)
		onExit(p, err)
	}()
	return p, nil
}

func (p *engineProc) send(c ipc.Command) { _ = p.in.Write(c) }

// stop asks the engine to release everything; kills it after timeout.
func (p *engineProc) stop(timeout time.Duration) {
	p.stopReq.Store(true)
	p.send(ipc.Command{Cmd: "stop"})
	select {
	case <-p.done:
	case <-time.After(timeout):
		_ = p.cmd.Process.Kill()
		<-p.done
	}
}

func (p *engineProc) running() bool {
	select {
	case <-p.done:
		return false
	default:
		return true
	}
}
