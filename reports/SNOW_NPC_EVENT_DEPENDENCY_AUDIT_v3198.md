# Snow NPC event dependency audit — v3.19.8

Scope: current canonical `source/upstream/mudlib/d/snow`, with website cross-check restricted to non-legacy `es2.xor.tw` material. No `/legacy-ES2` data is used.

## Result

The 23 Snow NPC source files are present. The useful distinction is not NPC count but whether their event dependencies close inside the current source tree.

### Closed/local chains

- Innkeeper protection: `innkeeper.c` dynamically creates `patrol.c` when attacked. Patrol is therefore not a missing fixed room NPC.
- Foreman freight work: `store.c` places `npc/obj/wagon`; `foreman.c` creates `crate`; `wagon.c` accumulates `wage_deserved`; foreman pays `/obj/money/coin`. Required source files exist.
- Hairpin → girl → invitation: `ruin1.c` creates `hairpin` during the source-defined time window; `girl.c` accepts it and can create/drop `invitation`. Required Snow source files exist.
- Waiter food service: dumpling, manto, pork, and roast chicken merchandise paths exist.
- Herbalist shop: black_pill, boar_berry, wild_ginseng, dragon_saliva medication files exist.
- Yu shop/note: merchandise paths and `npc/obj/note.c` exist; low-level payment path can create the note.

### Source-present but externally blocked / incomplete in current tree

- Guard → Snowkeep: `guard.c` consumes an `invitation` and moves the player to `/d/snowkeep/entrance`. The current project does **not** contain `d/snowkeep/entrance.c`. The Snow-side invitation chain exists, but traversal cannot close in the current world tree.
- Smith arrow conversion: `smith.c` accepts an object identifying as `lo iron` and creates `npc/obj/arrow.c`. The arrow exists, but no `lo iron` producer/object was found anywhere in the current canonical mudlib. Do not invent one.
- Abao / gammer `try/fon` chain: all `try/fon` references in the current canonical tree are confined to `child.c` and `gammer.c`. Several states are read that have no producer elsewhere in the current tree (notably the entry required for the food/follow branch). Treat the larger quest as incomplete/manual-review, not as a Snow-only closed quest.

### Important source behavior

- `inn_staff_room.c` is operationally referenced by `innkeeper.c` for opening/closing movement and should not be treated as an arbitrary extra room.
- `hairpin_quest` is queried by `girl.c`, but no setter was found in the current canonical tree. The hairpin hand-in itself removes the immediate killer relationship; the broader state is incomplete/manual-review.
- `note.c` itself describes routes/areas beyond the currently present Snow tree. This is source evidence of intended wider world context, not permission to fabricate those areas.

## Classification

- NPC source presence: 23/23
- Confirmed locally closed event/service groups: 6
- Confirmed current-tree external blockers: 2 (`/d/snowkeep/entrance`, `lo iron` source)
- Confirmed incomplete/manual-review state chain: Abao/gammer `try/fon`
- Additional manual-review state: `hairpin_quest` setter absent

No canonical gameplay LPC was modified in this audit.
