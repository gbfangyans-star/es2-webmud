// /d/oldpine/beast_trail.c — 迷霧森林（X12）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "獸徑");
    set("long", @LONG
一條野獸踩出來的狹窄小徑，兩旁的灌木被撞得東倒西歪，枝條上勾著幾撮粗硬的黑毛。泥地上的腳印又大又深，越往東走越密集，空氣中還飄著一股野獸的騷味。附近的樹幹上有幾道深深的抓痕，高度竟比人還高。往西南可以回到樹林，往東則是一面山壁。
LONG
    );
    set("exits", ([
        "southwest" : __DIR__"wood1",
        "east" : __DIR__"cave_mouth",
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
