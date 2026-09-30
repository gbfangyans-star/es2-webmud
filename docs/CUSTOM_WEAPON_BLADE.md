# 刀類武器（custom/weapon/blade）

依使用者提供的 ES2 原始武器資料（Big5 文字檔）製作。名稱、顏色碼、敘述、傷害力與武器特性照原資料；
所屬 NPC 與放置位置另行設定。

## 規則

- **指令名稱**：英文全名或 `blade` 都可以指定，例如 `wield fire god's wings`、`wield blade`。
- **傷害力**：以 `init_damage()` 直接還原原資料，`identify` 顯示的數字與原資料相同。
- **價值**：原資料有紀錄的照紀錄；沒有的在 50～1000 兩銀子之間取 50 的倍數，製作時抽一次固定。
- **重量**：依遊戲既有的膂力規則換算（`std/race/humanoid.c` 的 `valid_wield()`）：
  單手需要膂力 = 重量 / 500、雙手 = 重量 / 1000、左手 = 重量 / 250，膂力可以比需求少 1。
  需要的膂力隨最高傷害線性增加：
  - 雙手刀：最高傷害 36 → 雙手膂力 12（12000）；124 → 30（30000）。
  - 單手刀：最高傷害 26 → 單手膂力 8（4000）；84 → 24（12000）。
  - 例外：黑風刀依使用者指定，左手需要膂力 33（重量 8500）。
- **武器特性只在左手**：邪兵『火麟』、藍涎刀、幽冥刀的特性只在以左手刀法裝備時生效（使用者指定）。
  之後遇到「可用兩種技能、但特性只列一次」的資料，要先問使用者。
- **唯一性**：虎紋刀、邪門歪刀、長刀僉白、紫雲朱寰繼承 `F_UNIQUE`。這把刀存在於世上任何地方
  （玩家身上、容器、地上、當鋪儲藏室）時，NPC 重生不會拿到，也沒有替代品；刀消失後，原持有的
  NPC 下次重生時重新帶著它。
- **兩個版本**：軒轅龍骨刀（一般版 `blade_of_dragon`、南宮恨事件後 `blade_of_dragon_awakened`）、
  妄焱兵絕（一般版 `flame_weapon`、范老兒淬鍊後 `flame_weapon_forged`）。取得劇情另行製作。
- **藍涎刀的毒**（`daemon/condition/blue_venom.c`）：單手或左手使用時每次命中都上毒，持續 10 tick，
  每 2 tick 發作一次（共 5 次）。每次發作先扣目前值、再扣實格（可隨時間恢復的上限）：精目前值 -5、精實格 -3、氣目前值 -4、氣實格 -2、
  形體 -2。再次命中只重設剩餘時間，發作節奏不變。昏倒時照樣發作，形體扣到 0 即死亡。
  中毒訊息「你突然感到一陣冷冽的蝕骨之痛從傷口傳了過來！」、發作訊息「你中的毒發作了！」，
  同房間的人看到把「你」換成名字的版本。
  戰鬥系統在武器命中並造成傷害後呼叫武器的 `hit_ob(攻擊者, 目標, 傷害)`（`adm/daemons/combatd.c`），
  之後其他特殊武器也可以使用。
- **紫薇伏龍刀**：原資料只列一次傷害（8-41，刀法）與一組特性；依使用者指定，特性在刀法與左手刀法都生效。
  左手刀法的傷害依 `setup_blade()` 的比例（範圍減半）為 8-23。
- **未製作**：單刀（Poison blade）依使用者指示不製作。

## 一覽

| 名稱 | 檔案 | 英文 | 重量 | 需要膂力 | 價值（兩） | 唯一 |
|---|---|---|---|---|---|---|
| 黑風刀 | `black_kris.c` | black kris | 8500 | blade 17、secondhand blade 34 | 850 |  |
| 軒轅龍骨刀 | `blade_of_dragon.c` | blade of dragon | 19400 | twohanded blade 19 | 700 |  |
| 軒轅龍骨刀 | `blade_of_dragon_awakened.c` | blade of dragon | 19400 | twohanded blade 19 | 400 |  |
| 邪刀•焱靈 | `blade_of_fire_spirit.c` | blade of fire spirit | 25500 | twohanded blade 25 | 150 |  |
| 蛟骨刀 | `blade_of_hydra_bone.c` | blade of hydra bone | 9200 | blade 18 | 250 |  |
| 煉獄 | `blade_of_inferno.c` | blade of inferno | 19400 | twohanded blade 19 | 850 |  |
| 九環霸王刀 | `blade_of_nine_rings.c` | blade of nine-rings | 26700 | twohanded blade 26 | 1000 |  |
| 玄鐵斬崩刀 | `blade_of_strange_iron.c` | blade of strange-iron | 8300 | blade 16 | 250 |  |
| 靈刀祭血 | `blood_blade.c` | blood blade | 6100 | blade 12 | 950 |  |
| 藍涎刀 | `blue_poison_blade.c` | blue_poison blade | 6100 | blade 12、secondhand blade 24 | 750 |  |
| 紫薇伏龍刀 | `purple_dragon_blade.c` | purple dragon blade | 6100 | secondhand blade 24、blade 12 | 40 |  |
| 井中月 | `ceremonial_moon.c` | ceremonial moon | 8300 | blade 16 | 250 |  |
| 紫雲朱寰 | `cloudy_ring_blade.c` | cloudy ring blade | 12000 | blade 24 | 750 | 是 |
| 巨刀 | `colosus_blade.c` | colosus blade | 18800 | twohanded blade 18 | 500 |  |
| 古銅刀 | `copper_blade.c` | copper blade | 14500 | twohanded blade 14 | 300 |  |
| 渾天刀 | `cursed_blade_of_darkness.c` | cursed blade of darkness | 18800 | twohanded blade 18 | 950 |  |
| 妖刀赤獄 | `devilish_blade.c` | devilish blade of burning soul | 18800 | twohanded blade 18 | 150 |  |
| 邪門歪刀 | `evil_lopsided_blade.c` | evil-lopsided blade | 6100 | blade 12 | 850 | 是 |
| 翠羽刀 | `feather_blade.c` | feather blade | 9200 | blade 18 | 750 |  |
| 火神之翼 | `fire_gods_wings.c` | fire god's wings | 21800 | twohanded blade 21 | 500 |  |
| 妄焱兵絕 | `flame_weapon.c` | flame weapon | 4000 | blade 8 | 250 |  |
| 妄焱兵絕 | `flame_weapon_forged.c` | flame weapon | 8300 | blade 16 | 100 |  |
| 幽冥魔刀 | `ghost_blade.c` | ghost blade | 30000 | twohanded blade 30 | 650 |  |
| 鬼頭劈象刀 | `ghost_head_blade.c` | ghost blade | 30000 | twohanded blade 30 | 600 |  |
| 百鬼刀 | `ghosts_blade.c` | ghosts blade | 6100 | blade 12 | 200 |  |
| 邪兵『火麟』 | `grin_weapon.c` | grin weapon | 6100 | blade 12、secondhand blade 24 | 50 |  |
| 砍馬大刀 | `horse_twohanded_blade.c` | horse-twohanded blade | 12000 | twohanded blade 12 | 700 |  |
| 大刀 | `large_blade.c` | large blade | 12000 | twohanded blade 12 | 800 |  |
| 偃月刀 | `moon_blade.c` | moon blade | 14500 | twohanded blade 14 | 800 |  |
| 酖風刀 | `poison_wind_blade.c` | poison wind blade | 21400 | twohanded blade 21 | 800 |  |
| 龍紋斬馬刀 | `reckless_blade.c` | reckless blade | 19400 | twohanded blade 19 | 250 |  |
| 啐雪大刀 | `snow_blade.c` | snow blade | 15900 | twohanded blade 15 | 700 |  |
| 精鋼砍刀 | `steelblade.c` | steelblade | 14500 | twohanded blade 14 | 750 |  |
| 幽冥刀 | `styx_blade.c` | styx blade | 4000 | secondhand blade 16、blade 8 | 700 |  |
| 磨心刀 | `test_heart_blade.c` | test-heart blade | 8300 | blade 16 | 654 |  |
| 虎紋刀 | `tiger_blade.c` | tiger blade | 19400 | twohanded blade 19 | 650 | 是 |
| 長刀僉白 | `white_blade.c` | white blade | 9200 | blade 18 | 500 | 是 |
| 清風刀 | `wind_power_blade.c` | wind-power blade | 9200 | blade 18 | 850 |  |
| 斬風刀 | `wind_slasher_blade.c` | wind-slasher blade | 21400 | twohanded blade 21 | 160 |  |
| 蟬翼刀 | `wing_blade.c` | wing blade | 6100 | blade 12 | 600 |  |
