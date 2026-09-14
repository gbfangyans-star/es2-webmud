// /d/lee/farm_w2.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "農家");
    set("long", @LONG
另一戶農家的院牆由土磚砌成，門口靠著犁與鋤頭。雞鳴與人聲不時從院內傳出，顯得十分尋常。
LONG
    );
    set("exits", ([
        "north" : __DIR__"wroad3"
    ]));
    setup();
    replace_program(ROOM);
}
