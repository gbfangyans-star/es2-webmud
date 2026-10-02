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
    // 野獸強度（1～10，野豬為 4），數值見 daemon/race/beast.c。
    RACE_D("beast")->set_strength(this_object(), 5);
}
