// /d/lee/wroad4.c
// 李家村復原版。NEW（新增銜接房間，非原始 ES2 資料）
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
這段石子路夾在廣場與醫館一帶之間，路面同樣鋪著碎石，偶有村民往來。兩側種著幾株低矮的灌木，替過路人擋去了些許日頭，走起來倒也不算難受。
LONG
    );
    set("exits", ([
        "east" : __DIR__"square_w",
        "west" : __DIR__"wroad3"
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
