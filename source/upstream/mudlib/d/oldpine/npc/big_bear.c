// /d/oldpine/npc/big_bear.c — 迷霧森林／老松林 野獸：大黑熊（強度 5，野豬為 4）。

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

// 被打中受傷後有 20% 機會逃往相鄰的格子。
varargs int receive_damage(int damage, object from, object attacker)
{
    int r = ::receive_damage(damage, from, attacker);

    if( r > 0 && living(this_object()) && random(100) < 20 )
        call_out("flee_away", 0);
    return r;
}

void flee_away()
{
    if( !living(this_object()) ) return;
    message_vision("$N痛得怒吼一聲，轉身往旁邊跑去！\n", this_object());
    random_move();
}

void create()
{
    seteuid(getuid());
    set_name("大黑熊", ({ "big bear", "bear" }));
    set_race("beast");
    set_class("commoner");
    set_level(1);
    set("long", @LONG
一頭大黑熊，壯碩的體型讓你不自覺的想要後退幾步…
LONG
    );
    set("unit", "頭");
    set("beast_actions", ({
        ([ "action": "$N人立而起，揮掌往$n的$l拍去", "damage_type": "瘀傷" ]),
        ([ "action": "$N張開大口往$n的$l咬去", "damage_type": "咬傷" ]),
        ([ "action": "$N往$n的$l猛撲過去", "damage_type": "瘀傷" ])
    }));
    setup();
    RACE_D("beast")->set_strength(this_object(), 5);
}
