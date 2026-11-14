package engine

import (
	"context"
	"fmt"
	"time"

	"sscv2/internal/bt"
)

func (e *engine) switchCodec(ctx context.Context, caps bt.RemoteCaps, codec bt.Codec, previous *Encoder) (Encoder, int, error) {
	rate, makeEncoder := e.srate, newSSC
	var aacBitrate int
	if codec == bt.CodecSSC {
		if !caps.SSC || !sscUHQ() && caps.SSCCap&0x04 == 0 {
			return nil, 0, fmt.Errorf("24-bit SSC endpoint unavailable (cap 0x%02X)", caps.SSCCap)
		}
		if err := sscRateOK(rate); err != nil {
			return nil, 0, err
		}
		rate = sscEncodeRate(rate)
	} else if !caps.AAC {
		return nil, 0, bt.ErrNoCodec
	} else {
		var err error
		aacBitrate, err = aacTarget(caps.AACBitrate)
		if err != nil {
			return nil, 0, err
		}
		makeEncoder = func(rate, mtu int) (Encoder, error) { return newAAC(rate, mtu, aacBitrate) }
	}

	handle := bt.ACLHandle()
	start := time.Now()
	if err := bt.CloseStream(ctx); err != nil {
		return nil, 0, fmt.Errorf("close old stream: %w", err)
	}
	e.pipe.set(nil, 0, false)
	if *previous != nil {
		(*previous).Close()
		*previous = nil
	}
	enc, mtu, err := e.openCodec(ctx, codec, rate, aacBitrate, makeEncoder)
	if err != nil {
		return nil, 0, err
	}
	if got := bt.ACLHandle(); got != handle {
		enc.Close()
		return nil, 0, fmt.Errorf("ACL changed from 0x%04x to 0x%04x", handle, got)
	}
	logf("codec switch: %s START accepted on ACL 0x%04x in %s", codec, handle, time.Since(start))
	return enc, mtu, nil
}

func (e *engine) openCodec(ctx context.Context, codec bt.Codec, rate, aacBitrate int, makeEncoder func(int, int) (Encoder, error)) (Encoder, int, error) {
	mtu, err := bt.Configure(ctx, codec, uint32(rate), 2, uint32(aacBitrate))
	if err != nil {
		return nil, 0, err
	}
	enc, err := makeEncoder(e.srate, mtu)
	if err != nil {
		_ = bt.CloseStream(ctx)
		return nil, 0, err
	}
	if err := bt.StartStream(ctx); err != nil {
		enc.Close()
		_ = bt.CloseStream(ctx)
		return nil, 0, err
	}
	return enc, mtu, nil
}
