// /d/wutang/market_square.c — 五堂鎮（X10）。房間敘述照設計表原文。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "雲棧市集廣場");
    set("long", @LONG
這是雲棧市集廣場，在這不算廣闊的空地裡，卻是此市集最繁榮之處，不時傳來震耳欲聾的吵雜聲，真的不難想像這到底有多熱鬧，所到之處那一個地方不是人擠人，尤其是西方的雲棧客棧和北方的鎮天神廟，都是本地的名勝古蹟，而在廣場的中央有著官府所設製的公告欄是當地官府向人民宣布重要事情之用。
LONG
    );
    set("exits", ([
        "north" : __DIR__"temple_road_s",
        "southwest" : __DIR__"east_street4",
    ]));
    set("objects", ([
        __DIR__"npc/yaesae" : 1,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
