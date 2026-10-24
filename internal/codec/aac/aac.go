// Package aac wraps the Fraunhofer FDK AAC encoder for A2DP: AAC-LC, LATM
// (audioMuxVersion 2, StreamMuxConfig in every frame - the layout Android
// uses; with fdk's default Galaxy Buds accept the stream but stay silent).
package aac

/*
#cgo CXXFLAGS: -O2 -w -I${SRCDIR}/../../../third_party/fdk-aac/libAACenc/include -I${SRCDIR}/../../../third_party/fdk-aac/libAACenc/src -I${SRCDIR}/../../../third_party/fdk-aac/libFDK/include -I${SRCDIR}/../../../third_party/fdk-aac/libSYS/include -I${SRCDIR}/../../../third_party/fdk-aac/libMpegTPEnc/include -I${SRCDIR}/../../../third_party/fdk-aac/libSBRenc/include -I${SRCDIR}/../../../third_party/fdk-aac/libSACenc/include -I${SRCDIR}/../../../third_party/fdk-aac/libPCMutils/include -I${SRCDIR}/../../../third_party/fdk-aac/libArithCoding/include
#cgo CFLAGS: -O2 -I${SRCDIR}/../../../third_party/fdk-aac/libAACenc/include -I${SRCDIR}/../../../third_party/fdk-aac/libSYS/include
#cgo LDFLAGS: -lstdc++

#include <stdlib.h>
#include "aacenc_lib.h"

static int aac_set(HANDLE_AACENCODER h, int param, unsigned int v) {
    return (int)aacEncoder_SetParam(h, (AACENC_PARAM)param, v);
}

// Encode one frame of interleaved int16 PCM. Returns bytes written or <0.
static int aac_encode(HANDLE_AACENCODER h, const short *pcm, int samples,
                      unsigned char *out, int out_cap) {
    AACENC_BufDesc in_buf = {0}, out_buf = {0};
    AACENC_InArgs in_args = {0};
    AACENC_OutArgs out_args = {0};
    void *in_ptr = (void *)pcm;
    INT in_id = IN_AUDIO_DATA, in_size = samples * 2, in_el = 2;
    void *out_ptr = out;
    INT out_id = OUT_BITSTREAM_DATA, out_size = out_cap, out_el = 1;
    in_buf.numBufs = 1; in_buf.bufs = &in_ptr; in_buf.bufferIdentifiers = &in_id;
    in_buf.bufSizes = &in_size; in_buf.bufElSizes = &in_el;
    out_buf.numBufs = 1; out_buf.bufs = &out_ptr; out_buf.bufferIdentifiers = &out_id;
    out_buf.bufSizes = &out_size; out_buf.bufElSizes = &out_el;
    in_args.numInSamples = samples;
    AACENC_ERROR e = aacEncEncode(h, &in_buf, &out_buf, &in_args, &out_args);
    if (e != AACENC_OK) return -(int)e;
    return out_args.numOutBytes;
}

static int aac_info(HANDLE_AACENCODER h, unsigned *frame_len, unsigned *max_out) {
    AACENC_InfoStruct info;
    if (aacEncInfo(h, &info) != AACENC_OK) return -1;
    *frame_len = info.frameLength;
    *max_out = info.maxOutBufBytes;
    return 0;
}

static unsigned aac_get(HANDLE_AACENCODER h, int param) {
    return aacEncoder_GetParam(h, (AACENC_PARAM)param);
}

static int aac_init(HANDLE_AACENCODER h) {
    return (int)aacEncEncode(h, NULL, NULL, NULL, NULL);
}
*/
import "C"

import (
	"fmt"
	"unsafe"
)

// Encoder is one AAC-LC encoder instance.
type Encoder struct {
	h          C.HANDLE_AACENCODER
	FrameLen   int // PCM frames per AAC frame (1024)
	Channels   int
	SampleRate int
	Bitrate    int
	PeakBitrate int
	out        []byte
}

// New creates an encoder. frameBudget is the largest LATM frame allowed
// (the media payload of one AVDTP packet when every frame must fit one
// packet: Galaxy Buds offer 667 bytes, i.e. 250 kbps at 48 kHz); 0 = no cap.
func New(sampleRate, channels, bitrate, frameBudget int) (*Encoder, error) {
	if channels != 1 && channels != 2 {
		return nil, fmt.Errorf("aac: %d каналов не поддерживается", channels)
	}
	if sampleRate != 44100 && sampleRate != 48000 {
		return nil, fmt.Errorf("aac: частота %d не поддерживается", sampleRate)
	}
	var h C.HANDLE_AACENCODER
	if e := C.aacEncOpen(&h, 0, C.UINT(channels)); e != C.AACENC_OK {
		return nil, fmt.Errorf("aacEncOpen: %d", int(e))
	}
	enc := &Encoder{h: h, Channels: channels, SampleRate: sampleRate, Bitrate: bitrate}
	peak := 0
	if frameBudget > 16 {
		// fdk's peak bitrate bounds the whole transport frame (LATM
		// header included), so the budget is the payload itself. The old
		// build also subtracted the 12-byte RTP header a second time.
		peak = int(int64(frameBudget) * 8 * int64(sampleRate) / 1024)
		if enc.Bitrate > peak {
			enc.Bitrate = peak
		}
	}
	enc.PeakBitrate = peak
	mode := C.MODE_2
	if channels == 1 {
		mode = C.MODE_1
	}
	set := func(p C.AACENC_PARAM, v int) {
		C.aac_set(h, C.int(p), C.uint(v))
	}
	set(C.AACENC_AOT, C.AOT_AAC_LC)
	set(C.AACENC_SAMPLERATE, sampleRate)
	set(C.AACENC_CHANNELMODE, int(mode))
	set(C.AACENC_BITRATE, enc.Bitrate)
	if peak > 0 {
		set(C.AACENC_PEAK_BITRATE, peak)
	}
	set(C.AACENC_TRANSMUX, C.TT_MP4_LATM_MCP1)
	set(C.AACENC_AUDIOMUXVER, 2)
	set(C.AACENC_SIGNALING_MODE, 1)
	set(C.AACENC_HEADER_PERIOD, 1)
	set(C.AACENC_BITRATEMODE, 0) // CBR
	set(C.AACENC_AFTERBURNER, 1)
	// fdk's default lowpass at this bitrate is 17 kHz; ~245 kbps stereo
	// easily carries the full 20 kHz (fdk's maximum for AAC-LC).
	if enc.Bitrate >= 192000 {
		set(C.AACENC_BANDWIDTH, 20000)
	}
	if e := C.aac_init(h); e != 0 {
		C.aacEncClose(&h)
		return nil, fmt.Errorf("aac init: %d", int(e))
	}
	var fl, mo C.unsigned
	if C.aac_info(h, &fl, &mo) != 0 {
		C.aacEncClose(&h)
		return nil, fmt.Errorf("aacEncInfo failed")
	}
	enc.FrameLen = int(fl)
	enc.out = make([]byte, int(mo)+64)
	return enc, nil
}

// Encode consumes exactly FrameLen*Channels int16 samples and returns one
// LATM frame (possibly empty while the encoder primes). The returned slice
// is reused by the next call.
func (e *Encoder) Encode(pcm []int16) ([]byte, error) {
	need := e.FrameLen * e.Channels
	if len(pcm) < need {
		return nil, fmt.Errorf("aac: мало сэмплов (%d < %d)", len(pcm), need)
	}
	n := C.aac_encode(e.h, (*C.short)(unsafe.Pointer(&pcm[0])), C.int(need),
		(*C.uchar)(unsafe.Pointer(&e.out[0])), C.int(len(e.out)))
	if n < 0 {
		return nil, fmt.Errorf("aacEncEncode: %d", -int(n))
	}
	return e.out[:int(n)], nil
}

// Bandwidth is the audio bandwidth (Hz) the encoder chose.
func (e *Encoder) Bandwidth() int { return int(C.aac_get(e.h, C.AACENC_BANDWIDTH)) }

// Close frees the encoder.
func (e *Encoder) Close() {
	if e.h != nil {
		C.aacEncClose(&e.h)
		e.h = nil
	}
}
