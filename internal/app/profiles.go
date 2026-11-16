package app

import (
	"strings"

	"sscv2/internal/bitrate"
	"sscv2/internal/buds"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
	"sscv2/internal/profiles"
)

func profileDeviceID(addr string) profiles.DevID {
	source, vendor, product, _, _ := keys.DeviceID(addr)
	return profiles.DevID{Source: source, Vendor: vendor, Product: product}
}

func (a *App) profileCommands(headphones *config.Device) buds.ControlCommands {
	if headphones == nil {
		return buds.ControlCommands{}
	}
	return a.deviceProfiles.Commands(profileDeviceID(headphones.Addr), profileDeviceName(headphones))
}

func profileDeviceName(headphones *config.Device) string {
	if headphones.Name != "" {
		return headphones.Name
	}
	if store, err := keys.Open(); err == nil {
		if entry, ok := store.FindClassic(headphones.Addr); ok {
			return entry.Name
		}
	}
	return ""
}

func (a *App) recordWinUSBProfile(headphones *config.Device, previous, current ipc.EngineStatus) {
	if headphones == nil || !strings.EqualFold(headphones.Addr, current.Headphones) || !current.Connected {
		return
	}
	if headphones.Name == "" && current.HeadphonesName != "" && !strings.EqualFold(current.HeadphonesName, current.Headphones) {
		device := *headphones
		device.Name = current.HeadphonesName
		headphones = &device
	}
	caps := current.Capabilities
	if previous.Capabilities != nil && caps != nil && *previous.Capabilities == *caps &&
		strings.EqualFold(previous.Headphones, current.Headphones) {
		caps = nil
	}
	mode := config.ModeOff
	var info profiles.StreamInfo
	if current.Phase == "streaming" && (previous.Phase != current.Phase || previous.Codec != current.Codec ||
		previous.BitrateKbps != current.BitrateKbps || previous.MediaPayloadBytes != current.MediaPayloadBytes) {
		switch current.Codec {
		case "AAC":
			mode = config.ModeAAC
		case "SSC":
			mode = config.ModeSSC
		case "SSC UHQ":
			mode = config.ModeSSCUHQ
		}
		info = profiles.StreamInfo{
			Kbps: current.BitrateKbps, PayloadBytes: current.MediaPayloadBytes,
			FitsPacketKbps: bitrate.PacketCeiling(mode, current.SampleRate, current.MediaPayloadBytes),
		}
	}
	a.recordBitrateProfile(headphones, false, caps, mode, info)
}

func (a *App) recordBitrateProfile(headphones *config.Device, native bool, caps *ipc.CodecCapabilities, mode config.Mode, stream profiles.StreamInfo) {
	if headphones == nil || a.deviceProfiles == nil || caps == nil && stream.Kbps == 0 {
		return
	}
	id := profileDeviceID(headphones.Addr)
	if !id.Valid() {
		return
	}
	if err := a.deviceProfiles.Observe(id, profileDeviceName(headphones), native, caps, mode, stream); err != nil {
		logf("bitrate profiles: %v", err)
	}
}
