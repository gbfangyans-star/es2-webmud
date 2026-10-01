// /d/wutang/yan_mansion.c — 五堂鎮（V6）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "顏家大宅");
    set("long", @LONG
大宅的門戶敞開著，雕樑畫棟、朱漆門柱都看得出顏家當年的輝煌，如今卻蒙上了一層灰，庭院裡的花草也已經枯萎。院中靜得出奇，只有幾隻烏鴉停在屋簷上。往裡(in)走是正廳，往南則是大宅的前門。
LONG
    );
    set("exits", ([
        "in" : __DIR__"yan_hall",
        "south" : __DIR__"yan_gate",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
