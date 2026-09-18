/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "振武軍營大門");
    set("long", @LONG
兩扇厚重木門構成振武軍營的主要門戶，門板外包鐵條，兩側木柵高聳。守門士兵持槍立在門旁，目光不時掃過往來人群；門內便是操練校場，軍旗與號令聲從營中不斷傳來。往東就到雪亭鎮。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "west" : __DIR__"yard06",
        "east" : "/d/snow/sgate",
    ]));
    set("objects", ([
        "/custom/zhenwu/npc/soldier" : 2,
    ]));
    set("map/area", "振武軍營");
    setup();
}
