package install

import (
	"errors"

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
		key, _, err := registry.CreateKey(registry.CURRENT_USER, runKey, registry.SET_VALUE)
		if err != nil {
			return err
		}
		defer key.Close()
		return key.SetStringValue(config.AppName, `"`+Exe()+`"`)
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
