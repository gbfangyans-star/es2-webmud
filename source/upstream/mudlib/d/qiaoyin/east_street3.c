// /d/qiaoyin/east_street3.c — 喬陰縣（R10）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "東大街");
    set("long", @LONG
東大街的東段，離東門已經不遠，街上的店鋪漸漸稀疏，多了幾分冷清。東北方是一座清幽的宅院，門前打掃得一塵不染，南邊則是同仁藥鋪，門口飄著淡淡的藥香，往來的多是抓藥看病的街坊。
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
