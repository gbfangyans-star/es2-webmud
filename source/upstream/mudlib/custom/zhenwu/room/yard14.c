/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
南側另一片校場同樣擺著練兵木樁，地面散布細碎木屑與乾土。從這裡向北望去，層層校場一路延伸到大帳與軍營大門，整座振武軍營的規模一覽無遺。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"yard11",
        "west" : __DIR__"yard13",
    ]));
    set("objects", ([
        "/custom/zhenwu/npc/target_stake" : 1,
    ]));
    setup();
}
