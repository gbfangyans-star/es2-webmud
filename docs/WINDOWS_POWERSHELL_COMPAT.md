# Windows PowerShell compatibility

v2.8 fixes two issues observed on a real Windows PowerShell 5.1 machine:

1. `source/fetch_es2.ps1` contained non-ASCII text without a BOM. Windows PowerShell 5.1 can decode such scripts using the local ANSI code page, corrupting quoted strings and producing `ParserError / UnexpectedToken`.
2. PowerShell may select `npm.ps1`, which can be blocked by execution policy even though Node/npm are installed correctly.

Fixes:
- `fetch_es2.ps1` and `setup_windows.ps1` are ASCII-only.
- Other PowerShell scripts are emitted as UTF-8 with BOM.
- Windows scripts invoke `npm.cmd`, not `npm`.
- setup validates Git, Python, Node and npm.cmd before cloning.
