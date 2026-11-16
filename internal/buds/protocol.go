package buds

import (
	"encoding/binary"
	"strings"
)

// Protocol describes the RFCOMM service and message layout. The default
// probes Samsung's dedicated SPPNew UUID, even if the device has been renamed.
type Protocol uint8

const (
	SPPNew Protocol = iota
	SPPStandard
	PlusSPP
	LegacySPP
)

func ProtocolForName(name string) Protocol {
	name = strings.ToLower(strings.TrimSpace(name))
	name = strings.TrimPrefix(name, "samsung ")
	name = strings.TrimPrefix(name, "galaxy ")
	switch {
	case strings.HasPrefix(name, "buds+") || strings.HasPrefix(name, "buds plus"):
		return PlusSPP
	case strings.HasPrefix(name, "buds live") || strings.HasPrefix(name, "buds pro"):
		return SPPStandard
	case name == "buds" || strings.HasPrefix(name, "buds ("):
		return LegacySPP
	default:
		return SPPNew
	}
}

func (p Protocol) Service() string {
	switch p {
	case SPPStandard, PlusSPP:
		return "00001101-0000-1000-8000-00805f9b34fb"
	case LegacySPP:
		return "00001102-0000-1000-8000-00805f9b34fd"
	default:
		return sppNewService
	}
}

func (p Protocol) markers() (start, end byte) {
	if p == LegacySPP {
		return 0xfe, 0xee
	}
	return 0xfd, 0xdd
}

func (p Protocol) request(id byte, payload ...byte) []byte {
	start, end := p.markers()
	size := byte(len(payload) + 3)
	header := []byte{start, size, 0x10, id}
	if p == LegacySPP {
		header[1], header[2] = 0, size
	}
	frame := append(header, payload...)
	frame = binary.LittleEndian.AppendUint16(frame, budsCRC(frame[3:]))
	return append(frame, end)
}

func (p Protocol) ManagerInfo() []byte { return p.request(0x88, 1, 1, 0x22) }

func (p Protocol) EqualizerRequest(preset uint8) []byte {
	if p != LegacySPP {
		return p.request(0x86, preset)
	}
	if preset == 0 {
		return p.request(0x86, 0, 5)
	}
	return p.request(0x86, 1, preset+4)
}

func (p Protocol) reportedEqualizer(body []byte) *uint8 {
	var preset uint8
	switch p {
	case LegacySPP:
		if len(body) <= 12 || body[11] > 1 || body[12] > 9 {
			return nil
		}
		if body[11] == 1 {
			preset = body[12]%5 + 1
		}
	case PlusSPP:
		if len(body) <= 12 {
			return nil
		}
		preset = body[12]
	default:
		if len(body) <= 10 {
			return nil
		}
		preset = body[10]
	}
	if preset >= EqualizerCount && preset != EqualizerCustom {
		return nil
	}
	return &preset
}
