package nativebt

/*
#cgo LDFLAGS: -lws2_32
#include <winsock2.h>
#include <ws2bth.h>

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
	"time"
	"unsafe"

	"golang.org/x/sys/windows"

	"sscv2/internal/battery"
)

// ReadBudsBattery takes one sample over Windows RFCOMM. Callers check that
// the headphones are already connected before opening the socket.
func ReadBudsBattery(address uint64) (battery.BudsLevel, bool) {
	var wsa windows.WSAData
	if err := windows.WSAStartup(0x0202, &wsa); err != nil {
		return battery.BudsLevel{}, false
	}
	defer windows.WSACleanup()
	guid, err := windows.GUIDFromString("{" + battery.BudsService + "}")
	if err != nil {
		return battery.BudsLevel{}, false
	}
	socket := C.buds_connect(C.BTH_ADDR(address), (*C.GUID)(unsafe.Pointer(&guid)))
	if socket == C.INVALID_SOCKET {
		return battery.BudsLevel{}, false
	}
	defer C.closesocket(socket)
	query := battery.ManagerInfo()
	for data := query[:]; len(data) > 0; {
		n := int(C.send(socket, (*C.char)(unsafe.Pointer(&data[0])), C.int(len(data)), 0))
		if n <= 0 {
			return battery.BudsLevel{}, false
		}
		data = data[n:]
	}
	var decoder battery.BudsDecoder
	var buf [512]byte
	var level battery.BudsLevel
	var received bool
	deadline := time.Now().Add(3 * time.Second)
	for !received && time.Now().Before(deadline) {
		n := int(C.recv(socket, (*C.char)(unsafe.Pointer(&buf[0])), C.int(len(buf)), 0))
		if n <= 0 {
			break
		}
		decoder.Feed(buf[:n], func(report battery.BudsLevel) { level, received = report, true })
	}
	return level, received
}
