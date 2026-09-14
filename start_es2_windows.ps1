param([int]$MudPort=4000,[int]$WebPort=8080)
$ErrorActionPreference = "Stop"
$root = $PSScriptRoot
$neo = Join-Path $root "source\upstream\neolith\build-vs2022\src\Release\neolith.exe"
$conf = Join-Path $root "source\upstream\neolith.conf"
$server = Join-Path $root "server"
$version = (Get-Content (Join-Path $root "VERSION") -Raw -Encoding UTF8).Trim()
Write-Host "[ROOT] $root"
Write-Host "[VERSION] $version"
Write-Host "[NEOLITH] $neo"

function Test-Port([int]$Port) {
  try { $c=New-Object System.Net.Sockets.TcpClient; $ar=$c.BeginConnect("127.0.0.1",$Port,$null,$null); $ok=$ar.AsyncWaitHandle.WaitOne(300); if($ok){$c.EndConnect($ar)}; $c.Close(); return $ok } catch { return $false }
}
function Wait-Port([int]$Port,[int]$Seconds) { $deadline=(Get-Date).AddSeconds($Seconds); do { if(Test-Port $Port){return $true}; Start-Sleep -Milliseconds 400 } while((Get-Date)-lt $deadline); return $false }
function Get-ListenerPid([int]$Port) { try { return (Get-NetTCPConnection -State Listen -LocalPort $Port -ErrorAction Stop | Select-Object -First 1 -ExpandProperty OwningProcess) } catch { return $null } }
function Assert-CurrentWebMUD {
  if(!(Test-Port $WebPort)){ return $false }
  try {
    $info=Invoke-RestMethod -Uri ("http://127.0.0.1:{0}/api/version" -f $WebPort) -TimeoutSec 2
    if(($info.version -ne $version) -or ([IO.Path]::GetFullPath([string]$info.projectRoot) -ne [IO.Path]::GetFullPath($root))){
      throw "Port $WebPort is already serving WebMUD v$($info.version) from '$($info.projectRoot)'. Close the OLD WebMUD window before starting v$version."
    }
    Write-Host "[OK] Current WebMUD v$version is already running."
    return $true
  } catch {
    if($_.Exception.Message -like 'Port * is already serving*'){ throw }
    throw "Port $WebPort is already occupied by another process. Close the old WebMUD/server window first."
  }
}
function Assert-CurrentNeolith {
  if(!(Test-Port $MudPort)){ return $false }
  $pid=Get-ListenerPid $MudPort
  if($pid){
    try { $proc=Get-Process -Id $pid -ErrorAction Stop; $path=$proc.Path; if($path -and ([IO.Path]::GetFullPath($path) -ne [IO.Path]::GetFullPath($neo))){ throw "Port $MudPort is owned by another Neolith/process: $path. Close the OLD Neolith window first." } } catch { if($_.Exception.Message -like 'Port * is owned*'){ throw } }
  }
  Write-Host "[OK] Current Neolith listener is already running on $MudPort."
  return $true
}

if(!(Test-Path $neo)){ throw "Neolith executable not found: $neo" }
if(!(Test-Path $conf)){ throw "neolith.conf not found: $conf" }
if(!(Test-Path (Join-Path $server "package.json"))){ throw "server/package.json not found" }
if(!(Get-Command npm.cmd -ErrorAction SilentlyContinue)){ throw "npm.cmd not found in PATH" }
@("user","login","mail") | ForEach-Object { $d=Join-Path $root ("source\upstream\mudlib\data\"+$_); if(!(Test-Path $d)){New-Item -ItemType Directory -Force -Path $d|Out-Null} }

$mudUp=Assert-CurrentNeolith
if(!$mudUp){
  Write-Host "[START] Neolith v$version"
  Start-Process -FilePath $neo -ArgumentList @("-f",$conf) -WorkingDirectory $root
  if(!(Wait-Port $MudPort 20)){ throw "Neolith did not open port $MudPort within 20 seconds" }
  Write-Host "[OK] Neolith port $MudPort"
}
$webUp=Assert-CurrentWebMUD
if(!$webUp){
  Write-Host "[START] WebMUD v$version"
  Start-Process -FilePath "cmd.exe" -ArgumentList "/k","npm.cmd start" -WorkingDirectory $server
  if(!(Wait-Port $WebPort 20)){ throw "WebMUD did not open port $WebPort within 20 seconds" }
  Start-Sleep -Milliseconds 300
  [void](Assert-CurrentWebMUD)
}
Write-Host "[READY] ES2 WebMUD v$version"
Write-Host "Run OPEN_ES2_BROWSER.bat when you want to open the browser."
