@echo off
setlocal
cd /d "%~dp0"
echo ES2 MULTIPLAYER PVP FIGHT - ASSISTED LIVE / NON-KILL
echo Requires Neolith running and two existing characters in the SAME canonical room.
echo This sends only mutual-consent player fight. It NEVER sends kill, spawns, or teleports.
echo If the room forbids combat the result is SKIP, not FAIL or PASS.
echo.
python tools\live_multiplayer_pvp_fight.py
set RC=%ERRORLEVEL%
echo.
if "%RC%"=="0" echo [PASS] Live mutual player fight acceptance passed.
if "%RC%"=="4" echo [SKIP] Current conditions did not permit the live fight or operator cancelled.
if not "%RC%"=="0" if not "%RC%"=="4" echo [CHECK] Live mutual player fight needs review. Exit code %RC%.
pause
exit /b %RC%
