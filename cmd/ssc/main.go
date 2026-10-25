// SSCv2: tray app that streams Windows audio to Samsung Galaxy Buds over
// the laptop's built-in MediaTek MT79xx Bluetooth (BTstack in WinUSB mode)
// and keeps a BLE mouse working meanwhile.
//
//	ssc.exe                         tray (default; a copy outside Program Files installs/updates itself first)
//	ssc.exe install                 copy to Program Files (elevated, from the first run)
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
	"fmt"
	"os"
	"strconv"
	"strings"

	"golang.org/x/sys/windows"

	"sscv2/internal/app"
	"sscv2/internal/config"
	"sscv2/internal/driver"
	"sscv2/internal/engine"
	"sscv2/internal/helper"
	"sscv2/internal/install"
	"sscv2/internal/ipc"
	"sscv2/internal/logx"
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
	case "install":
		logx.Open(config.LogDir(), "helper.log", "helper")
		if err := install.Install(); err != nil {
			logx.Printf("install: %v", err)
			os.Exit(1)
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
