package install

import (
	"errors"
	"fmt"
	"os"

	"golang.org/x/sys/windows/registry"

	"sscv2/internal/config"
)

const runKey = `Software\Microsoft\Windows\CurrentVersion\Run`

func AutoStart() (bool, error) {
	key, err := registry.OpenKey(registry.CURRENT_USER, runKey, registry.QUERY_VALUE)
	if errors.Is(err, registry.ErrNotExist) {
		return false, nil
	}
	if err != nil {
		return false, err
	}
	defer key.Close()
	_, _, err = key.GetStringValue(config.AppName)
	if errors.Is(err, registry.ErrNotExist) {
		return false, nil
	}
	return err == nil, err
}

func SetAutoStart(on bool) error {
	if on {
		command, err := autoStartCommand(Exe())
		if err != nil {
			return err
		}
		key, _, err := registry.CreateKey(registry.CURRENT_USER, runKey, registry.SET_VALUE)
		if err != nil {
			return err
		}
		defer key.Close()
		return key.SetStringValue(config.AppName, command)
	}
	key, err := registry.OpenKey(registry.CURRENT_USER, runKey, registry.SET_VALUE)
	if errors.Is(err, registry.ErrNotExist) {
		return nil
	}
	if err != nil {
		return err
	}
	defer key.Close()
	err = key.DeleteValue(config.AppName)
	if errors.Is(err, registry.ErrNotExist) {
		return nil
	}
	return err
}

func autoStartCommand(exe string) (string, error) {
	info, err := os.Stat(exe)
	if err != nil {
		return "", err
	}
	if !info.Mode().IsRegular() {
		return "", fmt.Errorf("autostart executable is not a regular file: %s", exe)
	}
	return `"` + exe + `"`, nil
}
