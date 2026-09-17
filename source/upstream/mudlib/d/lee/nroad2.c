// /d/lee/nroad2.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
這段石子路兩旁房舍漸密，西側雜貨鋪門口堆著日用雜物。路面被車輪與腳步磨得發亮，向南可以繼續前往村中的廣場。路旁幾隻雞悠閒地啄著地上散落的穀粒，對來往的行人視若無睹，替這段熱鬧的路添了幾分生活氣息。
LONG
    );
    set("exits", ([
        "north" : __DIR__"nroad1",
        "south" : __DIR__"nroad3",
        "west" : __DIR__"grocery"
    ]));
    setup();
    replace_program(ROOM);
}
