package logx

import (
	"os"
	"path/filepath"
	"strings"
	"testing"
)

func TestOverlappingCapturesRemainSubscribed(t *testing.T) {
	Open(t.TempDir(), "test.log", "test")
	defer Close()
	a := Capture()
	Printf("a1")
	b := Capture()
	Printf("b1")
	first := a()
	Printf("b2")
	second := b()
	if len(first) != 2 || len(second) != 2 || !strings.Contains(second[1], "b2") {
		t.Fatalf("captures: %v / %v", first, second)
	}
}

func TestSharedJournalRotatesWithOpenWriters(t *testing.T) {
	path := filepath.Join(t.TempDir(), "debug.log")
	a, err := openJournal(path, 64)
	if err != nil {
		t.Fatal(err)
	}
	defer a.Close()
	b, err := openJournal(path, 64)
	if err != nil {
		t.Fatal(err)
	}
	defer b.Close()
	for i := 0; i < 20; i++ {
		for _, w := range []*journal{a, b} {
			if _, err := w.Write([]byte("0123456789abcdef\n")); err != nil {
				t.Fatal(err)
			}
		}
	}
	for _, name := range []string{path, path + ".old"} {
		info, err := os.Stat(name)
		if err != nil {
			t.Fatal(err)
		}
		if info.Size() > 64 || info.Size() == 0 {
			t.Fatalf("size %d", info.Size())
		}
	}
}
