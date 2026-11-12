package app

import (
	"os"
	"path/filepath"
	"testing"
	"time"

	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

func TestWorkerProcessIPC(t *testing.T) {
	t.Setenv("LOCALAPPDATA", t.TempDir())
	t.Setenv("SSCV2_WORKER_PROCESS_TEST", "1")
	stream := ipc.NativeStream{Mode: config.ModeAAC, BitrateKbps: 224}
	p, err := startWorkerProcess("-test.run=^TestWorkerProcessChild$", "test-stderr.log", ipc.NativeConfig{Stream: stream})
	if err != nil {
		t.Fatal(err)
	}
	events := make(chan ipc.Event, 2)
	exit := make(chan error, 1)
	p.watch(func(e ipc.Event) { events <- e }, func(err error) { exit <- err })
	t.Cleanup(func() {
		if p.running() {
			_ = p.process.Kill()
			<-p.done
		}
	})
	select {
	case e := <-events:
		if e.Ev != ipc.EventNativeReady || e.Native == nil || *e.Native != stream {
			t.Fatalf("unexpected startup event: %+v", e)
		}
	case err := <-exit:
		t.Fatalf("worker exited before readiness: %v", err)
	case <-time.After(5 * time.Second):
		t.Fatal("worker did not report readiness")
	}
	if p.stop(5*time.Second, true) {
		t.Fatal("worker did not handle stop")
	}
	if err := <-exit; err != nil {
		t.Fatal(err)
	}
	// The monitor drains events before reporting exit.
	select {
	case e := <-events:
		if e.Ev != ipc.EventNativeLog || e.Msg != "stopped" {
			t.Fatalf("unexpected final event: %+v", e)
		}
	default:
		t.Fatal("missing final event")
	}
	got, err := os.ReadFile(filepath.Join(config.LogDir(), "test-stderr.log"))
	if err != nil || string(got) != "stderr" {
		t.Fatalf("stderr = %q, %v", got, err)
	}
}

func TestWorkerProcessChild(t *testing.T) {
	if os.Getenv("SSCV2_WORKER_PROCESS_TEST") == "" {
		return
	}
	r, w := ipc.NewReader(os.Stdin), ipc.NewWriter(os.Stdout)
	var cfg ipc.NativeConfig
	if err := r.Read(&cfg); err != nil {
		os.Exit(1)
	}
	_, _ = os.Stderr.WriteString("stderr")
	if err := w.Write(ipc.Event{Ev: ipc.EventNativeReady, Native: &cfg.Stream}); err != nil {
		os.Exit(2)
	}
	var cmd ipc.Command
	if err := r.Read(&cmd); err != nil || cmd.Cmd != ipc.CommandStop || !cmd.Keep {
		os.Exit(3)
	}
	if err := w.Write(ipc.Event{Ev: ipc.EventNativeLog, Msg: "stopped"}); err != nil {
		os.Exit(4)
	}
	os.Exit(0)
}
