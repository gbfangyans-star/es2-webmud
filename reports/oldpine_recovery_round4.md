# Old Pine recovery — large batch round 4 / integration compatibility

Status: archaeology + compatibility closure. No early Old Pine gameplay has been merged yet. Gao Shen path01..path10 remains untouched.

## User-approved integration policy
- Stop room-by-room lineage reconciliation against the Gao Shen ten-room route.
- Recovered full Old Pine will be connected later as a separate branch.
- A branch point is an integration concern only; it is not evidence that the two historical layouts correspond.

## parrybook dependency recovered
Historical `d/oldpine/npc/obj/parrybook.c` exists. It is named 過招要旨 / parrybook / pbook, weight 800, value 100, paper. Its legacy skill mapping targets `parry`, requires combat_exp 15000, sen cost 30, difficulty 25, and caps skill at 50.

The legacy object is NOT drop-in compatible with current taedlar study books. Current taedlar books inherit `F_STUDY` and use `required/skill` + `content`; `feature/study.c` implements the modern study loop. Therefore the Cave5 reward file is no longer a missing-file blocker, but its exact learning semantics remain an API-port blocker. We will not translate the old difficulty/sen/exp formula into the modern study schema by guesswork.

The historical file also sets `replica_ob` to `__DIR__"cola"`. Current taedlar still supports `replica_ob` in `feature/unique.c`, but no Old Pine cola dependency is present in the canonical project. Since the old file comments out F_UNIQUE, this replica path is recorded as dormant legacy metadata, not an active restoration requirement unless uniqueness is restored.

## Object closure sampled this round
- bamboo_pipe: interactive ITEM; play/blow invokes current room `pipe_notify()`. Required by keep2 reopening mechanism.
- black_suit: CLOTH 夜行衣, armor 1; identity-masking armor properties rewrite id/name/short/long as 黑衣人. This is a real object and is NOT the same filename as spy's missing `black_cloth` reference.
- blade: ordinary BLADE 單刀, weight 4000, value 500, iron, `init_blade(25)`.
- parrybook: file recovered, semantic API port still blocked as above.

## NPC closure added this round
- serpent: 黑冠巨蟒; aggressive; age 400; max gin 900 / kee 1800 / sen 500; str40 cor70 spi20 int10; attack60 damage20 armor90 dodge80; combat_exp250000; score1000.
- skeleton is not an NPC. It is an ITEM used by cave5 bury logic: weight3500, unit具, no_get. This corrects the recovery classification.

## Remaining hard blockers
1. `maniac` requires `necromancy`, absent from current taedlar canonical source.
2. `spy` references `black_cloth`; current taedlar has no such object. Do not silently substitute `black_suit`.
3. parrybook legacy learning semantics require an explicit faithful adapter or recovered legacy study contract before gameplay merge.

## Merge readiness consequence
The historical-version reconciliation blocker is removed entirely. Remaining blockers are now gameplay/API dependencies only. Rooms/topology that do not depend on the three blockers can be staged independently, while blocked actors/rewards stay disabled rather than fabricated.
