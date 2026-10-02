// /d/wutang/west_street2.c — 五堂鎮（J12）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
五堂鎮西側的街道，路面由青石板鋪成，兩旁是幾間簡樸的民房。往北可以聽見鄉校傳來的讀書聲，往西走則漸漸離開市街，通往一條碎石路，往東是鎮上的街道。
LONG
    );
    set("exits", ([
        "west" : __DIR__"gravel_road_n",
        "east" : __DIR__"west_street1",
        "north" : __DIR__"school",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
