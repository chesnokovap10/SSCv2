package engine

import (
	"context"
	"fmt"
	"os"
	"time"

	"sscv2/internal/bt"
	"sscv2/internal/ipc"
)

func codecProbeEnabled() bool { return os.Getenv("SSCV2_CODEC_PROBE") == "1" }

func (e *engine) probeCodecSwitch(ctx context.Context, caps bt.RemoteCaps) error {
	if !caps.AAC || !caps.SSC || caps.SSCCap&0x04 == 0 {
		return fmt.Errorf("probe requires AAC and 24-bit SSC (SSC cap 0x%02X)", caps.SSCCap)
	}
	if err := sscRateOK(e.srate); err != nil {
		return err
	}
	handle := bt.ACLHandle()
	if handle > 0x0eff {
		return fmt.Errorf("probe cannot identify the original ACL handle")
	}
	for _, codec := range []bt.Codec{bt.CodecSSC, bt.CodecAAC} {
		timer := time.NewTimer(6 * time.Second)
		select {
		case <-timer.C:
		case <-ctx.Done():
			timer.Stop()
			return ctx.Err()
		case <-e.disc:
			timer.Stop()
			return errLinkLost
		}
		e.pipe.set(nil, 0)
		start := time.Now()
		if err := bt.CloseStream(ctx); err != nil {
			return fmt.Errorf("switch to %s, close old stream: %w", codec, err)
		}
		rate, makeEncoder := e.srate, newAAC
		if codec == bt.CodecSSC {
			rate, makeEncoder = sscEncodeRate(rate), newSSC
		}
		mtu, err := bt.Configure(ctx, codec, uint32(rate), 2, 256000)
		if err != nil {
			return fmt.Errorf("switch to %s, configure: %w", codec, err)
		}
		enc, err := makeEncoder(e.srate, mtu)
		if err != nil {
			return err
		}
		defer enc.Close()
		if err := bt.StartStream(ctx); err != nil {
			return fmt.Errorf("switch to %s, start: %w", codec, err)
		}
		if got := bt.ACLHandle(); got != handle {
			return fmt.Errorf("ACL changed from 0x%04x to 0x%04x", handle, got)
		}
		logf("codec probe: %s START accepted on ACL 0x%04x in %s", codec, handle, time.Since(start))
		e.pipe.set(enc, mtu)
		defer e.pipe.set(nil, 0)
		e.update(func(s *ipc.EngineStatus) {
			s.Codec, s.SampleRate, s.BitrateKbps = codec.String(), rate, enc.BitrateKbps()
		})
	}
	select {
	case <-ctx.Done():
		return nil
	case <-e.disc:
		return errLinkLost
	case a := <-e.retarget:
		e.target = a
		return nil
	}
}
