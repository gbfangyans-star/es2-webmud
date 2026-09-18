/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
軍營東南側的校場貼近營牆，幾面舊軍旗迎風拍響。操練留下的土坑已被反覆填平，木架旁散著斷裂的木片，顯示這裡長年承受高強度的軍事訓練。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"yard09",
        "west" : __DIR__"yard11",
    ]));
    set("map/area", "振武軍營");
    setup();
}
