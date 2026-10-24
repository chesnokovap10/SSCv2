package audio

import (
	"testing"
	"time"
)

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
	if err := c.Start(func(s []float32, n int) { frames += n }); err != nil {
		t.Fatal(err)
	}
	time.Sleep(500 * time.Millisecond)
	c.Close()
	// Loopback delivers nothing while the endpoint renders nothing, so only
	// log the count (the open/start/stop path is what is under test).
	t.Logf("captured %d frames in 0.5 s", frames)
}
