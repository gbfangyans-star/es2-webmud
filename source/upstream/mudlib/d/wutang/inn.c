// /d/wutang/inn.c — 五堂鎮（R10）。房間敘述照設計表原文。

#include <room.h>

inherit INN;

void create()
{
    set("short", "醇雨樓客棧");
    set("long", @LONG
這是一家中等規模的客棧﹐樓面不甚寬闊﹐但是卻有三層樓﹐看牆面樑柱的樣子﹐大概有七、八十年的歷史了﹐大門兩側的柱子還題得有字﹐只不過龍飛鳳舞地不知道寫些什麼﹐東首有座樓梯往二樓雅座。
LONG
    );
    set("exits", ([
        "south" : __DIR__"east_street2",
        "up" : __DIR__"inn2",
    ]));
    set("objects", ([
        __DIR__"npc/waiter" : 1,
        __DIR__"npc/yung_tai" : 1,
    ]));
    set("map/area", "五堂鎮");
    setup();
}
