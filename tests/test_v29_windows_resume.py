from pathlib import Path
ROOT=Path(__file__).parents[1]
setup=(ROOT/'setup_windows.ps1').read_text(encoding='ascii')
resume=(ROOT/'resume_from_v28_windows.ps1').read_text(encoding='ascii')
assert 'ReuseUpstreamFrom' in setup
assert 'ES2_WebMUD_SourceOnly_v2.8\\source\\upstream' in setup
assert 'Copy-CanonicalCheckout' in setup
assert 'Verify-Canonical $to' in setup
assert 'npm.cmd install' in setup
assert 'source\\upstream' in resume
assert 'setup_windows.ps1' in resume
print('v2.9 Windows resume setup contract passed')
