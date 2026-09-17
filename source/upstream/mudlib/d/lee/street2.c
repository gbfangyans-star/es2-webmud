// /d/lee/street2.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
街道繼續向南延伸，北面通往村中央，南面就是村口大門。西側的小旅店常傳出店小二招呼客人的聲音。街邊擺著一個小攤子，賣冰糖葫蘆的小販正吆喝著招攬生意，紅通通的糖葫蘆插在草把上，看著就讓人食指大動，不少路過的孩童都忍不住多看兩眼。
LONG
    );
    set("objects", ([
        __DIR__"npc/hawthorn_seller" : 1
    ]));
    set("exits", ([
        "north" : __DIR__"street1",
        "west" : __DIR__"inn",
        "south" : __DIR__"gate_s"
    ]));
    setup();
    replace_program(ROOM);
}
