package tray

import (
	"image"
	"image/color"
	"math"
	"unsafe"
)

// Color of the tray glyph.
type Color uint32

const (
	Gray  Color = 0x8A8A8A
	Blue  Color = 0x3D8BFD
	Amber Color = 0xF0A020
	Green Color = 0x2ECC71
	Red   Color = 0xE74C3C
)

// headphones signed-distance test: arc band + two ear cups, in unit space.
func coverage(x, y float64) float64 {
	// supersample 4x4
	const n = 4
	hit := 0
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			if inGlyph(x+(float64(i)+0.5)/n, y+(float64(j)+0.5)/n) {
				hit++
			}
		}
	}
	return float64(hit) / (n * n)
}

var glyphSize float64

func inGlyph(px, py float64) bool {
	s := glyphSize
	x, y := px/s, py/s // 0..1
	cx, cy := 0.5, 0.56
	r := math.Hypot(x-cx, y-cy)
	// headband: upper half ring
	if y <= cy && r >= 0.30 && r <= 0.41 {
		return true
	}
	// ear cups: rounded rectangles left and right
	cup := func(x0 float64) bool {
		x1, y0, y1, rad := x0+0.20, 0.52, 0.92, 0.07
		if x < x0 || x > x1 || y < y0 || y > y1 {
			return false
		}
		qx := math.Max(math.Max(x0+rad-x, x-(x1-rad)), 0)
		qy := math.Max(math.Max(y0+rad-y, y-(y1-rad)), 0)
		return qx*qx+qy*qy <= rad*rad
	}
	return cup(0.08) || cup(0.72)
}

// makeIcon renders the glyph in color c at size px and returns an HICON.
func makeIcon(c Color, px int) uintptr {
	glyphSize = float64(px)
	bih := bitmapInfoHeader{biWidth: int32(px), biHeight: -int32(px), biPlanes: 1, biBitCount: 32}
	bih.biSize = uint32(unsafe.Sizeof(bih))
	var bits uintptr
	hbm, _, _ := pCreateDIBSection.Call(0, uintptr(unsafe.Pointer(&bih)), 0, uintptr(unsafe.Pointer(&bits)), 0, 0)
	if hbm == 0 {
		return 0
	}
	pix := unsafe.Slice((*uint32)(unsafe.Pointer(bits)), px*px)
	r, g, b := float64(c>>16&0xFF), float64(c>>8&0xFF), float64(c&0xFF)
	for y := 0; y < px; y++ {
		for x := 0; x < px; x++ {
			a := coverage(float64(x), float64(y))
			// premultiplied BGRA
			pix[y*px+x] = uint32(a*255)<<24 | uint32(r*a)<<16 | uint32(g*a)<<8 | uint32(b*a)
		}
	}
	mask := make([]byte, ((px+15)/16)*2*px)
	hmask, _, _ := pCreateBitmap.Call(uintptr(px), uintptr(px), 1, 1, uintptr(unsafe.Pointer(&mask[0])))
	ii := iconInfo{fIcon: 1, hbmMask: hmask, hbmColor: hbm}
	h, _, _ := pCreateIconIndirect.Call(uintptr(unsafe.Pointer(&ii)))
	pDeleteObject.Call(hbm)
	pDeleteObject.Call(hmask)
	return h
}

// Glyph renders the headphones glyph (straight alpha) for the exe icon.
func Glyph(c Color, px int) *image.NRGBA {
	glyphSize = float64(px)
	img := image.NewNRGBA(image.Rect(0, 0, px, px))
	for y := 0; y < px; y++ {
		for x := 0; x < px; x++ {
			a := coverage(float64(x), float64(y))
			img.SetNRGBA(x, y, color.NRGBA{uint8(c >> 16), uint8(c >> 8), uint8(c), uint8(a * 255)})
		}
	}
	return img
}
