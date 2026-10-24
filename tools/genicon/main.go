// genicon writes cmd/ssc/app.ico (the tray glyph, several sizes, PNG
// entries) and compiles cmd/ssc/rsrc_windows_amd64.syso with windres:
//
//	go run ./tools/genicon
package main

import (
	"bytes"
	"encoding/binary"
	"image/png"
	"os"
	"os/exec"

	"sscv2/internal/tray"
)

func main() {
	sizes := []int{16, 20, 24, 32, 40, 48, 64, 256}
	var imgs [][]byte
	for _, s := range sizes {
		var b bytes.Buffer
		if err := png.Encode(&b, tray.Glyph(tray.Green, s)); err != nil {
			panic(err)
		}
		imgs = append(imgs, b.Bytes())
	}
	var ico bytes.Buffer
	binary.Write(&ico, binary.LittleEndian, []uint16{0, 1, uint16(len(sizes))})
	off := 6 + 16*len(sizes)
	for i, s := range sizes {
		w := byte(s)
		if s >= 256 {
			w = 0
		}
		ico.Write([]byte{w, w, 0, 0})
		binary.Write(&ico, binary.LittleEndian, []uint16{1, 32})
		binary.Write(&ico, binary.LittleEndian, []uint32{uint32(len(imgs[i])), uint32(off)})
		off += len(imgs[i])
	}
	for _, b := range imgs {
		ico.Write(b)
	}
	if err := os.WriteFile("cmd/ssc/app.ico", ico.Bytes(), 0o644); err != nil {
		panic(err)
	}
	cmd := exec.Command("windres", "-O", "coff", "-i", "app.rc", "-o", "rsrc_windows_amd64.syso")
	cmd.Dir = "cmd/ssc"
	cmd.Stdout, cmd.Stderr = os.Stdout, os.Stderr
	if err := cmd.Run(); err != nil {
		panic(err)
	}
}
