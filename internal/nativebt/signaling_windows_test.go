package nativebt

import (
	"context"
	"io"
	"net"
	"testing"
	"time"
)

func TestPeerPauseResumeAndAbort(t *testing.T) {
	link := &avdtpTestLink{}
	p := avdtpSession{link: link, ctx: context.Background()}
	m := newSignaledMedia(p.ctx, &testMedia{})
	if err := p.streamingCommand(m, []byte{0x10, suspendStream, 4}); err != nil {
		t.Fatal(err)
	}
	done := make(chan error, 1)
	go func() { _, err := m.Write([]byte{1}); done <- err }()
	select {
	case <-done:
		t.Fatal("sent while suspended")
	case <-time.After(10 * time.Millisecond):
	}
	if err := p.streamingCommand(m, []byte{0x20, startStream, 4}); err != nil {
		t.Fatal(err)
	}
	select {
	case err := <-done:
		if err != nil {
			t.Fatal(err)
		}
	case <-time.After(time.Second):
		t.Fatal("resume stuck")
	}
	err := p.streamingCommand(m, []byte{0x30, abort, 4})
	if err == nil {
		t.Fatal("abort did not terminate stream")
	}
	m.state(false, err)
	if _, err := m.Write([]byte{1}); err == nil {
		t.Fatal("sent after abort")
	}
}

func TestStreamingSignalingReaderRepliesAndStops(t *testing.T) {
	local, peer := net.Pipe()
	defer local.Close()
	defer peer.Close()
	p := avdtpSession{link: local, ctx: context.Background()}
	m := newSignaledMedia(p.ctx, &testMedia{})
	stop := p.watchStreamingCommands(m)
	defer stop()
	peer.SetDeadline(time.Now().Add(time.Second))
	if _, err := peer.Write([]byte{0x40, suspendStream, 4}); err != nil {
		t.Fatal(err)
	}
	var reply [2]byte
	if _, err := io.ReadFull(peer, reply[:]); err != nil {
		t.Fatal(err)
	}
	if reply != [2]byte{0x42, suspendStream} {
		t.Fatalf("reply %x", reply)
	}
}
