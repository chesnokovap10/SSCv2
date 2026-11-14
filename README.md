# SSCv2

**English** · [Русский](README.ru.md)

SSCv2 streams Windows audio to Bluetooth headphones through a supported MediaTek MT7921, MT7922 or MT7902 adapter. Choose AAC, Samsung Scalable Codec (SSC, 24-bit / 48 kHz), or SSC UHQ (96 kHz) from the tray. SSCv2 can run through WinUSB or use the Windows Bluetooth stack in Windows test mode.

## Install and update

Download `ssc.exe` from [Releases](https://github.com/chesnokovap10/SSCv2/releases) and run it. On first launch, approve the Windows UAC prompt. SSCv2 installs to `C:\Program Files\SSCv2` and creates a desktop shortcut.

To update, run the new `ssc.exe`. The update window shows the installed and incoming builds, including their commit hashes. Choose **Yes** to close the running tray, install the update and resume the selected codec. Choose **No** to keep the current installation running. Windows may ask for administrator approval separately.

For unattended updates of an existing installation, run the new `ssc.exe --update` from an elevated terminal. This command expects administrator rights before it starts.

Use **Settings → Uninstall…** to return the adapter to Windows and remove the installed program, helper service, shortcut and saved SSCv2 data. For portable debugging, set `SSCV2_PORTABLE=1` before launching.

## Get sound in the headphones

1. Pair the headphones in Windows. Pair a mouse too if you plan to use it with WinUSB.
2. Open the SSCv2 tray menu and select **Pair a device → Import devices paired in Windows**. Choose the headphones and, for WinUSB, the mouse if needed.
3. Select **AAC** or **SSC** under **Codec**. Start with **Auto** under **Bitrate**.
4. Select **Off (Windows Bluetooth)** to return the adapter to Windows. **Exit** also returns it to Windows before the tray closes.

### Bluetooth modes

- **WinUSB** is the default. SSCv2 uses built-in Windows tools to install the adapter driver and captures the Windows output via WASAPI loopback. Bluetooth devices on that adapter may disappear from Windows until you choose **Off**. The SSCv2 mouse bridge is available in this mode.
- **Windows test mode** keeps the adapter on the Windows Bluetooth stack. The release includes the signed AVDTP and WaveRT driver packages, so `ssc.exe` supplies the drivers for this mode. Other Bluetooth devices, including the mouse, stay under Windows control. Enable **Settings → Windows test mode…**, then restart Windows. Windows test signing applies to the whole computer. [Driver details](driver/README.md)

**Device info…** shows the adapter, codec, actual bitrate, audio source and connection status.

### Volume and mute

- Use the **Headphone volume** slider, its mute button or the keyboard volume keys in codec mode. The scale is **0–127**, with a keyboard step of **4**. The slider stays visible while the stream starts and in **Off** mode.
- SSCv2 sends volume changes to the headphones over AVRCP in both native Bluetooth and WinUSB modes. If the headphones do not confirm the requested level, SSCv2 can apply volume to PCM before encoding. Volume changes made on the headphones are independent of the SSCv2 slider.
- In WinUSB mode, SSCv2 mutes the output it captures via WASAPI loopback and restores the mute state when it releases the output.
- SSCv2 carries the headphone level and mute between codec mode and Windows when the Windows stereo endpoint is available. On reconnect, Windows may briefly expose the endpoint before SSCv2 can apply the saved level.
- SSCv2 forwards headset media controls to Windows, including an AVRCP Pause command when the headphones send one. If the link drops during playback, SSCv2 can pause the player and wait for the headphones to reconnect in the selected mode.

### Codecs and bitrates

| Codec | Available candidates, kbps |
|---|---|
| AAC | 128, 160, 192, 224, 256 |
| SSC | 88, 96, 128, 192, 229, 256, 328 |
| SSC UHQ | 152, 250, 291, 308, 442, 584, 886 |

The menu filters candidates by packet size and the known headphone profile. **Auto** chooses the rate at startup. For AAC, Windows test mode uses **224 kbps** and WinUSB uses up to **256 kbps** within its packet budget. The actual rate is shown once streaming starts.

If AAC, SSC or SSC UHQ fails to start with a manual bitrate, SSCv2 keeps that mode and bitrate selected and shows the error in the tray. Choose another bitrate to try again or select **Off** to restore Windows Bluetooth audio.

- **Galaxy Buds2 Pro** have a checked SSC limit of **229 kbps**. SSC UHQ is not advertised by this model and may be unavailable in the standard menu.
- **Settings → Show all bitrates** exposes experimental rates and allows an SSC UHQ attempt on a headset that advertises SSC alone. The headset and transport still determine whether the stream starts.
- **Settings → Max MTU for Samsung Galaxy Buds2 Pro** allows packets up to 1017 bytes in WinUSB mode. In Windows test mode, **Show all bitrates** exposes the larger-packet candidates, which may fail when the driver sends the first packet.

### Mouse and Bluetooth

In WinUSB mode, SSCv2 can bridge one paired BLE HID or classic Bluetooth HID mouse, including movement, scrolling and buttons 1–5. Import its pairing from Windows and select it in the tray. A classic mouse may need movement to initiate the connection.

The helper service handles privileged driver operations and access to Windows pairing keys. Windows test mode requires the service. With the service running, routine switches and imports run without a UAC prompt. The tray and audio worker run separately from the helper.

## Diagnostics and build

Use **Settings → Open the log folder** for `%LOCALAPPDATA%\SSCv2\logs`. Enable **Debug and UI API** for detailed logging and menu commands. Settings and pairing keys are stored in `%APPDATA%\SSCv2`. The helper service log is in `%ProgramData%\SSCv2`.

```bat
ssc.exe status
ssc.exe ctl status
ssc.exe ctl mode aac
ssc.exe ctl bitrate auto
ssc.exe ctl menu
```

The build requires Go 1.27 and MinGW-w64 (`gcc` and `g++` in `PATH`).

```bat
build.cmd
go test ./...
```

`build.cmd` builds `bin\ssc.exe` using BTstack, FDK-AAC and [libssc](libssc/README.md) through cgo. The tray menu and **Device info…** display the build version and commit hash.

Run `go run ./tools/genwrap` after changing the list of C or C++ sources. The build checks the generated cgo wrappers with `go run ./tools/genwrap -check`. The application links the SSC encoder from `libssc/src`. The decoder, test bench and reverse-engineering tools are used by the libssc tests and research.

The executable includes the AVDTP and WaveRT test-mode driver packages. See the [native driver build instructions](driver/README.md) to rebuild and sign them.
