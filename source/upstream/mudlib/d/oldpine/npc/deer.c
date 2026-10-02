// /d/oldpine/npc/deer.c — 迷霧森林／老松林 野獸：野鹿（強度 3，野豬為 4）。

#include <npc.h>

void create()
{
    seteuid(getuid());
    set_name("野鹿", ({ "deer" }));
    set_race("beast");
    set_class("commoner");
    set_level(1);
    set("long", @LONG
一頭警覺性很強的精壯野鹿，即使低頭吃草仍保持警戒。
LONG
    );
    set("unit", "頭");
    set("beast_actions", ({
        ([ "action": "$N低頭用鹿角往$n的$l頂了過去", "damage_type": "刺傷" ]),
        ([ "action": "$N揚起前蹄往$n的$l踢去", "damage_type": "瘀傷" ])
    }));
    setup();
    RACE_D("beast")->set_strength(this_object(), 3);
}
