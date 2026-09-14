@echo off
setlocal
cd /d "%~dp0"
echo ============================================================
echo ES2 LAN MODE - SAME HOME/WI-FI NETWORK ONLY
echo This does NOT configure router port forwarding or Internet access.
echo ============================================================
set "ROOT=%CD%"
set "NEOLITH=%ROOT%\source\upstream\neolith\build-vs2022\src\Release\neolith.exe"
set "CONF=%ROOT%\source\upstream\neolith.conf"
if not exist "%NEOLITH%" (echo [ERROR] Neolith executable not found.& pause& exit /b 1)
if not exist "%ROOT%\server\package.json" (echo [ERROR] server\package.json not found.& pause& exit /b 1)
if not exist "%ROOT%\source\upstream\mudlib\data\user" mkdir "%ROOT%\source\upstream\mudlib\data\user"
if not exist "%ROOT%\source\upstream\mudlib\data\login" mkdir "%ROOT%\source\upstream\mudlib\data\login"
if not exist "%ROOT%\source\upstream\mudlib\data\mail" mkdir "%ROOT%\source\upstream\mudlib\data\mail"
start "ES2 Neolith" /D "%ROOT%" cmd /k ""%NEOLITH%" -f "%CONF%""
timeout /t 2 /nobreak >nul
start "ES2 WebMUD LAN" /D "%ROOT%\server" cmd /k "set HOST=0.0.0.0&&npm.cmd start"
timeout /t 3 /nobreak >nul
echo [READY] LAN bridge requested on port 8080.
echo Use CHECK_ES2_LAN.bat to see the local IPv4 address.
endlocal
