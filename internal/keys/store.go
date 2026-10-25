// Package keys stores Bluetooth bonding keys for the WinUSB mode and moves
// them between Windows and BTstack.
//
// The headphones and the mouse are paired with Windows. In WinUSB mode the
// same controller (same BD_ADDR) talks to them through BTstack, so reusing
// the Windows keys lets them reconnect without pairing again - and without
// breaking the Windows bond. Windows keeps the keys in
// HKLM\SYSTEM\CurrentControlSet\Services\BTHPORT\Parameters\Keys, readable
// only by SYSTEM, which is why the import runs in the helper service.
package keys

import (
	"encoding/hex"
	"encoding/json"
	"errors"
	"os"
	"sscv2/internal/i18n"
	"strings"
	"sync"

	"sscv2/internal/bt"
	"sscv2/internal/config"
)

// Classic is a BR/EDR bond (headphones).
type Classic struct {
	Addr string `json:"addr"`
	Key  string `json:"key"`  // 32 hex chars, HCI byte order
	Type int    `json:"type"` // link_key_type_t
	Name string `json:"name,omitempty"`
	CoD  uint32 `json:"cod,omitempty"`
}

// IsAudio reports a Class-of-Device in the Audio/Video major class, or a
// Galaxy Buds name.
func (c Classic) IsAudio() bool {
	return (c.CoD>>8)&0x1F == 0x04 || strings.Contains(strings.ToLower(c.Name), "buds")
}

// LE is an LE bond (mouse), keys already in BTstack byte order.
type LE struct {
	Addr    string `json:"addr"`
	Random  bool   `json:"random"`
	LTK     string `json:"ltk"`
	IRK     string `json:"irk,omitempty"`
	EDIV    uint16 `json:"ediv"`
	Rand    string `json:"rand"` // 16 hex chars (8 bytes, big-endian)
	KeySize int    `json:"keySize"`
	SC      bool   `json:"sc"`
	Name    string `json:"name,omitempty"`
}

// File is the content of keys.json.
type File struct {
	Adapter string    `json:"adapter,omitempty"` // controller BD_ADDR the keys belong to
	Classic []Classic `json:"classic"`
	LE      []LE      `json:"le"`
}

// Store is keys.json in memory; it implements bt.KeyStore.
type Store struct {
	mu   sync.Mutex
	path string
	f    File
	// OnChange is called (outside the lock) after a key was added/changed.
	OnChange func()
}

// Open loads keys.json (missing file = empty store).
func Open() (*Store, error) {
	s := &Store{path: config.KeysPath()}
	b, err := os.ReadFile(s.path)
	if errors.Is(err, os.ErrNotExist) {
		return s, nil
	}
	if err != nil {
		return s, err
	}
	err = json.Unmarshal(b, &s.f)
	return s, err
}

// Snapshot returns a copy of the file content.
func (s *Store) Snapshot() File {
	s.mu.Lock()
	defer s.mu.Unlock()
	f := File{Adapter: s.f.Adapter}
	f.Classic = append(f.Classic, s.f.Classic...)
	f.LE = append(f.LE, s.f.LE...)
	return f
}

func (s *Store) saveLocked() error {
	return config.WriteJSONAtomic(s.path, &s.f)
}

// Merge adds/replaces entries (by address) and saves.
func (s *Store) Merge(in File) error {
	s.mu.Lock()
	if in.Adapter != "" {
		s.f.Adapter = in.Adapter
	}
	for _, c := range in.Classic {
		s.putClassicLocked(c)
	}
	for _, l := range in.LE {
		replaced := false
		for i := range s.f.LE {
			if strings.EqualFold(s.f.LE[i].Addr, l.Addr) {
				s.f.LE[i] = l
				replaced = true
			}
		}
		if !replaced {
			s.f.LE = append(s.f.LE, l)
		}
	}
	err := s.saveLocked()
	s.mu.Unlock()
	return err
}

func (s *Store) putClassicLocked(c Classic) {
	for i := range s.f.Classic {
		if strings.EqualFold(s.f.Classic[i].Addr, c.Addr) {
			if c.Name == "" {
				c.Name = s.f.Classic[i].Name
			}
			if c.CoD == 0 {
				c.CoD = s.f.Classic[i].CoD
			}
			s.f.Classic[i] = c
			return
		}
	}
	s.f.Classic = append(s.f.Classic, c)
}

// SetName records a friendly name for a classic device (e.g. from inquiry).
func (s *Store) SetName(addr, name string, cod uint32) {
	s.mu.Lock()
	defer s.mu.Unlock()
	for i := range s.f.Classic {
		if strings.EqualFold(s.f.Classic[i].Addr, addr) {
			if name != "" {
				s.f.Classic[i].Name = name
			}
			if cod != 0 {
				s.f.Classic[i].CoD = cod
			}
			_ = s.saveLocked()
		}
	}
}

// ---- bt.KeyStore (called on the BTstack thread) ----------------------------

func parseKey(h string) (bt.LinkKey, bool) {
	var k bt.LinkKey
	b, err := hex.DecodeString(h)
	if err != nil || len(b) != 16 {
		return k, false
	}
	copy(k[:], b)
	return k, true
}

func (s *Store) Get(a bt.Addr) (bt.LinkKey, int, bool) {
	s.mu.Lock()
	defer s.mu.Unlock()
	as := a.String()
	for _, c := range s.f.Classic {
		if strings.EqualFold(c.Addr, as) {
			k, ok := parseKey(c.Key)
			return k, c.Type, ok
		}
	}
	return bt.LinkKey{}, 0, false
}

func (s *Store) Put(a bt.Addr, k bt.LinkKey, typ int) {
	s.mu.Lock()
	s.putClassicLocked(Classic{Addr: a.String(), Key: hex.EncodeToString(k[:]), Type: typ})
	_ = s.saveLocked()
	cb := s.OnChange
	s.mu.Unlock()
	if cb != nil {
		cb()
	}
}

func (s *Store) Delete(a bt.Addr) {
	s.mu.Lock()
	defer s.mu.Unlock()
	as := a.String()
	out := s.f.Classic[:0]
	for _, c := range s.f.Classic {
		if !strings.EqualFold(c.Addr, as) {
			out = append(out, c)
		}
	}
	s.f.Classic = out
	_ = s.saveLocked()
}

func (s *Store) At(i int) (bt.Addr, bt.LinkKey, int, bool) {
	s.mu.Lock()
	defer s.mu.Unlock()
	if i < 0 || i >= len(s.f.Classic) {
		return bt.Addr{}, bt.LinkKey{}, 0, false
	}
	c := s.f.Classic[i]
	a, err := bt.ParseAddr(c.Addr)
	k, ok := parseKey(c.Key)
	if err != nil || !ok {
		return bt.Addr{}, bt.LinkKey{}, 0, false
	}
	return a, k, c.Type, true
}

// Bond converts an LE entry to a bt.LEBond.
func (l LE) Bond() (*bt.LEBond, error) {
	a, err := bt.ParseAddr(l.Addr)
	if err != nil {
		return nil, err
	}
	b := &bt.LEBond{Addr: a, Random: l.Random, EDIV: l.EDIV, KeySize: l.KeySize, SecureConn: l.SC}
	ltk, err := hex.DecodeString(l.LTK)
	if err != nil || len(ltk) != 16 {
		return nil, errors.New(i18n.T("нет LTK мыши", "no LTK for the mouse"))
	}
	copy(b.LTK[:], ltk)
	if irk, err := hex.DecodeString(l.IRK); err == nil && len(irk) == 16 {
		copy(b.IRK[:], irk)
	}
	if r, err := hex.DecodeString(l.Rand); err == nil && len(r) == 8 {
		copy(b.Rand[:], r)
	}
	return b, nil
}

// FindLE returns the LE bond for addr ("" = first one).
func (s *Store) FindLE(addr string) (LE, bool) {
	s.mu.Lock()
	defer s.mu.Unlock()
	for _, l := range s.f.LE {
		if addr == "" || strings.EqualFold(l.Addr, addr) {
			return l, true
		}
	}
	return LE{}, false
}

// FindClassic returns the classic bond for addr ("" = first audio device).
func (s *Store) FindClassic(addr string) (Classic, bool) {
	s.mu.Lock()
	defer s.mu.Unlock()
	for _, c := range s.f.Classic {
		if (addr == "" && c.IsAudio()) || (addr != "" && strings.EqualFold(c.Addr, addr)) {
			return c, true
		}
	}
	// keys without name/class: take the first one
	if addr == "" && len(s.f.Classic) > 0 {
		return s.f.Classic[0], true
	}
	return Classic{}, false
}
