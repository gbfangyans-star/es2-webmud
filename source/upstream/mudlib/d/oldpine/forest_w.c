// /d/oldpine/forest_w.c — 老松林（L8）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "樹林");
    set("long", @LONG
高大的老松將天空遮得只剩下零星幾點光亮，林中瀰漫著一股松脂的清香。一棵被雷劈倒的大松橫躺在地上，樹身早已腐朽中空，幾朵白色的菇菌從裂縫裡冒出頭來，倒下的樹幹旁長出了一圈嫩綠的小松苗。往東北可以穿過樹林，往南不遠處就是一塊較為開闊的空地。
LONG
    );
    set("exits", ([
        "northeast" : __DIR__"forest_n1",
        "south" : __DIR__"crossing",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
