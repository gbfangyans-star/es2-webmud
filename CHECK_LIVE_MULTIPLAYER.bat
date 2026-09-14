@echo off
setlocal
cd /d "%~dp0"
echo ============================================================
echo ES2 LIVE MULTIPLAYER ACCEPTANCE - TWO EXISTING CHARACTERS
echo Passwords are hidden and are NOT saved.
echo Neolith must already be running on port 4000.
echo ============================================================
python tools\live_multiplayer_acceptance.py
set "RC=%ERRORLEVEL%"
echo.
if "%RC%"=="0" (echo [PASS] Live multiplayer acceptance passed.) else (echo [CHECK] Review the result above. Exit code %RC%.)
pause
exit /b %RC%
