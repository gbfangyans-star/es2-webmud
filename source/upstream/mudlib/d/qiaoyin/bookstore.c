// /d/qiaoyin/bookstore.c — 喬陰縣（B8）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "名山書肆");
    set("long", @LONG
你現在來到一間燈光昏暗的書肆，除了你進來的那面牆上開了道門之外，三面牆壁都是書架，滿滿地排列著各式各樣的書。靠裡面的一個矮櫃上面放著文房四寶，一股淡淡的松煙墨香氣縈繞著整間屋子。
LONG
    );
    set("exits", ([
        "east" : __DIR__"west_lane2",
    ]));
    set("objects", ([
        __DIR__"npc/oldman" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
