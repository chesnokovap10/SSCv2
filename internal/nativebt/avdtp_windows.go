package nativebt

import (
	"context"
	"encoding/binary"
	"errors"
	"fmt"
	"io"
	"os"
	"time"

	"golang.org/x/sys/windows"

	"sscv2/internal/config"
	"sscv2/internal/driver"
)

const (
	discover           = 0x01
	setConfiguration   = 0x03
	abort              = 0x0a
	openStream         = 0x06
	startStream        = 0x07
	suspendStream      = 0x09
	getAllCapabilities = 0x0c
	getCapabilities    = 0x02
)

// The transport presents one L2CAP SDU per read or write.
type avdtpSession struct {
	link  io.ReadWriter
	label byte
}

type rejection struct {
	messageType byte
	payload     []byte
}

func (r *rejection) Error() string {
	return fmt.Sprintf("AVDTP rejected command (type %d, payload % x)", r.messageType, r.payload)
}

func (p *avdtpSession) command(signal byte, payload ...byte) ([]byte, error) {
	label := p.label
	p.label = (label + 1) & 15
	packet := append([]byte{label << 4, signal}, payload...)
	n, err := p.link.Write(packet)
	if err != nil {
		return nil, err
	}
	if n != len(packet) {
		return nil, io.ErrShortWrite
	}

	reply := make([]byte, 65535)
	n, err = p.link.Read(reply)
	if err != nil {
		return nil, err
	}
	reply = reply[:n]
	if len(reply) == 0 || reply[0]>>4 != label {
		return nil, fmt.Errorf("unexpected AVDTP transaction: % x", reply)
	}
	if reply[0]&0x0c != 0 {
		return nil, fmt.Errorf("fragmented AVDTP response")
	}
	if len(reply) < 2 || reply[1] != signal {
		return nil, fmt.Errorf("unexpected AVDTP signal: % x", reply)
	}
	switch kind := reply[0] & 3; kind {
	case 2:
		return reply[2:], nil
	case 1, 3:
		return nil, &rejection{kind, reply[2:]}
	default:
		return nil, fmt.Errorf("received an AVDTP command while waiting for a response")
	}
}

func inspect(link io.ReadWriter, out io.Writer, openMedia func() (io.WriteCloser, error), send func(io.Writer) error, mode config.Mode, kbps int) error {
	p := avdtpSession{link: link}
	endpoints, err := p.command(discover)
	if err != nil {
		return fmt.Errorf("discover: %w", err)
	}
	if len(endpoints)%2 != 0 {
		return fmt.Errorf("invalid endpoint list: % x", endpoints)
	}
	var selectedSEID byte
	var selectedCodec []byte
	for i := 0; i < len(endpoints); i += 2 {
		seid := endpoints[i] >> 2
		if endpoints[i+1]>>3 != 1 {
			continue // Audio sink only.
		}
		fmt.Fprintf(out, "SEID %d (in use: %t)\n", seid, endpoints[i]&2 != 0)
		caps, err := p.command(getAllCapabilities, seid<<2)
		if reject, ok := err.(*rejection); ok &&
			(reject.messageType == 1 || len(reject.payload) == 1 && reject.payload[0] == 0x19) {
			caps, err = p.command(getCapabilities, seid<<2)
		}
		if err != nil {
			return fmt.Errorf("SEID %d capabilities: %w", seid, err)
		}
		for len(caps) > 0 {
			if len(caps) < 2 || int(caps[1]) > len(caps)-2 {
				return fmt.Errorf("SEID %d: truncated capabilities: % x", seid, caps)
			}
			size := int(caps[1])
			value := caps[2 : 2+size]
			if caps[0] == 7 {
				if len(value) < 2 {
					return fmt.Errorf("SEID %d: truncated media codec", seid)
				}
				fmt.Fprintf(out, "  media type %#x, codec %#02x, data % x\n", value[0]>>4, value[1], value[2:])
				if selectedSEID == 0 && endpoints[i]&2 == 0 && openMedia != nil {
					selectedCodec = codecConfiguration(mode, value, kbps)
					if selectedCodec != nil {
						selectedSEID = seid
					}
				}
			}
			caps = caps[2+size:]
		}
		if selectedSEID != 0 {
			break
		}
	}
	if openMedia == nil {
		return nil
	}
	if selectedSEID == 0 {
		return fmt.Errorf("no idle %s sink supports the requested configuration", mode)
	}
	return p.stream(out, selectedSEID, selectedCodec, openMedia, send, mode)
}

func supportsAAC(codec []byte, bitrate int) bool {
	if len(codec) != 8 || codec[0]>>4 != 0 || codec[1] != 2 ||
		codec[2]&0x80 == 0 || codec[4]&0x84 != 0x84 {
		return false
	}
	maxBitrate := int(codec[5]&0x7f)<<16 | int(codec[6])<<8 | int(codec[7])
	return maxBitrate == 0 || maxBitrate >= bitrate
}

func codecConfiguration(mode config.Mode, codec []byte, kbps int) []byte {
	if mode == config.ModeSSC || mode == config.ModeSSCUHQ {
		rateFlag := byte(0x04)
		if mode == config.ModeSSCUHQ {
			rateFlag = 0x02
		}
		if len(codec) != 9 || codec[0]>>4 != 0 || codec[1] != 0xff ||
			binary.LittleEndian.Uint32(codec[2:6]) != 0x75 ||
			binary.LittleEndian.Uint16(codec[6:8]) != 0x0103 || codec[8]&rateFlag == 0 {
			return nil
		}
		return []byte{0, 0xff, 0x75, 0, 0, 0, 0x03, 0x01, rateFlag | codec[8]&0x08}
	}
	bitrate := uint32(kbps * 1000)
	if !supportsAAC(codec, int(bitrate)) {
		return nil
	}
	return []byte{0, 2, 0x80, 0, 0x84, byte(bitrate >> 16), byte(bitrate >> 8), byte(bitrate)}
}

func (p *avdtpSession) stream(out io.Writer, seid byte, codec []byte, openMedia func() (io.WriteCloser, error), send func(io.Writer) error, mode config.Mode) (result error) {
	const localSEID = 1
	payload := append([]byte{seid << 2, localSEID << 2, 1, 0, 7, byte(len(codec))}, codec...)
	_, err := p.command(setConfiguration, payload...)
	if err != nil {
		return fmt.Errorf("configure %s on SEID %d: %w", mode, seid, err)
	}
	defer func() {
		if _, err := p.command(abort, seid<<2); err != nil {
			result = errors.Join(result, fmt.Errorf("release %s SEID %d: %w", mode, seid, err))
		}
	}()
	if _, err := p.command(openStream, seid<<2); err != nil {
		return fmt.Errorf("open %s stream: %w", mode, err)
	}
	media, err := openMedia()
	if err != nil {
		return fmt.Errorf("open media L2CAP channel: %w", err)
	}
	defer media.Close()
	if _, err := p.command(startStream, seid<<2); err != nil {
		return fmt.Errorf("start %s stream: %w", mode, err)
	}
	if err := send(media); err != nil {
		if errors.Is(err, context.Canceled) {
			return nil // The deferred Abort releases the streaming endpoint.
		}
		return err
	}
	if _, err := p.command(suspendStream, seid<<2); err != nil {
		return fmt.Errorf("suspend %s stream: %w", mode, err)
	}
	fmt.Fprintf(out, "%s media channel opened, started and suspended on SEID %d\n", mode, seid)
	return nil
}

// runAVDTP opens the signaling channel and discovers the remote endpoints.
// If send is provided, it negotiates a media stream and hands it to the sender.
func runAVDTP(ctx context.Context, path string, out io.Writer, retry bool, mode config.Mode, kbps int, send func(io.Writer) error) error {
	started := time.Now()
	link, err := openChannel(ctx, path, retry)
	if err != nil {
		return err
	}
	defer link.Close()
	fmt.Fprintf(out, "AVDTP signaling opened in %v\n", time.Since(started).Round(time.Millisecond))
	var openMedia func() (io.WriteCloser, error)
	if send != nil {
		openMedia = func() (io.WriteCloser, error) {
			return openChannel(ctx, path, retry)
		}
	}
	return inspect(link, out, openMedia, send, mode, kbps)
}

func requireTestSigning() error {
	testSigning, err := driver.TestSigning()
	if err != nil {
		return err
	}
	if !testSigning {
		return fmt.Errorf("Windows is not running in test-signing mode")
	}
	return nil
}

func openChannel(ctx context.Context, path string, retry bool) (*os.File, error) {
	deadline := time.Now().Add(5 * time.Second)
	for {
		link, err := os.OpenFile(path, os.O_RDWR, 0)
		if !retry || !errors.Is(err, windows.ERROR_REQ_NOT_ACCEP) || time.Now().After(deadline) {
			return link, err
		}
		select {
		case <-ctx.Done():
			return nil, ctx.Err()
		case <-time.After(100 * time.Millisecond):
		}
	}
}
