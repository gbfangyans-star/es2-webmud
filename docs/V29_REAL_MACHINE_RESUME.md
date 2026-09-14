# v2.9 real-machine resume

The first real Windows run of v2.8 reached the full canonical catalog and exposed one incorrect audit assumption:

- incorrect audit path: `/feature/char/statistic`
- actual canonical object: `/feature/statistic`

v2.9 fixes the core audit path.

The v2.8 canonical checkout does not need to be downloaded again. If v2.8 and v2.9 are both under `C:\ES2`, v2.9 setup automatically detects:

`C:\ES2\ES2_WebMUD_SourceOnly_v2.8\source\upstream`

It copies that already-verified checkout into v2.9 and continues from verification/catalog/npm/preflight.

Explicit resume is also available:

`powershell -ExecutionPolicy Bypass -File .\resume_from_v28_windows.ps1`
