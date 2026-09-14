# CUSTOM RACE A-H

This is a user-approved WebMUD extension layer. It is not claimed as canonical `taedlar/es2_mudlib` data when the original repository does not provide the race implementation.

Implemented race set from the supplied `種族設定.html`, columns B-H only:

- human / 人類
- avatar / 人類族
- blackteeth / 黑齒
- yenhold / 厭火
- jiaojao / 焦僥
- woochan / 無腸
- dingling / 釘靈

Rules locked during review:

- Numeric conflicts use the new table, including human/avatar rebalance.
- `avatar` Chinese display name is `人類族`.
- Table gin/kee/sen values are birth values.
- 防禦力 maps to armor/damage reduction; 防禦能力 maps to dynamic `query_ability("defense")` plus race bonus.
- 移動力/行動力 are the same concept and are standardized as 行動力, backed by `query_ability("move")`.
- jiaojao `hide` compares against the highest-awareness current combat opponent.
- woochan `replete`: no cooldown, busy 1 tick; costs sen 20; heals damaged gin/kee/sen effective bars by age without restoring current values; consumes one third of maximum water from current water, clamped at zero; woochan is food-exempt only, not water-exempt.
- blackteeth `gnaw`: integer division; poison duration at least one tick; kee effective value may be reduced to zero.
- yenhold `breathe`: damage = age + a random value from kee maximum / 12 through kee maximum / 10.

Runtime tick basis: Neolith `HEARTBEAT_INTERVAL` is 2,000,000 microseconds, so 2 tick cooldowns are represented as 4 real seconds. ES2 world time advances at 60x real time, so one quarter of an ES2 day is 360 real seconds.

Per-race class level caps are stored as `class_level_cap` in the race daemon and enforced by `feature/char/score.c` at level-up time.
