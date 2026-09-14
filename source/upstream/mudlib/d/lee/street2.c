// /d/lee/street2.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
街道繼續向南延伸，北面通往村中央，南面就是村口大門。西側的小飯店常傳出店小二招呼客人的聲音。
LONG
    );
    set("exits", ([
        "north" : __DIR__"street1",
        "west" : __DIR__"inn",
        "south" : __DIR__"gate_s"
    ]));
    setup();
    replace_program(ROOM);
}
