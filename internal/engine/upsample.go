package engine

import "math"

// upsampler2x doubles the rate of interleaved stereo float PCM (48 -> 96 kHz
// for SSC UHQ): a half-band FIR, so even outputs are the input samples and
// odd outputs are interpolated with a Blackman-windowed sinc (64 taps per
// side of the phase, passband to ~21 kHz, ~-75 dB images).
type upsampler2x struct {
	h    []float32 // odd-phase taps, h[k] for input offset k-half+1 .. k-half
	hist [2][]float32
	out  []float32
}

const upTaps = 64

func newUpsampler2x() *upsampler2x {
	u := &upsampler2x{h: make([]float32, upTaps)}
	half := upTaps / 2
	n := float64(2 * upTaps)
	var sum float64
	for k := 0; k < upTaps; k++ {
		// odd output sits between input k-half and k-half+1: offset t in
		// input samples from it, then sinc at the 2x rate
		t := float64(k-half) + 0.5
		x := math.Pi * t
		s := math.Sin(x) / x
		m := t*2 + n/2 // position in the 2x-rate window
		w := 0.42 - 0.5*math.Cos(2*math.Pi*m/n) + 0.08*math.Cos(4*math.Pi*m/n)
		u.h[k] = float32(s * w)
		sum += s * w
	}
	for k := range u.h { // unity gain at DC
		u.h[k] = float32(float64(u.h[k]) / sum)
	}
	for c := range u.hist {
		u.hist[c] = make([]float32, upTaps-1)
	}
	return u
}

// process upsamples `in` (interleaved stereo, n frames) into 2n frames; the
// result is reused by the next call. Delay: upTaps/2 input samples.
func (u *upsampler2x) process(in []float32) []float32 {
	n := len(in) / 2
	u.out = u.out[:0]
	if cap(u.out) < 4*n {
		u.out = make([]float32, 0, 4*n)
	}
	u.out = u.out[:4*n]
	var buf [2][]float32
	for c := 0; c < 2; c++ {
		b := make([]float32, 0, len(u.hist[c])+n)
		b = append(b, u.hist[c]...)
		for i := 0; i < n; i++ {
			b = append(b, in[2*i+c])
		}
		buf[c] = b
	}
	half := upTaps / 2
	for c := 0; c < 2; c++ {
		b := buf[c]
		for i := 0; i < n; i++ {
			// input sample i sits at b[i+upTaps-1]; delay the even phase by
			// half-1 so both phases share the filter's centre
			centre := i + upTaps - 1 - half
			u.out[4*i+c] = b[centre]
			var acc float32
			base := i // b[i .. i+upTaps-1]
			for k := 0; k < upTaps; k++ {
				acc += u.h[k] * b[base+k]
			}
			u.out[4*i+2+c] = acc
		}
		copy(u.hist[c], b[len(b)-(upTaps-1):])
	}
	return u.out
}
