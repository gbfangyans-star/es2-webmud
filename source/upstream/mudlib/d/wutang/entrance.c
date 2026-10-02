// /d/wutang/entrance.c — 五堂鎮（N8）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "五堂鎮口");
    set("long", @LONG
這裡是五堂鎮的鎮口，幾輛人力車整齊地停在路邊，車伕們一邊擦汗一邊招攬客人，等著把旅客送往附近的城鎮。往北是振武軍營的方向，往南走就進入五堂鎮了。
LONG
    );
    set("exits", ([
        "north" : "/custom/zhenwu/room/gate",
        "south" : __DIR__"north_street",
    ]));
    set("objects", ([
        __DIR__"npc/young_man" : 1,
        __DIR__"npc/old_fire" : 1,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
