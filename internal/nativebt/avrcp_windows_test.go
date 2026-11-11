package nativebt

import (
	"bytes"
	"context"
	"io"
	"net"
	"testing"
	"time"

	"sscv2/internal/bt"
)

func TestAVRCPTrackButtons(t *testing.T) {
	link, buds := net.Pipe()
	defer link.Close()
	defer buds.Close()
	deadline := time.Now().Add(2 * time.Second)
	if err := buds.SetDeadline(deadline); err != nil {
		t.Fatal(err)
	}
	ctx, cancel := context.WithDeadline(context.Background(), deadline)
	defer cancel()
	keys := make(chan int, 8)
	go func() { _ = serveAVRCP(ctx, link, io.Discard, keys) }()

	volume := make([]byte, 14)
	if _, err := io.ReadFull(buds, volume); err != nil {
		t.Fatal(err)
	}
	volume[0] |= 2
	volume[3] = 0x09
	if _, err := buds.Write(volume); err != nil {
		t.Fatal(err)
	}
	for i, op := range []byte{0x4b, 0xcb, 0x4c, 0xcc} {
		label := byte(i+3) << 4
		command := []byte{label, 0x11, 0x0e, 0, 0x48, 0x7c, op, 0}
		if _, err := buds.Write(command); err != nil {
			t.Fatal(err)
		}
		var response [8]byte
		if _, err := io.ReadFull(buds, response[:]); err != nil {
			t.Fatal(err)
		}
		want := []byte{label | 2, 0x11, 0x0e, 0x09, 0x48, 0x7c, op, 0}
		if !bytes.Equal(response[:], want) {
			t.Fatalf("button 0x%02x: response %x, want %x", op, response, want)
		}
	}
	for _, want := range []int{bt.MediaNext, bt.MediaPrev} {
		select {
		case key := <-keys:
			if key != want {
				t.Fatalf("media key %d, want %d", key, want)
			}
		case <-ctx.Done():
			t.Fatalf("media key %d was not dispatched", want)
		}
	}
	select {
	case key := <-keys:
		t.Fatalf("unexpected extra media key %d", key)
	default:
	}
}
