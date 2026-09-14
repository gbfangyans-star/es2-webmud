# Equipment and Combat Index

v0.8 keeps gameplay execution in LPC and indexes only source-visible structure.

## Equipment
Repository armor objects can define `wear_as` plus `apply_armor/<slot>` mappings. The index now records both independently, so an audit can detect a source mismatch without simulating armor. Setup calls such as `setup_cloth()` and `setup_head_eq()` are also indexed as source traits.

## Combat-facing source
`combat_core_index.json` identifies files that call attack, defense, damage, weapon, armor, skill, condition, death, or busy/action functions. It does not calculate results.

## NPC combat profile
`combat_npc_index.json` gathers only data found in each NPC source: level, race/class, attributes, stat maximums, skills, skill mappings, equipment references and combat-facing calls.

## Browser HUD
The player page now mirrors the raw ES2 output for `score`, `skills`, and `inventory` in a side panel. The raw response remains visible. For `score` only, v0.8 additionally derives a convenience HUD from the exact fields emitted by the repository's `cmds/usr/score.c`: level, HP (形體), gin (精), kee (氣), sen (神), food, water, and fatigue. The values still come from the live ES2 command response; the browser does not calculate game state.

## Source-only invariant
No combat constants, equipment values, NPC numbers, or skill rules are imported from any other repository, old project, wiki, or guide.
