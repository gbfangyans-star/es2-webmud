// /d/qiaoyin/east_street2.c — 喬陰縣（P10）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "東大街");
    set("long", @LONG
東大街的中段，兩旁多是賣布匹、雜貨的店鋪，往來的行人比西大街少了一些，顯得清閒許多。街道往東西兩頭延伸。
LONG
    );
    set("exits", ([
        "west" : __DIR__"east_street1",
        "east" : __DIR__"east_street3",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
