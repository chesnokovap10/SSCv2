package main

import (
	"encoding/binary"
	"errors"
	"fmt"
	"io"
	"math"
	"os"
	"time"

	"sscv2/internal/codec/aac"
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
type probe struct {
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

func (p *probe) command(signal byte, payload ...byte) ([]byte, error) {
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

func inspect(link io.ReadWriter, out io.Writer, openMedia func() (io.WriteCloser, error)) error {
	p := probe{link: link}
	endpoints, err := p.command(discover)
	if err != nil {
		return fmt.Errorf("discover: %w", err)
	}
	if len(endpoints)%2 != 0 {
		return fmt.Errorf("invalid endpoint list: % x", endpoints)
	}
	var aacSEID byte
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
				if aacSEID == 0 && endpoints[i]&2 == 0 && supportsProbeAAC(value) {
					aacSEID = seid
				}
			}
			caps = caps[2+size:]
		}
	}
	if openMedia == nil {
		return nil
	}
	if aacSEID == 0 {
		return fmt.Errorf("no idle AAC sink supports the test configuration")
	}
	return p.checkAACConfiguration(out, aacSEID, openMedia)
}

// MPEG-2 AAC LC, 48 kHz, stereo, constant 192 kbit/s.
const probeAACBitrate = 192000

func supportsProbeAAC(codec []byte) bool {
	if len(codec) != 8 || codec[0]>>4 != 0 || codec[1] != 2 ||
		codec[2]&0x80 == 0 || codec[4]&0x84 != 0x84 {
		return false
	}
	maxBitrate := int(codec[5]&0x7f)<<16 | int(codec[6])<<8 | int(codec[7])
	return maxBitrate == 0 || maxBitrate >= probeAACBitrate
}

func (p *probe) checkAACConfiguration(out io.Writer, seid byte, openMedia func() (io.WriteCloser, error)) (result error) {
	const localSEID = 1
	bitrate := uint32(probeAACBitrate)
	_, err := p.command(setConfiguration, seid<<2, localSEID<<2,
		1, 0, // Media Transport
		7, 8, 0, 2, 0x80, 0, 0x84, byte(bitrate>>16), byte(bitrate>>8), byte(bitrate))
	if err != nil {
		return fmt.Errorf("configure AAC on SEID %d: %w", seid, err)
	}
	defer func() {
		if _, err := p.command(abort, seid<<2); err != nil {
			result = errors.Join(result, fmt.Errorf("release AAC SEID %d: %w", seid, err))
		}
	}()
	if _, err := p.command(openStream, seid<<2); err != nil {
		return fmt.Errorf("open AAC stream: %w", err)
	}
	media, err := openMedia()
	if err != nil {
		return fmt.Errorf("open media L2CAP channel: %w", err)
	}
	defer media.Close()
	if _, err := p.command(startStream, seid<<2); err != nil {
		return fmt.Errorf("start AAC stream: %w", err)
	}
	if err := sendAACTone(media, out); err != nil {
		return err
	}
	if _, err := p.command(suspendStream, seid<<2); err != nil {
		return fmt.Errorf("suspend AAC stream: %w", err)
	}
	fmt.Fprintf(out, "AAC media channel opened, started and suspended on SEID %d\n", seid)
	return nil
}

func sendAACTone(media io.Writer, out io.Writer) error {
	const sampleRate = 48000
	const samples = 2 * sampleRate
	encoder, err := aac.New(sampleRate, 2, probeAACBitrate, 600)
	if err != nil {
		return fmt.Errorf("initialize AAC tone encoder: %w", err)
	}
	defer encoder.Close()

	pcm := make([]int16, encoder.FrameLen*2)
	var packet [612]byte
	packet[0], packet[1] = 0x80, 0xe0 // RTP v2, marker, dynamic payload type 96.
	binary.BigEndian.PutUint32(packet[8:12], 1)
	started := time.Now()
	var sequence uint16
	var timestamp uint32
	for offset := 0; offset < samples; offset += encoder.FrameLen {
		for frame := 0; frame < encoder.FrameLen; frame++ {
			index := offset + frame
			envelope := max(0, min(1, float64(min(index, samples-index))/960))
			sample := int16(2600 * envelope * math.Sin(2*math.Pi*440*float64(index)/sampleRate))
			pcm[2*frame], pcm[2*frame+1] = sample, sample
		}
		payload, err := encoder.Encode(pcm)
		if err != nil {
			return err
		}
		if len(payload) == 0 {
			continue
		}
		if len(payload) > len(packet)-12 {
			return fmt.Errorf("AAC frame exceeds probe packet budget: %d", len(payload))
		}
		binary.BigEndian.PutUint16(packet[2:4], sequence)
		binary.BigEndian.PutUint32(packet[4:8], timestamp)
		copy(packet[12:], payload)
		deadline := started.Add(time.Duration(timestamp) * time.Second / sampleRate)
		time.Sleep(time.Until(deadline))
		size := 12 + len(payload)
		n, err := media.Write(packet[:size])
		if err != nil {
			return fmt.Errorf("write AAC packet %d: %w", sequence, err)
		}
		if n != size {
			return io.ErrShortWrite
		}
		sequence++
		timestamp += uint32(encoder.FrameLen)
	}
	if sequence == 0 {
		return fmt.Errorf("AAC encoder produced no packets")
	}
	time.Sleep(time.Until(started.Add(time.Duration(timestamp)*time.Second/sampleRate + 150*time.Millisecond)))
	fmt.Fprintf(out, "Sent %d AAC RTP packets (440 Hz test tone)\n", sequence)
	return nil
}

func run(args []string) error {
	checkAAC := len(args) == 2 && args[0] == "-configure-aac"
	if checkAAC {
		args = args[1:]
	}
	if len(args) != 1 {
		return fmt.Errorf("usage: avdtp-probe [-configure-aac] <profile-driver device interface path>")
	}
	link, err := os.OpenFile(args[0], os.O_RDWR, 0)
	if err != nil {
		return err
	}
	defer link.Close()
	var openMedia func() (io.WriteCloser, error)
	if checkAAC {
		openMedia = func() (io.WriteCloser, error) {
			return os.OpenFile(args[0], os.O_RDWR, 0)
		}
	}
	return inspect(link, os.Stdout, openMedia)
}

func main() {
	if err := run(os.Args[1:]); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}
