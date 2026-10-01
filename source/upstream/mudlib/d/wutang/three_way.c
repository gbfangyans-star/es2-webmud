// /d/wutang/three_way.c — 五堂鎮（N18）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "三岔路口");
    set("long", @LONG
一處三岔路口，路旁立著一塊斑駁的石碑，上頭刻著往各地的方向。往西是一片草原，再往西則是鯉君渡，往東南的官道可以前往喬陰縣，往北則回到五堂鎮。
LONG
    );
    set("exits", ([
        "north" : __DIR__"south_street2",
        "west" : __DIR__"boardwalk_e",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
