# Release Gate

`verify_release_windows.ps1` is the consolidated real-machine pre-release pipeline.

It checks:
- package/version/security invariants
- exact canonical Git source
- full catalog build
- core source audit
- multiplayer bridge structure
- runtime prerequisites and MUD TCP availability

Live gameplay acceptance remains separate. Passing the release gate does not manufacture a Neolith gameplay PASS.
