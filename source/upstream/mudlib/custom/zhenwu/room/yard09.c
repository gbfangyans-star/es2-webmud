/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
東側校場靠近營牆，風從牆頭吹落，捲起細碎塵沙。幾處木樁上密布槍刺與刀劈的痕跡，場邊還留著拖動重物形成的深溝，是士卒鍛鍊體力與兵器技巧的地方。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"yard06",
        "south" : __DIR__"yard12",
    ]));
    setup();
}
