package install

import (
	"os"
	"path/filepath"
	"testing"
)

func TestAutoStartRequiresInstalledExecutable(t *testing.T) {
	t.Setenv("ProgramFiles", t.TempDir())
	if _, err := autoStartCommand(Exe()); !os.IsNotExist(err) {
		t.Fatalf("expected missing executable error, got %v", err)
	}
	if err := os.MkdirAll(Exe(), 0o755); err != nil {
		t.Fatal(err)
	}
	if _, err := autoStartCommand(Exe()); err == nil {
		t.Fatal("accepted a directory as the executable")
	}
}

func TestAutoStartQuotesInstalledPath(t *testing.T) {
	exe := filepath.Join(t.TempDir(), "Program Files", "ssc.exe")
	if err := os.Mkdir(filepath.Dir(exe), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(exe, nil, 0o600); err != nil {
		t.Fatal(err)
	}
	if command, err := autoStartCommand(exe); err != nil || command != `"`+exe+`"` {
		t.Fatalf("startup command = %q, %v", command, err)
	}
}
