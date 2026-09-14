param(
    [string]$V28 = "C:\ES2\ES2_WebMUD_SourceOnly_v2.8"
)
$ErrorActionPreference = "Stop"
$root = $PSScriptRoot
$from = Join-Path $V28 "source\upstream"

if (-not (Test-Path $from)) {
    throw "Could not find the v2.8 canonical checkout at: $from"
}

Write-Host "Resuming v2.9 from the canonical checkout already downloaded by v2.8."
& powershell -ExecutionPolicy Bypass -File "$root\setup_windows.ps1" -ReuseUpstreamFrom "$from"
if ($LASTEXITCODE -ne 0) {
    throw "v2.9 resume setup failed."
}
