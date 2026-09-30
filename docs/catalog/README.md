# ES2 江湖圖鑑

`es2_catalog.html` 是由遊戲原始碼自動產生的一頁式清單：技能、武器、防具、物品、區域（含地圖與 NPC）。
不需要伺服器，用瀏覽器直接打開即可。

內容有更新時重新產生：

```
python3 tools/build_catalog.py
```

- 產生程式：`tools/build_catalog.py`（掃描 `d/`、`obj/`、`custom/`、`daemon/skill/`）
- 網頁樣板：`tools/catalog_template.html`
- 區域名稱取自房間的 `map/area`；沒有的依目錄命名（見 `DIR_AREA`）。
- 地圖座標依出口方向自動排列，上下樓分層顯示。
- 走動的 NPC 以出生房間（房間 `objects` 放置的位置）標示。
