# SSCv2 native Bluetooth drivers

- [`avdtp/`](avdtp/) contains the KMDF sources and the `SscAvdtpLocal.inf` source for the Windows Bluetooth profile.
- [`wavert/`](wavert/) contains the `SscBudsRender` sources and INF for the virtual audio output.
- [`probe/`](probe/) contains the legacy diagnostic INF and test script. The probe uses the AVDTP KMDF sources.
- [`internal/driver/payload/`](../internal/driver/payload/) contains the signed AVDTP and WaveRT packages embedded in `ssc.exe`. Each package includes its INF, SYS and catalog. They share the public certificate `payload/signer.cer`.

## Installing and using the drivers

Install or update SSCv2 from `ssc.exe`. Enable Windows test mode in the SSCv2 settings and restart Windows. The helper stages the embedded AVDTP package and registers its Bluetooth profile. Choosing a codec in test mode registers the embedded WaveRT device on first use and selects it as the audio output. The worker reads PCM through the helper service.

Off stops the worker and restores Windows A2DP. The WaveRT device stays installed for subsequent switches. Disabling the SSCv2 test-mode setting removes both packages, including older versions, and then removes certificate trust entries recorded by the helper.

With the installed tray running in Windows test mode and the Buds paired and selected, run `./tools/test-wavert.ps1 -Codec aac,ssc` to check both modes and return to Off. Pass `-PlaySound` to play a short WAV from the Windows Media directory in each mode.

For a direct PCM diagnostic from an elevated console, pass the WaveRT KS interface path and select the Buds render output in Windows.

```powershell
ssc.exe native-render aac $waveInterface 20
```

## Building and signing driver packages

The standard `build.cmd` uses the signed payloads in the checkout. To rebuild the drivers, use Visual Studio C++ Build Tools, Windows SDK 10.0.26100.0 and WDK 10.0.26100.6584. Set `$wdkRoot` to the WDK directory containing `Include` and `Lib`.

```powershell
git config --local sscv2.wdkRoot "$wdkRoot"
./driver/avdtp/build.ps1 -Package
./driver/wavert/build.ps1 -Package
./driver/avdtp/build.ps1 -Probe -Package
```

The scripts write build artifacts under `bin/driver/<driver-name>/`. With `-Package` they produce an unsigned INF, SYS and CAT in its `package/` subdirectory. Use `-WdkRoot` or `-OutputDirectory` to override the defaults for one build.

To update an embedded package, update `DriverVer` in the source INF and build the package. Use the certificate identified by `payload/signer.cer` in the signing account's Personal store. Sign the SYS, rerun `Inf2Cat` on the package directory, then sign the resulting CAT with the same certificate. Verify both INF and SYS against the signed catalog with `signtool verify /pa /c <catalog> <file>` on a machine that trusts the test certificate. Copy the verified INF, SYS and CAT together into the corresponding payload directory and rebuild `ssc.exe`. When changing the signing certificate, sign both packages and replace the shared public `signer.cer` in the same change. Keep the private key in the signing account's certificate store. The probe is built and signed separately for diagnostic use.

The AVDTP sources are adapted from Microsoft's Bluetooth Echo L2CAP client and the WaveRT sources from SimpleAudioSample, both at Windows-driver-samples revision `d49bb7d72f3651952b2b6e4ad28d14fe2247eb69`. See the included [AVDTP license](avdtp/LICENSE) and [WaveRT license](wavert/LICENSE).

## Legacy AVDTP probe

The probe INF targets the Galaxy Buds2 Pro Stereo A2DP hardware ID. Sign the probe package, trust its test signer on the test machine, and boot Windows in test-signing mode. Build the diagnostic and run it from elevated PowerShell.

```powershell
go build -o bin/avdtp-probe.exe ./cmd/avdtp-probe
./driver/probe/test-probe.ps1 -InfPath $signedInf -ProbePath ./bin/avdtp-probe.exe
```

The script requires exactly one enabled matching stereo device. It temporarily binds the probe driver, queries the AVDTP codecs, removes the package and verifies that Microsoft A2DP is active again.

- `-ConfigureAAC` negotiates AAC and sends a quiet two-second 440 Hz tone.
- `-LoopbackAAC` forwards the test tone through WASAPI loopback. It requires a 48 kHz mono or stereo default output.
- `-UseSSC` lets the script use the main executable as `-ProbePath`. With the probe already bound, `ssc.exe native-aac -stream-aac 10` streams the default output for ten seconds.

To exercise the legacy helper commands, an administrator can provision the signed probe INF, SYS and CAT in `%ProgramFiles%\SSCv2\native-bt`. Run `ssc.exe native-stereo bind` to bind the sole supported stereo device and `ssc.exe native-stereo restore` to return it to Microsoft A2DP.
