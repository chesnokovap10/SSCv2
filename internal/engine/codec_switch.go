package engine

import (
	"context"
	"fmt"
	"time"

	"sscv2/internal/bt"
)

func (e *engine) switchCodec(ctx context.Context, caps bt.RemoteCaps, codec bt.Codec) (Encoder, int, error) {
	rate, makeEncoder := e.srate, newAAC
	if codec == bt.CodecSSC {
		if !caps.SSC || caps.SSCCap&0x04 == 0 {
			return nil, 0, fmt.Errorf("24-bit SSC endpoint unavailable (cap 0x%02X)", caps.SSCCap)
		}
		if err := sscRateOK(rate); err != nil {
			return nil, 0, err
		}
		rate, makeEncoder = sscEncodeRate(rate), newSSC
	} else if !caps.AAC {
		return nil, 0, bt.ErrNoCodec
	}

	handle := bt.ACLHandle()
	e.pipe.set(nil, 0, false)
	start := time.Now()
	if err := bt.CloseStream(ctx); err != nil {
		return nil, 0, fmt.Errorf("close old stream: %w", err)
	}
	mtu, err := bt.Configure(ctx, codec, uint32(rate), 2, 256000)
	if err != nil {
		return nil, 0, err
	}
	enc, err := makeEncoder(e.srate, mtu)
	if err != nil {
		return nil, 0, err
	}
	if err := bt.StartStream(ctx); err != nil {
		enc.Close()
		return nil, 0, err
	}
	if got := bt.ACLHandle(); got != handle {
		enc.Close()
		return nil, 0, fmt.Errorf("ACL changed from 0x%04x to 0x%04x", handle, got)
	}
	logf("codec switch: %s START accepted on ACL 0x%04x in %s", codec, handle, time.Since(start))
	return enc, mtu, nil
}
