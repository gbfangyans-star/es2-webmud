// /d/wutang/hut.c — 五堂鎮（B6）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "草屋");
    set("long", @LONG
一間用茅草與土牆搭成的簡陋草屋，是菜田主人的住處。屋裡擺著幾件農具與一張竹床，牆角堆著剛收成的蔬菜，屋簷下掛著幾串風乾的辣椒與玉米。門板上釘著好幾塊新補上的木板，看來是被野豬撞壞過不只一次。往東就是一大片菜田。
LONG
    );
    set("exits", ([
        "east" : __DIR__"field1",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
