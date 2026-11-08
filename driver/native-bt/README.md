# SSCv2 native Bluetooth probe

This experimental x64 KMDF driver opens AVDTP signaling (L2CAP PSM 0x0019) on
the remote device identified by its Bluetooth service devnode. The unsigned
`SscAvdtpProbe.sys` is a build artifact for development. Device binding,
installation and testing on the Buds2 Pro are pending.

Build from the repository root with Visual Studio C++ Build Tools, Windows
SDK 10.0.26100.0 and WDK 10.0.26100.6584:

```powershell
./driver/native-bt/build-probe.ps1 -WdkRoot $wdkRoot -OutputDirectory "$env:TEMP\sscv2-native-probe"
```

Set $wdkRoot to the WDK directory containing Include and Lib. The build uses the checked-in sources in src.

The sources are adapted from Microsoft's Bluetooth Echo L2CAP client at
[Windows-driver-samples d49bb7d](https://github.com/microsoft/Windows-driver-samples/tree/d49bb7d72f3651952b2b6e4ad28d14fe2247eb69/bluetooth/bthecho)
and distributed under the [Microsoft Public License](LICENSE).
