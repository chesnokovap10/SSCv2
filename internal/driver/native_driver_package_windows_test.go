package driver

import (
	"bytes"
	"crypto/x509"
	"os"
	"path/filepath"
	"testing"
)

func TestEmbeddedDriverPackages(t *testing.T) {
	if _, err := x509.ParseCertificate(nativeDriverSigner); err != nil {
		t.Fatal(err)
	}
	for _, p := range []nativeDriverPackage{avdtpPackage, waveRTPackage} {
		t.Run(p.directory, func(t *testing.T) {
			dir := t.TempDir()
			inf, err := p.extract(dir)
			if err != nil {
				t.Fatal(err)
			}
			if inf != filepath.Join(dir, p.inf) {
				t.Fatalf("staging INF path = %q", inf)
			}
			for _, name := range []string{p.inf, p.sys, p.catalog} {
				want, err := p.read(name)
				if err != nil {
					t.Fatal(err)
				}
				got, err := os.ReadFile(filepath.Join(dir, name))
				if err != nil {
					t.Fatal(err)
				}
				if len(want) == 0 || !bytes.Equal(got, want) {
					t.Fatalf("staging changed or omitted %s", name)
				}
			}
			if _, err := p.version(); err != nil {
				t.Fatal(err)
			}
		})
	}
}
