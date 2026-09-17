// /d/lee/nie_backroom.c
// NEW（李家村復原版新增房間，非原始 ES2 資料，由專案成員指定內容）
// 醫館內室，聶晟煉丹、歇息的地方。經 in 從醫館進入，out 回到醫館。

inherit ROOM;

void create()
{
    set("short", "丹房");
    set("long", @LONG
這裡是醫館後方的一間小室，靠牆放著一座青銅丹爐與丹鼎，爐火尚有些許餘溫，看起來不久前才煉過藥。
牆角一張矮榻鋪著薄被，榻邊小几上擺著一壺涼透的茶與幾卷翻開的醫書，這裡是聶晟煉丹與歇息的
地方，平時鮮少有外人進來走動探訪打擾。
LONG
    );
    set("exits", ([
        "out" : __DIR__"shrine"
    ]));
    setup();
    replace_program(ROOM);
}
