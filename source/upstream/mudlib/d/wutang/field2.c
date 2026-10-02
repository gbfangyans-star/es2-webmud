// /d/wutang/field2.c — 五堂鎮（D8）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "菜田");
    set("long", @LONG
菜田的中央，一畦畦的菜圃整齊排列，卻被野豬啃得七零八落，田邊的竹籬笆也被撞出了好幾個破洞。四周不時傳來野豬哼哼的叫聲，田裡的泥土被翻得亂七八糟，一不小心就會踩進泥坑裡，往北、往東、往南都還是菜田。
LONG
    );
    set("exits", ([
        "north" : __DIR__"field1",
        "east" : __DIR__"field3",
        "south" : __DIR__"field4",
    ]));
    set("objects", ([
        __DIR__"npc/boar" : 3,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
