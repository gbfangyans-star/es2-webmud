param(
  [int]$MudPort = 4101,
  [int]$WebPort = 8181
)
$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
$sourceRoot = Join-Path $root "source\upstream"
$sourceMudlib = Join-Path $sourceRoot "mudlib"
$neo = Join-Path $sourceRoot "neolith\build-vs2022\src\Release\neolith.exe"
$server = Join-Path $root "server"
$runtime = Join-Path $root ".local-test\runtime"
$runtimeMudlib = Join-Path $runtime "mudlib"
$runtimeConf = Join-Path $runtime "neolith.localtest.conf"
$pidFile = Join-Path $root ".local-test\localtest-pids.json"
$seedRoot = Join-Path $root "tools\local_test_seed"

function Write-Step([string]$text) { Write-Host "[ES2 單機測試] $text" -ForegroundColor Cyan }
function Test-Port([int]$Port) {
  try {
    $c = New-Object System.Net.Sockets.TcpClient
    $ar = $c.BeginConnect("127.0.0.1",$Port,$null,$null)
    $ok = $ar.AsyncWaitHandle.WaitOne(250)
    if($ok){$c.EndConnect($ar)}
    $c.Close()
    return $ok
  } catch { return $false }
}
function Wait-Port([int]$Port,[int]$Seconds) {
  $deadline=(Get-Date).AddSeconds($Seconds)
  do {
    if(Test-Port $Port){ return $true }
    Start-Sleep -Milliseconds 350
  } while((Get-Date) -lt $deadline)
  return $false
}

Write-Step "準備獨立測試環境，不會使用正式玩家存檔。"
if(!(Test-Path $neo)){ throw "找不到 Neolith：$neo" }
if(!(Test-Path $sourceMudlib)){ throw "找不到 mudlib：$sourceMudlib" }
if(!(Test-Path (Join-Path $server "package.json"))){ throw "找不到 server\package.json" }
if(!(Get-Command node.exe -ErrorAction SilentlyContinue)){ throw "找不到 Node.js。請先安裝 Node.js LTS，安裝一次即可。" }
if(!(Get-Command npm.cmd -ErrorAction SilentlyContinue)){ throw "找不到 npm。請先安裝 Node.js LTS。" }

if(Test-Port $MudPort){ throw "單機測試 MUD Port $MudPort 已被占用。請先執行「關閉單機測試版.bat」。" }
if(Test-Port $WebPort){ throw "單機測試 Web Port $WebPort 已被占用。請先執行「關閉單機測試版.bat」。" }

New-Item -ItemType Directory -Force -Path $runtimeMudlib | Out-Null
# 每次啟動同步遊戲程式，但刻意保留單機測試自己的 data / log。
Write-Step "同步目前專案程式到單機測試區..."
$roboArgs = @(
  $sourceMudlib,
  $runtimeMudlib,
  "/MIR","/R:1","/W:1","/NFL","/NDL","/NJH","/NJS","/NP",
  "/XD",(Join-Path $sourceMudlib "data"),(Join-Path $sourceMudlib "log"),(Join-Path $sourceMudlib "bin")
)
& robocopy.exe @roboArgs | Out-Null
$rc=$LASTEXITCODE
if($rc -ge 8){ throw "同步 mudlib 失敗，Robocopy code=$rc" }

# 第一次建立測試資料時，以目前專案資料為基底。之後都保留在 .local-test，不回寫正式資料。
$runtimeData = Join-Path $runtimeMudlib "data"
if(!(Test-Path $runtimeData)){
  Write-Step "建立第一次單機測試存檔..."
  Copy-Item -Recurse -Force (Join-Path $sourceMudlib "data") $runtimeData
}
New-Item -ItemType Directory -Force -Path (Join-Path $runtimeData "user\t") | Out-Null
New-Item -ItemType Directory -Force -Path (Join-Path $runtimeData "login\t") | Out-Null
New-Item -ItemType Directory -Force -Path (Join-Path $runtimeMudlib "log") | Out-Null
New-Item -ItemType Directory -Force -Path (Join-Path $runtimeMudlib "bin") | Out-Null

# 固定提供一個公開、只供單機測試的管理者帳號；不修改正式帳號。
Copy-Item -Force (Join-Path $seedRoot "user\t\testadmin.o") (Join-Path $runtimeData "user\t\testadmin.o")
Copy-Item -Force (Join-Path $seedRoot "login\t\testadmin.o") (Join-Path $runtimeData "login\t\testadmin.o")
$wizlist = Join-Path $runtimeMudlib "adm\etc\wizlist"
if(Test-Path $wizlist){
  $wiz = Get-Content $wizlist -Raw -Encoding UTF8
  if($wiz -notmatch '(?m)^testadmin\s+\(arch\)\s*$'){
    Add-Content -Path $wizlist -Value "`r`ntestadmin (arch)" -Encoding UTF8
  }
}

# 本機測試用 config，只聽本機 127.0.0.1 對應的 Bridge；不要求路由器或外網 IP。
$confText = Get-Content (Join-Path $sourceRoot "neolith.conf") -Raw -Encoding UTF8
$confText = $confText -replace '(?m)^MudlibDir\s+.*$','MudlibDir`t mudlib'
$confText = $confText -replace '(?m)^Port\s+\d+:telnet\s*$',( "Port`t`t{0}:telnet" -f $MudPort )
Set-Content -Path $runtimeConf -Value $confText -Encoding UTF8

# 避免 LPC 內若有使用 MUD_PORT 常數時仍指到正式埠。
$globals = Join-Path $runtimeMudlib "include\globals.h"
if(Test-Path $globals){
  $g=Get-Content $globals -Raw -Encoding UTF8
  $g=$g -replace '(?m)^#define\s+MUD_PORT\s+\d+\s*$',("#define MUD_PORT {0}" -f $MudPort)
  Set-Content -Path $globals -Value $g -Encoding UTF8
}

if(!(Test-Path (Join-Path $server "node_modules\ws"))){
  Write-Step "第一次啟動：自動安裝 WebMUD 必要套件..."
  Push-Location $server
  try { & npm.cmd ci; if($LASTEXITCODE -ne 0){ throw "npm ci 失敗" } }
  finally { Pop-Location }
}

Write-Step "啟動 Neolith 單機測試核心（127.0.0.1:$MudPort）..."
$neoProc = Start-Process -FilePath $neo -ArgumentList @("-f",$runtimeConf) -WorkingDirectory $runtime -PassThru
if(!(Wait-Port $MudPort 20)){
  try { Stop-Process -Id $neoProc.Id -Force -ErrorAction SilentlyContinue } catch {}
  throw "Neolith 沒有在 20 秒內開啟單機測試 Port $MudPort。"
}

Write-Step "啟動 WebMUD 單機 Bridge（127.0.0.1:$WebPort）..."
$cmd = 'set "HOST=127.0.0.1"&&set "PORT=' + $WebPort + '"&&set "MUD_HOST=127.0.0.1"&&set "MUD_PORT=' + $MudPort + '"&&npm.cmd start'
$webProc = Start-Process -FilePath "cmd.exe" -ArgumentList @("/c",$cmd) -WorkingDirectory $server -PassThru -WindowStyle Minimized
if(!(Wait-Port $WebPort 20)){
  try { Stop-Process -Id $webProc.Id -Force -ErrorAction SilentlyContinue } catch {}
  try { Stop-Process -Id $neoProc.Id -Force -ErrorAction SilentlyContinue } catch {}
  throw "WebMUD 沒有在 20 秒內開啟單機測試 Port $WebPort。"
}

New-Item -ItemType Directory -Force -Path (Split-Path $pidFile -Parent) | Out-Null
@{neolith=$neoProc.Id; web=$webProc.Id; mudPort=$MudPort; webPort=$WebPort; started=(Get-Date).ToString('o')} | ConvertTo-Json | Set-Content -Path $pidFile -Encoding UTF8

Write-Host ""
Write-Host "============================================================" -ForegroundColor Green
Write-Host " ES2 單機測試版已啟動" -ForegroundColor Green
Write-Host " 不需要外網 IP，不需要路由器開 Port。" -ForegroundColor Green
Write-Host " 測試管理者帳號：testadmin" -ForegroundColor Yellow
Write-Host " 測試管理者密碼：test" -ForegroundColor Yellow
Write-Host " 網址：http://127.0.0.1:$WebPort" -ForegroundColor Yellow
Write-Host "============================================================" -ForegroundColor Green
Start-Process ("http://127.0.0.1:{0}" -f $WebPort)
