# Multiplayer live-test design audit — v3.19.2

The project distinguishes **STATIC**, **LIVE**, **ASSISTED LIVE**, and **WITHHELD DESTRUCTIVE** gates. A launcher must never imply a real runtime PASS when it only scanned source code.

## Windows/Neolith evidence already proven

See `MULTIPLAYER_ACCEPTANCE_LEDGER.json`. The accepted live chain includes two real logins, bidirectional tell, concurrent save integrity, abrupt reconnect, same-room visibility/say, team handshake/chat, follow through a canonical exit, and shared-room broadcast. The inn NPC test proved the canonical `no_fight` rule was applied consistently; it did **not** prove actual combat start.

## Remaining gates and safety policy

| Gate | Class | Automatic destructive action | Design decision |
|---|---|---:|---|
| Canonical combat/team contracts | STATIC | No | `CHECK_MULTIPLAYER_COMBAT.bat` is explicitly STATIC ONLY. |
| Mutual player `fight` | ASSISTED LIVE | No `kill` | Preferred live combat gate. Requires explicit `TYPE PVP FIGHT`, same room, mutual consent, then `halt` both. |
| Shared real NPC combat | ASSISTED LIVE / RISKY | Tool sends no `kill`, NPC may retaliate lethally | No longer described as non-lethal. Requires `TYPE RISKY FIGHT`; use only when the operator accepts the risk. |
| Death/corpse/revival | WITHHELD DESTRUCTIVE | Would require death | Static only until a disposable/safe scenario is explicitly approved. |
| Ground item contention | ASSISTED LIVE | No spawn | Uses only a visible canonical object. PASS requires exactly one contender to get the canonical post-move `get` failure, proving a single winner. |
| Guard | LIVE conditional | No | Level restriction is CHECK/SKIP, never hard failure. |
| Restart persistence | ASSISTED | No process kill | BEFORE/AFTER snapshots only. Both test characters must be saved and offline before BEFORE snapshot; operator controls restart. |
| Neolith storm | LIVE infrastructure | Connections only | Separate from character correctness gates and runs last. |

## Design corrections in v3.19.0

1. The previous NPC combat tool could report PASS merely because both sessions received non-empty command output, even when the room said `這裡禁止戰鬥`. That is corrected: rejection/no combat is CONDITION NOT MET, never combat PASS.
2. The old label "non-lethal NPC fight" was unsafe. Canonical `fight.c` can call `kill_ob()` when the NPC is non-civilized. The tool and launcher now say **potentially risky**.
3. Added `CHECK_MULTIPLAYER_PVP_FIGHT_LIVE.bat`, a lower-risk live combat gate based on canonical player mutual-consent `fight`, never `kill`, followed by `halt` cleanup.
4. Shared-world NPC probing no longer sends `fight`; it only checks both sessions can address the same visible NPC. Combat belongs in dedicated tools.
5. Ground-item contention no longer tries to infer ownership from `inventory` text, which prints object short descriptions rather than IDs. It now uses exact canonical `get.c` loser failure behavior and only records PASS when there is exactly one loser.
6. Restart acceptance now requires characters to be offline before the BEFORE snapshot so a later hash change is meaningful rather than a legitimate disconnect save.

## Release rule

A result may be called **LIVE PASS** only if real Neolith was contacted and the tested canonical interaction actually occurred. `SKIP`, room rejection, unmet level, or NPC refusal are never promoted to PASS. Static source audits are evidence about contracts, not substitutes for runtime acceptance.

## Evidence freshness rule (v3.19.0)

Live evidence is tied to gate-scoped fingerprints of the bridge/canonical implementation. Tooling, documentation, generated reports, and Web UI styling are intentionally excluded from these fingerprints. This prevents pointless re-testing after non-runtime edits while remaining conservative: changing any implementing file makes the relevant prior live evidence stale. Fingerprint freshness never upgrades a pending gate to PASS.

The offline development gate is deliberately separate from live certification. It can be run repeatedly during development without passwords or a real Neolith host, and its report contains `liveAcceptanceClaimed: false` by contract.

## Offline fault matrix and live-evidence carry-forward (v3.19.1)

`CHECK_MULTIPLAYER_FAULTS.bat` runs a fake-MUD-only bridge fault matrix: backend unavailable, backend disconnect, abrupt browser disconnect, one-session backend failure isolation, and oversized WebSocket payload containment. It never contacts real Neolith and cannot create a live gameplay PASS.

`multiplayer_evidence_carryforward.py` is fail-closed for already accepted live gates. If a bridge/canonical implementation file covered by recorded Windows evidence changes, the offline gate reports that evidence as stale and exits non-zero. Pending or withheld gates are never promoted by fingerprints.
