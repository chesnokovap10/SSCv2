// Package buds implements the Galaxy Buds control protocol over RFCOMM.
package buds

import (
	"bytes"
	"encoding/binary"
	"time"
)

// sppNewService is the Galaxy Buds SPPNew RFCOMM service.
const sppNewService = "2e73a4ad-332d-41fc-90e2-16bef06523f2"

const (
	PollInterval = time.Minute
	MaxAge       = 2 * PollInterval
)

// Level holds independent percentages. A negative level is unknown.
type Level struct {
	Left  int `json:"left"`
	Right int `json:"right"`
}

func (b Level) Known() bool { return b.Left >= 0 || b.Right >= 0 }

type Status struct {
	Level        Level
	Placement    byte   // left in the high nibble; zero means unknown
	Equalizer    *uint8 // confirmed factory preset in an extended status report
	EqualizerAck bool
}

const EqualizerCount = 6
const EqualizerCustom = 7

// EqualizerState reconciles the command acknowledgement with extended
// status reports. A report already in flight can still contain the old mode.
type EqualizerState struct {
	current *uint8
	ackAt   time.Time
}

func (e *EqualizerState) Current() *uint8 { return e.current }

func (e *EqualizerState) Observe(status Status, now time.Time) *uint8 {
	if status.Equalizer == nil {
		return nil
	}
	if status.EqualizerAck {
		e.ackAt = now
	} else if e.current != nil && *e.current != *status.Equalizer && now.Sub(e.ackAt) < 2*time.Second {
		return nil
	}
	e.current = status.Equalizer
	return e.current
}

// Decoder accepts the RFCOMM byte stream in arbitrary chunks. See
// https://github.com/timschneeb/GalaxyBudsClient/blob/master/GalaxyBudsRFCommProtocol.md
type Decoder struct {
	Protocol Protocol
	pending  []byte
}

func (d *Decoder) Feed(data []byte, report func(Level)) {
	d.FeedStatus(data, func(status Status) {
		if !status.EqualizerAck {
			report(status.Level)
		}
	})
}

func (d *Decoder) FeedStatus(data []byte, report func(Status)) {
	d.pending = append(d.pending, data...)
	startMarker, endMarker := d.Protocol.markers()
	for {
		start := bytes.IndexByte(d.pending, startMarker)
		if start < 0 {
			d.pending = d.pending[:0]
			return
		}
		d.pending = d.pending[start:]
		if len(d.pending) < 3 {
			return
		}
		header := binary.LittleEndian.Uint16(d.pending[1:3])
		size := int(header & 0x3ff)
		if d.Protocol == LegacySPP {
			size = int(d.pending[2])
		}
		if size < 3 {
			d.pending = d.pending[1:]
			continue
		}
		end := 3 + size
		if len(d.pending) <= end {
			return
		}
		body := d.pending[3 : end-2]
		if d.pending[end] != endMarker || binary.LittleEndian.Uint16(d.pending[end-2:end]) != budsCRC(body) {
			d.pending = d.pending[1:]
			continue
		}
		if d.Protocol == LegacySPP || header&0x2000 == 0 {
			d.budsReport(body, report)
		}
		d.pending = d.pending[end+1:]
	}
}

func (d *Decoder) budsReport(body []byte, report func(Status)) {
	var offset int
	switch body[0] {
	case 0x42: // Universal acknowledgement
		if d.Protocol != LegacySPP && len(body) == 3 && body[1] == 0x86 && body[2] < EqualizerCount {
			eq := body[2]
			report(Status{Level: Level{Left: -1, Right: -1}, Equalizer: &eq, EqualizerAck: true})
		}
		return
	case 0x60: // Status Updated
		offset = 2
	case 0x61: // Extended Status Updated
		offset = 3
	default:
		return
	}
	if len(body) < offset+2 {
		return
	}
	status := Status{Level: Level{Left: percent(body[offset]), Right: percent(body[offset+1])}}
	if len(body) > offset+4 {
		status.Placement = body[offset+4]
		if d.Protocol == LegacySPP {
			// The first generation reports worn bits rather than placement enums.
			v := status.Placement
			if v&^0x11 == 0 {
				status.Placement = (2-(v&1))<<4 | (2 - (v >> 4))
			} else {
				status.Placement = 0
			}
		}
	}
	if body[0] == 0x61 {
		status.Equalizer = d.Protocol.reportedEqualizer(body)
	}
	report(status)
}

func percent(raw byte) int {
	if raw > 100 {
		return -1
	}
	return int(raw)
}

func budsCRC(data []byte) uint16 {
	var crc uint16
	for _, b := range data {
		crc ^= uint16(b) << 8
		for range 8 {
			if crc&0x8000 != 0 {
				crc = crc<<1 ^ 0x1021
			} else {
				crc <<= 1
			}
		}
	}
	return crc
}
