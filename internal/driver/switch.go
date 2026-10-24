package driver

// Switching to WinUSB needs a signed driver package. Instead of keeping a
// long-lived self-signed root certificate on the machine, every switch uses
// an ephemeral signer, all inside one PowerShell script:
//
//   create cert (non-exportable key, valid 1 day) -> trust it (Root +
//   TrustedPublisher) -> sign catalog -> pnputil /add-driver /install onto
//   the adapter's devnode (in place) -> finally delete the cert with its key.
//
// Restore deletes the package with /uninstall: Windows puts the original
// driver back on the same devnode. Device ids below the adapter stay the
// same, so Windows keeps knowing the headphones (their endpoints, volume).
//
// The installed package stays valid because signature checks happen at
// staging/install time, and winusb.sys itself is Microsoft-signed.
// Restoring BTHUSB needs no certificate.
//
// Windows' AVCTP service (AVRCP) holds the headphones' AVRCP transport open;
// pulling the adapter from under it left it wedged, so it is stopped first
// and started again on restore.
//
// Everything here must run elevated (helper service or UAC'd helper).

import (
	"errors"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"syscall"
	"time"
)

const (
	signerSubject = "SSCv2 Driver Signer"
	infDeviceName = "SSCv2 WinUSB Bluetooth"
	catName       = "sscv2_winusb.cat"
	infName       = "sscv2_winusb.inf"
)

// Logf, when set, receives the switch script's timed log.
var Logf func(string, ...any)

// Result of a switch.
type Result struct {
	Changed bool
	Message string
}

func psLit(s string) string { return "'" + strings.ReplaceAll(s, "'", "''") + "'" }

// findSDKTool locates makecat.exe / signtool.exe in the Windows 10+ SDK,
// preferring the x64 build.
func findSDKTool(name string) string {
	roots := []string{
		`C:\Program Files (x86)\Windows Kits\10\bin`,
		`C:\Program Files\Windows Kits\10\bin`,
	}
	for _, root := range roots {
		var fallback string
		_ = filepath.WalkDir(root, func(p string, d os.DirEntry, err error) error {
			if err != nil || d.IsDir() {
				return nil
			}
			if strings.EqualFold(d.Name(), name) {
				if strings.Contains(strings.ToLower(p), `\x64\`) {
					fallback = p
					return filepath.SkipAll
				}
				if fallback == "" {
					fallback = p
				}
			}
			return nil
		})
		if fallback != "" {
			return fallback
		}
	}
	return ""
}

// findWinUSBInfs lists oemNN.inf packages that reference winusb.inf AND
// carry this VID:PID (ours, an older build's, or Zadig's). Vendor BTHUSB
// packages never reference winusb.inf, so they are never touched.
func findWinUSBInfs(id USBID) []string {
	dir := filepath.Join(os.Getenv("WINDIR"), "INF")
	matches, _ := filepath.Glob(filepath.Join(dir, "oem*.inf"))
	needle := strings.ToLower(fmt.Sprintf("vid_%04x&pid_%04x", id.VID, id.PID))
	var out []string
	for _, m := range matches {
		b, err := os.ReadFile(m)
		if err != nil {
			continue
		}
		if len(b) > 256<<10 {
			b = b[:256<<10]
		}
		t := strings.ToLower(decodeInf(b))
		if strings.Contains(t, needle) && strings.Contains(t, "winusb.inf") {
			out = append(out, filepath.Base(m))
		}
	}
	return out
}

// decodeInf handles UTF-16LE INF files (common for vendor packages).
func decodeInf(b []byte) string {
	if len(b) >= 2 && b[0] == 0xFF && b[1] == 0xFE {
		u := make([]uint16, 0, len(b)/2)
		for i := 2; i+1 < len(b); i += 2 {
			u = append(u, uint16(b[i])|uint16(b[i+1])<<8)
		}
		return syscall.UTF16ToString(u)
	}
	return string(b)
}

func infText(id USBID) string {
	return strings.ReplaceAll(fmt.Sprintf(`[Version]
Signature="$Windows NT$"
Class=USBDevice
ClassGuid={88bae032-5a81-49f0-bc3d-a4ff138216d6}
Provider="SSCv2"
DriverVer=10/24/2026,2.0.0.0
CatalogFile=%s

[Manufacturer]
%%Mfg%%=DeviceInstall,NTamd64

[DeviceInstall.NTamd64]
%%DeviceName%%=USB_Install, USB\VID_%04X&PID_%04X

[USB_Install]
Include = winusb.inf
Needs   = WINUSB.NT

[USB_Install.Services]
Include    = winusb.inf
Needs      = WINUSB.NT.Services

[USB_Install.HW]
AddReg = Dev_AddReg

[Dev_AddReg]
HKR,,DeviceInterfaceGUIDs,0x10000,"{3fe6abe9-5d35-4cc6-9b10-78e6f199c952}"

[Strings]
Mfg="SSCv2"
DeviceName="%s"
`, catName, id.VID, id.PID, infDeviceName), "\n", "\r\n")
}

// run starts a hidden console program and waits (with a timeout).
func run(timeout time.Duration, exe string, args ...string) (string, error) {
	cmd := exec.Command(exe, args...)
	cmd.SysProcAttr = &syscall.SysProcAttr{HideWindow: true, CreationFlags: 0x08000000}
	type res struct {
		out []byte
		err error
	}
	ch := make(chan res, 1)
	go func() {
		o, e := cmd.CombinedOutput()
		ch <- res{o, e}
	}()
	select {
	case r := <-ch:
		return string(r.out), r.err
	case <-time.After(timeout):
		if cmd.Process != nil {
			_ = cmd.Process.Kill()
		}
		return "", fmt.Errorf("%s: timeout after %s", filepath.Base(exe), timeout)
	}
}

func makeCatalog(dir, infPath string) error {
	makecat := findSDKTool("makecat.exe")
	if makecat == "" {
		return errors.New("makecat.exe из Windows SDK не найден (нужны инструменты Windows 10+ SDK)")
	}
	ddf := filepath.Join(dir, "sscv2_winusb.ddf")
	body := "[CatalogHeader]\r\nName=" + catName + "\r\nResultDir=" + dir +
		"\r\nCatalogVersion=2\r\nHashAlgorithms=SHA256\r\nPageHashes=false\r\nEncodingType=0x00010001\r\n\r\n" +
		"[CatalogFiles]\r\n<HASH>" + infName + "=" + infPath + "\r\n"
	if err := os.WriteFile(ddf, []byte(body), 0o644); err != nil {
		return err
	}
	defer os.Remove(ddf)
	if out, err := run(60*time.Second, makecat, ddf); err != nil {
		return fmt.Errorf("makecat: %v %s", err, strings.TrimSpace(out))
	}
	if _, err := os.Stat(filepath.Join(dir, catName)); err != nil {
		return errors.New("makecat не создал каталог")
	}
	return nil
}

// Variant (diagnostics): "remove" switches the old way, by uninstalling the
// devnode subtree (pnputil /remove-device /subtree) and re-scanning.
//
// Default: the driver is changed in place. Uninstalling the subtree deletes
// the registry keys of the Bluetooth enumerator below the adapter, so after
// every switch Windows got a new ParentIdPrefix and saw the headphones as a
// NEW device: new audio endpoints with no remembered volume (100 %), a
// restart right after their first install (output bounced headphones ->
// speakers -> headphones) and a pile of phantom devices.
var Variant string

func buildScript(enable bool, oldInfs []string, instanceID, infPath, catPath, signtool, logPath string) string {
	inPlace := Variant != "remove" && instanceID != ""
	var s strings.Builder
	w := func(line string) { s.WriteString(line); s.WriteString("\r\n") }
	w("$ErrorActionPreference = 'Stop'")
	w("$log = " + psLit(logPath))
	w("$id = " + psLit(instanceID))
	w("Set-Content -Path $log -Value '' -Encoding UTF8")
	w("function Log([string]$m) { Add-Content -Path $log -Value ((Get-Date -Format 'HH:mm:ss.fff') + ' ' + $m) -Encoding UTF8 }")
	// Every tool call is time-limited: a wedged PnP operation must never hang.
	w(`function Run([string]$exe, [string[]]$a, [int[]]$ok = @(0), [int]$timeout = 90) {
  $ErrorActionPreference = 'Continue'
  $q = @($a | ForEach-Object { if ($_ -match '\s') { '"' + $_ + '"' } else { $_ } })
  $o = [IO.Path]::GetTempFileName()
  $p = Start-Process -FilePath $exe -ArgumentList $q -NoNewWindow -PassThru -RedirectStandardOutput $o
  $null = $p.Handle
  if (-not $p.WaitForExit($timeout * 1000)) {
    Stop-Process -Id $p.Id -Force -ErrorAction SilentlyContinue
    Log "> $exe $($a -join ' ') -> TIMEOUT after $timeout s"
    throw "$exe timed out"
  }
  $code = $p.ExitCode
  $out = Get-Content $o -Raw -ErrorAction SilentlyContinue; Remove-Item $o -ErrorAction SilentlyContinue
  Log ("> $exe $($a -join ' ') -> $code")
  if ($ok -notcontains $code) { Log $out; throw "$exe failed ($code)" }
}`)
	w(`function Remove-Signer {
  foreach ($st in 'My','Root','TrustedPublisher') {
    Get-ChildItem "Cert:\LocalMachine\$st" | Where-Object { $_.Subject -like '*` + signerSubject + `*' } | ForEach-Object {
      if ($_.HasPrivateKey) { Remove-Item -Path $_.PSPath -DeleteKey } else { Remove-Item -Path $_.PSPath }
      Log "removed signer from $st"
    }
  }
}`)
	w(`function Stop-Avctp {
  $ErrorActionPreference = 'Continue'
  $svc = Get-Service BthAvctpSvc -ErrorAction SilentlyContinue
  if (-not $svc -or $svc.Status -eq 'Stopped') { return }
  Stop-Service BthAvctpSvc -Force -NoWait
  $t = (Get-Date).AddSeconds(8)
  while ((Get-Service BthAvctpSvc).Status -ne 'Stopped' -and (Get-Date) -lt $t) { Start-Sleep -Milliseconds 250 }
  if ((Get-Service BthAvctpSvc).Status -eq 'Stopped') { Log 'AVCTP stopped'; return }
  $w = Get-CimInstance Win32_Service -Filter "Name='BthAvctpSvc'"
  $other = @(Get-CimInstance Win32_Service | Where-Object { $_.ProcessId -eq $w.ProcessId -and $_.Name -ne 'BthAvctpSvc' -and $_.State -ne 'Stopped' })
  if ($w.ProcessId -and $other.Count -eq 0) { Stop-Process -Id $w.ProcessId -Force; Log "AVCTP host $($w.ProcessId) hung - terminated" }
  else { Log 'AVCTP did not stop (shared host) - left running' }
}`)
	w(`function Start-Avctp {
  $ErrorActionPreference = 'Continue'
  Start-Service BthAvctpSvc -ErrorAction SilentlyContinue
  Log ("AVCTP " + (Get-Service BthAvctpSvc).Status)
}`)
	// Svc: the service bound to the adapter now (WINUSB / usbccgp / "").
	w(`function Svc {
  try { [string](Get-PnpDeviceProperty -InstanceId $id -KeyName DEVPKEY_Device_Service -ErrorAction Stop).Data } catch { '' }
}`)
	w(`function Wait-Svc([string]$not, [int]$sec) {
  $t = (Get-Date).AddSeconds($sec)
  do { $v = Svc; if ($v -ne '' -and $v -ne $not) { return $v }; Start-Sleep -Milliseconds 250 } while ((Get-Date) -lt $t)
  return (Svc)
}`)
	w("$rc = 1")
	w("try {")
	w("  Remove-Signer")
	w("  Log (\"adapter driver: \" + (Svc))")
	if !enable {
		// AVCTP (AVRCP) must already run when the radio comes back. Started
		// afterwards, the headphones connect without AVRCP and Windows
		// rebuilds their endpoint a moment later.
		w("  Start-Avctp")
		if !inPlace && instanceID != "" {
			// old way: drop the devnode while it is still on WinUSB (instant),
			// THEN delete the package (deleting first lets Windows rebind
			// BTHUSB, and removing the live stack then hangs pnputil).
			w("  Run 'pnputil.exe' @('/remove-device', $id, '/subtree') @(0, 3010)")
		}
	}
	if !enable && inPlace {
		w("  Run 'pnputil.exe' @('/disable-device', $id) @(0, 3010) 60")
		w("  Log (\"adapter problem after disable: \" + (Get-PnpDevice -InstanceId $id).Problem)")
	}
	// Deleting the WinUSB package with /uninstall reinstalls the best
	// remaining driver (usbccgp -> BTHUSB) on the same devnode.
	for _, inf := range oldInfs {
		w("  Run 'pnputil.exe' @('/delete-driver', " + psLit(inf) + ", '/uninstall') @(0, 3010) 120")
	}
	if !enable && inPlace {
		w(`  Run 'pnputil.exe' @('/enable-device', $id) @(0, 3010) 60
  $v = Wait-Svc 'WINUSB' 20
  Log "adapter driver after restore: $v"
  if ($v -eq 'WINUSB' -or $v -eq '') {
    Log 'in-place restore did not rebind - re-enumerating the adapter'
    Run 'pnputil.exe' @('/enable-device', $id) @(0, 3010) 60
    Run 'pnputil.exe' @('/remove-device', $id, '/subtree') @(0, 3010)
  }`)
	}
	if enable {
		w("  $cert = New-SelfSignedCertificate -Subject 'CN=" + signerSubject + " (ephemeral)' -Type CodeSigningCert -CertStoreLocation Cert:\\LocalMachine\\My -KeyExportPolicy NonExportable -KeySpec Signature -NotAfter (Get-Date).AddDays(1)")
		w("  Log \"signer $($cert.Thumbprint)\"")
		w("  $cer = Join-Path $env:TEMP 'sscv2_ephemeral.cer'")
		w("  Export-Certificate -Cert $cert -FilePath $cer | Out-Null")
		w("  Import-Certificate -FilePath $cer -CertStoreLocation Cert:\\LocalMachine\\Root | Out-Null")
		w("  Import-Certificate -FilePath $cer -CertStoreLocation Cert:\\LocalMachine\\TrustedPublisher | Out-Null")
		w("  Remove-Item $cer")
		w("  Run " + psLit(signtool) + " @('sign', '/sm', '/s', 'My', '/sha1', $cert.Thumbprint, '/fd', 'SHA256', " + psLit(catPath) + ")")
		w("  Stop-Avctp")
		if inPlace {
			// Disable (stops the Bluetooth stack; the children keep their
			// registry keys, so their device ids stay the same), install onto
			// the stopped devnode (no reboot needed), enable.
			w("  Run 'pnputil.exe' @('/disable-device', $id) @(0, 3010) 60")
			w(`  if ((Get-PnpDevice -InstanceId $id).Problem -ne 'CM_PROB_DISABLED') {
    Log 'adapter could not be stopped (disable vetoed) - re-enumerating instead'
    Run 'pnputil.exe' @('/enable-device', $id) @(0, 3010) 60
    Run 'pnputil.exe' @('/add-driver', ` + psLit(infPath) + `) @(0, 3010)
    Run 'pnputil.exe' @('/remove-device', $id, '/subtree') @(0, 3010)
  } else {
    Run 'pnputil.exe' @('/add-driver', ` + psLit(infPath) + `, '/install') @(0, 3010, 259) 120
    Run 'pnputil.exe' @('/enable-device', $id) @(0, 3010) 60
  }`)
			w(`  $v = Wait-Svc 'usbccgp' 10
  Log "adapter driver after install: $v"
  if ($v -ne 'WINUSB') {
    Log 'in-place install did not bind WinUSB - re-enumerating the adapter'
    Run 'pnputil.exe' @('/enable-device', $id) @(0, 3010) 60
    Run 'pnputil.exe' @('/remove-device', $id, '/subtree') @(0, 3010)
  }`)
		} else {
			w("  Run 'pnputil.exe' @('/add-driver', " + psLit(infPath) + ") @(0, 3010)")
			if instanceID != "" {
				w("  Run 'pnputil.exe' @('/remove-device', $id, '/subtree') @(0, 3010)")
			}
		}
	}
	w("  Run 'pnputil.exe' @('/scan-devices') @(0, 3010)")
	w("  $rc = 0")
	w("} catch {")
	w("  Log (\"ERROR: \" + $_.Exception.Message)")
	if enable {
		// A half-done switch must not leave our package staged: after a
		// reboot Windows would bind it and Bluetooth would be gone.
		w(`  try {
    Get-ChildItem "$env:windir\INF\oem*.inf" | Where-Object { (Get-Content $_.FullName -Raw) -match '` + infDeviceName + `' } | ForEach-Object {
      Run 'pnputil.exe' @('/delete-driver', $_.Name) @(0, 3010) 30
    }
  } catch { Log ("rollback ERROR: " + $_.Exception.Message) }`)
	}
	if inPlace {
		w(`  try { if ((Get-PnpDevice -InstanceId $id).Problem -eq 'CM_PROB_DISABLED') { Run 'pnputil.exe' @('/enable-device', $id) @(0, 3010) 60 } } catch {}`)
	}
	w("} finally {")
	w("  try { Remove-Signer } catch { Log (\"cleanup ERROR: \" + $_.Exception.Message); $rc = 2 }")
	if !enable {
		w("  try { if ((Get-Service BthAvctpSvc).Status -ne 'Running') { Start-Avctp } } catch {}")
	}
	w("}")
	w("exit $rc")
	return s.String()
}

func logTail(path string, n int) string {
	b, _ := os.ReadFile(path)
	t := strings.TrimPrefix(string(b), "\ufeff")
	var lines []string
	for _, l := range strings.Split(t, "\n") {
		if l = strings.TrimSpace(l); l != "" {
			lines = append(lines, l)
		}
	}
	if len(lines) > n {
		lines = lines[len(lines)-n:]
	}
	if len(lines) == 0 {
		return ""
	}
	return "\n  " + strings.Join(lines, "\n  ")
}

// Switch installs WinUSB (enable=true) or restores BTHUSB. Must run elevated.
func Switch(id USBID, enable bool) (Result, error) {
	st := Detect(id)
	if st.Mode == NotPresent {
		return Result{}, fmt.Errorf("адаптер %s не найден", id)
	}
	if (enable && st.Mode == WinUSB) || (!enable && st.Mode == BthUSB) {
		return Result{Message: "адаптер уже в нужном режиме"}, nil
	}

	dir, err := os.MkdirTemp("", "sscv2drv")
	if err != nil {
		return Result{}, err
	}
	defer os.RemoveAll(dir)
	infPath := filepath.Join(dir, infName)
	catPath := filepath.Join(dir, catName)
	logPath := filepath.Join(dir, "switch.log")
	scriptPath := filepath.Join(dir, "switch.ps1")

	var signtool string
	if enable {
		if signtool = findSDKTool("signtool.exe"); signtool == "" {
			return Result{}, errors.New("signtool.exe из Windows SDK не найден")
		}
		if err := os.WriteFile(infPath, []byte(infText(id)), 0o644); err != nil {
			return Result{}, err
		}
		if err := makeCatalog(dir, infPath); err != nil {
			return Result{}, err
		}
	}
	// UTF-8 BOM so Windows PowerShell 5.1 reads non-ASCII paths correctly.
	script := "\ufeff" + buildScript(enable, findWinUSBInfs(id), st.InstanceID, infPath, catPath, signtool, logPath)
	if err := os.WriteFile(scriptPath, []byte(script), 0o644); err != nil {
		return Result{}, err
	}
	_, err = run(5*time.Minute, "powershell.exe", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", scriptPath)
	tail := logTail(logPath, 8)
	if Logf != nil {
		Logf("driver switch (winusb=%v) script log:%s", enable, logTail(logPath, 40))
	}
	if err != nil {
		msg := "переключение драйвера не удалось: " + err.Error()
		if ee, ok := err.(*exec.ExitError); ok && ee.ExitCode() == 2 {
			msg += " (временный сертификат не удалён — удалите '" + signerSubject + "' в certlm.msc)"
		}
		return Result{}, errors.New(msg + tail)
	}
	// Let PnP settle and confirm.
	want := BthUSB
	if enable {
		want = WinUSB
	}
	for i := 0; i < 30; i++ {
		if Detect(id).Mode == want {
			break
		}
		time.Sleep(500 * time.Millisecond)
	}
	now := Detect(id)
	if now.Mode != want {
		return Result{Changed: true}, fmt.Errorf("драйвер ещё не сменился (сейчас %s)%s", now.Mode, tail)
	}
	if enable {
		return Result{Changed: true, Message: "WinUSB установлен, адаптер в режиме потока"}, nil
	}
	return Result{Changed: true, Message: "адаптер возвращён Windows Bluetooth"}, nil
}
