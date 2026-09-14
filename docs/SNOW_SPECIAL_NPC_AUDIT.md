# Snow special NPC audit

Scope: the five high-complexity Snow NPCs already present in the canonical mudlib: 阿寶, 瞎眼老太婆, 王懷芝, 陳維俠, 白衣女子.

This audit does **not** import, invent, or rewrite gameplay. It verifies that their canonical LPC files, fixed room references, key behavior hooks, and absolute object dependencies are still present. `/legacy-ES2` is not a source.

Run `CHECK_SNOW_SPECIAL_NPCS.bat` on Windows. A passing static audit proves source wiring is present; it does not claim that every quest branch has been live-played.
