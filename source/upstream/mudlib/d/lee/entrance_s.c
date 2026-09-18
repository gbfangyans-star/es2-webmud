// /d/lee/entrance_s.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "村口");
    set("long", @LONG
這裡是李家村南面的村口，北方木製大門後便是村內街道。往西南沿著小路離村，便可回到雪亭一帶兩條河流交會的河邊。路邊立著一塊半人高的青石界碑年久失修，「李家村」三個字已被歲月磨得淺淡，碑角還纏著幾圈舊布條，像是往來旅客隨手繫上的平安結。幾名風塵僕僕的旅客或坐或倚在碑石邊，一邊揉著痠痛的腿腳，一邊互相打聽前方村鎮的近況。
LONG
    );
    set("exits", ([
        "north" : __DIR__"gate_s",
        "southwest" : "/d/snow/egate"
    ]));
    set("objects", ([
        __DIR__"npc/traveller" : 3
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
