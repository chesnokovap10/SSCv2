// Package battery decodes the battery reports sent by Bluetooth headphones.
package battery

import (
	"bytes"
	"encoding/binary"
	"strings"
	"time"
)

// BudsService is the Galaxy Buds SPPNew RFCOMM service.
const BudsService = "2e73a4ad-332d-41fc-90e2-16bef06523f2"

const (
	PollInterval = time.Minute
	MaxAge       = 2 * PollInterval
)

func IsBuds(name string) bool { return strings.Contains(strings.ToLower(name), "buds") }

// ManagerInfo announces a manager session so the earbuds send extended status.
func ManagerInfo() [10]byte {
	return [10]byte{0xfd, 0x06, 0x10, 0x88, 0x01, 0x01, 0x22, 0xda, 0x58, 0xdd}
}

// BudsLevel holds independent percentages. A negative level is unknown.
type BudsLevel struct {
	Left  int `json:"left"`
	Right int `json:"right"`
}

func (b BudsLevel) Known() bool { return b.Left >= 0 || b.Right >= 0 }

type BudsStatus struct {
	Level        BudsLevel
	Placement    byte   // left in the high nibble; zero means unknown
	Equalizer    *uint8 // confirmed factory preset in an extended status report
	EqualizerAck bool
}

const BudsEqualizerCount = 6

// BudsEqualizerState reconciles the command acknowledgement with extended
// status reports. A report already in flight can still contain the old mode.
type BudsEqualizerState struct {
	current *uint8
	ackAt   time.Time
}

func (e *BudsEqualizerState) Observe(status BudsStatus, now time.Time) *uint8 {
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

// BudsEqualizerRequest selects a factory preset on the SPPNew service.
func BudsEqualizerRequest(preset uint8) [8]byte {
	frame := [8]byte{0xfd, 4, 0x10, 0x86, preset, 0, 0, 0xdd}
	binary.LittleEndian.PutUint16(frame[5:7], budsCRC(frame[3:5]))
	return frame
}

// BudsDecoder accepts the RFCOMM byte stream in arbitrary chunks. See
// https://github.com/timschneeb/GalaxyBudsClient/blob/master/GalaxyBudsRFCommProtocol.md
type BudsDecoder struct {
	pending []byte
}

func (d *BudsDecoder) Feed(data []byte, report func(BudsLevel)) {
	d.FeedStatus(data, func(status BudsStatus) {
		if !status.EqualizerAck {
			report(status.Level)
		}
	})
}

func (d *BudsDecoder) FeedStatus(data []byte, report func(BudsStatus)) {
	d.pending = append(d.pending, data...)
	for {
		start := bytes.IndexByte(d.pending, 0xfd)
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
		if size < 3 {
			d.pending = d.pending[1:]
			continue
		}
		end := 3 + size
		if len(d.pending) <= end {
			return
		}
		body := d.pending[3 : end-2]
		if d.pending[end] != 0xdd || binary.LittleEndian.Uint16(d.pending[end-2:end]) != budsCRC(body) {
			d.pending = d.pending[1:]
			continue
		}
		if header&0x2000 == 0 {
			budsReport(body, report)
		}
		d.pending = d.pending[end+1:]
	}
}

func budsReport(body []byte, report func(BudsStatus)) {
	var offset int
	switch body[0] {
	case 0x42: // Universal acknowledgement
		if len(body) == 3 && body[1] == 0x86 && body[2] < BudsEqualizerCount {
			eq := body[2]
			report(BudsStatus{Level: BudsLevel{Left: -1, Right: -1}, Equalizer: &eq, EqualizerAck: true})
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
	status := BudsStatus{Level: BudsLevel{Left: percent(body[offset]), Right: percent(body[offset+1])}}
	if len(body) > offset+4 {
		status.Placement = body[offset+4]
	}
	if body[0] == 0x61 && len(body) > 10 && body[10] < BudsEqualizerCount {
		eq := body[10] // payload byte 9, excluding the message ID
		status.Equalizer = &eq
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
