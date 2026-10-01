// /d/wutang/inn2.c — 五堂鎮（R10_2）。房間敘述照設計表原文。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "醇雨樓客棧二樓");
    set("long", @LONG
這裡是醇雨樓客棧的二樓，樓梯旁的蘭花增添了幾分清香，七八張木桌整齊排列，川流不息。倚著窗欄可以看到五堂鎮來往的路人，是休憩用膳喘口氣的好去處。
LONG
    );
    set("exits", ([
        "down" : __DIR__"inn",
        "up" : __DIR__"inn3",
    ]));
    set("objects", ([
        __DIR__"npc/white_taoist" : 3,
        __DIR__"npc/red_taoist" : 3,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
