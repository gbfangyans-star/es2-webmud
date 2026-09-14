@echo off
setlocal
cd /d "%~dp0"
echo ES2 live Neolith connection storm gate
echo 5 waves x 50 simultaneous raw connections; no accounts or passwords required.
echo This verifies the real driver keeps accepting clients after rapid connect/disconnect churn.
echo.
python tools\live_neolith_storm.py --root "%CD%" --clients 50 --waves 5 --report neolith_storm_report.json
set RC=%ERRORLEVEL%
echo.
if "%RC%"=="0" echo Neolith storm gate PASSED.
if not "%RC%"=="0" echo Neolith storm gate needs review. Exit code %RC%.
pause
exit /b %RC%
