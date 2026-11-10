package helper

import (
	"bufio"
	"encoding/binary"
	"encoding/json"
	"errors"
	"io"
	"os"

	"golang.org/x/sys/windows/svc"

	"sscv2/internal/driver"
	"sscv2/internal/ipc"
	"sscv2/internal/logx"
)

const budsPCMOperation = "native-render-pcm"
const budsPCMMax = 4096

type budsPCMReader struct {
	*os.File
	input *bufio.Reader
}

// OpenBudsPCM connects to the running helper for the lifetime of the codec worker.
func OpenBudsPCM() (*budsPCMReader, error) {
	status, _ := serviceStatus()
	if status.State != svc.Running || status.ProcessId == 0 {
		return nil, ErrNoService
	}
	f, err := connectPipe(pipeName, status.ProcessId)
	if err != nil {
		return nil, err
	}
	input := bufio.NewReader(f)
	if err := json.NewEncoder(f).Encode(ipc.Request{Op: budsPCMOperation}); err != nil {
		f.Close()
		return nil, err
	}
	if err := readBudsPCMStatus(input); err != nil {
		f.Close()
		return nil, err
	}
	return &budsPCMReader{File: f, input: input}, nil
}

func readBudsPCMStatus(input *bufio.Reader) error {
	line, err := input.ReadBytes('\n')
	if err != nil {
		return err
	}
	var resp ipc.Response
	if err := json.Unmarshal(line, &resp); err != nil {
		return err
	}
	if !resp.OK {
		return errors.New(resp.Error)
	}
	return nil
}

func (r *budsPCMReader) Read(buffer []byte) (int, error) {
	if len(buffer) < 4 || len(buffer) > budsPCMMax || len(buffer)%4 != 0 {
		return 0, errors.New("invalid Buds PCM request size")
	}
	var header [2]byte
	binary.LittleEndian.PutUint16(header[:], uint16(len(buffer)))
	if _, err := r.Write(header[:]); err != nil {
		return 0, err
	}
	if _, err := io.ReadFull(r.input, header[:]); err != nil {
		return 0, err
	}
	size := int(binary.LittleEndian.Uint16(header[:]))
	if size == 0xffff {
		return 0, readBudsPCMStatus(r.input)
	}
	if size > len(buffer) || size%4 != 0 {
		return 0, errors.New("invalid Buds PCM response size")
	}
	return io.ReadFull(r.input, buffer[:size])
}

func serveBudsPCM(f *os.File, input *bufio.Reader) {
	reply := json.NewEncoder(f)
	path, err := driver.BudsRenderInterface()
	if err != nil {
		_ = reply.Encode(ipc.Response{Error: err.Error()})
		return
	}
	device, err := driver.OpenBudsPCM(path)
	if err != nil {
		_ = reply.Encode(ipc.Response{Error: err.Error()})
		return
	}
	defer device.Close()
	if err := reply.Encode(ipc.Response{OK: true}); err != nil {
		return
	}
	var packet [2 + budsPCMMax]byte
	for {
		if _, err := io.ReadFull(input, packet[:2]); err != nil {
			return
		}
		size := int(binary.LittleEndian.Uint16(packet[:2]))
		if size < 4 || size > budsPCMMax || size%4 != 0 {
			return
		}
		n, err := device.Read(packet[2 : 2+size])
		if err != nil {
			logx.Printf("Buds PCM: %v", err)
			binary.LittleEndian.PutUint16(packet[:2], 0xffff)
			if _, writeErr := f.Write(packet[:2]); writeErr == nil {
				_ = reply.Encode(ipc.Response{Error: err.Error()})
			}
			return
		}
		binary.LittleEndian.PutUint16(packet[:2], uint16(n))
		if _, err := f.Write(packet[:2+n]); err != nil {
			return
		}
	}
}
