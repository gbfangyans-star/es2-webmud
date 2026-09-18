// /d/lee/gate_e.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "村口大門");
    set("long", @LONG
李家村東面的村口大門立在道路盡頭，門外很快便接近溪畔。木門兩旁有簡單的守望位置，方便村民巡看。厚重的木門終年開著，門板下緣已經磨出一道淺淺的弧痕，是無數車輪與腳步經年累月踩踏出來的。守衛倚在門邊的木樁上，一邊留意著往來行人，一邊靜靜聽著不遠處溪水潺潺的聲音，偶爾有村民挑著擔子經過，總會停下來寒暄兩句。
LONG
    );
    set("objects", ([
        "/d/lee/npc/guard" : 1
    ]));
    set("exits", ([
        "west" : __DIR__"eroad2",
        "east" : __DIR__"riverside_s"
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
