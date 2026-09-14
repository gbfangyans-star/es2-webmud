$ErrorActionPreference = "Stop"
$root = $PSScriptRoot
$neo = Join-Path $root "source\upstream\neolith\build-vs2022\src\Release\neolith.exe"
$conf = Join-Path $root "source\upstream\neolith.conf"
$server = Join-Path $root "server"
$version = (Get-Content (Join-Path $root "VERSION") -Raw -Encoding UTF8).Trim()
$mudPort = 4001
$webPort = 4000

Write-Host "============================================================"
Write-Host "ES2 INTERNET MODE v$version"
Write-Host "Browser/WebMUD: TCP $webPort"
Write-Host "Neolith internal: TCP $mudPort"
Write-Host "============================================================"
Write-Host "[ROOT] $root"

function Get-Listener([int]$Port) {
  try { return Get-NetTCPConnection -State Listen -LocalPort $Port -ErrorAction Stop | Select-Object -First 1 }
  catch { return $null }
}
function Get-ProcessPath([int]$ProcessId) {
  try { return (Get-Process -Id $ProcessId -ErrorAction Stop).Path }
  catch { return $null }
}
function Same-Path([string]$A,[string]$B) {
  if(!$A -or !$B){ return $false }
  try { return ([IO.Path]::GetFullPath($A).TrimEnd('\') -ieq [IO.Path]::GetFullPath($B).TrimEnd('\')) }
  catch { return $false }
}
function Wait-Listener([int]$Port,[int]$Seconds) {
  $deadline=(Get-Date).AddSeconds($Seconds)
  do {
    $x=Get-Listener $Port
    if($x){ return $x }
    Start-Sleep -Milliseconds 350
  } while((Get-Date)-lt $deadline)
  return $null
}
function Assert-Web-Port {
  $listener=Get-Listener $webPort
  if(!$listener){ return $false }
  try {
    $info=Invoke-RestMethod -Uri ("http://127.0.0.1:{0}/api/version" -f $webPort) -TimeoutSec 2
    $sameVersion=([string]$info.version -eq $version)
    $sameRoot=Same-Path ([string]$info.projectRoot) $root
    if(!$sameVersion -or !$sameRoot){
      throw "TCP $webPort is already used by another WebMUD: version=$($info.version), root=$($info.projectRoot). Close the OLD WebMUD window/process first."
    }
    Write-Host "[OK] Current WebMUD v$version is already listening on $webPort."
    return $true
  } catch {
    if($_.Exception.Message -like 'TCP * is already used by another WebMUD*'){ throw }
    throw "TCP $webPort is already occupied by PID $($listener.OwningProcess), but it is not this WebMUD. Close that process first."
  }
}
function Test-MudHandshake {
  $client=$null
  try {
    $client=New-Object System.Net.Sockets.TcpClient
    $iar=$client.BeginConnect("127.0.0.1",$mudPort,$null,$null)
    if(!$iar.AsyncWaitHandle.WaitOne(3000,$false)){ throw "TCP connect timeout" }
    $client.EndConnect($iar)
    $client.ReceiveTimeout=5000
    $stream=$client.GetStream()
    $buf=New-Object byte[] 512
    $n=$stream.Read($buf,0,$buf.Length)
    if($n -le 0){ throw "Neolith accepted TCP but sent no login/telnet greeting" }
    Write-Host "[OK] Neolith active handshake returned $n byte(s)."
    return $true
  } catch {
    throw "Neolith TCP $mudPort is listening but player handshake failed: $($_.Exception.Message). Check source\upstream\mudlib\log\debug.log."
  } finally {
    if($client){ try{$client.Close()}catch{} }
  }
}

function Assert-Neolith-Port {
  $listener=Get-Listener $mudPort
  if(!$listener){ return $false }
  $listenerPid=$listener.OwningProcess
  $path=Get-ProcessPath $listenerPid
  if(!(Same-Path $path $neo)){
    throw "TCP $mudPort is already occupied by OLD/OTHER process PID $listenerPid ($path). Close the old Neolith/process first."
  }
  Write-Host "[OK] Current Neolith is already listening on $mudPort (PID $listenerPid)."
  return $true
}

if(!(Test-Path $neo)){ throw "Neolith executable not found: $neo" }
if(!(Test-Path $conf)){ throw "neolith.conf not found: $conf" }
if(!(Test-Path (Join-Path $server "package.json"))){ throw "server/package.json not found" }
if(!(Get-Command npm.cmd -ErrorAction SilentlyContinue)){ throw "npm.cmd not found in PATH" }
@("user","login","mail") | ForEach-Object {
  $d=Join-Path $root ("source\upstream\mudlib\data\"+$_)
  if(!(Test-Path $d)){ New-Item -ItemType Directory -Force -Path $d | Out-Null }
}

$neoUp=Assert-Neolith-Port
if(!$neoUp){
  Write-Host "[START] Neolith v$version on $mudPort..."
  $proc=Start-Process -FilePath $neo -ArgumentList @("-f",$conf) -WorkingDirectory $root -PassThru
  Start-Sleep -Milliseconds 500
  if($proc.HasExited){ throw "Neolith exited immediately with code $($proc.ExitCode). Check source\upstream\mudlib\log\debug.log." }
  $listener=Wait-Listener $mudPort 20
  if(!$listener){
    try { $proc.Refresh() } catch {}
    if($proc.HasExited){ throw "Neolith exited before opening TCP $mudPort (code $($proc.ExitCode)). Check source\upstream\mudlib\log\debug.log." }
    throw "Neolith did not open TCP $mudPort within 20 seconds."
  }
  $listenerPath=Get-ProcessPath $listener.OwningProcess
  if(!(Same-Path $listenerPath $neo)){
    throw "TCP $mudPort was opened by unexpected PID $($listener.OwningProcess) ($listenerPath), not this Neolith."
  }
  Write-Host "[OK] Neolith TCP $mudPort (PID $($listener.OwningProcess))."
}

$webUp=Assert-Web-Port
if(!$webUp){
  Write-Host "[START] WebMUD v$version on $webPort..."
  $cmd = 'set "HOST=0.0.0.0"&&set "PORT=4000"&&set "MUD_HOST=127.0.0.1"&&set "MUD_PORT=4001"&&npm.cmd start'
  Start-Process -FilePath "cmd.exe" -ArgumentList @("/k",$cmd) -WorkingDirectory $server | Out-Null
  $listener=Wait-Listener $webPort 20
  if(!$listener){ throw "WebMUD did not open TCP $webPort within 20 seconds." }
  Start-Sleep -Milliseconds 300
  [void](Assert-Web-Port)
}

[void](Test-MudHandshake)

Write-Host ""
Write-Host "[READY] Browser/WebMUD TCP $webPort."
Write-Host "[READY] Neolith TCP $mudPort."
Write-Host "Local test: http://127.0.0.1:$webPort"
Write-Host "Friend:     http://YOUR_PUBLIC_IP:$webPort"
Write-Host ""
Write-Host "If startup is refused, close the OLD ES2/Neolith/WebMUD windows shown in Task Manager and run this launcher again."
