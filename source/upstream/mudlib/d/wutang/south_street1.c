// /d/wutang/south_street1.c — 五堂鎮（N14）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
交叉路口往南的街道，路面漸漸寬了起來，常有挑著貨擔的商人與趕車的旅客經過。路旁有一家打鐵鋪傳來叮叮噹噹的聲音，也有幾間賣雜貨的小店。往北可以回到鎮中心，往南則通往鎮外的三岔路口。
LONG
    );
    set("exits", ([
        "north" : __DIR__"crossroad",
        "south" : __DIR__"south_street2",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
