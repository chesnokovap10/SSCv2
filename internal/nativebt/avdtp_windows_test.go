package nativebt

import (
	"bytes"
	"context"
	"errors"
	"io"
	"net"
	"os"
	"testing"
	"time"

	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

type avdtpTestLink struct {
	replies [][]byte
	writes  [][]byte
}

func (l *avdtpTestLink) Read(p []byte) (int, error) {
	if len(l.replies) == 0 {
		return 0, io.EOF
	}
	n := copy(p, l.replies[0])
	l.replies = l.replies[1:]
	return n, nil
}

func (l *avdtpTestLink) Write(p []byte) (int, error) {
	l.writes = append(l.writes, bytes.Clone(p))
	return len(p), nil
}

func TestNativeUHQConfiguration(t *testing.T) {
	for _, tc := range []struct {
		name       string
		rate       byte
		force      bool
		configured bool
	}{
		{"advertised", 0x3e, false, true},
		{"unadvertised", 0x3c, false, false},
		{"forced", 0x3c, true, true},
	} {
		t.Run(tc.name, func(t *testing.T) {
			link := &avdtpTestLink{replies: [][]byte{
				{0x02, discover, 4, 8},
				{0x12, getAllCapabilities, 7, 9, 0, 0xff, 0x75, 0, 0, 0, 3, 1, tc.rate},
				{0x23, setConfiguration, 7, 0x29},
			}}
			stream := ipc.NativeStream{Mode: config.ModeSSCUHQ, BitrateKbps: 152, TryUHQ: tc.force}
			var reported bool
			err := inspect(context.Background(), link, io.Discard, func() (io.WriteCloser, error) {
				t.Fatal("rejected configuration opened a media channel")
				return nil, nil
			}, nil, stream, func(supported bool) { reported = supported })
			if err == nil || reported != (tc.rate&2 != 0) {
				t.Fatalf("discovery reported %t, negotiation error: %v", reported, err)
			}
			if got := len(link.writes) == 3; got != tc.configured {
				t.Fatalf("configuration sent = %t, want %t", got, tc.configured)
			}
			if tc.configured {
				packet := link.writes[2]
				if packet[1] != setConfiguration || packet[len(packet)-1] != 0x0a {
					t.Fatalf("expected 96 kHz SetConfiguration, got %x", packet)
				}
			}
		})
	}
}

func TestNativeAACAutoUsesSinkLimit(t *testing.T) {
	codec := []byte{0, 2, 0x80, 0, 0x84, 0x02, 0xee, 0x00} // 192 kbps
	link := &avdtpTestLink{replies: [][]byte{
		{0x02, discover, 4, 8},
		append([]byte{0x12, getAllCapabilities, 7, 8}, codec...),
		{0x22, setConfiguration},
		{0x32, openStream},
		{0x42, startStream},
		{0x52, suspendStream},
		{0x62, abort},
	}}
	media := &testMedia{}
	var rate int
	err := inspect(context.Background(), link, io.Discard, func() (io.WriteCloser, error) {
		return media, nil
	}, func(_ io.Writer, kbps int) error {
		rate = kbps
		return nil
	}, ipc.NativeStream{Mode: config.ModeAAC, BitrateKbps: 224, AutoAAC: true}, nil)
	if err != nil || rate != 192 {
		t.Fatalf("negotiated %d kbps, error %v", rate, err)
	}
	configuration := link.writes[2]
	if got := configuration[len(configuration)-3:]; !bytes.Equal(got, codec[5:]) {
		t.Fatalf("configured bitrate bytes = %x, want %x", got, codec[5:])
	}
	if got := codecConfiguration(config.ModeAAC, codec, 224); got != nil {
		t.Fatalf("explicit 224 kbps unexpectedly accepted: %x", got)
	}
}

type testMedia struct{ bytes.Buffer }

func (*testMedia) Close() error { return nil }

func TestAVDTPReadHonorsCancellation(t *testing.T) {
	local, remote := net.Pipe()
	defer local.Close()
	defer remote.Close()
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()
	session := avdtpSession{link: local, ctx: ctx}
	done := make(chan error, 1)
	go func() {
		_, err := session.command(discover)
		done <- err
	}()
	_ = remote.SetReadDeadline(time.Now().Add(time.Second))
	if _, err := io.ReadFull(remote, make([]byte, 2)); err != nil {
		t.Fatal(err)
	}
	cancel()
	select {
	case err := <-done:
		if !errors.Is(err, os.ErrDeadlineExceeded) {
			t.Fatalf("expected deadline error, got %v", err)
		}
	case <-time.After(time.Second):
		t.Fatal("AVDTP read did not stop")
	}
}
