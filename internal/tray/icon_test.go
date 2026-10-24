package tray

import (
	"image"
	"image/color"
	"image/png"
	"os"
	"testing"
)

func TestRenderGlyph(t *testing.T) {
	px := 64
	glyphSize = float64(px)
	img := image.NewRGBA(image.Rect(0, 0, px*5, px))
	for k, c := range []Color{Gray, Blue, Amber, Green, Red} {
		for y := 0; y < px; y++ {
			for x := 0; x < px; x++ {
				a := coverage(float64(x), float64(y))
				bg := 255.0
				blend := func(v uint32) uint8 { return uint8(float64(v)*a + bg*(1-a)) }
				img.Set(k*px+x, y, color.RGBA{blend(uint32(c >> 16 & 0xFF)), blend(uint32(c >> 8 & 0xFF)), blend(uint32(c & 0xFF)), 255})
			}
		}
	}
	out := os.Getenv("ICON_OUT")
	if out == "" {
		t.Skip("set ICON_OUT=<file.png> to render the tray glyphs")
	}
	f, err := os.Create(out)
	if err != nil {
		t.Fatal(err)
	}
	defer f.Close()
	png.Encode(f, img)
}
