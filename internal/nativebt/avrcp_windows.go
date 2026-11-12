package nativebt

import (
	"context"
	"fmt"
	"io"
	"os"
	"runtime"
	"syscall"
	"time"

	"golang.org/x/sys/windows"

	"sscv2/internal/audio"
	"sscv2/internal/bt"
)

type avrcpPacket struct {
	data []byte
	err  error
}

type avrcpDevice struct {
	*os.File
	raw syscall.RawConn
}

// os.File serializes reads and writes for Windows device handles, even with
// overlapped I/O. Write directly while the Go reader waits for AVRCP traffic.
func (link avrcpDevice) Write(data []byte) (int, error) {
	event, err := windows.CreateEvent(nil, 1, 0, nil)
	if err != nil {
		return 0, err
	}
	defer windows.CloseHandle(event)
	// The low bit suppresses IOCP notification for this operation. Its
	// completion is consumed here, independently of Go's runtime poller.
	op := windows.Overlapped{HEvent: event | 1}
	var pin runtime.Pinner
	pin.Pin(&op)
	if len(data) != 0 {
		pin.Pin(&data[0])
	}
	defer pin.Unpin()
	var written uint32
	var writeErr error
	err = link.raw.Control(func(fd uintptr) {
		handle := windows.Handle(fd)
		writeErr = windows.WriteFile(handle, data, &written, &op)
		if writeErr != windows.ERROR_IO_PENDING {
			return
		}
		status, waitErr := windows.WaitForSingleObject(event, 1000)
		if waitErr == nil && status == windows.WAIT_OBJECT_0 {
			writeErr = windows.GetOverlappedResult(handle, &op, &written, false)
			return
		}
		_ = windows.CancelIoEx(handle, &op)
		_ = windows.GetOverlappedResult(handle, &op, &written, true)
		writeErr = waitErr
		if writeErr == nil {
			writeErr = os.ErrDeadlineExceeded
		}
	})
	if err != nil {
		return 0, err
	}
	return int(written), writeErr
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
	case 0x44:
		key = bt.MediaPlayPause
	case 0x46:
		key = bt.MediaPause
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

func watchAVRCP(ctx context.Context, path string, out io.Writer, handleMediaKey func(int), volume *budsVolume, activity *audio.Activity) {
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
		err := runAVRCP(ctx, path, out, keys, volume, activity)
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
func runAVRCP(ctx context.Context, path string, out io.Writer, keys chan<- int, volume *budsVolume, activity *audio.Activity) error {
	// Volume changes must be able to write while a read waits for a button.
	link, err := os.OpenFile(path+"-R", os.O_RDWR|windows.O_FILE_FLAG_OVERLAPPED, 0)
	if err != nil {
		return fmt.Errorf("accept Buds AVRCP: %w", err)
	}
	defer link.Close()
	raw, err := link.SyscallConn()
	if err != nil {
		return err
	}
	stopClose := context.AfterFunc(ctx, func() { _ = link.Close() })
	defer stopClose()
	fmt.Fprintln(out, "Buds AVRCP channel accepted")
	return serveAVRCP(ctx, avrcpDevice{File: link, raw: raw}, out, keys, volume, activity)
}

func serveAVRCP(ctx context.Context, link io.ReadWriter, out io.Writer, keys chan<- int, volume *budsVolume, activity *audio.Activity) error {
	ctx, cancel := context.WithCancel(ctx)
	defer cancel()
	defer volume.hardware.Store(false)
	send := func(data []byte) error {
		n, err := link.Write(data)
		if err == nil && n != len(data) {
			return io.ErrShortWrite
		}
		return err
	}
	var volumeHeader byte
	attempted := int32(-1)
	timeout := time.NewTimer(time.Second)
	timeout.Stop()
	defer timeout.Stop()
	var confirmation <-chan time.Time
	playbackStatus := func() byte {
		if activity.LoudWithin(3 * time.Second) {
			return 1 // playing
		}
		return 2 // paused
	}
	statusTicker := time.NewTicker(100 * time.Millisecond)
	defer statusTicker.Stop()
	var statusUpdates <-chan time.Time
	var statusHeader, registeredStatus byte
	sendVolume := func(level int32) error {
		attempted = level
		volumeHeader += 0x10 // next AVCTP transaction label
		if err := send(avrcpFrame(volumeHeader, 0, 0x50, byte(level))); err != nil {
			return fmt.Errorf("set Buds AVRCP volume: %w", err)
		}
		timeout.Reset(time.Second)
		confirmation = timeout.C
		return nil
	}
	if err := sendVolume(volume.target()); err != nil {
		return err
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
	for {
		if target := volume.target(); confirmation == nil && target != attempted {
			if err := sendVolume(target); err != nil {
				return err
			}
		}
		select {
		case <-ctx.Done():
			return ctx.Err()
		case <-volume.wake:
		case <-statusUpdates:
			if status := playbackStatus(); status != registeredStatus {
				statusUpdates = nil // AVRCP notifications are one-shot.
				if err := send(avrcpFrame(statusHeader, 0x0d, 0x31, 1, status)); err != nil {
					return err
				}
			}
		case <-confirmation:
			confirmation = nil
			volume.hardware.Store(false)
			fmt.Fprintln(out, "Buds did not confirm AVRCP volume")
		case packet := <-packets:
			if packet.err != nil {
				return fmt.Errorf("Buds AVRCP read: %w", packet.err)
			}
			p := packet.data
			if response, key := avrcpButton(p); response != nil {
				if key != 0 {
					select {
					case keys <- key:
						fmt.Fprintf(out, "Buds AVRCP button 0x%02x\n", p[6])
					default:
						fmt.Fprintln(out, "Buds AVRCP media command queue full")
					}
				}
				if err := send(response); err != nil {
					return err
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
					response = avrcpFrame(header, 0x0c, 0x30, 0, 0, 0, 0, 0, 0, 0, 0, playbackStatus())
				case 0x31:
					if len(p) < 14 {
						continue
					}
					if p[13] == 1 {
						statusHeader, registeredStatus = header, playbackStatus()
						statusUpdates = statusTicker.C
						response = avrcpFrame(header, 0x0f, 0x31, 1, registeredStatus)
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
				timeout.Stop()
				confirmation = nil
				if p[3] != 0x09 || len(p) < 14 {
					volume.hardware.Store(false)
					fmt.Fprintln(out, "Buds rejected AVRCP volume")
					continue
				}
				actual := int32(p[13])
				if actual > min(attempted+budsVolumeStepTolerance, 127) || actual < attempted-budsVolumeStepTolerance || (actual == 0) != (attempted == 0) {
					volume.hardware.Store(false)
					fmt.Fprintf(out, "Buds AVRCP volume mismatch: requested %d, got %d\n", attempted, actual)
					continue
				}
				volume.hardware.Store(true)
				fmt.Fprintf(out, "AVRCP volume acknowledged: %d\n", actual)
			}
		}
	}
}
