# v3.8 multiplayer work

This round deepens multiplayer validation without replacing canonical ES2 gameplay.

## New static contracts
`tools/audit_multiplayer_deep.py` verifies canonical source contracts for same-account takeover/reconnect, multi-opponent combat arrays, reciprocal fight/kill registration, attacker identity in damage, room/private messaging, online enumeration, first-letter per-player save namespaces, clean/disconnect saves, reconnect location, and ground-item contention through object movement.

## New live acceptance
`CHECK_LIVE_MULTIPLAYER.bat` logs in **two existing characters simultaneously** directly against Neolith. Passwords use hidden terminal input and are not saved. It checks two concurrent real logins, bidirectional `tell`, and near-simultaneous canonical `save` commands. `who` is reported too, but can be filtered by canonical level/visibility rules.

The tool intentionally does not create characters or inject save files.

## LAN staging
`START_ES2_LAN.bat` binds only the WebMUD bridge to `0.0.0.0:8080` so another device on the same trusted home/Wi-Fi network can test the browser. Neolith remains on its configured endpoint. This script does **not** configure public Internet exposure, router forwarding, TLS, DNS, or firewall rules.

Public Internet deployment remains a separate acceptance stage.
