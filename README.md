# ES2 WebMUD v3.19.3

## v3.20.1 - Player lifecycle tuning / home persistence verification

- User-approved WebMUD tuning: player revive delay changed from canonical 60 seconds to 20 seconds.
- No other death/corpse/revive combat logic changed.
- Added static lifecycle checks for corpse/death hooks and CUSTOM HOME SYSTEM persistence fields.
- Weapon-skill canonical blockers remain deferred for later completion.


## v3.19.0 multiplayer live-safety correction

This release does not add gameplay content. It corrects live acceptance design before more Windows testing: the earlier inn NPC result is recorded as a canonical no-fight-room proof rather than actual combat PASS; arbitrary NPC `fight` is explicitly potentially risky because canonical `fight.c` may call `kill_ob()` for non-civilized NPCs; a preferred mutual-player `fight` gate was added; shared-world NPC probing no longer starts combat; ground-item contention uses canonical `get.c` loser behavior instead of inventory-ID guessing; and restart snapshots require both test characters offline before the BEFORE phase. See `MULTIPLAYER_TEST_DESIGN.md` and `MULTIPLAYER_ACCEPTANCE_LEDGER.json`.


## v3.18.8 banner trigger + post-storm listener guard

- Uses the user-approved cinematic gold title artwork in the browser login presentation.
- Welcome detection accepts canonical `II` or Unicode `Ⅱ` and buffers split TCP/WebSocket chunks before replacing the browser-only banner.
- The original ES2/Neolith output is not modified.
- Master gate now re-checks Neolith port 4000 after the connection storm and does not ask for credentials if the driver stopped accepting connections.
- Authenticated live client retries transient TCP refusal and reports a concise Neolith listener error instead of raw WinError-only output.

## v3.18.8 live-gate visibility + approved title artwork

- Continues directly from the user's returned v3.18.3 tree, including the two existing test characters `wolfer` and `wolfer1`; no re-creation is required for the next live run.
- The two-character resilience gate now prints login and every wave immediately, with bounded login/tell waits, so a healthy run no longer looks frozen.
- Tell delivery observes sender and recipient concurrently in one bounded window while preserving the canonical 3-second sender cooldown.
- The approved centered gold `東方故事 II / 天朝帝國 / Celestial Empire` artwork is bundled at `web/login_title_v3184.png` and replaces only the browser presentation of the canonical login banner. Canonical MUD output/gameplay remains authoritative.

## v3.18.3 tell acceptance correction

The authenticated multiplayer resilience gate now follows canonical `/cmds/std/tell.c`: each sender is paced beyond the source-defined 3-second `MIN_TELL_INTERVAL`, sender and recipient output are observed independently, and failures are classified (cooldown / missing player / link-dead / ignore / no delivered token). The master report now embeds the live gate counters plus a small password-free failure sample, so a failed Windows run is diagnosable without repeating credentials blindly. Gameplay code is unchanged.

## v3.18.3 live acceptance hotfix
- Character/login IDs accept 3–12 lowercase letters and digits (`a-z`, `0-9`).
- Multiplayer Master authenticated gate accepts digit-bearing existing IDs and validates their canonical login save shard before password entry.
- Landing page keeps 「進入遊戲」 inside the artwork; the invisible click target is aligned to the gold button baked into `web/title_bg.png`.
- The landing art uses its native 1312×1199 aspect ratio so the clickable region scales with the actual image instead of a mismatched 3:2 canvas.

---

# ES2 WebMUD v3.6.0

## v3.6.0 介面修正 + HUD 靜默更新
- 首頁主視覺改為固定 3:2 畫布置中顯示，避免 `cover` 在 16:9 螢幕把標題放大裁切；真正的「進入遊戲」點擊區重新對齊背景按鈕。
- `START_ES2.bat` 現在只啟動 Neolith 與 WebMUD，不再自動開瀏覽器；新增 `OPEN_ES2_BROWSER.bat`，需要玩時再單獨開啟瀏覽器。
- HUD 仍每 2.5 秒向玩家自己的 canonical ES2 session 查詢 `hp`，但輪詢回應、`>` prompt 與空白行改為前端靜默消化，不再污染左側遊戲畫面。
- 角色 HUD 改成分色：形體、精、氣、神、食物、飲水、疲勞各自有不同色彩，數值與進度條同步。
- 原生 welcome banner 在 WebMUD 呈現層改為置中彩色標題卡；原始 ES2 welcome 檔與登入規則不變。
- 右側「手動存檔」按鈕改為「裝備欄」，仍只送出 canonical `inventory`，由原生輸出中的 `ˇ` 裝備標記決定內容。
- 多人 bridge v3.5 的 session 隔離、容量、heartbeat、慢客戶端保護全部保留。

## 啟動方式
1. 雙擊 `START_ES2.bat`，只開 Neolith + WebMUD 兩個服務視窗。
2. 需要進遊戲時，再雙擊 `OPEN_ES2_BROWSER.bat`。
3. 關閉瀏覽器不會自動關掉伺服器；要停止服務時關閉兩個服務視窗即可。

---

# ES2 WebMUD v3.4.0

## v3.4.0 即時 HUD + 多人連線第一階段
- 登入首頁改用單一正式主視覺，不再疊加第二組 HTML「東方故事二／天朝帝國」，也移除背景下方舊的登入／建立帳號選單。畫面上的「進入遊戲」區域仍是真正可點擊的 HTML hit target。
- 玩家進入世界且 WebMUD 已辨識目前房間後，瀏覽器每 2.5 秒在**一般指令提示狀態**下向 canonical ES2 發出一次 `hp` 查詢，HUD 因此可持續更新。特殊選單、密碼、Y/N/數字輸入狀態不輪詢，避免干擾原生 input_to。
- HUD 輪詢只解析 ES2 回傳數值；WebMUD 不自行計算 HP、精、氣、神、食物、飲水、疲勞。輪詢產生的 `hp` 摘要行不在左側終端重複刷屏。
- 多人 bridge 第一階段完成：每個 Browser WebSocket 仍建立獨立 TCP 連線到 Neolith，加入 `MAX_SESSIONS` 容量限制、TCP connect timeout、TCP_NODELAY、WebSocket heartbeat/殭屍連線清理。
- `/api/sessions` 改為 localhost-only，避免公開遠端 IP／session 細節；新增只回傳 count/capacity 的 `/api/online-count`。
- 新增 8 客戶端 fake-MUD 隔離測試：8 個 WebSocket 取得 8 條不同 TCP session，驗證沒有 cross-talk。這是 bridge 層測試；真正 Neolith 多玩家登入、互動與同時存檔仍需 Windows 實機下一階段驗收。

## v3.1 雙軌操作與持久化驗收
- 保留原本指令輸入框，所有數字選單仍可直接鍵入 `1 / 2 / 3...` 後 Enter。
- 瀏覽器偵測 ES2 自己輸出的「請輸入選項數字」選單，額外顯示直式可點按鈕；按鈕只送回相同數字，不自行決定遊戲規則。
- 數字選單轉譯位於共用 `input_prompt()` / `cursor_translate()`，不是只針對種族，因此同型態遊戲選項共用同一套介面。
- 建角密碼維持 Neolith `input_to(..., 1, ...)` no-echo，WebMUD 同步切換 password input，且 session evidence / history 不記錄密碼。
- 斷線立即保存 body + login link；玩家首字母 save 目錄權限限制在自己的 canonical `/data/user`、`/data/login`、`/data/mail` 路徑。
- 新增 v3.1 回歸測試，鎖定數字選單、密碼保密、斷線保存與 scoped save 權限。


## 最簡單啟動

Windows 直接雙擊專案根目錄的 `START_ES2.bat` 啟動 Neolith 與 WebMUD Bridge；瀏覽器改由 `OPEN_ES2_BROWSER.bat` 單獨開啟。

v3.0 將目前登入/建角的選擇介面改為直列數字選單，例如 `1. 是 / 2. 否`、`1. 人類 / 2. 化身神`、`1. 女性 / 2. 男性 / 3. 無法判斷`。玩家只需輸入數字後按 Enter。底層種族、性別與其他遊戲規則仍由原始 ES2 mudlib 決定。

角色保存已加入 Neolith 相容修正，並在斷線時立即保存角色與登入資料。正常 `quit` 仍沿用原始 ES2 保存流程。詳細說明見 `docs/V30_WEBMUD_COMPAT.md`。

---

# ES2 WebMUD Source-Only v1.5

唯一遊戲資料/規則來源：`https://github.com/taedlar/es2_mudlib`。

## v0.4 已完成
- Browser WebSocket -> Telnet/Neolith bridge。網頁不重做戰鬥。
- Source policy guard：工作樹 marker + Git origin 檢查，避免誤吃舊專案。
- 全 mudlib 索引器：room / npc / item / skill / command / daemon / feature / prototype / include。
- 抽取 inherit、functions、short/long、name/ids、exits、objects、set_skill、map_skill、部分標準欄位與 SHA-256。
- 複雜 add_action / door / timed logic / vendor / leader / damage logic 標記 manual_review，不猜規則。
- Graph auditor：檢查斷掉的出口、物件引用、重複 path、manual-review 數量。
- Source workbench：分類、搜尋、檢視索引資訊、直接編輯 canonical LPC，存檔前備份。
- 玩家瀏覽器：方向/角色快捷鍵、指令歷史、upstream 索引狀態。
- 戰鬥核心文件 `docs/COMBAT_CORE.md`，只記錄 upstream 已確認結構與公式。
- Fixture pipeline test，不使用任何外部 gameplay 資料。

## Windows 第一次準備
```powershell
powershell -ExecutionPolicy Bypass -File .\setup_windows.ps1
```
這只會 clone `taedlar/es2_mudlib`、建立 catalog、安裝 web bridge。

索引後再跑：
```powershell
python tools\audit_es2.py catalog\generated
python tests\test_pipeline.py
```

接著依 upstream README 編譯 Neolith，啟動 ES2。Web bridge 預設連 `127.0.0.1:4000`：
```powershell
cd server
npm start
```
玩家：`http://127.0.0.1:8080/`
工作台：`http://127.0.0.1:8080/admin.html`

## Canonical 規則
Catalog 不是遊戲資料庫，只是 upstream LPC 的可搜尋索引。任何 gameplay 行為最終仍以 `source/upstream/mudlib` 執行結果為準。


### v0.4 parser expansion
Adds direct setters, attributes/stats, merchandise, add_action, equipment, study requirements/content and skill-daemon registration indexing.


## 全量索引 + 斷鏈審計

抓到唯一允許的 upstream 後，可一次完成：

```powershell
python tools/build_catalog.py source/upstream -o catalog/generated
```

會產生 `manifest.json`、分類 catalog、`all.json` 與 `audit.json`。審計目前涵蓋房間出口、房內 objects、vendor merchandise、直接 equipment 引用與 duplicate path。

## v0.4 新增可抽取欄位

NPC：race、class、level、attributes、stat maximums、skills、skill maps、merchandise、equipment、add_action。

物件：直接 `set_name` aliases、weight，以及 F_STUDY 的 required/skill 與 content。技能：register_skill_daemon 與函式索引。所有無法安全資料化的腳本行為仍保留 LPC 原碼並標 `manual_review`。


## v0.5 本輪新增

- WebSocket/Telnet bridge 加入真正的 Telnet IAC negotiation 過濾/拒絕層，避免控制碼直接漏到瀏覽器。
- 瀏覽器 ANSI SGR 顯示、斷線指數退避重連、指令歷史保留。
- `/status.html` 系統頁：顯示 upstream 是否就緒、catalog 狀態、Web session 數量與流量。
- `tools/verify_source.py`：啟動前再次檢查 canonical marker 與 Git origin，防止誤指到舊專案。
- `tools/catalog_diff.py`：之後 upstream 更新時，可比較新增/刪除/變更 LPC，避免每次全靠人工找差異。
- `run_windows.ps1`：驗來源 -> 重建 catalog/audit -> 啟動 browser bridge。
- `tests/test_transport.mjs`：Telnet transport smoke test。
- 仍然沒有加入任何其他網站、fork、舊專案 gameplay data。

### v0.5 測試

```powershell
node tests\test_transport.mjs
python tests\test_pipeline.py
```

有完整 upstream 時再執行：

```powershell
python tools\verify_source.py source\upstream
python tools\build_catalog.py source\upstream -o catalog\generated
```


## v0.7 本輪新增

- 原生 login/character lifecycle 對接：瀏覽器辨識 canonical `logind.c` 的密碼提示，輸入框自動切換 password，不保存密碼到指令歷史。
- Indexer 修正 `/adm/daemons/*` 分類，並將 `/obj/login.c`、`/obj/user.c` 分為 runtime，不再誤當一般 item。
- Indexer 新增 command name/group、`input_to`、hidden input、literal prompt 等保守索引訊息。
- `tools/build_views.py`：從 canonical catalog 產生 `world_graph.json`、`command_index.json`、`browser_summary.json`。
- `tools/core_audit.py`：強制檢查 login/user/character/attack/combat/skill/condition/statistic 與 logind/enterd/combatd/chard 等核心物件是否完整。
- `/explorer.html`：可搜尋 room/NPC/item/skill/command/daemon/runtime/feature/prototype，並看 exits、objects、merchandise、equipment、skills、skill maps 關聯。
- `/map.html`：用 room exits 建立只讀世界連線圖；畫面座標只用於排版，不會寫回 LPC。
- Source editor 備份改為時間戳多版本，不再覆蓋上一個 `.bak`；寫入限制 localhost。
- Admin 新增 runtime 分類與 `manual_review` 過濾。
- 新增 `docs/LOGIN_AND_PLAYER_LIFECYCLE.md`、`docs/CATALOG_MODEL.md`。

### 本版測試

```powershell
node tests\test_transport.mjs
python tests\test_pipeline.py
python tests\test_views.py
```

完整 upstream checkout 建立後，`build_catalog.py` 現在還會跑 core audit。任何核心物件缺失都會直接失敗，不會把不完整 catalog 當成功。


## v0.7

- 索引 `create_door()`、`call_out()`、`set_temp()`、runtime traits、inherit references、command hooks。
- 新增 `reference_graph.json`，能追 room→object、vendor→商品、NPC→裝備，以及反向「誰引用我」。
- 新增 `vendor_index.json`、`npc_index.json`、`item_index.json`、`skill_index.json`。
- `/content.html`：NPC／物品／技能／商店／指令專用瀏覽器。
- `/explorer.html` 現在可以沿 incoming/outgoing reference 導航。
- Audit 新增 `door_without_exit`，門存在但沒有相應出口會報警。
- Vendor runtime 與 merchandise 靜態資料分離，不把庫存機制錯當成 JSON runtime。
- 所有複雜 `add_action`、`call_out`、door 狀態等仍由原 LPC 執行。


## v0.9

- 裝備索引新增 `wear_as`、`apply_armor/<slot>`、`setup_*()` 與 generic apply mapping。
- 新增 `equipment_index.json` 與 `equipment_audit.json`。
- 新增 `combat_npc_index.json`：只整理 NPC 原碼中的 level/attributes/stat maxima/skills/maps/equipment。
- 新增 `combat_core_index.json`：標出哪些 LPC 檔接觸 attack/defense/damage/weapon/armor/skill/condition/death/busy。
- `/content.html` 增加「裝備」「戰鬥 NPC」「戰鬥核心」。
- 玩家頁的 score / skills / inventory 現在會另外鏡像原始 ES2 回應，瀏覽器不重算任何數值。
- 裝備審計會檢查 `wear_as` 與 `apply_armor/<slot>` 是否一致。
- 不加入任何其他來源 gameplay data。

### v1.0 HUD 補強

`score` HUD 只解析 upstream `cmds/usr/score.c` 明確輸出的欄位：等級、形體(HP)、精(gin)、氣(kee)、神(sen)、食物、飲水、疲勞。原始文字仍完整保留；HUD 只是顯示層，不成為角色狀態來源。


## v1.1
- Observation-only HUD for score, skills and inventory.
- Source parser indexes condition hooks, death hooks and combat message traits.
- lifecycle.html links maintainers back to canonical LPC searches.
- No browser-side combat/death/condition authority.


## v1.2

- 新增技能 contract 索引：`valid_enable / valid_learn / skill_improved / skill_advanced / attack_using / dodge_using / parry_using / exert_function / perform_action / practice_skill`。
- 新增裝備生命週期索引：wear/remove/wield/unwield/query/setup。
- 新增 damage contract 索引：strength/ability/defend/absorb/inflict/receive/attack/fight。
- 新增互動 hook 索引：accept_object/accept_fight + 既有 add_action/call_out/door。
- `/contracts.html` 可以按技能、裝備、傷害、互動四條線檢視原始 LPC 介面。
- 新增 advisory `contract_audit.json`。Inheritance 可能補足的介面只提示，不誤判為硬錯。
- 新增 `INTEGRITY.json`，封包每個檔案都有 SHA-256，方便確認版本沒有被混入舊資料。
- 瀏覽器仍不計算戰鬥、不執行技能、不決定裝備效果。


## v1.3
- 新增 exact-source 技能 registry 與 dependency graph。
- `map_skill`、literal `SKILL_D("...")`、`wield_as`、literal weapon damage skill 都可連到唯一註冊的 skill daemon。
- `SKILL_D(variable)` 等動態派送維持 unresolved，不猜測。
- 新增 `npc_combat_profiles.json`，把 NPC skill/map/equipment/combat surface 集中檢視。
- 新增互動 script audit：`add_action` / `call_out` handler 若不是本檔函式會 advisory 標示，因為可能由 inheritance 提供。
- 新增 `/dependencies.html` 技能/武器依賴鏈瀏覽器。


## v1.4
- `world_audit.json` summarizes `/d/<domain>` content, manual review and interaction hooks.
- Structural orphan hints for NPC/item/skill, never treated as hard deletion candidates.
- `triage.json` ranks manual_review, unresolved dependencies, interactions and audit issues for review.
- `/audit.html` world audit dashboard.
- `source_status.json` + `/source.html` show origin/branch/commit/dirty/catalog/core status.
- Gameplay source remains restricted to `taedlar/es2_mudlib`.


## v1.5
- 修復 v1.2 `build_catalog.py` 縮排回歸。
- 真實 catalog 重建現在強制先通過 canonical Git origin 驗證。
- 新增 localhost-only `/operator.html`：來源驗證、重新索引、備份列表、diff、restore。
- restore 與 reindex 在來源驗證失敗時會拒絕執行。
- 新增 `runtime_readiness.py`，檢查 mudlib、neolith.conf、Neolith 路徑與 MUD TCP port。
- 不提供任意 filesystem 操作，source edit 仍只限 `mudlib/*`。


## v1.5
- 新增 read-only TCP runtime probe，不送帳密、不改遊戲資料。
- 新增 canonical login transcript validator，分辨既有角色登入與新角色建立 prompt。
- 新增 `/runtime.html` 與 `/api/runtime-probe`。
- 新增 `smoke_windows.ps1`，可在 Windows 一次跑來源驗證、readiness 與 TCP probe。
- 明確把「port 有開」和「遊戲真的驗證完成」分開，避免假性完成。


## v1.5
- 新增 runtime evidence bundle 格式與 SHA-256 manifest。
- 最終實機驗證固定要求 source、smoke、login、movement、combat、reconnect 六類證據。
- 新增 `/evidence.html`。
- 測試流程拆出 `test_v15_fast.py`，避免把完整 fixture pipeline 塞進單一長測試而被環境 timeout。
- 本版本仍未聲稱已在此環境跑過真實 Neolith session。


## v2.9
- `hp`、`skills`、`inventory` 觀測 parser 已改為依照 canonical command source 的精確格式。
- `hp` 保留 current/effective 與 current/maximum 的差異，不把兩者混成同一種上限。
- `skills` 解析 source ID、中文名稱、映射技能、有效等級與明示 delta；只有明示 delta 時才回推 raw base level。
- `inventory` 解析官方負重百分比、`ˇ` equipped 與 `◎` keep 標記；不從物品名猜裝備 slot。
- 新增 `build_player_observation.mjs`，把真實 hp/skills/inventory transcripts 轉成帶 SHA-256 的 observation JSON，供 runtime evidence 使用。
- 修正 `skills -a` 等帶參數指令仍能進入 raw capture。


## v2.9
- `score` 升級為 source-confirmed 結構化觀測：等級、karma、八屬性、HP/精/氣/神/食物/飲水/疲勞。
- 八屬性只有官方輸出明確帶 `(+/-delta)` 時才回推 base。
- `go` / `look` 新增 exact-message failure classifier；成功移動不靠 absence-of-error 猜測。
- 新增 `replay_session.mjs`，可離線重播真正捕獲的 command/response JSONL。
- 新增 `/replay.html` 與 replay coverage validator。
- gameplay source 仍只有 `taedlar/es2_mudlib`。


## v2.9
- 新增 browser-side `SessionRecorder`，直接保存 command/response raw evidence。
- 新增 `/session.html`，可匯出 JSONL 與 session manifest。
- 新增 `build_session_evidence.mjs`，把瀏覽器 capture 接到既有 replay parser。
- 新增 session coverage gate，要求 score/hp/skills/inventory/look/movement 六項都有實機紀錄。
- reconnect 次數也進 manifest，但不把「有 reconnect 次數」直接當作重連成功。
- gameplay source 邊界維持 `taedlar/es2_mudlib` only。


## v2.9
- 新增 canonical lifecycle event classifier：昏迷、甦醒、死亡、魂飛魄散、比試勝負、reconnect。
- 新增 `build_acceptance_matrix.mjs` 與 `final_runtime_gate.mjs`。
- 最終 acceptance 固定檢查 score/hp/skills/inventory/look/movement/combat/unconscious/revive/death/reconnect。
- command coverage 與真正 runtime success 明確分離；movement success 仍不靠猜。
- 新增 `/acceptance.html`。
- gameplay source 邊界仍是 `taedlar/es2_mudlib` only。


## v2.9
- 新增 `preflight.py`：canonical source、Python、Node、npm、Neolith 路徑、neolith.conf、MUD port 一次檢查。
- `setup_windows.ps1` 改成來源驗證優先的五段式流程。
- `runtime_online` 與 gameplay acceptance 嚴格分離。
- 下一階段正式轉入 canonical checkout + Neolith 實機回歸。


## v2.9
- 正式加入 multiplayer validation。
- `audit_multiplayer_bridge.py` 驗證每個 WebSocket 都在 connection handler 內建立自己的 TCP session。
- `multiplayer_probe.mjs` 可一次建立 10/50/... 個並發 WebSocket，確認 bridge session 能並行建立。
- 新增 `/api/health` 與 `/multiplayer.html`。
- 真實多人登入、同房間可見、聊天、移動、戰鬥、重連仍必須在 canonical Neolith runtime 上實測，不靠結構推論。


## v2.9
- 修掉 v2.1 多人審計測試的 Python 子程序 timeout 路徑，改成 Node 原生審計。
- 新增 `runtime_plan.py`：只搜尋真正存在的 Neolith binary，不猜路徑。
- 新增 `runtime_windows.ps1`：verify → catalog → runtime plan → preflight → optional Neolith start → WebMUD bridge。
- Neolith 只有在「剛好找到一個 binary + neolith.conf 存在」時才允許自動啟動。
- 新增多人實機 test-plan generator，要求 10/50 並發、雙帳號隔離、同房、聊天、移動、戰鬥、斷線與重連逐項留下證據。


## v2.9
- Admin reindex 改為 single-flight；同時第二個 reindex 直接 409，不再並行踩 catalog。
- 新增 `/api/admin/jobs`，顯示目前與最近的 admin jobs。
- restore 覆寫前必建 `pre_restore` safety backup，並回傳 before/restore/after SHA-256。
- source PUT 也回傳修改前後 SHA-256。
- 本輪不加入任何 gameplay 資料，只強化實機管理安全。


## v2.9
- 大修 browser session evidence：密碼輸入永不寫入 command / JSONL / storage，只留下 redacted operational event。
- 修正 raw ES2 response 沒有真正寫進 recorder 的缺口。
- recorder 改為 sessionStorage 持久化，同一瀏覽器 session 可跨 game/session 頁讀取 evidence。
- 主遊戲頁直接加入 JSONL / Manifest 匯出與清除按鈕。
- 新增 session SHA-256 hash chain 與 tamper validator。
- 新增 package release audit 與 `verify_release_windows.ps1` 統一實機 release gate。
- gameplay source 邊界與原始 ES2/Neolith authoritative architecture 完全不變。


## v2.9
- Runtime evidence validator 現在重新計算每個檔案 SHA-256 與 bytes，不再只檢查存在。
- 新增 session package：JSONL → replay → session evidence → hash chain → acceptance → manifest 一鍵封裝。
- 新增 session package validator，能抓檔案竄改、hash 不符、chain 失效與 acceptance manifest 不一致。
- Multiplayer plan 每個 PASS 必須綁 evidence 檔；attach 時複製進專屬 evidence 目錄並鎖定 bytes/SHA-256。
- 新增 `final_campaign_gate.py` 與 `final_campaign_windows.ps1`，最後只在 release/runtime/session/multiplayer 四大 gate 全過時 PASS。
- 不生成、不猜測任何 gameplay 結果；最終 gate 只驗證實機留下的 evidence。


## v2.9
- movement acceptance 不再把 `go` command coverage 當成功；必須有 look-before / go / look-after 的實際 transition evidence。
- session package v2 自動包含 movement-transition evidence，acceptance matrix 升級為 v2。
- runtime evidence validator 從純 hash 驗證升級為 hash + semantic minimums。
- `runtime_windows.ps1` 改為 fail-closed：preflight 失敗直接停止，不再繼續啟動 bridge。
- 新增 `closeout_windows.ps1`，一鍵 build session package → validate → final campaign → HTML dashboard。
- 新增 campaign dashboard builder，實機收官後可直接看到各 gate PASS/FAIL 與原因。


## v2.9
- 新增 validation campaign provenance，避免把不同版本/不同測試輪的綠燈拼在一起。
- `source_fingerprint.py` 對完整 `mudlib/**` 做 deterministic SHA-256 tree fingerprint，連本地 LPC 修改也會反映。
- release / runtime bundle / session package / multiplayer plan 全部綁同一 campaign ID、campaign SHA、project version、Git commit、mudlib tree SHA。
- final campaign gate v2 新增 provenance gate，任一 artifact 綁定不同就直接 FAIL。
- 新增 `start_validation_campaign_windows.ps1`，一鍵建立 source status、source fingerprint、campaign.json 與 multiplayer plan。
- `closeout_windows.ps1` 升級為 provenance-aware 收官流程。


## v2.9
- 修正 Windows PowerShell 5.1 解析 `source/fetch_es2.ps1` 的編碼問題。
- `fetch_es2.ps1` 與 `setup_windows.ps1` 改為 ASCII-only，避免繁中 Windows 將 UTF-8 無 BOM 誤解為 ANSI。
- 其餘 `.ps1` 統一以 UTF-8 BOM 儲存。
- Windows 腳本一律改用 `npm.cmd`，避開 PowerShell execution policy 阻擋 `npm.ps1`。
- setup 開始前先檢查 Git / Python / Node / npm.cmd。
- 新增 Windows script compatibility audit。


## v2.9
- 修正第一次完整 canonical repo 實機 catalog audit 發現的路徑錯誤：`char_statistic` 改為官方實際 `/feature/statistic`。
- `setup_windows.ps1` 支援既有 canonical `source/upstream`，驗證通過後直接續跑，不再一律報錯。
- 若 v2.8 與 v2.9 都在 `C:\ES2`，會自動找到 v2.8 已下載的 `source\upstream` 並複製沿用。
- 新增 `resume_from_v28_windows.ps1`，給本次實機升級直接使用。
- 保留 v2.8 PowerShell 5.1 / npm.cmd 相容性修正。


## v3.2.1 runtime hardening

- Long-text pager is now line-mode and numeric: 1 next page, 2 previous page, 3/4 line movement, 5 first, 6 last, 0 quit. The WebMUD renders these as clickable vertical buttons as well.
- Online characters receive a persistence checkpoint every 5 minutes; quit and disconnect still save immediately. `net_dead()` no longer performs a redundant second link save.
- Browser terminal output strips non-SGR ANSI/VT100 cursor-control remnants while preserving color SGR sequences.
- Password mode is visibly indicated beside the command box without recording the secret in command history/evidence.
- `START_ES2.bat` now waits for ports 4000 and 8080, avoids duplicate starts when services are already listening, and opens the browser only after both are ready.
- `CHECK_ES2.bat` provides a one-click runtime port check. `check_player_save_windows.ps1 -UserId <id>` verifies both login and body save files.


## v3.2.1 launcher hotfix
- Restored the proven v3.0 START_ES2.bat launch path after a Windows cmd.exe quoting regression in v3.2.
- start_es2_windows.ps1 now starts neolith.exe directly rather than wrapping it in cmd.exe.


## v3.3 WebMUD interface milestone

- Added a cinematic 東方故事二／天朝帝國 landing screen; the WebSocket connection begins only after the player presses 進入遊戲.
- Rebuilt the play screen as a fixed two-column viewport: only the left terminal scrolls as game text grows; the right HUD stays in place.
- Removed browser-generated numbered-choice buttons. Canonical non-binary menus stay as vertical 1/2/3/... text prompts; binary confirmations are displayed as Y/N.
- Replaced the old raw score-output card with a compact 7x7 nearby-room map derived only from generated canonical `world_graph.json`. The detected current room is always rendered in the center.
- Kept operational command buttons in the right sidebar and reserved three intentionally blank slots for later features.
- Improved browser ANSI presentation, including canonical 256-color foreground/background sequences, while leaving raw ES2 output authoritative.
- Room/exit/combat presentation gets lightweight browser-only highlighting; it does not change game rules or source data.


## v3.5.0 Multiplayer transport hardening

- WebSocket bridge 新增 64 KiB 單訊息 payload 上限，避免單一瀏覽器用超大訊息吃掉記憶體。
- 新增 slow-client backpressure 保護；瀏覽器累積未送資料超過 1 MiB 時會中止該 session，不拖累其他玩家。
- heartbeat interval 可配置，並保留每個 WebSocket 對應一條獨立 Neolith TCP session。
- session cleanup 改為 idempotent，TCP close / WebSocket close 競態不會重複清理同一 session。
- SIGINT/SIGTERM 增加 graceful shutdown，先關閉 WebSocket 再結束 bridge。
- `/api/multiplayer-health` 提供純 aggregate 指標：active / connected / connecting / capacity / peak、accepted / rejected / tcp errors / ws errors；不公開玩家 IP 或 session 細節。
- `/api/online-count` 改成只把已完成 TCP 連線的 session 算進 count，另列 connecting。
- 新增 50-client burst + 4×20 churn 測試，驗證 130 次 session 建立/清理、無 cross-talk、最後 active=0。
- 新增 capacity boundary 測試，確認超出容量的 client 以 WebSocket 1013 被乾淨拒絕。
- 新增 `CHECK_NEOLITH_CONCURRENCY.bat`：在 Windows 真實 Neolith 已啟動時，一次建立 20 條 raw TCP 連線，確認每條都收到 canonical login banner。
- 新增 `CHECK_MULTIPLAYER_STRESS.bat`、`CHECK_MULTIPLAYER_CAPACITY.bat`。
- `/multiplayer.html` 新增 live aggregate health 顯示。
- 這些改動僅屬 transport/runtime hardening，不改任何 ES2 gameplay rule。


## v3.8 multiplayer validation
- `CHECK_LIVE_MULTIPLAYER.bat`: two existing real-character login/tell/save acceptance against live Neolith. Passwords are hidden and not persisted.
- `START_ES2_LAN.bat` + `CHECK_ES2_LAN.bat`: trusted same-LAN phone/PC staging only.
- `python tools/audit_multiplayer_deep.py`: deeper canonical multiplayer source audit.


## v3.9 multiplayer resilience
Run `CHECK_LINKDEAD_RECONNECT.bat` after Neolith is running and when two existing test accounts are available. It intentionally drops one TCP connection, logs that account back in, verifies the canonical reconnect path, retests private messaging, then checks saving on both accounts. Passwords are requested interactively and are not stored.

### v3.10 multiplayer combat checkpoint

`CHECK_MULTIPLAYER_COMBAT.bat` verifies canonical ES2 PvP/team/shared-combat invariants without replacing game logic in the Web layer. This checkpoint is intentionally source-only; live two-character combat remains a Windows/Neolith acceptance gate.


### v3.11.0 multiplayer death-path audit
Run `CHECK_MULTIPLAYER_DEATH.bat` to verify the canonical death/corpse/PK/revival source contracts. This does not substitute for live Neolith acceptance with real player characters.

### v3.12 multiplayer live gates
After starting Neolith, `CHECK_MULTIPLAYER_SOAK.bat` runs a two-account live soak and writes a password-free report to `logs/multiplayer_soak_latest.json`. `CHECK_SAVE_INTEGRITY.bat` verifies concurrent player saves at the canonical sharded data paths. Use dedicated test characters because the tests deliberately connect, save, and periodically simulate an abrupt disconnect/reconnect.


## v3.13 multiplayer priority
- Added `CHECK_MULTIPLAYER_ROOM.bat` for two-real-character room speech, team, follow and guard acceptance.
- Added a 13-contract canonical multiplayer movement/room/team/guard audit.
- The live test uses only existing characters and real exits selected from live `look` output; it does not teleport or create substitute gameplay data.


### v3.14 multiplayer shared-world gate
Run `CHECK_MULTIPLAYER_SHARED_WORLD.bat` after starting Neolith. Use two existing test characters already placed in the same real room. Optional item/NPC identifiers must refer to objects visibly present in the canonical game world.


### v3.16 multiplayer
Run `CHECK_NEOLITH_STORM.bat` while Neolith is running to exercise 250 real-driver connection attempts in five concurrent waves, followed by a listener-survival probe.

### v3.17 multiplayer endurance / restart recovery
- `CHECK_MULTIPLAYER_ENDURANCE.bat`: 500-session bridge churn/isolation/cleanup regression.
- `CHECK_RESTART_BEFORE.bat` + `CHECK_RESTART_AFTER.bat`: two-phase canonical save-file integrity check across a real Neolith restart. Save both test characters before the BEFORE snapshot; the tool never stores passwords and never edits gameplay files.


## v3.18 multiplayer master acceptance

For the consolidated Windows multiplayer gate, start the server with `START_ES2.bat`, then run `CHECK_MULTIPLAYER_MASTER.bat`. The master gate consolidates source audits, bridge isolation/endurance, real Neolith connection storm, and two-existing-character save/reconnect resilience into one report: `multiplayer_master_report.json`. Tests that require a deliberately chosen real room/NPC/combat/restart condition remain separate assisted gates.


### v3.18.1 multiplayer login-gate hotfix
The live two-character gate now validates canonical ES2 login IDs before asking for passwords. IDs must be 3-12 letters a-z only; numeric IDs such as `test01` are rejected immediately. It also verifies the canonical `/data/login/<initial>/<id>.o` file exists and distinguishes invalid-ID, new-character, corrupt-save, and bad-password failures.


## v3.18.8 live blocker fixes
- Fixed canonical local `tell`/`reply` load failure caused by stale missing `<net/dns.h>` / `GTELL` dependency; absent inter-MUD branch is compile-guarded, local behavior remains source-defined.
- START_ES2 is version-safe and refuses to mix old/new WebMUD or Neolith processes on ports 8080/4000.
- Master verifies running build identity and tests authenticated multiplayer before the heavy Neolith storm.
- Browser login art is driven by the connection/login phase rather than fragile title-text matching.


## v3.18.8 packaging identity fix
The v3.18.6 archive accidentally retained the top-level folder name `es2_v3185_work`. Therefore a Windows Neolith title containing that path did not by itself prove an old process was running. v3.18.8 corrects the archive root name and prints the resolved project root, release version, and Neolith executable path at startup. Startup remains fully root-relative. Existing wolfer/wolfer1 saves are preserved.

### Multiplayer test labels in v3.18.8

Before running any multiplayer gate, read the label printed by its BAT file: **STATIC** means source audit only, **LIVE** means it contacts real Neolith, and **ASSISTED** means real runtime state plus an operator decision is required. `CHECK_MULTIPLAYER_COMBAT_LIVE.bat` is intentionally non-lethal by design and never sends `kill`.

### v3.19.2 multiplayer offline hardening

Added an offline fake-MUD fault matrix (`CHECK_MULTIPLAYER_FAULTS.bat`) plus fail-closed carry-forward verification for previously recorded Windows/Neolith live evidence. These tools do not alter canonical gameplay and do not claim live acceptance.

## v3.19.2 development readiness
- Adds a non-destructive offline readiness report for canonical mudlib presence, critical core objects, generated catalog coverage, manual-review visibility, and multiplayer evidence/report state.
- Does not modify canonical gameplay or the WebSocket/TCP bridge, preserving the freshness of already-passed Windows live multiplayer evidence.
- Adds `CHECK_DEVELOPMENT_READINESS.bat` and `DEVELOPMENT_READINESS.json` for the next content-production phase.

## v3.19.3 content workbench

- Adds `CHECK_CONTENT_WORKBENCH.bat` and a read-only `/workbench.html` developer view.
- Builds `catalog/generated/content_workbench.json` strictly from the canonical catalog, triage, and dependency indexes.
- Groups all explicit `manual_review` reasons, surfaces triage priority and dependency hotspots, and previews the exact upstream LPC source.
- Fixes development-readiness reporting so multiplayer evidence comes from the real ledger structure and reports are read from `reports/`.
- Does not modify canonical gameplay or the WebSocket/TCP bridge implementation, so prior covered live evidence remains eligible for carry-forward.

## v3.20.0 - Custom Home Phase 1

- Added custom Snow Inn NPC `家園傳送師` with private per-player home teleport.
- Added private `家園大廳`, 200-slot persistent no-weight storage, and `家園管家`.
- Home room development supports 10 future rooms at 10/20/.../100 gold.
- Developed rooms are generic shells until their future purposes are specified.
- Added custom Snow Inn easter-egg NPC `三屆打手槍冠軍［鐵手］林楓炎` with colored title/name and look-triggered dialogue.
- Custom additions are explicitly separated from canonical source drift checks through exact-hash approved-extension tracking.

### v3.20.2 - Custom 七彩石猜拳彩蛋
- 七彩石旁新增「正禾老變態［中仔］」：猜拳勝利 +50 文；失敗精/氣/神目前值各 -10%；平手無獎懲。
- 顯示採 ANSI：稱號黃、［中仔］亮青、勝利亮綠、失敗亮紅、50 文亮黃。
- 昏迷自動甦醒由 20 秒調整為 30 秒；真正死亡流程不變。

### v3.20.3 - Context panel / Internet launcher
- Desktop WebMUD adds a center context panel that passively summarizes room, visible people/items and combat text already emitted by ES2.
- Narrow/mobile layout hides the center panel automatically.
- Adds START_ES2_INTERNET.bat: WebMUD binds 0.0.0.0:8080 while Neolith stays local on 4000.

### v3.20.5 - Correct 4000/4001 Internet port split
- Fixes v3.20.4: Neolith config Port and mudlib MUD_PORT are now both 4001.
- Browser/WebMUD remains public TCP 4000 and bridges internally to 127.0.0.1:4001.
- The launcher now refuses to start WebMUD if Neolith is not actually listening on 4001.
- This is a runtime-network custom patch, not canonical gameplay content.

### v3.20.6 - Custom A-H race foundation
- Implements the reviewed A-H race table for human, avatar/人類族, blackteeth/黑齒, yenhold/厭火, jiaojao/焦僥, woochan/無腸 and dingling/釘靈.
- Numeric conflicts for human/avatar now follow the supplied new race table; birth gin/kee/sen and attribute rolls are applied at race initialization.
- Adds race passives and commands: `resurge`, `radiate`, `gnaw`, `breathe`, `hide`, `replete`, `hoof`.
- Standardizes 移動力 as 行動力 (`move` ability); defense ability remains dynamic from attributes plus race bonus.
- Adds per-race class level-cap metadata and enforcement at level-up.
- Adds the five previously missing A-H race choices to character creation and labels `avatar` as 人類族.
- Adds `audit_custom_races.py` and `docs/CUSTOM_RACE_A_H.md` for source-boundary and rule regression checks.
- Fixes the Snow Inn 林楓炎 display so title/nickname/name are composed once instead of duplicating the title and nickname.

## v3.20.7 WebMUD interaction polish + recall

CUSTOM extensions approved by the user:
- WebMUD now highlights both single-exit and multi-exit room lines.
- Standalone in-world `>` prompts are hidden in the browser presentation so they do not consume a blank line; raw MUD protocol behavior is unchanged.
- Door open/close actions explicitly broadcast to other players in the same room while the actor receives a second-person message.
- The center context panel lists interactable people/items in normal exploration. During combat it switches to a compact self-vs-target HUD showing HP/gin/kee/sen and does not mirror combat prose.
- Added read-only `webhud` LPC bridge for the browser combat panel.
- Added `recall`: returns to Snow Inn. `recall home`: opens the player's private home instance. Both are blocked while fighting or busy.


## v3.20.8 HUD inventory + test gold

- Context parser now only accepts NPC/item entity lines while parsing an active room description, after stripping ANSI/control sequences. Command/color-code output no longer contaminates room context.
- Combat HUD uses equal-width left/right cards and fixed numeric columns for aligned HP/gin/kee/sen values.
- Added a server-fed inventory panel below the context/combat area. Food, drink containers, armor and weapons expose buttons that submit canonical `eat`, `drink from`, `wear`, or `wield` commands. No gameplay effects are implemented in JavaScript.
- Snow Inn contains an approved CUSTOM test fixture `測試用黃金（100兩）`; every pickup grants 100 canonical gold and the fixture remains available for repeated testing.


## v3.20.10 WebMUD chat pane
- Compresses repeated terminal blank lines and suppresses standalone post-login `>` prompts.
- Adds a dedicated center-column message pane below CONTEXT with `CHAT` / `TELL` tabs.
- `CHAT` captures only canonical `【閒聊】...` channel output.
- `TELL` captures private `tell` and `reply` send/receive output.
- Local `say`, NPC speech, rumor/system/music/wizard channels, combat and ordinary room output are intentionally excluded.
- The pane mirrors server text only; it does not implement messaging rules in JavaScript.


## v3.20.13
- WebHUD polling is now terminal-silent: internal `webhud` responses and their blank lines no longer make the main console jump every few seconds.
- The right-side role-status HUD is fed by the silent LPC WebHUD bridge, so HP/精/氣/神 and food/water/fatigue appear without manually typing `hp` or `score`; level is also supplied.
- `score` gin/kee/sen text bars use square glyphs (`■` filled, `□` recoverable) instead of percent/greater-than glyphs.
- This `score.c` display change is an approved CUSTOM PRESENTATION PATCH; underlying ES2 stat calculations are unchanged.


## v3.20.13 live HUD / chat / Woochan display patch
- CHAT (`chat`) no longer requires level 2; other public-channel level gates remain unchanged.
- Combat HUD polls every 1 second and also refreshes shortly after normal incoming combat/game text, without requiring a classic `>` prompt.
- Woochan food is fixed at `0/0`; hunger does not block Woochan's normal stat healing, while water remains required.
- `score` gin/kee/sen tri-bars use 25 cells instead of 50.


## v3.20.13 WebMUD live HUD refinement
- Battle panel adopts approved Scheme A: compact two-column VS layout with fixed numeric alignment and segmented bars.
- Silent HUD polling now uses explicit `@@WEBHUD|BEGIN/END` framing and refreshes every 400 ms.
- Live `webhud` vitals take precedence over stale manual `score` cache in the right-side character status panel.
- Internal `webhud` command/payload/prompt remains suppressed from the visible terminal; polling whitespace must not create terminal rows.

## v3.20.14 老松林第一段／高慎 placement
- 依使用者地圖，草棚 southeast 新增 10 格老松林「小路」。
- 最東端放置高慎；人物敘述依使用者授權 legacy ES2 資料整理。
- 本輪不猜測高慎技能數值或教學清單。
- 外部虎刀門技能研究另見 `reports/TIGER_GATE_LEGACY_RESEARCH.md`。


## v3.20.15
- 高慎 apprenticeship/teacher table is active as a user-approved legacy-data extension.
- Tiger special-skill formulas remain intentionally pending source evidence.


### v3.20.16
Added the user-supplied Zhenwu Camp map west of Snow south shed: 14 parade-ground nodes plus big tent, shed, camp edge and double gate, with the supplied NPC placement (2 soldiers, 4 target stakes, Lu Xinien, Mee-pei). NPC system mechanics remain intentionally deferred.

### v3.20.17 custom home update
The private home hall now contains a development notice board (`look board`). The first selectable room type is `寢室`: use `develop bedroom` or `增建 寢室`. Developed bedroom types are saved on the character. A bedroom contains a bed; `rest bed` / `上床` starts rest and restores current 精/氣/神 by 10% of each maximum every 60 seconds, capped by the corresponding effective value. `leave bed` / `下床` ends rest. This is a user-approved CUSTOM extension, not canonical ES2 content.

## v3.20.18 — 家園告示板選單／書房
- `look board` 改為直列式增建選單，會依玩家目前已建房數顯示「下一間房編號」與動態 GOLD 價格。
- 選項目前為：1 寢室、2 書房、3-5 尚未開放。
- 可用 `select 1-5` / `選擇 1-5` 選房型；保留舊 `develop/增建` 文字別名相容。
- 書房正式可建，在書房內使用原本 ES2 `study` 時，學習效率加成 20%；書本條件、技能上限、精神消耗與疲勞規則不變。
- 以上皆為 user-approved CUSTOM HOME SYSTEM，不宣稱為 canonical ES2。

### v3.20.19 — Weightless currency + automatic change (CUSTOM)
- GOLD / SILVER / COIN no longer contribute to carried weight.
- Purchases are checked against total carried money value; exact denominations are no longer required.
- After payment the remainder is automatically returned as canonical GOLD/SILVER/COIN change.
- Currency exchange values are unchanged.


## v3.20.29 CUSTOM UI milestone
- Universal multi-layer local-map presentation contract (`map/area`, `map/layer`, `map/mode`).
- Current layer only on 7x7 plane; vertical/non-compass transitions listed separately.
- Generic maze privacy: unexplored runtime destinations show as `？？？`; changed runtime exit signatures invalidate explored maze visibility.
- Gameplay authority remains LPC runtime exits.
- Five-player source-level acceptance model: 5 players x 3 laps; live Neolith/TELNET remains required when runtime is available.

## v3.20.39 Old Pine recovery integration
- Restored source-grounded Old Pine NPCs: bandit, tall_bandit, fat_bandit, bandit_chief, butterfly, wolf_dog.
- Restored source-grounded objects: short_sword, long_sword, blade, leather.
- Restored original placements: tree2 butterflies x6; pine1 tall+fat bandit; pine7 wolf dog.
- Restored fat_bandit reinforcement callback to bandit_chief.
- Connected current custom Old Pine path08 north to recovered npath1 while retaining east path09 -> Gao Shen branch.
- Added round11 audit and five-walker source-level regression. This is NOT live Neolith/TELNET acceptance.

## v3.20.42 Old Pine recovery consolidation
The last complete downloadable v3.20.39 tree was used as the base because the v3.20.40/v3.20.41 mounted directories contained documentation only. Their claimed Old Pine changes were re-created in the actual tree only where source evidence was available, then audited. Old Pine recovered rooms are now 41/41. Live Neolith/TELNET acceptance is still pending.


## v3.20.43 Old Pine final sweep
See `reports/oldpine_final_sweep_v1.md`. Old Pine recovered room set is 41/41; unresolved compatibility blockers remain explicitly isolated.

## v3.20.44 Old Pine content closeout
Old Pine is now marked CONTENT CLOSED at the source-level boundary. The recovered room set remains 41/41 and the full final sweep, dynamic-topology audit, dependency audit, runtime-topology audit, JavaScript syntax check, and five-walker whole-area source coverage all pass. Four compatibility items remain explicitly isolated and do not block content closeout: spy/black_cloth, maniac/necromancy, venomsnake/snake_poison, and the legacy parrybook study adapter. Live Neolith/TELNET acceptance remains pending and is not claimed by this closeout.

## v3.20.45 Old Pine source-level freeze
Old Pine content closeout is frozen with per-LPC SHA-256 fingerprints in `reports/oldpine_content_freeze_v32045.json`. A dedicated release gate (`tools/audit_oldpine_closeout_release.py`) verifies the 41-room set, world branch, critical mechanics, blocker truth, and legacy parrybook contract. This milestone does not claim live Neolith/TELNET acceptance.

## v3.20.56
- 修正 Web HUD 場景互動／可使用道具按鈕送出路徑：所有 `data-command` 按鈕統一呼叫前端共用 `send(command)`，不再直接自行 `ws.send()`，使按鈕與手動輸入走完全相同的 command pipeline。
- 保存使用者提供的 `升級公式.xlsx` 於 `reference/user/`，作為後續升級系統實作參考來源。

### v3.20.62 - Internet launcher stale-process fix
- Fixes a false READY condition in `START_ES2_INTERNET.bat`: v3.20.60 only checked whether TCP 4001 was listening, so an older Neolith process could make the launcher report success even when the newly started Neolith exited immediately.
- Internet startup now verifies the listener process path belongs to the Neolith executable inside the current project folder.
- WebMUD TCP 4000 is verified through `/api/version` against both current `VERSION` and project root.
- Neolith is started directly with PowerShell `Start-Process`, avoiding nested `cmd /k` quoting ambiguity.
- `server/package.json` version is synchronized to 3.20.62.


## v3.20.76
- Final skill integration is based on the v3.20.75a function declarations proven by live old-Neolith login.
- Tiger Force private thresholds/growth and the Tiger Blade, Sanmeendo and Tiger Steps restored progression/combat learned hooks are retained.
- The dedicated browser scene-interaction panel and WEBHUD ACT feed were removed at user request. Chat, combat context, usable-item controls, role status and runtime map remain.
