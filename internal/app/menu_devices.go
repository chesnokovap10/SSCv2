package app

import (
	"strings"

	"sscv2/internal/config"
	"sscv2/internal/ipc"
)

type menuDeviceKind uint8

const (
	menuFound menuDeviceKind = iota
	menuHeadphones
	menuLEMouse
	menuClassicMouse
)

type menuDeviceKey struct {
	kind menuDeviceKind
	addr string
}

type menuDevice struct {
	kind   menuDeviceKind
	device config.Device
}

// menuDeviceID requires a.mu. Keep IDs bound to addresses while a popup or
// queued command can still refer to an older list.
func (a *App) menuDeviceID(kind menuDeviceKind, addr, name string) int {
	key := menuDeviceKey{kind: kind, addr: strings.ToUpper(addr)}
	id, ok := a.menuDeviceIDs[key]
	target := menuDevice{kind: kind, device: config.Device{Addr: addr, Name: name}}
	if ok {
		a.menuDeviceTargets[id-idDeviceBase] = target
		return id
	}
	id = idDeviceBase + len(a.menuDeviceTargets)
	if id >= 0x7000 { // IDs above this point are reserved for tray info rows.
		return 0
	}
	if a.menuDeviceIDs == nil {
		a.menuDeviceIDs = make(map[menuDeviceKey]int)
	}
	a.menuDeviceIDs[key] = id
	a.menuDeviceTargets = append(a.menuDeviceTargets, target)
	return id
}

func (a *App) selectMenuDevice(id int) {
	a.mu.Lock()
	var device *config.Device
	mouse := id == idNoMouse
	if !mouse {
		i := id - idDeviceBase
		if i < 0 || i >= len(a.menuDeviceTargets) {
			a.mu.Unlock()
			return
		}
		target := a.menuDeviceTargets[i]
		device = &target.device
		mouse = target.kind == menuLEMouse || target.kind == menuClassicMouse
	}
	if mouse {
		a.s.Mouse = device
	} else {
		a.s.Headphones = device
	}
	_ = config.Save(a.s)
	eng := a.eng
	a.mu.Unlock()
	if mouse {
		go a.restartWinUSB()
	} else if eng != nil {
		eng.send(ipc.Command{Cmd: "connect", Addr: device.Addr})
	}
}
