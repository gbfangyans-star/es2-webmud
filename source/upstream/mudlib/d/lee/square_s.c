// /d/lee/square_s.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "廣場");
    set("long", @LONG
這片廣場位在村中心偏南的位置，北面接著村中主路。南面可以前往李記當鋪，東邊就是廣場中央。
LONG
    );
    set("exits", ([
        "north" : __DIR__"square_w",
        "east" : __DIR__"square_c",
        "south" : __DIR__"pawnshop"
    ]));
    setup();
    replace_program(ROOM);
}
