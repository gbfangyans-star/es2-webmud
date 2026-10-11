# 冷梅莊莊主 梅影風（may yin fong）

> CUSTOM NPC（NEW）。設定由使用者提供（2026-10-09）。檔案：`source/upstream/mudlib/d/wutang/npc/may_yin_fong.c`。

## 基本

- 人類、武者、LV60、強度 S、55 歲，稱號「冷梅莊莊主」。
- 精氣神由 NPC 強度系統計算，約 精 800／氣 1750／神 600（依種族屬性擲骰浮動）。
- 裝備：銀霜鎧、奔雲靴、梅花白襖、白玉腰帶、白玉戒指、寒霜劍（右手）、冰雪匕（左手）。
  白玉腰帶世上只有一條，已在別人手上時改穿銀彎束腰。

## 武功

| 技能 | 等級 | 使用 |
|---|---|---|
| 冷梅劍法 lunmay | 180 | 劍術、招架 |
| 傲梅暗劍訣 advance_lunmay | 180 | 左手劍術、左手錐法 |
| 寒梅心法 hainmay force | 200 | 內功 |
| 梅影身法 mayin | 160 | 閃躲 |
| 七巧如意手 seven | 160 | 徒手 |
| sword / secondhand sword / secondhand dagger | 180 | |
| force | 190 | |
| parry / dodge / unarmed | 160 / 150 / 140 | |

## 走動

- 在 `/d/wutang/crossroad`（交叉路口）出生。
- 每 2 tick（4 秒）擲一次，10% 機率移動；戰鬥或忙碌時不動。
- 只走往 `/d/wutang/` 的出口，不會離開五堂鎮；若人在五堂鎮外，下一次擲骰時直接回交叉路口。

## 拜師（apprentice may）

1. 不是平民：「閣下的志向相當明確，又何必來糾纏老朽呢？」
2. 阿修羅、巫首、雨師妾：「閣下似乎不適合修習本門武功。」
3. 通過：成為武者，`custom_faction` = `fighter.lunmay`，稱號「冷梅莊弟子」。

## 傳授（acquire <技能> from may）

只教冷梅莊弟子；每門只補足到剛好可以升到 1 級的經驗，之後要自己修練。

| 條件 | 技能 |
|---|---|
| 拜師後 | 冷梅劍法、梅影身法、七巧如意手、sword、secondhand sword、secondhand dagger、parry、dodge、unarmed |
| LV15 | 寒梅心法、force |
| LV30 且寒梅心法 100 | 傲梅暗劍訣 |
