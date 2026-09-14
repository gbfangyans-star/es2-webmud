@echo off
setlocal
cd /d "%~dp0"
title ES2 Local Test
set "LOG=%~dp0localtest-start.log"
>"%LOG%" echo [ES2] Starting local test...
set "PSEXE=%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe"
if not exist "%PSEXE%" set "PSEXE=powershell.exe"
"%PSEXE%" -NoLogo -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\start_local_test.ps1" >>"%LOG%" 2>&1
set "RC=%ERRORLEVEL%"
type "%LOG%"
echo.
if not "%RC%"=="0" (
  echo [FAILED] Local test did not start. Error code: %RC%
  echo Send localtest-start.log or a screenshot of this window for diagnosis.
  echo.
  pause
  exit /b %RC%
)
echo [OK] ES2 local test started. Browser should open automatically.
pause
endlocal
