# Old Pine recovery — large batch round 1/3

Status: archaeological/version-diff research only. No early archive gameplay was merged into current taedlar-based playable content.

## Inventory locked
- 41 room code files
- 14 NPC code files (+ archival/support npc.1 and spy.old)
- 11 object code files (+ obj.1)

## NPC deep-audit progress
All 14 NPC source files were individually opened/inspected in the early mudchina/es2 archive. Confirmed examples and special behavior now tracked:
- bandit: 土匪探哨, exp 600, score 60, sword/parry/dodge 10, aggressive, short_sword, silver 3.
- bandit_chief: 土匪老大, exp 6000, score 700, blade 60/parry 50/dodge 50, combat chat, temporary apply compensation, start_help callback.
- bandit_commander: 常老大 / 老松寨寨主 / 潑風刀王, exp 260000, score 17000, force 60/blade 100/parry 100/dodge 70, bamboo_pipe carrier.
- fat_bandit: combat callback call_for_help; this must be traced to its spawned/helper NPC and room behavior before restoration.
- maniac: 瘋老頭子, exp 40000, score 8000, force/spells/necromancy setup; special combat behavior requires dependency audit.
- spy: 黑衣人, throwing loadout and killed_enemy -> dissolve chain; source references black_cloth which is NOT in the oldpine obj inventory and therefore is an external/missing dependency to resolve.
- venomsnake: 金銀花蛇, exp 30000, hit_ob applies snake_poison condition.
- wolf_dog: 狼狗, exp 10000, aggressive animal combat applies.
- butterfly: peaceful ambient animal, exp 100, score 10.
- remaining individually inspected: bandit_guard, bandit_leader, serpent, skeleton, tall_bandit.

## Object deep-audit progress
All 11 object source files were individually opened/inspected. bamboo_pipe is confirmed active gameplay: play/blow calls environment(player)->pipe_notify(). Other object files are equipment/book/throwing-weapon dependencies and remain version-diff inputs until consumers are fully mapped.

## New blockers/dependencies found this round
1. spy.c references __DIR__"obj/black_cloth", but oldpine/obj inventory contains black_suit.c, not black_cloth.c. Do not silently rename/substitute.
2. spy.c also references global /obj/dust. This is an external dependency, not an oldpine-local object.
3. maniac uses necromancy mapping; skill/daemon availability must be checked against the current canonical taedlar source before any restoration.
4. fat_bandit call_for_help and bandit_chief start_help are cross-NPC behavior and need call-chain tracing.
5. bamboo_pipe assumes current environment implements pipe_notify(); it must only be used where that callback exists or compatibility behavior is defined by original source.

## Merge boundary
Current custom path01..path10 and Gao Shen are unchanged. Preferred future branch near path08 remains a plan only.
