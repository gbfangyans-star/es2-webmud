// /d/qiaoyin/ngate.c — 喬陰縣（L2）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "喬陰縣城北門");
    set("long", @LONG
喬陰縣城的北門，城門洞裡陰涼幽暗，幾名官兵手按刀柄，仔細盤查著進出的行人。城門外是一條通往老松林的官道，近來老松林裡的土匪越聚越多，往北去的商旅都得結伴而行，城牆上也新貼了幾張緝拿盜匪的告示。往南進城便是北大街。
LONG
    );
    set("exits", ([
        "north" : "/d/oldpine/highway",
        "south" : __DIR__"north_street1",
    ]));
    set("objects", ([
        "/obj/area/garrison" : 4,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
