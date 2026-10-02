// /d/oldpine/crossing.c — 老松林（L10）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "空地");
    set("long", @LONG
一塊地面被踩得光禿禿的空地，四周的松樹上綁著幾根斷掉的繩子，地上散落著被翻得亂七八糟的行李和撕破的衣物，看來不久前才有旅人在這裡遭到洗劫。這塊空地是老松林裡幾條小路的交會處，往北、往西、往西南都有路通往林中，往東走則是一片霧氣瀰漫的森林。
LONG
    );
    set("exits", ([
        "north" : __DIR__"forest_w",
        "west" : __DIR__"path2",
        "east" : __DIR__"mist_entrance",
        "southwest" : __DIR__"hideout",
    ]));
    set("objects", ([
        __DIR__"npc/bandit_minion" : 1,
        __DIR__"npc/injured_traveller" : 1,
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
