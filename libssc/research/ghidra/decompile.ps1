# Decompile libssc/ref/libScalable_Encoder.so with Ghidra (headless) into research/decomp/.
# Tools are portable in D:\2\tools (JDK 21 + Ghidra 12.1.4); override with -Tools.
param(
    [string]$Tools = "D:\2\tools",
    [string]$Out = (Join-Path $PSScriptRoot "..\decomp")
)
$ErrorActionPreference = "Stop"
$jdk = Get-ChildItem $Tools -Directory -Filter "jdk-21*" | Select-Object -First 1
$ghidra = Get-ChildItem $Tools -Directory -Filter "ghidra_*_PUBLIC" | Select-Object -First 1
if (-not $jdk -or -not $ghidra) { throw "JDK 21 or Ghidra not found in $Tools" }
$env:JAVA_HOME = $jdk.FullName
$env:PATH = "$($jdk.FullName)\bin;$env:PATH"

$blob = Resolve-Path (Join-Path $PSScriptRoot "..\..\ref\libScalable_Encoder.so")
$proj = Join-Path $env:TEMP "libssc_ghidra"
New-Item -ItemType Directory -Force $proj | Out-Null
$Out = [System.IO.Path]::GetFullPath($Out)

& (Join-Path $ghidra.FullName "support\analyzeHeadless.bat") $proj libssc `
    -import $blob -overwrite `
    -scriptPath $PSScriptRoot -postScript DecompileAll.java $Out `
    -deleteProject
