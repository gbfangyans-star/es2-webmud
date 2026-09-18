// /d/lee/gate_s.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "村口大門");
    set("long", @LONG
李家村南面的村口大門守著主要進村道路。從這裡往北就是村內街道，往南則通向村口與外面的道路。這是村里人來人往最頻繁的一道門，門洞兩側的石牆被經年的手掌磨得光滑，牆角還堆著幾捆備用的柴薪。兩名守衛神情警覺，不時交換幾句低語，遇上面生的旅人便會多打量幾眼，確認沒有可疑之處才放行。
LONG
    );
    set("exits", ([
        "north" : __DIR__"street2",
        "south" : __DIR__"entrance_s"
    ]));
    set("objects", ([
        __DIR__"npc/guard" : 2
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
