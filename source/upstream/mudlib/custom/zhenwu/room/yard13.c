/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
這裡是校場南端，幾具粗重木樁立在黃土地上，樁身滿是刀砍槍刺留下的傷痕。新兵常在此練習出手與步法，久而久之連周圍泥土都被踩得緊實，幾乎看不見雜草。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"yard10",
        "east" : __DIR__"yard14",
    ]));
    set("objects", ([
        "/custom/zhenwu/npc/target_stake" : 1,
    ]));
    setup();
}
