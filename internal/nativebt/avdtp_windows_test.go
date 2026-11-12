package nativebt

import (
	"bytes"
	"io"
	"testing"

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
			err := inspect(link, io.Discard, func() (io.WriteCloser, error) {
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
