param(
  [string]$Repo = "",
  [string]$CampaignDir = ""
)
$ErrorActionPreference="Stop"
$root=$PSScriptRoot
if(-not $Repo){$Repo="$root\source\upstream"}
if(-not $CampaignDir){
  $stamp=Get-Date -Format "yyyyMMdd-HHmmss"
  $CampaignDir="$root\campaigns\$stamp"
}
New-Item -ItemType Directory -Force -Path $CampaignDir | Out-Null
$campaign=Join-Path $CampaignDir "campaign.json"
$sourceStatus=Join-Path $CampaignDir "source-status.json"
$fingerprint=Join-Path $CampaignDir "source-fingerprint.json"

Write-Host "[1/4] Verify canonical source"
python "$root\tools\verify_source.py" "$Repo" | Tee-Object -FilePath $sourceStatus

Write-Host "[2/4] Fingerprint exact mudlib tree"
python "$root\tools\source_fingerprint.py" "$Repo" --out "$fingerprint"

Write-Host "[3/4] Create validation campaign"
python "$root\tools\create_validation_campaign.py" --root "$root" --repo "$Repo" --out "$campaign"

Write-Host "[4/4] Create provenance-bound multiplayer plan"
node "$root\tools\new_multiplayer_test_plan.mjs" --out (Join-Path $CampaignDir "multiplayer-plan.json") --campaign "$campaign"

Write-Host ""
Write-Host "Campaign created:"
Write-Host $campaign
Write-Host "Use this same campaign.json for release report, runtime bundle, session package, multiplayer plan, and final closeout."
