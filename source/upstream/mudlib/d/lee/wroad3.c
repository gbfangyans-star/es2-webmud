// /d/lee/wroad3.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
村西的石子路在這裡較寬，北側靠近福祠，南側仍是農家。向東再走便能抵達村中廣場。
LONG
    );
    set("exits", ([
        "west" : __DIR__"wroad2",
        "east" : __DIR__"square_w",
        "north" : __DIR__"shrine",
        "south" : __DIR__"farm_w2"
    ]));
    setup();
    replace_program(ROOM);
}
