param(
    [string] $WdkRoot,
    [Parameter(Mandatory)] [string] $OutputDirectory,
    [switch] $Package,
    [string] $SdkRoot = "${env:ProgramFiles(x86)}\Windows Kits\10",
    [string] $SdkVersion = '10.0.26100.0'
)

$ErrorActionPreference = 'Stop'
$sample = Join-Path $PSScriptRoot 'src'
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
    "$wdk\Include\wdf\kmdf\1.33",
    "$SdkRoot\Include\$SdkVersion\shared",
    "$SdkRoot\Include\$SdkVersion\um",
    "$SdkRoot\Include\$SdkVersion\ucrt",
    "$sample\common\inc",
    "$sample\bthcli\sys"
) | ForEach-Object { "/I$_" }

Push-Location -LiteralPath $output
try {
    $sources = @(
        "$sample\bthcli\sys\device.c",
        "$sample\bthcli\sys\driver.c",
        "$sample\bthcli\sys\queue.c",
        "$sample\bthcli\sys\client.c",
        "$sample\common\lib\clisrv.c",
        "$sample\common\lib\connection.c"
    )
    & "$tools\cl.exe" /nologo /c /O2 /kernel /Zl /D_AMD64_ /D_WIN64 /DWINVER=0x0A00 /D_WIN32_WINNT=0x0A00 /DNTDDI_VERSION=0x0A00000C /DALLOC_PRAGMA $includes $sources
    if ($LASTEXITCODE) { throw "Driver compilation failed ($LASTEXITCODE)." }

    & "$tools\link.exe" /nologo /kernel /driver /subsystem:native /entry:FxDriverEntry /nodefaultlib /out:SscAvdtpProbe.sys device.obj driver.obj queue.obj client.obj clisrv.obj connection.obj "/libpath:$wdk\Lib\$SdkVersion\km\x64" "/libpath:$wdk\Lib\wdf\kmdf\x64\1.33" ntoskrnl.lib hal.lib wdfdriverentry.lib wdfldr.lib bufferoverflowfastfailk.lib
    if ($LASTEXITCODE) { throw "Driver link failed ($LASTEXITCODE)." }
} finally {
    Pop-Location
}





if ($Package) {
    $packageDirectory = (New-Item -ItemType Directory -Force -Path (Join-Path $output 'package')).FullName
    $inf = Join-Path $PSScriptRoot 'SscAvdtpProbe.inf'
    $binary = Join-Path $output 'SscAvdtpProbe.sys'
    Copy-Item -LiteralPath $inf, $binary -Destination $packageDirectory -Force
    & "$wdk\bin\$SdkVersion\x86\Inf2Cat.exe" "/driver:$packageDirectory" /os:10_GE_X64
    if ($LASTEXITCODE) { throw "Driver catalog generation failed ($LASTEXITCODE)." }
}
