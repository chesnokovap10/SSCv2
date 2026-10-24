@echo off
rem Builds bin\ssc.exe. Needs Go 1.24+ and MinGW-w64 gcc/g++ in PATH (cgo).
setlocal
cd /d "%~dp0"
set CGO_ENABLED=1
where gcc >nul 2>nul || (echo gcc ^(MinGW-w64^) not found in PATH & exit /b 1)
if not exist internal\bt\zbt_src_hci.c (go run ./tools/genwrap || exit /b 1)
go build -trimpath -ldflags "-H windowsgui -s -w" -o bin\ssc.exe .\cmd\ssc || exit /b 1
echo OK: %~dp0bin\ssc.exe
