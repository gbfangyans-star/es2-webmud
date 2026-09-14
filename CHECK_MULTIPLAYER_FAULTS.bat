@echo off
setlocal
cd /d "%~dp0"
echo ============================================================
echo ES2 MULTIPLAYER BRIDGE - OFFLINE FAULT MATRIX
echo ============================================================
echo This uses a local fake MUD only. It does NOT claim live ES2 gameplay PASS.
echo.
node tests\test_multiplayer_fault_matrix_v3191.mjs
set RC=%ERRORLEVEL%
echo.
echo Report: reports\multiplayer_fault_matrix_report.json
if not "%RC%"=="0" echo [FAIL] Offline fault matrix needs review. Exit code %RC%.
if "%RC%"=="0" echo [PASS] Offline fault matrix passed.
pause
exit /b %RC%
