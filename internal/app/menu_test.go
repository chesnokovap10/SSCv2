package app

import (
	"strings"
	"testing"

	"sscv2/internal/config"
	"sscv2/internal/i18n"
	"sscv2/internal/tray"
)

func dump(t *testing.T, items []tray.Item, depth int) {
	for _, it := range items {
		switch {
		case it.Separator:
			t.Logf("%s----", strings.Repeat("  ", depth))
		default:
			mark := "  "
			if it.Checked {
				mark = "* "
			}
			if it.Disabled || (it.ID == 0 && it.Sub == nil) {
				mark += "(x) "
			}
			t.Logf("%s%s%s [%d]", strings.Repeat("  ", depth), mark, it.Text, it.ID)
			if it.Sub != nil {
				dump(t, it.Sub, depth+1)
			}
		}
	}
}

func TestMenu(t *testing.T) {
	// refreshAdapter saves the settings when it finds the adapter: keep that
	// away from the real %APPDATA%\SSCv2\settings.json
	t.Setenv("APPDATA", t.TempDir())
	a := &App{mode: config.ModeOff, s: &config.Settings{Mode: config.ModeOff}}
	a.refreshAdapter()
	dump(t, a.menu(), 0)
}

func TestMenuEnglishUHQ(t *testing.T) {
	t.Setenv("APPDATA", t.TempDir())
	i18n.Set(i18n.EN)
	defer i18n.Set("")
	a := &App{mode: config.ModeSSCUHQ, s: &config.Settings{Mode: config.ModeSSCUHQ, SSCUHQBitrate: 584}}
	items := a.menu()
	dump(t, items, 0)
	var bitrate *tray.Item
	for i := range items {
		if strings.HasPrefix(items[i].Text, "Bitrate: ") {
			bitrate = &items[i]
		}
	}
	if bitrate == nil || len(bitrate.Sub) != 7 { // 886 needs Max MTU
		t.Fatalf("bitrate submenu: %+v", bitrate)
	}
	checked := 0
	for _, it := range bitrate.Sub {
		if it.Checked {
			checked = it.ID - idBitrateBase
		}
	}
	if checked != 584 {
		t.Errorf("checked bitrate %d, want 584", checked)
	}
}

func TestMenuAACNoMaxMTU(t *testing.T) {
	t.Setenv("APPDATA", t.TempDir())
	a := &App{mode: config.ModeAAC, s: &config.Settings{Mode: config.ModeAAC, AACBitrate: 256}}
	for _, it := range a.menu() {
		if it.Sub == nil || it.Sub[0].ID != idBitrateBase {
			continue
		}
		for _, b := range it.Sub {
			if b.ID == idBitrateBase+256 {
				t.Error("256 offered without Max MTU")
			}
			if b.ID == idBitrateBase && !b.Checked {
				t.Error("saved 256 without Max MTU should show as Auto")
			}
		}
		return
	}
	t.Fatal("no bitrate submenu")
}
