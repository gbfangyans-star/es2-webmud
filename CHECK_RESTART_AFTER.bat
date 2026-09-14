@echo off
setlocal
cd /d "%~dp0"
echo ES2 SERVER RESTART PERSISTENCE - ASSISTED AFTER SNAPSHOT
echo Run only after YOU have restarted Neolith. This tool never restarts or kills the server.
echo Run before logging the two test characters in again. The BEFORE snapshot must have been taken while both were offline.
echo.
python tools\restart_recovery_snapshot.py after
set RC=%ERRORLEVEL%
echo.
if "%RC%"=="0" echo [PASS] Save files survived the operator-controlled restart unchanged.
if not "%RC%"=="0" echo [CHECK] Restart persistence needs review. Exit code %RC%.
pause
exit /b %RC%
