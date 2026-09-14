@echo off
setlocal
cd /d "%~dp0"
echo ES2 real-Neolith multiplayer resilience gate
echo Two existing characters; passwords stay in memory only.
echo Runs 20 concurrent save waves, bidirectional tells, periodic abrupt reconnects,
echo canonical save-file checks, orphan-temp checks, and new debug.log save-error scanning.
echo.
python tools\live_multiplayer_resilience.py --root "%CD%" --waves 20 --reconnect-every 5 --report multiplayer_resilience_report.json
set RC=%ERRORLEVEL%
echo.
if "%RC%"=="0" echo Multiplayer resilience gate PASSED.
if not "%RC%"=="0" echo Multiplayer resilience gate needs review. Exit code %RC%.
pause
exit /b %RC%
