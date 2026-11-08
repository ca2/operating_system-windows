@echo off
setlocal
cd /d "%~dp0"
gcc -std=c99 -O2 -Wall -Wextra -Werror -static -static-libgcc import-audit.c -o import-audit.exe
exit /b %ERRORLEVEL%
