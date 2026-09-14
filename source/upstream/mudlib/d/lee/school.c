// /d/lee/school.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "私塾");
    set("long", @LONG
私塾裡整齊排著舊木桌椅，牆邊堆著幾冊翻得起毛的書本。白日常有孩童朗讀文章，窗外便是通往廣場的石子路。
LONG
    );
    set("objects", ([
        "/d/lee/npc/teacher" : 1
    ]));
    set("exits", ([
        "east" : __DIR__"nroad3"
    ]));
    setup();
    replace_program(ROOM);
}
