package engine

import (
	"io"
	"testing"

	"sscv2/internal/audio"
	"sscv2/internal/ipc"
)

func TestReleaseSessionAudioClearsFailedSession(t *testing.T) {
	stopped := 0
	e := &engine{
		out:           ipc.NewWriter(io.Discard),
		cap:           &audio.Capture{},
		stopMuteGuard: func() { stopped++ },
		st:            ipc.EngineStatus{Muted: true, CaptureDevice: "Speakers", CaptureFormat: "48000 Hz"},
	}
	e.releaseSessionAudio()
	e.releaseSessionAudio() // cleanup after a retry must be idempotent
	if stopped != 1 || e.cap != nil || e.stopMuteGuard != nil ||
		e.st.Muted || e.st.CaptureDevice != "" || e.st.CaptureFormat != "" {
		t.Fatalf("capture still owned after cleanup: stop calls %d, status %+v", stopped, e.st)
	}
}
