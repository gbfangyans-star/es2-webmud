#include <ansi.h>
inherit SKILL;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("tiger-force");
    setup();
}

int valid_enable(string usage)
{
    return usage == "force";
}

/*
 * User-provided Tiger Force growth table.
 * Initial completion is handled by Gao Shen: level 20 + CON 1.
 * Thereafter every actually gained level permanently grants:
 *   21-140 : gin +2, kee +2
 *   141-160: gin +3, kee +4
 *   161+   : gin +1, kee +1
 * Milestones: level 100 STR +1, COR +1; level 140 COR +2.
 * A per-character growth marker prevents duplicate permanent grants.
 */
void apply_growth_to(object me, int level)
{
    int old, lv;

    if( !objectp(me) || level <= 20 ) return;

    old = me->query("tiger_force/growth_level");
    if( old < 20 ) old = 20;
    if( old >= level ) return;

    for(lv = old + 1; lv <= level; lv++) {
        if( lv >= 161 ) {
            me->advance_stat("gin", 1);
            me->advance_stat("kee", 1);
        }
        else if( lv >= 141 ) {
            me->advance_stat("gin", 3);
            me->advance_stat("kee", 4);
        }
        else {
            me->advance_stat("gin", 2);
            me->advance_stat("kee", 2);
        }

        if( lv == 100 && !me->query("tiger_force/bonus_100") ) {
            me->set_attr("str", me->query_attr("str", 1) + 1);
            me->set_attr("cor", me->query_attr("cor", 1) + 1);
            me->set("tiger_force/bonus_100", 1);
        }
        if( lv == 140 && !me->query("tiger_force/cor_bonus_140") ) {
            me->set_attr("cor", me->query_attr("cor", 1) + 2);
            me->set("tiger_force/cor_bonus_140", 1);
        }
    }

    me->set("tiger_force/growth_level", level);
}

void skill_advanced(object me, string sk)
{
    apply_growth_to(me, me->query_skill("tiger-force", 1));
}

private int tiger_force_threshold(int level)
{
    int base;
    if( level < 20 ) return 0;
    if( level <= 100 ) base = 100;
    else if( level <= 140 ) base = 150;
    else if( level <= 180 ) base = 200;
    else base = 250;
    return level * level * base;
}

void skill_improved(object me, string sk)
{
    int level, next;
    level = me->query_skill("tiger-force", 1);
    while( level < 200 ) {
        next = level + 1;
        if( me->query_learn("tiger-force") < tiger_force_threshold(next) ) break;
        me->advance_skill("tiger-force", 1);
        level++;
    }
}

/*
 * User-provided exercise notation: each Tiger Force training tick spends
 * kee 2 / effective kee 1 and gin 3 / effective gin 1.
 * This keeps training behaviour explicit without inventing sen costs.
 */
int do_exercise(object me)
{
    if( me->query_stat("kee") < 3 || me->query_stat("gin") < 4 ) {
        tell_object(me, "你覺得氣血浮動、精力難繼，已無法再運轉瘋虎功。\n");
        me->interrupt_me(me, "exhausted");
        return 1;
    }

    me->consume_stat("kee", 2);
    me->damage_stat("kee", 1);
    me->consume_stat("gin", 3);
    me->damage_stat("gin", 1);

    /* Basic force learned is evaluated once per valid exercise tick by the
     * shared restored formula.  Tiger Force itself is learned from successful
     * combat hits, not from this exercise tick. */
    me->improve_restored_force_tick();
    return 1;
}

int halt_exercise(object me, object owner, object from, string how)
{
    return 1;
}

void remove_powerup(object me, int damage_bonus, int attack_bonus)
{
    if( !objectp(me) || !me->query_temp("tiger_force/powerup") ) return;

    me->add_temp("apply/damage", -damage_bonus);
    me->add_temp("apply/attack", -attack_bonus);
    me->delete_temp("tiger_force/powerup");
    tell_object(me, HIY "你體內奔騰的瘋虎勁逐漸平復，攻勢也恢復如常。\n" NOR);
}

int do_powerup(object me)
{
    int sk, damage_bonus, attack_bonus, duration;

    sk = me->query_skill("tiger-force", 1);
    if( sk < 100 )
        return notify_fail("你的瘋虎功尚未到一百級，還無法施展 powerup。\n");
    if( me->query_temp("tiger_force/powerup") )
        return notify_fail("你現在正處於瘋虎功 powerup 的催勁狀態。\n");

    damage_bonus = sk / 4;
    attack_bonus = sk / 3;
    duration = sk * 3 / 2;

    me->add_temp("apply/damage", damage_bonus);
    me->add_temp("apply/attack", attack_bonus);
    me->set_temp("tiger_force/powerup", 1);

    message_vision(HIR "$N猛吸一口氣，瘋虎功勁力沿周身經脈暴然奔走，整個人的攻勢頓時變得更沉、更快、更具壓迫感！\n" NOR,
        me);
    call_out("remove_powerup", duration, me, damage_bonus, attack_bonus);
    return 1;
}

varargs int exert_function(object me, string func, object target)
{
    switch(func) {
    case "tiger force":
    case "tiger-force":
        message_vision(HIY "$N盤膝坐定，調勻呼吸，開始依照瘋虎功口訣運轉內息。\n" NOR,
            me);
        me->start_busy((: do_exercise, me :), (: halt_exercise, me :));
        return 1;
    case "powerup":
        return do_powerup(me);
    default:
        return notify_fail("瘋虎功沒有這種功能。\n");
    }
}
