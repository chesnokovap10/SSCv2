package ssc

import (
	"bufio"
	"crypto/sha256"
	"encoding/binary"
	"encoding/hex"
	"fmt"
	"math"
	"os"
	"path/filepath"
	"strings"
	"testing"
)

// signal: the integer test signal of libssc/test/cgo_ref.py (keep in sync).
func signal(frame int) []int32 {
	x := uint32(0x1234567 + uint64(frame)*0x9E3779B9)
	out := make([]int32, 0, FrameLen*2)
	for i := 0; i < FrameLen; i++ {
		t := frame*FrameLen + i
		x = x*1103515245 + 12345
		noise := int64((x>>8)&0xFFFFFF) - 0x800000
		for _, pa := range [2][2]int64{{109, 1 << 21}, {251, 1 << 20}} {
			period, amp := pa[0], pa[1]
			p := int64(t) % period
			var tri int64
			if p < period/2 {
				tri = (4*p*amp)/period - amp
			} else {
				tri = 3*amp - (4*p*amp)/period
			}
			v := tri + noise>>5
			if frame%7 == 3 {
				v *= 4
			}
			if frame%11 == 5 {
				v = 0
			}
			out = append(out, int32(max(-(1<<23), min((1<<23)-1, v))))
		}
	}
	return out
}

// TestOracle: the cgo build is bit-exact with the Samsung blob on all 14
// bitrates (hashes from libssc/test/cgo_ref.py), and FrameBytes predicts
// every frame's size.
func TestOracle(t *testing.T) {
	f, err := os.Open(filepath.Join("testdata", "oracle.txt"))
	if err != nil {
		t.Fatal(err)
	}
	defer f.Close()
	sc := bufio.NewScanner(f)
	n := 0
	for sc.Scan() {
		var rate, bitrate, frames int
		var want string
		if _, err := fmt.Sscan(sc.Text(), &rate, &bitrate, &frames, &want); err != nil {
			t.Fatalf("oracle.txt: %q: %v", sc.Text(), err)
		}
		e, err := New(rate, bitrate)
		if err != nil {
			t.Fatal(err)
		}
		h := sha256.New()
		for i := 0; i < frames; i++ {
			out, err := e.EncodeInt32(signal(i))
			if err != nil {
				t.Fatal(err)
			}
			if len(out) != FrameBytes(rate, bitrate) {
				t.Errorf("%d/%d frame %d: %d bytes, FrameBytes %d", rate, bitrate, i, len(out), FrameBytes(rate, bitrate))
			}
			h.Write(binary.LittleEndian.AppendUint16(nil, uint16(len(out))))
			h.Write(out)
		}
		e.Close()
		if got := hex.EncodeToString(h.Sum(nil)); got != want {
			t.Errorf("%d Hz %d bps: frames differ from the blob", rate, bitrate)
		}
		n++
	}
	if n != 14 {
		t.Fatalf("%d profiles in oracle.txt", n)
	}
}

// TestWrappers: every libssc source has a z*.c wrapper here.
func TestWrappers(t *testing.T) {
	src := filepath.Join("..", "..", "..", "libssc", "src")
	// pitch.c / celt_lpc.c: included by ssc_*.c; ssc_decoder.c: test bench only
	skip := map[string]bool{"pitch.c": true, "celt_lpc.c": true, "ssc_decoder.c": true}
	for _, dir := range []string{"", "opus"} {
		files, _ := filepath.Glob(filepath.Join(src, dir, "*.c"))
		for _, p := range files {
			b := filepath.Base(p)
			if skip[b] {
				continue
			}
			w := "zssc_" + b
			if dir == "opus" {
				w = "zssc_opus_" + b
			}
			if _, err := os.Stat(w); err != nil {
				t.Errorf("%s: no wrapper %s (go run ./tools/genwrap)", strings.TrimPrefix(p, src), w)
			}
		}
	}
}

func TestFloat(t *testing.T) {
	e, err := New(48000, 229000)
	if err != nil {
		t.Fatal(err)
	}
	defer e.Close()
	if _, err := New(48000, 229000); err != ErrBusy {
		t.Fatalf("second encoder: %v", err)
	}
	pcm := make([]float32, FrameLen*2)
	for f := 0; f < 20; f++ {
		for i := 0; i < FrameLen; i++ {
			v := float32(0.5 * math.Sin(float64(f*FrameLen+i)*2*math.Pi*1000/48000))
			pcm[2*i], pcm[2*i+1] = v, -v
		}
		out, err := e.Encode(pcm)
		if err != nil {
			t.Fatal(err)
		}
		if len(out) != FrameBytes(48000, 229000) || out[0] != 0xFF || out[1] != 0xEE {
			t.Fatalf("frame %d: %d bytes % X", f, len(out), out[:4])
		}
	}
	for _, c := range []struct {
		v    float32
		want int32
	}{{0, 0}, {1, 1<<23 - 1}, {-1, -1 << 23}, {2, 1<<23 - 1}, {-2, -1 << 23}, {0.5, 1 << 22}} {
		if g := To24(c.v); g != c.want {
			t.Errorf("To24(%v) = %d, want %d", c.v, g, c.want)
		}
	}
}
