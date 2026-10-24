package bt

/*
#include "goshim.h"
*/
import "C"

import (
	"context"
	"errors"
	"fmt"
	"runtime"
	"sync"
	"sync/atomic"
	"time"
	"unsafe"
)

const (
	initTimeout    = 30 * time.Second
	connectTimeout = 30 * time.Second // must exceed the ~20 s page timeout
	streamTimeout  = 10 * time.Second
	callTimeout    = 5 * time.Second
)

// timer ids (shim.c has 8 slots)
const (
	timerVolRetry = iota
	timerMouseRetry
	timerVolReady
)

var (
	ErrNotReady  = errors.New("Bluetooth-стек не запущен")
	ErrTimeout   = errors.New("истекло время ожидания")
	ErrNoCodec   = errors.New("наушники не поддерживают выбранный кодек")
	errCancelled = errors.New("отменено")
)

type mpkt struct {
	data   [1024]byte
	n      int
	ts     uint32
	marker bool
}

type stackT struct {
	logf   func(string, ...any)
	keys   KeyStore
	opts   Options
	events chan Event

	localAddr Addr

	// cross-thread posting
	qmu         sync.Mutex
	queue       []func()
	kickPending atomic.Bool
	loopRunning atomic.Bool
	loopDone    chan struct{}

	hciReady atomic.Bool
	initCh   chan struct{}
	offCh    chan struct{}
	initTick time.Time
	powerErr error

	// ---- BTstack thread state ----
	connectCh chan error
	streamCh  chan error
	startCh   chan error
	discCh    chan error
	inquiryCh chan error

	a2dpCid, avrcpCid         uint16
	localSeid, remoteSeid     uint8
	sbcSeid, aacSeid, sscSeid uint8
	caps                      RemoteCaps
	remote                    Addr
	hasRemote                 bool
	found                     []Found
	inquiring                 bool

	// ---- shared ----
	aclHandle atomic.Uint32
	connected atomic.Bool
	streaming atomic.Bool
	avrcpUp   atomic.Bool
	mtu       atomic.Uint32
	codec     atomic.Int32
	// remoteCfg: the headphones configured the stream themselves (they
	// connected to us); codec in remoteCodec. Reset by Configure/Connect.
	remoteCfg   atomic.Bool
	remoteCodec atomic.Int32
	// sscCfg: capability byte of the SSC configuration in force (0x0C basic,
	// 0x0E with the 96 kHz UHQ bit), whoever set it
	sscCfg atomic.Uint32

	// media queue: encoder goroutine -> BTstack thread
	mqmu      sync.Mutex
	mq        [64]mpkt
	mqHead    int
	mqTail    int
	mqCount   int
	mqReq     atomic.Bool
	sendFails atomic.Uint32
	sentOK    atomic.Uint64
	txBuf     mpkt

	vol   volPump
	mouse mouseBridge
}

var stack = &stackT{
	logf:   func(string, ...any) {},
	events: make(chan Event, 64),
}

func (s *stackT) emit(e Event) {
	select {
	case s.events <- e:
	default:
		s.logf("bt: event queue full, dropped %d", e.Kind)
	}
}

// Events delivers asynchronous notifications (volume, disconnect, keys).
func Events() <-chan Event { return stack.events }

// ---- posting work to the BTstack thread -----------------------------------

func (s *stackT) call(f func()) {
	s.qmu.Lock()
	s.queue = append(s.queue, f)
	s.qmu.Unlock()
	if s.loopRunning.Load() && !s.kickPending.Swap(true) {
		C.ssc_kick()
	}
}

func (s *stackT) drain() {
	s.kickPending.Store(false)
	s.qmu.Lock()
	q := s.queue
	s.queue = nil
	s.qmu.Unlock()
	for _, f := range q {
		f()
	}
}

// callSync runs f on the BTstack thread and waits for it.
func (s *stackT) callSync(f func()) error {
	if !s.loopRunning.Load() {
		return ErrNotReady
	}
	done := make(chan struct{})
	s.call(func() { f(); close(done) })
	select {
	case <-done:
		return nil
	case <-time.After(callTimeout):
		return ErrTimeout
	}
}

func sig(ch chan error, err error) {
	if ch == nil {
		return
	}
	select {
	case ch <- err:
	default:
	}
}

func wait(ctx context.Context, ch chan error, d time.Duration) error {
	t := time.NewTimer(d)
	defer t.Stop()
	select {
	case err := <-ch:
		return err
	case <-t.C:
		return ErrTimeout
	case <-ctx.Done():
		return errCancelled
	}
}

// ---- lifecycle --------------------------------------------------------------

var localName *C.char // BTstack keeps the pointer

// Start brings BTstack up on the WinUSB adapter and waits for HCI_STATE_WORKING.
func Start(o Options) error {
	s := stack
	if s.loopRunning.Load() {
		return errors.New("стек уже запущен")
	}
	if o.Logf != nil {
		s.logf = o.Logf
	}
	s.keys = o.Keys
	s.opts = o
	s.initCh = make(chan struct{})
	s.offCh = make(chan struct{})
	s.loopDone = make(chan struct{})
	started := make(chan struct{})
	go s.loop(started)
	<-started
	if s.powerErr != nil {
		Shutdown()
		return s.powerErr
	}
	select {
	case <-s.initCh:
		return nil
	case <-time.After(initTimeout):
		Shutdown()
		return fmt.Errorf("адаптер не ответил за %s (WinUSB? прошивка?)", initTimeout)
	}
}

func (s *stackT) loop(started chan struct{}) {
	runtime.LockOSThread()
	defer close(s.loopDone)

	C.btstack_memory_init()
	C.btstack_run_loop_init(C.btstack_run_loop_windows_get_instance())
	verbose := C.int(0)
	if s.opts.Verbose {
		verbose = 1
	}
	C.ssc_log_init(verbose)
	if s.opts.Debug {
		applyDebug(s, true)
	}

	for _, id := range s.opts.USBIDs {
		C.hci_transport_usb_add_device(C.uint16_t(id[0]), C.uint16_t(id[1]))
	}
	C.hci_init(C.hci_transport_usb_instance(), nil)
	C.ssc_use_go_link_key_db()

	// SSP "Just Works" with general bonding so new keys are kept.
	C.gap_ssp_set_io_capability(C.SSP_IO_CAPABILITY_NO_INPUT_NO_OUTPUT)
	C.gap_ssp_set_authentication_requirement(C.SSP_IO_AUTHREQ_MITM_PROTECTION_NOT_REQUIRED_GENERAL_BONDING)
	name := s.opts.LocalName
	if name == "" {
		name = "SSCv2"
	}
	if localName == nil {
		localName = C.CString(name)
	}
	C.gap_set_local_name(localName)
	C.gap_set_class_of_device(0x200414) // Audio / Loudspeaker
	C.gap_set_allow_role_switch(true)   // many headphones want to be master
	C.gap_set_default_link_policy_settings(0x0005)
	C.gap_set_page_timeout(0x8000) // ~20 s

	C.l2cap_init()
	C.sdp_init()

	if s.opts.Mouse != nil {
		s.mouse.setup(s, s.opts.Mouse)
	}

	C.a2dp_source_init()
	C.avrcp_init()
	C.avrcp_controller_init()
	C.avrcp_target_init()
	C.ssc_register_handlers()
	C.ssc_register_sdp()

	var sbc, aac, ssc C.uint8_t
	withSSC := C.int(0)
	if s.opts.EnableSSC {
		withSSC = 1
	}
	C.ssc_register_endpoints(&sbc, &aac, &ssc, withSSC)
	s.sbcSeid, s.aacSeid, s.sscSeid = uint8(sbc), uint8(aac), uint8(ssc)
	s.logf("bt: endpoints SBC=%d AAC=%d SSC=%d", s.sbcSeid, s.aacSeid, s.sscSeid)

	s.initTick = time.Now()
	if rc := C.hci_power_control(C.HCI_POWER_ON); rc != 0 {
		s.logf("bt: hci_power_control(ON) failed: %d (adapter busy or not WinUSB?)", int(rc))
		s.powerErr = fmt.Errorf("адаптер не открылся (код %d) - занят другим процессом или не в режиме WinUSB", int(rc))
	}

	s.loopRunning.Store(true)
	close(started)
	// Work posted before the loop ran: process it now.
	s.kickPending.Store(true)
	C.ssc_kick()

	C.btstack_run_loop_execute()
	s.loopRunning.Store(false)
	s.logf("bt: run loop exited")
}

// Shutdown powers the controller off (releasing the USB device) and stops
// the run loop.
func Shutdown() {
	s := stack
	if !s.loopRunning.Load() {
		return
	}
	s.streaming.Store(false)
	if s.hciReady.Load() {
		s.call(func() { C.hci_power_control(C.HCI_POWER_OFF) })
		select {
		case <-s.offCh:
		case <-time.After(5 * time.Second):
			s.logf("bt: HCI power off timed out")
		}
	}
	s.call(func() { flushDump(); C.btstack_run_loop_trigger_exit() })
	select {
	case <-s.loopDone:
	case <-time.After(5 * time.Second):
		s.logf("bt: run loop did not exit")
	}
}

// RedirectCStdout sends C-level printf output to path.
func RedirectCStdout(path string) error {
	p := C.CString(path)
	defer C.free(unsafe.Pointer(p))
	if C.ssc_redirect_stdout(p) != 0 {
		return errors.New("freopen failed")
	}
	return nil
}

// Ready reports whether HCI is up.
func Ready() bool { return stack.hciReady.Load() }

// LocalAddr is the controller's BD_ADDR (valid after Start).
func LocalAddr() Addr { return stack.localAddr }

// ---- inquiry ----------------------------------------------------------------

// Scan runs a GAP inquiry for about `d` and returns what answered.
func Scan(ctx context.Context, d time.Duration) ([]Found, error) {
	s := stack
	if !s.hciReady.Load() {
		return nil, ErrNotReady
	}
	units := int(d.Seconds()*10+12) / 13 // 1.28 s units
	if units < 3 {
		units = 3
	}
	if units > 30 {
		units = 30
	}
	ch := make(chan error, 1)
	var rc C.int
	err := s.callSync(func() {
		s.found = nil
		s.inquiring = true
		s.inquiryCh = ch
		rc = C.gap_inquiry_start(C.uint8_t(units))
		if rc != 0 {
			s.inquiring = false
		}
	})
	if err != nil {
		return nil, err
	}
	if rc != 0 {
		return nil, fmt.Errorf("gap_inquiry_start: %d", int(rc))
	}
	err = wait(ctx, ch, time.Duration(units)*1280*time.Millisecond+5*time.Second)
	var out []Found
	_ = s.callSync(func() {
		if s.inquiring {
			C.gap_inquiry_stop()
			s.inquiring = false
		}
		out = append(out, s.found...)
	})
	if err != nil && err != ErrTimeout {
		return out, err
	}
	return out, nil
}

// ---- A2DP -------------------------------------------------------------------

// Connect opens the A2DP signalling channel to addr (pairing if needed)
// and discovers the sink's codecs.
func Connect(ctx context.Context, addr Addr) (RemoteCaps, error) {
	s := stack
	if !s.hciReady.Load() {
		return RemoteCaps{}, ErrNotReady
	}
	ch := make(chan error, 1)
	var rc C.uint8_t
	var already bool
	err := s.callSync(func() {
		if s.connected.Load() && s.hasRemote && s.remote == addr {
			already = true // the headphones connected by themselves
			return
		}
		s.remote, s.hasRemote = addr, true
		s.caps = RemoteCaps{}
		s.remoteCfg.Store(false)
		s.connectCh = ch
		s.connected.Store(false)
		s.streaming.Store(false)
		s.resetMedia()
		a := addr
		var cid C.uint16_t
		rc = C.a2dp_source_establish_stream((*C.uint8_t)(unsafe.Pointer(&a[0])), &cid)
		s.a2dpCid = uint16(cid)
	})
	if err != nil {
		return RemoteCaps{}, err
	}
	if already {
		var caps RemoteCaps
		_ = s.callSync(func() { caps = s.caps })
		return caps, nil
	}
	// 0x0C: the headphones are setting up A2DP themselves right now; the
	// capability discovery of that connection completes our wait.
	if rc != 0 && rc != C.ERROR_CODE_COMMAND_DISALLOWED {
		return RemoteCaps{}, fmt.Errorf("a2dp_source_establish_stream: 0x%02X", uint8(rc))
	}
	s.logf("bt: connecting to %s ...", addr)
	if err := wait(ctx, ch, connectTimeout); err != nil {
		return RemoteCaps{}, fmt.Errorf("подключение к %s: %w", addr, err)
	}
	var caps RemoteCaps
	_ = s.callSync(func() { caps = s.caps })
	return caps, nil
}

// Configure sets the stream configuration for codec and waits until the
// stream is established. Returns the media payload MTU.
func Configure(ctx context.Context, codec Codec, sampleRate uint32, channels uint8, aacBitrate uint32) (int, error) {
	s := stack
	if !s.connected.Load() {
		return 0, ErrNotReady
	}
	ch := make(chan error, 1)
	var rc C.uint8_t
	var noCodec bool
	err := s.callSync(func() {
		var local, remote uint8
		switch codec {
		case CodecAAC:
			local, remote, noCodec = s.aacSeid, s.caps.AACSeid, !s.caps.AAC
		case CodecSSC:
			local, remote, noCodec = s.sscSeid, s.caps.SSCSeid, !s.caps.SSC
		default:
			local, remote, noCodec = s.sbcSeid, s.caps.SBCSeid, !s.caps.SBC
		}
		if noCodec || local == 0 || remote == 0 {
			noCodec = true
			return
		}
		s.localSeid, s.remoteSeid = local, remote
		s.streamCh = ch
		s.codec.Store(int32(codec))
		cid := C.uint16_t(s.a2dpCid)
		switch codec {
		case CodecAAC:
			rc = C.ssc_set_config_aac(cid, C.uint8_t(local), C.uint8_t(remote), C.uint32_t(sampleRate), C.uint8_t(channels), C.uint32_t(aacBitrate))
		case CodecSSC:
			// Like the phone (A2dpCodecConfigSsc::setCodecConfig): 24-bit
			// 48 kHz (0x04) plus the sink's "no bitrate limit" bit (0x08).
			cap := C.uint8_t(C.SSC_CAP_BASIC)
			if s.caps.SSCCap != 0 {
				cap = C.uint8_t(0x04 | s.caps.SSCCap&0x08)
			}
			if sampleRate == 88200 || sampleRate == 96000 {
				// phone: UHQ v2 (0x02) plus the sink's 0x08 bit
				cap = C.uint8_t(0x02 | 0x08)
				if s.caps.SSCCap != 0 {
					cap = C.uint8_t(0x02 | s.caps.SSCCap&0x08)
				}
			}
			if s.opts.SSCCap != 0 {
				cap = C.uint8_t(s.opts.SSCCap) // experiments (ctl ssccap)
			}
			rc = C.ssc_set_config_ssc(cid, C.uint8_t(local), C.uint8_t(remote), cap)
		default:
			rc = C.ssc_set_config_sbc(cid, C.uint8_t(local), C.uint8_t(remote), C.uint16_t(sampleRate), C.uint8_t(channels))
		}
	})
	if err != nil {
		return 0, err
	}
	if noCodec {
		return 0, ErrNoCodec
	}
	if rc != 0 {
		return 0, fmt.Errorf("set_config %s: 0x%02X", codec, uint8(rc))
	}
	if err := wait(ctx, ch, streamTimeout); err != nil {
		return 0, fmt.Errorf("настройка потока %s: %w", codec, err)
	}
	return int(s.mtu.Load()), nil
}

// RemoteConfigured reports a stream the headphones configured themselves
// (they connected to us): its codec and payload size.
func RemoteConfigured() (Codec, int, bool) {
	s := stack
	if !s.remoteCfg.Load() || !s.connected.Load() {
		return 0, 0, false
	}
	return Codec(s.remoteCodec.Load()), int(s.mtu.Load()), true
}

// SSCConfig is the capability byte of the configured SSC stream (0 if none).
func SSCConfig() uint8 { return uint8(stack.sscCfg.Load()) }

// StartStream sends AVDTP START and waits for it.
func StartStream(ctx context.Context) error {
	s := stack
	if !s.connected.Load() {
		return ErrNotReady
	}
	ch := make(chan error, 1)
	var rc C.uint8_t
	if err := s.callSync(func() {
		s.startCh = ch
		rc = C.a2dp_source_start_stream(C.uint16_t(s.a2dpCid), C.uint8_t(s.localSeid))
	}); err != nil {
		return err
	}
	if rc != 0 {
		return fmt.Errorf("start_stream: 0x%02X", uint8(rc))
	}
	return wait(ctx, ch, streamTimeout)
}

// StopStream suspends the stream (AVDTP SUSPEND).
func StopStream() {
	s := stack
	if !s.streaming.Load() {
		return
	}
	_ = s.callSync(func() {
		C.a2dp_source_pause_stream(C.uint16_t(s.a2dpCid), C.uint8_t(s.localSeid))
	})
	s.streaming.Store(false)
}

// Disconnect closes the A2DP (and AVRCP) connection.
func Disconnect() {
	s := stack
	if !s.loopRunning.Load() {
		return
	}
	StopStream()
	ch := make(chan error, 1)
	var had bool
	_ = s.callSync(func() {
		if s.a2dpCid == 0 {
			return
		}
		had = true
		s.discCh = ch
		C.a2dp_source_disconnect(C.uint16_t(s.a2dpCid))
	})
	if had {
		_ = wait(context.Background(), ch, 5*time.Second)
	}
	s.connected.Store(false)
	s.streaming.Store(false)
}

// Connected / Streaming state.
func Connected() bool { return stack.connected.Load() }
func Streaming() bool { return stack.streaming.Load() }

// MediaMTU is the maximum media payload (after the RTP header is added by
// BTstack the packet fits the L2CAP MTU).
func MediaMTU() int {
	if m := int(stack.mtu.Load()); m > 0 {
		return m
	}
	return 667
}

// Stats returns (queued packets, failures since last call, packets sent).
func Stats() (int, uint32, uint64) {
	s := stack
	s.mqmu.Lock()
	q := s.mqCount
	s.mqmu.Unlock()
	return q, s.sendFails.Swap(0), s.sentOK.Load()
}

func (s *stackT) resetMedia() {
	s.mqmu.Lock()
	s.mqHead, s.mqTail, s.mqCount = 0, 0, 0
	s.mqmu.Unlock()
}

// SendMedia queues one RTP payload (codec frames; AAC/SSC raw, SBC with its
// 1-byte header already prepended). Safe from any goroutine.
func SendMedia(payload []byte, timestamp uint32) bool {
	return SendMediaMarker(payload, timestamp, false)
}

// SendMediaMarker is SendMedia with the RTP marker bit (RFC 3016: set on
// the packet that completes an AAC frame split over several packets).
func SendMediaMarker(payload []byte, timestamp uint32, marker bool) bool {
	s := stack
	if !s.streaming.Load() {
		return false
	}
	s.mqmu.Lock()
	if s.mqCount >= len(s.mq) || len(payload) > len(s.mq[0].data) {
		s.mqmu.Unlock()
		s.sendFails.Add(1)
		return false
	}
	slot := &s.mq[s.mqHead]
	slot.n = copy(slot.data[:], payload)
	slot.ts = timestamp
	slot.marker = marker
	s.mqHead = (s.mqHead + 1) % len(s.mq)
	s.mqCount++
	s.mqmu.Unlock()

	if !s.mqReq.Swap(true) {
		s.call(func() {
			s.mqReq.Store(false)
			if s.streaming.Load() && s.a2dpCid != 0 {
				C.a2dp_source_stream_endpoint_request_can_send_now(C.uint16_t(s.a2dpCid), C.uint8_t(s.localSeid))
			}
		})
	}
	return true
}

// BTstack thread: send one queued packet.
func (s *stackT) canSendNow() {
	s.mqmu.Lock()
	have := s.mqCount > 0
	if have {
		s.txBuf = s.mq[s.mqTail]
		s.mqTail = (s.mqTail + 1) % len(s.mq)
		s.mqCount--
	}
	more := s.mqCount > 0
	s.mqmu.Unlock()
	if have {
		cid, seid := C.uint16_t(s.a2dpCid), C.uint8_t(s.localSeid)
		max := int(C.a2dp_max_media_payload_size(cid, seid))
		if max > 0 && s.txBuf.n <= max {
			mk := C.uint8_t(0)
			if s.txBuf.marker {
				mk = 1
			}
			st := C.a2dp_source_stream_send_media_payload_rtp(cid, seid, mk, C.uint32_t(s.txBuf.ts),
				(*C.uint8_t)(unsafe.Pointer(&s.txBuf.data[0])), C.uint16_t(s.txBuf.n))
			if st != 0 {
				s.sendFails.Add(1)
			} else {
				s.sentOK.Add(1)
			}
		} else {
			s.sendFails.Add(1)
		}
	}
	if more {
		C.a2dp_source_stream_endpoint_request_can_send_now(C.uint16_t(s.a2dpCid), C.uint8_t(s.localSeid))
	}
}

// ---- timers -----------------------------------------------------------------

func (s *stackT) onTimer(id int) {
	switch id {
	case timerVolRetry:
		s.vol.pump(s)
	case timerMouseRetry:
		s.mouse.connect(s)
	case timerVolReady:
		if !s.vol.ready {
			s.logf("volume: no level from Windows confirmed in 5 s - mirroring headphone changes anyway")
			s.vol.ready = true
		}
	}
}
