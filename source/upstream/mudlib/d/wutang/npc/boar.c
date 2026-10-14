// /d/wutang/npc/boar.c — 五堂鎮 NPC：野豬（依五堂鎮設計表）。

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
    set_name("野豬", ({ "boar" }));
    set_race("beast");
    set_class("commoner");
    set_level(1);
    set("long", @LONG
一隻兇猛的野豬，正東張西望找食物。
LONG
    );
    // 野獸強度（1～10），數值見 daemon/race/beast.c。
    set_beast(4);
    setup();
}
