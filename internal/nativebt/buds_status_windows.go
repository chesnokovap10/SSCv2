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

	"sscv2/internal/buds"
)

// ReadBudsStatus takes one sample over Windows RFCOMM. Callers check that
// the headphones are already connected before opening the socket.
func ReadBudsStatus(address uint64, protocol buds.Protocol, preset *uint8) (buds.Status, bool) {
	status := buds.Status{Level: buds.Level{Left: -1, Right: -1}}
	var commands chan uint8
	if preset != nil {
		commands = make(chan uint8, 1)
		commands <- *preset
	}
	ctx, cancel := context.WithTimeout(context.Background(), 6*time.Second)
	defer cancel()
	confirmed := false
	readBudsStatus(ctx, address, protocol, commands, nil, nil, func(report buds.Status) bool {
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

func readBudsStatus(ctx context.Context, address uint64, protocol buds.Protocol, commands <-chan uint8, removal *buds.Removal, removed func(), report func(buds.Status) bool) {
	var wsa windows.WSAData
	if err := windows.WSAStartup(0x0202, &wsa); err != nil {
		return
	}
	defer windows.WSACleanup()
	guid, err := windows.GUIDFromString("{" + protocol.Service() + "}")
	if err != nil {
		return
	}
	socket := C.buds_connect(C.BTH_ADDR(address), (*C.GUID)(unsafe.Pointer(&guid)))
	if socket == C.INVALID_SOCKET {
		return
	}
	defer C.closesocket(socket)
	if !sendBudsFrame(socket, protocol.ManagerInfo()) {
		return
	}
	decoder := buds.Decoder{Protocol: protocol}
	var equalizer buds.EqualizerState
	var buf [512]byte
	firstReport := time.Now().Add(3 * time.Second)
	for ctx.Err() == nil {
		if !firstReport.IsZero() && time.Now().After(firstReport) {
			return
		}
		wait := time.Second
		if commands != nil && equalizer.Current() != nil {
			wait = 250 * time.Millisecond
			select {
			case preset := <-commands:
				if !sendBudsFrame(socket, protocol.EqualizerRequest(preset)) {
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
		decoder.FeedStatus(buf[:n], func(status buds.Status) {
			if !stop && ctx.Err() == nil {
				if !status.EqualizerAck {
					firstReport = time.Time{}
				}
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

func watchBudsStatus(ctx context.Context, address uint64, protocol buds.Protocol, commands <-chan uint8, report func(buds.Status), removed func()) {
	for ctx.Err() == nil {
		removal := &buds.Removal{}
		var last buds.Status
		var reportedAt time.Time
		received := false
		readBudsStatus(ctx, address, protocol, commands, removal, removed, func(status buds.Status) bool {
			received = true
			eqChanged := status.Equalizer != nil && (last.Equalizer == nil || *status.Equalizer != *last.Equalizer)
			if status.Level.Known() && (status.Level != last.Level || time.Since(reportedAt) >= buds.PollInterval) || eqChanged {
				report(status)
				last.Level, reportedAt = status.Level, time.Now()
				if status.Equalizer != nil {
					last.Equalizer = status.Equalizer
				}
			}
			return false
		})
		if ctx.Err() == nil {
			report(buds.Status{Level: buds.Level{Left: -1, Right: -1}})
		}
		delay := buds.PollInterval
		if received {
			delay = 5 * time.Second
		}
		timer := time.NewTimer(delay)
		select {
		case <-ctx.Done():
			timer.Stop()
			return
		case <-timer.C:
		}
	}
}
