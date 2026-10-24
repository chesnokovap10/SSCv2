# Decompile the SSC parts of libssc/ref/libbluetooth_jni.so (the phone's BT stack,
# stripped) with Ghidra headless into research/decomp_bt/. Full analysis of the
# 16 MB library takes a while; the project is kept in %TEMP%\libssc_ghidra_bt so a
# rerun with -Reuse skips it.
param(
    [string]$Tools = "D:\2\tools",
    [string]$Out = (Join-Path $PSScriptRoot "..\decomp_bt"),
    [switch]$Reuse
)
$ErrorActionPreference = "Stop"
$jdk = Get-ChildItem $Tools -Directory -Filter "jdk-21*" | Select-Object -First 1
$ghidra = Get-ChildItem $Tools -Directory -Filter "ghidra_*_PUBLIC" | Select-Object -First 1
if (-not $jdk -or -not $ghidra) { throw "JDK 21 or Ghidra not found in $Tools" }
$env:JAVA_HOME = $jdk.FullName
$env:PATH = "$($jdk.FullName)\bin;$env:PATH"

$lib = Resolve-Path (Join-Path $PSScriptRoot "..\..\ref\libbluetooth_jni.so")
$proj = Join-Path $env:TEMP "libssc_ghidra_bt"
New-Item -ItemType Directory -Force $proj | Out-Null
$Out = [System.IO.Path]::GetFullPath($Out)
$hl = Join-Path $ghidra.FullName "support\analyzeHeadless.bat"

if ($Reuse) {
    & $hl $proj bt -process libbluetooth_jni.so -noanalysis `
        -scriptPath $PSScriptRoot -postScript DecompileSsc.java $Out
} else {
    & $hl $proj bt -import $lib -overwrite -max-cpu 8 `
        -scriptPath $PSScriptRoot -postScript DecompileSsc.java $Out
}
