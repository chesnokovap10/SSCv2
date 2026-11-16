package profiles

import (
	"bytes"
	"encoding/json"
	"errors"
	"fmt"
	"maps"
	"os"
	"path/filepath"
	"slices"
	"sync"
	"sync/atomic"

	"sscv2/internal/bitrate"
	"sscv2/internal/buds"
	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

type ProfileStore struct {
	mu      sync.Mutex
	path    string
	pending map[observationKey]observation
	loaded  atomic.Pointer[[]profile]
	seen    bool
}

type observationKey struct {
	id     DevID
	native bool
	mode   config.Mode
}

type observation struct {
	name   string
	caps   *ipc.CodecCapabilities
	stream StreamInfo
}

// OpenProfiles keeps the store usable if the file is temporarily inaccessible.
func OpenProfiles(path string) (*ProfileStore, error) {
	s := &ProfileStore{path: path, pending: make(map[observationKey]observation)}
	return s, s.Refresh()
}

func (s *ProfileStore) current() []profile {
	if s != nil {
		if records := s.loaded.Load(); records != nil {
			return *records
		}
	}
	return defaultProfiles
}

func (s *ProfileStore) Refresh() error {
	if s == nil {
		return nil
	}
	s.mu.Lock()
	defer s.mu.Unlock()
	return s.refreshLocked()
}

func (s *ProfileStore) Observe(id DevID, name string, native bool, caps *ipc.CodecCapabilities, mode config.Mode, stream StreamInfo) error {
	if !id.Valid() {
		return nil
	}
	s.mu.Lock()
	defer s.mu.Unlock()
	if caps != nil {
		key := observationKey{id: id, native: native}
		old := s.pending[key].caps
		if old == nil || !caps.Partial || old.Partial {
			value := *caps
			s.pending[key] = observation{name: name, caps: &value}
		}
	}
	if mode.Streaming() && stream.Kbps > 0 {
		s.pending[observationKey{id: id, native: native, mode: mode}] = observation{name: name, stream: stream}
	}
	return s.refreshLocked()
}

func (s *ProfileStore) refreshLocked() error {
	data, err := os.ReadFile(s.path)
	var legacyPath string
	var legacyData []byte
	var records []profile
	switch {
	case err == nil:
		s.seen = true
		records, err = decodeProfiles(data)
		if err != nil {
			return err
		}
	case !errors.Is(err, os.ErrNotExist) || s.seen:
		// The editor may temporarily remove an existing file during a save.
		return err
	case filepath.Base(s.path) == ProfileFilename:
		legacyPath = filepath.Join(filepath.Dir(s.path), "bitrate-profiles.json")
		legacyData, err = os.ReadFile(legacyPath)
		if !errors.Is(err, os.ErrNotExist) {
			if err != nil {
				return err
			}
			records, err = decodeProfiles(legacyData)
			if err != nil {
				return fmt.Errorf("legacy profiles: %w", err)
			}
		}
	}

	changed := data == nil
	for _, builtin := range defaultProfiles {
		exists := slices.ContainsFunc(records, func(record profile) bool {
			return normalizeName(record.NameMatch) == builtin.NameMatch || normalizeName(record.Model) == builtin.NameMatch
		})
		if !exists {
			records = append(records, builtin)
			changed = true
		}
	}
	// Publish valid manual changes even if the next write is denied.
	s.loaded.Store(&records)
	merged := slices.Clone(records)
	for key, sample := range s.pending {
		if mergeObservation(&merged, key, sample) {
			changed = true
		}
	}
	if changed {
		if err := config.ReplaceJSONAtomic(s.path, merged, data); err != nil {
			return err
		}
		s.seen = true
		s.loaded.Store(&merged)
	}
	clear(s.pending)
	if legacyData != nil {
		// An editor may have changed the old file during migration. Preserve
		// that copy in this case, or if Windows still has it locked.
		current, err := os.ReadFile(legacyPath)
		if err == nil && bytes.Equal(current, legacyData) {
			if err := os.Remove(legacyPath); err != nil && !errors.Is(err, os.ErrNotExist) {
				return fmt.Errorf("new profiles saved, old file still present: %w", err)
			}
		}
	}
	return nil
}

func decodeProfiles(data []byte) ([]profile, error) {
	data = bytes.TrimPrefix(data, []byte{0xef, 0xbb, 0xbf})
	if !json.Valid(data) {
		return nil, errors.New("invalid profile JSON")
	}
	var records []profile
	decoder := json.NewDecoder(bytes.NewReader(data))
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&records); err != nil {
		return nil, err
	}
	if err := validateProfiles(records); err != nil {
		return nil, err
	}
	return records, nil
}

func validateProfiles(records []profile) error {
	for _, record := range records {
		if record.Commands.NoiseModes > buds.NoiseAdaptive+1 {
			return fmt.Errorf("%s: commands.noiseModes must be between 0 and 4", record.Model)
		}
		if err := validateLimits(record.MaxKbps); err != nil {
			return fmt.Errorf("%s: %w", record.Model, err)
		}
		for transport, entry := range record.Transports {
			if err := validateLimits(entry.MaxKbps); err != nil {
				return fmt.Errorf("%s (%s): %w", record.Model, transport, err)
			}
		}
	}
	return nil
}

func validateLimits(limits map[config.Mode]int) error {
	for mode, limit := range limits {
		if !mode.Streaming() {
			return fmt.Errorf("unknown codec %q in verifiedMaxKbps", mode)
		}
		choices := bitrate.Choices(mode)
		if limit < bitrate.Unsupported || limit > choices[len(choices)-1] {
			return fmt.Errorf("invalid verifiedMaxKbps for %s: %d", mode, limit)
		}
		if mode.UsesSSC() && limit > 0 && !slices.Contains(choices, limit) {
			return fmt.Errorf("invalid SSC bitrate for %s: %d", mode, limit)
		}
	}
	return nil
}

func mergeObservation(records *[]profile, key observationKey, sample observation) bool {
	p := findProfile(*records, key.id, sample.name)
	if p == nil {
		shared := slices.ContainsFunc(*records, func(record profile) bool { return record.ID == key.id })
		name := sample.name
		if shared && name == "" {
			return false // A shared Device ID needs a model name.
		}
		if name == "" {
			name = fmt.Sprintf("Bluetooth %04X:%04X", key.id.Vendor, key.id.Product)
		}
		entry := profile{Model: name, ID: key.id, Commands: (buds.ControlCommands{}).WithDefaults()}
		if factory := findNamedProfile(*records, sample.name, DevID{}); factory != nil {
			entry.Model, entry.NameMatch, entry.Commands = factory.Model, factory.NameMatch, factory.Commands
		} else if shared {
			entry.NameMatch = sample.name
		}
		*records = append(*records, entry)
		p = &(*records)[len(*records)-1]
	}
	bindID := !p.ID.Valid()
	if bindID {
		p.ID = key.id
	}
	transport := transportName(key.native)
	entry := p.Transports[transport]
	if sample.caps != nil {
		if entry.Advertised != nil && (*entry.Advertised == *sample.caps || sample.caps.Partial && !entry.Advertised.Partial) {
			return bindID
		}
		entry.Advertised = sample.caps
	} else {
		if entry.Streams[key.mode] == sample.stream {
			return bindID
		}
		entry.Streams = cloneMap(entry.Streams)
		entry.Streams[key.mode] = sample.stream
	}
	p.Transports = cloneMap(p.Transports)
	p.Transports[transport] = entry
	return true
}

func cloneMap[K comparable, V any](src map[K]V) map[K]V {
	if src == nil {
		return make(map[K]V)
	}
	return maps.Clone(src)
}
