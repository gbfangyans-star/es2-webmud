// /d/qiaoyin/east_street3.c — 喬陰縣（R10）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "東大街");
    set("long", @LONG
東大街的東段，往東不遠就是東門，北邊有一條小巷子，東北方是一座清幽的宅院，南邊則是同仁藥鋪。往西是東大街。
LONG
    );
    set("exits", ([
        "west" : __DIR__"east_street2",
        "east" : __DIR__"egate",
        "north" : __DIR__"alley",
        "northeast" : __DIR__"fonxan_hall",
        "south" : __DIR__"pharmacy",
    ]));
    set("objects", ([
        __DIR__"npc/girl" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
