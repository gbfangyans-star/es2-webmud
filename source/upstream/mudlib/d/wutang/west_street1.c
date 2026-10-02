// /d/wutang/west_street1.c — 五堂鎮（L12）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
五堂鎮的街道，往東不遠就是鎮中心的交叉路口，人聲漸漸熱鬧起來。路旁有幾個小販擺著攤子叫賣，偶爾還能看見幾隻從城外菜田跑進來的野豬，惹得鎮民一陣驚呼。
LONG
    );
    set("exits", ([
        "west" : __DIR__"west_street2",
        "east" : __DIR__"crossroad",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
