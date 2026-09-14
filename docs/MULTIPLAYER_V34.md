# v3.4 Multiplayer bridge foundation

This layer changes transport/runtime handling only. Gameplay remains authoritative in the canonical ES2 mudlib running under Neolith.

## Invariants
- One browser WebSocket creates one dedicated TCP connection to Neolith.
- Session byte counters, TCP state and heartbeat state are per connection.
- No player state is shared in browser storage or the Node bridge.
- Canonical player persistence remains `/data/login/<initial>/<id>.o` and `/data/user/<initial>/<id>.o`.
- Save-directory permission remains scoped to the same player's euid and first-letter shard.

## v3.4 hardening
- `MAX_SESSIONS` defaults to 200 and can be overridden by environment variable.
- New connections over capacity are rejected with WebSocket close code 1013.
- MUD TCP connection timeout defaults to 10 seconds.
- TCP_NODELAY is enabled for interactive command traffic.
- WebSocket ping/pong heartbeat terminates stale browser sockets.
- `/api/sessions` is localhost-only because it includes connection metadata.
- `/api/online-count` exposes only count and configured capacity.

## Automated isolation check
`node tests/test_multiplayer_isolation_v34.mjs`

The test starts a fake local TCP MUD plus the real Node bridge, opens eight WebSocket clients, and proves that all eight receive different TCP session IDs and no client's command text appears in another client's stream.

This does not replace the Windows/Neolith acceptance test. The next live stage is multiple real ES2 accounts connected concurrently, moving/chatting/fighting and saving/disconnecting at the same time.
