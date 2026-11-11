# SSCv2

**English** · [Русский](README.ru.md)

SSCv2 streams Windows audio to Bluetooth headphones through a supported MediaTek MT7921, MT7922 or MT7902 adapter. Choose AAC, Samsung Scalable Codec (SSC, 24-bit / 48 kHz), or SSC UHQ (96 kHz) from the tray. A paired Bluetooth mouse can continue working through SSCv2 while the codec is active.

## Install and update

Download `ssc.exe` from [Releases](https://github.com/chesnokovap10/SSCv2/releases) and run it. On first launch, approve the Windows UAC prompt. SSCv2 installs to `C:\Program Files\SSCv2` and creates a desktop shortcut.

To update, run the new `ssc.exe`. The update window shows the installed and incoming builds, including their commit hashes. Choose **Yes** to close the running tray, install the update and resume the selected codec. Choose **No** to keep the current installation running. Windows may ask for administrator approval separately.

Use **Settings → Uninstall…** to return the adapter to Windows and remove the installed program, helper service, shortcut and saved SSCv2 data. For portable debugging, set `SSCV2_PORTABLE=1` before launching.

## Get sound in the headphones

1. Pair the headphones and mouse in Windows.
2. Open the SSCv2 tray menu and select **Pair a device → Import devices paired in Windows**. Choose the headphones and, optionally, the mouse.
3. Select **AAC** or **SSC** under **Codec**. Start with **Auto** under **Bitrate**.
4. Select **Off (Windows Bluetooth)** to return the adapter to Windows. **Exit** also returns it to Windows before the tray closes.

SSCv2 uses the MediaTek adapter in WinUSB mode while a codec is active. Windows Bluetooth devices on that adapter may disappear and reappear during the switch. **Device info…** shows the adapter, codec, actual bitrate, audio source and connection status.

### Volume and mute

- Use the **Headphone volume** slider, its mute button or the keyboard volume keys in codec mode. The scale is **0–127**, with a keyboard step of **4**. The slider stays visible while the stream starts and in **Off** mode.
- SSCv2 sends volume changes to the headphones over AVRCP in both native Bluetooth and WinUSB modes. If the headphones do not confirm the requested level, SSCv2 can apply volume to PCM before encoding. Volume changes made on the headphones are independent of the SSCv2 slider.
- SSCv2 captures the default Windows output through WASAPI loopback and keeps that output muted while it is in use. If Windows unmutes it, SSCv2 reasserts mute. When SSCv2 releases the output, it restores the mute state it took ownership of.
- SSCv2 carries the headphone level and mute between codec mode and Windows when the Windows stereo endpoint is available. On reconnect, Windows may briefly expose the endpoint before SSCv2 can apply the saved level.
- If the headphone link drops during playback, SSCv2 sends Play/Pause and releases the physical output while waiting for the headphones. Headphone media controls are forwarded to Windows.

### Codecs and bitrates

| Codec | Available candidates, kbps |
|---|---|
| AAC | 128, 160, 192, 224, 256 |
| SSC | 88, 96, 128, 192, 229, 256, 328 |
| SSC UHQ | 152, 250, 291, 308, 442, 584, 886 |

The menu filters these candidates by packet size and the known profile of the headphones. **Auto** selects a rate using those limits. The actual rate is shown once streaming starts. Bitrate changes first try to reopen the audio stream on the same Bluetooth connection. A short pause is possible, and the engine can reconnect if reopening fails.

- **Galaxy Buds2 Pro** have a checked SSC limit of **229 kbps**. SSC UHQ is not advertised by this model and may be unavailable in the standard menu.
- **Settings → All bitrates** exposes experimental rates above the checked limit. Rates that do not fit the packet are still filtered.
- **Settings → Max MTU for Samsung Galaxy Buds2 Pro** allows packets up to 1017 bytes for rates such as AAC 256 kbps. Other headphones may drop these larger packets.

### Mouse and Bluetooth

SSCv2 can bridge one paired BLE HID or classic Bluetooth HID mouse, including movement, scrolling and buttons 1–5. Import its pairing from Windows and select it in the tray. A classic mouse may need movement to initiate the connection.

The optional helper service handles driver switching and access to Windows pairing keys. With the service running, routine switches and imports do not require a UAC prompt. The tray and audio engine run separately from the helper.

## Diagnostics and build

Use **Settings → Open the log folder** for `%LOCALAPPDATA%\SSCv2\logs`. Enable **Debug and UI API** for detailed logging and menu commands. Settings and pairing keys are stored in `%APPDATA%\SSCv2`. The helper service log is in `%ProgramData%\SSCv2`.

```bat
ssc.exe status
ssc.exe ctl status
ssc.exe ctl mode aac
ssc.exe ctl bitrate auto
ssc.exe ctl menu
```

The build requires Go 1.27 and MinGW-w64 (`gcc` and `g++` in `PATH`). Switching drivers also requires Windows SDK tools `makecat.exe` and `signtool.exe`.

```bat
build.cmd
go test ./...
```

`build.cmd` builds `bin\ssc.exe` using BTstack, FDK-AAC and [libssc](libssc/README.md) through cgo. The tray menu and **Device info…** display the build version and commit hash.

The executable includes the AVDTP and WaveRT test-mode driver packages. See the [native driver build instructions](driver/README.md) to rebuild and sign them.
