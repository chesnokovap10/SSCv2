package app

import (
	"bufio"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strconv"
	"strings"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"

	"sscv2/internal/codec/ssc"
	"sscv2/internal/config"
	"sscv2/internal/helper"
	"sscv2/internal/ipc"
	"sscv2/internal/keys"
	"sscv2/internal/logx"
)

// tailFile returns the last n lines of a text file.
func tailFile(path string, n int) string {
	f, err := os.Open(path)
	if err != nil {
		return "error: " + err.Error()
	}
	defer f.Close()
	const max = 8 << 20
	if fi, err := f.Stat(); err == nil && fi.Size() > max {
		f.Seek(fi.Size()-max, 0)
	}
	b, _ := io.ReadAll(f)
	lines := strings.Split(strings.TrimRight(string(b), "\n"), "\n")
	if n > 0 && len(lines) > n {
		lines = lines[len(lines)-n:]
	}
	return strings.Join(lines, "\n")
}

// Control API: the running tray accepts commands on a per-user named pipe,
// so everything the menu does can be scripted ("ssc.exe ctl <cmd> [arg]").
//
//	status | info | log [debug|tray|engine|helper] [N] | debug on|off | lang ru|en
//	mode off|aac|ssc|ssc_uhq | bitrate auto|<kbps> (current codec) | maxmtu on|off
//	aac fit|frag|over | ssc auto|<kbps> | ssccap auto|<hex> | restore <mode> | variant <v>
//	import windows | service install|remove | virtual install|remove
//	scan | connect <addr> | headphones <addr> | mouse <addr|none>
//	quit [keep] | uninstall [yes]

func ctlPipeName() string { return `\\.\pipe\SSCv2Tray-` + helper.CurrentUserSID() }

type ctlStatus struct {
	Mode     config.Mode      `json:"mode"`
	Busy     string           `json:"busy,omitempty"`
	State    string           `json:"state"`
	Adapter  string           `json:"adapter"`
	Driver   string           `json:"driver"`
	Service  string           `json:"service"`
	Engine   bool             `json:"engine"`
	Status   ipc.EngineStatus `json:"status"`
	Settings config.Settings  `json:"settings"`
	Scan     []ipc.Found      `json:"scan,omitempty"`
}

func (a *App) serveCtl() {
	sd, err := windows.SecurityDescriptorFromString("D:P(A;;GA;;;SY)(A;;GRGW;;;" + helper.CurrentUserSID() + ")")
	if err != nil {
		logf("ctl: %v", err)
		return
	}
	sa := &windows.SecurityAttributes{Length: uint32(unsafe.Sizeof(windows.SecurityAttributes{})), SecurityDescriptor: sd}
	name, _ := windows.UTF16PtrFromString(ctlPipeName())
	for {
		h, err := windows.CreateNamedPipe(name, windows.PIPE_ACCESS_DUPLEX,
			windows.PIPE_TYPE_BYTE|windows.PIPE_READMODE_BYTE|windows.PIPE_WAIT|windows.PIPE_REJECT_REMOTE_CLIENTS,
			windows.PIPE_UNLIMITED_INSTANCES, 64<<10, 64<<10, 0, sa)
		if err != nil {
			logf("ctl pipe: %v", err)
			return
		}
		if err := windows.ConnectNamedPipe(h, nil); err != nil && err != windows.ERROR_PIPE_CONNECTED {
			windows.CloseHandle(h)
			continue
		}
		go func() {
			f := os.NewFile(uintptr(h), "ctl")
			defer func() { windows.FlushFileBuffers(h); windows.DisconnectNamedPipe(h); f.Close() }()
			line, err := bufio.NewReader(f).ReadString('\n')
			if err != nil {
				return
			}
			out := a.ctl(strings.Fields(line))
			f.Write([]byte(out + "\n"))
		}()
	}
}

func (a *App) ctl(args []string) string {
	if len(args) == 0 {
		return "error: no command"
	}
	arg := func(i int) string {
		if i < len(args) {
			return args[i]
		}
		return ""
	}
	logf("ctl: %s", strings.Join(args, " "))
	switch args[0] {
	case "status":
		st := a.refreshAdapter()
		inst, run := helper.ServiceState()
		_, text := a.state()
		a.mu.Lock()
		cs := ctlStatus{Mode: a.mode, Busy: a.busy, State: text, Adapter: st.ID.String(), Driver: st.Mode.String(),
			Engine: a.eng != nil, Status: a.st, Settings: *a.s, Scan: a.scan}
		a.mu.Unlock()
		cs.Service = map[bool]string{false: "not installed", true: "stopped"}[inst]
		if run {
			cs.Service = "running"
		}
		b, _ := json.MarshalIndent(cs, "", "  ")
		return string(b)
	case "info":
		return a.infoText()
	case "debug":
		switch arg(1) {
		case "on":
			a.setDebug(true)
		case "off":
			a.setDebug(false)
		default:
			return "error: debug on|off"
		}
		return "ok"
	case "log":
		// log [debug|tray|engine|helper] [lines]: tail of a journal as the
		// tray sees it (works across file-system virtualization).
		name, n := "", 100
		for _, a := range args[1:] {
			if v, err := strconv.Atoi(a); err == nil {
				n = v
			} else {
				name = a
			}
		}
		if name == "" {
			name = "tray"
			if logx.Debug() {
				name = "debug"
			}
		}
		return tailFile(filepath.Join(config.LogDir(), name+".log"), n)
	case "aac":
		switch arg(1) {
		case "over": // old name of "maxmtu on"
			go a.setMaxMTU(true)
			return "ok: maxmtu on"
		case "fit", "frag":
		default:
			return "error: aac fit|frag|over"
		}
		a.mu.Lock()
		a.s.AACMode = arg(1)
		_ = config.Save(a.s)
		a.mu.Unlock()
		go a.restartEngine()
		return "ok: aac " + arg(1)
	case "maxmtu":
		switch arg(1) {
		case "on", "off":
			go a.setMaxMTU(arg(1) == "on")
			return "ok: maxmtu " + arg(1)
		}
		return "error: maxmtu on|off"
	case "lang":
		if arg(1) != "ru" && arg(1) != "en" {
			return "error: lang ru|en"
		}
		a.setLang(arg(1))
		return "ok: lang " + arg(1)
	case "bitrate":
		a.mu.Lock()
		m := a.mode
		a.mu.Unlock()
		if !m.Streaming() {
			return "error: codec is off"
		}
		kbps := 0
		if arg(1) != "auto" {
			n, err := strconv.Atoi(arg(1))
			ok := false
			for _, b := range bitrates[m] {
				ok = ok || b == n && err == nil && n > 0
			}
			if !ok {
				return fmt.Sprintf("error: bitrate auto|%v for %s", bitrates[m][1:], m)
			}
			kbps = n
		}
		go a.setBitrate(kbps)
		return fmt.Sprintf("ok: %s bitrate %d (0 = auto)", m, kbps)
	case "ssc":
		// SSC bitrate: kbps or "auto"; a UHQ rate goes to SSC UHQ
		kbps := 0
		if arg(1) != "auto" {
			n, err := strconv.Atoi(arg(1))
			if err != nil || !ssc.Valid(48000, n*1000) && !ssc.Valid(96000, n*1000) {
				return "error: ssc auto|88|96|128|192|229|256|328 or UHQ 152|250|291|308|442|584|886"
			}
			kbps = n
		}
		a.mu.Lock()
		if kbps > 0 && ssc.Valid(96000, kbps*1000) {
			a.s.SSCUHQBitrate = kbps
		} else {
			a.s.SSCBitrate = kbps
		}
		_ = config.Save(a.s)
		a.mu.Unlock()
		go a.restartEngine()
		return fmt.Sprintf("ok: ssc %d kbps (0 = auto)", kbps)
	case "ssccap":
		// SSC configuration byte for experiments: hex (0x0A) or "auto"
		v := int64(0)
		if arg(1) != "auto" {
			n, err := strconv.ParseInt(strings.TrimPrefix(strings.ToLower(arg(1)), "0x"), 16, 16)
			if err != nil || n <= 0 || n > 0xFF {
				return "error: ssccap auto|<hex byte>"
			}
			v = n
		}
		a.mu.Lock()
		a.s.SSCCap = int(v)
		_ = config.Save(a.s)
		a.mu.Unlock()
		go a.restartEngine()
		return fmt.Sprintf("ok: ssccap 0x%02X (0 = auto)", v)
	case "variant":
		a.mu.Lock()
		a.driverVariant = arg(1)
		a.mu.Unlock()
		return "ok: driver variant " + nz(arg(1), "default")
	case "restore":
		// diagnostics: how the headphones' level is restored after "Выкл"
		a.mu.Lock()
		a.restoreMode = arg(1)
		a.mu.Unlock()
		return "ok: restore mode " + nz(arg(1), "default")
	case "mode":
		switch arg(1) {
		case "off":
			go a.disable()
		case "aac":
			go a.enable(config.ModeAAC)
		case "ssc":
			go a.enable(config.ModeSSC)
		case "ssc_uhq", "uhq":
			go a.enable(config.ModeSSCUHQ)
		default:
			return "error: mode off|aac|ssc|ssc_uhq"
		}
		return "ok"
	case "quit":
		go a.exit(arg(1) == "keep")
		return "ok"
	case "uninstall":
		go a.uninstall(arg(1) == "yes")
		return "ok"
	case "version":
		return ipc.Version
	case "import":
		if arg(1) != "windows" {
			return "error: import windows"
		}
		go a.importWindows()
		return "ok"
	case "service":
		switch arg(1) {
		case "install":
			go a.installService()
		case "remove":
			go a.removeService()
		default:
			return "error: service install|remove"
		}
		return "ok"
	case "virtual":
		switch arg(1) {
		case "install":
			go func() { a.ensureVirtual(); a.setBusy("") }()
		case "remove":
			go a.removeVirtual()
		default:
			return "error: virtual install|remove"
		}
		return "ok"
	case "scan":
		a.command(idScan)
		return "ok"
	case "connect", "headphones":
		if arg(1) == "" {
			return "error: address needed"
		}
		dev := &config.Device{Addr: strings.ToUpper(arg(1))}
		if store, err := keys.Open(); err == nil {
			if c, ok := store.FindClassic(dev.Addr); ok {
				dev.Name = c.Name
			}
		}
		a.mu.Lock()
		a.s.Headphones = dev
		_ = config.Save(a.s)
		eng := a.eng
		a.mu.Unlock()
		if eng != nil {
			eng.send(ipc.Command{Cmd: "connect", Addr: arg(1)})
		}
		return "ok"
	case "mouse":
		a.mu.Lock()
		if arg(1) == "none" || arg(1) == "" {
			a.s.Mouse = nil
		} else {
			dev := &config.Device{Addr: strings.ToUpper(arg(1))}
			if store, err := keys.Open(); err == nil {
				if l, ok := store.FindLE(dev.Addr); ok {
					dev.Name = l.Name
				}
			}
			a.s.Mouse = dev
		}
		_ = config.Save(a.s)
		a.mu.Unlock()
		go a.restartEngine()
		return "ok"
	}
	return "error: unknown command " + args[0]
}

// Ctl sends one command to the running tray and returns its reply.
func Ctl(args []string) (string, error) {
	name, _ := windows.UTF16PtrFromString(ctlPipeName())
	var h windows.Handle
	var err error
	for i := 0; i < 20; i++ {
		if h, err = windows.CreateFile(name, windows.GENERIC_READ|windows.GENERIC_WRITE, 0, nil, windows.OPEN_EXISTING, 0, 0); err == nil {
			break
		}
		if err != windows.ERROR_PIPE_BUSY {
			return "", errors.New(T("трей SSCv2 не запущен", "the SSCv2 tray is not running"))
		}
		time.Sleep(100 * time.Millisecond)
	}
	if err != nil {
		return "", err
	}
	f := os.NewFile(uintptr(h), "ctl")
	defer f.Close()
	if _, err := fmt.Fprintln(f, strings.Join(args, " ")); err != nil {
		return "", err
	}
	var sb strings.Builder
	r := bufio.NewReader(f)
	for {
		s, err := r.ReadString('\n')
		sb.WriteString(s)
		if err != nil {
			break
		}
	}
	return strings.TrimRight(sb.String(), "\n"), nil
}
