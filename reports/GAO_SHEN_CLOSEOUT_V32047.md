# 高慎／虎刀門第一階收尾 v3.20.47

本輪以使用者提供的虎刀門資料為最高優先，完成以下收尾：

- 瘋虎功初次練成直接 Lv20，永久根骨 +1。
- Lv21-139 每級永久 Gin +2 / Kee +2。
- Lv100 永久膽識 +2。
- Lv140-160 每級 Gin +3 / Kee +4。
- Lv161+ 每級 Gin +1 / Kee +1。
- `exert tiger force`：每 tick Kee 消耗 2 / effective Kee 損耗 1；Gin 消耗 3 / effective Gin 損耗 1。
- Lv100 開放 `exert powerup`：傷害 + skill/4、attack + skill/3、持續 skill*1.5 秒，禁止重複疊加。
- 狻猊步法 enable dodge 後，在每次防禦判定前隨機播放六種約 60 字身法嘗試敘述；完全沿用原 ES2 defend 機率公式，不加額外 dodge、屬性或成功率。
- 三門刀法與瘋虎刀法各六式維持全招式可隨機使用。
- 瘋虎刀法 Lv90 且 exert >70 的追擊規則保留。

尚未以使用者資料確認的 rage / deathwish 不在本輪擅自補公式。

## Regression

- Targeted Tiger/Gao Shen regression: 22 tests passed.
- Includes five virtual Tiger Force boundary profiles covering Lv21, Lv100, Lv120, Lv140 and Lv161 growth/powerup edges.
- Existing Tiger Blade five-player follow-up boundary test remains green.
- No live Neolith/TELNET acceptance was available in this environment; this package reports structural/formula regression only.
