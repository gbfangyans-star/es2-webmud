@echo off
setlocal
cd /d "%~dp0"
echo ============================================================
echo ES2 START - version-safe launcher
echo ============================================================
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0start_es2_windows.ps1"
set "RC=%ERRORLEVEL%"
if not "%RC%"=="0" (
  echo.
  echo [STOP] ES2 was not started. Read the message above.
  echo This prevents an old and new project version from sharing ports 4000/8080.
  pause
  exit /b %RC%
)
endlocal
