# v3.0 WebMUD compatibility pass

This pass keeps the canonical ES2 gameplay data and rules in `source/upstream/mudlib`, while modernizing only transport/presentation and persistence compatibility needed for browser play.

## Numbered choice menus

All current LOGIN_D choice menus are read through ordinary line input. The shared `feature/user/input.c::input_prompt()` renderer displays option mappings as vertical numbered lists. The player enters `1`, `2`, `3`, ... and presses Enter. This replaces the browser-hostile `get_char()` + VT100 cursor interaction for login/character creation choices without changing the underlying canonical choices.

Examples covered include new-account confirmation, relogin/reincarnation confirmations, race, gender, and final character confirmation. `cursor_translate()` also accepts numeric option indices for compatibility.

This change also removes the stray single-character/newline interaction that could make the first password setup appear to fail after a `get_char()` confirmation.

## Persistence

`securityd.c` now permits `assure_file()` to create only the canonical first-letter directories under `/data/user`, `/data/login`, and `/data/mail` for the current player's own euid. The rule is path-component based and does not grant general `/data` write access.

Packaged deployments preserve the three persistence roots with `.keep` placeholders. `START_ES2.bat` also creates them defensively before launch.

`obj/user.c::net_dead()` now saves both the player body and login/link object immediately on disconnect. The original delayed `user_dump()` / quit path remains as a second safety net. Normal `quit` already saves both objects in the canonical mudlib.

## One-click Windows start

Run `START_ES2.bat` from the project root. It opens Neolith and the Node WebMUD bridge in separate windows and then opens `http://127.0.0.1:8080`.
