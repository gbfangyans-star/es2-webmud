@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "$a=Test-NetConnection 127.0.0.1 -Port 4000 -WarningAction SilentlyContinue; $b=Test-NetConnection 127.0.0.1 -Port 8080 -WarningAction SilentlyContinue; Write-Host ('Neolith 4000: '+$a.TcpTestSucceeded); Write-Host ('WebMUD 8080: '+$b.TcpTestSucceeded); pause"
