package engine

import (
	"sync"
	"time"
)

type captureBlock struct {
	samples              []float32
	frames               int
	gap                  bool
	at                   time.Time
	sequence, generation uint64
}

type captureQueue struct {
	blocks   chan *captureBlock
	pool     sync.Pool
	sequence uint64 // WASAPI producer only
	done     chan struct{}
}

func newCaptureQueue(consume func(*captureBlock)) *captureQueue {
	q := &captureQueue{blocks: make(chan *captureBlock, 4), done: make(chan struct{})}
	q.pool.New = func() any { return &captureBlock{} }
	go func() {
		defer close(q.done)
		var last uint64
		for b := range q.blocks {
			if time.Since(b.at) <= 40*time.Millisecond {
				b.gap = b.gap || b.sequence != last+1
				consume(b)
				last = b.sequence
			}
			q.pool.Put(b)
		}
	}()
	return q
}
func (q *captureQueue) push(samples []float32, frames int, gap bool, at time.Time, generation uint64) {
	q.sequence++
	b := q.pool.Get().(*captureBlock)
	b.samples = append(b.samples[:0], samples...)
	b.frames, b.gap, b.at, b.generation, b.sequence = frames, gap, at, generation, q.sequence
	select {
	case q.blocks <- b:
		return
	default:
	}
	// There is one producer; after dropping an old block a slot is guaranteed.
	select {
	case old := <-q.blocks:
		q.pool.Put(old)
	default:
	}
	q.blocks <- b
}
func (q *captureQueue) close() { close(q.blocks); <-q.done }
