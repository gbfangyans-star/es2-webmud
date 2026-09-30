# ES2 江湖圖鑑

`es2_catalog.html` 是由遊戲原始碼自動產生的一頁式清單：技能、武器、防具、物品、區域（含地圖與 NPC）。
不需要伺服器，用瀏覽器直接打開即可。

內容有更新時重新產生：

```
python3 tools/build_codex.py
```

- 產生程式：`tools/build_codex.py`（掃描 `d/`、`obj/`、`custom/`、`daemon/skill/`）
- 網頁樣板：`tools/codex_template.html`
- 區域名稱取自房間的 `map/area`；沒有的依目錄命名（見 `DIR_AREA`）。
- 不公開的目錄列在 `HIDDEN_DIRS`（巫師房間、家園）：不列入區域；裡面的 NPC 與物品只有被公開房間放置時才列出。
- 地圖座標依出口方向自動排列，上下樓分層顯示；需要手動調整的房間寫在 `MAP_POS`（相對某房間的位置），不顯示的房間寫在 `MAP_HIDE`。
- 走動的 NPC 以出生房間（房間 `objects` 放置的位置）標示。
- 用指令進出的路線（房間 `add_action` 的處理函式把玩家 `move` 到其他房間，例如 climb 圍牆）在地圖上畫虛線；只要一個方向要用指令就畫虛線。
