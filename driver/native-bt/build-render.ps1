param(
    [string] $OutputDirectory = (Join-Path $PSScriptRoot '..\..\bin\SscBudsRender'),
    [string] $WdkRoot,
    [string] $SdkRoot = "${env:ProgramFiles(x86)}\Windows Kits\10",
    [string] $SdkVersion = '10.0.26100.0',
    [switch] $Package
)

$ErrorActionPreference = 'Stop'
if (!$WdkRoot) {
    $WdkRoot = git -C $PSScriptRoot config --local --get sscv2.wdkRoot
    if ($LASTEXITCODE -ne 0) { throw 'Pass -WdkRoot or set sscv2.wdkRoot.' }
}
$wdk = (Resolve-Path -LiteralPath $WdkRoot).Path
$source = Join-Path $PSScriptRoot 'src\render'
$output = (New-Item -ItemType Directory -Force -Path $OutputDirectory).FullName
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vs = & $vswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (!$vs) { throw 'Visual Studio x64 C++ Build Tools were not found.' }
$version = (Get-Content "$vs\VC\Auxiliary\Build\Microsoft.VCToolsVersion.default.txt" -Raw).Trim()
$msvc = "$vs\VC\Tools\MSVC\$version"
$tools = "$msvc\bin\Hostx64\x64"

$includes = @(
    "$msvc\include",
    "$wdk\Include\$SdkVersion\km",
    "$wdk\Include\wdf\kmdf\1.31",
    "$SdkRoot\Include\$SdkVersion\shared",
    "$SdkRoot\Include\$SdkVersion\um",
    "$SdkRoot\Include\$SdkVersion\ucrt",
    $source,
    "$source\Inc",
    "$source\Main",
    "$source\Utilities",
    "$source\Filters"
) | ForEach-Object { "/I$_" }

$sources = @(
    "$source\Main\adapter.cpp",
    "$source\Main\basetopo.cpp",
    "$source\Main\common.cpp",
    "$source\Main\mintopo.cpp",
    "$source\Main\minwavert.cpp",
    "$source\Main\minwavertstream.cpp",
    "$source\render-pcm.cpp",
    "$source\Main\NewDelete.cpp",
    "$source\Filters\speakertopo.cpp",
    "$source\Filters\micarraytopo.cpp",
    "$source\Utilities\hw.cpp",
    "$source\Utilities\kshelper.cpp",
    "$source\Utilities\savedata.cpp",
    "$source\Utilities\ToneGenerator.cpp"
)
$scratch = (New-Item -ItemType Directory -Path (Join-Path ([IO.Path]::GetTempPath()) ("sscv2-render-" + [guid]::NewGuid()))).FullName
$binary = Join-Path $scratch 'SscBudsRender.sys'
Push-Location -LiteralPath $scratch
try {
    & "$tools\cl.exe" /nologo /c /O2 /kernel /Zl /D_NEW_DELETE_OPERATORS_ /DNTSTRSAFE_LIB /D_AMD64_ /D_WIN64 /DWINVER=0x0A00 /D_WIN32_WINNT=0x0A00 /DNTDDI_VERSION=0x0A000008 /DKMDF_VERSION_MAJOR=1 /DKMDF_VERSION_MINOR=31 $includes $sources
    if ($LASTEXITCODE) { throw "WaveRT compilation failed ($LASTEXITCODE)." }
    $objects = $sources | ForEach-Object { [IO.Path]::GetFileNameWithoutExtension($_) + '.obj' }
    & "$tools\link.exe" /nologo /kernel /driver /subsystem:native /entry:FxDriverEntry /nodefaultlib "/out:$binary" $objects "/libpath:$wdk\Lib\$SdkVersion\km\x64" "/libpath:$wdk\Lib\wdf\kmdf\x64\1.31" ntoskrnl.lib hal.lib portcls.lib stdunk.lib libcntpr.lib ntstrsafe.lib ks.lib wdfdriverentry.lib wdfldr.lib bufferoverflowfastfailk.lib
    if ($LASTEXITCODE) { throw "WaveRT link failed ($LASTEXITCODE)." }
    if ($Package) {
        $packageDirectory = (New-Item -ItemType Directory -Force -Path (Join-Path $output 'package')).FullName
        Copy-Item -LiteralPath "$source\SscBudsRender.inf", $binary -Destination $packageDirectory -Force
        & "$wdk\bin\$SdkVersion\x86\Inf2Cat.exe" "/driver:$packageDirectory" /os:10_VB_X64,10_GE_X64
        if ($LASTEXITCODE) { throw "WaveRT catalog generation failed ($LASTEXITCODE)." }
    } else {
        Copy-Item -LiteralPath $binary -Destination $output -Force
    }
} finally {
    Pop-Location
    Get-ChildItem -LiteralPath $scratch -File | Remove-Item
    Remove-Item -LiteralPath $scratch
}
