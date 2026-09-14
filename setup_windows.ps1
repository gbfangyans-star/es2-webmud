param(
    [string]$ReuseUpstreamFrom = ""
)

$ErrorActionPreference = "Stop"
$root = $PSScriptRoot
$target = Join-Path $root "source\upstream"

function Require-Command([string]$name) {
    $cmd = Get-Command $name -ErrorAction SilentlyContinue
    if (-not $cmd) {
        throw "Required command not found: $name"
    }
}

function Verify-Canonical([string]$path) {
    & python "$root\tools\verify_source.py" "$path"
    if ($LASTEXITCODE -ne 0) {
        throw "Canonical source verification failed for: $path"
    }
}

function Copy-CanonicalCheckout([string]$from, [string]$to) {
    if (-not (Test-Path $from)) {
        throw "Reuse source not found: $from"
    }
    Write-Host "Reusing existing canonical checkout:"
    Write-Host "  $from"
    New-Item -ItemType Directory -Force -Path (Split-Path $to -Parent) | Out-Null
    Copy-Item -Path $from -Destination $to -Recurse -Force
    Verify-Canonical $to
}

Write-Host "[0/5] Checking prerequisites..."
Require-Command "git"
Require-Command "python"
Require-Command "node"
Require-Command "npm.cmd"

Write-Host "[1/5] Preparing canonical taedlar/es2_mudlib..."

if (Test-Path $target) {
    Write-Host "source/upstream already exists. Verifying and reusing it."
    Verify-Canonical $target
}
elseif ($ReuseUpstreamFrom) {
    Copy-CanonicalCheckout $ReuseUpstreamFrom $target
}
else {
    $parent = Split-Path $root -Parent
    $autoV28 = Join-Path $parent "ES2_WebMUD_SourceOnly_v2.8\source\upstream"
    if (Test-Path $autoV28) {
        Write-Host "Found v2.8 canonical checkout next to v2.9."
        Copy-CanonicalCheckout $autoV28 $target
    }
    else {
        & "$root\source\fetch_es2.ps1"
    }
}

Write-Host "[2/5] Verifying canonical source..."
Verify-Canonical $target

Write-Host "[3/5] Building catalog..."
& python "$root\tools\build_catalog.py" "$target" -o "$root\catalog\generated"
if ($LASTEXITCODE -ne 0) {
    throw "Catalog build failed."
}

Write-Host "[4/5] Installing browser bridge..."
Push-Location "$root\server"
try {
    & npm.cmd install
    if ($LASTEXITCODE -ne 0) {
        throw "npm.cmd install failed."
    }
}
finally {
    Pop-Location
}

Write-Host "[5/5] Preflight..."
& python "$root\tools\preflight.py" "$target" --host 127.0.0.1 --port 4000
$preflightCode = $LASTEXITCODE
if ($preflightCode -ne 0) {
    Write-Host "Preflight is not fully green yet. This is expected if Neolith has not been built or started."
}

Write-Host ""
Write-Host "Setup stage complete."
Write-Host "Next command:"
Write-Host 'python .\tools\runtime_plan.py .\source\upstream'
