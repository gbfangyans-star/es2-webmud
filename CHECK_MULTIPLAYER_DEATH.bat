@echo off
setlocal
cd /d "%~dp0"
echo ES2 MULTIPLAYER DEATH/CORPSE/REVIVAL - STATIC ONLY
echo This launcher does NOT kill a character and does NOT perform a live death test.
echo Live death is intentionally withheld until an operator-approved disposable/safe test scenario exists.
echo.
python tools\audit_multiplayer_v311.py
set RC=%ERRORLEVEL%
echo.
if not "%RC%"=="0" echo [FAIL] Static death/corpse/PK/revival audit failed.
if "%RC%"=="0" echo [PASS] Static canonical death/corpse/PK/revival contracts are present.
pause
exit /b %RC%
