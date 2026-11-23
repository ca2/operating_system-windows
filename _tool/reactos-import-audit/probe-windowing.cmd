@echo off
setlocal
cd /d "%~dp0"
dll-load-probe.exe windowing_win32.dll > dll-load-probe.txt 2>&1
type dll-load-probe.txt
pause
