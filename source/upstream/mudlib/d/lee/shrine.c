// /d/lee/shrine.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "福祠");
    set("long", @LONG
小祠堂不大，石階與香爐都被村民擦拭得很乾淨。香火雖不旺盛，逢年過節仍有人前來祈求家宅平安與五穀豐收。
LONG
    );
    set("exits", ([
        "south" : __DIR__"wroad3"
    ]));
    setup();
    replace_program(ROOM);
}
