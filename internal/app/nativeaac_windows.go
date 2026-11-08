package app

import (
	"bufio"
	"errors"
	"fmt"
	"io"
	"os/exec"
	"sync/atomic"
	"syscall"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
)

type nativeProcess struct {
	cmd   *exec.Cmd
	input io.WriteCloser
	done  chan struct{}
	ready atomic.Bool
}

// startNativeAAC runs with opMu held.
func (a *App) startNativeAAC() {
	a.setBusy(T("Запуск AAC через Bluetooth Windows", "Starting AAC through Windows Bluetooth"))
	if active, err := driver.TestSigning(); err != nil || !active {
		message := T("Для нативного AAC нужна загрузка Windows в тестовом режиме.", "Native AAC requires Windows to boot in test mode.")
		if err != nil {
			message += " " + err.Error()
		}
		a.t.Balloon("SSCv2", message, 2)
		a.setMode(config.ModeOff)
		return
	}
	if a.refreshAdapter().Mode != driver.BthUSB {
		a.t.Balloon("SSCv2", T("Сначала верните адаптер в режим Bluetooth Windows через «Выкл».", "Choose Off to return the adapter to Windows Bluetooth first."), 2)
		a.setMode(config.ModeOff)
		return
	}
	if _, err := helper.Call(ipc.Request{Op: "native-stereo-bind"}); err != nil {
		a.nativeError(err)
		return
	}
	a.nativeBound = true

	cmd := exec.Command(selfPath(), "native-aac-worker")
	cmd.SysProcAttr = &syscall.SysProcAttr{HideWindow: true, CreationFlags: 0x08000000}
	input, err := cmd.StdinPipe()
	if err != nil {
		a.nativeError(errors.Join(err, a.stopNativeAAC()))
		return
	}
	output, err := cmd.StdoutPipe()
	if err == nil {
		cmd.Stderr = cmd.Stdout
		err = cmd.Start()
	}
	if err != nil {
		input.Close()
		if output != nil {
			output.Close()
		}
		a.nativeError(errors.Join(err, a.stopNativeAAC()))
		return
	}

	p := &nativeProcess{cmd: cmd, input: input, done: make(chan struct{})}
	a.mu.Lock()
	a.native = p
	a.mu.Unlock()
	a.setMode(config.ModeAAC)
	go a.watchNativeAAC(p, output)
	go func() {
		select {
		case <-p.done:
		case <-time.After(15 * time.Second):
			if !p.ready.Load() {
				_ = p.cmd.Process.Kill()
			}
		}
	}()
}

func (a *App) watchNativeAAC(p *nativeProcess, output io.Reader) {
	scanner := bufio.NewScanner(output)
	var last string
	for scanner.Scan() {
		line := scanner.Text()
		if line == "native-aac-ready" {
			p.ready.Store(true)
			a.refresh()
		} else {
			last = line
			logf("native AAC: %s", line)
		}
	}
	err := errors.Join(scanner.Err(), p.cmd.Wait())
	close(p.done)

	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	current := a.native == p
	a.mu.Unlock()
	if !current {
		return
	}
	if err == nil {
		err = errors.New("native AAC worker stopped")
	}
	if last != "" {
		err = fmt.Errorf("%w: %s", err, last)
	}
	a.nativeError(errors.Join(err, a.stopNativeAAC()))
}

// stopNativeAAC runs with opMu held and keeps a failed rollback retryable.
func (a *App) stopNativeAAC() error {
	a.mu.Lock()
	p := a.native
	a.native = nil
	a.mu.Unlock()
	if p != nil {
		_ = p.input.Close()
		select {
		case <-p.done:
		case <-time.After(3 * time.Second):
			_ = p.cmd.Process.Kill()
			<-p.done
		}
	}
	if a.nativeBound {
		if _, err := helper.Call(ipc.Request{Op: "native-stereo-restore"}); err != nil {
			return err
		}
		a.nativeBound = false
		a.recoverStockStereo()
	}
	return nil
}

func (a *App) recoverStockStereo() {
	const buds = "Buds2 Pro"
	wait := func(timeout time.Duration) bool {
		deadline := time.Now().Add(timeout)
		for {
			if audio.HeadphonesStereoActive(buds) {
				return true
			}
			if time.Now().After(deadline) {
				return false
			}
			time.Sleep(150 * time.Millisecond)
		}
	}
	logf("native AAC: reconnecting Buds A2DP after restoring the Windows stereo driver")
	if _, err := helper.Call(ipc.Request{Op: "native-stereo-reconnect"}); err != nil {
		logf("native AAC: reconnect Buds A2DP: %v", err)
		a.t.Balloon("SSCv2", T("Не удалось переподключить стереовыход Buds: ", "Could not reconnect Buds stereo: ")+err.Error(), 2)
		return
	}
	logf("native AAC: Windows stereo output active after reconnect: %v", wait(6*time.Second))
}

func (a *App) nativeError(err error) {
	logf("native AAC: %v", err)
	a.setMode(config.ModeOff)
	a.t.Balloon(T("Ошибка AAC через Bluetooth Windows", "Windows Bluetooth AAC failed"), err.Error(), 2)
}
