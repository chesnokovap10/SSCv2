package engine

import (
	"fmt"
	"strings"
)

// DevID is a Bluetooth Device ID (DI profile): vendor id source (1 =
// Bluetooth SIG company id, 2 = USB-IF), vendor and product.
type DevID struct{ Source, Vendor, Product uint16 }

func (d DevID) String() string {
	return fmt.Sprintf("%d:%04X:%04X", d.Source, d.Vendor, d.Product)
}

// profile: what was checked by ear on one headphones model.
type profile struct {
	Model string         // official model name, shown in the menu
	id    DevID          // Device ID of the model
	name  string         // lower-case part of the Bluetooth name (when the Device ID is unknown)
	max   map[string]int // codec ("aac" | "ssc" | "ssc_uhq") -> highest working kbps
}

// Only Samsung Galaxy Buds2 Pro (SM-R510; Device ID: Bluetooth SIG,
// Samsung 0x0075, product 0xA013) are checked so far: SSC 256k/328k (the
// encoder's "wide" 48 kHz modes, never sent by the phone) sound choked on
// them, 229k is the highest that sounds right. Other headphones have no
// profile: every bitrate is offered and "Auto" is the highest one packet
// holds.
var profiles = []profile{
	{Model: "Samsung Galaxy Buds2 Pro", id: DevID{1, 0x0075, 0xA013}, name: "buds2 pro", max: map[string]int{"ssc": 229}},
}

// findProfile matches by Device ID; by name only when the id is unknown.
func findProfile(id DevID, name string) *profile {
	for i := range profiles {
		if id.Vendor != 0 {
			if profiles[i].id == id {
				return &profiles[i]
			}
		} else if name != "" && strings.Contains(strings.ToLower(name), profiles[i].name) {
			return &profiles[i]
		}
	}
	return nil
}

// WorkingMax is the highest bitrate (kbps) checked to work for the codec on
// these headphones, and their model name; 0 = not known.
func WorkingMax(codec string, id DevID, name string) (int, string) {
	if p := findProfile(id, name); p != nil && p.max[codec] > 0 {
		return p.max[codec], p.Model
	}
	return 0, ""
}
