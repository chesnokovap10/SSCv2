// Package bt runs BTstack (user-mode Bluetooth stack over WinUSB) and
// exposes a small synchronous API: bring-up, inquiry, A2DP source with
// AAC/SSC endpoints, AVRCP absolute volume and the BLE HID mouse bridge.
//
// BTstack is single-threaded: it runs on one OS thread (locked goroutine)
// and every BTstack call is posted to that thread (see call/callSync).
// BTstack events arrive in goBtPacket on the same thread.
package bt

/*
#cgo CFLAGS: -O2 -w -I${SRCDIR} -I${SRCDIR}/../../third_party/btstack/src -I${SRCDIR}/../../third_party/btstack/platform/windows -I${SRCDIR}/../../third_party/btstack/3rd-party/rijndael -I${SRCDIR}/../../third_party/btstack/3rd-party/micro-ecc -D_WIN32_WINNT=0x0A00 -DWIN32_LEAN_AND_MEAN
#cgo LDFLAGS: -lsetupapi -lwinusb -lws2_32
*/
import "C"
