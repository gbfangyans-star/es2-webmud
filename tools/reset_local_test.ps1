$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
& (Join-Path $PSScriptRoot "stop_local_test.ps1")
$dir = Join-Path $root ".local-test"
if(Test-Path $dir){ Remove-Item -Recurse -Force $dir }
Write-Host "Local-test data reset. It will be rebuilt on next start."
