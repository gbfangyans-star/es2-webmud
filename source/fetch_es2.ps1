$ErrorActionPreference = "Stop"
$target = Join-Path $PSScriptRoot "upstream"
$expected = "https://github.com/taedlar/es2_mudlib.git"

if (Test-Path $target) {
    throw "source/upstream already exists. Stop to avoid mixing an old checkout."
}

Write-Host "Cloning canonical ES2 source..."
& git clone --recurse-submodules $expected $target
if ($LASTEXITCODE -ne 0) {
    throw "git clone failed with exit code $LASTEXITCODE"
}

if (-not (Test-Path (Join-Path $target "mudlib"))) {
    throw "Clone finished but mudlib was not found."
}

Write-Host "ES2 source fetched from the only allowed repository."
