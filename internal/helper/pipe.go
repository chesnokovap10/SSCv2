package helper

import (
	"bufio"
	"encoding/json"
	"fmt"
	"os"
	"sscv2/internal/i18n"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"

	"sscv2/internal/ipc"
	"sscv2/internal/logx"
)

const pipeName = `\\.\pipe\SSCv2Helper`

// pipeSDDL lets SYSTEM, Administrators and the owner (the user who installed
// the service) connect; nobody else may drive the privileged operations.
func pipeSDDL(ownerSID string) string {
	if ownerSID == "" {
		ownerSID = "IU" // interactive users
	}
	return "D:P(A;;GA;;;SY)(A;;GA;;;BA)(A;;GRGW;;;" + ownerSID + ")"
}

// Serve accepts helper requests until the process exits.
func Serve(ownerSID string) error {
	sd, err := windows.SecurityDescriptorFromString(pipeSDDL(ownerSID))
	if err != nil {
		return fmt.Errorf("pipe SDDL: %w", err)
	}
	sa := &windows.SecurityAttributes{Length: uint32(unsafe.Sizeof(windows.SecurityAttributes{})), SecurityDescriptor: sd}
	name, _ := windows.UTF16PtrFromString(pipeName)
	for {
		h, err := windows.CreateNamedPipe(name,
			windows.PIPE_ACCESS_DUPLEX,
			windows.PIPE_TYPE_BYTE|windows.PIPE_READMODE_BYTE|windows.PIPE_WAIT|windows.PIPE_REJECT_REMOTE_CLIENTS,
			windows.PIPE_UNLIMITED_INSTANCES, 64<<10, 64<<10, 0, sa)
		if err != nil {
			return fmt.Errorf("CreateNamedPipe: %w", err)
		}
		if err := windows.ConnectNamedPipe(h, nil); err != nil && err != windows.ERROR_PIPE_CONNECTED {
			windows.CloseHandle(h)
			time.Sleep(100 * time.Millisecond)
			continue
		}
		go serveConn(h)
	}
}

func serveConn(h windows.Handle) {
	f := os.NewFile(uintptr(h), "pipe")
	defer func() {
		windows.FlushFileBuffers(h)
		windows.DisconnectNamedPipe(h)
		f.Close()
	}()
	r := bufio.NewReader(f)
	line, err := r.ReadBytes('\n')
	if err != nil {
		return
	}
	var req ipc.Request
	resp := ipc.Response{}
	if err := json.Unmarshal(line, &req); err != nil {
		resp.Error = "bad request"
	} else {
		resp = Handle(req)
	}
	b, _ := json.Marshal(resp)
	b = append(b, '\n')
	if _, err := f.Write(b); err != nil {
		logx.Printf("pipe write: %v", err)
	}
}

// ErrNoService means the helper service is not reachable.
var ErrNoService = i18n.Error("служба не запущена", "the service is not running")

// callPipe sends one request to the running service.
func callPipe(req ipc.Request) (ipc.Response, error) {
	name, _ := windows.UTF16PtrFromString(pipeName)
	var h windows.Handle
	var err error
	for i := 0; i < 20; i++ {
		h, err = windows.CreateFile(name, windows.GENERIC_READ|windows.GENERIC_WRITE, 0, nil, windows.OPEN_EXISTING, 0, 0)
		if err == nil {
			break
		}
		if err != windows.ERROR_PIPE_BUSY {
			return ipc.Response{}, ErrNoService
		}
		time.Sleep(100 * time.Millisecond)
	}
	if err != nil {
		return ipc.Response{}, ErrNoService
	}
	f := os.NewFile(uintptr(h), "pipe")
	defer f.Close()
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
