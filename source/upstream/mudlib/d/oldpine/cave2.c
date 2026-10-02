// /d/oldpine/cave2.c — 迷霧森林（AD12）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "山洞");
    set("long", @LONG
山洞的東側，岩壁上布滿了一道道爪痕，像是有野獸經常在此磨爪。角落裡堆著一些被掏空的蜂巢，蜂蠟和蜂蜜沾了一地，引來一群小蟲嗡嗡飛舞。洞頂有一道細細的裂縫，透進一縷微光，正好照在地上一灘渾濁的積水上。往西可以回到洞口附近，往南通往更深的地方。
LONG
    );
    set("exits", ([
        "west" : __DIR__"cave1",
        "south" : __DIR__"cave_deep",
    ]));
    set("objects", ([
        __DIR__"npc/little_bear" : 3,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
