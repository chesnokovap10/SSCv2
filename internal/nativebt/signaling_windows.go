package nativebt

import (
	"context"
	"fmt"
	"io"
	"sync"
	"time"
)

type signaledMedia struct {
	io.WriteCloser
	ctx    context.Context
	mu     sync.Mutex
	paused bool
	err    error
	wake   chan struct{}
}

func newSignaledMedia(ctx context.Context, media io.WriteCloser) *signaledMedia {
	return &signaledMedia{WriteCloser: media, ctx: ctx, wake: make(chan struct{})}
}

func (m *signaledMedia) state(paused bool, err error) {
	m.mu.Lock()
	m.paused, m.err = paused, err
	close(m.wake)
	m.wake = make(chan struct{})
	m.mu.Unlock()
	if err != nil {
		m.WriteCloser.Close()
	}
}

func (m *signaledMedia) Write(packet []byte) (int, error) {
	for {
		m.mu.Lock()
		paused, err, wake := m.paused, m.err, m.wake
		m.mu.Unlock()
		if err != nil {
			return 0, err
		}
		if err := m.ctx.Err(); err != nil {
			return 0, err
		}
		if !paused {
			return m.WriteCloser.Write(packet)
		}
		select {
		case <-wake:
		case <-m.ctx.Done():
			return 0, m.ctx.Err()
		}
	}
}

func (p *avdtpSession) watchStreamingCommands(media *signaledMedia) func() {
	link, ok := p.link.(interface{ SetReadDeadline(time.Time) error })
	if !ok {
		return func() {}
	} // in-memory negotiation transports have no asynchronous reader
	// The previous START command left its transaction deadline on this link.
	if err := link.SetReadDeadline(time.Time{}); err != nil {
		media.state(false, err)
		return func() {}
	}
	ctx, cancel := context.WithCancel(p.ctx)
	interrupted := make(chan struct{})
	context.AfterFunc(ctx, func() {
		_ = link.SetReadDeadline(time.Now())
		close(interrupted)
	})
	done := make(chan struct{})
	go func() {
		defer close(done)
		packet := make([]byte, 65535)
		for ctx.Err() == nil {
			n, err := p.link.Read(packet)
			if ctx.Err() != nil {
				return
			}
			if err == nil && n == 0 {
				err = io.ErrUnexpectedEOF
			}
			if err == nil {
				err = p.streamingCommand(media, packet[:n])
			}
			if err != nil {
				media.state(false, err)
				return
			}
		}
	}()
	return func() {
		cancel()
		<-interrupted // Finish the deadline update before Abort reuses the link.
		<-done
	}
}

func (p *avdtpSession) streamingCommand(media *signaledMedia, packet []byte) error {
	if len(packet) < 2 {
		return io.ErrUnexpectedEOF
	}
	if packet[0]&3 != 0 {
		return fmt.Errorf("unsolicited AVDTP response: % x", packet)
	}
	if packet[0]&0x0c != 0 {
		return fmt.Errorf("fragmented streaming AVDTP command unsupported")
	}
	signal := packet[1] & 0x3f
	valid := len(packet) == 3 && packet[2] == 1<<2 // our configured local SEID
	reply := []byte{packet[0]&0xf0 | 2, signal}
	switch signal {
	case startStream, suspendStream, 0x08, abort:
		if !valid {
			reply[0] = packet[0]&0xf0 | 3
			if signal == startStream || signal == suspendStream {
				seid := byte(0)
				if len(packet) > 2 {
					seid = packet[2] & 0xfc
				}
				reply = append(reply, seid)
			}
			reply = append(reply, 0x12)
		}
	default:
		reply[0] = packet[0]&0xf0 | 1
		valid = false
	}
	if link, ok := p.link.(interface{ SetWriteDeadline(time.Time) error }); ok {
		if err := link.SetWriteDeadline(time.Now().Add(time.Second)); err != nil {
			return err
		}
	}
	n, err := p.link.Write(reply)
	if err != nil {
		return err
	}
	if n != len(reply) {
		return io.ErrShortWrite
	}
	if !valid {
		return nil
	}
	switch signal {
	case startStream:
		media.state(false, nil)
	case suspendStream:
		media.state(true, nil)
	default:
		return fmt.Errorf("headphones ended AVDTP stream (signal %#x)", signal)
	}
	return nil
}
