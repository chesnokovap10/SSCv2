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
	r := &BudsPCM{handle: handle}
	if _, err := r.property(2, nil); err != nil {
		r.Close()
		return nil, fmt.Errorf("reset Buds PCM session: %w", err)
	}
	return r, nil
}

func (r *BudsPCM) Close() error { return windows.CloseHandle(r.handle) }

func (r *BudsPCM) Read(buffer []byte) (int, error) {
	if len(buffer) < 4 || len(buffer)%4 != 0 {
		return 0, fmt.Errorf("invalid PCM buffer size %d", len(buffer))
	}
	return r.property(1, buffer)
}

func (r *BudsPCM) property(flags uint32, buffer []byte) (int, error) {
	const ioctlKSProperty = 0x002f0003
	property := struct {
		set   windows.GUID
		id    uint32
		flags uint32
	}{
		set:   windows.GUID{Data1: 0xcbf893b1, Data2: 0xa248, Data3: 0x4b4c, Data4: [8]byte{0x84, 0x35, 0x90, 0x78, 0x79, 0x8c, 0x7e, 0x23}},
		flags: flags,
	}
	var read uint32
	var output *byte
	if len(buffer) > 0 {
		output = &buffer[0]
	}
	err := windows.DeviceIoControl(r.handle, ioctlKSProperty, (*byte)(unsafe.Pointer(&property)), uint32(unsafe.Sizeof(property)), output, uint32(len(buffer)), &read, nil)
	if err != nil {
		return 0, fmt.Errorf("read Buds WaveRT PCM: %w", err)
	}
	if read > uint32(len(buffer)) || read%4 != 0 {
		return 0, fmt.Errorf("invalid WaveRT PCM size: %d", read)
	}
	return int(read), nil
}
