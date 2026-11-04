package tray

import (
	"image"
	"image/color"
	"math"
	"unsafe"

	"golang.org/x/sys/windows"
)

// Color of the tray glyph.
type Color uint32

type IconMode uint8

const (
	IconOff IconMode = iota
	IconAAC
	IconSSC
	IconSSCPlus
)

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
	return headphones(px/glyphSize, py/glyphSize)
}

func headphones(x, y float64) bool {
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
func makeIcon(c Color, mode IconMode, px int) uintptr {
	bih := bitmapInfoHeader{biWidth: int32(px), biHeight: -int32(px), biPlanes: 1, biBitCount: 32}
	bih.biSize = uint32(unsafe.Sizeof(bih))
	var bits uintptr
	hbm, _, _ := pCreateDIBSection.Call(0, uintptr(unsafe.Pointer(&bih)), 0, uintptr(unsafe.Pointer(&bits)), 0, 0)
	if hbm == 0 {
		return 0
	}
	drawIconMode(hbm, mode, px)
	pix := unsafe.Slice((*uint32)(unsafe.Pointer(bits)), px*px)
	r, g, b := float64(c>>16&0xFF), float64(c>>8&0xFF), float64(c&0xFF)
	for y := 0; y < px; y++ {
		for x := 0; x < px; x++ {
			textAlpha := float64(pix[y*px+x]&255) / 255
			a := max(textAlpha, trayHeadphonesCoverage(px, x, y))
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

var (
	iconModeText     = [...]string{"OFF", "AAC", "SSC", "SSC+"}
	createIconDC     = gdi32.NewProc("CreateCompatibleDC")
	deleteIconDC     = gdi32.NewProc("DeleteDC")
	createIconFont   = gdi32.NewProc("CreateFontW")
	flushIconDrawing = gdi32.NewProc("GdiFlush")
)

func drawIconMode(bitmap uintptr, mode IconMode, size int) {
	dc, _, _ := createIconDC.Call(0)
	if dc == 0 {
		return
	}
	defer deleteIconDC.Call(dc)
	oldBitmap, _, _ := selectObject.Call(dc, bitmap)
	defer selectObject.Call(dc, oldBitmap)
	face, _ := windows.UTF16PtrFromString("Segoe UI")
	height := -max(5, (size*34+50)/100)
	font, _, _ := createIconFont.Call(uintptr(height), 0, 0, 0, 600, 0, 0, 0, 1, 0, 0, 4, 0,
		uintptr(unsafe.Pointer(face))) // ANTIALIASED_QUALITY
	if font == 0 {
		return
	}
	defer pDeleteObject.Call(font)
	oldFont, _, _ := selectObject.Call(dc, font)
	defer selectObject.Call(dc, oldFont)
	setTextColor.Call(dc, 0xffffff)
	setBkMode.Call(dc, 1)
	label, _ := windows.UTF16PtrFromString(iconModeText[mode])
	bounds := menuRect{top: int32(iconLabelTop(size)), right: int32(size), bottom: int32(size)}
	drawText.Call(dc, uintptr(unsafe.Pointer(label)), ^uintptr(0), uintptr(unsafe.Pointer(&bounds)), 0x825)
	flushIconDrawing.Call()
}

func iconLabelTop(size int) int { return size - (size*32+50)/100 }

func trayHeadphonesCoverage(px, x, y int) float64 {
	const glyphTop, glyphBottom = 0.15, 0.92
	size := float64(iconLabelTop(px)-2) / (glyphBottom - glyphTop)
	width := min(float64(px), size*1.2)
	left := (float64(px) - width) / 2
	hits := 0
	for dy := 0; dy < 4; dy++ {
		for dx := 0; dx < 4; dx++ {
			sx := (float64(x) + (float64(dx)+0.5)/4 - left) / width
			sy := glyphTop + (float64(y)+(float64(dy)+0.5)/4-1)/size
			if headphones(sx, sy) {
				hits++
			}
		}
	}
	return float64(hits) / 16
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
