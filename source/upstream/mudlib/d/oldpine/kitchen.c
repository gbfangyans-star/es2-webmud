// /d/oldpine/kitchen.c — 迷霧森林（P14）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "廚房");
    set("long", @LONG
野店後頭的小廚房，牆壁被煙燻得烏黑，灶上架著一口大鐵鍋，鍋裡燉著不知名的野味，香氣四溢。屋樑上吊著幾串風乾的獸肉和辣椒，牆角堆滿了柴火與裝米的麻袋，麻袋上被咬出了好幾個破洞，地上還散落著米粒和老鼠屎。從這裡可以出去（out）回到店裡。
LONG
    );
    set("exits", ([
        "out" : __DIR__"inn",
    ]));
    set("objects", ([
        __DIR__"npc/rat" : 3,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
