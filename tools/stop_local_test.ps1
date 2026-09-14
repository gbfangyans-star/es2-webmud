$ErrorActionPreference = "SilentlyContinue"
$root = Split-Path -Parent $PSScriptRoot
$pidFile = Join-Path $root ".local-test\localtest-pids.json"
if(Test-Path $pidFile){
  try {
    $p = Get-Content $pidFile -Raw | ConvertFrom-Json
    foreach($id in @($p.web,$p.neolith)){
      if($id){ Stop-Process -Id ([int]$id) -Force -ErrorAction SilentlyContinue }
    }
  } catch {}
  Remove-Item $pidFile -Force -ErrorAction SilentlyContinue
}
# 若 cmd.exe 已經結束但 node 子程序仍在，僅清掉佔用單機測試埠的 process。
foreach($port in @(8181,4101)){
  try {
    Get-NetTCPConnection -State Listen -LocalPort $port -ErrorAction SilentlyContinue | ForEach-Object {
      Stop-Process -Id $_.OwningProcess -Force -ErrorAction SilentlyContinue
    }
  } catch {}
}
Write-Host "ES2 單機測試版已關閉。"
