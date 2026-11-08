#Requires -RunAsAdministrator
param(
    [Parameter(Mandatory)] [string] $InfPath,
    [Parameter(Mandatory)] [string] $ProbePath,
    [switch] $ConfigureAAC,
    [string] $WdkRoot
)

$ErrorActionPreference = 'Stop'
$inf = (Resolve-Path -LiteralPath $InfPath).Path
$probe = (Resolve-Path -LiteralPath $ProbePath).Path
if (!$WdkRoot) {
    $WdkRoot = git -C $PSScriptRoot config --local --get sscv2.wdkRoot
    if ($LASTEXITCODE -ne 0 -or !$WdkRoot) { throw 'Set sscv2.wdkRoot or pass -WdkRoot.' }
}
$devcon = (Resolve-Path -LiteralPath "$WdkRoot\tools\10.0.26100.0\x64\devcon.exe").Path
$catalog = Join-Path (Split-Path -Parent $inf) 'SscAvdtpProbe.cat'
if ((Split-Path -Leaf $inf) -ne 'SscAvdtpProbe.inf' -or
    (Get-AuthenticodeSignature -LiteralPath $catalog).Status -ne 'Valid') {
    throw 'Pass the INF from a trusted, signed SSCv2 probe package.'
}

$hardwareId = 'BTHENUM\{0000110b-0000-1000-8000-00805f9b34fb}_VID&00010075_PID&a013'
$nodes = @(Get-PnpDevice -Class MEDIA | Where-Object InstanceId -like "$hardwareId\*")
if ($nodes.Count -ne 1 -or $nodes[0].Status -ne 'OK') {
    throw 'Expected exactly one enabled Buds2 Pro Stereo device.'
}
$id = $nodes[0].InstanceId
$infProperty = 'DEVPKEY_Device_DriverInfPath'
$original = (Get-PnpDeviceProperty -InstanceId $id -KeyName $infProperty).Data
if ($original -ne 'microsoft_bluetooth_a2dp_src.inf') {
    throw "Unexpected original driver: $original"
}
$staged = { Get-WindowsDriver -Online | Where-Object { (Split-Path -Leaf $_.OriginalFileName) -eq 'SscAvdtpProbe.inf' } }
if (@(& $staged).Count) { throw 'Remove the previously staged probe package before running this test.' }

$files = Join-Path ([IO.Path]::GetTempPath()) ("sscv2-probe-" + [guid]::NewGuid())
New-Item -ItemType Directory -Path $files | Out-Null
$stdout = Join-Path $files 'stdout.txt'
$stderr = Join-Path $files 'stderr.txt'
$disabled = $false
try {
    pnputil /add-driver $inf
    if ($LASTEXITCODE) { throw "Package staging failed: $LASTEXITCODE" }
    $packages = @(& $staged)
    if ($packages.Count -ne 1) { throw 'Expected one staged SSCv2 package.' }

    $disabled = $true
    Disable-PnpDevice -InstanceId $id -Confirm:$false
    & $devcon update $inf $hardwareId
    if ($LASTEXITCODE -gt 1) { throw "Driver update failed: $LASTEXITCODE" }
    Enable-PnpDevice -InstanceId $id -Confirm:$false

    if ((Get-PnpDeviceProperty -InstanceId $id -KeyName $infProperty).Data -ne $packages[0].Driver) {
        throw 'Probe driver did not bind.'
    }
    $paths = @(pnputil /enum-interfaces /class '{105bdfd9-73ce-4bcf-b2e9-c5d611f69a23}' |
        ForEach-Object { if ($_ -match '(\\\\\?\\\S+)') { $Matches[1] } })
    if ($paths.Count -ne 1) { throw "Expected one probe interface, found $($paths.Count)." }

    $arguments = @()
    if ($ConfigureAAC) { $arguments += '-configure-aac' }
    $arguments += '"' + $paths[0] + '"'
    $process = Start-Process -FilePath $probe -ArgumentList $arguments -PassThru -WindowStyle Hidden -RedirectStandardOutput $stdout -RedirectStandardError $stderr
    if (!$process.WaitForExit(12000)) {
        $process.Kill()
        $process.WaitForExit()
        throw 'AVDTP probe timed out.'
    }
    Get-Content -LiteralPath $stdout, $stderr
    if ($process.ExitCode) { throw "Probe failed: $($process.ExitCode)" }
} finally {
    try {
        foreach ($package in (& $staged)) {
            pnputil /delete-driver $package.Driver /uninstall
            if ($LASTEXITCODE) { Write-Warning "Could not remove $($package.Driver): $LASTEXITCODE" }
        }
        if ($disabled) {
            pnputil /scan-devices
            Enable-PnpDevice -InstanceId $id -Confirm:$false -ErrorAction Continue
            $restored = (Get-PnpDeviceProperty -InstanceId $id -KeyName $infProperty).Data
            if ($restored -ne $original -or (Get-PnpDevice -InstanceId $id).Status -ne 'OK') {
                throw "Stereo device did not restore. Current driver: $restored"
            }
            "Restored driver: $restored"
        }
    } finally {
        foreach ($file in $stdout, $stderr) {
            if (Test-Path -LiteralPath $file) { Remove-Item -LiteralPath $file }
        }
        Remove-Item -LiteralPath $files
    }
}
