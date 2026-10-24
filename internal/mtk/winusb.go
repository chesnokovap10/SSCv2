package mtk

import (
	"fmt"
	"strings"
	"syscall"
	"unsafe"

	"golang.org/x/sys/windows"
)

var (
	modWinUSB                   = windows.NewLazySystemDLL("winusb.dll")
	procWinUsbInitialize        = modWinUSB.NewProc("WinUsb_Initialize")
	procWinUsbFree              = modWinUSB.NewProc("WinUsb_Free")
	procWinUsbControlTransfer   = modWinUSB.NewProc("WinUsb_ControlTransfer")
	procWinUsbReadPipe          = modWinUSB.NewProc("WinUsb_ReadPipe")
	procWinUsbQueryIfSettings   = modWinUSB.NewProc("WinUsb_QueryInterfaceSettings")
	procWinUsbQueryPipe         = modWinUSB.NewProc("WinUsb_QueryPipe")
	procWinUsbSetPipePolicy     = modWinUSB.NewProc("WinUsb_SetPipePolicy")
	guidDevInterfaceUSBDevice   = windows.GUID{Data1: 0xA5DCBF10, Data2: 0x6530, Data3: 0x11D2, Data4: [8]byte{0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED}}
	errNotFound                 = fmt.Errorf("адаптер не найден в режиме WinUSB")
)

const pipeTransferTimeout = 0x03

type usbDev struct {
	file   windows.Handle
	usb    uintptr
	evtEP  uint8
	logf   func(string, ...any)
}

// devicePath returns the whole-device interface path for vid:pid (never an
// interface of a composite device).
func devicePath(vid, pid uint16) (string, error) {
	list, err := windows.CM_Get_Device_Interface_List("", &guidDevInterfaceUSBDevice,
		windows.CM_GET_DEVICE_INTERFACE_LIST_PRESENT)
	if err != nil {
		return "", errNotFound
	}
	needle := fmt.Sprintf("vid_%04x&pid_%04x", vid, pid)
	for _, p := range list {
		l := strings.ToLower(p)
		if strings.Contains(l, needle) && !strings.Contains(l, "&mi_") {
			return p, nil
		}
	}
	return "", errNotFound
}

// Present reports whether vid:pid has a whole-device USB interface.
func Present(vid, pid uint16) bool {
	_, err := devicePath(vid, pid)
	return err == nil
}

func openDev(vid, pid uint16, logf func(string, ...any)) (*usbDev, error) {
	path, err := devicePath(vid, pid)
	if err != nil {
		return nil, err
	}
	d := &usbDev{file: windows.InvalidHandle, evtEP: 0x81, logf: logf}
	p16, _ := windows.UTF16PtrFromString(path)
	h, err := windows.CreateFile(p16, windows.GENERIC_READ|windows.GENERIC_WRITE,
		windows.FILE_SHARE_READ|windows.FILE_SHARE_WRITE, nil, windows.OPEN_EXISTING,
		windows.FILE_ATTRIBUTE_NORMAL|windows.FILE_FLAG_OVERLAPPED, 0)
	if err != nil {
		return nil, fmt.Errorf("не удалось открыть адаптер (занят или не WinUSB): %w", err)
	}
	d.file = h
	r, _, e := procWinUsbInitialize.Call(uintptr(h), uintptr(unsafe.Pointer(&d.usb)))
	if r == 0 {
		windows.CloseHandle(h)
		return nil, fmt.Errorf("WinUsb_Initialize: %v (драйвер WinUSB установлен?)", e)
	}

	// Locate the HCI event (interrupt IN) endpoint on interface 0.
	var ifd [9]byte
	if r, _, _ := procWinUsbQueryIfSettings.Call(d.usb, 0, uintptr(unsafe.Pointer(&ifd[0]))); r != 0 {
		for i := 0; i < int(ifd[4]); i++ {
			var pi struct {
				PipeType   int32
				PipeID     uint8
				_          uint8
				MaxPacket  uint16
				Interval   uint8
				_          [3]byte
			}
			if r, _, _ := procWinUsbQueryPipe.Call(d.usb, 0, uintptr(i), uintptr(unsafe.Pointer(&pi))); r != 0 {
				if pi.PipeType == 3 /* interrupt */ && pi.PipeID&0x80 != 0 {
					d.evtEP = pi.PipeID
					break
				}
			}
		}
	}
	to := uint32(50)
	procWinUsbSetPipePolicy.Call(d.usb, uintptr(d.evtEP), pipeTransferTimeout, 4, uintptr(unsafe.Pointer(&to)))
	return d, nil
}

func (d *usbDev) close() {
	if d.usb != 0 {
		procWinUsbFree.Call(d.usb)
		d.usb = 0
	}
	if d.file != windows.InvalidHandle {
		windows.CloseHandle(d.file)
		d.file = windows.InvalidHandle
	}
}

// ctrl performs a control transfer; returns bytes transferred.
func (d *usbDev) ctrl(reqType, req uint8, val, idx uint16, buf []byte) (int, error) {
	setup := uint64(reqType) | uint64(req)<<8 | uint64(val)<<16 | uint64(idx)<<32 | uint64(len(buf))<<48
	var bp uintptr
	if len(buf) > 0 {
		bp = uintptr(unsafe.Pointer(&buf[0]))
	}
	var got uint32
	r, _, e := procWinUsbControlTransfer.Call(d.usb, uintptr(setup), bp, uintptr(len(buf)),
		uintptr(unsafe.Pointer(&got)), 0)
	if r == 0 {
		return 0, fmt.Errorf("control %02X/%02X %04X:%04X: %v", reqType, req, val, idx, e)
	}
	return int(got), nil
}

// readEvent reads one packet from the interrupt IN pipe (50 ms timeout).
func (d *usbDev) readEvent(buf []byte) int {
	var got uint32
	r, _, _ := procWinUsbReadPipe.Call(d.usb, uintptr(d.evtEP), uintptr(unsafe.Pointer(&buf[0])),
		uintptr(len(buf)), uintptr(unsafe.Pointer(&got)), 0)
	if r == 0 {
		return 0
	}
	return int(got)
}

var _ = syscall.EINVAL
