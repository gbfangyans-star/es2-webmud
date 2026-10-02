// /d/oldpine/highway.c — 老松林（J16）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "官道");
    set("long", @LONG
老松林南邊的官道，路面寬闊平坦，兩旁種著整齊的柳樹，與林中崎嶇的小路相比，走起來輕鬆許多。路邊立著一塊里程碑，刻著往喬陰縣的方向與里數。由於近來老松林土匪橫行，官道上往來的旅人寥寥無幾，只有幾隻烏鴉停在柳枝上啞啞叫著。往北可以進入老松林，往南的官道通往喬陰縣。
LONG
    );
    set("exits", ([
        "north" : __DIR__"gravel_road",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
