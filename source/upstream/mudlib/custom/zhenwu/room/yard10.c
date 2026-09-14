/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
這片校場位在中軍一側，往西可通向棚場與軍營外圍。土地中央被無數雙軍靴踩得發亮，附近不時傳來整隊口令；在此停留片刻，便能看見軍士依照號令往各處操演。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"yard07",
        "south" : __DIR__"yard13",
        "east" : __DIR__"yard11",
        "west" : __DIR__"shed",
    ]));
    set("objects", ([
        "/custom/zhenwu/npc/lu_xinien" : 1,
    ]));
    setup();
}
