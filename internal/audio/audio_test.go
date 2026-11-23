package audio

import (
	"errors"
	"syscall"
	"testing"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
)

func TestVolumeCallbackNativeArguments(t *testing.T) {
	var level float32
	cb := newVolCallback(func(_ windows.GUID, _ bool, value float32) { level = value })
	defer liveCbs.Delete(cb)
	var iface *volCallback
	result, _, _ := syscall.SyscallN(cb.vtbl[0], uintptr(unsafe.Pointer(cb)),
		uintptr(unsafe.Pointer(&iidIAudioEndpointVolumeCb)), uintptr(unsafe.Pointer(&iface)))
	if result != 0 || iface != cb {
		t.Fatalf("QueryInterface returned %#x, interface %p", result, iface)
	}
	data := volNotify{master: 0.25}
	syscall.SyscallN(cb.vtbl[3], uintptr(unsafe.Pointer(cb)), uintptr(unsafe.Pointer(&data)))
	if level != data.master {
		t.Fatalf("OnNotify delivered %v, want %v", level, data.master)
	}
}

func TestFindRenderEndpointAfterReplacement(t *testing.T) {
	const adapter = "SSCv2 Buds WaveRT"
	old := Endpoint{ID: "old", AdapterName: adapter}
	replacement := Endpoint{ID: "new", Name: "Наушники (" + adapter + ")"}
	speakers := Endpoint{ID: "speakers", AdapterName: "Realtek"}

	if got := findRenderEndpoint([]Endpoint{replacement, old}, adapter, old.ID); got != old {
		t.Fatalf("selected %v while the current endpoint is active", got)
	}
	if got := findRenderEndpoint([]Endpoint{speakers, replacement}, adapter, old.ID); got != replacement {
		t.Fatalf("selected %v after the current endpoint disappeared", got)
	}
	if got := findRenderEndpoint([]Endpoint{speakers}, adapter, old.ID); got.ID != "" {
		t.Fatalf("selected an unrelated endpoint: %v", got)
	}
}

func TestCaptureReportsInvalidatedEndpoint(t *testing.T) {
	const invalidated hresult = 0x88890004
	ok := syscall.NewCallback(func(uintptr) uintptr { return 0 })
	clientVTable := [12]uintptr{10: ok, 11: ok}
	captureVTable := [6]uintptr{
		5: syscall.NewCallback(func(uintptr, uintptr) uintptr { return uintptr(invalidated) }),
	}

	event, err := windows.CreateEvent(nil, 0, 0, nil)
	if err != nil {
		t.Fatal(err)
	}
	defer windows.CloseHandle(event)
	c := &Capture{client: &comObject{vtable: &clientVTable[0]}, capture: &comObject{vtable: &captureVTable[0]}, event: event}
	if err := c.Start(nil); err != nil {
		t.Fatal(err)
	}
	defer c.Stop()
	if err := windows.SetEvent(event); err != nil {
		t.Fatal(err)
	}
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

func TestCaptureContinuityUsesDeviceFrames(t *testing.T) {
	var clock captureTimeline
	for _, p := range []struct {
		pos   uint64
		flags uint32
		gap   bool
	}{{0, 0, false}, {480, 0, false}, {1440, 0, true}, {0, 4, false}, {2400, 0, false}, {2880, 1, true}} {
		if got := clock.observe(p.pos, 480, p.flags); got != p.gap {
			t.Fatal(p, got)
		}
	}
}

func TestCaptureClockPreservesPacketAge(t *testing.T) {
	now := time.Now()
	c := captureClock{at: now, hns: 2000000}
	if got := c.packetTime(1500000, 0, now); now.Sub(got) != 50*time.Millisecond {
		t.Fatal(got)
	}
	if got := c.packetTime(1500000, 4, now); got != now {
		t.Fatal("invalid timestamp used")
	}
}
