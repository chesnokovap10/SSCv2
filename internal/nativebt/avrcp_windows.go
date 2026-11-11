package nativebt

import (
	"context"
	"fmt"
	"io"
	"os"
	"time"

	"sscv2/internal/bt"
)

type avrcpPacket struct {
	data []byte
	err  error
}

func avrcpFrame(header, ctype, pdu byte, data ...byte) []byte {
	return append([]byte{header, 0x11, 0x0e, ctype, 0x48, 0, 0, 0x19, 0x58, pdu, 0, 0, byte(len(data))}, data...)
}

// avrcpButton replies to both button states and dispatches only the press.
func avrcpButton(p []byte) (response []byte, key int) {
	if len(p) < 8 || p[0]&0x0f != 0 || p[1] != 0x11 || p[2] != 0x0e ||
		p[3] != 0 || p[4] != 0x48 || p[5] != 0x7c || len(p) != 8+int(p[7]) {
		return nil, 0
	}
	switch p[6] & 0x7f {
	case 0x44, 0x46:
		key = bt.MediaPlayPause
	case 0x45:
		key = bt.MediaStop
	case 0x4b:
		key = bt.MediaNext
	case 0x4c:
		key = bt.MediaPrev
	}
	response = append([]byte(nil), p...)
	response[0] |= 2   // AVCTP response, same transaction label
	response[3] = 0x09 // AV/C accepted
	if key == 0 {
		response[3] = 0x08 // AV/C not implemented
	}
	if p[6]&0x80 != 0 {
		key = 0
	}
	return response, key
}

func watchAVRCP(ctx context.Context, path string, out io.Writer, handleMediaKey func(int)) {
	keys := make(chan int, 8)
	go func() {
		for ctx.Err() == nil {
			select {
			case <-ctx.Done():
				return
			case key := <-keys:
				handleMediaKey(key)
			}
		}
	}()
	var lastError string
	for ctx.Err() == nil {
		err := runAVRCP(ctx, path, out, keys)
		if ctx.Err() != nil {
			return
		}
		if err.Error() != lastError {
			lastError = err.Error()
			fmt.Fprintf(out, "Buds AVRCP unavailable: %v\n", err)
		}
		select {
		case <-ctx.Done():
			return
		case <-time.After(time.Second):
		}
	}
}

// runAVRCP keeps the incoming control channel alive independently of AVDTP.
func runAVRCP(ctx context.Context, path string, out io.Writer, keys chan<- int) error {
	link, err := os.OpenFile(path+"-R", os.O_RDWR, 0)
	if err != nil {
		return fmt.Errorf("accept Buds AVRCP: %w", err)
	}
	defer link.Close()
	fmt.Fprintln(out, "Buds AVRCP channel accepted")
	return serveAVRCP(ctx, link, out, keys)
}

func serveAVRCP(ctx context.Context, link io.ReadWriter, out io.Writer, keys chan<- int) error {
	ctx, cancel := context.WithCancel(ctx)
	defer cancel()
	send := func(data []byte) error {
		n, err := link.Write(data)
		if err == nil && n != len(data) {
			return io.ErrShortWrite
		}
		return err
	}
	// Send before posting a blocking read on the synchronous device handle.
	const volumeHeader = 0x20
	if err := send(avrcpFrame(volumeHeader, 0, 0x50, 127)); err != nil {
		return fmt.Errorf("set Buds AVRCP volume: %w", err)
	}
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
	timeout := time.NewTimer(time.Second)
	defer timeout.Stop()
	confirmation := timeout.C
	for {
		select {
		case <-ctx.Done():
			return ctx.Err()
		case <-confirmation:
			confirmation = nil
			fmt.Fprintln(out, "Buds did not confirm AVRCP volume")
		case packet := <-packets:
			if packet.err != nil {
				return fmt.Errorf("Buds AVRCP read: %w", packet.err)
			}
			p := packet.data
			if response, key := avrcpButton(p); response != nil {
				if err := send(response); err != nil {
					return err
				}
				if key != 0 {
					select {
					case keys <- key:
						fmt.Fprintf(out, "Buds AVRCP button 0x%02x\n", p[6])
					default:
						fmt.Fprintln(out, "Buds AVRCP media command queue full")
					}
				}
				continue
			}
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
			if p[0] == volumeHeader|2 && p[9] == 0x50 && confirmation != nil {
				confirmation = nil
				if p[3] != 0x09 || len(p) < 14 {
					fmt.Fprintln(out, "Buds rejected AVRCP volume")
					continue
				}
				fmt.Fprintf(out, "AVRCP volume acknowledged: %d\n", p[13])
			}
		}
	}
}
