package app

import (
	"encoding/json"

	"golang.org/x/sys/windows"
)

func jsonUnmarshal(b []byte, v any) error { return json.Unmarshal(b, v) }

// openFolder shows a folder in Explorer (ShellExecute "open", which hands
// the folder to the running shell).
func openFolder(dir string) {
	verb, _ := windows.UTF16PtrFromString("open")
	path, _ := windows.UTF16PtrFromString(dir)
	if err := windows.ShellExecute(0, verb, path, nil, nil, windows.SW_SHOWNORMAL); err != nil {
		logf("open folder %s: %v", dir, err)
	}
}
