package helper

import (
	"errors"
	"fmt"
	"io"
	"os"
	"testing"

	"golang.org/x/sys/windows"
	"sscv2/internal/ipc"
)

func TestPipe(t *testing.T) {
	for _, test := range []struct {
		name string
		req  ipc.Request
		ok   bool
	}{
		{"ping", ipc.Request{Op: "ping"}, true},
		{"reject unsupported device", ipc.Request{Op: "driver", VID: 0x1234, PID: 0x5678, WinUSB: true}, false},
	} {
		t.Run(test.name, func(t *testing.T) {
			pipe, h := testPipeInstance(t)
			done := make(chan error, 1)
			go func() {
				if err := windows.ConnectNamedPipe(h, nil); err != nil && err != windows.ERROR_PIPE_CONNECTED {
					windows.CloseHandle(h)
					done <- err
					return
				}
				serveConn(h)
				done <- nil
			}()
			r, err := callPipeAt(pipe, windows.GetCurrentProcessId(), test.req)
			if err != nil || r.OK != test.ok || r.Version != ipc.Version {
				t.Fatalf("reply: %+v, error: %v", r, err)
			}
			if err := <-done; err != nil {
				t.Fatal(err)
			}
		})
	}
}

func TestPipeRejectsOtherProcessBeforeSending(t *testing.T) {
	pipe, h := testPipeInstance(t)
	done := make(chan error, 1)
	go func() {
		f := os.NewFile(uintptr(h), "test pipe")
		defer f.Close()
		if err := windows.ConnectNamedPipe(h, nil); err != nil && err != windows.ERROR_PIPE_CONNECTED {
			done <- err
			return
		}
		var b [1]byte
		n, err := f.Read(b[:])
		if n != 0 || !errors.Is(err, io.EOF) {
			done <- fmt.Errorf("untrusted server received %d request bytes, read error: %v", n, err)
			return
		}
		done <- nil
	}()
	if _, err := callPipeAt(pipe, windows.GetCurrentProcessId()+1, ipc.Request{Op: "ping"}); !errors.Is(err, errUnexpectedPipeServer) {
		t.Fatalf("expected server identity error, got %v", err)
	}
	if err := <-done; err != nil {
		t.Fatal(err)
	}
}

func testPipeInstance(t *testing.T) (string, windows.Handle) {
	t.Helper()
	pipe := fmt.Sprintf(`\\.\pipe\SSCv2HelperTest-%d-%s`, os.Getpid(), t.Name())
	h, err := newPipeInstance(pipe, CurrentUserSID(), true)
	if err != nil {
		t.Fatal(err)
	}
	return pipe, h
}
