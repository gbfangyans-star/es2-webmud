from pathlib import Path
import re
ROOT=Path(__file__).parents[1]
fetch=(ROOT/"source/fetch_es2.ps1").read_bytes()
setup=(ROOT/"setup_windows.ps1").read_bytes()
assert all(b < 128 for b in fetch)
assert all(b < 128 for b in setup)
st=setup.decode("ascii")
assert "npm.cmd install" in st
assert "Require-Command \"git\"" in st
assert "Require-Command \"python\"" in st
assert "Require-Command \"node\"" in st
assert "Require-Command \"npm.cmd\"" in st
ft=fetch.decode("ascii")
assert "https://github.com/taedlar/es2_mudlib.git" in ft
assert "git clone --recurse-submodules" in ft
print("v2.8 Windows PowerShell compatibility tests passed")
