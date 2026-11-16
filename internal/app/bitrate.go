package app

import (
	"fmt"

	"sscv2/internal/bitrate"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
	"sscv2/internal/profiles"
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
		codec.AACMaxKbps, _ = a.workingMaxFor(m, false)
	} else {
		codec.SSCBitrate = a.winUSBBitrate(m)
		codec.SSCMaxKbps, _ = a.workingMaxFor(m, false)
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
	a.mu.Unlock()
	if eng != nil && eng.running() && streaming {
		if err := eng.in.Write(ipc.Command{Cmd: ipc.CommandCodec, Codec: &codec}); err == nil {
			return
		}
	}
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
	return a.workingMaxFor(m, a.prefersNativeBitrates())
}

func (a *App) workingMaxFor(m config.Mode, native bool) (int, string) {
	name, id := "", profiles.DevID{}
	if h := a.s.Headphones; h != nil {
		name = profileDeviceName(h)
		// Device ID as Windows recorded it when the headphones were paired
		id = profileDeviceID(h.Addr)
	}
	return a.deviceProfiles.WorkingMax(m, id, name, native)
}

// prefersNativeBitrates uses the running worker when available. a.mu held.
func (a *App) prefersNativeBitrates() bool {
	return a.native != nil || a.eng == nil && a.s.WindowsTestSigning
}

func (a *App) bitratePolicy(m config.Mode, native bool) (bitrate.Policy, string) {
	return a.bitratePolicyWith(m, native, func(codec config.Mode) (int, string) { return a.workingMaxFor(codec, native) })
}

func (a *App) bitratePolicyWith(m config.Mode, native bool, workingMax func(config.Mode) (int, string)) (bitrate.Policy, string) {
	limit, model := workingMax(m)
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
	return a.uhqUnavailableWith(a.workingMax)
}

func (a *App) uhqUnavailableWith(workingMax func(config.Mode) (int, string)) bool {
	if a.s.AllBitrates {
		return false
	}
	if a.native != nil && a.native.uhqSupported != nil {
		return !*a.native.uhqSupported
	}
	if a.st.Connected && a.st.SSCUHQSupported != nil {
		return !*a.st.SSCUHQSupported
	}
	limit, _ := workingMax(config.ModeSSCUHQ)
	return limit == bitrate.Unsupported
}

// nativeStreamLocked requires a.mu.
func (a *App) nativeStreamLocked(mode config.Mode) ipc.NativeStream {
	policy, _ := a.bitratePolicy(mode, true)
	kbps := policy.Selected(mode, a.s.Bitrate(mode))
	autoAAC := mode == config.ModeAAC && kbps == 0
	if kbps == 0 {
		kbps = policy.NativeAuto(mode)
	}
	return ipc.NativeStream{Mode: mode, BitrateKbps: kbps, AutoAAC: autoAAC, TryUHQ: mode == config.ModeSSCUHQ && a.s.AllBitrates}
}

// noBitrate: nothing can be offered for the codec on these headphones (not
// supported by their profile, Settings > All bitrates off). a.mu held.
func (a *App) noBitrate(m config.Mode) bool {
	return m.Streaming() && !a.offered(m, a.s.Bitrate(m))
}

// unsupportedText: the status / menu note for such a codec. a.mu held.
func (a *App) unsupportedText(m config.Mode) string {
	if kbps := a.s.Bitrate(m); kbps != 0 {
		return fmt.Sprintf(T("Выбранный битрейт %d кбит/с недоступен для %s с текущими настройками; выберите другой битрейт или Auto.",
			"Selected bitrate %d kbps is unavailable for %s with the current settings; choose another bitrate or Auto."), kbps, modeName(m))
	}
	_, model := a.workingMax(m)
	return unsupportedBitrateText(m, model)
}

func unsupportedBitrateText(m config.Mode, model string) string {
	return fmt.Sprintf(T("%s не поддерживается %s - включите «Настройки ▸ Все битрейты»",
		"%s is not supported by %s - turn on \"Settings > All bitrates\""), modeName(m), model)
}

// winUSBBitrate requires a.mu.
func (a *App) winUSBBitrate(m config.Mode) int {
	policy, _ := a.bitratePolicy(m, false)
	return policy.Selected(m, a.s.Bitrate(m))
}
