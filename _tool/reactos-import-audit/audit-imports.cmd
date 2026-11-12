@echo off
setlocal
cd /d "%~dp0"
set "AUDIT_EXE=%~1"
if "%AUDIT_EXE%"=="" set "AUDIT_EXE=_app_app.exe"
import-audit.exe "%AUDIT_EXE%" --all > import-audit-report.txt 2>&1
set "AUDIT_RESULT=%ERRORLEVEL%"
type import-audit-report.txt
echo.
echo Report saved to import-audit-report.txt. Exit code: %AUDIT_RESULT%
pause
exit /b %AUDIT_RESULT%
