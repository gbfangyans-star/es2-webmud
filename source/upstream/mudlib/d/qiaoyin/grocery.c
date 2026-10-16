// /d/qiaoyin/grocery.c — 喬陰縣（J4）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "雜貨舖");
    set("long", @LONG
一間堆得滿滿的雜貨舖，櫃臺上擺著鹽、糖、符紙之類的日常雜貨，牆角疊著一捆捆的松材，屋樑上還吊著幾串乾辣椒。老闆老何在喬陰縣住了大半輩子，城裡人要買什麼零碎東西，多半都往這兒來。往東出門便是北大街。
LONG
    );
    set("exits", ([
        "east" : __DIR__"north_street1",
    ]));
    set("objects", ([
        __DIR__"npc/old_ho" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
