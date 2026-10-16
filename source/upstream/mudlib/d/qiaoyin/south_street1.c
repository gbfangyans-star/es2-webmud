// /d/qiaoyin/south_street1.c — 喬陰縣（L12）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "南大街");
    set("long", @LONG
南大街的北段，鄰近城中心的樹王墳。街邊有幾家小吃攤，蒸籠裡冒著白煙，飄來陣陣香味，攤子前的長凳上坐滿了埋頭吃喝的客人。路旁一棵老槐樹下，幾個老人正圍著棋盤，看得目不轉睛。
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
