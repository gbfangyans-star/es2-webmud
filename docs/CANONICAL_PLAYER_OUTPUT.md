# Canonical Player Output Parsing

v1.6 upgrades three browser observations from generic parsing to source-confirmed parsing using only `taedlar/es2_mudlib` main branch.

## `hp`
`cmds/usr/hp.c` prints seven pairs: HP, gin, kee, sen, food, water and fatigue. HP/gin/kee/sen use current/effective values; food/water/fatigue use current/maximum values.

## `skills`
`cmds/usr/skills.c` prints a Chinese skill label, source ID, qualitative level description and effective numeric level. Enabled/mapped basic skills print the mapped skill Chinese name and mapped ID; an optional signed delta shows the difference between effective and stored base-skill level. v1.6 reconstructs raw base level only when that delta is explicitly present.

## `inventory`
`cmds/usr/inventory.c` prints encumbrance percentage in the header. Each inventory line uses `ˇ` for an equipped object and `◎` for keep. It does not expose the canonical equipment slot path.

## Equipment slot boundary
`feature/equip.c` stores equipment internally as `armor/<part>` or `weapon/<skill>` and sets the item's `equipped` property to that path. Because `inventory` only exposes the equipped marker, the browser must not infer slot names from item names.
