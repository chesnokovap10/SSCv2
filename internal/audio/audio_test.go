package audio

import (
	"errors"
	"runtime"
	"syscall"
	"testing"
	"time"
	"unsafe"
)

func TestCaptureReportsInvalidatedEndpoint(t *testing.T) {
	const invalidated hresult = 0x88890004
	ok := syscall.NewCallback(func(uintptr) uintptr { return 0 })
	clientVTable := [12]uintptr{10: ok, 11: ok}
	captureVTable := [6]uintptr{
		5: syscall.NewCallback(func(uintptr, uintptr) uintptr { return uintptr(invalidated) }),
	}
	client, capture := &clientVTable[0], &captureVTable[0]
	var pinned runtime.Pinner
	pinned.Pin(client)
	pinned.Pin(capture)
	pinned.Pin(&client)
	pinned.Pin(&capture)
	defer pinned.Unpin()

	c := &Capture{client: uintptr(unsafe.Pointer(&client)), capture: uintptr(unsafe.Pointer(&capture))}
	if err := c.Start(nil); err != nil {
		t.Fatal(err)
	}
	defer c.Stop()
	select {
	case err := <-c.Errors():
		if !errors.Is(err, invalidated) {
			t.Fatalf("capture error = %v, want %v", err, invalidated)
		}
	case <-time.After(2 * time.Second):
		t.Fatal("capture did not report the endpoint failure")
	}
}

func TestListAndCapture(t *testing.T) {
	for _, e := range List(false, StateActive|StateDisabled) {
		t.Logf("render: %q desc=%q adapter=%q", e.Name, e.Desc, e.AdapterName)
	}
	d, err := DefaultRender()
	if err != nil {
		t.Fatal(err)
	}
	t.Logf("default: %s", d.Name)
	vol, err := endpointVolume("")
	if err != nil {
		t.Fatal(err)
	}
	s, _ := getScalar(vol)
	release(vol)
	t.Logf("default volume %.2f", s)
	c, err := OpenCapture("")
	if err != nil {
		t.Fatal(err)
	}
	t.Logf("format %s", c.Format)
	frames := 0
	if err := c.Start(func(s []float32, n int, _ bool) { frames += n }); err != nil {
		t.Fatal(err)
	}
	time.Sleep(500 * time.Millisecond)
	c.Close()
	// Loopback delivers nothing while the endpoint renders nothing, so only
	// log the count (the open/start/stop path is what is under test).
	t.Logf("captured %d frames in 0.5 s", frames)
}
