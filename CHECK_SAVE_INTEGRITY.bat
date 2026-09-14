@echo off
setlocal
cd /d "%~dp0"
echo ES2 concurrent canonical save integrity test
python tools\live_save_integrity.py --root "%CD%"
pause
