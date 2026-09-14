# Real Machine Runbook

v2.2 turns the next phase into an explicit sequence:

1. `setup_windows.ps1` fetches only the canonical repository and builds the catalog.
2. Build Neolith according to the upstream repository README/submodule instructions.
3. `python tools/runtime_plan.py source/upstream` locates actual `neolith` / `neolith.exe` candidates. It never invents a path.
4. `runtime_windows.ps1 -StartNeolith` is allowed only when exactly one binary candidate and `neolith.conf` exist.
5. The script waits for the MUD TCP port, then starts the WebMUD bridge.
6. Run `node tools/multiplayer_probe.mjs --clients 10`, then 50.
7. Use two dedicated test accounts to execute the multiplayer test plan.
8. Export browser session JSONL, replay it, build the single-player acceptance matrix, and retain the raw transcript as authority.

A TCP-open result is not login success. A concurrent-WebSocket result is not multiplayer gameplay success. Each acceptance stage needs captured live evidence.
