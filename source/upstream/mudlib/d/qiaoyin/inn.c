// /d/qiaoyin/inn.c — 喬陰縣（J14）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit INN;

void create()
{
    set("short", "金水客棧");
    set("long", @LONG
一家寬敞的客棧，大廳裡擺著十幾張桌子，跑堂的店小二穿梭其間，招呼著南來北往的客人。牆角有一座木梯通往二樓，大門往東開，出去便是南大街。
LONG
    );
    set("exits", ([
        "east" : __DIR__"south_street2",
        "up" : __DIR__"inn2",
    ]));
    set("objects", ([
        __DIR__"npc/waiter" : 1,
    ]));
    set("no_fight", 1);
    set("valid_startroom", 1);
    set("map/area", "喬陰縣");
    setup();
}
