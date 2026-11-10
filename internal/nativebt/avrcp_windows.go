package nativebt

import (
	"context"
	"fmt"
	"io"
	"os"
	"time"

	"sscv2/internal/audio"
)

type avrcpPacket struct {
	data []byte
	err  error
}

func avrcpFrame(header, ctype, pdu byte, data ...byte) []byte {
	return append([]byte{header, 0x11, 0x0e, ctype, 0x48, 0, 0, 0x19, 0x58, pdu, 0, 0, byte(len(data))}, data...)
}

// runAVRCP keeps the incoming control channel alive independently of AVDTP.
func runAVRCP(ctx context.Context, path, endpoint string, ready func(), out io.Writer) error {
	link, err := os.OpenFile(path+"-R", os.O_RDWR, 0)
	if err != nil {
		return fmt.Errorf("accept Buds AVRCP: %w", err)
	}
	defer link.Close()
	fmt.Fprintln(out, "Buds AVRCP channel accepted")
	packets := make(chan avrcpPacket, 1)
	go func() {
		for {
			buf := make([]byte, 512)
			n, err := link.Read(buf)
			select {
			case packets <- avrcpPacket{buf[:n], err}:
			case <-ctx.Done():
				return
			}
			if err != nil {
				return
			}
		}
	}()
	send := func(data []byte) error { _, err := link.Write(data); return err }
	if err := send(avrcpFrame(0x10, 1, 0x10, 3)); err != nil {
		return err
	}
	ticker := time.NewTicker(25 * time.Millisecond)
	defer ticker.Stop()
	capability := false
	pending := false
	last := -1
	label := byte(1)
	var deadline time.Time
	for {
		select {
		case <-ctx.Done():
			return ctx.Err()
		case <-ticker.C:
			if pending && time.Now().After(deadline) {
				return fmt.Errorf("Buds did not confirm AVRCP volume")
			}
			if !capability || pending {
				continue
			}
			scalar, muted, err := audio.EndpointVolume(endpoint)
			if err != nil {
				return err
			}
			level := int(audio.ScalarTo127(scalar))
			if muted {
				level = 0
			}
			if level == last {
				continue
			}
			label = (label + 1) & 15
			if err := send(avrcpFrame(label<<4, 0, 0x50, byte(level))); err != nil {
				return err
			}
			last, pending, deadline = level, true, time.Now().Add(time.Second)
		case packet := <-packets:
			if packet.err != nil {
				return fmt.Errorf("Buds AVRCP read: %w", packet.err)
			}
			p := packet.data
			if len(p) < 13 || p[1] != 0x11 || p[2] != 0x0e || p[5] != 0 || p[6] != 0 || p[7] != 0x19 || p[8] != 0x58 {
				continue
			}
			if p[0]&2 == 0 {
				header := p[0] | 2
				var response []byte
				switch p[9] {
				case 0x10:
					if len(p) < 14 {
						continue
					}
					if p[13] == 3 {
						response = avrcpFrame(header, 0x0c, 0x10, 3, 1, 1)
					} else {
						response = avrcpFrame(header, 0x0c, 0x10, 2, 1, 0, 0x19, 0x58)
					}
				case 0x30:
					response = avrcpFrame(header, 0x0c, 0x30, 0, 0, 0, 0, 0, 0, 0, 0, 2)
				case 0x31:
					if len(p) < 14 {
						continue
					}
					if p[13] == 1 {
						response = avrcpFrame(header, 0x0f, 0x31, 1, 2)
					} else {
						response = avrcpFrame(header, 0x0a, 0x31, 0)
					}
				default:
					response = avrcpFrame(header, 0x08, p[9])
				}
				if err := send(response); err != nil {
					return err
				}
				continue
			}
			if p[0] == 0x12 && p[9] == 0x10 && p[3] == 0x0c {
				capability = true
			}
			if p[0] == (label<<4|2) && p[9] == 0x50 && pending {
				if p[3] != 0x09 || len(p) < 14 {
					return fmt.Errorf("Buds rejected AVRCP volume")
				}
				pending = false
				ready()
				fmt.Fprintf(out, "AVRCP volume acknowledged: %d\n", p[13])
			}
		}
	}
}
