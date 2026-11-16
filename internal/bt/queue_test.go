package bt

import (
	"testing"
	"time"
)

func TestExpiredCommandNeverRuns(t *testing.T) {
	s := &stackT{}
	s.loopRunning.Store(true)
	s.kickPending.Store(true)
	ran := false
	if err := s.callSyncWithin(func() { ran = true }, time.Millisecond); err != ErrTimeout {
		t.Fatal(err)
	}
	s.drain()
	if ran {
		t.Fatal("expired command ran")
	}
}

func TestVolumeRetryIsBoundedAndRearmsSameValue(t *testing.T) {
	v := volPump{sent: 32}
	for attempt := 0; attempt < 2; attempt++ {
		v.retryUnconfirmed()
		if v.sent != -1 {
			t.Fatal("same desired level would be suppressed")
		}
		v.sent = 32
	}
	v.retryUnconfirmed()
	if v.sent != 32 {
		t.Fatal("unbounded retry")
	}
}
