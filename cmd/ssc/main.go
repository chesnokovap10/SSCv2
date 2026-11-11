// SSCv2: tray app that streams Windows audio to Samsung Galaxy Buds over
// the laptop's built-in MediaTek MT79xx Bluetooth (BTstack in WinUSB mode)
// and keeps a BLE mouse working meanwhile.
//
//	ssc.exe                         tray (default; a copy outside Program Files installs/updates itself first)
//	ssc.exe install                 copy to Program Files (elevated, from the first run)
//	ssc.exe --update                update from this build without prompts (already elevated)
//	ssc.exe uninstall [--yes]       uninstall (through the running tray)
//	ssc.exe uninstall-system --pid N   machine-wide part of uninstall (elevated)
//	ssc.exe engine                  streaming process (started by the tray)
//	ssc.exe service --owner <SID>   helper service (started by the SCM)
//	ssc.exe service-install|service-uninstall   (elevated, from the tray)
//	ssc.exe helper-op <b64> <out>   one privileged op (elevated, from the tray)
//	ssc.exe ctl <cmd> [arg]          control the running tray (status, mode aac, ...)
//	ssc.exe status                  print adapter/service state (console)
package main

import (
	"context"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"

	"golang.org/x/sys/windows"

	"sscv2/internal/app"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/engine"
	"sscv2/internal/helper"
	"sscv2/internal/install"
	"sscv2/internal/ipc"
	"sscv2/internal/logx"
	"sscv2/internal/nativebt"
)

func main() {
	args := os.Args[1:]
	if len(args) == 0 {
		os.Exit(app.Run())
	}
	owner := func() string {
		for i := 1; i+1 < len(args); i++ {
			if args[i] == "--owner" {
				return args[i+1]
			}
		}
		return ""
	}
	switch args[0] {
	case "--update":
		if len(args) != 1 {
			fmt.Fprintln(console(), "usage: ssc.exe --update")
			os.Exit(2)
		}
		if !windows.GetCurrentProcessToken().IsElevated() {
			fmt.Fprintln(console(), "update requires an elevated process")
			os.Exit(5)
		}
		if !install.Installed() {
			fmt.Fprintln(console(), "SSCv2 is not installed")
			os.Exit(1)
		}
		logx.Open(config.LogDir(), "helper.log", "helper")
		if !install.UpToDate() {
			if err := install.Install(); err != nil {
				logx.Printf("update: %v", err)
				fmt.Fprintln(console(), "update:", err)
				os.Exit(1)
			}
		}
	case "install":
		logx.Open(config.LogDir(), "helper.log", "helper")
		if err := install.Install(); err != nil {
			logx.Printf("install: %v", err)
			os.Exit(1)
		}
		if installed, _ := helper.ServiceState(); !installed {
			sid := owner()
			if sid == "" {
				sid = helper.CurrentUserSID()
			}
			if err := helper.InstallService(sid); err != nil {
				logx.Printf("install helper: %v", err)
				os.Exit(1)
			}
		}
	case "uninstall-system":
		pid := 0
		for i := 1; i+1 < len(args); i++ {
			if args[i] == "--pid" {
				pid, _ = strconv.Atoi(args[i+1])
			}
		}
		os.Exit(app.UninstallSystem(pid))
	case "uninstall":
		a := []string{"uninstall"}
		if len(args) > 1 && args[1] == "--yes" {
			a = append(a, "yes")
		}
		out, err := app.Ctl(a)
		if err != nil {
			fmt.Fprintln(console(), "error:", err, "- start ssc.exe and use Settings > Uninstall")
			os.Exit(1)
		}
		fmt.Fprintln(console(), out)
	case "test-signing":
		out := console()
		if len(args) != 2 || (args[1] != "on" && args[1] != "off") {
			fmt.Fprintln(out, "usage: ssc.exe test-signing on|off")
			os.Exit(2)
		}
		enabled := args[1] == "on"
		if _, err := helper.Call(ipc.Request{Op: "test-signing", TestSigning: &enabled}); err != nil {
			fmt.Fprintln(out, "test-signing:", err)
			os.Exit(1)
		}
		active, err := driver.TestSigning()
		switch {
		case err != nil:
			fmt.Fprintln(out, "Boot setting saved. Current Windows test signing:", err)
		case active != enabled:
			fmt.Fprintln(out, "Boot setting saved. Restart Windows to apply it.")
		default:
			fmt.Fprintln(out, "Boot setting saved. The requested mode is already active.")
		}
	case "native-stereo":
		out := console()
		if len(args) != 2 || (args[1] != "bind" && args[1] != "restore") {
			fmt.Fprintln(out, "usage: ssc.exe native-stereo bind|restore")
			os.Exit(2)
		}
		if _, err := helper.Call(ipc.Request{Op: "native-stereo-" + args[1]}); err != nil {
			fmt.Fprintln(out, "native-stereo:", err)
			os.Exit(1)
		}
		fmt.Fprintln(out, "native-stereo:", args[1], "complete")
	case "native-aac-local":
		out := console()
		var err error
		switch {
		case len(args) == 2 && (args[1] == "enable" || args[1] == "disable"):
			err = driver.SetLocalProfile(args[1] == "enable")
		case len(args) == 3 && args[1] == "probe":
			err = nativebt.ProbeLocalProfile(context.Background(), args[2], out)
		case len(args) == 3 && args[1] == "handoff":
			err = nativebt.ProbeLocalHandoff(context.Background(), args[2], out)
		default:
			err = fmt.Errorf("usage: ssc.exe native-aac-local enable|disable|probe ADDRESS|handoff ADDRESS")
		}
		if err != nil {
			fmt.Fprintln(out, err)
			os.Exit(1)
		}
	case "native-render":
		out := console()
		if len(args) != 4 {
			fmt.Fprintln(out, "usage: ssc.exe native-render aac|ssc WAVE_INTERFACE SECONDS")
			os.Exit(2)
		}
		seconds, err := strconv.Atoi(args[3])
		if err != nil || seconds < 1 || seconds > 3600 {
			fmt.Fprintln(out, "stream duration must be 1 to 3600 seconds")
			os.Exit(2)
		}
		settings, err := config.Load()
		if err != nil || !settings.WindowsTestSigning || settings.Headphones == nil {
			fmt.Fprintln(out, "native-render requires the SSCv2 Windows test-mode option and configured headphones")
			os.Exit(1)
		}
		ctx, cancel := context.WithCancel(context.Background())
		timer := time.AfterFunc(time.Duration(seconds)*time.Second, cancel)
		err = nativebt.RunRenderDiagnostic(ctx, settings.Headphones.Addr, args[2], out, config.Mode(args[1]))
		timer.Stop()
		cancel()
		if err != nil {
			fmt.Fprintln(out, "native-render:", err)
			os.Exit(1)
		}
	case "native-aac-worker", "native-ssc-worker", "native-ssc_uhq-worker":
		mode := config.ModeAAC
		switch args[0] {
		case "native-ssc-worker":
			mode = config.ModeSSC
		case "native-ssc_uhq-worker":
			mode = config.ModeSSCUHQ
		}
		if err := nativebt.RunWorker(os.Stdin, os.Stdout, args[1:], mode, engine.HandleMediaKey); err != nil {
			fmt.Fprintf(os.Stdout, "native worker: %v\n", err)
			os.Exit(1)
		}
	case "native-aac":
		out := console()
		if err := nativebt.Run(args[1:], out); err != nil {
			fmt.Fprintln(out, "native-aac:", err)
			os.Exit(1)
		}
	case "engine":
		os.Exit(engine.Run(os.Stdin, os.Stdout))
	case "service":
		if err := helper.RunService(owner()); err != nil {
			logx.Printf("service: %v", err)
			os.Exit(1)
		}
	case "service-install":
		logx.Open(config.LogDir(), "helper.log", "helper")
		if err := helper.InstallService(owner()); err != nil {
			logx.Printf("service install: %v", err)
			os.Exit(1)
		}
		logx.Printf("service installed")
	case "service-uninstall":
		logx.Open(config.LogDir(), "helper.log", "helper")
		if err := helper.UninstallService(); err != nil {
			logx.Printf("service uninstall: %v", err)
			os.Exit(1)
		}
		logx.Printf("service removed")
	case "helper-op":
		if len(args) < 3 {
			os.Exit(2)
		}
		os.Exit(helper.RunHelperOp(args[1], args[2]))
	case "ctl":
		out, err := app.Ctl(args[1:])
		if err != nil {
			fmt.Fprintln(console(), "error:", err)
			os.Exit(1)
		}
		fmt.Fprintln(console(), out)
		if strings.HasPrefix(out, "error") {
			os.Exit(1)
		}
	case "status":
		out := console()
		st, ok := driver.FindAdapter(driver.USBID{})
		if !ok {
			fmt.Fprintln(out, "MediaTek adapter: not found")
		} else {
			fmt.Fprintf(out, "MediaTek adapter %s: %s [service %s] %s\n", st.ID, st.Mode, st.Service, st.InstanceID)
		}
		inst, run := helper.ServiceState()
		testSigning, err := driver.TestSigning()
		if err != nil {
			fmt.Fprintf(out, "Windows test signing: unknown (%v)\n", err)
		} else {
			fmt.Fprintf(out, "Windows test signing: %t\n", testSigning)
		}
		paths, err := nativebt.Interfaces()
		if err != nil {
			fmt.Fprintf(out, "Native Bluetooth interfaces: unknown (%v)\n", err)
		} else {
			fmt.Fprintf(out, "Native Bluetooth interfaces: %d\n", len(paths))
		}
		fmt.Fprintf(out, "version %s\nhelper service: installed=%v running=%v\n", ipc.Version, inst, run)
		fmt.Fprintf(out, "installed copy: %s (present %v, this is it %v)\n", install.Exe(), install.Installed(), install.RunningInstalled())
		fmt.Fprintf(out, "settings: %s\nlogs: %s\n", config.SettingsPath(), config.LogDir())
	default:
		fmt.Fprintf(console(), "unknown command %q\n", args[0])
		os.Exit(2)
	}
}

// console attaches to the parent console (the exe is a GUI-subsystem binary).
func console() *os.File {
	// Redirected/piped output: use it as is.
	if h, err := windows.GetStdHandle(windows.STD_OUTPUT_HANDLE); err == nil && h != 0 && h != windows.InvalidHandle {
		if t, _ := windows.GetFileType(h); t == windows.FILE_TYPE_PIPE || t == windows.FILE_TYPE_DISK {
			return os.Stdout
		}
	}
	k := windows.NewLazySystemDLL("kernel32.dll").NewProc("AttachConsole")
	k.Call(^uintptr(0)) // ATTACH_PARENT_PROCESS
	f, err := os.OpenFile("CONOUT$", os.O_WRONLY, 0)
	if err != nil {
		return os.Stdout
	}
	return f
}
