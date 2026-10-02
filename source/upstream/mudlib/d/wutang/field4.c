// /d/wutang/field4.c — 五堂鎮（D10）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "菜田");
    set("long", @LONG
菜田的西南角，地上的蘿蔔幾乎都被野豬拱了出來，只剩下一個個坑洞。看來菜田主人對這群野豬實在是束手無策。田邊的水溝已經被泥土填平了一半，往北、往東還有更多被糟蹋的菜圃。
LONG
    );
    set("exits", ([
        "north" : __DIR__"field2",
        "east" : __DIR__"field5",
    ]));
    set("objects", ([
        __DIR__"npc/boar" : 3,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
