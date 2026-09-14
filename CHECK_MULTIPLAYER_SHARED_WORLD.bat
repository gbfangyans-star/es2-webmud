@echo off
setlocal
cd /d "%~dp0"
echo ES2 live shared-world acceptance
echo Requires Neolith running and TWO existing test characters placed in the same real room.
echo Optional item/NPC probes use only objects already present in canonical ES2.
echo.
python tools\live_multiplayer_sharedworld.py
set RC=%ERRORLEVEL%
echo.
if not "%RC%"=="0" echo Shared-world acceptance needs review. Exit code %RC%.
if "%RC%"=="0" echo Shared-world acceptance PASSED.
pause
exit /b %RC%
