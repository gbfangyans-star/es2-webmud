/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
這片校場靠近大帳，黃土地被長年操演磨得平整堅實。幾根粗木立在場邊，木身遍布刀痕與撞擊留下的缺口，北風穿過營旗時發出獵獵聲響，使整座軍營顯得肅整而緊張。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "east" : __DIR__"yard03",
        "south" : __DIR__"yard05",
    ]));
    set("objects", ([
        "/custom/zhenwu/npc/target_stake" : 5,
    ]));
    setup();
}
