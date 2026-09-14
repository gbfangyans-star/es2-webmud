# ES2 Combat Core Map (source-only)

Source boundary: only `taedlar/es2_mudlib` main.

## Character loop
`mudlib/std/char.c` is the character composition root. It inherits action, attack, attribute, combat, command, condition, dbase, finance, message, relation, move, name, score, skill, statistic and team features.

The character heartbeat is documented by upstream as running every two seconds. During a live combat heartbeat it cleans invalid enemies, continues a busy action if one exists, otherwise calls `attack()`. A shuffled slower tick later calls `update_condition()` and `regenerate()`.

## Attack dispatch
`feature/char/attack.c::attack()` selects an opponent if one was not supplied. If weapons are equipped, each mapped weapon skill is resolved with `skill_mapped()` and the weapon receives `attack_with(attacker, opponent, art)`. If no weapon is equipped, mapped `unarmed` is used through the skill daemon.

Opponent selection uses `intimidate` versus the target's `wittiness`, with the final attack opportunity clamped to 20%-80%. A charge target gets priority and an intimidate bonus; charging also penalizes the target's wittiness.

## Core ability formulas
From `feature/char/combat.c`:
- attack strength = `str * cor * 150 + kee * 30`
- defense strength = `str * cps * 150 + kee * 30`
- magic strength = `spi * spi * 150 + sen * 30`
- spell strength = `wis * wis * 150 + sen * 30`
- carriage = `str * str * 200`
- attack ability = `dex * cor / 10 + gin/32 + apply/attack`
- defense ability = `dex * cps / 10 + gin/32 + apply/defense`
- intimidate = `cor * str / 10 + kee/32 + apply/intimidate`
- wittiness = `cps * wis / 10 + kee/16 + apply/wittiness`
- magic ability = `spi * int / 10 + sen/32 + apply/magic`
- spell ability = `spi * wis / 10 + sen/32 + apply/spell`

These formulas are NOT reimplemented by the browser. This document exists so tooling/admin UI can understand the upstream model without creating a second runtime truth.

## Defense and damage
Physical defense can add the mapped dodge skill. Defense success derives from `50 + (attack ability - counter ability) * 2`, clamped to 5%-95%, then uses the upstream random roll.

Unarmed default damage converts strength using `1 + strength/10000 + random(strength/10000)` plus `apply/damage`, unless a mapped `force` skill supplies damage. Target armor resistance comes from `apply/armor` before `receive_damage()` applies character-state damage rules.

## Skills
`feature/char/skill.c` supports skill mapping. A skill can be unmapped, mapped to another skill, or mapped to `none` (disabled). For a mapped skill, `query_skill()` averages the original and mapped skill and caps the returned value at 200. `improve_skill()` accumulates learning progress and delegates follow-up processing to the skill object.

## Browser integration rule
The web client must send commands to Neolith/ES2. It must never calculate hits, damage, skill gain, death, conditions or NPC combat itself.
