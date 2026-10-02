// /d/oldpine/ledge.c — 迷霧森林（AD16）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "平台");
    set("long", @LONG
一塊突出的大石頭形成的平台，位置高出洞底許多，下面的動靜看得一清二楚。石面上有幾處被人用刀刻下的記號，旁邊還丟著一個乾癟的水袋，看來曾有人在此躲避野獸。在這裡總算可以暫時喘口氣，但下面的低吼聲不時傳來，提醒你危險並未遠離。從這裡可以爬下去，回到山洞深處。
LONG
    );
    set("exits", ([
        "down" : __DIR__"cave_deep",
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
