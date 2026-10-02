// /d/oldpine/clearing_w.c — 老松林（F8）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "林間空地");
    set("long", @LONG
林子中間一塊不大的空地，中央用石頭圍了個火堆，裡面的灰燼還帶著餘溫，旁邊散落著酒罈的碎片和吃剩的獸骨。幾棵松樹的枝椏上掛著破爛的衣物，樹下堆著好幾個被扯開的包袱，裡頭的東西早被搜刮一空，看來是土匪臨時落腳的地方。往西北可以回到林子邊緣，往東則有一條小路穿過樹林。
LONG
    );
    set("exits", ([
        "northwest" : __DIR__"entrance",
        "east" : __DIR__"path1",
    ]));
    set("objects", ([
        __DIR__"npc/bandit" : 2,
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
