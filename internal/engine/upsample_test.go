package engine

import (
	"math"
	"testing"
)

// TestUpsample: a tone at 48 kHz comes out as the same tone at 96 kHz
// (error vs the ideal signal, after the filter delay) across the band.
func TestUpsample(t *testing.T) {
	for _, c := range []struct {
		hz     float64
		minSNR float64
	}{{1000, 100}, {10000, 100}, {18000, 80}, {20000, 75}} {
		u := newUpsampler2x()
		const block = 432
		var got []float32
		for b := 0; b < 20; b++ {
			in := make([]float32, block*2)
			for i := 0; i < block; i++ {
				v := float32(0.5 * math.Sin(2*math.Pi*c.hz*float64(b*block+i)/48000))
				in[2*i], in[2*i+1] = v, v
			}
			got = append(got, u.process(in)...)
		}
		delay := upTaps // output samples at 96 kHz: out[2i] = in[i-upTaps/2]
		var sig, noise float64
		for j := 4000; j < len(got)/2; j++ {
			want := 0.5 * math.Sin(2*math.Pi*c.hz*float64(j-delay)/96000)
			e := float64(got[2*j]) - want
			sig += want * want
			noise += e * e
			if got[2*j] != got[2*j+1] {
				t.Fatal("channels differ")
			}
		}
		snr := 10 * math.Log10(sig/noise)
		t.Logf("%5.0f Hz: SNR %.1f dB", c.hz, snr)
		if snr < c.minSNR {
			t.Errorf("%v Hz: SNR %.1f dB < %v", c.hz, snr, c.minSNR)
		}
	}
}
