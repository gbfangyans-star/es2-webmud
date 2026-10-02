// /d/oldpine/hideout.c — 老松林（J12）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "林間空地");
    set("long", @LONG
松林深處一塊隱密的空地，四周用砍下的樹枝圍起了簡陋的柵欄，柵欄上掛著幾面破舊的布旗。空地中央搭著一個獸皮棚子，裡面堆著搶來的米糧和兵器，棚前插著一把生了鏽的大刀，刀柄上纏著褪色的紅布。這裡顯然是土匪在老松林裡的據點。往東北和往南各有一條小路。
LONG
    );
    set("exits", ([
        "northeast" : __DIR__"crossing",
        "south" : __DIR__"gravel_road",
    ]));
    set("objects", ([
        __DIR__"npc/xue_biao" : 1,
        __DIR__"npc/bandit" : 2,
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
