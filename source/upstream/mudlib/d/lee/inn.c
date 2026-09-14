// /d/lee/inn.c
// 李家村復原版。CONFIRMED_MIXED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "小飯店");
    set("long", @LONG
這是一間規模很小的旅店，屋裡只有幾張老舊桌椅。店小二忙著招呼客人，說書先生李半仙偶爾在此停留，東門通往街道。
LONG
    );
    set("objects", ([
        "/d/lee/npc/waiter" : 1,
        "/d/lee/npc/li_ban_xian" : 1
    ]));
    set("exits", ([
        "east" : __DIR__"street2"
    ]));
    setup();
    replace_program(ROOM);
}
