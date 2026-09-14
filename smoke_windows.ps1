$ErrorActionPreference="Stop"
$root=$PSScriptRoot
python "$root\tools\verify_source.py" "$root\source\upstream"
python "$root\tools\runtime_readiness.py" "$root\source\upstream" --host 127.0.0.1 --port 4000
python "$root\tools\runtime_probe.py" --host 127.0.0.1 --port 4000
Write-Host "Runtime smoke probe complete. This does not replace real login/movement/combat validation."
