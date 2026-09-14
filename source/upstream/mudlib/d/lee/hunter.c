// /d/lee/hunter.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "獵戶");
    set("long", @LONG
這是一戶獵人居住的小屋，牆邊掛著繩索、獸皮與修補過多次的竹簍。屋裡帶著淡淡煙燻味，門外連著村中的石子路。
LONG
    );
    set("objects", ([
        "/d/lee/npc/hunter" : 1
    ]));
    set("exits", ([
        "south" : __DIR__"wroad2"
    ]));
    setup();
    replace_program(ROOM);
}
