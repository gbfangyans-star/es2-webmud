@echo off
setlocal
cd /d "%~dp0"
echo === ES2 CONTENT CHANGE SAFETY - READ ONLY ===
python tools\verify_source.py || exit /b 1
python tools\content_change_guard.py || exit /b 1
python tools\content_change_impact.py || exit /b 1
python tools\content_intake_plan.py || exit /b 1
python tools\development_readiness.py || exit /b 1
echo [PASS] Canonical content is unchanged from sealed baseline and intake tooling is ready.
endlocal
