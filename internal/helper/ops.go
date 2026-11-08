// Package helper performs the privileged operations (driver switch, reading
// and writing the Windows Bluetooth keys). They run inside the helper service (LocalSystem, no UAC prompts)
// or, when the service is not installed, in a UAC-elevated copy of ssc.exe.
package helper

import (
	"encoding/json"
	"fmt"
	"time"

	"sscv2/internal/driver"
	"sscv2/internal/i18n"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
	"sscv2/internal/logx"
)

// Handle executes one request. Inputs are validated: the service must not
// become a way to rebind arbitrary devices or write arbitrary registry data.
func Handle(req ipc.Request) (resp ipc.Response) {
	if req.Debug {
		stop := logx.Capture()
		defer func() { resp.Log = stop() }()
	}
	defer func() {
		if r := recover(); r != nil {
			resp = ipc.Response{Error: fmt.Sprintf(i18n.T("?????????? ??????: %v", "internal error: %v"), r)}
		}
	}()
	if req.Lang != "" {
		i18n.Set(req.Lang)
	}
	logx.Printf("helper: op=%s", req.Op)
	resp = ipc.Response{Version: ipc.Version}
	fail := func(err error) ipc.Response {
		logx.Printf("helper: %s failed: %v", req.Op, err)
		resp.Error = err.Error()
		return resp
	}
	switch req.Op {
	case "ping":
		resp.OK = true
	case "driver":
		driver.Logf = logx.Printf
		t0 := time.Now()
		defer func() { logx.Printf("helper: driver op took %s", time.Since(t0).Round(time.Millisecond)) }()
		id := driver.USBID{VID: req.VID, PID: req.PID}
		known := false
		for _, k := range driver.KnownMediaTek {
			if k == id {
				known = true
			}
		}
		if !known {
			return fail(fmt.Errorf(i18n.T("?????????? %s ?? ?? ?????? ?????????????? MediaTek", "device %s is not a supported MediaTek adapter"), id))
		}
		driver.Variant = req.Variant
		r, err := driver.Switch(id, req.WinUSB)
		if err != nil {
			return fail(err)
		}
		resp.OK, resp.Message = true, r.Message
	case "test-signing":
		if req.TestSigning == nil {
			return fail(fmt.Errorf("test-signing requires an explicit state"))
		}
		if err := driver.SetTestSigning(*req.TestSigning); err != nil {
			return fail(err)
		}
		resp.OK = true
	case "keys-read":
		bonds, err := keys.ReadWindows()
		if err != nil {
			return fail(err)
		}
		resp.Data, _ = json.Marshal(bonds)
		resp.OK = true
	case "keys-write":
		if err := keys.WriteWindowsClassic(req.Adapter, req.Device, req.Key); err != nil {
			return fail(err)
		}
		resp.OK = true
	default:
		return fail(fmt.Errorf(i18n.T("??????????? ???????? %q", "unknown operation %q"), req.Op))
	}
	return resp
}
