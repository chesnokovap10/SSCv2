param(
    [string] $Exe = (Join-Path $env:ProgramFiles 'SSCv2\ssc.exe'),
    [ValidateSet('aac', 'ssc', 'ssc_uhq')]
    [string[]] $Codec = @('aac', 'aac'),
    [switch] $PlaySound
)

$ErrorActionPreference = 'Stop'
$Exe = (Resolve-Path -LiteralPath $Exe).Path

function Invoke-Tray {
    $output = & $Exe ctl @args | Out-String
    if ($LASTEXITCODE -ne 0 -or $output -match '^error:') {
        throw $output.Trim()
    }
    $output
}

function Wait-TrayMode([string] $Mode) {
    $deadline = [DateTime]::UtcNow.AddSeconds(30)
    do {
        $status = Invoke-Tray status | ConvertFrom-Json
        $ready = $Mode -eq 'off' -or $status.state -like '* (Windows Bluetooth)'
        if ($status.mode -eq $Mode -and !$status.busy -and $ready) {
            return $status | Select-Object mode,state,driver,service
        }
        Start-Sleep -Milliseconds 250
    } while ([DateTime]::UtcNow -lt $deadline)
    throw "Timed out waiting for $Mode. Last state: $($status.state)"
}

$null = Invoke-Tray status | ConvertFrom-Json
try {
    foreach ($mode in $Codec) {
        $null = Invoke-Tray mode off
        $null = Wait-TrayMode off
        $null = Invoke-Tray mode $mode
        Wait-TrayMode $mode
        if ($PlaySound) {
            $wave = Get-ChildItem -LiteralPath "$env:WINDIR\Media" -Filter '*.wav' | Select-Object -First 1
            if ($wave) { [System.Media.SoundPlayer]::new($wave.FullName).PlaySync() }
        }
    }
} finally {
    $null = Invoke-Tray mode off
    Wait-TrayMode off
}
