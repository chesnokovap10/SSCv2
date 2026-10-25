package driver

import (
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"testing"
)

// TestScriptParses: every switch script variant is valid PowerShell.
func TestScriptParses(t *testing.T) {
	ps, err := exec.LookPath("powershell.exe")
	if err != nil {
		t.Skip("no powershell")
	}
	for _, enable := range []bool{true, false} {
		s := buildScript(enable, []string{"oem1.inf"}, `USB\VID_0489&PID_E0E2\0`, `C:\x\a.inf`, `C:\x\a.cat`, `C:\x\signtool.exe`, `C:\x\log.txt`)
		for _, fn := range []string{"function Present", "function Reenumerate", "rescanning"} {
			if !strings.Contains(s, fn) {
				t.Errorf("enable=%v: %q missing", enable, fn)
			}
		}
		f := filepath.Join(t.TempDir(), "s.ps1")
		if err := os.WriteFile(f, []byte(s), 0o600); err != nil {
			t.Fatal(err)
		}
		out, err := exec.Command(ps, "-NoProfile", "-NonInteractive", "-Command",
			`$e=$null; [void][System.Management.Automation.Language.Parser]::ParseFile('`+f+`',[ref]$null,[ref]$e); if ($e) { $e | % { $_.ToString() }; exit 1 }`).CombinedOutput()
		if err != nil {
			t.Errorf("enable=%v: parse errors:\n%s", enable, out)
		}
	}
}
