@echo off
setlocal
cd /d "%~dp0"
echo ============================================================
echo ES2 INTERNET MODE - version-safe launcher
echo ============================================================
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0start_es2_internet_windows.ps1"
set "RC=%ERRORLEVEL%"
if not "%RC%"=="0" (
  echo.
  echo [STOP] ES2 Internet mode was NOT started.
  echo Read the error above. This launcher now refuses stale/old listeners.
  pause
  exit /b %RC%
)
echo.
pause
endlocal
