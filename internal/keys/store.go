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
	"strings"
	"sync"

	"golang.org/x/sys/windows"

	"sscv2/internal/bt"
	"sscv2/internal/config"
	"sscv2/internal/i18n"
	"sscv2/internal/logx"
)

// Classic is a BR/EDR bond (headphones, or a classic HID mouse).
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

// IsPeripheral reports the Peripheral major class (mice, keyboards).
func (c Classic) IsPeripheral() bool { return (c.CoD>>8)&0x1F == 0x05 }

// IsPointing reports a pointing device (Peripheral, minor bit "pointing").
func (c Classic) IsPointing() bool { return c.IsPeripheral() && c.CoD&0x80 != 0 }

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
	f, err := readFile(s.path)
	s.f = f
	return s, err
}

func readFile(path string) (File, error) {
	var f File
	b, err := os.ReadFile(path)
	if errors.Is(err, os.ErrNotExist) {
		return f, nil
	}
	if err != nil {
		return f, err
	}
	err = json.Unmarshal(b, &f)
	return f, err
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

// editLocked serializes updates across the tray and engine. Lock a separate
// file so replacing keys.json does not replace the file holding the lock.
func (s *Store) editLocked(edit func(*File) bool) error {
	lock, err := os.OpenFile(s.path+".lock", os.O_CREATE|os.O_RDWR, 0o600)
	if err != nil {
		return err
	}
	defer lock.Close()
	handle := windows.Handle(lock.Fd())
	var region windows.Overlapped
	if err := windows.LockFileEx(handle, windows.LOCKFILE_EXCLUSIVE_LOCK, 0, 1, 0, &region); err != nil {
		return err
	}
	defer windows.UnlockFileEx(handle, 0, 1, 0, &region)
	f, err := readFile(s.path)
	if err != nil {
		return err
	}
	if edit(&f) {
		if err := config.WriteJSONAtomic(s.path, &f); err != nil {
			return err
		}
	}
	s.f = f
	return nil
}

// Merge adds/replaces entries (by address) and saves.
func (s *Store) Merge(in File) error {
	return s.merge(in, false)
}

// ImportWindows replaces LE bonds with the current Windows snapshot.
// Classic bonds may also be learned directly by BTstack.
func (s *Store) ImportWindows(in File) error {
	return s.merge(in, true)
}

func (s *Store) merge(in File, refreshLE bool) error {
	s.mu.Lock()
	defer s.mu.Unlock()
	return s.editLocked(func(f *File) bool {
		if refreshLE {
			f.LE = nil
		}
		if in.Adapter != "" {
			f.Adapter = in.Adapter
		}
		for _, c := range in.Classic {
			f.putClassic(c)
		}
		for _, l := range in.LE {
			replaced := false
			for i := range f.LE {
				if strings.EqualFold(f.LE[i].Addr, l.Addr) {
					f.LE[i] = l
					replaced = true
					break
				}
			}
			if !replaced {
				f.LE = append(f.LE, l)
			}
		}
		return true
	})
}

func (f *File) putClassic(c Classic) {
	for i := range f.Classic {
		if strings.EqualFold(f.Classic[i].Addr, c.Addr) {
			if c.Name == "" {
				c.Name = f.Classic[i].Name
			}
			if c.CoD == 0 {
				c.CoD = f.Classic[i].CoD
			}
			f.Classic[i] = c
			return
		}
	}
	f.Classic = append(f.Classic, c)
}

// SetName records a friendly name for a classic device (e.g. from inquiry).
func (s *Store) SetName(addr, name string, cod uint32) {
	s.mu.Lock()
	defer s.mu.Unlock()
	err := s.editLocked(func(f *File) bool {
		for i := range f.Classic {
			c := &f.Classic[i]
			if !strings.EqualFold(c.Addr, addr) {
				continue
			}
			previous := *c
			if name != "" {
				c.Name = name
			}
			if cod != 0 {
				c.CoD = cod
			}
			return *c != previous
		}
		return false
	})
	if err != nil {
		logx.Printf("save Bluetooth device name: %v", err)
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
	c := Classic{Addr: a.String(), Key: hex.EncodeToString(k[:]), Type: typ}
	err := s.editLocked(func(f *File) bool {
		f.putClassic(c)
		return true
	})
	if err != nil {
		// Keep the live bond usable even if the disk write failed.
		s.f.putClassic(c)
		logx.Printf("save Bluetooth bond: %v", err)
	}
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
	err := s.editLocked(func(f *File) bool {
		return f.deleteClassic(as)
	})
	if err != nil {
		s.f.deleteClassic(as)
		logx.Printf("delete Bluetooth bond: %v", err)
	}
}

func (f *File) deleteClassic(addr string) bool {
	for i, c := range f.Classic {
		if strings.EqualFold(c.Addr, addr) {
			f.Classic = append(f.Classic[:i], f.Classic[i+1:]...)
			return true
		}
	}
	return false
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
	// keys without name/class: take the first one that is not a mouse/keyboard
	if addr == "" {
		for _, c := range s.f.Classic {
			if !c.IsPeripheral() {
				return c, true
			}
		}
	}
	return Classic{}, false
}

// FindClassicMouse returns the first classic pointing device.
func (s *Store) FindClassicMouse() (Classic, bool) {
	s.mu.Lock()
	defer s.mu.Unlock()
	for _, c := range s.f.Classic {
		if c.IsPointing() {
			return c, true
		}
	}
	return Classic{}, false
}
