package nativebt

/*
#cgo LDFLAGS: -lws2_32
#include <winsock2.h>
#include <ws2bth.h>

static int buds_receive(SOCKET s, char *data, int size, long timeout_ms) {
	fd_set ready;
	FD_ZERO(&ready);
	FD_SET(s, &ready);
	struct timeval timeout = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};
	int result = select(0, &ready, NULL, NULL, &timeout);
	if (result == 0) return -2;
	if (result < 0) return -1;
	return recv(s, data, size, 0);
}

static SOCKET buds_connect(BTH_ADDR address, const GUID *service) {
	SOCKET s = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
	if (s == INVALID_SOCKET) return s;

	SOCKADDR_BTH peer = {0};
	peer.addressFamily = AF_BTH;
	peer.btAddr = address;
	peer.serviceClassId = *service;
	u_long nonblocking = 1;
	if (ioctlsocket(s, FIONBIO, &nonblocking) != 0) goto fail;
	if (connect(s, (SOCKADDR *)&peer, sizeof(peer)) != 0) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) goto fail;
		fd_set writable, failed;
		FD_ZERO(&writable);
		FD_ZERO(&failed);
		FD_SET(s, &writable);
		FD_SET(s, &failed);
		struct timeval timeout = {3, 0};
		if (select(0, NULL, &writable, &failed, &timeout) <= 0 ||
		    !FD_ISSET(s, &writable) || FD_ISSET(s, &failed)) goto fail;
	}

	nonblocking = 0;
	DWORD timeout_ms = 2500;
	if (ioctlsocket(s, FIONBIO, &nonblocking) != 0 ||
	    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout_ms, sizeof(timeout_ms)) != 0 ||
	    setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout_ms, sizeof(timeout_ms)) != 0) goto fail;
	return s;

fail:
	closesocket(s);
	return INVALID_SOCKET;
}
*/
import "C"

import (
	"context"
	"time"
	"unsafe"

	"golang.org/x/sys/windows"

	"sscv2/internal/battery"
)

// ReadBudsStatus takes one sample over Windows RFCOMM. Callers check that
// the headphones are already connected before opening the socket.
func ReadBudsStatus(address uint64, preset *uint8) (battery.BudsStatus, bool) {
	status := battery.BudsStatus{Level: battery.BudsLevel{Left: -1, Right: -1}}
	var commands chan uint8
	if preset != nil {
		commands = make(chan uint8, 1)
		commands <- *preset
	}
	ctx, cancel := context.WithTimeout(context.Background(), 6*time.Second)
	defer cancel()
	confirmed := false
	readBudsStatus(ctx, address, commands, nil, nil, func(report battery.BudsStatus) bool {
		if report.Level.Known() {
			status.Level = report.Level
		}
		if report.Equalizer != nil {
			status.Equalizer = report.Equalizer
		}
		confirmed = report.Equalizer != nil && (preset == nil || *report.Equalizer == *preset)
		return confirmed
	})
	return status, confirmed
}

func sendBudsFrame(socket C.SOCKET, data []byte) bool {
	for len(data) > 0 {
		n := int(C.send(socket, (*C.char)(unsafe.Pointer(&data[0])), C.int(len(data)), 0))
		if n <= 0 {
			return false
		}
		data = data[n:]
	}
	return true
}

func readBudsStatus(ctx context.Context, address uint64, commands <-chan uint8, removal *battery.BudsRemoval, removed func(), report func(battery.BudsStatus) bool) {
	var wsa windows.WSAData
	if err := windows.WSAStartup(0x0202, &wsa); err != nil {
		return
	}
	defer windows.WSACleanup()
	guid, err := windows.GUIDFromString("{" + battery.BudsService + "}")
	if err != nil {
		return
	}
	socket := C.buds_connect(C.BTH_ADDR(address), (*C.GUID)(unsafe.Pointer(&guid)))
	if socket == C.INVALID_SOCKET {
		return
	}
	defer C.closesocket(socket)
	query := battery.ManagerInfo()
	if !sendBudsFrame(socket, query[:]) {
		return
	}
	var decoder battery.BudsDecoder
	var equalizer battery.BudsEqualizerState
	var buf [512]byte
	for ctx.Err() == nil {
		wait := time.Second
		if commands != nil {
			wait = 250 * time.Millisecond
			select {
			case preset := <-commands:
				frame := battery.BudsEqualizerRequest(preset)
				if !sendBudsFrame(socket, frame[:]) {
					return
				}
			default:
			}
		}
		if removal != nil && !removal.Deadline().IsZero() {
			wait = min(wait, time.Until(removal.Deadline()))
		}
		n := int(C.buds_receive(socket, (*C.char)(unsafe.Pointer(&buf[0])), C.int(len(buf)), C.long(max(1, wait.Milliseconds()+1))))
		if n <= 0 {
			if n == -2 {
				if ctx.Err() == nil && removal != nil && removal.Confirm(time.Now()) {
					removed()
				}
				continue
			}
			return
		}
		stop := false
		decoder.FeedStatus(buf[:n], func(status battery.BudsStatus) {
			if !stop && ctx.Err() == nil {
				status.Equalizer = equalizer.Observe(status, time.Now())
				if removal != nil && !status.EqualizerAck {
					removal.Observe(status.Placement, time.Now())
				}
				stop = report(status)
			}
		})
		if stop {
			return
		}
		if ctx.Err() == nil && removal != nil && removal.Confirm(time.Now()) {
			removed()
		}
	}
}

func watchBudsStatus(ctx context.Context, address uint64, commands <-chan uint8, report func(battery.BudsStatus), removed func()) {
	for ctx.Err() == nil {
		removal := &battery.BudsRemoval{}
		var last battery.BudsStatus
		var reportedAt time.Time
		readBudsStatus(ctx, address, commands, removal, removed, func(status battery.BudsStatus) bool {
			eqChanged := status.Equalizer != nil && (last.Equalizer == nil || *status.Equalizer != *last.Equalizer)
			if status.Level.Known() && (status.Level != last.Level || time.Since(reportedAt) >= battery.PollInterval) || eqChanged {
				report(status)
				last.Level, reportedAt = status.Level, time.Now()
				if status.Equalizer != nil {
					last.Equalizer = status.Equalizer
				}
			}
			return false
		})
		if ctx.Err() == nil {
			report(battery.BudsStatus{Level: battery.BudsLevel{Left: -1, Right: -1}})
		}
		timer := time.NewTimer(5 * time.Second)
		select {
		case <-ctx.Done():
			timer.Stop()
			return
		case <-timer.C:
		}
	}
}
