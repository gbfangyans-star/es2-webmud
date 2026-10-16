// /d/qiaoyin/smithy.c — 喬陰縣（N8）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "鐵匠鋪");
    set("long", @LONG
一間熱氣騰騰的鐵匠鋪，屋子中央的火爐燒得通紅，一旁擺著鐵砧與水箱，燒紅的鐵塊浸入水中時便冒起一陣白煙。牆上掛滿了刀、劍、斧頭等各式兵器，都是鐵匠閒暇時打造的。往西出門便是北大街。
LONG
    );
    set("exits", ([
        "west" : __DIR__"north_street3",
    ]));
    set("objects", ([
        __DIR__"npc/smith" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
