// /d/wutang/pavilion.c — 五堂鎮（F12）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "涼亭");
    set("long", @LONG
一座建在小丘上的木造涼亭，四周種著幾株垂柳，微風吹過時柳枝輕輕搖曳。站在亭中向西望去，可以眺望寬闊的羿水在遠方緩緩流過，河面上點點帆影，景色十分宜人。往東是一條碎石路。
LONG
    );
    set("exits", ([
        "east" : __DIR__"gravel_road_n",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
