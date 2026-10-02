// /d/wutang/east_street2.c — 五堂鎮（R12）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
廟口大街的中段，北邊就是三層樓高的醇雨樓客棧，飯菜的香味不時從客棧裡飄出來，引得路人頻頻回頭。街上的行人多半是往來的旅客與商販，十分熱鬧。
LONG
    );
    set("exits", ([
        "west" : __DIR__"east_street1",
        "east" : __DIR__"east_street3",
        "north" : __DIR__"inn",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
