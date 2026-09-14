@echo off
setlocal
cd /d "%~dp0"
echo ============================================================
echo ES2 zMUD 4.62 Big5 Bridge
echo zMUD port : 4002 (Big5 / CP950)
echo Neolith   : 127.0.0.1:4001 (UTF-8)
echo ============================================================
echo.
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0zmud_big5_bridge.ps1" -ListenAddress 0.0.0.0 -ListenPort 4002 -MudHost 127.0.0.1 -MudPort 4001
if not "%ERRORLEVEL%"=="0" (
  echo.
  echo [ERROR] zMUD bridge stopped with error %ERRORLEVEL%.
  pause
)
endlocal
