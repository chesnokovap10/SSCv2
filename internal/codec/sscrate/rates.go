// Package sscrate lists the bitrates accepted by libssc.
package sscrate

import "slices"

// Kbps returns the encoder rates for this sample rate in ascending order.
func Kbps(sampleRate int) []int {
	if sampleRate == 96000 {
		return []int{152, 250, 291, 308, 442, 584, 886}
	}
	return []int{88, 96, 128, 192, 229, 256, 328}
}

func Valid(sampleRate, kbps int) bool {
	return slices.Contains(Kbps(sampleRate), kbps)
}
