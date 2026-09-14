@echo off
setlocal
cd /d "%~dp0"
set "PSEXE=%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe"
if not exist "%PSEXE%" set "PSEXE=powershell.exe"
"%PSEXE%" -NoLogo -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\stop_local_test.ps1"
pause
endlocal
