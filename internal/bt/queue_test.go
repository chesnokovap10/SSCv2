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

func TestFragmentedFrameAdmissionIsAtomic(t *testing.T) {
	s := &stackT{}
	s.mqCount = len(s.mq) - 1
	s.mqHead = len(s.mq) - 1
	if s.enqueueMediaFrame([]byte{1, 2, 3}, 7, 2, time.Now()) || s.mqHead != len(s.mq)-1 || s.mqCount != len(s.mq)-1 {
		t.Fatal("partial frame admitted")
	}
	s.mqCount--
	if !s.enqueueMediaFrame([]byte{1, 2, 3}, 7, 2, time.Now()) || s.mq[len(s.mq)-1].marker || !s.mq[0].marker || s.mq[0].ts != 7 {
		t.Fatal("fragment wrap or marker")
	}
}
