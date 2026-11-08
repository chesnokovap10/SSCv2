# SSCv2 native Bluetooth probe

This experimental x64 KMDF driver opens AVDTP signaling (L2CAP PSM 0x0019) on
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

For the first hardware trial, sign the catalog with a test certificate trusted
by the test machine and boot into Windows test-signing mode. Record the selected
Stereo devnode's instance ID and its current driver. Stage the signed package
without `/install`, then select the probe INF via Device Manager's Have Disk
action on that specific Stereo devnode. The probe interface GUID is
`{105bdfd9-73ce-4bcf-b2e9-c5d611f69a23}`. Open its device path with
`avdtp-probe.exe`, then verify the Bluetooth mouse remains responsive.

To restore stereo audio, close the probe and switch the same devnode back to
its original Microsoft A2DP driver in Device Manager. Verify stereo playback,
then remove the staged probe package by its published `oem*.inf` name using
`pnputil /delete-driver` without forcing removal.
