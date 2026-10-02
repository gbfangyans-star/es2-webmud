// /d/wutang/field1.c — 五堂鎮（D6）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "菜田");
    set("long", @LONG
一大片菜田，田裡種著白菜、蘿蔔與青蔥，只是不少菜苗被翻得東倒西歪，地上滿是野豬的蹄印與拱出來的土坑。田埂上插著幾根削尖的竹竿，似乎是主人用來防範野豬的。往西是菜田主人的草屋。
LONG
    );
    set("exits", ([
        "west" : __DIR__"hut",
        "south" : __DIR__"field2",
    ]));
    set("objects", ([
        __DIR__"npc/big_boar" : 1,
        __DIR__"npc/boar" : 2,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
