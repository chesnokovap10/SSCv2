package keys

import (
	"fmt"
	"sync"
	"testing"

	"sscv2/internal/bt"
)

func TestStaleStorePreservesNewBonds(t *testing.T) {
	t.Setenv("APPDATA", t.TempDir())
	engine, err := Open()
	if err != nil {
		t.Fatal(err)
	}
	tray, err := Open()
	if err != nil {
		t.Fatal(err)
	}
	mouse := LE{Addr: "00:11:22:33:44:55", Name: "Mouse"}
	if err := tray.ImportWindows(File{LE: []LE{mouse}}); err != nil {
		t.Fatal(err)
	}
	headphones := bt.Addr{1, 2, 3, 4, 5, 6}
	engine.Put(headphones, bt.LinkKey{}, 7)
	tray.SetName(headphones.String(), "Headphones", 0)
	if got := tray.Snapshot(); len(got.LE) != 1 || got.LE[0] != mouse ||
		len(got.Classic) != 1 || got.Classic[0].Name != "Headphones" {
		t.Fatalf("import, pairing, and name updates should all survive: %+v", got)
	}
	if err := tray.ImportWindows(File{}); err != nil {
		t.Fatal(err)
	}
	engine.Delete(headphones)
	onDisk, err := Open()
	if err != nil {
		t.Fatal(err)
	}
	if got := onDisk.Snapshot(); len(got.LE) != 0 || len(got.Classic) != 0 {
		t.Fatalf("deleted bonds were resurrected: %+v", got)
	}
}

func TestConcurrentStoresKeepBothWriters(t *testing.T) {
	t.Setenv("APPDATA", t.TempDir())
	const writes = 12
	errs := make(chan error, 2)
	start := make(chan struct{})
	var wg sync.WaitGroup
	for writer := 1; writer <= 2; writer++ {
		s, err := Open()
		if err != nil {
			t.Fatal(err)
		}
		wg.Go(func() {
			<-start
			for i := 0; i < writes; i++ {
				addr := fmt.Sprintf("00:00:00:00:%02X:%02X", writer, i)
				if err := s.Merge(File{Classic: []Classic{{Addr: addr}}}); err != nil {
					errs <- err
					return
				}
			}
		})
	}
	close(start)
	wg.Wait()
	close(errs)
	for err := range errs {
		t.Error(err)
	}
	onDisk, err := Open()
	if err != nil {
		t.Fatal(err)
	}
	if got := len(onDisk.Snapshot().Classic); got != 2*writes {
		t.Fatalf("saved %d bonds, want %d", got, 2*writes)
	}
}
