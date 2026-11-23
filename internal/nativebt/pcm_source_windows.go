package nativebt

import (
	"context"
	"sync"
	"time"
)

// pcmSource drains the helper away from the packet sender. Its queue retains
// at most two AAC frames; delayed consumers resume from recent PCM.
type pcmSource struct {
	mu           sync.Mutex
	buffer       [8192]byte
	head, queued int
	latest       time.Time
	err          error
}

func (s *pcmSource) store(data []byte, now time.Time) {
	s.mu.Lock()
	defer s.mu.Unlock()
	if now.Sub(s.latest) > 50*time.Millisecond {
		s.head, s.queued = 0, 0
	}
	s.latest = now
	if discard := s.queued + len(data) - len(s.buffer); discard > 0 {
		s.head = (s.head + discard) % len(s.buffer)
		s.queued -= discard
	}
	tail := (s.head + s.queued) % len(s.buffer)
	n := copy(s.buffer[tail:], data)
	copy(s.buffer[:], data[n:])
	s.queued += len(data)
}
func (s *pcmSource) read(b []byte) (int, error) {
	s.mu.Lock()
	defer s.mu.Unlock()
	if time.Since(s.latest) > 50*time.Millisecond {
		s.queued = 0
	}
	n := min(len(b), s.queued)
	first := copy(b[:n], s.buffer[s.head:])
	copy(b[first:n], s.buffer[:])
	s.head = (s.head + n) % len(s.buffer)
	s.queued -= n
	return n, s.err
}
func (s *pcmSource) pump(ctx context.Context, read func(context.Context, []byte) (int, error)) {
	tick := time.NewTicker(5 * time.Millisecond)
	defer tick.Stop()
	var b [4096]byte
	for ctx.Err() == nil {
		n, err := read(ctx, b[:])
		if err != nil {
			s.mu.Lock()
			s.err = err
			s.mu.Unlock()
			return
		}
		if n > 0 {
			s.store(b[:n], time.Now())
		}
		if n == len(b) {
			continue
		}
		select {
		case <-ctx.Done():
			return
		case <-tick.C:
		}
	}
}
