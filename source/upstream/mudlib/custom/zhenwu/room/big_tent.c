/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "大帳");
    set("long", @LONG
一座厚重軍帳立在校場北端，帳布經風吹日曬已略顯褪色，帳前卻收拾得一塵不亂。兩側兵器架與軍旗排列整齊，往來士卒經過此處都不自覺放輕聲音，顯示這裡是軍中主將處理軍務的地方。
LONG
    );
    set("exits", ([
        "out" : __DIR__"yard04",
    ]));
    set("objects", ([
        "/custom/zhenwu/npc/mee_pei" : 1,
    ]));
    setup();
}
