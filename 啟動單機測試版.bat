@echo off
chcp 65001 >nul
cd /d "%~dp0"
title ES2 單機測試版
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\start_local_test.ps1"
if errorlevel 1 (
  echo.
  echo [失敗] 單機測試版沒有成功啟動，請把上面的錯誤畫面傳給專案負責人。
  pause
)
