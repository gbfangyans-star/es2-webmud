param([Parameter(Mandatory=$true)][string]$UserId)
$ErrorActionPreference="Stop"
$root=$PSScriptRoot
$id=$UserId.Trim().ToLowerInvariant()
if($id -notmatch '^[a-z][a-z0-9_]*$'){ throw "UserId must begin with a-z and contain only a-z, 0-9, underscore." }
$initial=$id.Substring(0,1)
$base=Join-Path $root "source\upstream\mudlib\data"
$paths=@(
  Join-Path $base ("login\"+$initial+"\"+$id+".o"),
  Join-Path $base ("user\"+$initial+"\"+$id+".o")
)
$ok=$true
foreach($p in $paths){
  if(Test-Path $p){ $f=Get-Item $p; Write-Host ("[OK] "+$p+"  "+$f.Length+" bytes  "+$f.LastWriteTime) }
  else { Write-Host ("[MISSING] "+$p); $ok=$false }
}
if(!$ok){ exit 2 }
