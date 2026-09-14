/* CUSTOM OLD PINE MAP — topology supplied by user; prose follows Snow-area style. */
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
黃土小路在此折向東南，兩側長著低矮灌木與零散老松。地上散著被風吹落的松針，踩上去略帶鬆軟，幾塊裸露石頭使路勢顯得不甚平整。回頭仍能辨出雪亭方向，前方則只見一條細路鑽入更深的林影。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "northwest" : __DIR__"path02",
        "southeast" : __DIR__"path04",
    ]));
    setup();
}
