@echo off
setlocal
cd /d "%~dp0"
echo =============================================
echo ES2 CANONICAL CONTENT GUARD - READ ONLY
echo =============================================
python tools\verify_source.py source\upstream || exit /b 1
python tools\content_change_guard.py || exit /b 1
python tools\build_content_workbench.py || exit /b 1
python tools\content_intake_plan.py || exit /b 1
python tools\development_readiness.py || exit /b 1
echo.
echo [PASS] Canonical content unchanged; intake tooling is ready.
endlocal
