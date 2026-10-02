// /d/wutang/backyard.c — 五堂鎮（Z8）。房間敘述照設計表原文。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "後院");
    set("long", @LONG
這裡是民房的後院，在後院裡有養著各式各樣的家畜，而在不遠的前方也有著一條很清澈的小溪，通常這也是這地方人家洗衣服和用水的小溪，而在小溪中也有幾隻小魚，溪中也有鴨子在上面玩水。
LONG
    );
    set("exits", ([
        "north" : __DIR__"path_e",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
