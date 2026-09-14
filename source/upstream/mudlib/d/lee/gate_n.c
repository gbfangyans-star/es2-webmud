// /d/lee/gate_n.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "村口大門");
    set("long", @LONG
李家村北面的村口大門由厚實木料搭成，門柱上留著長年風吹雨打的痕跡。門內石子路向南伸入村中，兩旁低矮屋舍與田地相間，來往村民大多在此放慢腳步。
LONG
    );
    set("exits", ([
        "south" : __DIR__"nroad1"
    ]));
    setup();
    replace_program(ROOM);
}
