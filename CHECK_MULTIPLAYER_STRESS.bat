@echo off
setlocal
cd /d "%~dp0"
echo [ES2] Running 50-client burst + 80-session churn bridge test...
node tests\test_multiplayer_stress_v35.mjs
if errorlevel 1 (
  echo.
  echo [FAIL] Multiplayer bridge stress test failed.
  pause
  exit /b 1
)
echo.
echo [PASS] Bridge stress and cleanup test passed.
pause
endlocal
