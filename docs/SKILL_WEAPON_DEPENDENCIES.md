# Skill and Weapon Dependency Graph

The graph resolves only exact source evidence.

1. `DAEMON_D->register_skill_daemon("name")` creates a skill-name registry.
2. `map_skill(base, "name")` may link to that registry when exactly one daemon registers the same literal name.
3. `SKILL_D("name")->method(...)` is an exact literal dependency.
4. `SKILL_D(variable)->method(...)` is deliberately kept unresolved.
5. `wield_as` and literal `init_damage(..., "skill")` values may link a weapon object to a registered skill daemon by exact literal name.

No fuzzy matching, aliases, wiki names or inferred martial-art relationships are used.
