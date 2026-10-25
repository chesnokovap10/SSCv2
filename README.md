# SSCv2

**English** · [Русский](README.ru.md)

A Windows tray program that streams audio to Samsung Galaxy Buds over the laptop's
**built-in MediaTek MT79xx Bluetooth** (MT7921/MT7922/MT7902), bypassing the Windows stack,
with **AAC**, **SSC** (Samsung Scalable Codec, 24 bit / 48 kHz) or **SSC UHQ** (96 kHz) —
while a **BLE mouse** keeps working. There is no main window: just an icon and a right-click
menu.

Version: `0.1 #<commit hash>` (e.g. `0.1 #67cd8794`), shown in the menu and in "Device info".

## Install and update

Run `ssc.exe` from any folder. On the first run it (after a UAC prompt) copies itself to
`C:\Program Files\SSCv2`, puts an **SSCv2** shortcut on the desktop and starts from there.
If the program is already installed and a different file is started, the installed copy is
**updated**: the running tray gives Bluetooth back to Windows and quits, the file is replaced
and the new tray resumes the same codec. Nothing is added to "Apps & features".

`SSCV2_PORTABLE=1` runs without installing (for debugging).

**Uninstall:** "Settings → Uninstall…". Bluetooth goes back to Windows; the service, the
virtual headphones, `Program Files\SSCv2`, `%ProgramData%\SSCv2`, settings, pairing keys, logs
and the shortcut are removed. The file the program was installed from stays.

## Menu

| Item | What it does |
|---|---|
| **Codec ▸** Off / AAC / SSC / SSC UHQ | "Off": the adapter belongs to the Windows driver (BTHUSB), headphones and mouse work as usual. Otherwise: adapter in WinUSB, MT79xx firmware, BTstack, the headphones on the chosen codec, mouse bridge. |
| **Bitrate ▸** | The list for the current codec; "Auto" — see below. |
| Pair a device ▸ | Import keys from Windows, search nearby (codec on), choose headphones and mouse. |
| Device info… | Adapter, chip/firmware, headphones (codec, bitrate, volume), mouse, service. Same text on a left click on the icon. |
| **Settings ▸** Language | Русский / English (default: the Windows language). |
| Settings ▸ Max MTU for Galaxy Buds2 Pro | Packets of up to 1017 bytes instead of the 679 the headphones announce: AAC 256 kbps in whole frames. Buds2 Pro play them cleanly; other headphones may drop them — hence an option. |
| Settings ▸ Debug journal | Detailed shared journal of all processes (`debug.log`, see below). |
| Settings ▸ Open the log folder | `%LOCALAPPDATA%\SSCv2\logs`. |
| Settings ▸ Start / Remove the service | Helper service (LocalSystem): with it, switching and key import need no UAC prompts. |
| Settings ▸ Uninstall… | Full removal (see above). |

Icon colour: grey — off, amber — switching/connecting, blue — waiting for the headphones,
green — streaming, red — error.

### Codecs and bitrates

| Codec | Bitrates, kbps | "Auto" |
|---|---|---|
| AAC | 128, 160, 192, 224, 256 | as much as the headphones' packet holds: `(MTU − 12) × 8 × rate / 1024`, at most 256 (Buds2 Pro: 250 at 48 kHz; 256 with "Max MTU") |
| SSC | 88, 96, 128, 192, 229, 256, 328 | like the phone: 192 (128 if the headphones announce a limit); with "Max MTU" — 229, the best on Buds2 Pro |
| SSC UHQ | 152, 250, 291, 308, 442, 584, 886 | the highest one packet holds (584; 886 with "Max MTU") |

* SSC is our `libssc`, a bit-exact twin of the encoder in the phone firmware. Windows output
  must run at 48000 Hz. On Buds2 Pro 256 and 328 sound bad (the "wide" modes the phone never
  uses at 48 kHz) — 229 is the practical maximum.
* SSC UHQ: the 48 kHz capture is upsampled 2× to 96 kHz, 9 ms frames. Buds2 Pro accept it
  although they do not announce it.
* Bitrates whose frames do not fit the headphones' packet (AAC 256, SSC 328, UHQ 886) are
  offered only with "Max MTU". The SSC configuration byte (`ctl ssccap`) is not saved — it lasts
  until the tray restarts.

### Buttons and volume

* Taps on the headphones → Windows media keys: single — play/pause, double — next track,
  triple — restart / previous track (the player decides). The headphones are told whether
  something plays, so a tap sends the right command.
* Windows volume ⇄ headphone volume (AVRCP), both ways.
* **Mute** in Windows (key, mixer) silences the stream to the headphones.
* When the link is lost (headphones in the case) playback is paused and the sound goes back
  to the speakers until the headphones return.

## How it works

One `ssc.exe`, several roles:

```
ssc.exe            tray (user)  ── stdin/stdout JSON ──►  ssc.exe engine (user)
   │                                                       MT79xx firmware (WinUSB)
   │ \\.\pipe\SSCv2Helper (SYSTEM, admins, owner)          BTstack: A2DP/AVDTP/AVRCP, LE HID
   ▼                                                       WASAPI → AAC (FDK) / SSC (libssc) → RTP
ssc.exe service (LocalSystem)                              volume ⇄ AVRCP, buttons, mouse
   driver switch, registry keys, VB-CABLE
```

* **The engine is a separate process** per session: fresh BTstack state, a crash in C code
  does not take the tray down; the tray restarts the engine and undoes its audio changes.
* **The service** is only for privileged work: the driver switch (a temporary certificate per
  switch), reading `BTHPORT\Parameters\Keys` (SYSTEM only), writing a new key back to
  Windows, installing VB-CABLE. Without the service a UAC-elevated copy of `ssc.exe` does the
  same. The service runs from `Program Files\SSCv2`.
* **Keys.** Pair headphones and mouse in Windows, then "Import devices paired in Windows"
  copies the keys — same controller address, no re-pairing, Windows keeps working with them.
  Headphones paired while a codec is on get their new key written to the Windows registry
  too (with the service running).
* **Virtual headphones.** The VB-CABLE driver (VB-Audio, Microsoft-signed) is embedded in
  `ssc.exe` (`internal/vbcable/files`). When a codec is switched on the program installs the
  device, names it after the chosen headphones and makes it the default output — its slider
  controls the headphones. It is removed with the service or the program.

### Why the driver is switched "in place"

The adapter is switched by disabling the device → adding/removing the WinUSB package →
enabling it (`pnputil /disable-device`, `/add-driver /install` or `/delete-driver
/uninstall`, `/enable-device`). Removing the node (`/remove-device /subtree`) is not an option:
it deletes the Bluetooth registry entries, and after every switch back Windows saw the
headphones as a *new* device (100 % volume, audio jumping, ghost devices). The old way remains
as a fallback, used automatically when Windows refuses to stop the adapter.

### Go and C

Everything of our own is Go: the driver switch (SetupAPI), the MT79xx firmware loader
(WinUSB), WASAPI/volume/IPolicyConfig (raw COM), the BT logic (events, A2DP, AVRCP, mouse
bridge), the service, the tray, installation. The C/C++ libraries build through cgo with
plain `go build` (no CMake): **BTstack** (`third_party/btstack`), **FDK-AAC**
(`third_party/fdk-aac`) and our **libssc** (`libssc/src`). `tools/genwrap` writes one wrapper
per source (`internal/bt/zbt_*.c`, `internal/codec/aac/zfdk_*.cpp`,
`internal/codec/ssc/zssc_*.c`).

| Package | Purpose |
|---|---|
| `cmd/ssc` | entry point, process roles, icon |
| `internal/app` | tray: menu, codecs, install/uninstall, `ctl` commands |
| `internal/engine` | streaming process: capture → codec → BT, reconnects, buttons, mute |
| `internal/bt` | BTstack: bring-up, A2DP source (AAC/SSC), AVRCP, inquiry, BLE mouse bridge |
| `internal/codec/aac`, `internal/codec/ssc` | AAC-LC (LATM like Android), SSC through libssc |
| `internal/audio` | WASAPI capture, volume and mute, virtual headphones |
| `internal/driver`, `internal/mtk` | WinUSB ↔ BTHUSB, MT79xx RAM firmware (from DriverStore `mtkbt*`) |
| `internal/helper` | service, pipe, privileged operations, UAC |
| `internal/install` | Program Files, shortcut, uninstall |
| `internal/keys`, `internal/vbcable` | keys (keys.json, Windows registry), embedded VB-CABLE driver |
| `internal/i18n`, `internal/config`, `internal/logx`, `internal/tray` | languages, settings, logs, icon |
| `libssc/` | our SSC implementation: [README](libssc/README.md), [plan](libssc/PLAN.md) |

## Build

Needs Go 1.24+ and MinGW-w64 (gcc/g++) in `PATH`.

```bat
build.cmd
```

The result is `bin\ssc.exe` with version `0.1 #<hash>` from git. The first build compiles
BTstack, FDK-AAC and libssc (~1–2 min), later builds are cached. Switching to WinUSB needs the
Windows 10+ SDK (`makecat.exe`, `signtool.exe`).

```bat
go test ./...
```

## Files

* `%APPDATA%\SSCv2\settings.json` — codec, bitrates, language, "Max MTU", headphones/mouse,
  debug. Every load and save is logged in `tray.log` (with the caller).
* `%APPDATA%\SSCv2\keys.json` — pairing keys (secrets, this user only).
* `%LOCALAPPDATA%\SSCv2\logs\` — `tray.log`, `engine.log`, `engine-c.log`, `helper.log`,
  `debug.log`; the service log is `%ProgramData%\SSCv2\service.log`.

## Command line

```bat
ssc.exe status
ssc.exe ctl status | info | version | log [debug|tray|engine|helper] [N]
ssc.exe ctl mode off|aac|ssc|ssc_uhq | bitrate auto|<kbps> | maxmtu on|off | lang ru|en
ssc.exe ctl debug on|off | import windows | service install|remove | scan | connect <addr>
ssc.exe ctl quit | uninstall
```

Diagnostics: `ctl aac frag` (AAC 256 frames split over two RFC 3016 packets — Buds2 Pro do not
reassemble them), `ctl ssccap auto|<hex>` (SSC configuration byte), `SSCV2_SSC_SHIFT=1..8`
(feed the SSC encoder extra headroom bits).

### Debug journal

Switched on in "Settings", with `ssc.exe ctl debug on` or `SSCV2_DEBUG=1`. The tray, engine
and service write to one time-ordered file, `%LOCALAPPDATA%\SSCv2\logs\debug.log`; each line
has a category (`findstr " vol:" debug.log`):

| Category | Content |
|---|---|
| `mode`, `ui`, `helper` | switches, menu items, service requests and the driver switch script log |
| `dev`, `vol` | audio device events and every volume/mute change — with its origin |
| `hci`, `l2cap`, `sdp` | HCI commands and events, L2CAP channels |
| `avdtp`, `avrcp` | A2DP signalling, AVRCP (volume, headphone buttons) |
| `att`, `smp` | BLE mouse: GATT and pairing |
| `media` | every 5 s — summary of audio packets, mouse reports and advertising |

Pairing keys (link key, LTK) are masked. The file rotates at 64 MB.

## Licences

BTstack — BlueKitchen licence (non-commercial use only), FDK-AAC — Fraunhofer licence, Opus
(in libssc) — BSD; texts in `third_party/*` and `libssc/src/opus/COPYING`. VB-CABLE is
donationware by VB-Audio: free for personal use, redistribution inside another program only
with their permission. libssc and SSC — personal use only.
