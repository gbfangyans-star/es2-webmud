# 現有 NPC 強度清單（待確認）

> 這是給你勾選用的清單。「建議強度」是我依等級與角色定位初步抓的，請直接回覆要改的地方即可，
> 例如「五堂鎮 護院武師：LV10 C」「雪亭鎮 官兵 改軍人」「沒提到的照建議」。
> 「手填」欄是目前檔案裡手動寫死的屬性數／精氣神數，轉換時會拿掉改由系統計算；若某個 NPC 要保留特殊數值請註明。

建議原則：小孩、動物、一般百姓 → C；守衛、士兵、土匪、門派弟子 → B；有名有姓的高手（約 LV30～49）→ A；LV50 以上的地區高手 → S。

| # | 地點 | 名稱 | 檔案 | 種族 | 職業 | 等級 | 手填(屬性/精氣神) | 建議強度 | 備註 |
|---|---|---|---|---|---|---|---|---|---|
| 1 | 鬼怪 | 餓鬼 | `custom/ghost/npc/hungry_ghost.c` | — | （平民） | — | 0/0 | 另議 | 用 setup_ghost() 另有一套設定 |
| 2 | 鬼怪 | 魑魅 | `custom/ghost/npc/mountain_sprite.c` | — | （平民） | — | 0/0 | 另議 | 用 setup_ghost() 另有一套設定 |
| 3 | 鬼怪 | 倀鬼 | `custom/ghost/npc/tiger_thrall.c` | — | （平民） | — | 0/0 | 另議 | 用 setup_ghost() 另有一套設定 |
| 4 | 鬼怪 | 遊魂 | `custom/ghost/npc/wandering_soul.c` | — | （平民） | — | 0/0 | 另議 | 用 setup_ghost() 另有一套設定 |
| 5 | 鬼怪 | 魍魎 | `custom/ghost/npc/water_goblin.c` | — | （平民） | — | 0/0 | 另議 | 用 setup_ghost() 另有一套設定 |
| 6 | 鬼怪 | 枉死鬼 | `custom/ghost/npc/wronged_ghost.c` | — | （平民） | — | 0/0 | 另議 | 用 setup_ghost() 另有一套設定 |
| 7 | 家園 | （butler） | `custom/home/npc/butler.c` | 人類 | （平民） | 1 | 0/0 | C |  |
| 8 | 天師道 | 朱衣派弟子 | `custom/taoism/npc/fire_taoist.c` | 人類族(avatar) | 道士 | 30 | 3/3 | A |  |
| 9 | 天師道 | 素衣派弟子 | `custom/taoism/npc/freeze_taoist.c` | 無腸 | 道士 | 30 | 3/3 | A |  |
| 10 | 天師道 | 玄衣派弟子 | `custom/taoism/npc/storm_taoist.c` | 人類族(avatar) | 道士 | 30 | 3/3 | A |  |
| 11 | 天師道 | 紫衣派弟子 | `custom/taoism/npc/thunder_taoist.c` | 人類族(avatar) | 道士 | 30 | 3/3 | A |  |
| 12 | 振武營 | 魯熙年 | `custom/zhenwu/npc/lu_xinien.c` | 人類 | 軍人 | — | 0/0 | B | 目前沒設等級（視為 LV1） |
| 13 | 振武營 | 米沛 | `custom/zhenwu/npc/mee_pei.c` | 人類 | 軍人 | — | 5/3 | B | 目前沒設等級（視為 LV1） |
| 14 | 振武營 | 小兵 | `custom/zhenwu/npc/soldier.c` | 人類 | 軍人 | — | 0/3 | B | 目前沒設等級（視為 LV1） |
| 15 | 振武營 | 假人 | `custom/zhenwu/npc/target_stake.c` | 人類 | 平民 | 20 | 0/0 | 不套用 | 練功假人 |
| 16 | 振武營 | 振武軍營士兵 | `custom/zhenwu/npc/zhenwu_soldier.c` | 人類 | 軍人 | 15 | 3/3 | B |  |
| 17 | 李家村 | 小孩 | `d/lee/npc/child.c` | 人類 | 平民 | 3 | 0/3 | C |  |
| 18 | 李家村 | 農夫 | `d/lee/npc/farmer.c` | 人類 | 平民 | 8 | 1/3 | C |  |
| 19 | 李家村 | 守衛 | `d/lee/npc/guard.c` | 人類 | 武者 | 15 | 2/3 | B |  |
| 20 | 李家村 | 冰糖葫蘆小販 | `d/lee/npc/hawthorn_seller.c` | 人類 | 平民 | 5 | 0/0 | C |  |
| 21 | 李家村 | 小藥童 | `d/lee/npc/herb_boy.c` | 人類 | 平民 | 5 | 1/3 | C |  |
| 22 | 李家村 | 獵戶 | `d/lee/npc/hunter.c` | 人類 | 武者 | 6 | 0/0 | B |  |
| 23 | 李家村 | 李勖賢 | `d/lee/npc/lee_hsu_hsien.c` | 人類 | 平民 | 10 | 1/0 | C |  |
| 24 | 李家村 | 李嘯天 | `d/lee/npc/lee_xiao_tian.c` | 人類 | 平民 | 20 | 1/3 | C |  |
| 25 | 李家村 | 李岩 | `d/lee/npc/lee_yen.c` | 人類 | 平民 | 4 | 0/0 | C |  |
| 26 | 李家村 | 李勇 | `d/lee/npc/lee_yong.c` | 人類 | 武者 | 15 | 2/3 | B |  |
| 27 | 李家村 | 李忠 | `d/lee/npc/lee_zhong.c` | 人類 | 平民 | 5 | 0/0 | C |  |
| 28 | 李家村 | 李半仙 | `d/lee/npc/li_ban_xian.c` | 人類 | 平民 | 5 | 0/0 | C |  |
| 29 | 李家村 | 聶晟 | `d/lee/npc/nee_cheng.c` | 人類 | 平民 | 30 | 6/3 | A |  |
| 30 | 李家村 | 私塾先生 | `d/lee/npc/teacher.c` | 人類 | 平民 | 5 | 0/0 | C |  |
| 31 | 李家村 | 旅客 | `d/lee/npc/traveller.c` | 人類 | 平民 | 5 | 0/0 | C |  |
| 32 | 李家村 | 店小二 | `d/lee/npc/waiter.c` | 人類 | 平民 | 2 | 0/0 | C |  |
| 33 | 李家村 | 婦人 | `d/lee/npc/woman.c` | 人類 | 平民 | 8 | 1/3 | C |  |
| 34 | 迷霧森林 | 土匪 | `d/oldpine/npc/bandit.c` | 人類 | 盜賊 | 10 | 0/3 | B |  |
| 35 | 迷霧森林 | 土匪嘍囉 | `d/oldpine/npc/bandit_minion.c` | 人類 | 盜賊 | 5 | 0/3 | B |  |
| 36 | 迷霧森林 | 大黑熊 | `d/oldpine/npc/big_bear.c` | 野獸 | 平民 | 1 | 0/0 | B |  |
| 37 | 迷霧森林 | 大觀和尚 | `d/oldpine/npc/da_guan.c` | 人類 | 和尚 | 50 | 1/3 | S |  |
| 38 | 迷霧森林 | 野鹿 | `d/oldpine/npc/deer.c` | 野獸 | 平民 | 1 | 0/0 | C |  |
| 39 | 迷霧森林 | 採藥人 | `d/oldpine/npc/herbalist.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 40 | 迷霧森林 | 受傷的旅客 | `d/oldpine/npc/injured_traveller.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 41 | 迷霧森林 | 高慎 | `d/oldpine/npc/kao_shen.c` | 人類 | 武者 | — | 1/0 | B | 目前沒設等級（視為 LV1） |
| 42 | 迷霧森林 | 靈玉嬋 | `d/oldpine/npc/lin_yuchan.c` | 人類 | 武者 | 30 | 5/3 | A |  |
| 43 | 迷霧森林 | 小黑熊 | `d/oldpine/npc/little_bear.c` | 野獸 | 平民 | 1 | 0/0 | C |  |
| 44 | 迷霧森林 | 老鼠 | `d/oldpine/npc/rat.c` | 野獸 | 平民 | 1 | 0/0 | C |  |
| 45 | 迷霧森林 | 旅行小販 | `d/oldpine/npc/seller.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 46 | 迷霧森林 | 松鼠 | `d/oldpine/npc/squirrel.c` | 野獸 | 平民 | 1 | 0/0 | C |  |
| 47 | 迷霧森林 | 店小二 | `d/oldpine/npc/waiter.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 48 | 迷霧森林 | 凶暴的野熊 | `d/oldpine/npc/wild_bear.c` | 野獸 | 平民 | 1 | 0/0 | B |  |
| 49 | 迷霧森林 | 土狼 | `d/oldpine/npc/wolf.c` | 野獸 | 平民 | 1 | 0/0 | B |  |
| 50 | 迷霧森林 | 徐彪 | `d/oldpine/npc/xue_biao.c` | 厭火 | 盜賊 | 20 | 0/3 | B |  |
| 51 | 雪亭鎮 | 陳維俠 | `d/snow/npc/alchemist.c` | 人類 | 平民 | 30 | 6/0 | A |  |
| 52 | 雪亭鎮 | 阿寶 | `d/snow/npc/child.c` | 人類 | 平民 | 10 | 4/0 | C |  |
| 53 | 雪亭鎮 | 小孩 | `d/snow/npc/child1.c` | 人類 | （平民） | 1 | 0/3 | C |  |
| 54 | 雪亭鎮 | 小孩 | `d/snow/npc/child2.c` | 人類 | （平民） | 1 | 0/0 | C |  |
| 55 | 雪亭鎮 | 小孩 | `d/snow/npc/child3.c` | 人類 | （平民） | 1 | 0/3 | C |  |
| 56 | 雪亭鎮 | 小孩 | `d/snow/npc/child4.c` | 人類 | （平民） | 1 | 0/3 | C |  |
| 57 | 雪亭鎮 | 工頭 | `d/snow/npc/foreman.c` | 人類 | （平民） | 8 | 4/1 | C |  |
| 58 | 雪亭鎮 | 瞎眼老太婆 | `d/snow/npc/gammer.c` | 人類 | 平民 | 44 | 4/0 | A |  |
| 59 | 雪亭鎮 | 官兵 | `d/snow/npc/garrison.c` | 人類 | 平民 | 17 | 2/0 | B | 建議職業改「軍人」 |
| 60 | 雪亭鎮 | 白衣女子 | `d/snow/npc/girl.c` | 人類 | 平民 | 55 | 5/0 | S |  |
| 61 | 雪亭鎮 | 青衣漢子 | `d/snow/npc/guard.c` | 人類 | 平民 | 20 | 2/0 | C |  |
| 62 | 雪亭鎮 | 藥鋪掌櫃 | `d/snow/npc/herbalist.c` | 人類 | 平民 | 3 | 0/0 | C |  |
| 63 | 雪亭鎮 | （innkeeper） | `d/snow/npc/innkeeper.c` | — | （平民） | — | 0/0 | C | 目前沒設等級（視為 LV1） |
| 64 | 雪亭鎮 | 拾荒老頭 | `d/snow/npc/junkman.c` | 人類 | （平民） | 2 | 0/0 | C |  |
| 65 | 雪亭鎮 | 武官 | `d/snow/npc/lieutenant.c` | 人類 | 平民 | 24 | 2/0 | B | 建議職業改「軍人」 |
| 66 | 雪亭鎮 | 楊大嬸 | `d/snow/npc/miller.c` | 人類 | （平民） | 2 | 0/0 | C |  |
| 67 | 雪亭鎮 | 黑衣老人 | `d/snow/npc/oldman.c` | 人類 | 平民 | 7 | 0/2 | B |  |
| 68 | 雪亭鎮 | 巡邏官兵 | `d/snow/npc/patrol.c` | 人類 | 平民 | 15 | 0/2 | B | 建議職業改「軍人」 |
| 69 | 雪亭鎮 | 鐵匠 | `d/snow/npc/smith.c` | 人類 | （平民） | 13 | 4/1 | C |  |
| 70 | 雪亭鎮 | 王懷芝 | `d/snow/npc/teacher.c` | 人類 | 書生 | 5 | 0/1 | B |  |
| 71 | 雪亭鎮 | （waiter） | `d/snow/npc/waiter.c` | — | （平民） | — | 0/0 | C | 目前沒設等級（視為 LV1） |
| 72 | 雪亭鎮 | 少婦 | `d/snow/npc/woman.c` | 人類 | （平民） | 2 | 0/0 | C |  |
| 73 | 雪亭鎮 | 魚天 | `d/snow/npc/yu.c` | 人類 | （平民） | 1 | 0/0 | C |  |
| 74 | 五堂鎮 | 冷梅莊二代弟子 | `d/wutang/npc/apprentice.c` | 人類 | 武者 | 25 | 0/3 | B |  |
| 75 | 五堂鎮 | 大野豬 | `d/wutang/npc/big_boar.c` | 野獸 | 平民 | 1 | 0/0 | B |  |
| 76 | 五堂鎮 | 野豬 | `d/wutang/npc/boar.c` | 野獸 | 平民 | 1 | 0/0 | C |  |
| 77 | 五堂鎮 | 釣客 | `d/wutang/npc/fisher.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 78 | 五堂鎮 | 護院武師 | `d/wutang/npc/guard.c` | 黑齒 | 武者 | 20 | 0/3 | B |  |
| 79 | 五堂鎮 | 郭布 | `d/wutang/npc/guo_boo.c` | 人類 | 道士 | 60 | 8/3 | S |  |
| 80 | 五堂鎮 | 小黃 | `d/wutang/npc/huang.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 81 | 五堂鎮 | 呼延光 | `d/wutang/npc/huyen_guan.c` | 人類 | 書生 | 35 | 7/3 | A |  |
| 82 | 五堂鎮 | 珍寶商人 | `d/wutang/npc/jeweller.c` | 人類 | 平民 | 10 | 0/3 | C |  |
| 83 | 五堂鎮 | 廟祝 | `d/wutang/npc/keeper.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 84 | 五堂鎮 | 李山 | `d/wutang/npc/lee_shan.c` | 人類 | 平民 | 5 | 0/3 | C |  |
| 85 | 五堂鎮 | 陸四爺 | `d/wutang/npc/lu_estimator.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 86 | 五堂鎮 | 老火 | `d/wutang/npc/old_fire.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 87 | 五堂鎮 | 老人 | `d/wutang/npc/oldman.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 88 | 五堂鎮 | 紅衣道士 | `d/wutang/npc/red_taoist.c` | 人類 | 道士 | 15 | 0/3 | B |  |
| 89 | 五堂鎮 | 老駱 | `d/wutang/npc/ro.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 90 | 五堂鎮 | 趙欽差 | `d/wutang/npc/royalist.c` | 人類 | 軍人 | 1 | 0/3 | B |  |
| 91 | 五堂鎮 | 賣餅大叔 | `d/wutang/npc/seller.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 92 | 五堂鎮 | 綿羊 | `d/wutang/npc/sheep.c` | 野獸 | 平民 | 1 | 0/0 | C |  |
| 93 | 五堂鎮 | 牧羊人 | `d/wutang/npc/shepherd.c` | 人類 | 平民 | 1 | 0/3 | C |  |
| 94 | 五堂鎮 | 煙波釣叟 | `d/wutang/npc/smoke_fisher.c` | 人類 | 武者 | 50 | 5/3 | S |  |
| 95 | 五堂鎮 | 小桃 | `d/wutang/npc/tao.c` | 人類 | 平民 | 5 | 0/3 | C |  |
| 96 | 五堂鎮 | 城隍爺 | `d/wutang/npc/town_god.c` | — | （平民） | — | 0/0 | 另議 | 特殊 NPC |
| 97 | 五堂鎮 | 店小二 | `d/wutang/npc/waiter.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 98 | 五堂鎮 | 白衣道士 | `d/wutang/npc/white_taoist.c` | 無腸 | 道士 | 15 | 2/3 | B |  |
| 99 | 五堂鎮 | 葉翔 | `d/wutang/npc/yaesae.c` | 人類 | 盜賊 | 30 | 4/3 | A |  |
| 100 | 五堂鎮 | 楊子陵 | `d/wutang/npc/yang_zlin.c` | 人類 | 武者 | 45 | 2/3 | A |  |
| 101 | 五堂鎮 | 青年公子 | `d/wutang/npc/young_gentleman.c` | 人類 | 平民 | 10 | 0/3 | C |  |
| 102 | 五堂鎮 | 小鼠兒 | `d/wutang/npc/young_man.c` | 人類 | 平民 | 1 | 0/0 | C |  |
| 103 | 五堂鎮 | 青年書生 | `d/wutang/npc/young_scholar.c` | 人類 | 平民 | 10 | 0/3 | C |  |
| 104 | 五堂鎮 | 雍泰 | `d/wutang/npc/yung_tai.c` | 厭火 | 武者 | 20 | 5/3 | B |  |
