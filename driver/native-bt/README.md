# SSCv2 native Bluetooth drivers

- `src/` contains shared KMDF sources for both driver builds.
- `SscAvdtpLocal.inf` is the source INF for the tray's experimental Bluetooth route.
- `local-package/` holds the signed driver and public certificate embedded in the SSCv2 executable.
- `diagnostics/` contains the legacy probe INF, unsigned development binary, and test script.

## Tray driver

`SscAvdtpLocal` is the shared driver for AAC (192 kbit/s) and SSC
(24-bit, 48 kHz, 128 kbit/s) in Windows test mode. The tray reads 48 kHz PCM from the Buds WaveRT output. Enable Windows test mode in the tray settings and restart. The helper
installs the embedded package and registers the Bluetooth profile after
Windows boots in test mode. Clearing the setting stops the native stream,
restores Windows A2DP, and removes the driver package. The helper removes
certificate trust entries it added and leaves pre-existing entries in place.

Use the build script with `-LocalProfile -Package` to generate a fresh
unsigned package under the chosen output directory's `local-package/`.
Build into a separate output directory to preserve an existing signed package.

## Buds stereo render driver prototype

`src/render` contains the complete WaveRT driver sources and INF, adapted
from Microsoft's SimpleAudioSample at Windows-driver-samples revision
`d49bb7d72f3651952b2b6e4ad28d14fe2247eb69` under the included MS-PL.
Run `./driver/native-bt/build-render.ps1 -Package` from the repository root.
The package goes to `bin/SscBudsRender/package` by default.

`-Package` generates an unsigned INF, SYS and catalog. The INF creates a separate root-enumerated WaveRT render device. The render filter exposes a bounded
PCM queue through a diagnostic KS property restricted to administrators.

On a test system with the signed WaveRT device installed and
the local AVDTP profile active, run the following command from an elevated
console. Pass the render filter's KS device interface path. SSCv2 uses the
Buds address from its settings and requires its Windows test-mode option.

```powershell
ssc.exe native-render aac $waveInterface 20
```

Select the Buds render output in Windows and play audio during the diagnostic.
Use `ssc` to select the SSC encoder.

For tray use, provision the test-signed INF, SYS and CAT in
`%ProgramFiles%\SSCv2\native-bt` and trust the test signer on the machine.
Update both the tray and its helper service to the same build. Run SSCv2 as
administrator to access the restricted PCM property. Choosing a codec in
test mode registers the WaveRT device on first use, selects its output and
releases the configured Buds A2DP session to the worker. Off stops the worker,
restores the Windows A2DP service and returns the previous audio output. The
WaveRT device stays installed for subsequent switches.

## Legacy diagnostic probe

This experimental x64 KMDF 1.31 driver targets Windows 10 version 2004 and later, including Windows 11. It opens AVDTP signaling (L2CAP PSM 0x0019) on
the remote device identified by its Bluetooth service devnode. The unsigned
`SscAvdtpProbe.sys` is a build artifact for development. Installation and hardware testing are pending.

Build from the repository root with Visual Studio C++ Build Tools, Windows
SDK 10.0.26100.0 and WDK 10.0.26100.6584:

```powershell
git config --local sscv2.wdkRoot "$wdkRoot"
./driver/native-bt/build-probe.ps1 -OutputDirectory "$env:TEMP\sscv2-native-probe"
```

Set `$wdkRoot` to the WDK directory containing `Include` and `Lib` before running the setup command. The setting is local to this Git checkout. Pass `-WdkRoot` to override it for one build.

The sources are adapted from Microsoft's Bluetooth Echo L2CAP client at
[Windows-driver-samples d49bb7d](https://github.com/microsoft/Windows-driver-samples/tree/d49bb7d72f3651952b2b6e4ad28d14fe2247eb69/bluetooth/bthecho)
and distributed under the [Microsoft Public License](LICENSE).

Add `-Package` to build the INF, SYS and unsigned catalog into the output
directory's `package` subdirectory. The INF matches the Samsung Buds2 Pro
Stereo A2DP hardware ID. It can match multiple paired units of that model.

For a hardware trial, sign the SYS and catalog with a test certificate trusted
by the test machine and boot Windows into test-signing mode. With the Go CGO C/C++ toolchain enabled, build the probe with
`go build -o avdtp-probe.exe ./cmd/avdtp-probe`, then run from an elevated
PowerShell with the signed package and probe executable:

```powershell
./driver/native-bt/diagnostics/test-probe.ps1 -InfPath $signedInf -ProbePath $probeExe
```

The script requires exactly one enabled matching stereo device. It temporarily
switches its driver, queries the AVDTP codecs, removes the test package, and
checks that the original Microsoft A2DP driver is active again.

Pass -ConfigureAAC to negotiate AAC, open a separate media channel, and send a quiet two-second 440 Hz test tone. Confirm playback by listening on the Buds.

Use -LoopbackAAC to render the test tone through the default Windows output and stream the WASAPI loopback capture to the Buds. This diagnostic requires a 48 kHz mono or stereo default output.

The same diagnostic is available in the main executable. Pass -UseSSC to
test-probe.ps1 and point -ProbePath at the built SSCv2 executable. With the
driver already bound, the executable finds its active interface and can also
forward default-output loopback for a bounded interval without rendering a
test tone:

```powershell
ssc.exe native-aac -stream-aac 10
```

For testing the privileged helper, an administrator can provision the signed
INF, SYS and CAT under the SSCv2 installation directory in its native-bt
subfolder. Use ssc.exe native-stereo bind to switch the sole supported stereo
devnode, and ssc.exe native-stereo restore to remove the test binding and
verify that Microsoft A2DP is back. The helper accepts no package path from
the caller. These commands belong to the legacy probe workflow.
