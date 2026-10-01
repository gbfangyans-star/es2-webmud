// /d/wutang/dark_alley_w.c — 五堂鎮（R8）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "暗巷");
    set("long", @LONG
暗巷的另一頭，兩旁的牆壁高得幾乎遮住了天空，地上滿是積水與垃圾，散發出一股霉味。巷子到這裡就到了盡頭，往東可以走回巷口，隱約還聽得到市集那頭傳來的吵雜聲。
LONG
    );
    set("exits", ([
        "east" : __DIR__"dark_alley_e",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
