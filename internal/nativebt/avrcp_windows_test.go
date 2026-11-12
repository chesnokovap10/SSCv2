package nativebt

import (
	"bytes"
	"context"
	"io"
	"net"
	"testing"
	"time"

	"sscv2/internal/audio"
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
	activity := &audio.Activity{}
	go func() { _ = serveAVRCP(ctx, link, io.Discard, keys, newBudsVolume(), activity) }()

	volume := make([]byte, 14)
	if _, err := io.ReadFull(buds, volume); err != nil {
		t.Fatal(err)
	}
	volume[0] |= 2
	volume[3] = 0x09
	if _, err := buds.Write(volume); err != nil {
		t.Fatal(err)
	}
	if _, err := buds.Write(avrcpFrame(0x20, 3, 0x31, 1, 0, 0, 0, 0)); err != nil {
		t.Fatal(err)
	}
	checkStatus := func(want []byte) {
		t.Helper()
		got := make([]byte, len(want))
		if _, err := io.ReadFull(buds, got); err != nil {
			t.Fatal(err)
		}
		if !bytes.Equal(got, want) {
			t.Fatalf("playback status = %x, want %x", got, want)
		}
	}
	checkStatus(avrcpFrame(0x22, 0x0f, 0x31, 1, 2))
	activity.Observe([]float32{0.5})
	checkStatus(avrcpFrame(0x22, 0x0d, 0x31, 1, 1))
	if _, err := buds.Write(avrcpFrame(0x80, 1, 0x30)); err != nil {
		t.Fatal(err)
	}
	checkStatus(avrcpFrame(0x82, 0x0c, 0x30, 0, 0, 0, 0, 0, 0, 0, 0, 1))
	for i, op := range []byte{0x4b, 0xcb, 0x4c, 0xcc, 0x46, 0xc6} {
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
	for _, want := range []int{bt.MediaNext, bt.MediaPrev, bt.MediaPause} {
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

func TestAVRCPVolumeTracksTheLatestLevel(t *testing.T) {
	link, buds := net.Pipe()
	defer link.Close()
	defer buds.Close()
	deadline := time.Now().Add(2 * time.Second)
	if err := buds.SetDeadline(deadline); err != nil {
		t.Fatal(err)
	}
	ctx, cancel := context.WithDeadline(context.Background(), deadline)
	defer cancel()
	volume := newBudsVolume()
	volume.set(5)
	keys := make(chan int, 8)
	go func() { _ = serveAVRCP(ctx, link, io.Discard, keys, volume, &audio.Activity{}) }()

	receiveLevel := func(want byte) []byte {
		t.Helper()
		packet := make([]byte, 14)
		if _, err := io.ReadFull(buds, packet); err != nil {
			t.Fatal(err)
		}
		if packet[9] != 0x50 || packet[13] != want {
			t.Fatalf("got %x, expected SetAbsoluteVolume(%d)", packet, want)
		}
		return packet
	}
	ack := func(packet []byte) {
		t.Helper()
		packet[0] |= 2
		packet[3] = 0x09
		if _, err := buds.Write(packet); err != nil {
			t.Fatal(err)
		}
	}
	fallback := func() float32 { return 0.04 }
	first := receiveLevel(5)
	if gain := volume.gain(fallback); gain != 0.04 {
		t.Fatalf("gain before the first confirmation = %v", gain)
	}
	volume.set(10)
	volume.set(102)
	ack(first)
	second := receiveLevel(102)
	if second[0] == first[0]&^2 {
		t.Fatal("volume updates reused the transaction label")
	}
	if gain := volume.gain(fallback); gain != 1 {
		t.Fatalf("gain while hardware volume is active = %v", gain)
	}
	ack(second)
	volume.set(5)
	lower := receiveLevel(5)
	if gain := volume.gain(fallback); gain != 1 {
		t.Fatalf("PCM gain changed while the decrease from 80%% to 4%% was in flight: %v", gain)
	}
	ack(lower)
	volume.set(0)
	if gain := volume.gain(fallback); gain != 1 {
		t.Fatalf("PCM gain changed while AVRCP was handling mute: %v", gain)
	}
	ack(receiveLevel(0))
	volume.set(5)
	ack(receiveLevel(5))
}
