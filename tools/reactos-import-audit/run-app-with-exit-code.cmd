@echo off
setlocal
cd /d "%~dp0"
echo Starting _app_app.exe and waiting for it to exit...
start "" /wait "_app_app.exe"
set "APP_RESULT=%ERRORLEVEL%"
echo _app_app exit code: %APP_RESULT%
echo _app_app exit code: %APP_RESULT%>app-exit-code.txt
echo Saved to app-exit-code.txt
pause
exit /b %APP_RESULT%
