# ES2 WebMUD multiplayer status — v3.19.2

## v3.19.0 safety/certification cleanup

No new gameplay data was added. The already observed inn NPC test is intentionally classified as **no-fight rule evidence**, not actual combat. Preferred remaining live combat acceptance is two-player mutual `fight` in a canonical combat-allowed room. NPC fight is now explicitly risky, destructive death/PK remains withheld, ground-item contention proof is stricter, and restart persistence requires offline-before-snapshot.


This report separates what is proven in the Web bridge from what still requires a live Windows Neolith test.

## Proven by automated tests
- One WebSocket maps to one TCP connection to Neolith.
- Concurrent bridge sessions are isolated; cross-talk tests cover 8 and 50 simulated clients.
- Capacity, heartbeat, slow-client and cleanup protections are present.
- Canonical ES2 source contains room speech (`say`), private player messaging (`tell`), online-player enumeration (`who`), clean-quit saving, link-dead saving and reconnect handling.

## Canonical multiplayer lifecycle
- `say`: sends to other objects in the same room and calls their `relay_say` hook.
- `tell`: resolves an online player with `find_player`, checks interactivity/ignore rules, and sends directly to that player.
- `who`: enumerates live driver users and applies canonical visibility/level filters.
- `quit`: saves the link object and player body before destruction when `SAVE_USER` is enabled.
- unexpected disconnect: `obj/user.c::net_dead()` stops combat, records the last room, saves, then hands the link-dead player to LOGIN_D.
- reconnect: cancels the link-dead timeout and returns the player to the recorded last room.

## Still requires real Windows/Neolith acceptance
1. Two real characters log in simultaneously.
2. Both enter the same room and see each other's room messages.
3. `say` and `tell` work in both directions.
4. Both interact with the same NPC without session contamination.
5. Both save at nearly the same time; each canonical save file remains valid.
6. Player A uses `quit`; player B loses the browser/network abruptly.
7. Both reconnect and retain independent state/location according to canonical behavior.
8. Repeat with 10+ logged-in characters and then run a longer soak test.

Passing the static audit does not claim those live-driver tests have passed.


## v3.8 additions
- Deep static audit now covers same-account takeover, multi-opponent combat, attacker identity, per-player save sharding, and ground-item contention.
- `CHECK_LIVE_MULTIPLAYER.bat` can verify two real existing accounts without storing passwords.
- `START_ES2_LAN.bat` adds a same-LAN staging mode for phone/second-PC testing; it is explicitly not public Internet deployment.


## v3.9 additions
- Canonical audit extended to player-to-player `give`, no-drop/self safeguards, link-dead combat cleanup, void staging, room restoration, and get/drop object movement.
- `CHECK_LINKDEAD_RECONNECT.bat` performs a live two-account abrupt-disconnect/reconnect acceptance against the real Neolith driver.
- The live resilience test verifies messaging before disconnect, canonical reconnect recognition, messaging after reconnect, and both accounts saving afterward.
- No gameplay rule is reimplemented in the Web bridge; these checks exercise or audit the original ES2 mudlib contracts.

## v3.10 PvP / team / shared-combat audit

Added a source-locked audit for canonical ES2 multiplayer combat and team behavior. It verifies mutual-consent `fight`, player `kill` warning/reciprocal semantics, rejection of link-dead PvP targets, per-character multi-enemy state, same-room combat targeting, guard participation, two-party team formation, team-scoped chat, shared team membership state, quit cleanup, and enemy cleanup after room changes.

This is static canonical verification. It does **not** claim that real two-character Neolith combat has been executed in this build environment. Use the Windows live acceptance tools on the actual server for that gate.


## v3.11 death / corpse / PK / revival audit

Added `tools/audit_multiplayer_v311.py` and `CHECK_MULTIPLAYER_DEATH.bat`. The audit verifies canonical ES2 contracts for combat/team cleanup on death, corpse creation, inventory transfer into the corpse, corpse decay, killer attribution, PK penalties/records, NPC bounty attribution, corpse remains visibility, ghost loot restriction, living-to-ghost transition, ghost-to-mist transition, and temple revival. These are static source proofs only; real Windows Neolith multi-character death/loot/revival remains a live acceptance item.

## v3.12 live operations / soak gate

Added two live-driver gates that do not invent gameplay rules:
- `CHECK_MULTIPLAYER_SOAK.bat`: two existing accounts repeatedly exercise canonical `tell`, `hp`, concurrent `save`, and abrupt link-dead reconnect for a 10-minute default soak. Passwords remain in memory only; the optional JSON report contains no passwords.
- `CHECK_SAVE_INTEGRITY.bat`: performs concurrent canonical saves and verifies each player's sharded `/data/user/<initial>/<id>.o` and `/data/login/<initial>/<id>.o` files are present/non-empty with no orphan `.tmp` save files.

These are acceptance tools, not claims of results in this build environment. Real Windows Neolith execution is still required.


## v3.13 room / team / follow live gate

Multiplayer work remains the priority. Added `tools/audit_multiplayer_v313.py`, a 13-contract source-locked audit covering room-scoped speech, direct tells, follow movement, team handshake/chat, guard participation, and link-dead PvP rejection. Added `CHECK_MULTIPLAYER_ROOM.bat` for two real existing accounts. The live gate never teleports characters or invents a test room: the operator places both characters in the same real room, then the gate verifies room speech, team formation/chat, follow through an operator-selected real exit, and (when canonical level requirements permit) guard state. Passwords stay in memory.

This is deliberately separated from static proof. Until the Windows/Neolith live gate is run, v3.13 does not claim room/team/follow acceptance has passed on the user's machine.


## v3.14 shared-world contention / NPC live gate

Added a 13-contract canonical audit for shared ground-object ownership, player-to-player transfer safeguards, multi-opponent combat state, guard participation, and last-damage attribution. Added `CHECK_MULTIPLAYER_SHARED_WORLD.bat`, an operator-assisted real-Neolith gate for two existing characters in the same canonical room. It verifies room broadcast, optionally races both players for one already-existing ground object, optionally lets both address one already-existing NPC with `fight` (never escalates to `kill`), then performs concurrent per-character saves. The gate never spawns items/NPCs, teleports characters, or invents gameplay data.


## v3.15 resilience / save-collision gate

Added `CHECK_MULTIPLAYER_RESILIENCE.bat` and `tools/live_multiplayer_resilience.py`. The live gate uses two existing real characters and performs 20 waves of bidirectional tells plus simultaneous canonical saves, with an abrupt disconnect/reconnect every five waves. After each wave it checks both characters' sharded `/data/user` and `/data/login` files and rejects orphan `.tmp` files. It also scans only the newly appended portion of `mudlib/log/debug.log` for save-object/mkdir failures, so the historical Windows save-directory bug cannot silently pass. Passwords remain memory-only and the JSON report contains no passwords.

This is an executable Windows/Neolith acceptance gate, not a claim that it has already passed on the user's machine.


## v3.16 real-driver connection storm / churn gate

Added `CHECK_NEOLITH_STORM.bat` and `tools/live_neolith_storm.py`. The gate targets the actual Neolith TCP listener, not the Node bridge: five waves of 50 simultaneous connections (250 total) must each receive driver output, then a final post-storm connection must still receive the login banner. Only newly appended debug-log text is scanned for fatal resource failures. No account, password, NPC, item, or gameplay data is created. This complements the authenticated two-character resilience/save-collision gate rather than replacing it.

## v3.17 endurance / restart-persistence gate

Multiplayer remains the priority; no gameplay rules were moved into the Web layer. Added a 500-session bridge endurance regression (20 waves x 25 clients) that requires unique isolated TCP responses, zero cross-talk, and zero leaked active/connected sessions after churn. Added a two-phase real-Windows restart-persistence snapshot gate for two existing characters: BEFORE records sizes and SHA-256 hashes of each canonical `/data/user` and `/data/login` file, AFTER verifies a Neolith restart did not mutate/truncate those files or leave `.tmp` save artifacts. The restart gate deliberately does not auto-kill the driver; the operator controls the real server restart, avoiding accidental termination of unrelated processes.


## v3.18 unified multiplayer master gate

Added `CHECK_MULTIPLAYER_MASTER.bat` and `tools/multiplayer_master_gate.py`. One command now runs the accumulated canonical multiplayer audits, per-session bridge structural audit, 8-session isolation, 500-session bridge endurance, the real Neolith TCP storm, and the authenticated two-character tell/save/link-dead/reconnect resilience gate. It writes `multiplayer_master_report.json` with explicit PASS/FAIL stages. Room/team/follow/guard, shared-world NPC/item contention, destructive combat/death, and controlled server-restart persistence remain clearly marked operator-assisted gates rather than being faked by the harness. Passwords remain memory-only.


## v3.18.3 live-test corrections
- Login IDs now support 3–12 lowercase letters and digits (a-z, 0-9), including IDs such as `test01`.
- The authenticated multiplayer resilience gate uses the same ID rule and no longer rejects digit-bearing accounts before password entry.
- The landing art now uses its native 1312×1199 aspect ratio; the invisible click target is aligned over the baked-in gold 「進入遊戲」 button in the image.
- These are project compatibility/UI changes; canonical gameplay remains Neolith + ES2 mudlib authoritative.


## v3.18.3 tell live-gate correction

- Canonical `tell.c` defines `MIN_TELL_INTERVAL` as 3 seconds.
- The previous live harness could issue the next tell inside that anti-spam window, conflating canonical rate limiting with delivery failure.
- v3.18.3 paces each sender to 3.35 seconds minimum between tells.
- Delivery is accepted only when the unique token is observed on the recipient connection.
- Sender output is also captured for diagnosis.
- Failure reports classify canonical cooldown, missing player, link-dead target and ignore states.
- Passwords are still memory-only and never included in reports.
- No ES2 gameplay source was changed for this fix.


## v3.18.8 live visibility hardening
- Uses the returned live-test tree and preserves `wolfer` / `wolfer1` save files.
- Authenticated resilience now emits immediate login status and per-wave progress.
- Login is bounded to 40 seconds; tell observation is bounded to 4.25 seconds per delivery attempt.
- Tell sender/recipient sockets are observed interleaved rather than sequentially, avoiding misleading multi-second silent waits.
- Browser login-banner presentation now uses the user-approved centered cinematic title artwork.


## v3.18.8 live blocker fixes
- Fixed canonical local `tell`/`reply` load failure caused by stale missing `<net/dns.h>` / `GTELL` dependency; absent inter-MUD branch is compile-guarded, local behavior remains source-defined.
- START_ES2 is version-safe and refuses to mix old/new WebMUD or Neolith processes on ports 8080/4000.
- Master verifies running build identity and tests authenticated multiplayer before the heavy Neolith storm.
- Browser login art is driven by the connection/login phase rather than fragile title-text matching.

## v3.18.8 live-test design hardening

The remaining multiplayer gates were audited before further Windows testing. Launchers are now explicitly classified as STATIC, LIVE, or ASSISTED. The old combat/death launchers no longer imply live behavior when they only scan canonical source. A separate `CHECK_MULTIPLAYER_COMBAT_LIVE.bat` was added for a real, operator-selected canonical NPC; it never sends `kill`, requires an exact confirmation phrase before `fight`, and issues `halt` to both test characters after a short observation window. Restart snapshots now report the current release version instead of the stale `3.17.0` literal. See `MULTIPLAYER_TEST_DESIGN.md` and `reports/multiplayer_test_design_audit.json`.

## v3.19.0 evidence freshness / offline gate

This release adds a conservative evidence-freshness layer so previously completed real Windows/Neolith acceptance is not needlessly repeated after tooling-only releases. `tools/multiplayer_evidence_fingerprint.py` hashes only the bridge/canonical files that materially implement each live gate. A fingerprint match can keep an existing live PASS fresh; it can never create a new live PASS. If an implementing file changes, the affected evidence is marked stale and must be revalidated on the real Windows/Neolith host.

`CHECK_MULTIPLAYER_OFFLINE.bat` / `tools/multiplayer_offline_gate.py` now consolidate all work that can safely run without the user's Windows runtime: canonical multiplayer audits, live-test design audit, bridge structural audit, 8-session isolation, capacity boundary, churn/stress, 500-session endurance, evidence fingerprinting, and generation of the next certification plan. Its PASS is explicitly **OFFLINE ONLY** and never substitutes for authenticated gameplay evidence.

The machine-readable reports are `reports/multiplayer_evidence_fingerprint.json`, `reports/multiplayer_certification_plan.json`, and `reports/multiplayer_offline_gate.json`.

## v3.19.1 offline fault containment

Added a fake-MUD bridge fault matrix covering backend refusal, backend disconnect, abrupt browser disconnect, per-session backend failure isolation, and oversized WebSocket payload containment. All five scenarios pass locally. The offline gate now also runs a fail-closed carry-forward verifier for previously accepted Windows/Neolith live evidence. No bridge implementation or canonical gameplay file was changed in this release, so the recorded transport/login/room live evidence remains fresh; pending combat/item/restart gates remain pending.
