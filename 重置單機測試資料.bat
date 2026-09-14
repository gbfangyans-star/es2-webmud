@echo off
chcp 65001 >nul
cd /d "%~dp0"
echo 這會刪除「這台電腦的單機測試角色／測試存檔」，不會碰正式多人版資料。
choice /C YN /N /M "確定重置？ [Y/N] "
if errorlevel 2 exit /b 0
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\reset_local_test.ps1"
pause
