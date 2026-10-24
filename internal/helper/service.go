package helper

import (
	"encoding/base64"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
	"golang.org/x/sys/windows/svc"
	"golang.org/x/sys/windows/svc/mgr"

	"sscv2/internal/config"
	"sscv2/internal/ipc"
	"sscv2/internal/logx"
)

const (
	ServiceName    = "SSCv2Helper"
	serviceDisplay = "SSCv2 Bluetooth Helper"
	serviceDesc    = "Переключает драйвер встроенного Bluetooth (MediaTek) и переносит ключи сопряжения для SSCv2."
)

// ---- running as a service ---------------------------------------------------

type handler struct{ owner string }

func (h handler) Execute(args []string, req <-chan svc.ChangeRequest, st chan<- svc.Status) (bool, uint32) {
	st <- svc.Status{State: svc.StartPending}
	errc := make(chan error, 1)
	go func() { errc <- Serve(h.owner) }()
	st <- svc.Status{State: svc.Running, Accepts: svc.AcceptStop | svc.AcceptShutdown}
	logx.Printf("service running (owner %s)", h.owner)
	for {
		select {
		case err := <-errc:
			logx.Printf("pipe server stopped: %v", err)
			return true, 1
		case c := <-req:
			switch c.Cmd {
			case svc.Interrogate:
				st <- c.CurrentStatus
			case svc.Stop, svc.Shutdown:
				st <- svc.Status{State: svc.StopPending}
				logx.Printf("service stopping")
				return false, 0
			}
		}
	}
}

// RunService is the entry for "ssc.exe service --owner <SID>".
func RunService(owner string) error {
	logx.Open(config.ServiceDir(), "service.log", "service")
	return svc.Run(ServiceName, handler{owner: owner})
}

// ---- management (needs admin) -------------------------------------------------

// ServiceState: "not installed", "stopped", "running", ...
func ServiceState() (installed, running bool) {
	scm, err := windows.OpenSCManager(nil, nil, windows.SC_MANAGER_CONNECT)
	if err != nil {
		return false, false
	}
	defer windows.CloseServiceHandle(scm)
	h, err := windows.OpenService(scm, windows.StringToUTF16Ptr(ServiceName), windows.SERVICE_QUERY_STATUS)
	if err != nil {
		return false, false
	}
	s := &mgr.Service{Name: ServiceName, Handle: h}
	defer s.Close()
	q, err := s.Query()
	if err != nil {
		return true, false
	}
	return true, q.State == svc.Running
}

func installDir() string {
	pf := os.Getenv("ProgramFiles")
	if pf == "" {
		pf = `C:\Program Files`
	}
	return filepath.Join(pf, config.AppName)
}

func copyFile(src, dst string) error {
	in, err := os.Open(src)
	if err != nil {
		return err
	}
	defer in.Close()
	tmp := dst + ".new"
	out, err := os.Create(tmp)
	if err != nil {
		return err
	}
	if _, err := io.Copy(out, in); err != nil {
		out.Close()
		return err
	}
	out.Close()
	// The old exe may still be held by an exiting service process: move it
	// aside (allowed for a running image) and retry briefly.
	var err2 error
	for i := 0; i < 20; i++ {
		_ = os.Remove(dst + ".old")
		_ = os.Rename(dst, dst+".old")
		if err2 = os.Rename(tmp, dst); err2 == nil {
			_ = os.Remove(dst + ".old")
			return nil
		}
		time.Sleep(250 * time.Millisecond)
	}
	return err2
}

// InstallService copies the executable to Program Files (a SYSTEM service
// must not run from a user-writable folder), registers and starts it.
func InstallService(owner string) error {
	self, err := os.Executable()
	if err != nil {
		return err
	}
	m, err := mgr.Connect()
	if err != nil {
		return err
	}
	defer m.Disconnect()
	if s, err := m.OpenService(ServiceName); err == nil {
		stopAndWait(s)
		s.Close()
	}
	dir := installDir()
	if err := os.MkdirAll(dir, 0o755); err != nil {
		return err
	}
	exe := filepath.Join(dir, "ssc.exe")
	if !sameFile(self, exe) {
		if err := copyFile(self, exe); err != nil {
			return fmt.Errorf("копирование в %s: %w", dir, err)
		}
	}
	s, err := m.OpenService(ServiceName)
	if err == nil {
		cfg, _ := s.Config()
		cfg.BinaryPathName = fmt.Sprintf(`"%s" service --owner %s`, exe, owner)
		cfg.StartType = mgr.StartAutomatic
		if err := s.UpdateConfig(cfg); err != nil {
			s.Close()
			return err
		}
	} else {
		s, err = m.CreateService(ServiceName, exe, mgr.Config{
			DisplayName: serviceDisplay,
			Description: serviceDesc,
			StartType:   mgr.StartAutomatic,
		}, "service", "--owner", owner)
		if err != nil {
			return fmt.Errorf("создание службы: %w", err)
		}
	}
	defer s.Close()
	_ = s.SetRecoveryActions([]mgr.RecoveryAction{{Type: mgr.ServiceRestart, Delay: 5 * time.Second}}, 86400)
	if err := s.Start(); err != nil {
		return fmt.Errorf("запуск службы: %w", err)
	}
	return nil
}

func sameFile(a, b string) bool {
	fa, err1 := os.Stat(a)
	fb, err2 := os.Stat(b)
	return err1 == nil && err2 == nil && os.SameFile(fa, fb)
}

func stopAndWait(s *mgr.Service) {
	if _, err := s.Control(svc.Stop); err != nil {
		return
	}
	for i := 0; i < 50; i++ {
		q, err := s.Query()
		if err != nil || q.State == svc.Stopped {
			return
		}
		time.Sleep(200 * time.Millisecond)
	}
}

// UninstallService stops and deletes the service and its files.
func UninstallService() error {
	m, err := mgr.Connect()
	if err != nil {
		return err
	}
	defer m.Disconnect()
	s, err := m.OpenService(ServiceName)
	if err != nil {
		return errors.New("служба не установлена")
	}
	stopAndWait(s)
	err = s.Delete()
	s.Close()
	if err != nil {
		return err
	}
	time.Sleep(500 * time.Millisecond)
	self, _ := os.Executable()
	exe := filepath.Join(installDir(), "ssc.exe")
	if !sameFile(self, exe) {
		_ = os.RemoveAll(installDir())
	}
	return nil
}

// ---- elevation ------------------------------------------------------------------

var (
	shell32            = windows.NewLazySystemDLL("shell32.dll")
	procShellExecuteEx = shell32.NewProc("ShellExecuteExW")
)

type shellExecuteInfo struct {
	cbSize       uint32
	fMask        uint32
	hwnd         uintptr
	lpVerb       *uint16
	lpFile       *uint16
	lpParameters *uint16
	lpDirectory  *uint16
	nShow        int32
	hInstApp     uintptr
	lpIDList     uintptr
	lpClass      *uint16
	hkeyClass    uintptr
	dwHotKey     uint32
	hIcon        uintptr
	hProcess     windows.Handle
}

// ErrCancelled: the user declined the UAC prompt.
var ErrCancelled = errors.New("запрос прав администратора отклонён")

// RunElevated starts this executable with args via UAC and waits for it.
func RunElevated(args string) (uint32, error) {
	self, err := os.Executable()
	if err != nil {
		return 1, err
	}
	sei := shellExecuteInfo{
		fMask:        0x00000040 | 0x00000100, // NOCLOSEPROCESS | NOASYNC
		lpVerb:       windows.StringToUTF16Ptr("runas"),
		lpFile:       windows.StringToUTF16Ptr(self),
		lpParameters: windows.StringToUTF16Ptr(args),
		nShow:        0,
	}
	sei.cbSize = uint32(unsafe.Sizeof(sei))
	r, _, e := procShellExecuteEx.Call(uintptr(unsafe.Pointer(&sei)))
	if r == 0 {
		if e == windows.ERROR_CANCELLED {
			return 1, ErrCancelled
		}
		return 1, e
	}
	defer windows.CloseHandle(sei.hProcess)
	windows.WaitForSingleObject(sei.hProcess, windows.INFINITE)
	var code uint32
	windows.GetExitCodeProcess(sei.hProcess, &code)
	return code, nil
}

// Call performs a privileged request: through the service when it runs,
// otherwise in a UAC-elevated copy of ssc.exe ("helper-op").
func Call(req ipc.Request) (ipc.Response, error) {
	req.Debug = logx.Debug()
	t0 := time.Now()
	logx.Dbgf("helper", "-> %s %s", req.Op, reqSummary(req))
	resp, err := call(req)
	for _, l := range resp.Log {
		logx.Dbgf("helper", "| %s", l)
	}
	logx.Dbgf("helper", "<- %s in %s: ok=%v msg=%q err=%v", req.Op, time.Since(t0).Round(time.Millisecond), resp.OK, resp.Message, err)
	return resp, err
}

func reqSummary(r ipc.Request) string {
	switch r.Op {
	case "driver":
		return fmt.Sprintf("%04X:%04X winusb=%v", r.VID, r.PID, r.WinUSB)
	case "keys-write":
		return r.Adapter + " " + r.Device // never the key
	case "virtual-install":
		return fmt.Sprintf("%q", r.Name)
	}
	return ""
}

func call(req ipc.Request) (ipc.Response, error) {
	resp, err := callPipe(req)
	if err == nil {
		if !resp.OK {
			return resp, errors.New(resp.Error)
		}
		return resp, nil
	}
	if !errors.Is(err, ErrNoService) {
		return resp, err
	}
	out := filepath.Join(os.TempDir(), fmt.Sprintf("sscv2_helper_%d.json", time.Now().UnixNano()))
	defer os.Remove(out)
	b, _ := json.Marshal(req)
	arg := fmt.Sprintf(`helper-op %s "%s"`, base64.RawURLEncoding.EncodeToString(b), out)
	if _, err := RunElevated(arg); err != nil {
		return ipc.Response{}, err
	}
	data, err := os.ReadFile(out)
	if err != nil {
		return ipc.Response{}, fmt.Errorf("нет ответа от помощника: %w", err)
	}
	if err := json.Unmarshal(data, &resp); err != nil {
		return resp, err
	}
	if !resp.OK {
		return resp, errors.New(resp.Error)
	}
	return resp, nil
}

// RunHelperOp is the entry for the elevated "helper-op <b64> <out>" process.
func RunHelperOp(b64, out string) int {
	logx.Open(config.LogDir(), "helper.log", "helper")
	var req ipc.Request
	resp := ipc.Response{}
	b, err := base64.RawURLEncoding.DecodeString(b64)
	if err == nil {
		err = json.Unmarshal(b, &req)
	}
	if err != nil {
		resp.Error = "bad request"
	} else {
		resp = Handle(req)
	}
	data, _ := json.Marshal(resp)
	if err := os.WriteFile(out, data, 0o600); err != nil {
		return 2
	}
	if !resp.OK {
		return 1
	}
	return 0
}

// CurrentUserSID returns the SID string of the calling user.
func CurrentUserSID() string {
	tu, err := windows.GetCurrentProcessToken().GetTokenUser()
	if err != nil {
		return ""
	}
	return tu.User.Sid.String()
}
