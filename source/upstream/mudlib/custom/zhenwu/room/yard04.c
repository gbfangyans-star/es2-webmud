/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
這裡是校場西側，土地上散著被踏碎的草梗與細石。附近常有士卒列隊練習步伐，沉重腳步把地面踩出一道道淺痕；向北可望見大帳，向東則是軍營較寬闊的操演區。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "in" : __DIR__"big_tent",
        "south" : __DIR__"yard07",
        "east" : __DIR__"yard05",
    ]));
    set("objects", ([
        "/custom/zhenwu/npc/zhenwu_soldier" : 5,
    ]));
    setup();
}
