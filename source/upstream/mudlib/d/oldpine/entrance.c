// /d/oldpine/entrance.c — 老松林（D6）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "老松林");
    set("long", @LONG
出了雪亭鎮往東不遠，便是這片綿延數里的老松林。高大的松樹一株挨著一株，枝葉遮天，即使是正午，林子裡也顯得陰暗。這裡原是雪亭鎮往來喬陰的捷徑，近來卻因為土匪出沒，旅人多半寧可繞道五堂鎮。路旁立著一塊被風雨侵蝕的木牌，上頭的字跡已經模糊難辨。往西可以回到雪亭鎮，往東南則有一條小路深入林中。
LONG
    );
    set("exits", ([
        "west" : "/d/snow/sgate",
        "southeast" : __DIR__"clearing_w",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
