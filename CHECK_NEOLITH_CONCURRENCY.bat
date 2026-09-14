@echo off
setlocal
cd /d "%~dp0"
echo [ES2] Probing 20 simultaneous Neolith connections on 127.0.0.1:4000...
node tools\probe_neolith_concurrency.mjs 127.0.0.1 4000 20
if errorlevel 1 (
  echo.
  echo [FAIL] Neolith concurrent connection probe failed.
  echo Make sure START_ES2.bat is already running.
  pause
  exit /b 1
)
echo.
echo [PASS] Neolith accepted 20 simultaneous connections and returned a banner to each.
pause
endlocal
