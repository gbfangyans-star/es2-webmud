@echo off
setlocal
cd /d "%~dp0"
echo ============================================================
echo ES2 Internet + zMUD 4.62 mode
echo WebMUD : TCP 4000
echo Neolith: TCP 4001 (internal UTF-8)
echo zMUD   : TCP 4002 (Big5 / CP950)
echo ============================================================
echo.

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0start_es2_internet_windows.ps1"
if not "%ERRORLEVEL%"=="0" (
  echo.
  echo [STOP] ES2 Internet mode failed. zMUD bridge was not started.
  pause
  exit /b 1
)

start "ES2 zMUD Big5 Bridge" cmd.exe /k ""%~dp0START_ZMUD_BRIDGE.bat""
echo.
echo [READY] Web players : http://YOUR_PUBLIC_IP:4000
echo [READY] zMUD players: YOUR_PUBLIC_IP port 4002
echo [NOTE]  Keep TCP 4001 private if possible.
echo.
pause
endlocal
