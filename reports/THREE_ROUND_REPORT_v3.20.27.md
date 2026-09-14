# v3.20.25–v3.20.27 three-round batch

## Round 1 — runtime topology authority
- ROOM telemetry now begins an authoritative snapshot for the occupied LPC room.
- Existing outgoing edges for that room are cleared before fresh EXIT telemetry is merged.
- This prevents stale map exits after dynamic maze reset, doors, blockers, or other LPC exit mutation.
- Runtime room path remains exact and duplicate Chinese room names are not used as authority.

## Round 2 — zero-manual custom map seed generation
- Added tools/generate_custom_map_graph.py.
- It scans custom LPC ROOM files and literal exits, including __DIR__ destinations.
- Generated seed: 32 custom rooms / 64 exits in this snapshot.
- The JSON is now reproducible from LPC source rather than a per-area hand-maintained map.
- Runtime WebHUD remains authoritative over generated seed data.

## Round 3 — regression / five-walker source test
- Added tools/test_five_walkers_runtime_map.py.
- Five virtual source-level walkers each traversed the Gao Shen route forward/back three times.
- 270 directional transitions passed.
- Dynamic-exit audit and JavaScript syntax check passed.
- IMPORTANT: this environment still has no running Neolith/TELNET driver, so this is not claimed as live multiplayer acceptance. Live five-player testing remains required when runtime is available.

## Old Pine archaeology boundary
The early mudchina/es2 /d/oldpine material remains archaeological/version-diff input only. It has NOT been silently merged into current gameplay. Current Gao Shen path01..path10 is unchanged.
