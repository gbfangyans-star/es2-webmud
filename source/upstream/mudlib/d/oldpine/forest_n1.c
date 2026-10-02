// /d/oldpine/forest_n1.c — 老松林（N6）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "樹林");
    set("long", @LONG
松林在這裡長得特別茂密，樹與樹之間的空隙只容一人側身通過，地上的松針積了厚厚一層，踩上去軟綿綿的，沒有半點聲響。灌木叢後隱約有被人踩平的痕跡，旁邊還丟著幾根啃過的雞骨頭和一個空酒葫蘆，看來常有人躲在這裡守株待兔。往東樹林延伸開去，往西南則有一條被人踩出來的小徑。
LONG
    );
    set("exits", ([
        "east" : __DIR__"forest_n2",
        "southwest" : __DIR__"forest_w",
    ]));
    set("objects", ([
        __DIR__"npc/bandit" : 2,
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
