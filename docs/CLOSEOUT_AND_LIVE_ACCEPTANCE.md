# Closeout and Live Acceptance

v2.6 tightens the last mile.

## Movement
A captured `go` command is no longer enough for acceptance. `verify_movement_transition.mjs` requires:
1. a captured `look` before movement,
2. a `go <direction>` response with no exact canonical failure,
3. a captured `look` after movement,
4. different normalized before/after raw output.

This is stronger observational runtime evidence. It still does not make the browser authoritative.

## Runtime evidence
The runtime bundle validator now verifies hashes plus semantic minimums:
- source status JSON says `ok`
- runtime smoke JSON says `ok`
- canonical login prompt observed
- exact canonical reconnect marker observed
- movement/combat transcripts are substantive

## Closeout
`closeout_windows.ps1` packages and validates the captured session, runs the final campaign gate, and builds a human-readable dashboard.
