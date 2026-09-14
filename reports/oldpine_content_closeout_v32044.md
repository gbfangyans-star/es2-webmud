# Old Pine content closeout — v3.20.44

Status: CONTENT CLOSED (source-level), with four explicit compatibility blockers retained as isolated follow-up work.

## Closure boundary
- Recovered Old Pine room set: 41/41 LPC rooms present.
- World integration: current path08 branch to recovered npath1 retained; Gao-Shen east branch retained.
- Runtime-map contract: LPC exits remain authoritative; dynamic cave/pine maze behavior remains runtime-driven and maze concealment remains enabled.
- Recovered mechanics retained: tree route, vine fall/success branch, cave maze, Cave5 burial/reward chain, waterfall/riverbank/lake/cliffs, pine maze, keep ambush, reset reopening, bamboo-pipe callback.
- Recovered placements retained for source-supported NPCs/items.

## Explicit compatibility backlog (does not block content closeout)
1. spy -> black_cloth: canonical dependency absent; black_suit is not substituted.
2. maniac -> necromancy: canonical implementation absent.
3. venomsnake -> snake_poison: canonical condition absent.
4. parrybook study adapter: legacy contract preserved, but current F_STUDY semantics differ; no invented adapter enabled.

## Acceptance boundary
This closes the Old Pine CONTENT layer only. Live Neolith/TELNET acceptance remains pending because no runnable Neolith driver is available in this environment. Source-level walker/audit results must not be represented as live-player acceptance.
