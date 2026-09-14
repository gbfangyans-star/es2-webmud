@echo off
setlocal
cd /d "%~dp0"
echo [ES2] Running bridge capacity boundary test...
node tests\test_multiplayer_capacity_v35.mjs
if errorlevel 1 (
  echo.
  echo [FAIL] Capacity boundary test failed.
  pause
  exit /b 1
)
echo.
echo [PASS] Capacity limit rejected overflow sessions cleanly.
pause
endlocal
