@echo off
setlocal
cd /d "%~dp0"
echo =============================================
echo ES2 CONTENT WORKBENCH - OFFLINE / READ ONLY
echo =============================================
python tools\verify_source.py source\upstream || exit /b 1
python tools\build_content_workbench.py || exit /b 1
python tools\development_readiness.py || exit /b 1
python -m pytest -q tests\test_v3193_content_workbench.py || exit /b 1
echo.
echo [PASS] Content workbench ready. No gameplay data was created or modified.
endlocal
