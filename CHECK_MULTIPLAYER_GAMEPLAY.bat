@echo off
setlocal
cd /d "%~dp0"
python tools\audit_multiplayer_gameplay.py
if errorlevel 1 (
  echo.
  echo Multiplayer gameplay source audit FAILED.
) else (
  echo.
  echo Multiplayer gameplay source audit PASSED.
)
pause
