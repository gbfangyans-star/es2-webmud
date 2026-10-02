// /d/wutang/field5.c — 五堂鎮（F10）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "菜田");
    set("long", @LONG
菜田的東側，往東就是菜田前的空地。田裡的作物被踩得亂七八糟，泥地上的蹄印一路延伸到空地那頭。田邊幾棵果樹的樹皮被啃得斑斑駁駁，往西、往北都是一片狼藉的菜田。
LONG
    );
    set("exits", ([
        "west" : __DIR__"field4",
        "north" : __DIR__"field3",
        "east" : __DIR__"clearing",
    ]));
    set("objects", ([
        __DIR__"npc/boar" : 2,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
