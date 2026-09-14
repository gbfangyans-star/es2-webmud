# Web transport

The browser is deliberately not a gameplay engine.

`browser -> WebSocket /mud -> TCP -> Neolith/ES2`

v0.5 moves Telnet IAC negotiation handling into the bridge. Protocol bytes are stripped before browser rendering and unsupported Telnet options are rejected cleanly. ANSI SGR rendering stays in the browser. This prevents Telnet control bytes from appearing as garbage while leaving all ES2 commands and combat behavior untouched.

The bridge also records per-session age and byte counts for local diagnostics at `/status.html`. It does not persist player content.
