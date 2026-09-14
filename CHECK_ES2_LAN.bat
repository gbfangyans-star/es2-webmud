@echo off
setlocal
cd /d "%~dp0"
echo ES2 LAN addresses (use one from the same Wi-Fi/LAN):
for /f "tokens=2 delims=:" %%A in ('ipconfig ^| findstr /C:"IPv4 Address" /C:"IPv4 位址"') do (
  for /f "tokens=*" %%B in ("%%A") do echo   http://%%B:8080
)
echo.
echo If Windows Firewall asks, allow Node.js only on Private networks.
echo This is LAN access, not public Internet deployment.
pause
