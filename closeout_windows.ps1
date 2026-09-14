param(
  [Parameter(Mandatory=$true)][string]$Campaign,
  [Parameter(Mandatory=$true)][string]$ReleaseReport,
  [Parameter(Mandatory=$true)][string]$RuntimeBundle,
  [Parameter(Mandatory=$true)][string]$SessionJsonl,
  [Parameter(Mandatory=$true)][string]$MultiplayerPlan,
  [string]$OutDir = "closeout"
)
$ErrorActionPreference="Stop"
$root=$PSScriptRoot
$out=Join-Path $root $OutDir
New-Item -ItemType Directory -Force -Path $out | Out-Null
$sessionPkg=Join-Path $out "session-package"
$campaignReport=Join-Path $out "FINAL_CAMPAIGN_REPORT.json"
$dashboard=Join-Path $out "FINAL_CAMPAIGN_REPORT.html"

Write-Host "[1/6] Build provenance-bound session package"
node "$root\tools\build_session_package.mjs" --session "$SessionJsonl" --out "$sessionPkg" --campaign "$Campaign"

Write-Host "[2/6] Validate session package"
node "$root\tools\validate_session_package.mjs" "$sessionPkg"

Write-Host "[3/6] Validate exact campaign provenance"
python "$root\tools\validate_campaign_provenance.py" --campaign "$Campaign" --release "$ReleaseReport" --runtime-bundle "$RuntimeBundle" --session-package "$sessionPkg" --multiplayer "$MultiplayerPlan"

Write-Host "[4/6] Final campaign gate"
python "$root\tools\final_campaign_gate.py" --campaign "$Campaign" --release "$ReleaseReport" --runtime-bundle "$RuntimeBundle" --session-package "$sessionPkg" --multiplayer "$MultiplayerPlan" --out "$campaignReport"

Write-Host "[5/6] Build operator dashboard"
python "$root\tools\build_campaign_dashboard.py" --campaign "$campaignReport" --out "$dashboard"

Write-Host "[6/6] Done"
Write-Host "Campaign report: $campaignReport"
Write-Host "Dashboard: $dashboard"
