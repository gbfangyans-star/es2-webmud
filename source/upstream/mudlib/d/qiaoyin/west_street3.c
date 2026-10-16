// /d/qiaoyin/west_street3.c — 喬陰縣（H10）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "西大街");
    set("long", @LONG
西大街的中段，南邊是一間氣派的錢莊，朱漆大門上釘著一排銅釘，門口站著幾名護院武師，目光不住地打量著來往的行人。錢莊對面的牆根下，幾個閒漢倚著牆曬太陽，不時朝錢莊門口張望。
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
