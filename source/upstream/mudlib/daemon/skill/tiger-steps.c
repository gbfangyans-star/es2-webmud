#include <ansi.h>
inherit SKILL;

string *dodge_actions = ({
    "$N眼見攻勢逼近，腳下忽然一錯，使出狻猊步法，身形沿著$n來勢斜斜滑開，衣袂被勁風猛然掀起，轉瞬已換了方位，試圖避開這迎面而來的一擊。\n",
    "$N肩頭微沉，雙足一前一後踏出狻猊步法，身子貼著$n的攻勢急轉半圈，步幅雖小卻連續變位，整個人順勢向側面閃開，試圖讓這一擊落空。\n",
    "$N察覺$n招勢逼到近前，腰身猛然一折，狻猊步法隨念而動，腳尖點地後迅速後撤，再橫移半步，身形在刀風拳影間游走，試圖避過來勢。\n",
    "$N不退反進，腳下踏出狻猊步法，先迎著$n的攻勢踏近半步，隨即扭腰錯肩從側邊滑過，身形在極短距離內連換兩次方位，試圖從攻勢縫隙脫身。\n",
    "$N呼吸一沉，雙膝微屈，狻猊步法驟然展開，身形先向下伏再猛地側旋，足下連踏數步將來勢引向身旁，試圖在$n攻勢真正落下前閃出範圍。\n",
    "$N看準$n攻勢將至的一瞬，腳尖輕點地面，使出狻猊步法繞身疾走，前一刻還停在原處，下一刻已沿著弧線移向側後方，試圖讓迎來的一擊擦身而過。\n",
});

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("tiger-steps");
    setup();
}

int valid_enable(string usage)
{
    return usage == "dodge";
}

/*
 * User-approved presentation rule:
 * tiger-steps never changes ES2's dodge probability formula.  The special
 * skill only supplies its normal effective dodge value and emits one of six
 * attempt narratives before the core defend() result is rolled.  Therefore
 * seeing the narrative never means the dodge succeeded.
 */
int dodge_using(object me, int ability, int strength, object from)
{
    object attacker;

    if( objectp(me) ) {
        attacker = from;
        if( objectp(from) && !from->is_character()
        &&  objectp(environment(from)) && environment(from)->is_character() )
            attacker = environment(from);

        if( objectp(attacker) && attacker != me )
            message_vision(HIC + dodge_actions[random(sizeof(dodge_actions))] + NOR,
                me, attacker);
        else
            tell_object(me, HIC + dodge_actions[random(sizeof(dodge_actions))] + NOR);
    }

    return me->query_skill("dodge");
}
