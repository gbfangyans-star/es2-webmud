# 2026-09-13 正式母版整合批次

基底：使用者上傳 `ES2_WebMUD_SourceOnly_v3.20.77_REAPPLIED_ARCH6_1(2).zip`

## Round A — 已驗證功能回填
- Web UI redesign 回填。
- Build 4 FAST MAP：拓樸快取、optimistic movement、HUD authoritative correction。
- HELP pager 修正。
- 保留使用者最新版中額外 wizard/custom/runtime files，不做目錄搬家。

## Round B — 基礎武學補齊
- 23 種武器技能 registry 皆存在。
- 原 sword + 新增 22 個缺失 daemon。
- 靜態驗證 23/23：檔案、registry、COMBAT_D->fight、actions 通過。
- 報告：`reports/basic_skill_validation_integrated.json`。

## Round C — 李家村 V1
- 正式新增 `/d/lee/`。
- 38 rooms / 44 edges，依使用者最新版地圖拓樸。
- confirmed 與 generated 內容在檔頭／報告分開標記。
- 鞭法 NPC 不放。
- 外部南村口不猜接點。

## 測試
- `node --check web/app.js`: PASS。
- 李家村拓樸 validator: 0 errors。
- 5 walkers source-level topology test: PASS，0 broken exits。
- 基礎武學 integrated static validator: 23/23 PASS。
- Selected pytest: 10 pass / 3 fail；3 項皆為既有 legacy expectation/reference file 問題，不是本批次新 LPC map/skill failure。
- 全 pytest collection 會被舊 `tools/test_five_walkers_multilevel_maze.py` 的 module-level `SystemExit(0)` 中止，因此不能宣稱 full-suite PASS。
