package aac

import (
	"math"
	"testing"
)

func TestEncodeSine(t *testing.T) {
	e, err := New(48000, 2, 256000, 667)
	if err != nil {
		t.Fatal(err)
	}
	defer e.Close()
	if e.FrameLen != 1024 {
		t.Fatalf("frame len %d", e.FrameLen)
	}
	pcm := make([]int16, e.FrameLen*2)
	total, frames := 0, 0
	for f := 0; f < 50; f++ {
		for i := 0; i < e.FrameLen; i++ {
			v := int16(8000 * math.Sin(float64(f*e.FrameLen+i)*2*math.Pi*440/48000))
			pcm[2*i], pcm[2*i+1] = v, v
		}
		out, err := e.Encode(pcm)
		if err != nil {
			t.Fatal(err)
		}
		if len(out) > 0 {
			frames++
			if len(out) > 667 {
				t.Fatalf("frame %d bytes > mtu", len(out))
			}
		}
		total += len(out)
	}
	t.Logf("bitrate=%d peak=%d frames=%d avg=%d bytes", e.Bitrate, e.PeakBitrate, frames, total/frames)
}
