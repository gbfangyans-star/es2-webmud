// /d/oldpine/bear_cave.c — 老松林（V8）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "山洞");
    set("long", @LONG
一個陰暗潮濕的山洞，洞頂不時滴下冰涼的水珠，空氣中瀰漫著一股濃重的腥臊味。地上散落著被啃得乾乾淨淨的獸骨，其中似乎還混著幾根人骨，角落裡鋪著一堆被壓扁的乾草，看起來是某種大型野獸的窩。洞口透進一點微光，外頭就是那片比人還高的草叢。
LONG
    );
    set("exits", ([
        "out" : __DIR__"grass2",
    ]));
    set("objects", ([
        __DIR__"npc/wild_bear" : 1,
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
