package app

import (
	"errors"
	"io"
	"os"
	"path/filepath"
	"sync"
	"sync/atomic"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"

	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

// workerProcess owns the process and JSON lines exchanged over its pipes.
type workerProcess struct {
	process       *os.Process
	stdin         *os.File
	stdout        *os.File
	in            *ipc.Writer
	done          chan struct{}
	waitErr       error // read after done is closed
	stopReq       atomic.Bool
	volumeMu      sync.Mutex
	volumePending *ipc.Command
	volumeWriting bool
}

func startWorkerProcess(command, stderrLog string, cfg any) (*workerProcess, error) {
	self, err := os.Executable()
	if err != nil {
		return nil, err
	}
	input, stdin, err := os.Pipe()
	if err != nil {
		return nil, err
	}
	defer input.Close()
	stdout, output, err := os.Pipe()
	if err != nil {
		stdin.Close()
		return nil, err
	}
	defer output.Close()

	stderr, err := os.OpenFile(filepath.Join(config.LogDir(), stderrLog), os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0o600)
	if err != nil {
		stderr, err = os.OpenFile(os.DevNull, os.O_WRONLY, 0)
	}
	if err != nil {
		stdin.Close()
		stdout.Close()
		return nil, err
	}
	defer stderr.Close()
	process, err := createWorker(self, []string{command}, input, output, stderr)
	if err != nil {
		stdin.Close()
		stdout.Close()
		return nil, err
	}
	p := &workerProcess{process: process, stdin: stdin, stdout: stdout, in: ipc.NewWriter(stdin), done: make(chan struct{})}
	if err := p.in.Write(cfg); err != nil {
		stdin.Close()
		stdout.Close()
		_ = process.Kill()
		_, _ = process.Wait()
		return nil, err
	}
	return p, nil
}

// watch starts after the tray has published this process as current. It drains
// events before notifying the tray of exit, including a final status or error.
func (p *workerProcess) watch(onEvent func(ipc.Event), onExit func(error)) {
	go func() {
		var readErr error
		r := ipc.NewReader(p.stdout)
		for {
			var event ipc.Event
			if err := r.Read(&event); err != nil {
				if !errors.Is(err, io.EOF) {
					readErr = err
					_ = p.process.Kill()
				}
				break
			}
			onEvent(event)
		}
		_ = p.stdout.Close()
		state, err := p.process.Wait()
		if err == nil && !state.Success() {
			err = errors.New(state.String())
		}
		_ = p.stdin.Close()
		p.waitErr = errors.Join(readErr, err)
		close(p.done)
		onExit(p.waitErr)
	}()
}

func (p *workerProcess) send(c ipc.Command) { _ = p.in.Write(c) }

// queueVolume keeps IPC writes off the tray thread and coalesces slider updates.
func (p *workerProcess) queueVolume(command ipc.Command) {
	p.volumeMu.Lock()
	defer p.volumeMu.Unlock()
	p.volumePending = &command
	if p.volumeWriting {
		return
	}
	p.volumeWriting = true
	go func() {
		for {
			p.volumeMu.Lock()
			update := p.volumePending
			p.volumePending = nil
			if update == nil || p.stopReq.Load() {
				p.volumeWriting = false
				p.volumeMu.Unlock()
				return
			}
			p.volumeMu.Unlock()
			p.send(*update)
		}
	}()
}

// stop requests a graceful shutdown and kills the worker if it does not exit.
// keep transfers WinUSB audio routing to its replacement.
func (p *workerProcess) stop(timeout time.Duration, keep bool) (forced bool) {
	p.stopReq.Store(true)
	if !p.running() {
		return false
	}
	timer := time.NewTimer(timeout)
	defer timer.Stop()
	go func() {
		p.send(ipc.Command{Cmd: ipc.CommandStop, Keep: keep})
		if p.stdin != nil {
			_ = p.stdin.Close()
		}
	}()
	select {
	case <-p.done:
		return false
	case <-timer.C:
		_ = p.process.Kill()
		<-p.done
		return true
	}
}

func (p *workerProcess) running() bool {
	select {
	case <-p.done:
		return false
	default:
		return true
	}
}

// createWorker hides the console and startup cursor and inherits only IPC pipes
// and the worker's stderr handle.
func createWorker(exe string, args []string, input, output, stderr *os.File) (*os.Process, error) {
	name, err := windows.UTF16PtrFromString(exe)
	if err != nil {
		return nil, err
	}
	command, err := windows.UTF16PtrFromString(windows.ComposeCommandLine(append([]string{exe}, args...)))
	if err != nil {
		return nil, err
	}
	var handles [3]windows.Handle
	for i, file := range []*os.File{input, output, stderr} {
		self := windows.CurrentProcess()
		if err := windows.DuplicateHandle(self, windows.Handle(file.Fd()), self, &handles[i], 0, true, windows.DUPLICATE_SAME_ACCESS); err != nil {
			return nil, err
		}
		defer windows.CloseHandle(handles[i])
	}
	attrs, err := windows.NewProcThreadAttributeList(1)
	if err != nil {
		return nil, err
	}
	defer attrs.Delete()
	if err := attrs.Update(windows.PROC_THREAD_ATTRIBUTE_HANDLE_LIST, unsafe.Pointer(&handles[0]), unsafe.Sizeof(handles)); err != nil {
		return nil, err
	}
	const startfForceOffFeedback = 0x80
	start := windows.StartupInfoEx{
		StartupInfo: windows.StartupInfo{
			Flags:      windows.STARTF_USESTDHANDLES | windows.STARTF_USESHOWWINDOW | startfForceOffFeedback,
			ShowWindow: windows.SW_HIDE,
			StdInput:   handles[0],
			StdOutput:  handles[1],
			StdErr:     handles[2],
		},
		ProcThreadAttributeList: attrs.List(),
	}
	start.Cb = uint32(unsafe.Sizeof(start))
	var info windows.ProcessInformation
	flags := uint32(windows.EXTENDED_STARTUPINFO_PRESENT | windows.CREATE_NO_WINDOW)
	if err := windows.CreateProcess(name, command, nil, nil, true, flags, nil, nil, &start.StartupInfo, &info); err != nil {
		return nil, err
	}
	defer windows.CloseHandle(info.Process)
	defer windows.CloseHandle(info.Thread)
	process, err := os.FindProcess(int(info.ProcessId))
	if err != nil {
		_ = windows.TerminateProcess(info.Process, 1)
	}
	return process, err
}
