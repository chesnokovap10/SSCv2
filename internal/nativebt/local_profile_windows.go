package nativebt

import (
	"errors"
	"fmt"
	"strconv"
	"strings"

	"sscv2/internal/driver"
)

var ErrLocalProfileUnavailable = errors.New("local AVDTP profile is not present")

func LocalProfilePath(address string) (string, error) {
	value, err := parseLocalAddress(address)
	if err != nil {
		return "", err
	}
	paths, err := driver.LocalProfileInterfaces()
	if err != nil {
		return "", err
	}
	if len(paths) == 0 {
		return "", ErrLocalProfileUnavailable
	}
	if len(paths) != 1 {
		return "", fmt.Errorf("expected one local profile interface, found %d", len(paths))
	}
	return fmt.Sprintf("%s\\%012X", paths[0], value), nil
}

func parseLocalAddress(address string) (uint64, error) {
	compact := strings.ReplaceAll(address, ":", "")
	value, err := strconv.ParseUint(compact, 16, 48)
	if len(compact) != 12 || err != nil || value == 0 {
		return 0, fmt.Errorf("invalid Bluetooth address %q", address)
	}
	return value, nil
}
