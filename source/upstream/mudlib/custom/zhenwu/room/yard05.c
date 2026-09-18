/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
校場中央人聲與兵器碰撞聲最為集中，四周黃土被反覆踩踏得幾乎不生寸草。場邊插著幾面振武軍旗，風一吹便整齊展開，讓人一踏進來便感受到軍伍特有的森嚴氣息。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"yard02",
        "south" : __DIR__"yard08",
        "west" : __DIR__"yard04",
        "east" : __DIR__"yard06",
    ]));
    set("map/area", "振武軍營");
    setup();
}
