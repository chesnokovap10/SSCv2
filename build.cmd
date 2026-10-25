@echo off
rem Builds bin\ssc.exe. Needs Go 1.24+ and MinGW-w64 gcc/g++ in PATH (cgo).
rem Version: "0.1 #<commit hash, 8 chars>", from git.
setlocal
cd /d "%~dp0"
set CGO_ENABLED=1
where gcc >nul 2>nul || (echo gcc ^(MinGW-w64^) not found in PATH & exit /b 1)
if not exist internal\bt\zbt_src_hci.c (go run ./tools/genwrap || exit /b 1)
set HASH=dev
for /f %%i in ('git rev-parse --short^=8 HEAD 2^>nul') do set HASH=%%i
set VERSION=0.1 #%HASH%
go build -trimpath -ldflags "-H windowsgui -s -w -X 'sscv2/internal/ipc.Version=%VERSION%'" -o bin\ssc.exe .\cmd\ssc || exit /b 1
echo OK: %~dp0bin\ssc.exe (version %VERSION%)
