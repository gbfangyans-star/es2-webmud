// /d/lee/watermelon_s3.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "西瓜田");
    set("long", @LONG
李家村東南側的瓜田延伸到溪邊附近，水氣讓此處土壤較為鬆軟。沿田埂可回到西面的其他瓜田。田邊立著一座簡陋的稻草人，衣衫破舊，隨風輕輕晃動，多少能唬住幾隻膽小的鳥雀。
LONG
    );
    set("exits", ([
        "west" : __DIR__"watermelon_s2",
        "north" : __DIR__"watermelon_n3"
    ]));
    setup();
    replace_program(ROOM);
}
