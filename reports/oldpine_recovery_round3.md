# Old Pine recovery — large batch round 3

Status: archaeological/version-diff research only. No early MudChina room/NPC gameplay has been merged into the taedlar-based playable world.

## Newly closed mechanics
- cave5 is a terminal/special cave with eastdown -> waterfall, one skeleton, wall lore, and `bury skeleton`.
- bury removes the skeleton, rolls `random(kar + 10)`, and always drops the player to waterfall afterward.
- if roll >25 it creates `npc/obj/parrybook` in cave5; if >20 only paper fragments are described; otherwise no book reward.
- wall lore identifies 南危水 and explicitly tells the player to bury the remains for a parry/dueling-method reward.
- IMPORTANT blocker: reward path `d/oldpine/npc/obj/parrybook` must be verified as present/compatible before restoration.

## Stone / cave entry
- path3 climb-up -> stone was already known.
- stone is a dead-end vertical staging room with one venomsnake.
- `climb down` -> cave1. Therefore the secret route feeds directly into the randomized cave maze.

## Tree layer fully closed
- clearing `climb pine` -> tree1.
- tree1: up -> tree2, down -> clearing; contains one spy.
- tree2: up -> tree3, down -> tree1; contains six butterflies.
- tree3: down -> tree2 only.
- This is a clean 3-room vertical layer and maps naturally to the new HUD layer model.

## Consolidated topology
Surface: npath -> clearing -> east bridge / south slope branches.
Vertical tree: clearing <-> tree1 <-> tree2 <-> tree3.
Secret/cave route: epath2 vine success -> passage -> secrectpath1 -> path3 -> stone -> cave1..4 dynamic maze -> cave5 -> waterfall.
Water return: waterfall -> riverbank2 -> riverbank1 -> lake, with riverbank1 cliff climb back into cliff branch.
Keep route: dynamic pine maze -> pine2 -> keep1 -> keep2 -> keep3.

## Restoration classification
READY-AS-EVIDENCE: room topology, tree layer, stone transition, cave5 bury logic, keep ambush/pipe mechanism, vine success/failure, cliff/water chains.
BLOCKED: parrybook dependency/API, spy black_cloth mismatch, maniac necromancy, later Gao-Shen-era topology reconciliation.
VERSION-EVIDENCE-ONLY: commented external exits such as CHOYIN remnants.

## Merge boundary
Current playable custom path01..path10 and Gao Shen remain unchanged. The path08 branch proposal remains design-only.
