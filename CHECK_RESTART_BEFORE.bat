@echo off
setlocal
cd /d "%~dp0"
echo ES2 SERVER RESTART PERSISTENCE - ASSISTED BEFORE SNAPSHOT
echo This tool does NOT restart or kill Neolith. Save and LOG OUT both test characters first.
REM Offline-before-snapshot prevents legitimate disconnect saves from looking like restart corruption.
echo.
python tools\restart_recovery_snapshot.py before
set RC=%ERRORLEVEL%
echo.
if "%RC%"=="0" echo [PASS] BEFORE snapshot captured.
if not "%RC%"=="0" echo [CHECK] BEFORE snapshot needs review. Exit code %RC%.
pause
exit /b %RC%
