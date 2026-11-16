package buds

import "encoding/binary"

const (
	noiseControlUpdate  = 0x77
	noiseControlCommand = 0x78
)

const (
	NoiseOff uint8 = iota
	NoiseANC
	NoiseAmbient
	NoiseAdaptive
)

const NoiseUnknown uint8 = 0xff

type NoiseControl struct {
	Mode     uint8 `json:"mode"`
	Modes    uint8 `json:"modes"`
	Fallback bool  `json:"fallback,omitempty"`
}

func (c *NoiseControl) Allows(mode uint8) bool {
	return c != nil && mode < c.Modes && mode <= NoiseAdaptive
}

func (c *NoiseControl) UsesFallback() bool { return c != nil && c.Fallback }

func (c *NoiseControl) Request(protocol Protocol, mode uint8) []byte {
	return c.RequestWithCommands(protocol, ControlCommands{}, mode)
}

func (c *NoiseControl) RequestWithCommands(protocol Protocol, commands ControlCommands, mode uint8) []byte {
	if !c.Allows(mode) {
		return nil
	}
	return protocol.request(commands.WithDefaults().Noise, mode)
}

func (d *Decoder) decodeNoiseControl(body []byte) *NoiseControl {
	if modes := d.Commands.NoiseModes; modes > 0 && modes <= NoiseAdaptive+1 {
		d.noiseModes, d.noiseFallback = modes, false
		if len(body) > 13 && body[13] < modes && d.Protocol != PlusSPP && d.Protocol != LegacySPP {
			return d.noiseControl(body[13])
		}
		return d.noiseControl(NoiseUnknown)
	}
	if (d.Protocol != SPPNew && d.Protocol != SPPStandard) || len(body) < 19 {
		return nil
	}
	// Extended status carries the current mode at payload[12] and the
	// Samsung device/color IDs at payload[14:18]. The latter distinguish
	// devices with unified noise controls even if they have been renamed.
	left := noiseModes(binary.LittleEndian.Uint16(body[15:17]))
	right := noiseModes(binary.LittleEndian.Uint16(body[17:19]))
	// A negative entry identifies a known model with a different command.
	if left < 0 || right < 0 {
		d.noiseModes, d.noiseFallback = 0, false
		return nil
	}
	modes := max(left, right)
	mode := body[13]
	fallback := modes == 0
	if fallback {
		modes = int(NoiseAdaptive) + 1
	}
	d.noiseModes, d.noiseFallback = uint8(modes), fallback
	if fallback && mode >= d.noiseModes {
		mode = NoiseUnknown
	}
	return d.noiseControl(mode)
}

func noiseModes(device uint16) int {
	switch {
	case device >= 278 && device <= 284: // Buds Live
		return -1
	case device >= 298 && device <= 301: // Buds Pro
		return 3
	case device >= 313 && device <= 321 || device == 14337: // Buds2
		return 3
	case device >= 325 && device <= 328: // Buds2 Pro
		return 3
	case device == 330 || device == 331: // Buds FE
		return 3
	case device == 333 || device == 334: // Buds3
		return 3
	case device == 340 || device == 341: // Buds3 Pro
		return 4
	default:
		return 0
	}
}

func (d *Decoder) noiseControl(mode uint8) *NoiseControl {
	if mode >= d.noiseModes && !(d.noiseModes > 0 && mode == NoiseUnknown) {
		return nil
	}
	return &NoiseControl{Mode: mode, Modes: d.noiseModes, Fallback: d.noiseFallback}
}

func (d *Decoder) reportNoiseUpdate(mode uint8, report func(Status)) {
	if mode > NoiseAdaptive {
		return
	}
	if control := d.noiseControl(mode); control != nil {
		report(Status{Level: Level{Left: -1, Right: -1}, NoiseControl: control, ControlOnly: true})
	}
}
