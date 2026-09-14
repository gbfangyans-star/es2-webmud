/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
這裡位於軍營腹地，四周校場彼此相連，腳下黃土因長年操練而堅硬如石。軍士奔走時揚起薄薄塵霧，營旗、木樁與兵器架錯落在視野中，整片區域充滿規律而沉重的軍旅節奏。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"yard05",
        "south" : __DIR__"yard11",
    ]));
    setup();
}
