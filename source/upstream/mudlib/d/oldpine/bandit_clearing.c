// /d/oldpine/bandit_clearing.c — 迷霧森林（R18）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "空地");
    set("long", @LONG
迷霧森林西南角的一塊空地，地上的草被踩得東倒西歪，幾根削尖的木樁斜插在地上，木樁上還掛著破碎的衣物。空地邊緣堆著幾個空酒罈，一面破舊的布旗插在樹上，旗上歪歪斜斜地寫著一個「寨」字。看來老松林的土匪也把手伸進了這片森林。往東北可以回到矮樹叢。
LONG
    );
    set("exits", ([
        "northeast" : __DIR__"shrubs",
    ]));
    set("objects", ([
        __DIR__"npc/bandit" : 3,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
