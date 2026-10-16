// /d/qiaoyin/north_street2.c — 喬陰縣（L6）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "北大街");
    set("long", @LONG
北大街的中段，街道兩旁店鋪林立，酒旗招展，挑擔的小販沿街叫賣，是喬陰縣城裡最熱鬧的地方之一。路邊的酒樓傳出划拳行令的喧鬧聲，門口停著幾輛馬車。往北走是北門的方向，往南則通往城中心的樹王墳。
LONG
    );
    set("exits", ([
        "north" : __DIR__"north_street1",
        "south" : __DIR__"north_street3",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
