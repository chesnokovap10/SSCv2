package main

import (
	"fmt"
	"os"

	"sscv2/internal/nativebt"
)

func main() {
	if err := nativebt.RunProbe(os.Args[1:], os.Stdout); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}
