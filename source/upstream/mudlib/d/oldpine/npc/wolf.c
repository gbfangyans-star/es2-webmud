// /d/oldpine/npc/wolf.c — 迷霧森林／老松林 野獸：土狼（強度 4，野豬為 4）。

#include <npc.h>

// 看到玩家就下殺手（kill），玩家昏倒後也會繼續攻擊直到死亡。
void init()
{
    object ob = this_player();

    ::init();
    if( objectp(ob) && userp(ob) && living(this_object()) && !is_fighting(ob)
    &&  !environment()->query("no_fight") && visible(ob) ) {
        kill_ob(ob);
    }
}

void create()
{
    seteuid(getuid());
    set_name("土狼", ({ "wolf" }));
    set_race("beast");
    set_class("commoner");
    set_level(1);
    set("long", @LONG
一口白森森的利牙，正虎視眈眈的盯著你。
LONG
    );
    set("unit", "頭");
    set("beast_actions", ({
        ([ "action": "$N猛地撲上來，張口往$n的$l咬去", "damage_type": "咬傷" ]),
        ([ "action": "$N伸出利爪往$n的$l抓去", "damage_type": "抓傷" ]),
        ([ "action": "$N繞到$n身後，往$n的$l一口咬下", "damage_type": "咬傷" ])
    }));
    // 野獸強度（1～10），數值見 daemon/race/beast.c。
    set_beast(4);
    setup();
}
