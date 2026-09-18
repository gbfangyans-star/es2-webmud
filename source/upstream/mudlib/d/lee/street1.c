// /d/lee/street1.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
村中央往南的街道比石子路平整些，兩側屋舍緊靠。西側就是李記當鋪，南北來往的人多半從這裡穿過。屋簷下掛著幾盞燈籠，入夜後會點起微弱的燈火，照亮這段人來人往的街道。
LONG
    );
    set("exits", ([
        "west" : __DIR__"pawnshop",
        "north" : __DIR__"square_c",
        "south" : __DIR__"street2",
        "east" : __DIR__"watermelon_s1"
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
