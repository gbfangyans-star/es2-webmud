@echo off
setlocal
cd /d "%~dp0"
echo ============================================================
echo ES2 DEVELOPMENT READINESS - OFFLINE / NON-DESTRUCTIVE
echo ============================================================
python tools\development_readiness.py
set RC=%ERRORLEVEL%
echo.
echo Report: DEVELOPMENT_READINESS.json
if %RC%==0 (echo [PASS] Development/source prerequisites are ready.) else (echo [FAIL] See report above.)
pause
exit /b %RC%
