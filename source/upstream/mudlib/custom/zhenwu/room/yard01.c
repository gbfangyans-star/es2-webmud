/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
軍營北側的校場鋪著踩實的黃土，地面留著密密麻麻的靴印與拖曳兵器的痕跡。晨昏操練時的喝聲彷彿仍在營中迴盪，木架與兵器架沿場邊排開，空氣裡混著皮革、汗水和乾土的氣味。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "south" : __DIR__"yard04",
        "east" : __DIR__"yard02",
        "north" : __DIR__"big_tent",
    ]));
    setup();
}
