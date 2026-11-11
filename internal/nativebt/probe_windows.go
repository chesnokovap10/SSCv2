package nativebt

import (
	"context"
	"encoding/binary"
	"errors"
	"fmt"
	"io"
	"math"
	"os"
	"strconv"
	"time"

	"golang.org/x/sys/windows"

	"sscv2/internal/codec/aac"
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

func inspect(ctx context.Context, link io.ReadWriter, out io.Writer, openMedia func() (io.WriteCloser, error), send func(io.Writer, io.Writer) error, mode config.Mode, kbps int) error {
	p := probe{link: link}
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
					selectedCodec = probeCodecConfiguration(mode, value, kbps)
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
		return fmt.Errorf("no idle %s sink supports the test configuration", mode)
	}
	return p.checkConfiguration(ctx, out, selectedSEID, selectedCodec, openMedia, send, mode)
}

// MPEG-2 AAC LC, 48 kHz, stereo, constant 192 kbit/s.
const probeAACBitrate = 192000

// MaxAACKbps keeps AAC frames within the Windows Bluetooth media channel.
const MaxAACKbps = 224

func supportsProbeAAC(codec []byte, bitrate int) bool {
	if len(codec) != 8 || codec[0]>>4 != 0 || codec[1] != 2 ||
		codec[2]&0x80 == 0 || codec[4]&0x84 != 0x84 {
		return false
	}
	maxBitrate := int(codec[5]&0x7f)<<16 | int(codec[6])<<8 | int(codec[7])
	return maxBitrate == 0 || maxBitrate >= bitrate
}

func probeCodecConfiguration(mode config.Mode, codec []byte, kbps int) []byte {
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
	if !supportsProbeAAC(codec, int(bitrate)) {
		return nil
	}
	return []byte{0, 2, 0x80, 0, 0x84, byte(bitrate >> 16), byte(bitrate >> 8), byte(bitrate)}
}

func (p *probe) checkConfiguration(ctx context.Context, out io.Writer, seid byte, codec []byte, openMedia func() (io.WriteCloser, error), send func(io.Writer, io.Writer) error, mode config.Mode) (result error) {
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
	if err := send(media, out); err != nil {
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

func sendAACTone(media io.Writer, out io.Writer) error {
	return sendAAC(media, out, probeAACBitrate/1000, 2*48000, "440 Hz test tone", true, func(pcm []int16, offset int) error {
		for i := 0; i < len(pcm)/2; i++ {
			sample := toneSample(offset+i, 2*48000)
			pcm[2*i], pcm[2*i+1] = sample, sample
		}
		return nil
	})
}

func toneSample(index, samples int) int16 {
	envelope := max(0, min(1, float64(min(index, samples-index))/960))
	return int16(2600 * envelope * math.Sin(2*math.Pi*440*float64(index)/48000))
}

func sendAAC(media io.Writer, out io.Writer, kbps, samples int, source string, pace bool, fill func([]int16, int) error) error {
	const sampleRate = 48000
	budget := 600
	if kbps > MaxAACKbps {
		budget = 1005
	}
	encoder, err := aac.New(sampleRate, 2, kbps*1000, budget)
	if err != nil {
		return fmt.Errorf("initialize AAC tone encoder: %w", err)
	}
	defer encoder.Close()

	pcm := make([]int16, encoder.FrameLen*2)
	packet := make([]byte, 12+budget)
	packet[0], packet[1] = 0x80, 0xe0 // RTP v2, marker, dynamic payload type 96.
	binary.BigEndian.PutUint32(packet[8:12], 1)
	started := time.Now()
	var pacer packetPacer
	frameDuration := time.Second * time.Duration(encoder.FrameLen) / sampleRate
	var sequence uint16
	var timestamp uint64
	if samples == 0 {
		defer func() { fmt.Fprintf(out, "Sent %d AAC RTP packets (%s)\n", timestamp/uint64(encoder.FrameLen), source) }()
	}
	for offset := 0; samples == 0 || offset < samples; offset += encoder.FrameLen {
		if err := fill(pcm, offset); err != nil {
			return err
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
		binary.BigEndian.PutUint32(packet[4:8], uint32(timestamp))
		copy(packet[12:], payload)
		if pace {
			pacer.wait(frameDuration)
		}
		size := 12 + len(payload)
		n, err := media.Write(packet[:size])
		if err != nil {
			return fmt.Errorf("write AAC packet %d (%d bytes): %w", sequence, size, err)
		}
		if n != size {
			return io.ErrShortWrite
		}
		if samples == 0 && timestamp == 0 {
			fmt.Fprintln(out, "native-aac-ready")
		}
		sequence++
		timestamp += uint64(encoder.FrameLen)
	}
	if timestamp == 0 {
		return fmt.Errorf("AAC encoder produced no packets")
	}
	finished := started.Add(time.Duration(timestamp) * time.Second / sampleRate)
	if pace {
		finished = pacer.next
	}
	time.Sleep(time.Until(finished.Add(150 * time.Millisecond)))
	fmt.Fprintf(out, "Sent %d AAC RTP packets (%s)\n", timestamp/uint64(encoder.FrameLen), source)
	return nil
}

// Run opens the probe driver interface and runs the requested AAC diagnostic.
func Run(args []string, out io.Writer) error {
	return run(context.Background(), args, out, false, config.ModeAAC)
}

// RunLive streams until ctx is canceled.
func RunLive(ctx context.Context, args []string, out io.Writer, mode config.Mode) error {
	return run(ctx, args, out, true, mode)
}

func run(ctx context.Context, args []string, out io.Writer, live bool, mode config.Mode) error {
	return runWithRender(ctx, args, out, live, mode, nil)
}

func runWithRender(ctx context.Context, args []string, out io.Writer, live bool, mode config.Mode, render *renderPCM) error {
	var loopback time.Duration
	if len(args) >= 2 && args[0] == "-stream-aac" {
		seconds, err := strconv.Atoi(args[1])
		if err != nil || seconds < 1 || seconds > 3600 {
			return fmt.Errorf("stream duration must be 1 to 3600 seconds")
		}
		loopback = time.Duration(seconds) * time.Second
		args = args[2:]
	}
	if live {
		loopback = time.Nanosecond // no frame limit or generated tone
	}
	checkAAC := loopback != 0
	if len(args) > 0 && !checkAAC {
		switch args[0] {
		case "-loopback-aac":
			loopback = -2 * time.Second
			checkAAC = true
		case "-configure-aac":
			checkAAC = true
		}
		if checkAAC {
			args = args[1:]
		}
	}
	if len(args) > 1 || len(args) == 1 && len(args[0]) > 0 && args[0][0] == '-' {
		return fmt.Errorf("usage: [-configure-aac|-loopback-aac|-stream-aac seconds] [profile-driver device interface path]")
	}
	testSigning, err := driver.TestSigning()
	if err != nil {
		return err
	}
	if !testSigning {
		return fmt.Errorf("Windows is not running in test-signing mode")
	}
	var path string
	if len(args) == 1 {
		path = args[0]
	} else {
		path, err = singleInterface()
		if err != nil {
			return err
		}
	}
	connectStarted := time.Now()
	link, err := openChannel(ctx, path, live)
	if err != nil {
		return err
	}
	defer link.Close()
	fmt.Fprintf(out, "AVDTP signaling opened in %v\n", time.Since(connectStarted).Round(time.Millisecond))
	var openMedia func() (io.WriteCloser, error)
	if checkAAC {
		openMedia = func() (io.WriteCloser, error) {
			return openChannel(ctx, path, live)
		}
	}
	kbps := DefaultBitrate(mode)
	if render != nil {
		kbps = render.kbps
	}
	send := sendAACTone
	if render != nil {
		send = func(media io.Writer, out io.Writer) error {
			return sendPCM(media, out, mode, kbps, 0, "Buds WaveRT", true, func(pcm []float32, _ int) error {
				return render.fill(ctx, pcm)
			})
		}
	} else if loopback != 0 {
		send = func(media io.Writer, out io.Writer) error { return sendLoopback(ctx, media, out, loopback, mode) }
	}
	return inspect(ctx, link, out, openMedia, send, mode, kbps)
}

func openChannel(ctx context.Context, path string, live bool) (*os.File, error) {
	deadline := time.Now().Add(5 * time.Second)
	for {
		link, err := os.OpenFile(path, os.O_RDWR, 0)
		if !live || !errors.Is(err, windows.ERROR_REQ_NOT_ACCEP) || time.Now().After(deadline) {
			return link, err
		}
		select {
		case <-ctx.Done():
			return nil, ctx.Err()
		case <-time.After(100 * time.Millisecond):
		}
	}
}
