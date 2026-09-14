$ErrorActionPreference="Stop"
$root=$PSScriptRoot
python "$root\tools\preflight.py" "$root\source\upstream" --host 127.0.0.1 --port 4000
