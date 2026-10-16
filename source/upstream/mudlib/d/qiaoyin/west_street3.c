// /d/qiaoyin/west_street3.c — 喬陰縣（H10）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "西大街");
    set("long", @LONG
西大街的中段，南邊是一間氣派的錢莊，門口站著幾名護院武師，北邊則有一條街道通往城北。街道往東西兩頭延伸。
LONG
    );
    set("exits", ([
        "west" : __DIR__"west_street2",
        "east" : __DIR__"west_street4",
        "north" : __DIR__"mid_lane2",
        "south" : __DIR__"bank",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
