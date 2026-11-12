package audio

import (
	"sync/atomic"
	"time"
)

// Activity tracks the last audible PCM block across capture and playback threads.
type Activity struct {
	lastLoud atomic.Int64
}

func (a *Activity) Observe(samples []float32) {
	for _, sample := range samples {
		if sample > 0.003 || sample < -0.003 { // about -50 dBFS
			a.lastLoud.Store(time.Now().UnixMilli())
			return
		}
	}
}

func (a *Activity) LoudWithin(d time.Duration) bool {
	return time.Now().UnixMilli()-a.lastLoud.Load() < d.Milliseconds()
}

func (a *Activity) PlayingOnLinkLoss() bool {
	return a.LoudWithin(2 * time.Second)
}
