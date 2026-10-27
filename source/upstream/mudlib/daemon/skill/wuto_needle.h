// wuto_needle.h — 武陀灸堂四套針法（驚異二針、五敗針法、引源針法、三自回針法）共用。
// 設計：docs/martial_arts/武陀灸堂_門派設計.md（2026-10-27 定案）
//
// 施針指令 acupuncture <針法> [to <目標>] 會呼叫 enable 在針灸之術（cauterization）上的
// 技能檔的 acupuncture_cauterization(me, 針法, 目標)；NPC 施針不帶目標。

#define WUTO_FACTION    "alchemist.wuto"
#define TICK_SECONDS    2

int query_threshold_percent() { return 80; }   // C-05：練到 200 級共 800 萬
int valid_enable(string usage) { return usage == "cauterization"; }

// 持續效果靠 condition 的 call_out，技能檔本身不需要常駐；但保持載入比較單純。
int clean_up() { return 1; }

int is_wuto(object me) { return me->query("custom_faction") == WUTO_FACTION; }

// 學習條件：武陀灸堂弟子。各技能檔的 valid_learn() 呼叫這裡。
int check_wuto(object me)
{
    if( !is_wuto(me) )
        return notify_fail(gender_self(me) + "不是武陀灸堂弟子，學不來這門針法。\n");
    return 1;
}

// 已經學會：等級 1 以上，或求教後還沒練成（累積點數大於 0）。
int knows_needle(object me, string skill)
{
    return me->query_skill(skill, 1) > 0 || me->query_learn(skill) > 0;
}

// C-04：施針成功，該套針法與針灸之術各得一次系統悟性公式。只對玩家生效。
void needle_gain(object me, string skill)
{
    if( !userp(me) ) return;
    me->improve_skill_exact(skill, COMBAT_D->int_formula_exp(me));
    me->improve_skill_exact("cauterization", COMBAT_D->int_formula_exp(me));
}

// 把 apply 的加成以 condition 掛在目標身上，持續 ticks 個 tick（一 tick 兩秒）。
void set_needle_effect(object target, string cnd, string kind, mapping apply, int ticks)
{
    if( ticks < 1 ) ticks = 1;
    target->set_condition(cnd, ([
        "kind":   kind,
        "apply":  apply,
        "until":  time() + ticks * TICK_SECONDS,
        "serial": time() * 1000 + random(1000),
    ]));
}

// 對象：沒有指定就是自己；必須是同一個地方、清醒的人物。
object needle_target(object me, object target)
{
    if( !objectp(target) ) return me;
    if( !target->is_character() || target->is_corpse() || !living(target)
    ||  environment(target) != environment(me) )
        return 0;
    return target;
}
