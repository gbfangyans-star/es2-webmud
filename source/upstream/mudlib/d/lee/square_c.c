// /d/lee/square_c.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "廣場中央");
    set("long", @LONG
這裡是李家村最容易聚集人群的中央廣場，四周道路交錯。孩童常在空地追逐，村民也會停下交換消息或談論村中近事。
LONG
    );
    set("objects", ([
        "/d/lee/npc/child" : 3
    ]));
    set("exits", ([
        "west" : __DIR__"square_s",
        "north" : __DIR__"square_e",
        "south" : __DIR__"street1",
        "east" : __DIR__"watermelon_n1"
    ]));
    setup();
    replace_program(ROOM);
}
