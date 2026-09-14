# Old Pine recovery manifest v1

Status: ARCHAEOLOGICAL / VERSION-DIFF INPUT. Do not silently treat as current taedlar canonical.

## Early ES2 room inventory confirmed in mudchina/es2 /d/oldpine
cave1 cave2 cave3 cave4 cave5 clearing cliff1 cliff2 cliffdown cliffside epath1 epath2 epath3 keep1 keep2 keep3 lake npath1 npath2 npath3 passage path3 pine1 pine2 pine3 pine4 pine5 pine6 pine7 riverbank1 riverbank2 secrectpath1 spath1 spath2 spath3 spath4 stone tree1 tree2 tree3 waterfall

Room files: 41. Subdirectories: npc, obj.

## NPC inventory confirmed
bandit, bandit_chief, bandit_commander, bandit_guard, bandit_leader, butterfly, fat_bandit, maniac, serpent, skeleton, spy, tall_bandit, venomsnake, wolf_dog.

NPC code files: 14 (+ npc.1 and spy.old archival/support files).

## Object inventory confirmed
bamboo_pipe, black_suit, blade, book, fur_coat, glaive, leather, long_sword, robe, short_sword, throwing_knife.

Object code files: 11 (+ obj.1 support file).

## Confirmed mechanics already individually inspected
- cave rooms include reset-time randomized exits; this is dynamic topology, not a fixed map.
- epath2 has a vine interaction that can route to passage or waterfall depending on the original check.
- clearing has a climb-pine interaction into the tree branch.
- Old Pine Keep is keep1 -> keep2 -> keep3, with keep2 controlling a blocking-stone ambush.
- bamboo_pipe supports play/blow and calls the current room's pipe_notify(). This is the missing link for the keep2 stone reopening mechanism.
- bandit_commander is 常老大, 老松寨寨主, nickname 潑風刀王; carries bamboo_pipe.

## Version boundary
The currently playable custom 10-room Gao Shen route remains unchanged. No automatic merge is permitted until a room-by-room version diff establishes whether the early LPC forest is retained, replaced, or partially reused by the later Gao Shen-era map.

## Remaining recovery work
1. Extract every room's fixed and dynamic exits.
2. Extract all non-directional actions and prerequisites.
3. Extract all 14 NPC stats, inventory, chats, special callbacks, death/accept hooks.
4. Extract all 11 object mechanics and consumers.
5. Trace all cross-file callbacks (pipe_notify and similar).
6. Compare external links against later taedlar remnants and user-supplied map.
7. Only then choose the final branch connection near current path08.
