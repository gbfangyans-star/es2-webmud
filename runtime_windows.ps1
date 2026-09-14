param(
  [switch]$StartNeolith,
  [int]$MudPort = 4000,
  [int]$WebPort = 8080
)
$ErrorActionPreference="Stop"
$root=$PSScriptRoot
$repo="$root\source\upstream"

Write-Host "[1/6] Verify canonical source"
python "$root\tools\verify_source.py" "$repo"

Write-Host "[2/6] Build canonical catalog"
python "$root\tools\build_catalog.py" "$repo" -o "$root\catalog\generated"

Write-Host "[3/6] Runtime plan"
$planText = python "$root\tools\runtime_plan.py" "$repo"
$plan = $planText | ConvertFrom-Json
$planText

Write-Host "[4/6] Preflight"
python "$root\tools\preflight.py" "$repo" --host 127.0.0.1 --port $MudPort
$preflightCode=$LASTEXITCODE
if($preflightCode -ne 0){
  throw "Preflight failed. Fix canonical source / Node / npm / Neolith prerequisites before starting the bridge."
}

if($StartNeolith){
  if(-not $plan.autoStartSafe){ throw "Neolith cannot be auto-started safely: expected exactly one detected binary and neolith.conf." }
  $bin=$plan.binaryCandidates[0]
  Write-Host "[5/6] Starting Neolith: $bin"
  Start-Process -FilePath $bin -ArgumentList @("-f",$plan.config) -WorkingDirectory $repo
  $deadline=(Get-Date).AddSeconds(20)
  do {
    Start-Sleep -Milliseconds 500
    $ok=$false
    try {
      $c=New-Object System.Net.Sockets.TcpClient
      $ar=$c.BeginConnect("127.0.0.1",$MudPort,$null,$null)
      $ok=$ar.AsyncWaitHandle.WaitOne(300)
      if($ok){$c.EndConnect($ar)}
      $c.Close()
    } catch {$ok=$false}
  } while(-not $ok -and (Get-Date) -lt $deadline)
  if(-not $ok){throw "Neolith process was started but MUD port $MudPort did not become reachable."}
} else {
  Write-Host "[5/6] Neolith auto-start skipped. Use -StartNeolith after Neolith is built/detected."
}

Write-Host "[6/6] Starting WebMUD bridge"
$env:MUD_PORT="$MudPort"
$env:PORT="$WebPort"
Push-Location "$root\server"
try { npm.cmd start } finally { Pop-Location }
