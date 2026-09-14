// /d/lee/creek.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "小溪");
    set("long", @LONG
清淺溪水貼著李家村東側流過，岸邊散著大小不一的石塊。西面靠近瓜田，北面則可沿溪邊小路返回村東門。
LONG
    );
    set("exits", ([
        "north" : __DIR__"riverside_s",
        "west" : __DIR__"watermelon_s3"
    ]));
    setup();
    replace_program(ROOM);
}
