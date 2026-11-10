package driver

import (
	"fmt"
	"unsafe"

	"golang.org/x/sys/windows"
)

type BudsPCM struct{ handle windows.Handle }

func OpenBudsPCM(wavePath string) (*BudsPCM, error) {
	name, err := windows.UTF16PtrFromString(wavePath)
	if err != nil {
		return nil, err
	}
	handle, err := windows.CreateFile(name, windows.GENERIC_READ, windows.FILE_SHARE_READ|windows.FILE_SHARE_WRITE, nil, windows.OPEN_EXISTING, 0, 0)
	if err != nil {
		return nil, fmt.Errorf("open Buds WaveRT filter: %w", err)
	}
	return &BudsPCM{handle: handle}, nil
}

func (r *BudsPCM) Close() error { return windows.CloseHandle(r.handle) }

func (r *BudsPCM) Read(buffer []byte) (int, error) {
	const ioctlKSProperty = 0x002f0003
	const ksPropertyGet = 1
	property := struct {
		set   windows.GUID
		id    uint32
		flags uint32
	}{
		set:   windows.GUID{Data1: 0xcbf893b1, Data2: 0xa248, Data3: 0x4b4c, Data4: [8]byte{0x84, 0x35, 0x90, 0x78, 0x79, 0x8c, 0x7e, 0x23}},
		flags: ksPropertyGet,
	}
	var read uint32
	err := windows.DeviceIoControl(r.handle, ioctlKSProperty, (*byte)(unsafe.Pointer(&property)), uint32(unsafe.Sizeof(property)), &buffer[0], uint32(len(buffer)), &read, nil)
	if err != nil {
		return 0, fmt.Errorf("read Buds WaveRT PCM: %w", err)
	}
	if read > uint32(len(buffer)) || read%4 != 0 {
		return 0, fmt.Errorf("invalid WaveRT PCM size: %d", read)
	}
	return int(read), nil
}
