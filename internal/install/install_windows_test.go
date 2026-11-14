package install

import (
	"os"
	"path/filepath"
	"testing"
	"time"

	"golang.org/x/sys/windows"
)

func TestFailedExecutableReplacementKeepsPreviousImage(t *testing.T) {
	dir := t.TempDir()
	old, staged := filepath.Join(dir, "ssc.exe"), filepath.Join(dir, "incoming.new")
	if err := os.WriteFile(old, []byte("previous"), 0600); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(staged, []byte("new"), 0600); err != nil {
		t.Fatal(err)
	}
	name := windows.StringToUTF16Ptr(staged)
	h, err := windows.CreateFile(name, windows.GENERIC_READ, windows.FILE_SHARE_READ|windows.FILE_SHARE_WRITE,
		nil, windows.OPEN_EXISTING, 0, 0)
	if err != nil {
		t.Fatal(err)
	}
	defer windows.CloseHandle(h)
	if err := replaceExecutable(staged, old, 20*time.Millisecond); err == nil {
		t.Fatal("replacement succeeded despite a sharing violation")
	}
	if got, err := os.ReadFile(old); err != nil || string(got) != "previous" {
		t.Fatalf("previous image = %q, %v", got, err)
	}
}
