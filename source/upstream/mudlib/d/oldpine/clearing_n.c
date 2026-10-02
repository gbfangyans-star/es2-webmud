// /d/oldpine/clearing_n.c — 老松林（R4）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "空地");
    set("long", @LONG
老松林北緣的一塊空地，四周的老松被人砍倒了幾棵，留下一圈高低不齊的樹樁，正好圍出一片平坦的泥地。地上滿是凌亂的腳印，幾棵松樹的樹幹上留著深淺不一的刀痕，有些痕跡又深又齊，像是有人經常在這裡練刀，而且刀法十分了得。林風穿過松針沙沙作響，四下顯得格外清靜。往南可以回到樹林裡。
LONG
    );
    set("exits", ([
        "south" : __DIR__"forest_n3",
    ]));
    set("objects", ([
        __DIR__"npc/kao_shen" : 1,
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
