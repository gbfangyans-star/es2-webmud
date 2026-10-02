// /d/oldpine/cave1.c — 迷霧森林（AB12）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "山洞");
    set("long", @LONG
洞內比想像中寬敞，岩壁上長著一層濕滑的青苔，從洞口透進來的光線只能照亮幾步遠。地上鋪著一層乾草和落葉，踩上去軟綿綿的，還混著一股淡淡的奶腥味。洞穴往東和往南延伸，深處不時傳來窸窣的聲響和小獸的哼叫聲。身後的洞口透進一點天光，那是唯一的出路。
LONG
    );
    set("exits", ([
        "east" : __DIR__"cave2",
        "south" : __DIR__"cave3",
        "out" : __DIR__"cave_mouth",
    ]));
    set("objects", ([
        __DIR__"npc/little_bear" : 2,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
