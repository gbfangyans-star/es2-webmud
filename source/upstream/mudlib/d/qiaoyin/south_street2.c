// /d/qiaoyin/south_street2.c — 喬陰縣（L14）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "南大街");
    set("long", @LONG
南大街的南段，西邊是金水客棧，客棧門口常有往來的江湖人物進出，腰間佩刀掛劍，神色各異。街邊幾名穿著儒衫的年輕人正高聲談論著詩文，看來是哪家書院的弟子，路人也不禁駐足聆聽。
LONG
    );
    set("exits", ([
        "north" : __DIR__"south_street1",
        "west" : __DIR__"inn",
        "south" : __DIR__"sgate",
    ]));
    set("objects", ([
        __DIR__"npc/apprentice" : 3,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
