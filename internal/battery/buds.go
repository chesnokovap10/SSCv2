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

// BudsDecoder accepts the RFCOMM byte stream in arbitrary chunks. See
// https://github.com/timschneeb/GalaxyBudsClient/blob/master/GalaxyBudsRFCommProtocol.md
type BudsDecoder struct {
	pending []byte
}

func (d *BudsDecoder) Feed(data []byte, report func(BudsLevel)) {
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

func budsReport(body []byte, report func(BudsLevel)) {
	var offset int
	switch body[0] {
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
	level := BudsLevel{Left: percent(body[offset]), Right: percent(body[offset+1])}
	report(level)
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
