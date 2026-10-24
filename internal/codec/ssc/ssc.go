// Package ssc wraps libssc (libssc/), our bit-exact twin of Samsung's
// libScalable_Encoder.so from the phone firmware: the Samsung Scalable Codec
// encoder for A2DP (vendor 0x00000075, codec 0x0103).
//
// The zssc_*.c files (go run ./tools/genwrap) compile the libssc sources into
// this package; each includes ssc_names.h first, like libssc/build.py does
// with -include.
//
// libssc keeps its DRC state and work buffers in process globals, as the
// blob does, so only one encoder may be open at a time.
package ssc

/*
#cgo CFLAGS: -std=gnu11 -O2 -w -DFIXED_POINT=1 -DOPUS_BUILD=1 -DVAR_ARRAYS=1 -DDISABLE_FLOAT_API=1 -I${SRCDIR}/../../../libssc/src -I${SRCDIR}/../../../libssc/src/opus

#include <stdlib.h>
#include "ssc_names.h"
#include "ssc_encoder.h"
*/
import "C"

import (
	"errors"
	"fmt"
	"sync"
	"unsafe"
)

// FrameLen is the PCM frames per SSC frame (18 ms at 48 kHz).
const FrameLen = 864

// Basic (44.1/48 kHz) and UHQ (96 kHz) bitrates the encoder knows, ascending.
// Any other value makes it write a malformed frame.
var (
	BasicBitrates = []int{88000, 96000, 128000, 192000, 229000, 256000, 328000}
	UHQBitrates   = []int{152000, 250000, 291000, 308000, 442000, 584000, 886000}
)

// ErrBusy: another encoder is open (libssc state is process-global).
var ErrBusy = errors.New("ssc: энкодер уже открыт")

var (
	mu   sync.Mutex
	open bool
)

// Encoder is one SSC encoder (stereo, 24-bit input).
type Encoder struct {
	st         *C.SscEncoder
	SampleRate int
	Bitrate    int
	pcm        *C.int32_t // FrameLen*2 samples, C memory (the DRC rewrites it)
	out        *C.uint8_t
	outCap     int
}

// Valid reports whether bitrate is one the encoder knows for sampleRate.
func Valid(sampleRate, bitrate int) bool {
	list := BasicBitrates
	if sampleRate == 96000 {
		list = UHQBitrates
	}
	for _, b := range list {
		if b == bitrate {
			return true
		}
	}
	return false
}

// FrameBytes is the size of every frame (header included) at this rate:
// the encoder is CBR. The 44.1/48 kHz mode counts the budget at 44100 Hz
// and narrow (non-UHQ, < 256k) rates get +3/128.
func FrameBytes(sampleRate, bitrate int) int {
	fsMode := sampleRate
	if sampleRate == 48000 {
		fsMode = 44100
	}
	n := bitrate * FrameLen / (fsMode * 8)
	if sampleRate != 96000 && bitrate != 256000 && bitrate != 328000 {
		n += (n * 3) >> 7
	}
	n |= 1
	return min(n-1, 1275) + C.SSC_HEADER_BYTES
}

// New opens an encoder. sampleRate is 44100, 48000 or 96000 (UHQ).
func New(sampleRate, bitrate int) (*Encoder, error) {
	if sampleRate != 44100 && sampleRate != 48000 && sampleRate != 96000 {
		return nil, fmt.Errorf("ssc: частота %d не поддерживается", sampleRate)
	}
	if !Valid(sampleRate, bitrate) {
		return nil, fmt.Errorf("ssc: битрейт %d не поддерживается на %d Гц", bitrate, sampleRate)
	}
	mu.Lock()
	defer mu.Unlock()
	if open {
		return nil, ErrBusy
	}
	var cerr C.int
	st := C.ssc_encoder_create(C.int(sampleRate), 2, 24, &cerr)
	if st == nil {
		return nil, fmt.Errorf("ssc_encoder_create: %d", int(cerr))
	}
	// Output: the range coder may write its tail up to the full budget
	// even when the frame is cut at 1275 bytes; 64 KB covers every rate.
	const outCap = 64 << 10
	e := &Encoder{
		st:         st,
		SampleRate: sampleRate,
		Bitrate:    bitrate,
		pcm:        (*C.int32_t)(C.calloc(FrameLen*2, 4)),
		out:        (*C.uint8_t)(C.calloc(outCap, 1)),
		outCap:     outCap,
	}
	open = true
	return e, nil
}

// fullScale: 24-bit input, full scale 2^23 (what the encoder's DRC limiter
// is tuned for; 2^29 as in the old program is 36 dB hot and gets squashed).
const fullScale = 8388608

// Encode consumes FrameLen interleaved stereo float samples (-1..1) and
// returns one SSC frame. The slice is reused by the next call.
func (e *Encoder) Encode(pcm []float32) ([]byte, error) {
	if e.st == nil {
		return nil, errors.New("ssc: энкодер закрыт")
	}
	if len(pcm) < FrameLen*2 {
		return nil, fmt.Errorf("ssc: мало сэмплов (%d < %d)", len(pcm), FrameLen*2)
	}
	in := unsafe.Slice((*int32)(unsafe.Pointer(e.pcm)), FrameLen*2)
	for i, v := range pcm[:FrameLen*2] {
		in[i] = To24(v)
	}
	n := C.ssc_encode(e.st, e.pcm, FrameLen, e.out, C.int(e.Bitrate))
	if n < 0 {
		return nil, fmt.Errorf("ssc_encode: %d", int(n))
	}
	return unsafe.Slice((*byte)(unsafe.Pointer(e.out)), int(n)), nil
}

// EncodeInt32 encodes FrameLen interleaved stereo samples already in the
// encoder's scale (24 bit, full scale 2^23). For tests against the blob.
func (e *Encoder) EncodeInt32(pcm []int32) ([]byte, error) {
	if len(pcm) < FrameLen*2 {
		return nil, fmt.Errorf("ssc: мало сэмплов (%d < %d)", len(pcm), FrameLen*2)
	}
	copy(unsafe.Slice((*int32)(unsafe.Pointer(e.pcm)), FrameLen*2), pcm)
	n := C.ssc_encode(e.st, e.pcm, FrameLen, e.out, C.int(e.Bitrate))
	if n < 0 {
		return nil, fmt.Errorf("ssc_encode: %d", int(n))
	}
	return unsafe.Slice((*byte)(unsafe.Pointer(e.out)), int(n)), nil
}

// To24 converts a float sample to the encoder's 24-bit scale (clipped).
func To24(v float32) int32 {
	x := float64(v) * fullScale
	switch {
	case x >= fullScale-1:
		return fullScale - 1
	case x <= -fullScale:
		return -fullScale
	case x >= 0:
		return int32(x + 0.5)
	default:
		return int32(x - 0.5)
	}
}

// Close frees the encoder.
func (e *Encoder) Close() {
	if e.st == nil {
		return
	}
	C.ssc_encoder_destroy(e.st)
	C.free(unsafe.Pointer(e.pcm))
	C.free(unsafe.Pointer(e.out))
	e.st = nil
	mu.Lock()
	open = false
	mu.Unlock()
}
