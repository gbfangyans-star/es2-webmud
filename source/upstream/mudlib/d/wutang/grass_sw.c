// /d/wutang/grass_sw.c — 五堂鎮（J16）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "草原");
    set("long", @LONG
草原的西南角，地勢稍低，草叢間有幾處小水窪，綿羊們聚在水邊喝水。往北、往東都是綠油油的草地。水窪邊的泥地上印滿了羊蹄印，空氣中帶著青草與泥土混合的氣味。
LONG
    );
    set("exits", ([
        "north" : __DIR__"grass_nw",
        "east" : __DIR__"grass_se",
    ]));
    set("objects", ([
        __DIR__"npc/sheep" : 2,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
