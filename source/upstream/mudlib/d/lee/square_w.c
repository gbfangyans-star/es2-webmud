// /d/lee/square_w.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "廣場");
    set("long", @LONG
這片空地是村民日常往來與歇腳的地方，地面被踩得十分結實。北面連著私塾附近的道路，南面還有另一片廣場。
LONG
    );
    set("exits", ([
        "north" : __DIR__"nroad3",
        "west" : __DIR__"wroad3",
        "east" : __DIR__"square_e",
        "south" : __DIR__"square_s"
    ]));
    setup();
    replace_program(ROOM);
}
