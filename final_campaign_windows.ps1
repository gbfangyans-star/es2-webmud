param(
  [Parameter(Mandatory=$true)][string]$Campaign,
  [Parameter(Mandatory=$true)][string]$ReleaseReport,
  [Parameter(Mandatory=$true)][string]$RuntimeBundle,
  [Parameter(Mandatory=$true)][string]$SessionPackage,
  [Parameter(Mandatory=$true)][string]$MultiplayerPlan,
  [string]$Out = "FINAL_CAMPAIGN_REPORT.json"
)
$ErrorActionPreference="Stop"
$root=$PSScriptRoot
Write-Host "[1/5] Campaign provenance validation"
python "$root\tools\validate_campaign_provenance.py" --campaign "$Campaign" --release "$ReleaseReport" --runtime-bundle "$RuntimeBundle" --session-package "$SessionPackage" --multiplayer "$MultiplayerPlan"
Write-Host "[2/5] Runtime evidence validation"
python "$root\tools\validate_runtime_evidence.py" "$RuntimeBundle"
Write-Host "[3/5] Session package validation"
node "$root\tools\validate_session_package.mjs" "$SessionPackage"
Write-Host "[4/5] Multiplayer evidence validation"
node "$root\tools\validate_multiplayer_plan.mjs" --plan "$MultiplayerPlan"
Write-Host "[5/5] Final campaign gate"
python "$root\tools\final_campaign_gate.py" --campaign "$Campaign" --release "$ReleaseReport" --runtime-bundle "$RuntimeBundle" --session-package "$SessionPackage" --multiplayer "$MultiplayerPlan" --out "$Out"
Write-Host "Final campaign report: $Out"
