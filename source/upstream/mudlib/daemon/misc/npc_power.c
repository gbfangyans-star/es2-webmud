/*---
description: NPC 強度計算 —— 依種族、職業、等級、強度等級自動算出 NPC 的屬性與精氣神。
custom: NEW. WebMUD NPC 強度設計（使用者設計：各職業重要屬性排序、強度 C/B/A/S、屬性上限 45）。
---*/

// 用法（在 NPC 的 create() 裡，setup() 之前）：
//
//     set_race("human");
//     set_class("fighter");
//     set_level(10);
//     set_power("C");        // C 雜兵 / B 一般 / A 菁英 / S 頭目
//     setup();
//
// 規則：
//   屬性 = 種族擲出的基礎值 + (等級-1) x 成長速度 x 強度倍率，最高 45。
//   成長速度依職業的重要屬性排序：第 1 重要每級 0.43、第 2 重要 0.36、
//   第 3 重要 0.29、其他屬性 0.10（B 級第 1 重要屬性約在 LV70 到 45）。
//   精氣神 = 種族基礎值 + 模擬從 1 級升到目前等級的成長 x 強度倍率；每級成長
//   沿用該職業玩家升級的公式（精 = 機敏/除數、氣 = 根骨/除數、神 = 靈性/除數）。
//   A、S 級等級超過 20 時，每多一級精氣神再各 +10（不乘強度倍率）。
//   create() 裡用 set_attr()/set_stat_maximum() 手動指定的項目一律保留不覆蓋。

#define ATTR_CAP        45

// 強度倍率（百分比），只乘在「成長」的部分。
private mapping tier_pct = ([
    "C": 70, "B": 100, "A": 120, "S": 140,
]);

private mapping tier_name = ([
    "C": "雜兵", "B": "一般", "A": "菁英", "S": "頭目",
]);

// 各職業重要屬性，依重要程度排列。平民不偏重任何屬性。
private mapping class_attr = ([
    "fighter":   ({ "con", "str", "cor" }),     // 武者
    "scholar":   ({ "int", "dex", "con" }),     // 書生
    "soldier":   ({ "str", "cor", "cps" }),     // 軍人
    "taoist":    ({ "wis", "spi", "int" }),     // 道士
    "monk":      ({ "spi", "wis", "int" }),     // 和尚
    "alchemist": ({ "int", "spi", "str" }),     // 方士
    "thief":     ({ "cor", "dex", "cps" }),     // 盜賊
    "commoner":  ({ }),                         // 平民
]);

// 每級成長速度（百分之一點）：第 1、2、3 重要屬性，以及其他屬性。
private int *rank_rate = ({ 43, 36, 29 });
#define OTHER_RATE      10

// 各職業升級時精氣神成長的除數（精=機敏/d、氣=根骨/d、神=靈性/d），
// 與 /daemon/class/ 各職業 advance_level() 一致。平民沒有升級公式，用 5。
private mapping class_stat_div = ([
    "fighter":   ({ 4, 2, 8 }),
    "scholar":   ({ 5, 3, 3 }),
    "soldier":   ({ 3, 3, 8 }),
    "taoist":    ({ 4, 4, 3 }),
    "monk":      ({ 6, 6, 6 }),
    "alchemist": ({ 4, 4, 4 }),
    "thief":     ({ 2, 4, 8 }),
    "commoner":  ({ 5, 5, 5 }),
]);

// 菁英、頭目額外加成：等級超過 ELITE_BONUS_FROM 後，每級精氣神各 +ELITE_BONUS_PER，
// 獨立計算，不乘強度倍率。
private string *elite_tier = ({ "A", "S" });
#define ELITE_BONUS_FROM    20
#define ELITE_BONUS_PER     10

private string *all_attr = ({ "str", "cor", "int", "spi", "cps", "dex", "con", "wis" });

void create() { seteuid(getuid()); }

// 把各種寫法統一成 C/B/A/S；不認得的回傳 0。
string normalize_tier(string tier)
{
    if( !stringp(tier) ) return 0;
    switch( tier ) {
    case "C": case "c": case "雜兵": return "C";
    case "B": case "b": case "一般": return "B";
    case "A": case "a": case "菁英": return "A";
    case "S": case "s": case "頭目": return "S";
    }
    return 0;
}

string query_tier_name(string tier)
{
    tier = normalize_tier(tier);
    return tier ? tier_name[tier] : 0;
}

// 某項屬性的每級成長速度（百分之一點）。
int query_attr_rate(string cls, string attr)
{
    string *order;
    int i;

    if( !arrayp(order = class_attr[cls]) ) order = ({ });
    i = member_array(attr, order);
    return i >= 0 ? rank_rate[i] : OTHER_RATE;
}

// 基礎值 base 在等級 lv、強度 tier 下的屬性值。
int calc_attr(int base, string cls, string attr, int lv, string tier)
{
    int val;

    if( lv < 1 ) lv = 1;
    val = base + ((lv - 1) * query_attr_rate(cls, attr) * tier_pct[tier] + 5000) / 10000;
    if( val > ATTR_CAP ) val = base > ATTR_CAP ? base : ATTR_CAP;
    return val;
}

// 菁英、頭目在等級 lv 時精氣神各自的額外加成（不乘強度倍率）。
int query_elite_bonus(int lv, string tier)
{
    if( member_array(tier, elite_tier) == -1 || lv <= ELITE_BONUS_FROM ) return 0;
    return (lv - ELITE_BONUS_FROM) * ELITE_BONUS_PER;
}

// 從 1 級升到 lv 級，精氣神各自累積的成長（尚未乘強度倍率）。
// base_attr 是各屬性的基礎值；manual 中的屬性固定不隨等級成長。
int *calc_stat_growth(mapping base_attr, mapping manual, string cls, int lv, string tier)
{
    int *div, *gain, l;
    string *src;

    if( !arrayp(div = class_stat_div[cls]) ) div = class_stat_div["commoner"];
    src = ({ "dex", "con", "spi" });
    gain = ({ 0, 0, 0 });

    // 升級時的屬性是「升級前那一級」的屬性，所以從 1 級算到 lv-1 級。
    for( l = 1; l < lv; l++ ) {
        int i;
        for( i = 0; i < 3; i++ ) {
            int a;
            a = base_attr[src[i]];
            if( a && !manual[src[i]] ) a = calc_attr(a, cls, src[i], l, tier);
            gain[i] += a / div[i];
        }
    }
    return gain;
}

// 套用到 NPC 身上。由 /std/char/npc.c 的 setup() 呼叫。
// manual_attr / manual_stat：create() 裡手動指定、不要覆蓋的項目。
void apply_power(object ob, string tier, mapping manual_attr, mapping manual_stat)
{
    mapping base_attr;
    string cls, *stat;
    int lv, pct, bonus, *gain, i;

    if( !objectp(ob) || !(tier = normalize_tier(tier)) ) return;
    if( !mapp(manual_attr) ) manual_attr = ([]);
    if( !mapp(manual_stat) ) manual_stat = ([]);

    cls = ob->query_class();
    if( undefinedp(class_attr[cls]) ) cls = "commoner";
    lv = ob->query_level();
    if( lv < 1 ) lv = 1;
    pct = tier_pct[tier];

    // 屬性：以種族初始化時擲出的值為基礎。
    base_attr = ([]);
    foreach( string a in all_attr ) {
        base_attr[a] = ob->query_attr(a, 1);
        if( manual_attr[a] || !base_attr[a] ) continue;
        ob->set_attr(a, calc_attr(base_attr[a], cls, a, lv, tier));
    }

    // 精氣神：種族基礎值 + 升級成長 x 強度倍率 + 菁英／頭目額外加成。
    gain = calc_stat_growth(base_attr, manual_attr, cls, lv, tier);
    bonus = query_elite_bonus(lv, tier);
    stat = ({ "gin", "kee", "sen" });
    for( i = 0; i < 3; i++ ) {
        if( manual_stat[stat[i]] ) continue;
        if( undefinedp(ob->query_stat_maximum(stat[i])) ) continue;
        ob->set_stat_maximum(stat[i],
            ob->query_stat_maximum(stat[i]) + (gain[i] * pct + 50) / 100 + bonus);
    }

    ob->set("power_tier", tier);
}
