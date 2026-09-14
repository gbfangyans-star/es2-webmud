# Canonical content patch transaction

This is the guarded write path for future bulk content work. It does **not** invent gameplay data and accepts only explicit replacement text prepared from the approved source set.

A patch plan is JSON with `sourceBoundary: "taedlar/es2_mudlib only"` and a non-empty `files` array. Every item contains `path`, `expectedBeforeSha256`, and `replacementText`.

`python tools/content_patch_transaction.py plan.json` performs a dry-run only. Add `--apply` for an explicit write.

Safety properties: canonical-path containment, exact pre-write SHA guard, duplicate-path rejection, UTF-8 encoding, pre-write byte backups, atomic file replacement, post-write SHA verification, and best-effort rollback if a batch write fails. It never updates the sealed baseline automatically. A real content batch must still run impact/catalog/regression/release gates before sealing.


## v3.20.8
- Web-only: context ANSI/parser isolation, aligned combat HUD, server-fed inventory action panel.
- Approved custom LPC: `cmds/usr/webhud.c` extended with read-only inventory metadata.
- Approved custom LPC: `custom/test/obj/infinite_100_gold.c` adds repeatable 100-gold testing fixture.
- Approved canonical-room modification: `d/snow/inn_hall.c` spawns the testing fixture.

## v3.20.10
- WebMUD terminal blank-line compaction retained.
- Added center-column CHAT/TELL-only mirror pane; SAY and other channels excluded.


### v3.20.13
- `web/app.js`: silent HUD poll cleanup; side role HUD accepts LPC WebHUD self-state.
- `cmds/usr/webhud.c`: always emits SELF state and appends level + food/water/fatigue for browser-only status display.
- `cmds/usr/score.c`: CUSTOM PRESENTATION PATCH replacing `%` / `>` tri-bar glyphs with `■` / `□`; formulas unchanged.

## v3.20.13 approved custom changes
- `chat` is exempt from the original level-2 public-channel gate; other public channels keep the gate.
- Woochan food is fixed at `0/0`, while water remains canonical and hunger no longer blocks Woochan healing.
- `score` gin/kee/sen tri-bars are 25 cells.
- WebMUD combat HUD polling no longer waits for a classic prompt, refreshes every 1 second, and kicks an 80 ms refresh after normal incoming game/combat text.

### v3.20.14
- CUSTOM MAP: 草棚 southeast -> 老松林 10 格小路，拓撲依使用者圖片。
- CUSTOM LEGACY NPC: 高慎放置於最東端小路；暫不實作技能教授。

### v3.20.15
- CUSTOM LEGACY TIGER SCHOOL: 高慎 now accepts apprentices directly with no prerequisite.
- Teacher table landed from user-provided legacy output: unarmed/parry/dodge/tiger-steps/blade/twohanded blade/secondhand blade/force/tiger force 120; tiger blade 140.
- Learning gates: force and tiger force require character Lv.15; tiger blade requires tiger force Lv.30.
- No combat formula/action for tiger force, tiger blade, or tiger-steps was invented; those remain source-research blockers.


## v3.20.16 — CUSTOM Zhenwu Camp map/NPC placement
- User-supplied map images define the Zhenwu Camp topology and NPC placement.
- Added 14 distinct parade-ground rooms, big tent, shed area, camp edge and Zhenwu double gate.
- Snow south shed (`d/snow/sgate.c`) west exit now connects to the Zhenwu gate, replacing the upstream commented missing `/d/newcamp/gate` destination with this approved custom reconstruction.
- Added descriptive NPC shells only: 2 Zhenwu soldiers, 4 target stakes, recruiter Lu Xinien, and general Mee-pei.
- No `enlist`, military advancement, teacher skills, combat stats, quest rules, or rewards were invented. Those remain deferred pending reliable source data.

## v3.20.17 — Custom Home Bedroom
- User-approved CUSTOM HOME extension; not canonical ES2 content.
- Added a development notice board to the private home hall.
- The board now owns room-type selection; first available type: `寢室` (`bedroom`).
- Existing progressive room price remains: room N costs N × 10 gold, maximum 10 rooms.
- Room type is persisted per player under `custom_home/room_type/<n>`.
- Added private bedroom and a fixed bed object.
- `rest bed` / `上床` starts bed rest; `leave bed` / `下床` stops it.
- Every 60 seconds of uninterrupted bed rest restores current gin/kee/sen by 10% of each maximum, capped at the effective value (and never above maximum).
- Leaving the bedroom or entering combat stops/invalidates bed rest.

### v3.20.18 CUSTOM HOME SYSTEM
- Reworked `custom/home/obj/development_board.c` into a numbered room-development menu.
- Added dynamic next-room GOLD price display and selectable options 1-5.
- Enabled bedroom (1) and study room (2); 3-5 remain explicit placeholders.
- Added `custom/home/room/study_room.c`.
- Modified canonical `feature/study.c` only to read an explicit room-side CUSTOM study efficiency multiplier. A home study room sets 120%, leaving canonical requirements/caps/cost/fatigue semantics unchanged.
- Updated home hall room-type dispatch to instantiate study rooms.

### v3.20.19 CUSTOM ECONOMY CONVENIENCE
- User-approved custom change: gold, silver and coin now have zero carried weight.
- `feature/char/finance.c` now evaluates spending by total carried monetary value rather than requiring exact denominations.
- Successful payment rewrites the remaining value into canonical gold/silver/coin denominations, equivalent to the merchant returning exact change.
- The legacy `can_afford()==2` "merchant cannot make change" state is retired; players no longer need to visit an exchange point just to break money for purchases.
- Currency values remain unchanged: gold 10000, silver 100, coin 1.

### v3.20.20 HOME RUNTIME / COMMAND ARBITRATION FIX
- Fixed CUSTOM HOME ITEM compatibility with the bundled ES2 mudlib/Neolith runtime:
  - removed invalid `#include <object.h>` from `development_board.c` and `bed.c`;
  - removed invalid parent `::init()` calls from ITEM objects because `/std/item` has no `init()`.
- Audited local home verbs for command shadowing. The teleporter now yields the canonical wizard `home` command while regular players retain `home` and `家園`.
- Internal browser `webhud` telemetry is excluded from the legacy `MAX_COMMAND_PER_SECOND` player-action budget.
- HUD refresh changed from 400 ms to 800 ms, with a 350 ms player-input priority window and debounced event refreshes, preventing telemetry bursts from competing with real commands.
- Added `tools/audit_home_runtime_compat.py` and expanded WebMUD audit coverage.

### v3.20.21 EXACT LOCAL MAP / CUSTOM AREA MAP
- Silent `webhud` now emits the exact `base_name(environment(me))` room path.
- The browser treats this exact LPC path as authoritative for the right-side local map; room-title parsing is fallback only and ambiguous titles are never guessed.
- Added `web/custom_map_graph.json` for approved CUSTOM areas (Old Pine, Zhenwu Camp, private home) and bridge edges to Snow.
- Verified `recall home` directly creates/binds/moves into `/custom/home/room/home_hall`; fighting/busy safety guards remain.

## v3.20.45 — Old Pine closeout release gate
- Froze recovered Old Pine LPC content with per-file SHA-256 fingerprints.
- Added a dedicated closeout release audit for 41 rooms, branch integration, critical mechanics and explicit blocker isolation.
- No guessed gameplay content was introduced.
- Live Neolith/TELNET acceptance remains pending.

## v3.20.56 HUD command routing
- Scene interaction and usable-item buttons now call the shared browser `send(command)` function.
- Removed direct per-button WebSocket sends and duplicate session-recorder calls from `bindCommandButtons()`.
- Preserved the user-provided upgrade formula workbook under `reference/user/升級公式.xlsx` for the next upgrade-system pass.

## v3.20.57
- Combat HUD bars reduced from 25 segments to 10 visual segments; underlying values/formulas unchanged.
- Bank deposit/withdraw/convert now accept both canonical English money ids and player-facing Chinese currency names (錢/文/文錢/銅錢, 銀/銀子/碎銀, 金/金子/黃金).
- Bank object assignment checks parenthesized to avoid ambiguous `!x = ...` expressions.


## v3.20.58 bank direct trace
- Traced command path through PLR_PATH -> /cmds/std/deposit|withdraw -> room BANK do_* functions.
- Found literal sign term `錢幣` was not normalized by v3.20.57.
- Replaced fragile `present("*_money")` lookup with canonical MONEY/money_id inventory resolution.
- Withdraw/convert now use a strict coin/silver/gold money factory instead of arbitrary path construction.
- Added literal Chinese usage examples to the bank sign.
