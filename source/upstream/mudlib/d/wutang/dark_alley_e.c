// /d/wutang/dark_alley_e.c — 五堂鎮（T8）。房間敘述照設計表原文。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "暗巷");
    set("long", @LONG
這是一條非常陰冷的巷子，因為在兩旁的房子的中間，而巷子是非常的窄的，而陽光也是被房子所遮敝著，所以使的這非常的涼快，而巷子的盡頭傳來吵雜的聲音，也看得到那一頭人來人往的樣子。
LONG
    );
    set("exits", ([
        "east" : __DIR__"temple_road_s",
        "west" : __DIR__"dark_alley_w",
    ]));
    set("objects", ([
        __DIR__"npc/lee_shan" : 1,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
