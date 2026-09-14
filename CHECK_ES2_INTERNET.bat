@echo off
echo === ES2 v3.20.5 Internet listeners ===
netstat -ano | findstr LISTENING | findstr ":4000 :4001"
echo.
echo Expected:
echo   0.0.0.0:4000 = WebMUD
echo   *:4001       = Neolith
pause
