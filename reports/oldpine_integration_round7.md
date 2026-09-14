# Old Pine integration round 7

- Staged cave1..cave5 as LPC under custom/oldpine_recovered.
- cave1..4 preserve reset-time randomized exits and fixed anchors; all tagged map/mode=maze.
- cave5 now preserves wall lore, skeleton burial, KAR roll, high-roll parrybook drop, mid/low fall to waterfall.
- Corrected prior archaeology note: high roll (>25) returns immediately after dropping parrybook and does NOT fall to waterfall.
- Staged skeleton ITEM and parrybook legacy object metadata. Modern study adapter remains pending; book can exist as reward but study semantics are not yet claimed compatible.
- Staged pine1..pine7 dynamic maze topology with fixed anchors and map/mode=maze. NPC spawns remain withheld until their dependencies are ported.
- Pine maze remains staging-only because keep1 and cliffdown are not yet in recovered room set.
