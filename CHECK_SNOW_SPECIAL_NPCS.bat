@echo off
setlocal
cd /d "%~dp0"
python tools\audit_snow_special_npcs.py
if errorlevel 1 (
  echo [FAIL] Snow special NPC audit failed.
  exit /b 1
)
echo [PASS] Snow special NPC canonical wiring audit passed.
