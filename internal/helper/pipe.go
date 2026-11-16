package helper

import (
	"bufio"
	"encoding/json"
	"fmt"
	"os"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"
	"golang.org/x/sys/windows/svc"

	"sscv2/internal/i18n"
	"sscv2/internal/ipc"
	"sscv2/internal/logx"
)

const pipeName = `\\.\pipe\SSCv2Helper`

const (
	maxHelperConnections = 32
	maxHelperRequest     = 4096
)

// pipeSDDL lets SYSTEM, Administrators and the owner (the user who installed
// the service) connect; nobody else may drive the privileged operations.
func pipeSDDL(ownerSID string) string {
	const admins = "D:P(A;;GA;;;SY)(A;;GA;;;BA)"
	if ownerSID == "" {
		return admins
	}
	// GENERIC_READ | FILE_WRITE_DATA. GENERIC_WRITE would also allow the
	// client to create its own server instance under the same name.
	return admins + "(A;;0x80000002;;;" + ownerSID + ")"
}

// Serve accepts helper requests until the process exits.
func Serve(ownerSID string) error {
	first := true
	active := make(chan struct{}, maxHelperConnections)
	for {
		h, err := newPipeInstance(pipeName, ownerSID, first)
		if err != nil {
			return err
		}
		if err := acceptPipe(h); err != nil {
			windows.CloseHandle(h)
			time.Sleep(100 * time.Millisecond)
			continue
		}
		first = false
		select {
		case active <- struct{}{}:
			go func() {
				defer func() { <-active }()
				serveConn(h, ownerSID != "")
			}()
		default:
			windows.CloseHandle(h)
		}
	}
}

func acceptPipe(h windows.Handle) error {
	return AcceptPipe(h)
}

// AcceptPipe accepts a local connection on an overlapped named-pipe handle.
func AcceptPipe(h windows.Handle) error {
	event, err := windows.CreateEvent(nil, 1, 0, nil)
	if err != nil {
		return err
	}
	defer windows.CloseHandle(event)
	op := windows.Overlapped{HEvent: event}
	switch err := windows.ConnectNamedPipe(h, &op); err {
	case nil, windows.ERROR_PIPE_CONNECTED:
		return nil
	case windows.ERROR_IO_PENDING:
		var size uint32
		return windows.GetOverlappedResult(h, &op, &size, true)
	default:
		return err
	}
}

func newPipeInstance(pipe, ownerSID string, first bool) (windows.Handle, error) {
	sd, err := windows.SecurityDescriptorFromString(pipeSDDL(ownerSID))
	if err != nil {
		return 0, fmt.Errorf("pipe SDDL: %w", err)
	}
	sa := &windows.SecurityAttributes{Length: uint32(unsafe.Sizeof(windows.SecurityAttributes{})), SecurityDescriptor: sd}
	mode := uint32(windows.PIPE_ACCESS_DUPLEX | windows.FILE_FLAG_OVERLAPPED)
	if first {
		mode |= windows.FILE_FLAG_FIRST_PIPE_INSTANCE
	}
	h, err := windows.CreateNamedPipe(windows.StringToUTF16Ptr(pipe), mode,
		windows.PIPE_TYPE_BYTE|windows.PIPE_READMODE_BYTE|windows.PIPE_WAIT|windows.PIPE_REJECT_REMOTE_CLIENTS,
		windows.PIPE_UNLIMITED_INSTANCES, 64<<10, 64<<10, 0, sa)
	if err != nil {
		return 0, fmt.Errorf("CreateNamedPipe: %w", err)
	}
	return h, nil
}

func serveConn(h windows.Handle, allowPCM bool) {
	f := os.NewFile(uintptr(h), "pipe")
	defer f.Close()
	if err := f.SetReadDeadline(time.Now().Add(5 * time.Second)); err != nil {
		return
	}
	r := bufio.NewReaderSize(f, maxHelperRequest)
	line, err := r.ReadSlice('\n')
	if err != nil {
		return
	}
	var req ipc.Request
	resp := ipc.Response{}
	if err := json.Unmarshal(line, &req); err != nil {
		resp.Error = "bad request"
	} else if req.Op == budsPCMOperation {
		if allowPCM {
			serveBudsPCM(f, r)
			return
		}
		resp.Error = "Buds PCM requires a configured service owner"
	} else {
		resp = Handle(req)
	}
	b, _ := json.Marshal(resp)
	b = append(b, '\n')
	if err := f.SetWriteDeadline(time.Now().Add(5 * time.Second)); err != nil {
		return
	}
	if _, err := f.Write(b); err != nil {
		logx.Printf("pipe write: %v", err)
	}
}

// ErrNoService means the helper service is not reachable.
var ErrNoService = i18n.Error("служба не запущена", "the service is not running")
var errUnexpectedPipeServer = i18n.Error("канал не принадлежит службе SSCv2", "the pipe does not belong to the SSCv2 service")

// callPipe sends one request to the running service.
func callPipe(req ipc.Request) (ipc.Response, error) {
	status, _ := serviceStatus()
	if status.State != svc.Running || status.ProcessId == 0 {
		return ipc.Response{}, ErrNoService
	}
	return callPipeAt(pipeName, status.ProcessId, req)
}

func callPipeAt(pipe string, servicePID uint32, req ipc.Request) (ipc.Response, error) {
	f, err := connectPipe(pipe, servicePID)
	if err != nil {
		return ipc.Response{}, err
	}
	defer f.Close()
	// Driver transitions have a multi-minute deadline of their own.
	timeout := 30 * time.Second
	if req.Op == "driver" {
		timeout = 8 * time.Minute
	} else if req.Op == "test-signing" || req.Op == "native-profile-sync" ||
		req.Op == "native-render-ensure" || req.Op == "native-render-restore" ||
		req.Op == "native-avrcp-release" || req.Op == "native-a2dp-resume" ||
		req.Op == "native-stereo-bind" || req.Op == "native-stereo-restore" {
		timeout = 5 * time.Minute
	}
	if err := f.SetDeadline(time.Now().Add(timeout)); err != nil {
		return ipc.Response{}, err
	}
	b, _ := json.Marshal(req)
	if _, err := f.Write(append(b, '\n')); err != nil {
		return ipc.Response{}, err
	}
	line, err := bufio.NewReader(f).ReadBytes('\n')
	if err != nil {
		return ipc.Response{}, fmt.Errorf(i18n.T("ответ службы: %w", "service reply: %w"), err)
	}
	var resp ipc.Response
	err = json.Unmarshal(line, &resp)
	return resp, err
}

func connectPipe(pipe string, servicePID uint32) (*os.File, error) {
	name := windows.StringToUTF16Ptr(pipe)
	var h windows.Handle
	var err error
	for i := 0; i < 20; i++ {
		h, err = windows.CreateFile(name, windows.GENERIC_READ|windows.FILE_WRITE_DATA, 0, nil, windows.OPEN_EXISTING,
			windows.FILE_FLAG_OVERLAPPED|windows.SECURITY_SQOS_PRESENT|windows.SECURITY_IDENTIFICATION, 0)
		if err == nil {
			break
		}
		if err != windows.ERROR_PIPE_BUSY && err != windows.ERROR_FILE_NOT_FOUND {
			return nil, ErrNoService
		}
		time.Sleep(100 * time.Millisecond)
	}
	if err != nil {
		return nil, ErrNoService
	}
	f := os.NewFile(uintptr(h), "pipe")

	var pid uint32
	if err := windows.GetNamedPipeServerProcessId(h, &pid); err != nil {
		f.Close()
		return nil, fmt.Errorf("GetNamedPipeServerProcessId: %w", err)
	}
	if pid == 0 || pid != servicePID {
		f.Close()
		return nil, errUnexpectedPipeServer
	}
	return f, nil
}
