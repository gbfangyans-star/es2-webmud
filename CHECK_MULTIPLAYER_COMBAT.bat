@echo off
setlocal
cd /d "%~dp0"
echo ES2 MULTIPLAYER COMBAT - STATIC ONLY
echo This launcher does NOT log in characters and does NOT perform live combat.
echo Use CHECK_MULTIPLAYER_COMBAT_LIVE.bat for the operator-assisted real-NPC probe.
echo.
python tools\audit_multiplayer_v310.py
set RC=%ERRORLEVEL%
echo.
if not "%RC%"=="0" echo [FAIL] Static canonical combat/team audit failed.
if "%RC%"=="0" echo [PASS] Static canonical combat/team audit passed.
pause
exit /b %RC%
