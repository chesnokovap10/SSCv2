package engine

import (
	"context"
	"fmt"
	"time"

	"sscv2/internal/bt"
)

func (e *engine) switchCodec(ctx context.Context, caps bt.RemoteCaps, codec bt.Codec, previous *Encoder) (Encoder, int, bool, error) {
	rate, makeEncoder := e.srate, newAAC
	if codec == bt.CodecSSC {
		if !caps.SSC || !sscUHQ() && caps.SSCCap&0x04 == 0 {
			return nil, 0, false, fmt.Errorf("24-bit SSC endpoint unavailable (cap 0x%02X)", caps.SSCCap)
		}
		if err := sscRateOK(rate); err != nil {
			return nil, 0, false, err
		}
		rate, makeEncoder = sscEncodeRate(rate), newSSC
	} else if !caps.AAC {
		return nil, 0, false, bt.ErrNoCodec
	}

	handle := bt.ACLHandle()
	start := time.Now()
	if err := bt.CloseStream(ctx); err != nil {
		return nil, 0, false, fmt.Errorf("close old stream: %w", err)
	}
	e.pipe.set(nil, 0, false)
	if *previous != nil {
		(*previous).Close()
		*previous = nil
	}
	enc, mtu, err := e.openCodec(ctx, codec, rate, makeEncoder)
	if err != nil {
		return nil, 0, true, err
	}
	if got := bt.ACLHandle(); got != handle {
		enc.Close()
		return nil, 0, true, fmt.Errorf("ACL changed from 0x%04x to 0x%04x", handle, got)
	}
	logf("codec switch: %s START accepted on ACL 0x%04x in %s", codec, handle, time.Since(start))
	return enc, mtu, true, nil
}

func (e *engine) openCodec(ctx context.Context, codec bt.Codec, rate int, makeEncoder func(int, int) (Encoder, error)) (Encoder, int, error) {
	mtu, err := bt.Configure(ctx, codec, uint32(rate), 2, 256000)
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
