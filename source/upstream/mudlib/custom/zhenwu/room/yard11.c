/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
校場中段寬敞平坦，場邊豎著供士卒練習的木架，黃土地上交錯著腳印與兵器拖痕。南北兩側都還有操演場地，軍士往來頻繁，讓這裡始終保持著忙碌的氣氛。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"yard08",
        "south" : __DIR__"yard14",
        "west" : __DIR__"yard10",
        "east" : __DIR__"yard12",
    ]));
    set("map/area", "振武軍營");
    setup();
}
