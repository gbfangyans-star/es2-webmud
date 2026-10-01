// /d/wutang/inn3.c — 五堂鎮（R10_3）。房間敘述照設計表原文。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "醇雨樓客棧三樓");
    set("long", @LONG
這裡是醇雨樓客棧的三樓﹐佈置和二樓雅座大致差不多﹐不過樓中放了幾盆蘭花﹐更添幾分雅致﹐往下的樓梯在西邊。
LONG
    );
    set("exits", ([
        "down" : __DIR__"inn2",
    ]));
    set("objects", ([
        __DIR__"npc/jeweller" : 1,
        __DIR__"npc/young_scholar" : 1,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
