// /d/qiaoyin/west_street1.c — 喬陰縣（D10）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "西大街");
    set("long", @LONG
西大街的西端，往北的街道可以通往西門，往東則是熱鬧的西大街。街角有幾個孩童在玩耍，不時傳來嬉笑聲，一隻黃狗懶洋洋地趴在牆邊曬太陽。路旁的屋簷下掛著一串串風乾的辣椒和玉米，看來這裡多是尋常人家。
LONG
    );
    set("exits", ([
        "north" : __DIR__"west_lane2",
        "east" : __DIR__"west_street2",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
