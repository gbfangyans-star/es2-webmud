// /d/wutang/bamboo_hall.c — 五堂鎮（H14）。房間敘述照設計表原文。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "主廳");
    set("long", @LONG
這是一間綠竹所造的小屋, 簡單的擺設中流露出異於凡俗的清幽雅緻, 東西兩側兩扇小窗引進樹林的淡淡清香繚繞室內, 幾張竹桌竹椅整齊的排在屋內, 竹桌上還泡著一壺清茶, 和一籃水果。
LONG
    );
    set("exits", ([
        "south" : __DIR__"bamboo_grove",
    ]));
    set("objects", ([
        __DIR__"npc/huyen_guan" : 1,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
