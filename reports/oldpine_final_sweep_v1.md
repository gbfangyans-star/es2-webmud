# Old Pine final sweep v1 (v3.20.43)

## Closed in this sweep
- Verified all 41 recovered Old Pine room LPC files are present and source-connected from the recovered branch.
- Verified the world branch from current Gao-Shen path08 to recovered npath1 remains present.
- Verified known recovered placements: tree2 butterflies, pine1 tall/fat bandits, pine7 wolf dog, keep guards/leader/commander, cave5 skeleton.
- Verified dynamic cave/pine resets, Cave5 burial reward, Keep ambush and bamboo-pipe callback.
- Added a final-sweep audit that checks local file references and blocker truth against canonical taedlar source while excluding CUSTOM recovery code.
- Added five-walker whole-area source coverage: 5 walkers x 3 laps x 41 rooms = 615 room-coverage checks, plus critical mechanics checks.

## Faithful blockers intentionally left isolated
1. spy -> black_cloth: absent from current canonical LPC/H files. black_suit is not silently substituted.
2. maniac -> necromancy: historical name evidence exists in legacy docs, but no current canonical implementation was found; NPC remains isolated.
3. venomsnake -> snake_poison: current canonical condition implementation is absent; poison behavior is not deleted or invented.
4. parrybook: legacy contract is preserved (combat exp 15000, sen 30, difficulty 25, parry cap 50), but current F_STUDY uses a materially different contract. No fake adapter is enabled without recovered semantics/API evidence.

## Acceptance boundary
Content layer can be treated as source-complete except for the four explicit compatibility blockers above. All tests in this environment remain source-level fallback, NOT live Neolith/TELNET acceptance.
