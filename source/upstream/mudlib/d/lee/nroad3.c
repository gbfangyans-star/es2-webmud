// /d/lee/nroad3.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
石子路到了村中心附近變得熱鬧，西側可見私塾的木門與窗紙。孩童讀書聲偶爾越牆而出，南面就是村內往來最頻繁的廣場。
LONG
    );
    set("exits", ([
        "north" : __DIR__"nroad2",
        "south" : __DIR__"square_w",
        "west" : __DIR__"school"
    ]));
    setup();
    replace_program(ROOM);
}
