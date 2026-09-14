@echo off
setlocal
cd /d "%~dp0"
echo ES2 live room/team/follow multiplayer acceptance
echo Requires Neolith running and two EXISTING test characters.
echo Passwords are hidden and are not written to disk.
python tools\live_multiplayer_room_acceptance.py
pause
