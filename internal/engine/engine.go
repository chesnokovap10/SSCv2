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
	"sscv2/internal/bt"
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
	retarget    chan string
	changeCodec chan ipc.CodecChange
	incoming    chan incomingEv
	disc        chan struct{}

	pipe     pipeline
	cap      *audio.Capture
	volume   atomic.Uint32
	srate    int
	unmuteAt atomic.Int64 // unix ms when the pipeline may play again
	keep     atomic.Bool  // stopped for a restart: leave the audio routing
	carried  bool         // the routing came from the previous engine (not set up here yet)
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
	sscForced = e.cfg.SSCBitrate * 1000
	sscUHQMode = e.cfg.SSCUHQ
	sscMaxMTU = e.cfg.MaxMTU
	sscWorking = e.cfg.SSCMaxKbps * 1000
	logf("engine start %s: codec=%s uhq=%v bitrate aac=%d ssc=%d maxmtu=%v headphones=%q mouse=%q adapter=%04X:%04X debug=%v lang=%s",
		ipc.Version, e.cfg.Codec, e.cfg.SSCUHQ, e.cfg.AACBitrate, e.cfg.SSCBitrate, e.cfg.MaxMTU, e.cfg.Headphones, e.cfg.Mouse,
		e.cfg.VID, e.cfg.PID, e.cfg.Debug, i18n.Lang())
	e.volume.Store(uint32(e.cfg.Volume))
	e.pipe.userMuted.Store(e.cfg.HeadphonesMuted)
	e.target = e.cfg.Headphones
	if c := e.cfg.Carry; c != nil {
		// the previous engine left the routing in place: own it from now on
		e.st.MuteEndpoint = c.MuteEndpoint
		e.carried = true
	}
	e.ctx, e.cancel = context.WithCancel(context.Background())
	go e.commands(r)

	err := e.run()
	e.teardown()
	if err != nil && !errors.Is(err, context.Canceled) {
		logf("engine error: %v", err)
		e.update(func(s *ipc.EngineStatus) { s.Phase, s.Message = "error", err.Error() })
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
		case "stop":
			e.keep.Store(c.Keep)
			e.cancel()
		case "scan":
			go e.scan()
		case "volume":
			e.volume.Store(uint32(c.Volume))
			e.pipe.userMuted.Store(c.On)
			bt.SetVolume(c.Volume)
		case "codec":
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
	prev := e.st
	f(&e.st)
	snap := e.st
	e.mu.Unlock()
	if logx.Debug() && (prev.Phase != snap.Phase || prev.Message != snap.Message || prev.Connected != snap.Connected ||
		prev.Streaming != snap.Streaming || prev.AVRCP != snap.AVRCP || prev.Volume != snap.Volume || prev.MouseState != snap.MouseState) {
		logx.Dbgf("state", "phase=%s msg=%q connected=%v streaming=%v avrcp=%v volume=%d mouse=%q",
			snap.Phase, snap.Message, snap.Connected, snap.Streaming, snap.AVRCP, snap.Volume, snap.MouseState)
	}
	_ = e.out.Write(ipc.Event{Ev: "status", Status: &snap})
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
		ForceMediaMTU: map[bool]int{true: overMTU}[e.cfg.MaxMTU || e.cfg.AACMode == "over"],
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
	for {
		if e.target == "" {
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
			if e.carried {
				e.releaseAudio() // the headphones did not come: sound back to the speakers
			}
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
		case errors.Is(err, errLinkLost):
			// Put in the case / out of range: pause what was playing, fall
			// back to the speakers, stop calling them.
			e.onLinkLost()
			activeUntil = time.Time{}
			e.drainIncoming()
			continue
		case errors.Is(err, errReconnect):
			activeUntil = time.Now().Add(20 * time.Second)
			backoff = time.Second
			msg = i18n.T("переподключение на ", "reconnecting for ") + strings.ToUpper(e.cfg.Codec)
		case err != nil:
			logf("session: %v", err)
			msg = err.Error()
		default:
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
func (e *engine) session(addrStr string) error {
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
	e.update(func(s *ipc.EngineStatus) { s.Connected = true })

	if err := e.setupAudio(); err != nil {
		return err
	}

	var codec bt.Codec
	var mk func(int, int) (Encoder, error)
	// A stream the headphones configured themselves carries no codec list
	// (no discovery): judge it below, before the capability checks.
	_, _, remoteCfg := bt.RemoteConfigured()
	switch e.cfg.Codec {
	case "ssc":
		if !caps.SSC && !remoteCfg {
			return errors.New(i18n.T("наушники не поддерживают SSC", "the headphones do not support SSC"))
		}
		if caps.SSC && caps.SSCCap&0x04 == 0 {
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
		codec, mk = bt.CodecAAC, newAAC
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
		logf("using the %s stream the headphones set up", rc)
		mtu = rmtu
	} else {
		rate := e.srate
		if codec == bt.CodecSSC {
			rate = sscEncodeRate(e.srate)
		}
		mtu, err = bt.Configure(ctx, codec, uint32(rate), 2, 256000)
		if err != nil {
			return err
		}
	}
	enc, err := mk(e.srate, mtu)
	if err != nil {
		return err
	}
	defer func() { enc.Close() }()
	if err := bt.StartStream(ctx); err != nil {
		return err
	}
	// Silence until the headphones settled on the Windows level (Galaxy Buds
	// jump to their own, often 100 %, level right after connecting).
	e.pipe.muted.Store(true)
	e.unmuteAt.Store(time.Now().Add(4 * time.Second).UnixMilli())
	go e.unmuteWhenSettled()
	e.installEncoder(enc, mtu, codec)
	defer e.pipe.set(nil, 0, false)
	bt.SetVolume(uint8(e.volume.Load()))

	for {
		select {
		case <-e.ctx.Done():
			return nil
		case <-e.disc:
			return errLinkLost
		case a := <-e.retarget:
			e.target = a
			return nil
		case change := <-e.changeCodec:
			if e.cfg.Codec == change.Codec && e.cfg.SSCUHQ == change.SSCUHQ {
				continue
			}
			e.cfg.Codec, e.cfg.SSCUHQ = change.Codec, change.SSCUHQ
			sscUHQMode = change.SSCUHQ
			sscForced, sscWorking = change.SSCBitrate*1000, change.SSCMaxKbps*1000
			if change.Codec == "ssc" {
				codec = bt.CodecSSC
			} else {
				codec = bt.CodecAAC
			}
			next, mtu, err := e.switchCodec(ctx, caps, codec)
			if err != nil {
				logf("codec switch to %s: %v", codec, err)
				return errReconnect
			}
			enc.Close()
			enc = next
			e.installEncoder(enc, mtu, codec)
		}
	}
}

func (e *engine) installEncoder(enc Encoder, mtu int, codec bt.Codec) {
	frag := aacMode == "frag" && codec == bt.CodecAAC
	e.pipe.set(enc, mtu, frag)
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
		s.SampleRate = rate
	})
}

func (e *engine) unmuteWhenSettled() {
	start := time.Now()
	for e.pipe.muted.Load() {
		if time.Now().UnixMilli() >= e.unmuteAt.Load() || time.Since(start) > 6*time.Second {
			e.pipe.muted.Store(false)
			logf("volume: settled, audio on after %.1f s", time.Since(start).Seconds())
			return
		}
		select {
		case <-e.ctx.Done():
			return
		case <-time.After(50 * time.Millisecond):
		}
	}
}

// setupAudio captures the default render endpoint before its physical mute.
func (e *engine) setupAudio() error {
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
	id := cp.Device.ID
	e.mu.Lock()
	previous := e.st.MuteEndpoint
	e.mu.Unlock()
	if previous != "" && previous != id {
		if err := audio.SetMute(previous, false); err != nil {
			cp.Close()
			return err
		}
		e.update(func(s *ipc.EngineStatus) { s.MuteEndpoint = "" })
	}
	muted, err := audio.Muted(id)
	if err != nil {
		cp.Close()
		return err
	}
	if err := audio.SetMute(id, true); err != nil {
		cp.Close()
		return err
	}
	if err := cp.Start(func(samples []float32, frames int) { e.pipe.onCapture(samples, frames, cp.Format.Channels) }); err != nil {
		if !muted {
			_ = audio.SetMute(id, false)
		}
		cp.Close()
		return err
	}
	e.cap = cp
	e.srate = cp.Format.SampleRate
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

var evNames = map[bt.EventKind]string{bt.EvDisconnected: "disconnected", bt.EvVolume: "volume", bt.EvLinkKey: "link key",
	bt.EvMouse: "mouse", bt.EvAVRCPConnected: "AVRCP connected", bt.EvVolumeApplied: "volume applied",
	bt.EvACLUp: "ACL up", bt.EvA2DPReady: "A2DP ready", bt.EvMediaKey: "media key"}

func (e *engine) btEvents() {
	for ev := range bt.Events() {
		logx.Dbgf("bt", "event %s %s vol=%d %s", evNames[ev.Kind], ev.Addr, ev.Volume, ev.Mouse)
		switch ev.Kind {
		case bt.EvDisconnected:
			select {
			case e.disc <- struct{}{}:
			default:
			}
		case bt.EvVolume:
			e.volume.Store(uint32(ev.Volume))
			_ = e.out.Write(ipc.Event{Ev: "volume", Volume: &ev.Volume})
		case bt.EvACLUp, bt.EvA2DPReady:
			select {
			case e.incoming <- incomingEv{kind: ev.Kind, addr: ev.Addr.String()}:
			default:
			}
		case bt.EvVolumeApplied:
			// Give the confirmed headphone volume time to settle.
			e.unmuteAt.Store(time.Now().Add(250 * time.Millisecond).UnixMilli())
		case bt.EvAVRCPConnected:
			bt.SetVolume(uint8(e.volume.Load()))
		case bt.EvLinkKey:
			logf("new link key for %s", ev.Addr)
			_ = e.out.Write(ipc.Event{Ev: "linkkey", Addr: ev.Addr.String(),
				Key: fmt.Sprintf("%x", ev.Key[:]), KeyType: ev.KeyType})
		case bt.EvMouse:
			e.update(func(s *ipc.EngineStatus) { s.MouseState = ev.Mouse })
		case bt.EvMediaKey:
			// taps on the headphones -> Windows media keys
			vk := map[int]uint16{bt.MediaPlayPause: vkMediaPlayPause, bt.MediaNext: vkMediaNext,
				bt.MediaPrev: vkMediaPrev, bt.MediaStop: vkMediaStop}[ev.Media]
			if vk != 0 {
				pressKey(vk)
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
		bt.SetPlaying(bt.Streaming() && e.pipe.loudWithin(3*time.Second))
		e.update(func(s *ipc.EngineStatus) {
			s.Queue, s.Fails, s.Sent = q, fails, sent
			s.Volume = int(bt.Volume())
			s.AVRCP = bt.AVRCPConnected()
			s.Streaming = bt.Streaming()
			s.Connected = bt.Connected()
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
	logf("scan: %d device(s)", len(list))
	_ = e.out.Write(ipc.Event{Ev: "scan", Devices: list})
}

// teardown restores the audio setup and releases the adapter.
var (
	errLinkLost  = i18n.Error("связь с наушниками потеряна", "the link to the headphones was lost")
	errReconnect = i18n.Error("переподключение для выбора кодека", "reconnecting to choose the codec")
)

// onLinkLost pauses playback (when something was playing) and gives the
// sound back to the speakers until the headphones reconnect.
func (e *engine) onLinkLost() {
	if e.pipe.loudWithin(2 * time.Second) {
		logf("link lost while playing: sending media Play/Pause")
		mediaPlayPause()
		time.Sleep(300 * time.Millisecond) // let players pause before the output moves
	} else {
		logf("link lost (nothing playing)")
	}
	e.releaseAudio()
	logf("output back to the speakers until the headphones return")
}

// releaseAudio stops capture and volume sync and undoes the output changes
// (physical endpoint mute). setupAudio
// redoes them on the next connection.
// stopAudio stops capture and volume sync only.
func (e *engine) stopAudio() {
	e.pipe.set(nil, 0, false)
	if e.cap != nil {
		e.cap.Close()
		e.cap = nil
	}
	logf("audio: routing left for the next engine")
}

func (e *engine) releaseAudio() {
	e.carried = false
	e.pipe.set(nil, 0, false)
	if e.cap != nil {
		e.cap.Close()
		e.cap = nil
	}
	e.mu.Lock()
	st := e.st
	e.mu.Unlock()
	RestoreAudio(st)
	e.update(func(s *ipc.EngineStatus) {
		s.MuteEndpoint, s.Muted = "", false
		s.CaptureDevice, s.CaptureFormat = "", ""
	})
}

// teardown restores the audio setup and releases the adapter.
func (e *engine) teardown() {
	if e.keep.Load() {
		e.stopAudio() // routing stays for the next engine
	} else {
		e.releaseAudio()
	}
	bt.Disconnect()
	bt.Shutdown()
	logf("engine stopped")
}

// RestoreAudio undoes what an engine changed (also used by the tray when an
// engine died).
func RestoreAudio(st ipc.EngineStatus) {
	if err := audio.InitCOM(); err != nil {
		return
	}
	if st.MuteEndpoint != "" {
		_ = audio.SetMute(st.MuteEndpoint, false)
	}
}

func nz(a, b string) string {
	if a != "" {
		return a
	}
	return b
}
