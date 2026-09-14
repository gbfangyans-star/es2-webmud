# Old Pine recovery — expanded large batch round 2/3

Status: archaeological/version-diff research only. Early mudchina/es2 material is NOT merged into current taedlar-based playable content.

## Scope completed this round
This round expands the oldpine recovery from file inventory into mechanics/topology extraction for the high-risk parts of the region: dynamic caves, dynamic pine maze, cliff traversal, waterfall/vine route, secret-passage route, tree branch, Old Pine Keep ambush, and external-link remnants.

## Dynamic topology confirmed
### Cave maze
- cave1..cave4 are reset-time dynamic rooms. Their exits are assigned with random() expressions, so a static browser graph cannot be authoritative for them.
- cave1 has north fixed to cave2 while several other directions randomize among cave rooms.
- cave2 fixes east to cave4 while the other directions randomize.
- cave5 is a special terminal cave rather than another generic random cell. It exits eastdown to waterfall and contains a skeleton plus wall/bury interactions.

### Pine maze
- pine1..pine7 are not a fixed planar map.
- pine2 has a fixed east exit to keep1; the remaining main directions are randomized among pine2..pine6.
- pine4 fixes north to pine5.
- pine5 fixes north to pine6.
- pine6 fixes west to pine7.
- pine7 adds southwest to cliffdown while the four cardinal directions remain randomized.
- Several pine rooms deliberately print disorientation text in valid_leave().

This makes runtime LPC exits mandatory for a precise nearby map.

## Surface hub and tree branch
- clearing has three ordinary exits: west -> npath3, north -> spath1, east -> epath1.
- `climb pine` moves the player from clearing to tree1.
- tree1 contains the spy NPC; tree2 and tree3 continue the vertical tree branch.
- clearing and tree1 also exchange room messages when players move/climb, so this is more than a cosmetic side path.

## East bridge / vine / waterfall chain
- epath2 is the mossy stone bridge with west -> epath1 and east -> epath3.
- `hold vine` / `grab vine` checks dodge.
- failure route: player falls to waterfall.
- success route: player climbs to passage.
- passage is the secret-passage entrance and has north -> secrectpath1, south -> waterfall.
- secrectpath1 continues north toward path3; path3 only returns south normally and has a climb action on the large stone.
- path3 `climb up` moves to stone.
- waterfall flows south through riverbank2 -> riverbank1 -> lake.
- riverbank1 supports `climb cliff`, linking this water route back into the cliff branch.

## Cliff branch
- cliff1 has no ordinary exits; `climb up` -> cliffside and `climb down` -> riverbank1.
- cliff2 has no ordinary exits; `climb up` -> cliffdown and `climb down` -> epath3.
- cliffdown is itself part of the randomized pine edge: cardinal exits randomize into pine rooms and northeast is fixed to pine7. Its `climb down` action goes to cliff2 (the original message text says “爬了上去”, a source inconsistency preserved as archaeology rather than silently corrected).
- cliffside currently has only north -> pine1; commented old exits remain evidence, not active topology.

## Old Pine Keep event chain
- pine2 east -> keep1.
- keep1 is the hidden keep entrance, with keep2 deeper inside.
- keep2 west -> keep1 and east -> keep3 under normal conditions.
- first east traversal while west is open triggers the ambush: west exit is deleted, keep1 east is deleted, five additional bandit guards are spawned and attack the triggering player.
- keep2 reset restores both sides of the entrance.
- keep2 `pipe_notify()` also restores the blocked entrance and emits the winch/stone-opening message.
- bamboo_pipe `play/blow` calls the current room's pipe_notify(), proving it is an active control object for compatible rooms rather than flavour equipment.

## Cave5 burial branch
- cave5 contains one skeleton and exposes `bury` plus a wall description callback.
- The full do_bury reward/requirement chain still needs a line-by-line dependency extraction before restoration. This remains open rather than guessed.

## Confirmed external/version remnants
- npath1 connects the early oldpine region back toward Snow in this archive lineage.
- spath4 contains the previously identified commented CHOYIN-era external link. Commented links are version evidence only and must not be made playable automatically.
- epath3 description clearly represents a forest exit / cliff-boardwalk boundary, so it is a major candidate for version-diff comparison against later maps.

## Compatibility blockers still open
1. cave5 bury reward/dependencies.
2. exact tree1/tree2/tree3 ordinary exits and any fall/damage logic must be fully captured before port.
3. exact stone room behaviour and its NPC/object interactions.
4. fat_bandit -> bandit_chief help chain and all helper spawning semantics.
5. spy black_cloth mismatch and /obj/dust external dependency.
6. maniac necromancy dependency against current taedlar skill availability.
7. later Gao Shen-era oldpine vs early archive topology: do not merge until room-by-room diff is complete.

## Merge boundary
Current custom path01..path10 and Gao Shen are unchanged. Preferred future branch near path08 remains only a design candidate.

## Cross-NPC callback resolved this round
The fat_bandit -> bandit_chief help chain is now fully traced in the early source:
- fat_bandit combat chat can invoke `call_for_help()`.
- it refuses to call twice (`called_help`) and refuses if a bandit chief is already present.
- otherwise it sets `called_help`, shouts for help, creates one `bandit_chief`, moves it into the current room, and invokes `start_help()` on that chief.
- bandit_chief `start_help()` is presentation/dialogue only; the source excerpt does not itself force an immediate kill_ob call. Do not invent additional aggression beyond the NPC's own aggressive attitude/core combat behavior.

## Current taedlar compatibility checks added this round
A direct scan of the current project canonical mudlib shows:
- no `necromancy` references were found in current LPC/include files. The early maniac therefore remains BLOCKED for faithful restoration until that old skill dependency is resolved or user explicitly authorizes a custom compatibility decision.
- no `black_cloth` references/files were found in the current canonical mudlib. The early spy dependency remains unresolved and must not be silently mapped to black_suit.
- `/obj/dust.c` DOES exist in the current canonical mudlib, so the spy's external dust dependency is available at path level. Its API/behaviour still needs compatibility verification before port.

This reduces one blocker (dust path existence) while strengthening two blockers (necromancy and black_cloth absent in current canonical source).
