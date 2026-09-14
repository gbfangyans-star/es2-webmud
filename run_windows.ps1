$ErrorActionPreference="Stop"
$root=$PSScriptRoot
python "$root\tools\verify_source.py" "$root\source\upstream"
python "$root\tools\build_catalog.py" "$root\source\upstream" -o "$root\catalog\generated"
Push-Location "$root\server"
try { npm.cmd start } finally { Pop-Location }
