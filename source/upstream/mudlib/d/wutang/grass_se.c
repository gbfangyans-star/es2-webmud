// /d/wutang/grass_se.c — 五堂鎮（L16）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "草原");
    set("long", @LONG
草原的東南角，這裡的草被羊群啃得短短的，露出一塊塊泥土。往南可以走上通往三岔路口的木道，往北、往西則是更大的草原。草地上散落著幾坨羊糞，牧羊人搭的一個小棚子歪歪斜斜地立在一旁。
LONG
    );
    set("exits", ([
        "west" : __DIR__"grass_sw",
        "north" : __DIR__"grass_ne",
        "south" : __DIR__"boardwalk_e",
    ]));
    set("objects", ([
        __DIR__"npc/sheep" : 2,
        __DIR__"npc/shepherd" : 1,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
