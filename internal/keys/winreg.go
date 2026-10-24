package keys

import (
	"encoding/binary"
	"encoding/hex"
	"fmt"
	"strings"

	"golang.org/x/sys/windows/registry"
)

const (
	bthKeysPath    = `SYSTEM\CurrentControlSet\Services\BTHPORT\Parameters\Keys`
	bthDevicesPath = `SYSTEM\CurrentControlSet\Services\BTHPORT\Parameters\Devices`
)

// macToAddr turns "405ef6b006c2" into "40:5E:F6:B0:06:C2".
func macToAddr(m string) string {
	m = strings.ToUpper(m)
	if len(m) != 12 {
		return m
	}
	var b strings.Builder
	for i := 0; i < 12; i += 2 {
		if i > 0 {
			b.WriteByte(':')
		}
		b.WriteString(m[i : i+2])
	}
	return b.String()
}

func addrToMac(a string) string {
	return strings.ToLower(strings.NewReplacer(":", "", "-", "").Replace(a))
}

func reverse(b []byte) []byte {
	out := make([]byte, len(b))
	for i := range b {
		out[i] = b[len(b)-1-i]
	}
	return out
}

// deviceInfo reads Name/COD of a device from BTHPORT\Parameters\Devices.
func deviceInfo(mac string) (string, uint32) {
	k, err := openKey(registry.LOCAL_MACHINE, bthDevicesPath+`\`+mac, registry.QUERY_VALUE)
	if err != nil {
		return "", 0
	}
	defer k.Close()
	var name string
	if b, _, err := k.GetBinaryValue("Name"); err == nil {
		name = strings.TrimRight(string(b), "\x00")
	}
	cod, _, _ := k.GetIntegerValue("COD")
	return name, uint32(cod)
}

func intValue(k registry.Key, name string) uint64 {
	if v, _, err := k.GetIntegerValue(name); err == nil {
		return v
	}
	if b, _, err := k.GetBinaryValue(name); err == nil && len(b) <= 8 {
		var buf [8]byte
		copy(buf[:], b)
		return binary.LittleEndian.Uint64(buf[:])
	}
	return 0
}

// AdapterBonds is what Windows stores for one local adapter.
type AdapterBonds struct {
	Adapter string `json:"adapter"`
	File
}

// ReadWindows reads all bonds Windows keeps (needs SYSTEM). Classic keys are
// REG_BINARY values named after the device; LE bonds are subkeys holding
// LTK/IRK (over-the-air order -> reversed for BTstack), ERand (REG_QWORD ->
// big-endian bytes), EDIV, KeyLength, Address, AddressType.
func ReadWindows() ([]AdapterBonds, error) {
	root, err := openKey(registry.LOCAL_MACHINE, bthKeysPath, registry.ENUMERATE_SUB_KEYS|registry.QUERY_VALUE)
	if err != nil {
		return nil, fmt.Errorf("нет доступа к ключам Bluetooth Windows (нужна служба или права администратора): %w", err)
	}
	defer root.Close()
	adapters, err := root.ReadSubKeyNames(-1)
	if err != nil {
		return nil, err
	}
	var out []AdapterBonds
	for _, ad := range adapters {
		k, err := openKey(root, ad, registry.ENUMERATE_SUB_KEYS|registry.QUERY_VALUE)
		if err != nil {
			continue
		}
		ab := AdapterBonds{Adapter: macToAddr(ad)}
		ab.File.Adapter = ab.Adapter
		names, _ := k.ReadValueNames(-1)
		for _, n := range names {
			if len(n) != 12 {
				continue // e.g. "CentralIRK", "MasterIRK"
			}
			b, typ, err := k.GetBinaryValue(n)
			if err != nil || typ != registry.BINARY || len(b) != 16 {
				continue
			}
			name, cod := deviceInfo(n)
			// Type 7 = unauthenticated combination key (P-256). Only
			// bookkeeping for BTstack; encryption uses the key itself.
			ab.Classic = append(ab.Classic, Classic{Addr: macToAddr(n), Key: hex.EncodeToString(b), Type: 7, Name: name, CoD: cod})
		}
		subs, _ := k.ReadSubKeyNames(-1)
		for _, sub := range subs {
			lk, err := openKey(k, sub, registry.QUERY_VALUE)
			if err != nil {
				continue
			}
			ltk, _, err := lk.GetBinaryValue("LTK")
			if err != nil || len(ltk) != 16 {
				lk.Close()
				continue
			}
			le := LE{LTK: hex.EncodeToString(reverse(ltk))}
			if irk, _, err := lk.GetBinaryValue("IRK"); err == nil && len(irk) == 16 {
				le.IRK = hex.EncodeToString(reverse(irk))
			}
			erand := intValue(lk, "ERand")
			le.EDIV = uint16(intValue(lk, "EDIV"))
			var r [8]byte
			binary.BigEndian.PutUint64(r[:], erand)
			le.Rand = hex.EncodeToString(r[:])
			le.KeySize = int(intValue(lk, "KeyLength"))
			if le.KeySize < 7 || le.KeySize > 16 {
				le.KeySize = 16
			}
			le.SC = erand == 0 && le.EDIV == 0
			addr := intValue(lk, "Address")
			if addr == 0 {
				le.Addr = macToAddr(sub)
			} else {
				le.Addr = macToAddr(fmt.Sprintf("%012x", addr&0xFFFFFFFFFFFF))
			}
			le.Random = intValue(lk, "AddressType") != 0
			le.Name, _ = deviceInfo(sub)
			lk.Close()
			ab.LE = append(ab.LE, le)
		}
		k.Close()
		out = append(out, ab)
	}
	return out, nil
}

// WriteWindowsClassic stores a BR/EDR link key for adapter/device in the
// Windows registry (needs SYSTEM), so a device paired in WinUSB mode keeps
// working when the adapter returns to Windows.
func WriteWindowsClassic(adapter, device, keyHex string) error {
	b, err := hex.DecodeString(keyHex)
	if err != nil || len(b) != 16 {
		return fmt.Errorf("неверный ключ")
	}
	k, err := createKey(registry.LOCAL_MACHINE, bthKeysPath+`\`+addrToMac(adapter), registry.SET_VALUE)
	if err != nil {
		return fmt.Errorf("запись ключа Windows: %w", err)
	}
	defer k.Close()
	return k.SetBinaryValue(addrToMac(device), b)
}
