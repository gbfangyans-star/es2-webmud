// /d/lee/wroad1.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
這段石子路緊靠西村口，路旁泥地上留著車輪與牲口腳印。向東繼續走可以深入李家村，向西便是村口大門。路邊立著一塊簡陋的木牌，寫著「小心牲口」四個字，字跡歪斜，倒也透著幾分鄉野的樸拙。
LONG
    );
    set("exits", ([
        "west" : __DIR__"gate_w",
        "east" : __DIR__"wroad2"
    ]));
    setup();
    replace_program(ROOM);
}
