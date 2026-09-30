# 技能名稱與代碼（使用者指定）

尚未實作的技能先在這裡定好代碼與中文名稱，並登記到 `data/chinese.o`，讓 `identify`、`skills` 等顯示中文。
之後製作技能時，技能 daemon（`daemon/skill/<代碼>.c`）與裝備特性一律沿用這裡的代碼。
新增或更改技能名稱時一併更新本表。

| 分類 | 中文名稱 | 代碼 | 備註 |
|---|---|---|---|
| 咒術 | 幻劍術 | `virtual sword` | 對照表原本就有 |
| 咒術 | 幽冥三箭 | `taoism of purify` | 仙符鏽袍。對照表另有舊代碼 `youmin`（茅山咒術【幽冥三箭】），不再使用 |
| 咒術 | 茅山幻術 | `taoism of nature` | 雲羅絲衣 |
| 咒術 | 茅山奇術 | `taoism of darkness` | |
| 法術 | 天師道法【紫薇心經】 | `chivi sutra` | 對照表原本就有 |
| 法術 | 天師道法【桃山密籙】 | `taoism of conviction` | 天地雲衫 |
| 法術 | 天師道法【素雲書】 | `taoism-cloud` | 焚羽護衣。對照表另有舊代碼 `su cloudy`、`su uen`，不再使用 |
| 法術 | 茅山法術 | `mao-shan magic` | |
| 法術 | 茅山【五雷術】 | `mao-shan lightning` | |
| 法術 | 茅山奇術【遁甲書】 | `taoism of dunja` | |
| 法術 | 茅山道法【奇門術】 | `mao-shan mysticism` | |
| 內功 | 茅山心經 | `mao-shan force` | |
| 步法 | 茅山步法 | `mao-shan steps` | |
| 劍術、拆招卸力之法 | 太乙劍法 | `taiyie` | 對照表原本就有 |
| 劍術、左手劍術 | 茅山劍法 | `mao-shan sword` | |
| 其他 | 大悲咒 | `compassion` | 無相福田 |
| 其他 | 善想禪要 | `absorption` | 金線僧袍 |

代碼一律小寫（遊戲的技能代碼都是小寫）。
