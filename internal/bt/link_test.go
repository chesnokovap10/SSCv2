package bt

import "testing"

func TestLink(t *testing.T) {
	if Ready() {
		t.Fatal("not started")
	}
}
