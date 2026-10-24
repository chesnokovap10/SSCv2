package app

import (
	"strings"
	"testing"

	"sscv2/internal/config"
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
	a := &App{mode: config.ModeOff, s: &config.Settings{Mode: config.ModeOff}}
	a.refreshAdapter()
	dump(t, a.menu(), 0)
}
