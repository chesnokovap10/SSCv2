package bt

// Functions called from C (shim.c). This file's preamble must only hold
// declarations (cgo //export rule).

/*
#include <stdint.h>
*/
import "C"

import (
	"unsafe"
)

//export goBtPacket
func goBtPacket(src C.int, ptype C.uint8_t, channel C.uint16_t, packet *C.uint8_t, size C.uint16_t) {
	if packet == nil {
		return
	}
	p := unsafe.Slice((*byte)(unsafe.Pointer(packet)), int(size))
	stack.onPacket(int(src), uint8(ptype), uint16(channel), p, packet)
}

//export goBtHci
func goBtHci(ptype C.uint8_t, in C.uint8_t, packet *C.uint8_t, size C.uint16_t) {
	if packet == nil {
		return
	}
	dump.onHCI(uint8(ptype), in != 0, unsafe.Slice((*byte)(unsafe.Pointer(packet)), int(size)))
}

//export goBtDrain
func goBtDrain() { stack.drain() }

//export goBtTimer
func goBtTimer(id C.int) { stack.onTimer(int(id)) }

//export goBtLog
func goBtLog(level C.int, msg *C.char) {
	stack.logf("BTstack[%d]: %s", int(level), C.GoString(msg))
}

func addrFromC(a *C.uint8_t) Addr {
	var out Addr
	copy(out[:], unsafe.Slice((*byte)(unsafe.Pointer(a)), 6))
	return out
}

//export goLinkKeyLocalAddr
func goLinkKeyLocalAddr(a *C.uint8_t) {
	stack.localAddr = addrFromC(a)
}

//export goLinkKeyGet
func goLinkKeyGet(a *C.uint8_t, key *C.uint8_t, typ *C.int) C.int {
	ks := stack.keys
	if ks == nil {
		return 0
	}
	k, t, ok := ks.Get(addrFromC(a))
	if !ok {
		return 0
	}
	copy(unsafe.Slice((*byte)(unsafe.Pointer(key)), 16), k[:])
	*typ = C.int(t)
	return 1
}

//export goLinkKeyPut
func goLinkKeyPut(a *C.uint8_t, key *C.uint8_t, typ C.int) {
	var k LinkKey
	copy(k[:], unsafe.Slice((*byte)(unsafe.Pointer(key)), 16))
	addr := addrFromC(a)
	if stack.keys != nil {
		stack.keys.Put(addr, k, int(typ))
	}
	stack.emit(Event{Kind: EvLinkKey, Addr: addr, Key: k, KeyType: int(typ)})
}

//export goLinkKeyDelete
func goLinkKeyDelete(a *C.uint8_t) {
	if stack.keys != nil {
		stack.keys.Delete(addrFromC(a))
	}
}

//export goLinkKeyAt
func goLinkKeyAt(idx C.int, a *C.uint8_t, key *C.uint8_t, typ *C.int) C.int {
	if stack.keys == nil {
		return 0
	}
	addr, k, t, ok := stack.keys.At(int(idx))
	if !ok {
		return 0
	}
	copy(unsafe.Slice((*byte)(unsafe.Pointer(a)), 6), addr[:])
	copy(unsafe.Slice((*byte)(unsafe.Pointer(key)), 16), k[:])
	*typ = C.int(t)
	return 1
}
