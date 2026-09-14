@echo off
setlocal
cd /d "%~dp0"
echo ================================================================
echo ES2 MULTIPLAYER - OFFLINE DEVELOPMENT GATE
echo No real Neolith login is performed. No live PASS is claimed.
echo ================================================================
python tools\multiplayer_offline_gate.py
set RC=%ERRORLEVEL%
echo.
if "%RC%"=="0" (echo [PASS] Offline multiplayer development gate.) else (echo [FAIL] Review reports\multiplayer_offline_gate.json)
echo.
pause
exit /b %RC%
