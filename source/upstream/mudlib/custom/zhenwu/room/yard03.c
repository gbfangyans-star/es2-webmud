/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
校場東北角視野開闊，往來軍士多從這裡穿過。地上用石灰與木樁分出操練的位置，遠處可見振武軍營大門，守門軍士的身影在門樓下來回巡視，營內一切井然有序。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "west" : __DIR__"yard02",
        "south" : __DIR__"yard06",
    ]));
    set("objects", ([
        "/custom/zhenwu/npc/target_stake" : 5,
    ]));
    set("map/area", "振武軍營");
    setup();
}
