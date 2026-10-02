// /d/wutang/east_street3.c — 五堂鎮（T12）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
廟口大街往東延伸的一段，北邊是一間布莊，門口掛著五顏六色的布疋，南邊則是官府設的五堂別館，門口立著兩隻石獅子，顯得十分莊重。往西是熱鬧的大街，往東則通往城隍廟的方向。
LONG
    );
    set("exits", ([
        "west" : __DIR__"east_street2",
        "east" : __DIR__"east_street4",
        "north" : __DIR__"cloth_shop",
        "south" : __DIR__"guesthouse",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
