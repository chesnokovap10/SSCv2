// Package engine is the streaming process ("ssc.exe engine"): it owns the
// adapter in WinUSB mode (MT79xx firmware, BTstack), the audio capture and
// encoder, AVRCP volume sync and the BLE mouse bridge. The tray talks to it
// over stdin/stdout (package ipc). One BTstack lifetime per process.
package engine

import (
	"context"
	"errors"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
	"sync"
	"sync/atomic"
	"time"

	"golang.org/x/sys/windows"

	"sscv2/internal/audio"
	"sscv2/internal/bitrate"
	"sscv2/internal/bt"
	"sscv2/internal/buds"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/i18n"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
	"sscv2/internal/logx"
	"sscv2/internal/mtk"
)

type engine struct {
	cfg   ipc.EngineConfig
	out   *ipc.Writer
	store *keys.Store

	mu     sync.Mutex
	st     ipc.EngineStatus
	target string // headphones address

	ctx         context.Context
	cancel      context.CancelFunc
	scanning    atomic.Bool
	retarget    chan string
	changeCodec chan ipc.CodecChange
	incoming    chan incomingEv
	disc        chan struct{}

	pipe          pipeline
	cap           *audio.Capture
	stopMuteGuard func()

	srate   int
	keep    atomic.Bool // stopped for a restart: leave the audio routing
	carried bool        // the routing came from the previous engine (not set up here yet)
}

func logf(f string, a ...any) { logx.Printf(f, a...) }

// Run is the engine process entry point. Returns the exit code.
func Run(in io.Reader, stdout *os.File) int {
	logx.Open(config.LogDir(), "engine.log", "engine")
	// The JSON protocol uses a duplicate of stdout; the C runtime's stdout
	// (BTstack printf) is pointed at a log file.
	var out io.Writer = stdout
	var dup windows.Handle
	self := windows.CurrentProcess()
	if err := windows.DuplicateHandle(self, windows.Handle(stdout.Fd()), self, &dup, 0, false,
		windows.DUPLICATE_SAME_ACCESS); err == nil {
		out = os.NewFile(uintptr(dup), "ipc")
		if err := bt.RedirectCStdout(filepath.Join(config.LogDir(), "engine-c.log")); err != nil {
			logf("redirect C stdout: %v", err)
		}
	} else {
		logf("dup stdout: %v", err)
	}
	e := &engine{
		out:         ipc.NewWriter(out),
		retarget:    make(chan string, 4),
		changeCodec: make(chan ipc.CodecChange, 1),
		incoming:    make(chan incomingEv, 8),
		disc:        make(chan struct{}, 4),
	}
	e.st.Volume = -1
	r := ipc.NewReader(in)
	if err := r.Read(&e.cfg); err != nil {
		logf("no config: %v", err)
		return 2
	}
	logx.SetDebug(e.cfg.Debug)
	i18n.Set(e.cfg.Lang)
	if e.cfg.AACMode != "" {
		aacMode = e.cfg.AACMode
	}
	aacForced = e.cfg.AACBitrate * 1000
	sscForced = e.cfg.SSCBitrate
	sscUHQMode = e.cfg.SSCUHQ
	sscWorking = e.cfg.SSCMaxKbps
	aacWorking = e.cfg.AACMaxKbps
	logf("engine start %s: codec=%s uhq=%v bitrate aac=%d ssc=%d maxmtu=%v headphones=%q mouse=%q adapter=%04X:%04X debug=%v lang=%s",
		ipc.Version, e.cfg.Codec, e.cfg.SSCUHQ, e.cfg.AACBitrate, e.cfg.SSCBitrate, e.cfg.MaxMTU, e.cfg.Headphones, e.cfg.Mouse,
		e.cfg.VID, e.cfg.PID, e.cfg.Debug, i18n.Lang())
	e.setVolume(e.cfg.Volume, e.cfg.HeadphonesMuted)
	e.target = e.cfg.Headphones
	if c := e.cfg.Carry; c != nil {
		// the previous engine left the routing in place: own it from now on
		e.st.MuteEndpoint = c.MuteEndpoint
		e.carried = true
	}
	e.ctx, e.cancel = context.WithCancel(context.Background())
	go e.commands(r)

	err := e.run()
	if errors.Is(err, errStreamStart) {
		e.keep.Store(false)
	}
	if cleanupErr := e.teardown(); cleanupErr != nil {
		if errors.Is(err, context.Canceled) {
			err = nil
		}
		err = errors.Join(err, cleanupErr)
	}
	if err != nil && !errors.Is(err, context.Canceled) {
		logf("engine error: %v", err)
		e.update(func(s *ipc.EngineStatus) {
			s.Phase, s.Message = "error", err.Error()
			s.StreamStartFailed = errors.Is(err, errStreamStart)
		})
		return 1
	}
	e.update(func(s *ipc.EngineStatus) { s.Phase, s.Message = "stopped", "" })
	return 0
}

func (e *engine) commands(r *ipc.Reader) {
	for {
		var c ipc.Command
		if err := r.Read(&c); err != nil {
			logf("tray gone (%v) - stopping", err)
			e.cancel()
			return
		}
		logx.Dbgf("ipc", "tray -> engine: %s %s", c.Cmd, c.Addr)
		switch c.Cmd {
		case "debug":
			logx.SetDebug(c.On)
			bt.SetDebug(c.On)
		case "lang":
			i18n.Set(c.Lang)
		case ipc.CommandStop:
			e.keep.Store(c.Keep)
			e.cancel()
		case "scan":
			if e.scanning.CompareAndSwap(false, true) {
				go e.scan()
			}
		case "volume":
			e.setVolume(c.Volume, c.On)
		case ipc.CommandEqualizer:
			if c.Equalizer != nil {
				bt.SetBudsEqualizer(c.Addr, *c.Equalizer)
			}
		case ipc.CommandNoiseControl:
			if c.NoiseMode != nil {
				bt.SetBudsNoiseControl(c.Addr, *c.NoiseMode)
			}
		case ipc.CommandCodec:
			if c.Codec != nil && (c.Codec.Codec == "aac" || c.Codec.Codec == "ssc") {
				// Keep the latest request if the previous switch is still in progress.
				select {
				case <-e.changeCodec:
				default:
				}
				e.changeCodec <- *c.Codec
			}
		case "connect":
			select {
			case e.retarget <- c.Addr:
			default:
			}
		}
	}
}

func (e *engine) update(f func(*ipc.EngineStatus)) {
	e.mu.Lock()
	defer e.mu.Unlock()
	prev := e.st
	f(&e.st)
	snap := e.st
	if logx.Debug() && (prev.Phase != snap.Phase || prev.Message != snap.Message || prev.Connected != snap.Connected ||
		prev.Streaming != snap.Streaming || prev.AVRCP != snap.AVRCP || prev.Volume != snap.Volume || prev.MouseState != snap.MouseState) {
		logx.Dbgf("state", "phase=%s msg=%q connected=%v streaming=%v avrcp=%v volume=%d mouse=%q",
			snap.Phase, snap.Message, snap.Connected, snap.Streaming, snap.AVRCP, snap.Volume, snap.MouseState)
	}
	_ = e.out.Write(ipc.Event{Ev: ipc.EventStatus, Status: &snap})
}

func (e *engine) run() error {
	// 1. MediaTek RAM firmware (chip boots from ROM after every power-up).
	id := driver.USBID{VID: e.cfg.VID, PID: e.cfg.PID}
	if st := driver.Detect(id); st.Mode != driver.WinUSB {
		return fmt.Errorf(i18n.T("адаптер %s не в режиме WinUSB (сейчас: %s)", "adapter %s is not in WinUSB mode (now: %s)"), id, st.Mode)
	}
	e.update(func(s *ipc.EngineStatus) {
		s.Phase, s.Message = "firmware", i18n.T("загрузка прошивки адаптера", "loading the adapter firmware")
	})
	info, err := mtk.Setup(e.cfg.VID, e.cfg.PID, "", logf)
	if err != nil {
		if errors.Is(err, mtk.ErrNotFound) {
			return fmt.Errorf(i18n.T("адаптер %04X:%04X не в режиме WinUSB", "adapter %04X:%04X is not in WinUSB mode"), e.cfg.VID, e.cfg.PID)
		}
		return fmt.Errorf(i18n.T("прошивка MediaTek: %w", "MediaTek firmware: %w"), err)
	}
	e.update(func(s *ipc.EngineStatus) {
		s.Chip = info.String()
		s.Firmware = info.FwBuild
	})

	// 2. Keys + BTstack.
	e.store, err = keys.Open()
	if err != nil {
		logf("keys.json: %v", err)
	}
	opts := bt.Options{
		EnableSSC:     true,
		SSCCap:        uint8(e.cfg.SSCCap),
		Keys:          e.store,
		Logf:          logf,
		Verbose:       e.cfg.Verbose,
		Debug:         e.cfg.Debug,
		ForceMediaMTU: map[bool]int{true: bitrate.WinUSBExtendedMTU}[e.cfg.MaxMTU || e.cfg.AACMode == "over"],
		USBIDs:        [][2]uint16{{e.cfg.VID, e.cfg.PID}},
	}
	if e.cfg.Mouse != "" {
		if l, ok := e.store.FindLE(e.cfg.Mouse); ok {
			if b, err := l.Bond(); err == nil {
				opts.Mouse = b
				e.update(func(s *ipc.EngineStatus) { s.Mouse = l.Addr; s.MouseState = i18n.T("запуск", "starting") })
			} else {
				logf("mouse bond: %v", err)
			}
		} else if c, ok := e.store.FindClassic(e.cfg.Mouse); ok {
			if a, err := bt.ParseAddr(c.Addr); err == nil {
				opts.ClassicMouse = &a
				e.update(func(s *ipc.EngineStatus) { s.Mouse = c.Addr; s.MouseState = i18n.T("запуск", "starting") })
			}
		} else {
			logf("mouse %s: no keys", e.cfg.Mouse)
		}
	}
	e.update(func(s *ipc.EngineStatus) {
		s.Phase, s.Message = "starting", i18n.T("запуск Bluetooth-стека", "starting the Bluetooth stack")
	})
	if err := bt.Start(opts); err != nil {
		return err
	}
	e.update(func(s *ipc.EngineStatus) { s.AdapterAddr = bt.LocalAddr().String() })
	go e.btEvents()
	go e.ticker()

	if err := audio.InitCOM(); err != nil {
		return fmt.Errorf("COM: %w", err)
	}

	// 3. Stream to the headphones. Like Windows: call them actively for a
	// while after the mode is switched on (or other headphones are chosen);
	// after a lost link (put in the case) only wait for them to connect by
	// themselves when they are taken out.
	backoff := 3 * time.Second
	activeUntil := time.Now().Add(activeWindow)
	var reconnectUntil time.Time
	for {
		if e.target == "" {
			e.releaseSessionAudio()
			e.update(func(s *ipc.EngineStatus) {
				s.Phase, s.Message = "idle", i18n.T("наушники не выбраны - «Сопрячь устройство»", "no headphones chosen - see Pair a device")
			})
			select {
			case <-e.ctx.Done():
				return e.ctx.Err()
			case a := <-e.retarget:
				e.target = a
				activeUntil = time.Now().Add(activeWindow)
				continue
			}
		}

		if time.Now().After(activeUntil) {
			if !reconnectUntil.IsZero() {
				e.drainIncoming()
				reconnectUntil = time.Time{}
			}
			e.releaseSessionAudio() // the headphones did not come: sound back to the speakers
			// passive: wait until the headphones connect to us
			e.update(func(s *ipc.EngineStatus) {
				s.Phase, s.Message = "waiting", i18n.T("ожидание наушников (подключатся, когда их достанут из кейса)", "waiting for the headphones (they connect when taken out of the case)")
				s.Connected, s.Streaming = false, false
			})
			logf("waiting for %s to connect by itself", e.target)
			select {
			case <-e.ctx.Done():
				return e.ctx.Err()
			case a := <-e.retarget:
				e.target = a
				activeUntil = time.Now().Add(activeWindow)
				continue
			case in := <-e.incoming:
				if !strings.EqualFold(in.addr, e.target) {
					continue
				}
				if in.kind == bt.EvACLUp {
					logf("headphones connected by themselves - giving them 2 s to open A2DP")
					e.waitA2DP(2 * time.Second)
				}
			}
		}

		err := e.session(e.target)
		if e.ctx.Err() != nil {
			return e.ctx.Err()
		}
		msg := i18n.T("ожидание наушников", "waiting for the headphones")
		switch {
		case errors.Is(err, errSessionChanged):
			e.releaseSessionAudio()
			activeUntil = time.Now().Add(activeWindow)
			reconnectUntil = time.Time{}
			backoff = 3 * time.Second
			continue
		case errors.Is(err, errStreamStart):
			return err
		case errors.Is(err, errLinkLost):
			// Put in the case / out of range: pause what was playing, fall
			// back to the speakers, stop calling them.
			e.onLinkLost()
			activeUntil = time.Time{}
			reconnectUntil = time.Time{}
			e.drainIncoming()
			continue
		case errors.Is(err, errReconnect):
			if reconnectUntil.IsZero() {
				reconnectUntil = time.Now().Add(20 * time.Second)
				backoff = time.Second
			}
			activeUntil = reconnectUntil
			msg = i18n.T("переподключение на ", "reconnecting for ") + strings.ToUpper(e.cfg.Codec)
		case err != nil:
			e.releaseSessionAudio()
			logf("session: %v", err)
			msg = err.Error()
		default:
			reconnectUntil = time.Time{}
			e.releaseSessionAudio()
			backoff = 3 * time.Second
		}
		if time.Now().After(activeUntil) {
			continue // go passive
		}
		e.update(func(s *ipc.EngineStatus) {
			s.Phase, s.Message = "waiting", msg
			s.Connected, s.Streaming = false, false
		})
		select {
		case <-e.ctx.Done():
			return e.ctx.Err()
		case a := <-e.retarget:
			e.target = a
			reconnectUntil = time.Time{}
			backoff = 3 * time.Second
			activeUntil = time.Now().Add(activeWindow)
		case in := <-e.incoming:
			if strings.EqualFold(in.addr, e.target) && in.kind == bt.EvACLUp {
				e.waitA2DP(2 * time.Second)
			}
		case <-time.After(backoff):
			if backoff < 15*time.Second {
				backoff += backoff / 2
			}
		}
	}
}

// activeWindow: how long the headphones are called actively after the mode
// was switched on (Windows also only reconnects audio devices for a while).
const activeWindow = 60 * time.Second

var errSessionChanged = errors.New("headphones or audio output changed")

type incomingEv struct {
	kind bt.EventKind
	addr string
}

// waitA2DP gives headphones that connected by themselves time to open A2DP
// (then Connect just reuses it); otherwise Connect opens it on their link.
func (e *engine) waitA2DP(d time.Duration) {
	t := time.After(d)
	for {
		select {
		case in := <-e.incoming:
			if in.kind == bt.EvA2DPReady && strings.EqualFold(in.addr, e.target) {
				return
			}
		case <-t:
			return
		case <-e.ctx.Done():
			return
		}
	}
}

func (e *engine) drainIncoming() {
	for {
		select {
		case <-e.incoming:
		default:
			return
		}
	}
}

// session connects, streams until the link drops (nil) or fails (error).
func (e *engine) session(addrStr string) (result error) {
	addr, err := bt.ParseAddr(addrStr)
	if err != nil {
		return err
	}
	name := addrStr
	if c, ok := e.store.FindClassic(addrStr); ok && c.Name != "" {
		name = c.Name
	}
	e.update(func(s *ipc.EngineStatus) {
		s.Phase, s.Message = "connecting", i18n.T("подключение к ", "connecting to ")+name
		s.Headphones, s.HeadphonesName = addr.String(), name
		s.Battery = nil
		s.Equalizer = nil
		s.NoiseControl = nil
		s.Capabilities, s.MediaPayloadBytes = nil, 0
	})
	for len(e.disc) > 0 {
		<-e.disc
	}

	ctx, cancel := context.WithCancel(e.ctx)
	defer cancel()
	caps, err := bt.Connect(ctx, addr)
	if err != nil {
		return err
	}
	defer bt.Disconnect()
	var startupChange *ipc.CodecChange
	select {
	case change := <-e.changeCodec:
		e.selectCodec(change)
		startupChange = &change
	default:
	}
	startingSelectedStream := e.cfg.SSCUHQ || e.cfg.SSCBitrate > 0 || e.cfg.AACBitrate > 0 && e.cfg.Codec == "aac"
	defer func() {
		if startingSelectedStream && result != nil && !errors.Is(result, errReconnect) {
			result = fmt.Errorf("%w: %v", errStreamStart, result)
		}
	}()
	_, _, remoteCfg := bt.RemoteConfigured()
	uhqSupported := caps.SSCUHQ || remoteCfg && bt.SSCConfig()&0x02 != 0
	e.update(func(s *ipc.EngineStatus) {
		s.Connected, s.SSCUHQSupported = true, &uhqSupported
		if !remoteCfg {
			s.Capabilities = &ipc.CodecCapabilities{
				AAC: caps.AAC, SSC: caps.SSC && caps.SSCCap&0x04 != 0, SSCUHQ: caps.SSCUHQ,
				AACMaxBps: caps.AACBitrate,
			}
		}
	})
	sscUHQMode, sscForced = e.cfg.SSCUHQ, e.cfg.SSCBitrate
	tryUHQ := e.cfg.TryUHQ && caps.SSC && !remoteCfg && !uhqSupported
	if sscUHQ() && !uhqSupported && !remoteCfg && !tryUHQ {
		return bt.ErrNoCodec
	}

	if err := e.openAudio(); err != nil {
		return err
	}

	var codec bt.Codec
	var mk func(int, int) (Encoder, error)
	var aacBitrate int
	// A stream the headphones configured themselves carries no codec list
	// (no discovery): judge it below, before the capability checks.
	switch e.cfg.Codec {
	case "ssc":
		if !caps.SSC && !remoteCfg {
			return errors.New(i18n.T("наушники не поддерживают SSC", "the headphones do not support SSC"))
		}
		if !sscUHQ() && caps.SSC && caps.SSCCap&0x04 == 0 {
			// the phone would go 16-bit 44.1 kHz here; we only do 24-bit 48 kHz
			return fmt.Errorf(i18n.T("наушники не поддерживают 24-битный SSC (cap 0x%02X) - выберите AAC", "the headphones do not support 24-bit SSC (cap 0x%02X) - choose AAC"), caps.SSCCap)
		}
		codec, mk = bt.CodecSSC, newSSC
		if err := sscRateOK(e.srate); err != nil {
			return err
		}
	default:
		if !caps.AAC && !remoteCfg {
			return errors.New(i18n.T("наушники не поддерживают AAC", "the headphones do not support AAC"))
		}
		codec = bt.CodecAAC
		aacBitrate, err = aacTarget(caps.AACBitrate)
		if err != nil {
			return err
		}
		mk = func(rate, mtu int) (Encoder, error) { return newAAC(rate, mtu, aacBitrate) }
	}

	var mtu int
	if rc, rmtu, ok := bt.RemoteConfigured(); ok {
		if rc == bt.CodecSSC && (bt.SSCConfig()&0x02 != 0) != sscUHQ() {
			// their choice of UHQ (96 kHz) or basic differs from ours
			logf("headphones chose SSC cap 0x%02X themselves - reconnecting for ours (UHQ %v)", bt.SSCConfig(), sscUHQ())
			bt.Disconnect()
			return errReconnect
		}
		if rc != codec {
			// They connected by themselves and chose another codec: reconnect
			// from our side, where we pick the codec.
			logf("headphones chose %s themselves - reconnecting for %s", rc, codec)
			bt.Disconnect()
			return errReconnect
		}
		if rc == bt.CodecAAC && bt.AACSampleRate() != e.srate {
			logf("headphones configured AAC at %d Hz, capture is %d Hz; renegotiating", bt.AACSampleRate(), e.srate)
			return errReconnect
		}
		logf("using the %s stream the headphones set up", rc)
		mtu = rmtu
	} else {
		rate := e.srate
		if codec == bt.CodecSSC {
			rate = sscEncodeRate(e.srate)
		}
		mtu, err = bt.Configure(ctx, codec, uint32(rate), 2, uint32(aacBitrate))
		if err != nil {
			return err
		}
	}
	enc, err := mk(e.srate, mtu)
	if err != nil {
		return err
	}
	defer func() {
		if enc != nil {
			enc.Close()
		}
	}()
	if err := bt.StartStream(ctx); err != nil {
		return err
	}
	if err := e.startAudio(); err != nil {
		return err
	}
	e.installEncoder(enc, mtu, codec)
	if startupChange != nil {
		_ = e.out.Write(ipc.Event{Ev: "codec", Codec: startupChange})
	}
	startingSelectedStream = false
	defer e.pipe.set(nil, 0, false)
	outputCheck := time.NewTicker(time.Second)
	defer outputCheck.Stop()

	for {
		select {
		case <-e.ctx.Done():
			return nil
		case <-e.disc:
			return errLinkLost
		case err := <-e.cap.Errors():
			if output, lookupErr := audio.DefaultRender(); lookupErr == nil && output.ID != e.cap.Device.ID {
				return errSessionChanged
			}
			return err
		case err := <-e.pipe.errors:
			return fmt.Errorf("%w: encode: %v", errStreamStart, err)
		case <-outputCheck.C:
			if output, err := audio.DefaultRender(); err == nil && output.ID != e.cap.Device.ID {
				return errSessionChanged
			}
		case a := <-e.retarget:
			e.target = a
			return errSessionChanged
		case change := <-e.changeCodec:
			previous := e.currentCodec()
			reject := func(err error) {
				_ = e.out.Write(ipc.Event{Ev: "codecRejected", Codec: &previous, RejectedCodec: &change, Msg: err.Error()})
			}
			if change.SSCUHQ && !uhqSupported && !change.TryUHQ {
				reject(bt.ErrNoCodec)
				continue
			}
			sameMode := e.cfg.Codec == change.Codec && e.cfg.SSCUHQ == change.SSCUHQ
			if sameMode && e.cfg.AACBitrate == change.AACBitrate && e.cfg.AACMaxKbps == change.AACMaxKbps && e.cfg.SSCBitrate == change.SSCBitrate &&
				e.cfg.SSCMaxKbps == change.SSCMaxKbps && (!change.SSCUHQ || sscUHQ()) {
				_ = e.out.Write(ipc.Event{Ev: "codec", Codec: &change})
				continue
			}
			aacForced = change.AACBitrate * 1000
			aacWorking = change.AACMaxKbps
			sscUHQMode = change.SSCUHQ
			sscForced, sscWorking = change.SSCBitrate, change.SSCMaxKbps
			target := bt.CodecAAC
			if change.Codec == "ssc" {
				target = bt.CodecSSC
			}
			next, nextMTU := enc, mtu
			var err error
			if s, ok := enc.(*sscEnc); ok && target == bt.CodecSSC && s.e.SampleRate == sscEncodeRate(e.srate) {
				var br int
				br, err = sscBitrate(s.e.SampleRate, mtu, bt.SSCConfig())
				if err == nil {
					e.pipe.mu.Lock()
					s.e.Bitrate = br
					e.pipe.mu.Unlock()
					e.selectCodec(change)
					e.reportEncoder(enc, mtu, target)
					_ = e.out.Write(ipc.Event{Ev: "codec", Codec: &change})
					continue
				}
			} else {
				next, nextMTU, err = e.switchCodec(ctx, caps, target, &enc)
			}
			if err != nil {
				e.selectCodec(previous)
				reject(err)
				if enc != nil && bt.Streaming() {
					continue
				}
				if enc != nil {
					return errReconnect
				}
				// CLOSE succeeded but the new configuration failed. Restore
				// the last negotiated codec on the existing signaling link.
				rate := e.srate
				maker := newSSC
				br := 0
				if codec == bt.CodecSSC {
					rate = sscEncodeRate(rate)
				} else {
					br, err = aacTarget(caps.AACBitrate)
					if err != nil {
						return errReconnect
					}
					maker = func(rate, mtu int) (Encoder, error) { return newAAC(rate, mtu, br) }
				}
				enc, mtu, err = e.openCodec(ctx, codec, rate, br, maker)
				if err != nil {
					return errReconnect
				}
				e.installEncoder(enc, mtu, codec)
				continue
			}
			e.selectCodec(change)
			enc, mtu, codec = next, nextMTU, target
			e.installEncoder(enc, nextMTU, target)
			_ = e.out.Write(ipc.Event{Ev: "codec", Codec: &change})
		}
	}
}

func (e *engine) installEncoder(enc Encoder, mtu int, codec bt.Codec) {
	frag := aacMode == "frag" && codec == bt.CodecAAC
	bt.SetMediaPeriod(enc.FrameLen(), e.srate)
	e.pipe.set(enc, mtu, frag)
	e.reportEncoder(enc, mtu, codec)
}

func (e *engine) reportEncoder(enc Encoder, mtu int, codec bt.Codec) {
	frag := aacMode == "frag" && codec == bt.CodecAAC
	bw := ""
	if b, ok := enc.(interface{ Bandwidth() int }); ok {
		bw = fmt.Sprintf(", band %d Hz", b.Bandwidth())
	}
	label, rate := codec.String(), e.srate
	if si, ok := enc.(interface{ streamInfo() (string, int) }); ok {
		label, rate = si.streamInfo()
	}
	logf("streaming %s %d Hz, %d kbps%s, payload %d, packing %s", label, rate, enc.BitrateKbps(), bw, mtu, map[bool]string{true: "frag", false: "fit"}[frag])
	e.update(func(s *ipc.EngineStatus) {
		s.Phase, s.Message = "streaming", ""
		s.Streaming = true
		s.Codec = label
		s.BitrateKbps = enc.BitrateKbps()
		s.MediaPayloadBytes = mtu
		s.SampleRate = rate
	})
}

func (e *engine) setVolume(level uint8, muted bool) {
	e.pipe.setVolume(level, muted)
	if muted {
		level = 0
	}
	bt.SetVolume(level)
}

// openAudio reads the output format for codec negotiation without muting it.
func (e *engine) openAudio() error {
	if e.cap != nil {
		return nil
	}
	cp, err := audio.OpenCapture("")
	if err != nil {
		return err
	}
	if cp.Format.SampleRate != 44100 && cp.Format.SampleRate != 48000 {
		cp.Close()
		return fmt.Errorf(i18n.T("частота вывода %d Гц не поддерживается", "unsupported output rate %d Hz"), cp.Format.SampleRate)
	}
	e.cap = cp
	e.srate = cp.Format.SampleRate
	return nil
}

// startAudio takes ownership of the output mute once Bluetooth is streaming.
func (e *engine) startAudio() error {
	if e.stopMuteGuard != nil {
		return nil
	}
	cp := e.cap
	id := cp.Device.ID
	e.mu.Lock()
	previous := e.st.MuteEndpoint
	e.mu.Unlock()
	if previous != "" && previous != id {
		if err := audio.SetMute(previous, false); err != nil {
			return err
		}
		e.update(func(s *ipc.EngineStatus) { s.MuteEndpoint = "" })
	}
	muted, err := audio.Muted(id)
	if err != nil {
		return err
	}
	stopMuteGuard, err := audio.HoldMute(id)
	if err != nil {
		return err
	}
	mix := stereoMix(cp.Format.Channels, cp.Format.ChannelMask)
	if err := cp.Start(func(samples []float32, frames int, discontinuity bool) {
		e.pipe.onCapture(samples, frames, cp.Format.Channels, cp.Format.SampleRate, discontinuity, mix)
	}); err != nil {
		stopMuteGuard()
		if !muted {
			_ = audio.SetMute(id, false)
		}
		return err
	}
	e.stopMuteGuard = stopMuteGuard
	e.carried = false
	logf("capture: %s [%s]", cp.Device.Name, cp.Format)
	e.update(func(s *ipc.EngineStatus) {
		if !muted {
			s.MuteEndpoint = id
		}
		s.CaptureDevice, s.CaptureFormat, s.Muted = cp.Device.Name, cp.Format.String(), true
	})
	return nil
}

var evNames = map[bt.EventKind]string{bt.EvDisconnected: "disconnected", bt.EvVolume: "volume", bt.EvLinkKey: "link key", bt.EvBudsRemoved: "Buds removed", bt.EvBudsControls: "Buds controls",
	bt.EvMouse: "mouse", bt.EvAVRCPConnected: "AVRCP connected", bt.EvVolumeApplied: "volume applied",
	bt.EvACLUp: "ACL up", bt.EvA2DPReady: "A2DP ready", bt.EvMediaKey: "media key", bt.EvStreamReleased: "media channel released"}

func (e *engine) btEvents() {
	for ev := range bt.Events() {
		logx.Dbgf("bt", "event %s %s vol=%d %s", evNames[ev.Kind], ev.Addr, ev.Volume, ev.Mouse)
		switch ev.Kind {
		case bt.EvDisconnected, bt.EvStreamReleased:
			select {
			case e.disc <- struct{}{}:
			default:
			}
		case bt.EvACLUp, bt.EvA2DPReady:
			select {
			case e.incoming <- incomingEv{kind: ev.Kind, addr: ev.Addr.String()}:
			default:
			}
		case bt.EvLinkKey:
			logf("new link key for %s", ev.Addr)
			_ = e.out.Write(ipc.Event{Ev: "linkkey", Addr: ev.Addr.String(),
				Key: fmt.Sprintf("%x", ev.Key[:]), KeyType: ev.KeyType})
		case bt.EvMouse:
			e.update(func(s *ipc.EngineStatus) { s.MouseState = ev.Mouse })
		case bt.EvMediaKey:
			HandleMediaKey(ev.Media)
		case bt.EvBudsControls:
			e.update(func(s *ipc.EngineStatus) {
				if s.Headphones == ev.Addr.String() {
					s.Equalizer, s.NoiseControl = bt.BudsControls(s.Headphones)
				}
			})
		case bt.EvBudsRemoved:
			e.mu.Lock()
			current := e.st.Streaming && e.st.Headphones == ev.Addr.String()
			e.mu.Unlock()
			if current && bt.Streaming() && e.pipe.active.Load() {
				logf("Buds removed: sending media Pause")
				HandleMediaKey(bt.MediaPause)
			}
		}
	}
}

// ticker refreshes the counters every 2 s.
func (e *engine) ticker() {
	t := time.NewTicker(2 * time.Second)
	defer t.Stop()
	var lastBytes, lastFrames uint64
	for {
		select {
		case <-e.ctx.Done():
			return
		case <-t.C:
		}
		q, fails, sent := bt.Stats()
		_, mstate, mrep := bt.MouseStatus()
		eb, fr := e.pipe.encBytes.Load(), e.pipe.frames.Load()
		if bt.Streaming() {
			maxF, over := e.pipe.takeFrameStats()
			logf("CAP rate=%d fs enc=%d kbps peak=%.3f queue=%d fail=%d sent=%d maxframe=%d split=%d",
				(fr-lastFrames)/2, (eb-lastBytes)*8/2000, e.pipe.takePeak(), q, fails, sent, maxF, over)
		}
		lastBytes, lastFrames = eb, fr
		bt.SetPlaying(bt.Streaming() && e.pipe.activity.LoudWithin(3*time.Second))
		e.update(func(s *ipc.EngineStatus) {
			s.Queue, s.Fails, s.Sent = q, fails, sent
			s.Volume = int(e.pipe.volume.Load() & 127)
			s.AVRCP = bt.AVRCPConnected()
			s.Streaming = bt.Streaming()
			s.Connected = bt.Connected()
			var commands buds.ControlCommands
			if strings.EqualFold(s.Headphones, e.cfg.Headphones) {
				commands = e.cfg.BudsCommands
			}
			s.Battery, s.Equalizer, s.NoiseControl = bt.PollBudsStatus(s.Headphones, s.HeadphonesName, commands)
			if s.Mouse != "" {
				s.MouseState, s.MouseReports = mstate, mrep
			}
		})
	}
}

func (e *engine) scan() {
	logf("scan requested")
	found, err := bt.Scan(e.ctx, 10*time.Second)
	if err != nil {
		_ = e.out.Write(ipc.Event{Ev: "log", Msg: i18n.T("поиск: ", "search: ") + err.Error()})
	}
	var list []ipc.Found
	for _, f := range found {
		list = append(list, ipc.Found{Addr: f.Addr.String(), Name: f.Name, CoD: f.CoD, RSSI: int(f.RSSI), Audio: f.IsAudio()})
		if e.store != nil && f.Name != "" {
			e.store.SetName(f.Addr.String(), f.Name, f.CoD)
		}
	}
	e.scanning.Store(false)
	logf("scan: %d device(s)", len(list))
	_ = e.out.Write(ipc.Event{Ev: "scan", Devices: list})
}

func (e *engine) closeCapture() {
	e.pipe.set(nil, 0, false)
	if e.stopMuteGuard != nil {
		e.stopMuteGuard()
		e.stopMuteGuard = nil
	}
	if e.cap != nil {
		e.cap.Close()
		e.cap = nil
	}
}

// teardown restores the audio setup and releases the adapter.
var (
	errLinkLost    = i18n.Error("связь с наушниками потеряна", "the link to the headphones was lost")
	errReconnect   = i18n.Error("переподключение для выбора кодека", "reconnecting to choose the codec")
	errStreamStart = i18n.Error("не удалось запустить поток", "stream failed to start")
)

// onLinkLost pauses playback (when something was playing) and gives the
// sound back to the speakers until the headphones reconnect.
func (e *engine) onLinkLost() {
	PauseOnLinkLoss(e.pipe.activity.PlayingOnLinkLoss(), logf)
	if err := e.releaseAudio(); err != nil {
		logf("release audio after link loss: %v", err)
		return
	}
	logf("output back to the speakers until the headphones return")
}

// releaseAudio stops capture and volume sync and undoes the output changes
// (physical endpoint mute). startAudio
// redoes them on the next connection.
// stopAudio stops capture and volume sync only.
func (e *engine) stopAudio() {
	e.closeCapture()
	logf("audio: routing left for the next engine")
}

func (e *engine) releaseSessionAudio() {
	e.mu.Lock()
	muted := e.st.MuteEndpoint != ""
	e.mu.Unlock()
	if e.cap != nil || e.carried || muted {
		if err := e.releaseAudio(); err != nil {
			logf("release audio: %v", err)
		}
	}
}

func (e *engine) releaseAudio() error {
	e.carried = false
	e.closeCapture()
	e.mu.Lock()
	st := e.st
	e.mu.Unlock()
	err := RestoreAudio(st)
	e.update(func(s *ipc.EngineStatus) {
		if err == nil {
			s.MuteEndpoint, s.Muted = "", false
		}
		s.CaptureDevice, s.CaptureFormat = "", ""
	})
	return err
}

// teardown restores the audio setup and releases the adapter.
func (e *engine) teardown() error {
	var err error
	if e.keep.Load() {
		e.stopAudio() // routing stays for the next engine
	} else {
		err = e.releaseAudio()
	}
	bt.Disconnect()
	bt.Shutdown()
	logf("engine stopped")
	return err
}

// RestoreAudio undoes what an engine changed (also used by the tray when an
// engine died).
func RestoreAudio(st ipc.EngineStatus) error {
	if st.MuteEndpoint != "" {
		if err := audio.SetMute(st.MuteEndpoint, false); err != nil {
			return fmt.Errorf("restore mute on %q: %w", st.MuteEndpoint, err)
		}
	}
	return nil
}

func nz(a, b string) string {
	if a != "" {
		return a
	}
	return b
}

func (e *engine) selectCodec(change ipc.CodecChange) {
	e.cfg.Codec, e.cfg.SSCUHQ, e.cfg.TryUHQ = change.Codec, change.SSCUHQ, change.TryUHQ
	e.cfg.AACBitrate, e.cfg.SSCBitrate, e.cfg.SSCMaxKbps = change.AACBitrate, change.SSCBitrate, change.SSCMaxKbps
	e.cfg.AACMaxKbps = change.AACMaxKbps
	aacForced, aacWorking = change.AACBitrate*1000, change.AACMaxKbps
	sscUHQMode, sscForced, sscWorking = change.SSCUHQ, change.SSCBitrate, change.SSCMaxKbps
}

func (e *engine) currentCodec() ipc.CodecChange {
	c := e.cfg
	return ipc.CodecChange{Codec: c.Codec, SSCUHQ: c.SSCUHQ, TryUHQ: c.TryUHQ, AACBitrate: c.AACBitrate, AACMaxKbps: c.AACMaxKbps, SSCBitrate: c.SSCBitrate, SSCMaxKbps: c.SSCMaxKbps}
}
