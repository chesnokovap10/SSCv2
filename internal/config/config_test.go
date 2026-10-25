package config

import "testing"

func TestMigrate(t *testing.T) {
	s := &Settings{Mode: ModeSSC, AACMode: "over", SSCBitrate: 584}
	s.migrate()
	if !s.MaxMTU || s.AACMode != "" {
		t.Errorf("aac over -> MaxMTU: %+v", s)
	}
	if s.Mode != ModeSSCUHQ || s.SSCUHQBitrate != 584 || s.SSCBitrate != 0 {
		t.Errorf("UHQ bitrate -> SSC UHQ: %+v", s)
	}
	s = &Settings{Mode: "bogus", SSCBitrate: 229}
	s.migrate()
	if s.Mode != ModeOff || s.SSCBitrate != 229 {
		t.Errorf("unknown mode / basic bitrate: %+v", s)
	}
	s.SetBitrate(ModeAAC, 192)
	if s.Bitrate(ModeAAC) != 192 || s.Bitrate(ModeSSC) != 229 || s.Bitrate(ModeOff) != 0 {
		t.Errorf("Bitrate: %+v", s)
	}
}
