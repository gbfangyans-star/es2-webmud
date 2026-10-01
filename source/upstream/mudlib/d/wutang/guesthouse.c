// /d/wutang/guesthouse.c — 五堂鎮（T14）。房間敘述照設計表原文。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "五堂別館");
    set("long", @LONG
這裏是五堂鎮官府所設的別館，專供往來的大官休息之用，別館裏樸實雅緻的佈置，可看出鎮方樸實的一面。
LONG
    );
    set("exits", ([
        "north" : __DIR__"east_street3",
    ]));
    set("objects", ([
        __DIR__"npc/royalist" : 1,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
