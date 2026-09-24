/* CUSTOM A-H RACE COMMAND: headless dance (戰舞) */
#include <ansi.h>
inherit F_CLEAN_UP;
#define DANCE_CONDITION "headless_dance"

private void create() { seteuid(getuid()); }

// 傳回 lo~hi 之間（含端點）的隨機值；hi < lo（年紀太小整數除法後常見）時視為
// lo == hi。
private int ranged(int lo, int hi) {
    if (hi < lo) hi = lo;
    return lo + random(hi - lo + 1);
}

int main(object me, string arg) {
    int age, duration;
    string mode;

    if (me->query_race() != "headless") return notify_fail("你不是刑天，無法使用戰舞。\n");
    if (me->is_fighting()) return notify_fail("戰鬥中無法使用戰舞。\n");
    if (!arg) return notify_fail("戰舞格式：dance for war／dance for glory／dance for heal\n");

    mode = arg;
    if (strlen(mode) > 4 && mode[0..3] == "for ") mode = mode[4..];

    age = me->query("age");
    duration = 20 + age;

    switch (mode) {
    case "war": {
        int dmg, atk;
        dmg = 5 + ranged(age/5, age/2); if (dmg > 50) dmg = 50;
        atk = 10 + ranged(age/4, age/3); if (atk > 50) atk = 50;
        me->set_condition(DANCE_CONDITION, ([
            "mode":"war", "duration":duration,
            "damage_bonus":dmg, "intimidate_bonus":atk
        ]));
        message_vision(HIR "$N跳起激昂的戰舞，雙眼燃起熊熊戰意！\n" NOR, me);
        break;
    }
    case "glory": {
        int def, wit, elem;
        def = 10 + ranged(age/3, age/2); if (def > 80) def = 80;
        wit = 10 + ranged(age/4, age/3); if (wit > 50) wit = 50;
        elem = 50 + ranged(age/3, age/2); if (elem > 100) elem = 100;
        me->set_condition(DANCE_CONDITION, ([
            "mode":"glory", "duration":duration,
            "defense_bonus":def, "wittiness_bonus":wit, "element_bonus":elem
        ]));
        message_vision(HIW "$N步伐莊嚴，神情顯得無比沉著。\n" NOR, me);
        break;
    }
    case "heal":
        me->supplement_stat("HP", 5);
        me->supplement_stat("kee", 20 + age);
        me->heal_stat("kee", age);
        message_vision(HIG "$N跳起輕柔的平靜之舞，身上的傷口隨著舞步緩緩癒合。\n" NOR, me);
        break;
    default:
        return notify_fail("戰舞格式：dance for war／dance for glory／dance for heal\n");
    }

    me->start_busy(2);
    if (userp(me)) me->save();
    return 1;
}

int help(object me) {
    write(
        "指令格式：dance for war／dance for glory／dance for heal\n"
        "刑天專屬戰舞，每次只能選一種，使用後 delay 2 tick，戰鬥中無法使用。\n"
        "war：增加傷害力 5+(年紀/5~年紀/2)（上限50）、攻勢等級 10+(年紀/4~年紀/3)（上限50），"
        "維持 20+年紀 tick。\n"
        "glory：增加防禦力 10+(年紀/3~年紀/2)（上限80）、守勢等級 10+(年紀/4~年紀/3)（上限50）、"
        "四屬性防禦（抗火/冰/風/雷）50+(年紀/3~年紀/2)（上限100），維持 20+年紀 tick。"
        "war 與 glory 不能同時生效，重新跳舞會直接覆蓋前一次效果。\n"
        "heal：立即恢復形體 5 點、氣現在值 20+年紀、氣上限 年紀，只生效一次、沒有持續時間，"
        "不受 war／glory 限制。\n"
    );
    return 1;
}
