// /d/lee/pawnshop.c
// 李家村復原版。CONFIRMED_MIXED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.
// MODIFIED：改用原始 ES2 的 HOCKSHOP 房間類型（/std/room/hockshop.c，作者 Annihilator），
// 取代先前另外寫的簡化版收購機制；典當/贖回/賣斷/收購轉售規則沿用原始程式，未自行更動。

#include <room.h>

inherit HOCKSHOP;

void create()
{
    set("short", "李記當鋪");
    set("long", @LONG
李員外在村裡的主要生意之一，掌櫃李嘯天替李家打理此處產業。附近的旅客、店鋪都會到這典當周轉，
櫃臺後堆著各式不同標記的木箱，看來頗為貴重。牆上掛著一幅字畫，寫著「童叟無欺」四個大字，算是給
上門的客人先吃顆定心丸。櫃臺邊還擺著一把算盤與幾疊當票，透著幾分精打細算的生意氣息。
LONG
    );
    set("objects", ([
        "/d/lee/npc/lee_xiao_tian" : 1,
        "/obj/food/mooncake" : 2
    ]));
    set("exits", ([
        "east" : __DIR__"street1"
    ]));
    setup();
    replace_program(HOCKSHOP);
}
