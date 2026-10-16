// /d/qiaoyin/south_street1.c — 喬陰縣（L12）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "南大街");
    set("long", @LONG
南大街的北段，往北就是樹王墳，往南則通往南門。街邊有幾家小吃攤，蒸籠裡冒著白煙，飄來陣陣香味。
LONG
    );
    set("exits", ([
        "north" : __DIR__"tree_tomb",
        "south" : __DIR__"south_street2",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
