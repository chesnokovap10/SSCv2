# SSCv2 native Bluetooth probe

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
./driver/native-bt/test-probe.ps1 -InfPath $signedInf -ProbePath $probeExe
```

The script requires exactly one enabled matching stereo device. It temporarily
switches its driver, queries the AVDTP codecs, removes the test package, and
checks that the original Microsoft A2DP driver is active again.

Pass -ConfigureAAC to negotiate AAC, open a separate media channel, and send a quiet two-second 440 Hz test tone. Confirm playback by listening on the Buds.
