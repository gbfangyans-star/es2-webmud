// /d/qiaoyin/west_lane2.c — 喬陰縣（D8）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
西大街北邊的一條街道，西邊有一間書肆，門口掛著一塊寫著「名山書肆」的舊招牌，偶爾可以聞到從裡面飄出來的墨香。往北通往西門，往南便是西大街。
LONG
    );
    set("exits", ([
        "north" : __DIR__"west_lane1",
        "west" : __DIR__"bookstore",
        "south" : __DIR__"west_street1",
    ]));
    set("objects", ([
        __DIR__"npc/crone" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
