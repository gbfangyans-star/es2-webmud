// /d/wutang/east_street4.c — 五堂鎮（V12）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
廟口大街的東端，再往東走就是香火鼎盛的城隍廟，空氣中飄著淡淡的香煙味。往東北可以通往雲棧市集廣場，市集那頭的吵雜聲遠遠就能聽見。
LONG
    );
    set("exits", ([
        "west" : __DIR__"east_street3",
        "east" : __DIR__"city_god_temple",
        "northeast" : __DIR__"market_square",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
