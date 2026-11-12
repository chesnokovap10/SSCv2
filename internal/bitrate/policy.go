// Package bitrate selects codec bitrates for the WinUSB and Windows Bluetooth
// transports. Rates are in kbps unless the name says otherwise.
package bitrate

import (
	"sscv2/internal/codec/ssc"
	"sscv2/internal/codec/sscrate"
	"sscv2/internal/config"
)

const (
	MaxAACKbps        = 256
	MaxNativeAACKbps  = 224
	WinUSBExtendedMTU = 1017

	standardPayload = 667 // 679-byte media MTU announced by Galaxy Buds
	extendedPayload = WinUSBExtendedMTU - 12
)

type Policy struct {
	Native      bool
	MaxMTU      bool
	AllBitrates bool
	WorkingMax  int
}

// Choices lists the selectable rates for a mode. Zero selects Auto.
func Choices(mode config.Mode) []int {
	switch mode {
	case config.ModeAAC:
		return []int{0, 128, 160, 192, MaxNativeAACKbps, MaxAACKbps}
	case config.ModeSSC, config.ModeSSCUHQ:
		return append([]int{0}, sscrate.Kbps(sscSampleRate(mode))...)
	default:
		return nil
	}
}

func (p Policy) Offered(mode config.Mode, kbps int) bool {
	if !p.AllBitrates && (p.WorkingMax < 0 || p.WorkingMax > 0 && kbps > p.WorkingMax) {
		return false
	}
	if p.Native && !p.AllBitrates && mode == config.ModeAAC && kbps > MaxNativeAACKbps {
		return false
	}
	extended := p.MaxMTU
	if p.Native {
		extended = p.AllBitrates
	}
	if kbps == 0 {
		return mode.Streaming()
	}
	if kbps < 0 {
		return false
	}
	packetPayload := payload(extended)
	switch mode {
	case config.ModeAAC:
		return kbps <= aacCeiling(packetPayload)
	case config.ModeSSC, config.ModeSSCUHQ:
		return ssc.FrameBytes(sscSampleRate(mode), kbps*1000) <= packetPayload
	default:
		return false
	}
}

// Selected resolves a saved choice to Auto when the current transport or
// headphones cannot use it.
func (p Policy) Selected(mode config.Mode, saved int) int {
	if p.Offered(mode, saved) {
		return saved
	}
	return 0
}

// Experimental marks rates outside the model profile or the native defaults.
func (p Policy) Experimental(mode config.Mode, kbps int) bool {
	if p.WorkingMax < 0 || p.WorkingMax > 0 && kbps > p.WorkingMax {
		return true
	}
	if !p.Native {
		return false
	}
	standard := Policy{Native: true}
	return !standard.Offered(mode, kbps)
}

func (p Policy) NativeAuto(mode config.Mode) int {
	if mode == config.ModeAAC {
		return MaxNativeAACKbps
	}
	if best := BestSSC(sscSampleRate(mode), standardPayload, p.WorkingMax); best != 0 {
		return best
	}
	return NativeDiagnosticDefault(mode)
}

// WinUSBAutoCeiling is the nominal Auto rate shown before the sink's MTU and
// codec capabilities are known. The engine uses the negotiated values.
func (p Policy) WinUSBAutoCeiling(mode config.Mode) int {
	packetPayload := payload(p.MaxMTU)
	if mode == config.ModeAAC {
		return min(MaxAACKbps, aacCeiling(packetPayload))
	}
	return BestSSC(sscSampleRate(mode), packetPayload, 0)
}

func NativeDiagnosticDefault(mode config.Mode) int {
	switch mode {
	case config.ModeSSC:
		return 128
	case config.ModeSSCUHQ:
		return 152
	default:
		return 192
	}
}

func NativeAACBudget(kbps int) int {
	if kbps > MaxNativeAACKbps {
		return extendedPayload
	}
	return 600
}

// BestSSC returns the highest encoder rate within the payload and rate
// limits. A nonpositive limit leaves the rate unrestricted.
func BestSSC(sampleRate, packetPayload, limit int) int {
	best := 0
	for _, kbps := range sscrate.Kbps(sampleRate) {
		if (limit <= 0 || kbps <= limit) && ssc.FrameBytes(sampleRate, kbps*1000) <= packetPayload {
			best = kbps
		}
	}
	return best
}

func sscSampleRate(mode config.Mode) int {
	if mode == config.ModeSSCUHQ {
		return 96000
	}
	return 48000
}

func payload(extended bool) int {
	if extended {
		return extendedPayload
	}
	return standardPayload
}

func aacCeiling(packetPayload int) int {
	return packetPayload * 8 * 48000 / (1024 * 1000)
}
