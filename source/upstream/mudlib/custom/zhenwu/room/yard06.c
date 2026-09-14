/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
這片校場緊鄰軍營大門，來往軍士不時從東邊經過。木製拒馬與練兵器具靠著場邊擺放，地面仍留有整隊操練形成的平直足跡，遠近都能聽見教官短促有力的號令。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"yard03",
        "south" : __DIR__"yard09",
        "west" : __DIR__"yard05",
        "east" : __DIR__"gate",
    ]));
    setup();
}
