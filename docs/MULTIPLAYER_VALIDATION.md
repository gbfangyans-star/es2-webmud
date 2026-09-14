# Multiplayer Validation

v2.1 formalizes multiplayer testing.

The bridge architecture is one WebSocket connection -> one independent TCP connection to Neolith. `audit_multiplayer_bridge.py` checks that this invariant still exists in `server/index.js`.

`multiplayer_probe.mjs` opens many browser-side WebSocket sessions concurrently and expects every one to receive the bridge's `[ES2 connected]` marker. It does not send credentials or gameplay commands.

Real acceptance still requires separate test accounts on a live canonical ES2 runtime and must prove:
- account/session isolation
- same-room visibility
- chat visibility
- movement independence
- combat independence
- disconnect/reconnect behavior
- repeated 10/50-client concurrency runs

A successful concurrent connection probe is not proof that gameplay interaction is correct.
