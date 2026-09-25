# CUSTOM RACE A-H

This is a user-approved WebMUD extension layer. It is not claimed as canonical `taedlar/es2_mudlib` data when the original repository does not provide the race implementation.

Implemented race set:

- human / 人類
- avatar / 人類族
- blackteeth / 黑齒
- yenhold / 厭火
- jiaojao / 焦僥
- woochan / 無腸
- dingling / 釘靈
- headless / 刑天

## Source priority

The 2006-09-15 original race data (`種族詳細資料`, race.detail.txt) takes priority over the earlier `種族設定.html` table and over earlier locked review rules. Class level caps, hidden bonuses, attribute ranges, karma, 基數 and race-skill formulas all follow it. Where the original is silent, the user-approved rules below fill the gap.

## Numbers

- Table gin/kee/sen values are birth values.
- Class level caps are stored as `class_level_cap` in the race daemon and enforced by `feature/char/score.c` at level-up time. `commoner` (平民) is capped at 1 for every race. A cap of `-1` means the original data's 「無」: the race cannot join that class. `set_class()` refuses the change and returns 0.
- 基數 is stored on the race daemon as `commoner_score_base` (percent, 100 = human). The soldier and taoist class daemons multiply their character level-up thresholds by it. It never affects skill experience. Future class daemons must apply it the same way.
- Hidden bonuses follow the original data. 防禦力 = `apply/armor`, 攻擊能力值 = `apply/attack`, 防禦能力值 = `apply/defense`, 攻勢等級 = `apply/intimidate`, 守勢等級 = `apply/wittiness`, 警覺性 = `apply/awarness`. 縱躍閃躲之法 / 拆招卸力之法 are skill levels (`apply/dodge`, `apply/parry`).
- Existing characters keep their rolled attributes. The new ranges apply only to newly created characters. Hidden bonuses are re-applied at every login, so they update for everyone.

## Tick basis

Neolith `HEARTBEAT_INTERVAL` is 2,000,000 microseconds, so 1 tick = one 2-second heartbeat. Conditions are only updated every 5~14 heartbeats, so per-tick race effects (gnaw poison, dance durations, sorrow/rite) are driven by call_out chains in their condition daemons, tied to a per-application serial. ES2 world time advances at 60x real time, so one quarter of an ES2 day is 360 real seconds.

## Race skills

- human `resurge`, avatar `radiate`, jiaojao `hide`: unchanged earlier design. The original's 焦僥 steal/anti-steal advantage is represented by 警覺性 100.
- yenhold `breathe`: every enemy in the room takes kee damage = current kee / 10 + cor x 2. No self damage. Costs sen 10, cooldown 1 tick.
- dingling `hoof`: success roll unchanged (行動力 ratio). On success the target loses kee = dingling str and is busy 2~3 ticks; self busy 1. On failure, self busy 2.
- woochan `replete`: costs sen 20, water maximum / 6 (clamped at zero), busy 1 tick, no cooldown (unchanged). Heals damaged gin/kee/sen bars by age. HP current and maximum +(1 + age/20). Fatigue -(1 + age/20).
- blackteeth `gnaw`: bite and poison rolls unchanged. The bite deals kee 1 + age/20. The poison deals kee 5 + age/15 (max 15) every tick for 1 + age/10 ticks (max 12). All divisions are integer divisions.
- headless `dance for <mode>`: requires a wielded axe and cannot be used in combat.
  - `glory` 榮光之舞: damage +5+str/2, armor +5+cps/2, for int/2 ticks.
  - `fury` 忿怒之舞: damage +15, intimidate +dex/2, for cor/2 ticks.
  - `axe` 斧舞: axe / secondhand axe / twohanded axe skills +int+10, for wis/2 ticks.
  - glory / fury / axe share one slot; a new one replaces the old. Busy 2 after use.
  - `sorrow` 哀傷之舞: each application restores 3~5 of a random one of gin/kee/sen, lowers the other two by 1~2 (never below 1), and costs food and water 1 each.
  - `rite` 祭舞: each application restores gin 2~3, kee 3~5, or sen 1~2 (random).
  - sorrow / rite apply once immediately, then once per tick for wis/2 more ticks, with a dance message each tick. They stop when the dancer enters combat, leaves the room, or stops wielding an axe.
