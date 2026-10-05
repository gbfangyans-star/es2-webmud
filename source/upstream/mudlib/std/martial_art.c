/*---
description: 新版武功共用引擎（NEW）。武功檔只填資料，選招、出招、傷害加成、
             升級給武術造詣／武學之道都在這裡處理。設計見 docs/martial_arts/。
---*/
#include <ansi.h>

inherit SKILL;

/* 以下由武功檔在 create() 裡設定。 */
string art_id;          // 技能代碼，例如 "sanmeendo"
string art_name;        // 中文名稱
string art_usage;       // enable 在哪個基本技能，例如 "blade"
string art_desc;        // 武功簡介
int art_bonus;          // 整套傷害加成 (%)
mapping *moves = ({});  // 招式：name action lvl attack defense force bonus weight damage_type

/* 升級獎勵：升到第 lv 級時
 *   武術造詣 = lv × ma_coef
 *   武學之道 = (lv − mm_minus) × mm_coef，lv >= mm_start 才給 */
int ma_coef, mm_start, mm_minus, mm_coef;
string mm_first_msg;    // 第一次獲得武學之道時的訊息（可留空）

int is_martial_art() { return 1; }
string query_art_name() { return art_name; }
string query_base_skill() { return art_usage; }
string query_description() { return art_desc; }
mapping *query_moves() { return moves; }

int valid_enable(string usage) { return usage == art_usage; }

/* 目前等級可以使出的招式；一招都不夠格時至少給第一招。 */
mapping *usable_moves(object me)
{
    mapping *list = ({}), m;
    int lv;

    lv = me->query_skill(art_id, 1);
    foreach(m in moves)
        if( m["lvl"] <= lv ) list += ({ m });
    if( !sizeof(list) ) list = moves[0..0];
    return list;
}

/* 依出招權重（預設 5）挑一招。 */
mapping pick_move(object me)
{
    mapping *list, m;
    int total, r, w;

    list = usable_moves(me);
    foreach(m in list) total += m["weight"] ? m["weight"] : 5;
    r = random(total);
    foreach(m in list) {
        w = m["weight"] ? m["weight"] : 5;
        if( r < w ) return m;
        r -= w;
    }
    return list[0];
}

/* 把招式資料轉成 COMBAT_D->fight() 用的 action。
 * pct 是另外乘上的百分比（一般 100）。 */
mapping make_action(mapping m, int pct)
{
    return ([
        "action":      m["action"],
        "attack":      m["attack"],
        "defense":     m["defense"],
        "force":       m["force"],
        "damage_type": m["damage_type"] ? m["damage_type"] : "割傷",
        "damage_pct":  (100 + art_bonus + m["bonus"]) * pct / 100,
    ]);
}

/* 武功檔可以覆寫，處理整套特效。damage 是 fight() 的傳回值。 */
void after_strike(object me, object opponent, object weapon, mapping m, int damage)
{
}

void attack_using(object me, object opponent, object weapon)
{
    mapping m;
    int damage;

    if( !opponent ) return;
    m = pick_move(me);
    damage = COMBAT_D->fight(me, opponent, art_id, make_action(m, 100), weapon);
    after_strike(me, opponent, weapon, m, damage);
}

void skill_advanced(object me, string skill)
{
    int lv;

    if( !userp(me) ) return;
    lv = me->query_skill(art_id, 1);

    if( ma_coef > 0 ) me->gain_score("martial art", lv * ma_coef);

    if( mm_coef > 0 && lv >= mm_start && lv > mm_minus ) {
        me->gain_score("martial mastery", (lv - mm_minus) * mm_coef);
        if( stringp(mm_first_msg) && !me->query("martial_art/" + art_id + "/mastery") ) {
            me->set("martial_art/" + art_id + "/mastery", 1);
            tell_object(me, HIC + mm_first_msg + NOR);
        }
    }
}
