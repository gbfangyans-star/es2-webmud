@echo off
setlocal
cd /d "%~dp0"
if not exist "logs" mkdir "logs"
echo ES2 live two-player soak test (default 10 minutes)
echo Requires Neolith running and two EXISTING test characters.
python tools\live_multiplayer_soak.py --minutes 10 --report logs\multiplayer_soak_latest.json
pause
