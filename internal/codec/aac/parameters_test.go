package aac

import "testing"

func TestInvalidBitratesAreRejected(t *testing.T) {
	for _, rate := range []int{-9, 0, 2000000000} {
		e, err := New(48000, 2, rate, 0)
		if err == nil {
			e.Close()
			t.Fatalf("accepted bitrate %d", rate)
		}
	}
}
