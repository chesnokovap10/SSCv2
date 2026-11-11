package audio

import (
	"errors"
	"fmt"
	"runtime"
	"sscv2/internal/logx"
	"sync"
	"sync/atomic"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"

	"sscv2/internal/i18n"
)

const (
	shareModeShared     = 0
	streamFlagsLoopback = 0x00020000
	bufferDiscontinuity = 0x1
	bufferFlagsSilent   = 0x2
	waveFormatFloat     = 0x0003
	waveFormatExt       = 0xFFFE
)

var (
	avrt                  = windows.NewLazySystemDLL("avrt.dll")
	procAvSetMmThreadChar = avrt.NewProc("AvSetMmThreadCharacteristicsW")
	procAvRevertMmThread  = avrt.NewProc("AvRevertMmThreadCharacteristics")
	winmm                 = windows.NewLazySystemDLL("winmm.dll")
	procTimeBeginPeriod   = winmm.NewProc("timeBeginPeriod")
	procTimeEndPeriod     = winmm.NewProc("timeEndPeriod")
)

// waveFormatEx (+ extensible tail)
type waveFormatEx struct {
	tag           uint16
	channels      uint16
	samplesPerSec uint32
	avgBytes      uint32
	blockAlign    uint16
	bits          uint16
	cbSize        uint16
	validBits     uint16
	channelMask   uint32
	subFormat     windows.GUID
}

// Format of the captured stream.
type Format struct {
	SampleRate int
	Channels   int
	Bits       int  // container bits per sample
	Float      bool // IEEE float samples
}

func (f Format) String() string {
	k := "int"
	if f.Float {
		k = "float"
	}
	return fmt.Sprintf("%d Hz, %d ch, %d-bit %s", f.SampleRate, f.Channels, f.Bits, k)
}

// Callback receives interleaved samples converted to float32 (len =
// frames*channels). The slice is reused after the call returns. A discontinuity
// marks a gap between this packet and the preceding packet.
type Callback func(samples []float32, frames int, discontinuity bool)

// Capture is a WASAPI shared-mode capture: loopback on a render endpoint,
// direct capture on a recording endpoint (e.g. the cable's "CABLE Output").
type Capture struct {
	client  uintptr
	capture uintptr
	Format  Format
	Device  Endpoint
	running atomic.Bool
	wg      sync.WaitGroup
	conv    []float32
	errors  chan error
}

// OpenCapture prepares capture on endpoint id ("" = default output).
func OpenCapture(id string) (*Capture, error) {
	en, err := enumerator()
	if err != nil {
		return nil, err
	}
	defer release(en)
	var dev uintptr
	if id == "" {
		dev, err = defaultDevice(en, eRender)
	} else {
		dev, err = deviceByID(en, id)
	}
	if err != nil {
		return nil, fmt.Errorf(i18n.T("устройство захвата: %w", "capture device: %w"), err)
	}
	defer release(dev)

	flow := uint32(eRender)
	var ep uintptr
	if hr(vcall(dev, 0, uintptr(unsafe.Pointer(&iidIMMEndpoint)), uintptr(unsafe.Pointer(&ep)))) == nil {
		vcall(ep, 3, uintptr(unsafe.Pointer(&flow)))
		release(ep)
	}
	c := &Capture{Device: describe(dev, flow == eCapture)}
	loop := uintptr(streamFlagsLoopback)
	if flow == eCapture {
		loop = 0
	}

	if err := hr(vcall(dev, 3, uintptr(unsafe.Pointer(&iidIAudioClient)), clsctxAll, 0, uintptr(unsafe.Pointer(&c.client)))); err != nil {
		return nil, fmt.Errorf("IAudioClient: %w", err)
	}
	var wfx *waveFormatEx
	if err := hr(vcall(c.client, 8, uintptr(unsafe.Pointer(&wfx)))); err != nil {
		c.Close()
		return nil, fmt.Errorf("GetMixFormat: %w", err)
	}
	defer taskFree(uintptr(unsafe.Pointer(wfx)))
	c.Format = Format{SampleRate: int(wfx.samplesPerSec), Channels: int(wfx.channels), Bits: int(wfx.bits)}
	c.Format.Float = wfx.tag == waveFormatFloat || (wfx.tag == waveFormatExt && wfx.subFormat == subtypeFloat)

	// 40 ms buffer, polled every 5 ms (the verified mode).
	const hns = 40 * 10000
	if err := hr(vcall(c.client, 3, shareModeShared, loop, hns, 0, uintptr(unsafe.Pointer(wfx)), 0)); err != nil {
		c.Close()
		return nil, fmt.Errorf("IAudioClient.Initialize: %w", err)
	}
	if err := hr(vcall(c.client, 14, uintptr(unsafe.Pointer(&iidIAudioCaptureClient)), uintptr(unsafe.Pointer(&c.capture)))); err != nil {
		c.Close()
		return nil, fmt.Errorf("IAudioCaptureClient: %w", err)
	}
	if c.Format.Bits != 16 && c.Format.Bits != 32 {
		c.Close()
		return nil, fmt.Errorf(i18n.T("формат %s не поддерживается", "format %s is not supported"), c.Format)
	}
	return c, nil
}

// Start begins capturing on a dedicated, MMCSS-boosted OS thread.
func (c *Capture) Start(cb Callback) error {
	if c.client == 0 {
		return errors.New("capture not open")
	}
	if err := hr(vcall(c.client, 10)); err != nil {
		return fmt.Errorf("IAudioClient.Start: %w", err)
	}
	c.running.Store(true)
	c.errors = make(chan error, 1)
	c.wg.Add(1)
	go func() {
		defer c.wg.Done()
		if err := c.loop(cb); err != nil {
			c.errors <- err
		}
	}()
	return nil
}

// Errors reports the terminal error, if any, from the current capture.
func (c *Capture) Errors() <-chan error { return c.errors }

func (c *Capture) loop(cb Callback) error {
	runtime.LockOSThread()
	defer runtime.UnlockOSThread()
	task := uint32(0)
	name, _ := windows.UTF16PtrFromString("Audio")
	h, _, _ := procAvSetMmThreadChar.Call(uintptr(unsafe.Pointer(name)), uintptr(unsafe.Pointer(&task)))
	procTimeBeginPeriod.Call(1)
	defer procTimeEndPeriod.Call(1)
	if h != 0 {
		defer procAvRevertMmThread.Call(h)
	}

	ch := c.Format.Channels
	var lastPacket time.Time
	for c.running.Load() {
		time.Sleep(5 * time.Millisecond)
		for c.running.Load() {
			var pkt uint32
			if err := hr(vcall(c.capture, 5, uintptr(unsafe.Pointer(&pkt)))); err != nil {
				return fmt.Errorf("capture: GetNextPacketSize: %w", err)
			}
			if pkt == 0 {
				break
			}
			var data uintptr
			var frames, flags uint32
			var devPos, qpc uint64
			if err := hr(vcall(c.capture, 3, uintptr(unsafe.Pointer(&data)), uintptr(unsafe.Pointer(&frames)),
				uintptr(unsafe.Pointer(&flags)), uintptr(unsafe.Pointer(&devPos)), uintptr(unsafe.Pointer(&qpc)))); err != nil {
				return fmt.Errorf("capture: GetBuffer: %w", err)
			}
			var out []float32
			if frames > 0 && cb != nil {
				n := int(frames) * ch
				if cap(c.conv) < n {
					c.conv = make([]float32, n)
				}
				out = c.conv[:n]
				switch {
				case flags&bufferFlagsSilent != 0 || data == 0:
					clear(out)
				case c.Format.Float && c.Format.Bits == 32:
					copy(out, unsafe.Slice((*float32)(unsafe.Pointer(data)), n))
				case c.Format.Bits == 16:
					src := unsafe.Slice((*int16)(unsafe.Pointer(data)), n)
					for i, v := range src {
						out[i] = float32(v) / 32768
					}
				default: // 32-bit integer
					src := unsafe.Slice((*int32)(unsafe.Pointer(data)), n)
					for i, v := range src {
						out[i] = float32(float64(v) / 2147483648.0)
					}
				}
			}
			if frames == 0 {
				break
			}
			// Return the WASAPI packet before running the encoder and transport.
			if err := hr(vcall(c.capture, 4, uintptr(frames))); err != nil {
				return fmt.Errorf("capture: ReleaseBuffer: %w", err)
			}
			now := time.Now()
			discontinuity := flags&bufferDiscontinuity != 0
			if !lastPacket.IsZero() {
				gap := now.Sub(lastPacket)
				discontinuity = discontinuity || gap >= 80*time.Millisecond
				if discontinuity {
					logx.Dbgf("audio", "capture: packet gap=%v flags=0x%x device frame=%d", gap.Round(time.Millisecond), flags, devPos)
				}
			}
			lastPacket = now
			if out != nil {
				cb(out, int(frames), discontinuity)
			}
		}
	}
	return nil
}

// Stop ends capturing (the device stays open; Close releases it).
func (c *Capture) Stop() {
	if !c.running.Swap(false) {
		return
	}
	c.wg.Wait()
	if c.client != 0 {
		vcall(c.client, 11)
	}
}

// Close releases COM objects.
func (c *Capture) Close() {
	c.Stop()
	release(c.capture)
	c.capture = 0
	release(c.client)
	c.client = 0
}
