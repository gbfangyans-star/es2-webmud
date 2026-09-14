$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
& (Join-Path $PSScriptRoot "stop_local_test.ps1")
$dir = Join-Path $root ".local-test"
if(Test-Path $dir){ Remove-Item -Recurse -Force $dir }
Write-Host "單機測試資料已重置。下次啟動會重新建立乾淨測試環境。"
