package app

import (
	"bufio"
	"errors"
	"fmt"
	"io"
	"os"
	"slices"
	"strconv"
	"strings"
	"time"

	"sscv2/internal/audio"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/engine"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
	"sscv2/internal/nativebt"
)

type nativeProcess struct {
	mode        config.Mode
	kbps        int
	process     *os.Process
	input       io.WriteCloser
	done        chan struct{}
	started     chan struct{}
	ready       bool
	lastAACKbps int
}

// nativeBitrateLocked resolves Auto to the native transport's default.
func (a *App) nativeBitrateLocked(mode config.Mode) int {
	if kbps := a.bitrateFor(mode); kbps != 0 {
		return kbps
	}
	return a.nativeAutoBitrateLocked(mode)
}

func (a *App) nativeAutoBitrateLocked(mode config.Mode) int {
	if mode == config.ModeAAC {
		return nativebt.MaxAACKbps
	}
	limit, _ := a.workingMax(mode)
	best := 0
	for _, kbps := range bitrates[mode] {
		if kbps > best && (limit <= 0 || kbps <= limit) && engine.BitrateFits(string(mode), kbps, false) {
			best = kbps
		}
	}
	if best == 0 {
		return nativebt.DefaultBitrate(mode)
	}
	return best
}

// startNativeAudio runs with opMu held.
func (a *App) startNativeAudio(mode config.Mode) {
	a.setBusy(fmt.Sprintf(T("Запуск %s через Bluetooth Windows", "Starting %s through Windows Bluetooth"), modeName(mode)))
	if active, err := driver.TestSigning(); err != nil || !active {
		message := T("Для Bluetooth Windows требуется загрузка в тестовом режиме.", "The native Bluetooth driver requires Windows to boot in test mode.")
		if err != nil {
			message += " " + err.Error()
		}
		a.t.Balloon("SSCv2", message, 2)
		a.setMode(config.ModeOff)
		return
	}
	if a.refreshAdapter().Mode != driver.BthUSB {
		a.t.Balloon("SSCv2", T("Сначала верните адаптер в режим Bluetooth Windows через «Выкл».", "Choose Off to return the adapter to Windows Bluetooth first."), 2)
		a.setMode(config.ModeOff)
		return
	}
	if err := a.resumeNativeStereo(); err != nil {
		a.nativeError(err)
		return
	}
	a.mu.Lock()
	var address, budsName string
	if a.s.Headphones != nil {
		address, budsName = a.s.Headphones.Addr, a.s.Headphones.Name
	}
	a.mu.Unlock()
	if _, err := helper.Call(ipc.Request{Op: "native-profile-sync"}); err != nil {
		a.nativeError(err)
		return
	}
	path, err := nativebt.LocalProfilePath(address)
	// PnP can publish the interface shortly after the helper registers it.
	for deadline := time.Now().Add(5 * time.Second); errors.Is(err, nativebt.ErrLocalProfileUnavailable) && time.Now().Before(deadline); {
		time.Sleep(100 * time.Millisecond)
		path, err = nativebt.LocalProfilePath(address)
	}
	if err != nil {
		a.nativeError(err)
		return
	}
	previous := make([]string, 2)
	for role := range previous {
		endpoint, err := audio.DefaultRenderRole(role)
		if err != nil {
			a.nativeError(err)
			return
		}
		previous[role] = endpoint.ID
		if isBudsRender(endpoint) {
			previous[role] = previousRenderOutput(audio.List(false, audio.StateActive), endpoint.ID, "", budsName)
		}
	}
	if _, err := helper.Call(ipc.Request{Op: "native-render-ensure"}); err != nil {
		a.nativeError(err)
		return
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
				a.nativeError(errors.New("Buds WaveRT output is unavailable"))
				return
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
		a.nativeError(err)
		return
	}
	if err := audio.SetRenderVisible(output, true); err != nil {
		a.nativeError(errors.Join(err, a.stopNativeAudio()))
		return
	}
	for role, id := range previous {
		if id == "" && role != 0 {
			continue
		}
		if err := audio.SetDefaultRenderRole(output, role); err != nil {
			a.nativeError(errors.Join(err, a.stopNativeAudio()))
			return
		}
	}

	if _, err := helper.Call(ipc.Request{Op: "native-avrcp-release", Device: address}); err != nil {
		logf("Buds AVRCP release: %v", err)
	}
	a.startNativeWorker(mode, path, output, address, stereo)
}

func (a *App) startNativeWorker(mode config.Mode, path, endpoint, address, stereo string) {
	a.mu.Lock()
	kbps := a.nativeBitrateLocked(mode)
	a.mu.Unlock()
	process, input, output, err := startWorker(selfPath(), "native-"+string(mode)+"-worker", path, endpoint, address, stereo, strconv.Itoa(kbps))
	if err != nil {
		a.nativeError(errors.Join(err, a.stopNativeAudio()))
		return
	}

	p := &nativeProcess{mode: mode, kbps: kbps, process: process, input: input, done: make(chan struct{}), started: make(chan struct{})}
	a.mu.Lock()
	a.native = p
	a.mu.Unlock()
	go a.watchNativeAudio(p, output)
	logf("native worker: started PID %d", p.process.Pid)
	go a.watchNativeStartup(p, p.started)
	a.setMode(mode)
}

// switchNativeCodec runs with opMu held, so it cannot race a stop or another command.
func (a *App) switchNativeCodec(p *nativeProcess, mode config.Mode) {
	// Wait for the previous command's acknowledgment before replacing it.
	select {
	case <-p.started:
	case <-p.done:
		return
	}
	started := make(chan struct{})
	a.mu.Lock()
	kbps := a.nativeBitrateLocked(mode)
	if p.mode == mode && p.kbps == kbps {
		a.mu.Unlock()
		return
	}
	p.mode, p.kbps, p.ready, p.started = mode, kbps, false, started
	a.mu.Unlock()
	if _, err := fmt.Fprintln(p.input, mode, kbps); err != nil {
		a.nativeError(errors.Join(err, a.stopNativeAudio()))
		return
	}
	logf("native worker: switching to %s at %d kbps on PID %d", mode, kbps, p.process.Pid)
	go a.watchNativeStartup(p, started)
	a.setMode(mode)
}

func (a *App) watchNativeStartup(p *nativeProcess, started <-chan struct{}) {
	timer := time.NewTimer(15 * time.Second)
	defer timer.Stop()
	select {
	case <-started:
	case <-p.done:
	case <-timer.C:
		a.mu.Lock()
		if a.native == p && p.started == started && !p.ready {
			_ = p.process.Kill()
		}
		a.mu.Unlock()
	}
}

func (a *App) watchNativeAudio(p *nativeProcess, output io.ReadCloser) {
	scanner := bufio.NewScanner(output)
	var last string
	for scanner.Scan() {
		line := scanner.Text()
		a.mu.Lock()
		mode, kbps := p.mode, p.kbps
		ready := line == "native-"+string(mode)+"-ready"
		if ready && !p.ready {
			p.ready = true
			if mode == config.ModeAAC {
				p.lastAACKbps = kbps
			}
			close(p.started)
		}
		a.mu.Unlock()
		if ready {
			logf("native %s: ready", mode)
			logf("native %s: streaming at %d kbps", mode, kbps)
			a.refresh()
		} else {
			last = line
			logf("native %s: %s", mode, line)
		}
	}
	_ = output.Close()
	state, err := p.process.Wait()
	if err == nil && !state.Success() {
		err = errors.New(state.String())
	}
	err = errors.Join(scanner.Err(), err)
	close(p.done)

	a.opMu.Lock()
	defer a.opMu.Unlock()
	a.mu.Lock()
	current := a.native == p
	a.mu.Unlock()
	if !current {
		return
	}
	if err == nil {
		err = fmt.Errorf("native %s worker stopped", p.mode)
	}
	if last != "" {
		err = fmt.Errorf("%w: %s", err, last)
	}
	if p.mode == config.ModeAAC && !p.ready {
		fallback := p.lastAACKbps
		if fallback == 0 && p.kbps > nativebt.MaxAACKbps {
			fallback = nativebt.MaxAACKbps
		}
		if fallback != 0 && fallback != p.kbps {
			logf("native AAC: %d kbps failed, retrying at %d kbps: %v", p.kbps, fallback, err)
			if cleanupErr := a.stopNativeAudio(); cleanupErr != nil {
				a.nativeError(errors.Join(err, cleanupErr))
				return
			}
			a.mu.Lock()
			a.s.SetBitrate(config.ModeAAC, fallback)
			a.mu.Unlock()
			a.t.Balloon("SSCv2", fmt.Sprintf(T("AAC %d кбит/с не запустился. Повторная попытка на %d кбит/с.", "AAC %d kbps failed to start. Retrying at %d kbps."), p.kbps, fallback), 2)
			a.startNativeAudio(config.ModeAAC)
			a.setBusy("")
			return
		}
	}
	a.nativeError(errors.Join(err, a.stopNativeAudio()))
}

// stopNativeAudio runs with opMu held and keeps a failed rollback retryable.
func (a *App) stopNativeAudio() error {
	a.stopNativeWorker()
	return a.resumeNativeStereo()
}

func (a *App) stopNativeWorker() {
	a.mu.Lock()
	p := a.native
	a.native = nil
	a.mu.Unlock()
	if p != nil {
		_ = p.input.Close()
		select {
		case <-p.done:
		case <-time.After(3 * time.Second):
			_ = p.process.Kill()
			<-p.done
		}
	}
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
		if err != nil {
			return err
		}
		wasDefault[role] = output != "" && current.ID == output
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
	if _, err := helper.Call(ipc.Request{Op: op, Device: address}); err != nil {
		return err
	}
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
				return err
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
					return err
				}
			}
		}
	}
	if err := hideNativeRender(); err != nil {
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
		if endpoint.ID != waveID && strings.Contains(strings.ToLower(endpoint.Name), name) {
			return endpoint.ID
		}
	}
	return ""
}

func isBudsRender(endpoint audio.Endpoint) bool {
	return strings.EqualFold(endpoint.AdapterName, driver.BudsRenderName) ||
		strings.Contains(endpoint.Name, "("+driver.BudsRenderName+")")
}

func previousRenderOutput(endpoints []audio.Endpoint, waveID, previousID, budsName string) string {
	var buds, fallback string
	for _, endpoint := range endpoints {
		if endpoint.ID == waveID {
			continue
		}
		if endpoint.ID == previousID {
			return previousID
		}
		if budsName != "" && strings.Contains(strings.ToLower(endpoint.Name), strings.ToLower(budsName)) {
			buds = endpoint.ID
		}
		if fallback == "" {
			fallback = endpoint.ID
		}
	}
	if buds != "" {
		return buds
	}
	return fallback
}

func (a *App) nativeError(err error) {
	logf("native Bluetooth: %v", err)
	a.setMode(config.ModeOff)
	a.t.Balloon(T("Ошибка через Bluetooth Windows", "Windows Bluetooth failed"), err.Error(), 2)
}
