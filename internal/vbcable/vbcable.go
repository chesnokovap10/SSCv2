// Package vbcable carries the VB-Audio Virtual Cable driver (x64, Windows
// 10+) inside ssc.exe. It backs the "virtual headphones" output device; the
// helper extracts it to a private folder and installs it on demand.
//
// The driver is VB-Audio's (https://vb-audio.com/Cable/), Microsoft-signed.
package vbcable

import (
	"embed"
	"os"
	"path/filepath"
)

//go:embed files/*
var files embed.FS

// Files of the driver package; the first one is the INF, the last the catalog.
var Files = []string{"vbMmeCable64_win10.inf", "vbaudio_cable64_win10.sys", "vbaudio_cable64_win10.cat"}

// Extract writes the driver package into a new private temp folder and
// returns it; the caller removes it when done.
func Extract() (string, error) {
	dir, err := os.MkdirTemp("", "sscv2vbc")
	if err != nil {
		return "", err
	}
	for _, f := range Files {
		b, err := files.ReadFile("files/" + f)
		if err == nil {
			err = os.WriteFile(filepath.Join(dir, f), b, 0o600)
		}
		if err != nil {
			os.RemoveAll(dir)
			return "", err
		}
	}
	return dir, nil
}
