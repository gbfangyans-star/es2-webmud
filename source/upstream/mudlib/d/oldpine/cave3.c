// /d/oldpine/cave3.c — 迷霧森林（AB14）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "山洞");
    set("long", @LONG
洞穴在這裡低了下來，得彎著腰才能前進。地上散落著被咬碎的骨頭和魚鱗，空氣又悶又臭，讓人幾乎喘不過氣。岩壁的凹陷處被扒成了一個淺淺的窩，裡面鋪著柔軟的獸毛，摸上去還帶著餘溫。往北可以回到洞口附近，往東則傳來更粗重的喘息聲。
LONG
    );
    set("exits", ([
        "north" : __DIR__"cave1",
        "east" : __DIR__"cave_deep",
    ]));
    set("objects", ([
        __DIR__"npc/little_bear" : 3,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
