package app

import (
	"fmt"

	"sscv2/internal/bitrate"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
)

// codecChange requires a.mu.
func (a *App) codecChange(m config.Mode) ipc.CodecChange {
	codec := ipc.CodecChange{
		Codec:  m.EngineCodec(),
		SSCUHQ: m == config.ModeSSCUHQ,
		TryUHQ: m == config.ModeSSCUHQ && a.s.AllBitrates,
	}
	if m == config.ModeAAC {
		codec.AACBitrate = a.winUSBBitrate(m)
	} else {
		codec.SSCBitrate = a.winUSBBitrate(m)
	}
	if m == config.ModeSSC {
		codec.SSCMaxKbps, _ = a.workingMax(m)
	}
	return codec
}

// setBitrate stores kbps (0 = auto) for the current codec and applies it.
func (a *App) setBitrate(kbps int) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	m := a.mode
	retryStream := a.st.StreamStartFailed && a.eng == nil && a.native == nil
	if !m.Streaming() || !a.offered(m, kbps) || a.s.Bitrate(m) == kbps && !retryStream {
		a.mu.Unlock()
		return
	}
	a.s.SetBitrate(m, kbps)
	_ = config.Save(a.s)
	defer a.t.RefreshMenu()
	if retryStream {
		a.mu.Unlock()
		a.switchModeLocked(m)
		return
	}
	if p := a.native; p != nil {
		a.mu.Unlock()
		a.changeNativeCodecLocked(p, m)
		return
	}
	codec, eng, streaming := a.codecChange(m), a.eng, a.st.Streaming
	if eng != nil && eng.running() && streaming {
		if err := eng.in.Write(ipc.Command{Cmd: ipc.CommandCodec, Codec: &codec}); err == nil {
			a.mu.Unlock()
			return
		}
	}
	a.mu.Unlock()
	a.restartWinUSBLocked()
}

func (a *App) setMaxMTU(on bool) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	a.s.MaxMTU = on
	if on && a.s.AACMode == "over" {
		a.s.AACMode = ""
	}
	_ = config.Save(a.s)
	a.mu.Unlock()
	a.restartWinUSBLocked()
}

func (a *App) setAllBitrates(on bool) {
	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	m := a.mode
	a.s.AllBitrates = on
	_ = config.Save(a.s)
	blocked, eng := a.noBitrate(m), a.eng
	a.mu.Unlock()
	a.t.RefreshMenu()
	if !blocked && eng == nil && m.Streaming() {
		a.switchModeLocked(m) // the codec was waiting for "All bitrates"
	}
}

func bitrateText(kbps int) string {
	if kbps == 0 {
		return T("Авто", "Auto")
	}
	return fmt.Sprintf(T("%d кбит/с", "%d kbps"), kbps)
}

// autoHint explains what "Auto" means for a codec.
func autoHint(m config.Mode, policy bitrate.Policy, model string, showLimit bool) string {
	if policy.Native {
		return bitrateText(policy.NativeAuto(m))
	}
	limit := policy.WorkingMax
	if limit < 0 {
		return fmt.Sprintf(T("не проверен на %s", "not checked on %s"), model)
	}
	if limit > 0 {
		if showLimit {
			return fmt.Sprintf(T("%d кбит/с - макс. рабочий для %s", "%d kbps - the highest working on %s"), limit, model)
		}
		return bitrateText(limit)
	}
	rate := policy.WinUSBAutoCeiling(m)
	if policy.MaxMTU {
		return bitrateText(rate)
	}
	return fmt.Sprintf(T("%d кбит/с - сколько вмещает пакет", "%d kbps - as much as a packet holds"), rate)
}

// workingMax: the highest bitrate checked to work for a codec on the chosen
// headphones and their model (0, "" = not known). a.mu held.
func (a *App) workingMax(m config.Mode) (int, string) {
	name, id := "", bitrate.DevID{}
	if h := a.s.Headphones; h != nil {
		name = h.Name
		if name == "" {
			if store, err := keys.Open(); err == nil {
				if c, ok := store.FindClassic(h.Addr); ok {
					name = c.Name
				}
			}
		}
		// Device ID as Windows recorded it when the headphones were paired
		if src, vid, pid, _, ok := keys.DeviceID(h.Addr); ok {
			id = bitrate.DevID{Source: src, Vendor: vid, Product: pid}
		}
	}
	return bitrate.WorkingMax(m, id, name)
}

// prefersNativeBitrates uses the running worker when available. a.mu held.
func (a *App) prefersNativeBitrates() bool {
	return a.native != nil || a.eng == nil && a.s.WindowsTestSigning
}

func (a *App) bitratePolicy(m config.Mode, native bool) (bitrate.Policy, string) {
	limit, model := a.workingMax(m)
	if m == config.ModeSSCUHQ && limit == bitrate.Unsupported {
		supported := a.st.SSCUHQSupported
		if native {
			supported = nil
			if a.native != nil {
				supported = a.native.uhqSupported
			}
		}
		if supported != nil && *supported {
			limit = 0
		}
	}
	return bitrate.Policy{Native: native, MaxMTU: a.s.MaxMTU, AllBitrates: a.s.AllBitrates, WorkingMax: limit}, model
}

func (a *App) offered(m config.Mode, kbps int) bool {
	policy, _ := a.bitratePolicy(m, a.prefersNativeBitrates())
	return policy.Offered(m, kbps)
}

// uhqUnavailable requires a.mu.
func (a *App) uhqUnavailable() bool {
	if a.s.AllBitrates {
		return false
	}
	if a.native != nil && a.native.uhqSupported != nil {
		return !*a.native.uhqSupported
	}
	if a.st.Connected && a.st.SSCUHQSupported != nil {
		return !*a.st.SSCUHQSupported
	}
	limit, _ := a.workingMax(config.ModeSSCUHQ)
	return limit == bitrate.Unsupported
}

// nativeStreamLocked requires a.mu.
func (a *App) nativeStreamLocked(mode config.Mode) ipc.NativeStream {
	return ipc.NativeStream{Mode: mode, BitrateKbps: a.nativeBitrateLocked(mode), TryUHQ: mode == config.ModeSSCUHQ && a.s.AllBitrates}
}

// noBitrate: nothing can be offered for the codec on these headphones (not
// supported by their profile, Settings > All bitrates off). a.mu held.
func (a *App) noBitrate(m config.Mode) bool {
	return m.Streaming() && !a.offered(m, 0)
}

// unsupportedText: the status / menu note for such a codec. a.mu held.
func (a *App) unsupportedText(m config.Mode) string {
	_, model := a.workingMax(m)
	return fmt.Sprintf(T("%s не поддерживается %s - включите «Настройки ▸ Все битрейты»",
		"%s is not supported by %s - turn on \"Settings > All bitrates\""), modeName(m), model)
}

// winUSBBitrate requires a.mu.
func (a *App) winUSBBitrate(m config.Mode) int {
	policy, _ := a.bitratePolicy(m, false)
	return policy.Selected(m, a.s.Bitrate(m))
}

func (a *App) nativeBitrateLocked(mode config.Mode) int {
	policy, _ := a.bitratePolicy(mode, true)
	if kbps := policy.Selected(mode, a.s.Bitrate(mode)); kbps != 0 {
		return kbps
	}
	return policy.NativeAuto(mode)
}
