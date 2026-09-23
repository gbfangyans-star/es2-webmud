#include <ansi.h>

inherit SKILL;

string school() { return ""; }
string type() { return "spell"; }
int valid_enable(string usage) { return usage == "spells"; }

string spell_id(string kind, int rank)
{
    if( kind == "fire" )
        return ({ "magic_fire", "earth_fire", "inferno_fire", "pure_fire" })[rank-1];
    if( kind == "freeze" )
        return ({ "chill_freeze", "ominous_freeze", "shadow_freeze", "polar_freeze" })[rank-1];
    if( kind == "storm" )
        return ({ "quick_storm", "crazy_storm", "killer_storm", "whirl_storm" })[rank-1];
    return ({ "swamp_thunder", "blaster_thunder", "divine_thunder", "hexagram_thunder" })[rank-1];
}

int spell_rank(string kind, string spell)
{
    int rank;

    for(rank = 1; rank <= 4; rank++)
        if( spell == spell_id(kind, rank) || spell == sprintf("%d", rank) )
            return rank;
    return 0;
}

int spell_cost(string kind, int rank)
{
    if( kind == "fire" ) return ({ 5, 20, 45, 75 })[rank-1];
    if( kind == "freeze" ) return ({ 5, 20, 30, 50 })[rank-1];
    if( kind == "storm" ) return ({ 10, 30, 50, 75 })[rank-1];
    return ({ 5, 50, 75, 90 })[rank-1];
}

int spell_delay(string kind, int rank)
{
    if( kind == "fire" ) return ({ 1, 1, 2, 3 })[rank-1];
    if( kind == "freeze" ) return ({ 1, 2, 0, 2 })[rank-1];
    if( kind == "storm" ) return ({ 1, 1, 1, 3 })[rank-1];
    return ({ 1, 1, 2, 2 })[rank-1];
}

int spell_power(string kind, int rank, int base, int caster_kee,
    int caster_sen)
{
    if( kind == "fire" ) {
        if( rank == 1 ) return base/2;
        if( rank == 2 ) return base/3;
        if( rank == 3 ) return base/2 + caster_kee/4;
        return base*3;
    }
    if( kind == "freeze" ) {
        if( rank == 1 ) return base/2;
        if( rank == 2 ) return base;
        if( rank == 3 ) return 0;
        return base*3/2;
    }
    if( kind == "storm" )
        return ({ base/4, base/3, base*3/4, base*5/4 })[rank-1];
    if( rank == 1 ) return base/2;
    if( rank == 2 ) return base/4 + caster_sen/8;
    if( rank == 3 ) return base/3;
    return base*7/4;
}

string cast_narration(string kind, int rank)
{
    if( kind == "fire" ) return ({
        "$N施展「咒火」，一點靈焰在指尖燃起，撲向$n。",
        "$N施展「地火」，地面裂出火紋，熱浪從$n腳下升起。",
        "$N施展「大業火」，沉重的火輪挾著灼氣撞向$n。",
        "$N施展「三昧真火」，三色真焰交纏成柱，向$n席捲而去。"
    })[rank-1];
    if( kind == "freeze" ) return ({
        "$N施展「寒冰」，掌中寒光凝成冰刃，射向$n。",
        "$N施展「兆冰」，幽藍寒氣滲入$n的精與神。",
        "$N施展「無相冰」，無形寒意悄然封向$n的四肢。",
        "$N施展「七重玄冰」，層層冰輪自$n周圍合攏。"
    })[rank-1];
    if( kind == "storm" ) return ({
        "$N施展「疾風」，袖間風符一閃，銳風直取$n。",
        "$N施展「暴風」，風勢驟然聚攏，破開$n周身的風障。",
        "$N施展「飛戮風」，利風挾著肅殺之氣割向$n。",
        "$N施展「轉輪大風」，巨大的風輪轟鳴著碾向$n。"
    })[rank-1];
    return ({
        "$N施展「澤雷」，低沉雷光沿地奔向$n。",
        "$N施展「爆雷」，掌中電光驟縮，隨即在$n身前炸開。",
        "$N施展「神光雷」，一道清亮雷芒直探$n的神識。",
        "$N施展「六卦熒雷」，六道雷光交織成卦，罩住$n。"
    })[rank-1];
}

string hit_narration(string kind)
{
    if( kind == "fire" ) return "$n被烈焰燒灼，氣息頓時一亂。";
    if( kind == "freeze" ) return "$n周身寒氣透骨，氣脈隨之一滯。";
    if( kind == "storm" ) return "$n被銳風掃中，衣袍與氣息一同震盪。";
    return "$n被雷光擊中，氣脈間迸出一陣麻意。";
}

int resistance(object target, string kind)
{
    int n;

    n = target->query_temp("apply/armor_vs_" + kind);
    if( kind == "storm" ) n += target->query_temp("apply/armor_vs_wind");
    if( kind == "freeze" ) n += target->query_temp("apply/armor_vs_ice");
    if( kind == "thunder" ) n += target->query_temp("apply/armor_vs_lightning");
    if( n < 0 ) n = 0;
    return n;
}

int spell_hits(object me, object target, string kind, int technique,
    int ignore_resistance)
{
    int chance, resist;

    resist = ignore_resistance ? 0 : resistance(target, kind);
    chance = 60 + technique/2 + me->query_ability("spell")/4 - resist/2;
    if( chance < 20 ) chance = 20;
    if( chance > 99 ) chance = 99;
    if( random(100) < chance ) return 1;
    message_vision("$N的咒文被$n抵禦開來。\n", me, target);
    return 0;
}

int elemental_damage(object me, object target, string kind, int power,
    int ignore_resistance)
{
    int resist, bonus, damage;

    resist = ignore_resistance ? 0 : resistance(target, kind);
    bonus = me->query_temp("apply/damage_vs_" + kind);
    if( kind == "storm" ) bonus += me->query_temp("apply/damage_vs_wind");
    if( kind == "freeze" ) bonus += me->query_temp("apply/damage_vs_ice");
    if( kind == "thunder" ) bonus += me->query_temp("apply/damage_vs_lightning");
    if( bonus < -90 ) bonus = -90;
    if( bonus > 200 ) bonus = 200;
    damage = power * (100 + bonus) / (100 + resist);
    if( damage < 1 ) damage = 1;
    return damage;
}

int hit_kee(object me, object target, string kind, int power,
    int technique, int ignore_damage_resistance,
    int ignore_accuracy_resistance)
{
    int damage;

    if( !objectp(target) || !living(target)
    || environment(target) != environment(me) ) return 0;
    if( !spell_hits(me, target, kind, technique,
        ignore_accuracy_resistance) ) return 0;
    damage = elemental_damage(me, target, kind, power,
        ignore_damage_resistance);
    damage = target->receive_damage(damage, me, me);
    message_vision(HIR + hit_narration(kind)
        + "（" + damage + "點氣傷）\n" NOR, me, target);
    return damage;
}

void absorb_freeze(object me, object target, int dealt, int rank)
{
    int amount, i;
    string *stats;

    if( dealt < 1 || !objectp(target) ) return;
    stats = ({ "gin", "kee", "sen" });
    amount = dealt * (10 + rank*3) / 100;
    if( amount < 1 ) amount = 1;
    for(i = 0; i < sizeof(stats); i++) {
        if( random(100) >= 55 + rank*5 ) continue;
        target->consume_stat(stats[i], amount, me);
        me->supplement_stat(stats[i], amount);
    }
}

int extra_storm_hits(int skill, int technique)
{
    int second, third;

    if( skill < 100 ) return 0;
    second = 20 + (skill-100)/4 + technique/20;
    third = 5 + (skill-100)/20 + technique/50;
    if( second > 50 ) second = 50;
    if( third > 15 ) third = 15;
    if( random(100) >= second ) return 0;
    if( random(100) < third ) return 2;
    return 1;
}

void award_spell_hit(object me, int rank, int amount)
{
    int gain;

    gain = 1 + amount/40;
    if( gain > 20 ) gain = 20;
    me->gain_score("combat", gain);
}
varargs int cast_spell(object me, string spell, object target)
{
    string kind;
    object *enemies;
    int rank, skill, technique, base, power, cost, delay;
    int dealt, second, extra, stage, caster_kee, caster_sen;

    kind = school();
    if( kind != "fire" && kind != "freeze"
    && kind != "storm" && kind != "thunder" ) return 0;
    if( me->skill_mapped("spells") != "taoism-" + kind )
        return notify_fail("你沒有使用這一系咒術。\n");
    if( me->is_busy() ) return notify_fail("你現在沒有空施咒。\n");

    rank = spell_rank(kind, spell);
    if( !rank )
        return notify_fail("此系只有四道咒文，請輸入咒文英文名或 cast 1 至 cast 4。\n");
    skill = me->query_skill("taoism-" + kind, 1);
    if( skill < 1 + (rank-1)*20 )
        return notify_fail("你的咒術修為還不足以施展這道咒文。\n");

    if( !objectp(target) ) {
        enemies = me->query_enemy();
        if( sizeof(enemies) ) target = enemies[0];
    }
    if( !objectp(target) || target == me || !living(target)
    || environment(target) != environment(me) )
        return notify_fail("這裡沒有可施咒的對象。\n");

    cost = spell_cost(kind, rank);
    if( me->query_stat("sen") < cost )
        return notify_fail("你的神不足以施咒。\n");
    caster_kee = me->query_stat("kee");
    caster_sen = me->query_stat("sen");
    me->consume_stat("sen", cost);
    me->fight_ob(target);
    target->fight_ob(me);
    message_vision(HIC + cast_narration(kind, rank) + NOR + "\n",
        me, target);

    technique = me->query_skill("spells") + skill/2;
    base = me->query_strength("spell") / 3000;
    base = base * (100 + me->query_skill("spells")) / 100;
    if( base < 10 ) base = 10;
    me->gain_score("magic", 1 + random(rank + 1));
    power = spell_power(kind, rank, base, caster_kee, caster_sen);
    if( me->query_temp("taoism/overload") ) {
        power = power*3/2;
        if( !(kind == "thunder" && rank == 4) )
            me->delete_temp("taoism/overload");
    }
    delay = spell_delay(kind, rank);

    if( kind == "freeze" && rank == 3 ) {
        if( spell_hits(me, target, kind, technique, 0) ) {
            target->start_busy(3);
            award_spell_hit(me, rank, base);
            message_vision(HIB "$n周身凝起薄冰，一時難以動彈。\n" NOR,
                me, target);
        }
        else delay = 1;
        if( delay > 0 ) me->start_busy(delay);
        return 1;
    }
    if( kind == "freeze" && rank == 2 ) {
        if( spell_hits(me, target, kind, technique, 1) ) {
            target->consume_stat("gin", power, me);
            award_spell_hit(me, rank, power);
            target->consume_stat("sen", power/3, me);
            me->supplement_stat("gin", power/2);
            me->supplement_stat("sen", power/6);
            message_vision(HIB "$n精與神一陣虛浮，寒氣回流$N體內。\n" NOR,
                me, target);
        }
        me->start_busy(delay);
        return 1;
    }
    if( kind == "thunder" && rank == 3 ) {
        if( spell_hits(me, target, kind, technique, 1) ) {
            target->consume_stat("sen", power, me);
            award_spell_hit(me, rank, power);
            message_vision(HIW "雷芒直透$n神識，$n目光一時渙散。\n" NOR,
                me, target);
        }
        if( random(100) < 15 ) {
            delay++;
            tell_object(me, HIR "雷力反噬，你需要更多時間平復氣息。\n" NOR);
        }
        me->start_busy(delay);
        return 1;
    }

    if( power < 1 ) power = 1;
    second = 0;
    if( kind == "fire" ) {
        second = power/3;
        power -= second;
    }
    dealt = hit_kee(me, target, kind, power, technique,
        kind == "fire" && rank == 2 || kind == "storm" && rank == 2,
        kind == "fire" && rank == 2);

    if( kind == "fire" && dealt > 0 && objectp(target)
    && living(target) && environment(target) == environment(me) ) {
        message_vision(HIR "$N掌勢一轉，餘焰又向$n爆開！\n" NOR,
            me, target);
        dealt += hit_kee(me, target, kind, second, technique, rank == 2,
            rank == 2);
    }
    if( kind == "fire" && rank == 2 && dealt > 0 )
        me->supplement_stat("kee", dealt);

    if( kind == "storm" && dealt > 0 ) {
        if( rank == 3 && objectp(target) )
            target->consume_stat("HP", dealt/4, me);
        if( me->query_temp("taoism/next_storm_three") ) {
            extra = 2;
            me->delete_temp("taoism/next_storm_three");
        }
        else extra = extra_storm_hits(skill, technique);
        stage = 2;
        while( extra-- > 0 && objectp(target) && living(target)
        && environment(target) == environment(me) ) {
            message_vision(HIC "$N再催" + (stage == 2 ? "第二重" : "第三重")
                + "風符，風刃接連斬向$n！\n" NOR, me, target);
            second = hit_kee(me, target, kind, power, technique, rank == 2, 0);
            if( rank == 3 && second > 0 )
                target->consume_stat("HP", second/4, me);
            stage++;
        }
        if( rank == 1 && skill >= 100 )
            me->set_temp("taoism/next_storm_three", 1);
    }

    if( kind == "freeze" && dealt > 0 )
        absorb_freeze(me, target, dealt, rank);
    if( dealt > 0 ) award_spell_hit(me, rank, dealt);

    if( kind == "thunder" && random(100) < 15 ) {
        delay++;
        tell_object(me, HIR "雷力反噬，你需要更多時間平復氣息。\n" NOR);
    }
    me->start_busy(delay);
    return 1;
}