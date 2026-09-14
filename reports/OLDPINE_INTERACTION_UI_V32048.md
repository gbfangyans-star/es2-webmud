# 老松林互動與 HUD 收尾 v3.20.48

- 修正 recovered rooms 使用錯誤 `item_desc` key：改用 canonical ROOM `detail`，使 `look footprints/sign/vine/...` 正常進入 `room.c::do_look()`。
- 小石橋長敘述加入藤蔓提示；瀑布、山壁、水潭補可觀察細節；攀爬路線補自然提示。
- WebHUD 新增場景互動資料：NPC 觀察/性命相搏/攻擊；高慎另有拜師/技能；房間 detail 物件提供觀察；已存在的老松林 climb/hold command 提供中文按鈕。
- 原 CONTEXT 非戰鬥狀態改為只顯示可直接使用道具：食物、飲水、可 study 書籍；CHAT/TELL 保留；CHAT 下新增獨立場景互動欄。
- 地圖 EXIT HUD 同步傳送目的房 `short`，避免未探索 runtime 節點顯示 `/custom/...` path。
- HUD server-text kick 180ms -> 20ms，初次 poll 500ms -> 120ms；800ms polling 保留作保險。
- 高慎 Lv15 拒教文字改為「你根基未穩，還是多練練吧。」；條件不變。
