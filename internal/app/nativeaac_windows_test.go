package app

import (
	"testing"

	"sscv2/internal/audio"
)

func TestNativeOutputRestorationSkipsHandsFree(t *testing.T) {
	const buds = "Buds2 Pro JK08"
	handsFree := audio.Endpoint{ID: "handsfree", Name: "Головной телефон (Buds2 Pro JK08 Hands-Free AG Audio)"}
	stereo := audio.Endpoint{ID: "stereo", Name: "Наушники (Buds2 Pro JK08 Stereo)"}
	speakers := audio.Endpoint{ID: "speakers", Name: "Динамики (Realtek(R) Audio)"}
	endpoints := []audio.Endpoint{handsFree, speakers, stereo}
	if got := budsStereoOutput(endpoints, "wave", buds); got != stereo.ID {
		t.Fatalf("Buds stereo endpoint = %q, want %q", got, stereo.ID)
	}
	if got := budsStereoOutput(endpoints[:2], "wave", buds); got != "" {
		t.Fatalf("Hands-Free made stereo appear ready: %q", got)
	}
	if got := previousRenderOutput(endpoints, "wave", handsFree.ID, buds); got != stereo.ID {
		t.Fatalf("restored %q, want stereo", got)
	}
	if got := previousRenderOutput(endpoints[:2], "wave", stereo.ID, buds); got != speakers.ID {
		t.Fatalf("fallback %q, want speakers", got)
	}
	if got := previousRenderOutput(endpoints, "wave", speakers.ID, buds); got != speakers.ID {
		t.Fatalf("restored %q, want saved speakers", got)
	}
}
