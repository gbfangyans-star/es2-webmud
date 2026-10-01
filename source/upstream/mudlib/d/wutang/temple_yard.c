// /d/wutang/temple_yard.c — 五堂鎮（Z4）。房間敘述照設計表原文。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "後院");
    set("long", @LONG
這是鎮天神廟的後院，通常開放給鎮民來此休息，在此有種著許多的樹和盆景，而在老黃桐樹下也有著四張石椅和一張光滑的石桌供人在此乘涼。
LONG
    );
    set("exits", ([
        "out" : __DIR__"temple",
    ]));
    set("objects", ([
        __DIR__"npc/oldman" : 1,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
