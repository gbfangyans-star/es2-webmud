// /d/lee/eroad1.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
廣場東面的石子路筆直延伸，兩側逐漸由房舍轉為田地。往東仍可看見另一段道路與村口方向。路旁的屋舍漸漸稀疏，取而代之的是連片的田埂，偶有農人挑著擔子由此經過，留下一串深淺不一的腳印。
LONG
    );
    set("exits", ([
        "west" : __DIR__"square_e",
        "east" : __DIR__"eroad2"
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
