param(
    [string] $WdkRoot,
    [string] $OutputDirectory,
    [switch] $Package,
    [switch] $Probe,
    [string] $SdkRoot = "${env:ProgramFiles(x86)}\Windows Kits\10",
    [string] $SdkVersion = '10.0.26100.0'
)

$ErrorActionPreference = 'Stop'
$source = $PSScriptRoot
$driverName = 'SscAvdtpLocal'
$defines = @('/DSSC_LOCAL_PROFILE')
$infRoot = $source
if ($Probe) {
    $driverName = 'SscAvdtpProbe'
    $defines = @()
    $infRoot = Join-Path $source '..\probe'
}
if (!$OutputDirectory) {
    $OutputDirectory = Join-Path $source "..\..\bin\driver\$driverName"
}
if (!$WdkRoot) {
    $WdkRoot = git -C $PSScriptRoot config --local --get sscv2.wdkRoot
    if ($LASTEXITCODE -ne 0 -or !$WdkRoot) {
        throw 'Set sscv2.wdkRoot in the local Git config or pass -WdkRoot.'
    }
}
$wdk = (Resolve-Path -LiteralPath $WdkRoot).Path
$output = (New-Item -ItemType Directory -Force -Path $OutputDirectory).FullName
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vs = & $vswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (!$vs) { throw 'Visual Studio x64 C++ Build Tools were not found.' }
$version = (Get-Content "$vs\VC\Auxiliary\Build\Microsoft.VCToolsVersion.default.txt" -Raw).Trim()
$tools = "$vs\VC\Tools\MSVC\$version\bin\Hostx64\x64"

$includes = @(
    "$vs\VC\Tools\MSVC\$version\include",
    "$wdk\Include\$SdkVersion\km",
    "$wdk\Include\wdf\kmdf\1.31",
    "$SdkRoot\Include\$SdkVersion\shared",
    "$SdkRoot\Include\$SdkVersion\um",
    "$SdkRoot\Include\$SdkVersion\ucrt",
    "$source\common\inc",
    "$source\bthcli\sys"
) | ForEach-Object { "/I$_" }

Push-Location -LiteralPath $output
try {
    $sources = @(
        "$source\bthcli\sys\device.c",
        "$source\bthcli\sys\driver.c",
        "$source\bthcli\sys\queue.c",
        "$source\bthcli\sys\client.c",
        "$source\common\lib\clisrv.c",
        "$source\common\lib\connection.c"
    )
    & "$tools\cl.exe" /nologo /c /O2 /kernel /Zl /D_AMD64_ /D_WIN64 /DWINVER=0x0A00 /D_WIN32_WINNT=0x0A00 /DNTDDI_VERSION=0x0A000008 /DALLOC_PRAGMA /DKMDF_VERSION_MAJOR=1 /DKMDF_VERSION_MINOR=31 $defines $includes $sources
    if ($LASTEXITCODE) { throw "Driver compilation failed ($LASTEXITCODE)." }

    & "$tools\link.exe" /nologo /kernel /driver /subsystem:native /entry:FxDriverEntry /nodefaultlib "/out:$driverName.sys" device.obj driver.obj queue.obj client.obj clisrv.obj connection.obj "/libpath:$wdk\Lib\$SdkVersion\km\x64" "/libpath:$wdk\Lib\wdf\kmdf\x64\1.31" ntoskrnl.lib hal.lib wdfdriverentry.lib wdfldr.lib bufferoverflowfastfailk.lib
    if ($LASTEXITCODE) { throw "Driver link failed ($LASTEXITCODE)." }
} finally {
    Pop-Location
}
if ($Package) {
    $packageDirectory = (New-Item -ItemType Directory -Force -Path (Join-Path $output 'package')).FullName
    $inf = Join-Path $infRoot "$driverName.inf"
    $binary = Join-Path $output "$driverName.sys"
    Copy-Item -LiteralPath $inf, $binary -Destination $packageDirectory -Force
    & "$wdk\bin\$SdkVersion\x86\Inf2Cat.exe" "/driver:$packageDirectory" /os:10_VB_X64,10_GE_X64
    if ($LASTEXITCODE) { throw "Driver catalog generation failed ($LASTEXITCODE)." }
}
