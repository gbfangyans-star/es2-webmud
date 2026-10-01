// /d/wutang/npc/big_boar.c — 五堂鎮 NPC：大野豬（依五堂鎮設計表）。

#include <npc.h>

// 野豬會主動攻擊玩家；被打中受傷後有 20% 機會逃往相鄰的格子。
void init()
{
    object ob = this_player();

    ::init();
    if( objectp(ob) && userp(ob) && living(this_object()) && !is_fighting(ob)
    &&  !environment()->query("no_fight") && visible(ob) )
        kill_ob(ob);
}

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
    message_vision("$N痛得嗷嗷大叫，掉頭就跑！\n", this_object());
    random_move();
}

void create()
{
    seteuid(getuid());
    set_name("大野豬", ({ "big boar", "boar" }));
    set_race("beast");
    set_class("commoner");
    set_level(1);
    set("long", @LONG
一隻兇猛的大野豬，眼盯著你一副蓄勢待發的樣子。
LONG
    );
    setup();
    set_stat_maximum("gin", 30);
    set_stat_effective("gin", 30);
    set_stat_current("gin", 30);
    set_stat_maximum("kee", 80);
    set_stat_effective("kee", 80);
    set_stat_current("kee", 80);
}
