@echo off
setlocal
cd /d "%~dp0"
echo ============================================================
set /p ES2_VERSION=<VERSION
echo ES2 MULTIPLAYER MASTER ACCEPTANCE - v%ES2_VERSION%
echo ============================================================
echo Functional multiplayer is tested BEFORE the heavy Neolith storm.
echo The gate also rejects an old WebMUD version still occupying port 8080.
echo.
echo REQUIREMENTS:
echo   1. START_ES2.bat from THIS v%ES2_VERSION% folder is running.
echo   2. Two existing test characters are available.
echo   3. Passwords stay hidden and memory-only.
echo.
python tools\multiplayer_master_gate.py
set "RC=%ERRORLEVEL%"
echo.
if "%RC%"=="0" echo [PASS] Multiplayer master automatic/live gate passed.
if not "%RC%"=="0" echo [CHECK] Multiplayer master gate needs review. Exit code %RC%.
echo Detailed result: multiplayer_master_report.json
pause
exit /b %RC%
