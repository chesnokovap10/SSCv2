package app

import (
	"encoding/json"

	"golang.org/x/sys/windows"
)

func jsonUnmarshal(b []byte, v any) error { return json.Unmarshal(b, v) }

func openTarget(target string) {
	verb, _ := windows.UTF16PtrFromString("open")
	path, _ := windows.UTF16PtrFromString(target)
	if err := windows.ShellExecute(0, verb, path, nil, nil, windows.SW_SHOWNORMAL); err != nil {
		logf("open %s: %v", target, err)
	}
}
