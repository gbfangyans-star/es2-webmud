# 虎刀門追擊與刀法 action 實作 v3.20.46

## 來源邊界
- canonical repo 可確認 ES2 的 enable/map_skill、combat action、weapon damage 與 exert(force_ratio) 架構。
- 專案既有 legacy research 與 2010-04-28 update 記錄虎刀追擊規則：tiger blade 技能 >=90 且 exert >70，攻擊後必有第一追；第一追造成傷害（或 rage）則第二追。
- 同一更新明確取消第一追舊有約 75kg 附加力道，因此本版追擊不額外加力道。
- 2010-05-01 記錄第二追附加傷害改固定值，但現有證據沒有留下該固定數字，本版不猜數值，第二追只依正常 tiger-blade attack/action/weapon damage 結算。
- rage 尚未有可靠公式，本版不自行發明 rage；第二追目前只由「第一追造成傷害」觸發，保留未來 rage alternate trigger 接口。

## 本版規則
1. tiger-blade 普通攻擊先出一招。
2. raw tiger-blade <90 或 force_ratio <=70：結束，不追擊。
3. raw tiger-blade >=90 且 force_ratio >70：必定第一追。
4. 第一追實際 damage >0 且目標仍在同房存活：第二追。
5. 追擊沿用 tiger-blade 六式隨機 action，不加固定傷害倍率。

## Action
- sanmeendo：6 招，enable blade，單手刀。
- tiger-blade：6 招，enable twohanded blade，雙手刀。
- 招式一學會即全數可抽，不做等級解鎖。
