# Source Audit
Allowed source only: taedlar/es2_mudlib main.

Observed in allowed repository:
- main v1.5 uses Neolith.
- mudlib has adm, cmds, d/snow, daemon, data, docs/help, feature, include, log, obj, std.
- std/char.c inherits the character combat/action/skill feature set.
- heartbeat drives fighting and periodic condition/regeneration.
- feature/char/combat.c contains the actual ability/strength calculations.
- d/snow is the human starting town, with npc/obj/skill subfolders.

No gameplay data from prior projects or any other repository/site is included.
