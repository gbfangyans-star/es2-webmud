@echo off
setlocal
cd /d "%~dp0"
echo [ES2] Running 8-client bridge isolation test...
node tests\test_multiplayer_isolation_v34.mjs
if errorlevel 1 (
  echo.
  echo [FAIL] Multiplayer bridge isolation test failed.
  pause
  exit /b 1
)
echo.
echo [PASS] 8 browser sessions were isolated into 8 TCP sessions.
pause
endlocal
