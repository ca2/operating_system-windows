@echo off
setlocal
cd /d "%~dp0"
echo Running _app_app.exe with stdout and stderr redirected...
"%~dp0_app_app.exe" > "%~dp0ca2-console.log" 2>&1
set "APP_RESULT=%ERRORLEVEL%"
echo Application exit code: %APP_RESULT%
echo Application exit code: %APP_RESULT%> "%~dp0app-exit-code.txt"
echo Trace file: "%~dp0ca2-console.log"
pause
exit /b %APP_RESULT%
ca