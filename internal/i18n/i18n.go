// Package i18n picks the user-visible language (Russian or English).
// Every message is written in place as T("по-русски", "in English"), so the
// text stays next to the code that shows it.
package i18n

import (
	"sync/atomic"

	"golang.org/x/sys/windows"
)

const (
	RU = "ru"
	EN = "en"
)

var english atomic.Bool

func init() { Set(System()) }

// System is the Windows UI language: "ru" for Russian, otherwise "en".
func System() string {
	p := windows.NewLazySystemDLL("kernel32.dll").NewProc("GetUserDefaultUILanguage")
	if r, _, _ := p.Call(); r&0x3FF == 0x19 { // LANG_RUSSIAN
		return RU
	}
	return EN
}

// Set switches the language ("ru" | "en"; "" = Windows UI language).
func Set(lang string) {
	if lang == "" {
		lang = System()
	}
	english.Store(lang != RU)
}

// Lang is the current language code.
func Lang() string {
	if english.Load() {
		return EN
	}
	return RU
}

// T returns the text in the current language.
func T(ru, en string) string {
	if english.Load() {
		return en
	}
	return ru
}

// msgErr is an error whose text follows the current language (for package
// level error values, created before the language is known).
type msgErr struct{ ru, en string }

func (e *msgErr) Error() string { return T(e.ru, e.en) }

// Error makes such an error; compare it with errors.Is as usual.
func Error(ru, en string) error { return &msgErr{ru, en} }
