param(
  [string]$Repo = "",
  [int]$MudPort = 4000,
  [Parameter(Mandatory=$true)][string]$Campaign,
  [string]$Out = ""
)
$ErrorActionPreference="Stop"
$root=$PSScriptRoot
if(-not $Repo){$Repo="$root\source\upstream"}
if(-not $Out){$Out="$root\RELEASE_GATE_REPORT.json"}
$tmp="$Out.tmp.json"
$report=[ordered]@{
  version=(Get-Content "$root\VERSION" -Raw).Trim()
  started=(Get-Date).ToString("o")
  steps=@()
}
function Step($name,[scriptblock]$body){
  Write-Host "== $name =="
  try {
    & $body
    if($LASTEXITCODE -ne 0){throw "$name failed ($LASTEXITCODE)"}
    $script:report.steps += @{name=$name;status="PASS"}
  } catch {
    $script:report.steps += @{name=$name;status="FAIL";error="$($_.Exception.Message)"}
    throw
  }
}
Step "release-audit" { python "$root\tools\release_audit.py" "$root" }
Step "canonical-source" { python "$root\tools\verify_source.py" "$Repo" }
Step "source-fingerprint" { python "$root\tools\source_fingerprint.py" "$Repo" }
Step "catalog-build" { python "$root\tools\build_catalog.py" "$Repo" -o "$root\catalog\generated" }
Step "core-audit" { python "$root\tools\core_audit.py" "$Repo" }
Step "multiplayer-bridge-audit" { node "$root\tools\audit_multiplayer_bridge.mjs" "$root\server\index.js" }
Step "preflight" { python "$root\tools\preflight.py" "$Repo" --host 127.0.0.1 --port $MudPort }
$report.finished=(Get-Date).ToString("o")
$report.ok= -not ($report.steps | Where-Object {$_.status -ne "PASS"})
$report | ConvertTo-Json -Depth 6 | Set-Content "$tmp" -Encoding UTF8
python "$root\tools\bind_release_report.py" --campaign "$Campaign" --release "$tmp" --out "$Out"
Remove-Item "$tmp" -ErrorAction SilentlyContinue
Write-Host "Campaign-bound release gate report: $Out"
