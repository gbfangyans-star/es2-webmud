/* CUSTOM OLD PINE MAP — topology supplied by user; prose follows Snow-area style. */
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
小路走到老松林較深處的一片空隙，四周古松環立，地面覆著厚厚松針，中央卻被長年踩出一塊堅實黃土。這裡遠離雪亭喧鬧，只有松濤與風聲相伴，是個清靜卻帶著幾分肅殺氣息的所在。路向西折回林外，附近似乎有人在此候著過往行人。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "west" : __DIR__"path09",
    ]));
    set("objects", ([
        "/custom/oldpine/npc/kao_shen" : 1,
    ]));
    setup();
}
