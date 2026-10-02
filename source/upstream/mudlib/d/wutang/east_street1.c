// /d/wutang/east_street1.c — 五堂鎮（P12）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
交叉路口東邊的廟口大街，街上人潮不斷，兩旁的店鋪招牌林立。往南是一間門面氣派的錢莊，門口站著幾個身材魁梧的護院，往東沿著大街可以走到醇雨樓客棧。
LONG
    );
    set("exits", ([
        "west" : __DIR__"crossroad",
        "east" : __DIR__"east_street2",
        "south" : __DIR__"bank",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
