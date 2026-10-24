package helper

import (
	"testing"
	"time"

	"sscv2/internal/ipc"
)

func TestPipe(t *testing.T) {
	go Serve(CurrentUserSID())
	time.Sleep(200 * time.Millisecond)
	r, err := callPipe(ipc.Request{Op: "ping"})
	if err != nil || !r.OK {
		t.Fatalf("ping: %v %+v", err, r)
	}
	t.Logf("ping ok, version %s", r.Version)
	r, err = callPipe(ipc.Request{Op: "driver", VID: 0x1234, PID: 0x5678, WinUSB: true})
	t.Logf("foreign device rejected: ok=%v err=%q", r.OK, r.Error)
	if r.OK {
		t.Fatal("foreign VID/PID accepted")
	}
	r, _ = callPipe(ipc.Request{Op: "keys-read"})
	t.Logf("keys-read as user: ok=%v err=%q", r.OK, r.Error)
}
