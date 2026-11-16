package buds

import "time"

const RemovalDelay = 400 * time.Millisecond

// Removal detects the transition from worn to both known out of ear.
// Use one instance per RFCOMM connection.
type Removal struct {
	armed    bool
	deadline time.Time
}

func (r *Removal) Observe(placement byte, now time.Time) time.Time {
	left, right := placement>>4, placement&15
	switch {
	case left == 1 || right == 1:
		r.armed = true
		r.deadline = time.Time{}
	case left < 2 || left > 4 || right < 2 || right > 4:
		r.deadline = time.Time{}
	case r.armed && r.deadline.IsZero():
		r.deadline = now.Add(RemovalDelay)
	}
	return r.deadline
}

func (r *Removal) Deadline() time.Time { return r.deadline }

func (r *Removal) Confirm(now time.Time) bool {
	if r.deadline.IsZero() || now.Before(r.deadline) {
		return false
	}
	r.armed = false
	r.deadline = time.Time{}
	return true
}
