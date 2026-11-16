package profiles

import (
	"path/filepath"
	"testing"

	"golang.org/x/sys/windows"

	"sscv2/internal/config"
)

func TestProfileWriteRetriesAfterWindowsSharingViolation(t *testing.T) {
	path := filepath.Join(t.TempDir(), ProfileFilename)
	store, err := OpenProfiles(path)
	if err != nil {
		t.Fatal(err)
	}
	filename, err := windows.UTF16PtrFromString(path)
	if err != nil {
		t.Fatal(err)
	}
	handle, err := windows.CreateFile(filename, windows.GENERIC_READ, windows.FILE_SHARE_READ, nil, windows.OPEN_EXISTING, 0, 0)
	if err != nil {
		t.Fatal(err)
	}
	id := DevID{Source: 1, Vendor: 117, Product: 4321}
	stream := StreamInfo{Kbps: 192}
	err = store.Observe(id, "Buds Test", true, nil, config.ModeAAC, stream)
	if closeErr := windows.CloseHandle(handle); closeErr != nil {
		t.Fatal(closeErr)
	}
	if err == nil {
		t.Fatal("expected the editor lock to prevent an automatic write")
	}
	if err := store.Refresh(); err != nil {
		t.Fatal(err)
	}
	p := findProfile(store.current(), id, "")
	if p == nil || p.Transports["windows"].Streams[config.ModeAAC] != stream {
		t.Fatalf("stream observation did not survive the write error: %+v", p)
	}
}
