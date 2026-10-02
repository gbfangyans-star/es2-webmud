// /d/wutang/path_e.c — 五堂鎮（Z6）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
一條夾在民房之間的泥土小路，兩旁的竹籬笆上晾著衣物，偶爾傳來幾聲雞鳴犬吠。往西可以回到熱鬧的廟口小路，往南則是民房的後院，隱約聽得見潺潺的溪水聲。
LONG
    );
    set("exits", ([
        "west" : __DIR__"temple_road_n",
        "south" : __DIR__"backyard",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
