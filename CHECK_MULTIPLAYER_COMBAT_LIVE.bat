@echo off
setlocal
cd /d "%~dp0"
echo ES2 MULTIPLAYER NPC COMBAT - ASSISTED LIVE / POTENTIALLY RISKY
echo Requires Neolith running, two existing characters in the SAME real room, and a visible canonical NPC.
echo IMPORTANT: canonical fight.c may make a non-civilized NPC answer with kill_ob().
echo This tool NEVER sends kill itself, but NPC retaliation can still become lethal.
echo Preferred low-risk combat gate: CHECK_MULTIPLAYER_PVP_FIGHT_LIVE.bat
echo.
python tools\live_multiplayer_combat_acceptance.py
set RC=%ERRORLEVEL%
echo.
if "%RC%"=="0" echo [PASS] Live NPC combat actually started and both test characters halted cleanly.
if "%RC%"=="4" echo [SKIP] Combat was rejected/not entered, or operator cancelled. This is NOT combat PASS.
if not "%RC%"=="0" if not "%RC%"=="4" echo [CHECK] Live NPC combat needs review. Exit code %RC%.
pause
exit /b %RC%
