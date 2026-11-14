package app

import (
	"errors"
	"slices"
	"strings"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
	"sscv2/internal/nativebt"
)

// openNativePlaybackLocked prepares the Windows route and starts the native worker.
func (a *App) openNativePlaybackLocked(mode config.Mode) error {
	if active, err := driver.TestSigning(); err != nil || !active {
		message := T("Для Bluetooth Windows требуется загрузка в тестовом режиме.", "The native Bluetooth driver requires Windows to boot in test mode.")
		if err != nil {
			message += " " + err.Error()
		}
		return errors.New(message)
	}
	if a.refreshAdapter().Mode != driver.BthUSB {
		return errors.New(T("Сначала верните адаптер в режим Bluetooth Windows через «Выкл».", "Choose Off to return the adapter to Windows Bluetooth first."))
	}
	a.mu.Lock()
	var address, budsName string
	if a.s.Headphones != nil {
		address, budsName = a.s.Headphones.Addr, a.s.Headphones.Name
	}
	a.mu.Unlock()
	if _, err := helper.Call(ipc.Request{Op: "native-profile-sync"}); err != nil {
		return err
	}
	path, err := nativebt.LocalProfilePath(address)
	// PnP can publish the interface shortly after the helper registers it.
	for deadline := time.Now().Add(5 * time.Second); errors.Is(err, nativebt.ErrLocalProfileUnavailable) && time.Now().Before(deadline); {
		time.Sleep(100 * time.Millisecond)
		path, err = nativebt.LocalProfilePath(address)
	}
	if err != nil {
		return err
	}
	previous := make([]string, 2)
	for role := range previous {
		endpoint, err := audio.DefaultRenderRole(role)
		if err != nil {
			return err
		}
		previous[role] = endpoint.ID
		if isBudsRender(endpoint) {
			previous[role] = previousRenderOutput(audio.List(false, audio.StateActive), endpoint.ID, "", budsName)
		}
	}
	existingRender := slices.ContainsFunc(audio.List(false, audio.StateActive|audio.StateDisabled), isBudsRender)
	if _, err := helper.Call(ipc.Request{Op: "native-render-ensure"}); err != nil {
		return err
	}
	var output string
	for deadline := time.Now().Add(3 * time.Second); output == ""; {
		for _, endpoint := range audio.List(false, audio.StateActive|audio.StateDisabled) {
			if isBudsRender(endpoint) {
				output = endpoint.ID
				break
			}
		}
		if output == "" {
			if time.Now().After(deadline) {
				return errors.New("Buds WaveRT output is unavailable")
			}
			time.Sleep(50 * time.Millisecond)
		}
	}
	var stereoVolume *config.StereoVolume
	stereo := budsStereoOutput(audio.List(false, audio.StateActive), output, budsName)
	if stereo != "" {
		if level, muted, err := audio.EndpointVolume(stereo); err == nil {
			stereoVolume = &config.StereoVolume{Level: level, Muted: muted}
		}
	}
	// Persist the route before changing defaults or releasing Windows A2DP.
	a.mu.Lock()
	a.s.NativeA2DPAddress, a.s.NativeRenderEndpoint = address, output
	a.s.NativePreviousOutputs = previous
	a.s.NativeStereoVolume = stereoVolume
	err = config.Save(a.s)
	if err != nil {
		a.s.NativeA2DPAddress, a.s.NativeRenderEndpoint = "", ""
		a.s.NativePreviousOutputs = nil
		a.s.NativeStereoVolume = nil
	}
	a.mu.Unlock()
	if err != nil {
		return err
	}
	if err := audio.SetRenderVisible(output, true); err != nil {
		return err
	}
	if !existingRender {
		// A freshly installed WaveRT endpoint can start at 100%.
		a.mu.Lock()
		level, muted := float32(a.volumeLocked())/127, a.s.HeadphonesMuted
		a.mu.Unlock()
		if stereoVolume != nil && stereoVolume.Level < 0.99 {
			level, muted = stereoVolume.Level, stereoVolume.Muted
		}
		if err := audio.SetEndpointVolume(output, level, muted); err != nil {
			return err
		}
	}
	for role, id := range previous {
		if id == "" && role != 0 {
			continue
		}
		if err := audio.SetDefaultRenderRole(output, role); err != nil {
			return err
		}
	}

	if _, err := helper.Call(ipc.Request{Op: "native-avrcp-release", Device: address}); err != nil {
		logf("Buds AVRCP release: %v", err)
	}
	return a.startNativeWorker(mode, path, output, address, stereo)
}

// resumeNativeStereo runs with opMu held.
func (a *App) resumeNativeStereo() error {
	a.mu.Lock()
	address, render := a.s.NativeA2DPAddress, a.s.NativeRenderBound
	output, previous := a.s.NativeRenderEndpoint, a.s.NativePreviousOutputs
	stereoVolume := a.s.NativeStereoVolume
	var budsName string
	if a.s.Headphones != nil {
		budsName = a.s.Headphones.Name
	}
	a.mu.Unlock()
	wasDefault := make([]bool, len(previous))
	for role := range previous {
		current, err := audio.DefaultRenderRole(role)
		// A disappeared WaveRT endpoint can leave a role without a default.
		wasDefault[role] = output != "" && (err != nil || current.ID == output || isBudsRender(current))
	}
	if address == "" {
		return hideNativeRender()
	}
	op := "native-a2dp-resume"
	if render {
		op = "native-render-restore"
	}
	if stereoVolume != nil && budsName != "" {
		settled, cancel, done := make(chan struct{}), make(chan struct{}), make(chan struct{})
		go func() {
			defer close(done)
			audio.RestoreHeadphonesVolume(budsName, stereoVolume.Level, stereoVolume.Muted, 8*time.Second, logf, settled, cancel)
		}()
		defer func() { close(cancel); <-done }()
	}
	_, restoreErr := helper.Call(ipc.Request{Op: op, Device: address})
	if output != "" {
		endpoints := audio.List(false, audio.StateActive)
		buds := budsStereoOutput(endpoints, output, budsName)
		for deadline := time.Now().Add(3 * time.Second); (stereoVolume != nil || slices.Contains(wasDefault, true)) && budsName != "" && buds == "" && time.Now().Before(deadline); {
			time.Sleep(50 * time.Millisecond)
			endpoints = audio.List(false, audio.StateActive)
			buds = budsStereoOutput(endpoints, output, budsName)
		}
		if buds != "" && stereoVolume != nil {
			if err := audio.SetEndpointVolume(buds, stereoVolume.Level, stereoVolume.Muted); err != nil {
				logf("restore Windows stereo volume: %v", err)
			}
		}
		for role, id := range previous {
			if !wasDefault[role] {
				continue
			}
			target := buds
			if target == "" {
				target = previousRenderOutput(endpoints, output, id, budsName)
			}
			if target != "" {
				if err := audio.SetDefaultRenderRole(target, role); err != nil {
					restoreErr = errors.Join(restoreErr, err)
				}
			}
		}
	}
	if err := errors.Join(restoreErr, hideNativeRender()); err != nil {
		return err
	}
	a.mu.Lock()
	defer a.mu.Unlock()
	a.s.NativeA2DPAddress, a.s.NativeRenderBound = "", false
	a.s.NativeRenderEndpoint, a.s.NativePreviousOutputs = "", nil
	a.s.NativeStereoVolume = nil
	if err := config.Save(a.s); err != nil {
		a.s.NativeA2DPAddress, a.s.NativeRenderBound = address, render
		a.s.NativeRenderEndpoint, a.s.NativePreviousOutputs = output, previous
		a.s.NativeStereoVolume = stereoVolume
		return err
	}
	return nil
}

func hideNativeRender() error {
	for _, endpoint := range audio.List(false, audio.StateActive) {
		if isBudsRender(endpoint) {
			if err := audio.SetRenderVisible(endpoint.ID, false); err != nil {
				return err
			}
		}
	}
	return nil
}

func budsStereoOutput(endpoints []audio.Endpoint, waveID, budsName string) string {
	name := strings.ToLower(budsName)
	if name == "" {
		return ""
	}
	for _, endpoint := range endpoints {
		if endpoint.ID != waveID && !isBudsRender(endpoint) && !isHandsFreeOutput(endpoint) &&
			strings.Contains(strings.ToLower(endpoint.Name), name) {
			return endpoint.ID
		}
	}
	return ""
}

func isHandsFreeOutput(endpoint audio.Endpoint) bool {
	return strings.Contains(strings.ToLower(endpoint.Name), "hands-free") ||
		strings.Contains(strings.ToLower(endpoint.AdapterName), "hands-free")
}

func isBudsRender(endpoint audio.Endpoint) bool {
	return endpoint.MatchesAdapter(driver.BudsRenderName)
}

func previousRenderOutput(endpoints []audio.Endpoint, waveID, previousID, budsName string) string {
	var fallback string
	for _, endpoint := range endpoints {
		if endpoint.ID == waveID || isBudsRender(endpoint) || isHandsFreeOutput(endpoint) {
			continue
		}
		if endpoint.ID == previousID {
			return previousID
		}
		if fallback == "" {
			fallback = endpoint.ID
		}
	}
	if buds := budsStereoOutput(endpoints, waveID, budsName); buds != "" {
		return buds
	}
	return fallback
}
