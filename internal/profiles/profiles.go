package profiles

import (
	"strings"

	"sscv2/internal/bitrate"
	"sscv2/internal/buds"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

// DevID is a Bluetooth Device ID (DI profile): vendor id source (1 =
// Bluetooth SIG company id, 2 = USB-IF), vendor and product.
type DevID struct {
	Source  uint16 `json:"source"`
	Vendor  uint16 `json:"vendor"`
	Product uint16 `json:"product"`
}

func (id DevID) Valid() bool {
	return (id.Source == 1 || id.Source == 2) && id.Vendor != 0 && id.Product != 0
}

type profile struct {
	Model      string                      `json:"model"`
	ID         DevID                       `json:"deviceId,omitzero"`
	NameMatch  string                      `json:"nameMatch,omitempty"`
	Commands   buds.ControlCommands        `json:"commands,omitzero"`
	MaxKbps    map[config.Mode]int         `json:"verifiedMaxKbps,omitempty"`
	Transports map[string]transportProfile `json:"transports,omitempty"`
}

type transportProfile struct {
	Advertised *ipc.CodecCapabilities     `json:"advertised,omitempty"`
	Streams    map[config.Mode]StreamInfo `json:"streams,omitempty"`
	MaxKbps    map[config.Mode]int        `json:"verifiedMaxKbps,omitempty"`
}

// StreamInfo describes what SSCv2 configured. Listening is a separate check.
type StreamInfo struct {
	Kbps           int `json:"lastConfiguredKbps"`
	PayloadBytes   int `json:"payloadBytes,omitempty"`
	FitsPacketKbps int `json:"fitsPacketKbps,omitempty"`
}

// Factory control settings are seeded independently of verified audio limits.
// Buds2 and Buds2 Pro can advertise the same Device ID, so their names also
// take part in matching. The other model entries gain a Device ID when seen.
var defaultProfiles = []profile{
	budsProfile("Buds", "buds", 0),
	budsProfile("Buds+", "buds+", 0),
	{Model: "Samsung Galaxy Buds Live", NameMatch: "buds live",
		Commands: buds.ControlCommands{Equalizer: 0x86, Noise: 0x98, NoiseUpdate: 0x9b, NoiseModes: 2}},
	budsProfile("Buds Pro", "buds pro", 3),
	{Model: "Samsung Galaxy Buds2", ID: DevID{1, 0x0075, 0xA013}, NameMatch: "buds2", Commands: standardCommands(3)},
	{Model: "Samsung Galaxy Buds2 Pro", ID: DevID{1, 0x0075, 0xA013}, NameMatch: "buds2 pro",
		Commands: standardCommands(3),
		MaxKbps:  map[config.Mode]int{config.ModeSSC: 229, config.ModeSSCUHQ: bitrate.Unsupported}},
	budsProfile("Buds FE", "buds fe", 3),
	budsProfile("Buds Core", "buds core", 3),
	budsProfile("Buds3", "buds3", 3),
	budsProfile("Buds3 Pro", "buds3 pro", 4),
	budsProfile("Buds3 FE", "buds3 fe", 3),
	budsProfile("Buds4", "buds4", 4),
	budsProfile("Buds4 Pro", "buds4 pro", 4),
}

const ProfileFilename = "profiles.json"

func standardCommands(modes uint8) buds.ControlCommands {
	if modes == 0 {
		return buds.ControlCommands{Equalizer: 0x86}
	}
	return (buds.ControlCommands{NoiseModes: modes}).WithDefaults()
}

func budsProfile(model, name string, modes uint8) profile {
	return profile{Model: "Samsung Galaxy " + model, NameMatch: name, Commands: standardCommands(modes)}
}

func findProfile(records []profile, id DevID, name string) *profile {
	named := findNamedProfile(records, name, DevID{})
	if id.Vendor == 0 {
		return named
	}
	if exactName := findNamedProfile(records, name, id); named != nil && exactName != nil &&
		normalizeName(exactName.NameMatch) == normalizeName(named.NameMatch) {
		return exactName
	}
	if named != nil && (!named.ID.Valid() || named.ID == id) {
		return named
	}
	var exact *profile
	for i := range records {
		if records[i].ID != id {
			continue
		}
		if exact != nil {
			return nil // The Device ID alone cannot identify the model.
		}
		exact = &records[i]
	}
	if named != nil && exact != nil && exact.NameMatch != "" {
		return nil // The name and Device ID refer to different known profiles.
	}
	return exact
}

func normalizeName(s string) string {
	s = strings.ToLower(strings.TrimSpace(s))
	s = strings.TrimPrefix(s, "samsung ")
	s = strings.TrimPrefix(s, "galaxy ")
	if strings.HasPrefix(s, "buds ") && len(s) > 5 && s[5] >= '0' && s[5] <= '9' {
		s = "buds" + s[5:]
	}
	return strings.Replace(s, "buds plus", "buds+", 1)
}

func findNamedProfile(records []profile, name string, requiredID DevID) *profile {
	name = normalizeName(name)
	var best *profile
	bestLen := 0
	for i := range records {
		if requiredID.Vendor != 0 && records[i].ID != requiredID {
			continue
		}
		match := normalizeName(records[i].NameMatch)
		if len(match) <= bestLen {
			continue
		}
		if name == match || strings.HasPrefix(name, match+"(") ||
			strings.HasPrefix(name, match+" (") || match != "buds" && strings.HasPrefix(name, match+" ") {
			best, bestLen = &records[i], len(match)
		}
	}
	return best
}

// WorkingMax is the highest bitrate (kbps) checked to work for the codec on
// these headphones, and their model name; 0 = not known, Unsupported = the
// codec does not work on them.
func transportName(native bool) string {
	if native {
		return "windows"
	}
	return "winusb"
}

func (s *ProfileStore) WorkingMax(codec config.Mode, id DevID, name string, native bool) (int, string) {
	return workingMax(s.current(), codec, id, name, native)
}

func (s *ProfileStore) Commands(id DevID, name string) buds.ControlCommands {
	if p := findProfile(s.current(), id, name); p != nil {
		return p.Commands
	}
	return buds.ControlCommands{}
}

func workingMax(profiles []profile, codec config.Mode, id DevID, name string, native bool) (int, string) {
	if p := findProfile(profiles, id, name); p != nil {
		limit := p.Transports[transportName(native)].MaxKbps[codec]
		if limit == 0 {
			limit = p.MaxKbps[codec]
		}
		if limit != 0 {
			return limit, p.Model
		}
	}
	return 0, ""
}
