// /d/wutang/yan_gate.c — 五堂鎮（V8）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "前門");
    set("long", @LONG
顏家大宅的前門，四周一片死寂，杳無人煙。門板與石階上留著斑斑血跡，牆上還有好幾道深深的刀痕，看得出這裡不久前經過一場惡鬥。往北可以進入大宅，往東則能回到廟口小路。
LONG
    );
    set("exits", ([
        "north" : __DIR__"yan_mansion",
        "east" : __DIR__"temple_road_n",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
